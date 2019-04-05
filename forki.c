#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h>

void waitexample() 
{ 
	int stat; 
	pid_t forki = fork();
  
	// This status 1 is reported by WEXITSTATUS 
	if (forki == 0) 
		exit(1); 
	else
		wait(&stat); 
	if (WIFEXITED(stat)) 
		printf("Exit status: %d\n", WEXITSTATUS(stat)); 
	else if (WIFSIGNALED(stat)) 
		psignal(WTERMSIG(stat), "Exit signal"); 
} 
  
// Driver code 
int main() 
{ 
	waitexample(); 
	return 0; 
} 
