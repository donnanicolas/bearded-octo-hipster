#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void *sendData(void *arg) {
	int connections = *(int *) arg
	  , i = 0
	  , fd;

	struct sockaddr_in dir= {};

	
	for(i=0; i < connections; i++) {
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if(fd < 0) {
			perror("socket");
			return NULL;
		}

		dir.sin_family = AF_INET;
		dir.sin_port = htons(3000);
		inet_aton("127.0.0.1",&dir.sin_addr);
	
		if(connect(fd, (struct sockaddr *) &dir, sizeof dir) < 0) {
			perror("connect");
			return NULL;
		}
		write(fd, "test\n", 6);
		printf("%d\n", i);
	}
	return NULL;
}


int main(int argc, char *argv[]) {

	int i = 0
	  , concurrency
	  , quantity;

	pthread_t thread;

	pthread_attr_t *attr = NULL;

	if(argc < 3) {
		printf("Debe ingresar por lo menos 2 argumentos");
		return -1;
	}

	concurrency = atoi(argv[1]);
	quantity = atoi(argv[2]);

	printf("%d\n%d\n", concurrency, quantity);

	for(i=0; i < concurrency; i++) {
		int s;
		s = pthread_create(&thread, attr, sendData, &quantity);
	}
	
	pthread_exit();

	return 0;
}
