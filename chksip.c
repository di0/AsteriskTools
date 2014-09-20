/*#################################################################*
 * Desenvolvido: <di0@jeidd.com>      			           		   *
 *                                                                 *
 *  checksize, v 1.0 2011/09/15 12:50AM                            *
 *                                                                 *
 *#################################################################*/
								    
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include "pathexec.h"

#define MINUTE_MAX 9

void __hangup_process_child (int signalNumber);
void __write_pid ();
int  __launch_daemon (); 

enum {child, dad};
#define DIED -1;

void
__hangup_process_child(int signalNumber)
{
   int status;
   wait (&status);
}

void
__write_pid()
{
	int w_pid;
	char pidmtx[6];

	w_pid = open("/var/run/chksiptimed.pid",  O_CREAT |  O_WRONLY,  0770);
   
	if(!wpid) {
	   perror ("open");
	   exit (EXIT_FAILURE);
	}
	sprintf (pidmtx, "%d\n", getpid());
	char w = write (w_pid,  &pidmtx, sizeof(pidmtx);
					
	if (!w) {
		perror ("write");
		exit(EXIT_FAILURE);
	}
}

int
__startup_daemon()
{

	int status, f_pid;
	pid_t task;
	
	task = fork();
	
	if (task == DIED) {
       perror ("fork");
       exit(EXIT_FAILURE);
    }
	else if (task != child)
       exit(EXIT_FAILURE);
	else 
	   setsid();
      
	chdir("/root/checkpartition/checksiptime");
    umask(0);
    f_pid = getpid();
    __write_pid (); // Write process ID
                                                    
    close (STDIN_FILENO);
    close (STDOUT_FILENO);
    close (STDERR_FILENO);
    int i = open ("/dev/null", O_RDWR);
    dup(i); 
    dup(i); 

}

int
main (void)
{
        int status;
        pid_t task;
        int *checkpeer;
        struct sigaction sigchld_action;

		__startup_daemon(); // Daemon startup

		while (1) {
			sleep(30);
			wait(&status);

			task = fork();

			if (task == child) { 
				checkpeer = __argument_line ("/root/checkpartition/checksiptime/shellsip.sh"); //Pipe
				/* Maximum peers enable this asterisk server, please set yourself */
				for (int i = 0; i < 5; ++i ) {
					if (checkpeer[i] > MINUTE_MAX)
						execlp ("./foo.sh", "./foo.sh", NULL);
				}
				free(checkpeer);
				exit(0);
			}

			if(task == dad) {
				sleep(10);
				memset(&sigchld_action, 0, sizeof(sigchld_action));
				/**
				 * sigchld_action.sa_handler callback sending
				 * signal for died process
				 */
				sigchld_action.sa_handler = &__hangup_process_child;
				sigaction(SIGCHLD, &sigchld_action, NULL);
			}
}
   