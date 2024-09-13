#include <stdio.h>
#include <unistd.h>

main() {
	int i;
	int pid;
	int pid2;
	int pid3;
	pid = fork();
	pid2 = fork();
	pid3 = fork();
	printf("hellooo\n");
	//all original parents
	if(pid > 0){
		if(pid2 > 0){
			if(pid3 > 0){
				printf("PPP\n");
			}
			else{
				printf("PPC\n");
			}
		}
		else{
			if(pid3 > 0){
				printf("PCP\n");
			}
			else{
				printf("PCC\n");
			}
		}
	}
	//all original children
	else{
		if(pid2 > 0){
			if(pid3 > 0){
				printf("CPP\n");
			}
			else{
				printf("CPC\n");
			}
		}
		else{
			if(pid3 > 0){
				printf("CCP\n");
			}
			else{
				printf("CCC\n");
			}
		}
	}
}
