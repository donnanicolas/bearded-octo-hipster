#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "lib/pthread_pool.h"
#include "tramullator.h"
#include "string.h"

#include <stdio.h>

int main (int argc, char *argv[]) {
	pthread_pool *tp = NULL;
	int  piped[2]
	  , sd
	  , csd;

	struct sockaddr_in dir = {};
	
	tp = pthread_pool_create(NULL);
	if(tp == NULL) {
		write(2, "No se pudo crear el thread pool!\n", 33);
		return -1;
	}

	printf ("threads: %d\n", tp->current);

	sd = socket(AF_INET,SOCK_STREAM,0);
	if (sd < 0){
		perror ("socket");
		return -1;
	}

	int opt=1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof (opt));

	dir.sin_family = AF_INET;
	dir.sin_port = htons(atoi("3000"));
	inet_pton(AF_INET, "0.0.0.0", &dir.sin_addr);
	if (bind (sd, (struct sockaddr *)&dir ,sizeof dir) < 0){
		perror ("bind");
		return -1;
	}
	
	listen (sd,10);

	printf("listening...\n");

	if(pipe(piped) < 0) {
		printf("NOp!!\n");
		return 0;	
	}
	

	if(fork() == 0) {
		int readed = 0
		  , logd;
		char buffer[1024];

		memset(buffer, '\0', 1024);

		logd = open("log.out", O_RDWR | O_CREAT | O_APPEND, 0644);
		if(logd < 0) {
			printf("Nop!!!\n");
			return -1;
		}

		close(piped[1]);

		while(readed = read(piped[0], buffer, 1024)) {
			printf("llego al pipe: %s\n", buffer);
			write(logd, buffer, readed);
		}
		return 0;
	}

	close(piped[0]);

	while ((csd = accept(sd, NULL, NULL)) > 0) {
		write(piped[1], "Request Recieved\n", 17); 
		add_new_task(&(tp->list), tramullo, (void *) &csd, 1);	
	}

	return 0;
}
