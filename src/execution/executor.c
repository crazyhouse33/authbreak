#include "output.h"

#include <unistd.h>//fork
#include <stdio.h>//pipe
#include <stdlib.h>//EXIT_SUCCESS
#include <sys/wait.h>


#define READ 0
#define WRITE 1

Output* executor_get_output(char* command, char** prompt, double timout)
{
	int pipefd[2];
	pid_t cpid;

	cpid = fork();

	if (cpid == 0) {    /* Child reads from pipe */
		close(pipefd[WRITE]);          /* Close unused write end */
		dup2(STDIN_FILENO, pipefd[READ]); /*Replace STDIN by our pipe*/
		/*Do child stuff*/

		//EXIT
		close(pipefd[READ]);
		_exit(EXIT_SUCCESS);

	} else {            /* Parent writes argv[1] to pipe */
		close(pipefd[READ]);          /* Close unused read end */

		//EXIT
		close(pipefd[WRITE]);          /* Reader will see EOF */
		wait(NULL);                /* Wait for child */
		exit(EXIT_SUCCESS);
	}
}

