#include "executor.h"
#include "argv.h" //buildarg and buffercontrolling
#include "delayer.h"
#include "error.h"
#include "file_info.h" //search_executable
#include "timer.h"
#include <errno.h>  //perror
#include <stdio.h>  //pipe
#include <stdlib.h> //EXIT_SUCCESS
#include <string.h> //strlen
#include <sys/wait.h>
#include <unistd.h> //fork

Delayer exec_delayer;
Delayer prompt_delayer;
bool useless_exec;
bool useless_prompt;

#define READ 0
#define WRITE 1

static void executor_prepare_argv(char **argv) {
  // put a binary file to remove any need for a PATH search
  char *exe = search_executable(argv[0]);
  if (exe == NULL)
    controlled_error_msg(3, "Cannot find the executable %s\n", argv[0]);
  argv[0] = exe;
}

static void executor_prepare_delayers(double delay_min, double delay_rand, double prompt_delay, double prompt_delay_rand) {
  Delayer_init(&exec_delayer, delay_min, delay_rand);
  Delayer_init(&prompt_delayer, prompt_delay, prompt_delay_rand);
  useless_prompt = Delayer_is_useless(&prompt_delayer);
  useless_exec = Delayer_is_useless(&exec_delayer);
}

void executor_prepare(char **argv, double delay_min, double delay_rand, double prompt_delay, double prompt_delay_rand) {
  executor_prepare_argv(argv);
  executor_prepare_delayers(delay_min, delay_rand, prompt_delay, prompt_delay_rand);
}

static void child_life(char **argv, char **envp) {
  /*Do child stuff*/
  execve(*argv, argv, envp);
  perror("Process creation failed");
}

// TODO better control over when to send in pipe
static void parent_life(int read_fd, int write_fd, char **prompt, Output *output) {
  // inject prompt
  size_t i = 0;
  char *cur_prompt;
  // TODO polling to play with prompt and reads
  while (cur_prompt = prompt[i++]) {
    write(write_fd, cur_prompt, strlen(cur_prompt)); // TODO dont call strlen and control ourself the size?
  }
  read_append_into_Output(read_fd, output);
}

// TODO optim: reuse the same pipe over and over
void executor_get_output_no_delay(char **argv, char **prompt, char **envp, double timout, Output *output) {

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
  parent_life(pipe_son[READ], pipe_father[WRITE], prompt, output);

  // EXIT
  close(pipe_father[WRITE]); /* Reader will see EOF */
  int status;
  waitpid(cpid, &status, 0); /* Wait for child terminaison*/
  output->term_time = get_time_ns() - t1;
  output->exit_status = WEXITSTATUS(status);
  close(pipe_son[READ]);
}

void executor_get_output(char **argv, char **prompt, char **envp, double timout, Output *output) {
  executor_get_output_no_delay(argv, prompt, envp, timout, output);
  if (!useless_exec) // I hope compiler is smart enought to one-time-ify for the default mode
    Delayer_delay(&exec_delayer);
}
