#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{
 void sigint_handler(int sig);
 void sigtstp_handler(int sig);
 void sigquit_handler(int sig);
 int child;
 char s[200];
 int pipefds[2];
 char buffer[200];

 //Signal
 if (signal(SIGINT, sigint_handler) == SIG_ERR){
 perror("signal SIGINT");
 exit(1);
 }
 else if (signal(SIGTSTP, sigtstp_handler) == SIG_ERR){
 perror("signal SIGTSTP");
 exit(1);
 }
 else if (signal(SIGQUIT, sigquit_handler) == SIG_ERR){
 perror("signal SIGQUIT");
 exit(1);
 }

 //Pipe
 if(pipe(pipefds) == -1) {
 perror("pipe");
 exit(EXIT_FAILURE);
 }

 //Parent
 printf("Enter instruction for child:");

 //Parent Input
 if (fgets(s, sizeof(s), stdin) == NULL){
perror("signal PARENT");
 }
 else {
 s[strcspn(s, "\n")] = '\0';
 printf("you entered: %s\n\n", s);
}

 //Child
 printf("Enter how many child you want? :");
 scanf("%d", &child);

 if (child  < 1){
 perror("child error");
 }
 else {
 printf("You entered: %d\n\n", child);
 }

 printf("Beri arahan kepada anak. ");
 write(pipefds[1], &s, sizeof(s));
 printf("Terima.\n\n");

 printf("Anak terima arahan. ");\
 read(pipefds[0], &buffer, sizeof(buffer));
 printf("done.\n\n");

 for(int i = 0; i <("%d", child); i++) {
 pid_t pid = fork();

 if(pid == 0) {
 printf("This child recieve '%s' from parent\n\n", buffer);
 exit(0);
}
 else {
 printf("waiting for child...\n");
 wait(NULL);
 close(pipefds[1]);
 close(pipefds[0]);
 printf("child finished.\n\n");
}
}
}

//Ctrl+C
void sigint_handler(int sig)
{
 printf("Ctrl + C Captured \n");
}

//Ctrl+Z
void sigtstp_handler(int sig)
{
 printf("Ctrl + Z Captured \n");
}

//Ctrl+Backspace
void sigquit_handler(int sig)
{
 printf("Ctrl + Backspace Captured \n");
}
