#include <stdio.h>
#include <unistd.h>

main() {
	int i;
	for (i = 0; i < 3; i++){
		fork();
	}
	printf("hello\n");
}
