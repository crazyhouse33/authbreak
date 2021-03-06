#include "executor.h"
#include "argv.h" //buildarg and buffercontrolling
#include "error.h"
#include "file_info.h" //search_executable
#include "timer.h"
#include <errno.h>  //perror
#include <stdio.h>  //pipe
#include <stdlib.h> //EXIT_SUCCESS
#include <string.h> //strlen
#include <sys/wait.h>
#include <unistd.h> //fork

#define READ 0
#define WRITE 1

void executor_prepare_argv(char **argv) {
  // put a binary file to remove any need for a PATH search
  char *exe = search_executable(argv[0]);
  if (exe == NULL)
    controlled_error_msg(3, "Cannot find the executable %s\n", argv[0]);
  argv[0] = exe;
}

static void child_life(char **argv, char **envp) {
  /*Do child stuff*/
  execve(*argv, argv, envp);
  perror("Process creation failed");
}

// TODO better control over when to send in pipe
static void parent_life(int read_fd, int write_fd, char **prompt, size_t prompt_number, Output *output) {
  // inject prompt
  for (int i = 0; i < prompt_number; i++) {
    write(write_fd, prompt[i], strlen(prompt[i])); // TODO dont call strlen and control ourself the size?
  }
  size_t readed = 0;
  size_t new_read = 1;
  while (new_read > 0) { // we stop when read return error or no data (generally =>  end of process), maybe se problems could occur here.
    new_read = read_append_into_Output(read_fd, output, &readed);
  }
  output->out[readed] = 0;
}

// TODO optim: reuse the same pipe over and over
Output *executor_get_output(char **argv, char **prompt, size_t prompt_number, char **envp, double timout) {

  Output *output = Output_new();
  int pipe_father[2];
  int pipe_son[2];

  pipe(pipe_father);
  pipe(pipe_son);

  pid_t cpid;

  size_t argc;

  unsigned long t1 = get_time_ns();
  cpid = fork();

  if (cpid == 0) { /* Child reads from pipe */
    /*Listening on father pipe*/
    close(pipe_father[WRITE]);             /* Close unused write end */
    dup2(pipe_father[READ], STDIN_FILENO); /*Replace STDIN by our pipe*/

    /*Redirecting stdout and stder to the write pipe*/
    close(pipe_son[READ]);
    dup2(pipe_son[WRITE], STDOUT_FILENO); /*Replace STDOUT by our pipe*/
    dup2(pipe_son[WRITE], STDERR_FILENO);

    child_life(argv, envp);

    // EXIT (executed only if exevp failed)
    close(pipe_father[READ]);
    close(pipe_son[WRITE]);
    _exit(EXIT_FAILURE);
  }
  // Parent code
  close(pipe_father[READ]); /* Close unused read end */
  close(pipe_son[WRITE]);
  parent_life(pipe_son[READ], pipe_father[WRITE], prompt, prompt_number, output);

  // EXIT
  close(pipe_father[WRITE]); /* Reader will see EOF */
  int status;
  waitpid(cpid, &status, 0); /* Wait for child terminaison*/
  output->term_time = get_time_ns() - t1;
  output->exit_status = WEXITSTATUS(status);
  close(pipe_son[READ]);
  return output;
}
