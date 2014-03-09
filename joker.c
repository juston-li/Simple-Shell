/*Joker shell
 *
 *Shell with a specified timeout for commands
 *
 *@Juston Li
 */

#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "joker.h"

int pid;
extern char **environ;
const char shell_msg[] = "joker#";
const char too_many_args_msg[] = "Too many arguments\nUsage: ./joker 'NUMBER' \
-where NUMBER is the time limit a process can run\n   or: ./joker          -No time limit\n";
const char nonint_args_msg[] = "Improper argument. Argument must be a positive integer.\n";
const char overflow_msg[] = "Input was too long. Acceptable arguments must be less than 1024 bytes.\n";
const char kill_msg[] = "Let's put a smile on that FACE!\n";
char fail_kill_msg[] = "Oh, you. You just couldn't let me go, could you? This is what\
 happens when an unstoppable force meets an immovable object.\n";


/*alarm child has gone past time limit, kill and print fail_msg*/
void alarm_handler (int signum) {	
	write(1,kill_msg,sizeof(kill_msg)-1);
	kill(pid, SIGKILL);
}

int main( int argc, char** argv) {
	int timer;
	if (argc == 1) {
		timer = 0;
	} else if (argc > 2) {
		write(1,too_many_args_msg,sizeof(too_many_args_msg));
		return 0;
	}  else {
		timer = myatoi(argv[1]);
		if(timer == -1) {
			write(1,nonint_args_msg,sizeof(nonint_args_msg));
			return 0;
		}
	}
	signal(SIGALRM, alarm_handler);
	while(1) {
		int space_count = 0;
		char buf[10240] = {'\0'};
		int buf_count = 0;	

		/*Display shell*/
		write(1,shell_msg,sizeof(shell_msg));
		int readerror = read(0, buf, sizeof(buf));
		if (readerror ==-1) {
			perror("Failed to read command");
		}
		if (buf[1024] != '\0') {
			write(1, overflow_msg, sizeof(overflow_msg));
			continue;
		}
		/* count spaces parse*/
		while(buf[buf_count] != '\0') {
			if (buf[buf_count] == ' ') {
				space_count++;
			}
			buf_count++;
		}
		/*get rid of \n at the end from enter*/
		buf[buf_count-1] = '\0';
		/*Pass buf to parse to add each arg to newargv
			Handle multiple spacing here. bad parse implementation*/
		char* newargv[1024] = {'\0'};
		int arg_counter = 0;
		int buf_counter = 0;
		while (buf_counter < space_count+1) {
			char* parsed = parse(buf,buf_counter);
			if(parsed[0]=='\0') {
				buf_counter++;
			} else {
				newargv[arg_counter] = parsed;
				buf_counter++;
				arg_counter++;	
			}
		}
		
		pid = fork();
		if (!pid) {  
			execve(newargv[0], newargv, environ);
			perror ("Command failed"); 	/*if child reaches here, exec failed*/					
			_exit(128);					/*let parent know with status 128*/
		} else {
			int status = 0;
			int exit = 0;
			alarm(timer);
			wait(&status);
			/*Child returned before alarm, cancel alarm*/
			alarm(0);
			if (WIFEXITED(status)) {
				exit = WEXITSTATUS(status);
			}
			/*Print failed to kill message if child wasn't killed by 
			  signal or terminated with error status*/
			if ( !WIFSIGNALED(status) && exit != 128) {
				write(1,fail_kill_msg,sizeof(fail_kill_msg));	
			}
		}
	}
}
