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
	  , ipv
	  , csd;

	/*   log   */
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

		while((readed = read(piped[0], buffer, 1024)) > 0) {
			printf("llego al pipe: %s\n", buffer);
			write(logd, buffer, readed);
		}
		return 0;
	}

	close(piped[0]);
	/* end log */


//	if (fork())
//		ipv=4;
//	else
		ipv=6;
	sd = opensocket(ipv);

	/* pthread_pool create */
	tp = pthread_pool_create(NULL);
	if(tp == NULL) {
		write(2, "No se pudo crear el thread pool!\n", 33);
		return -1;
	}

	printf ("threads: %d\n", tp->current);
	/* end pthread_pool create */


	listen (sd,10);
	printf("listening...\n");

	struct sockaddr adr;
	int lenn;
	while ((csd = accept(sd, &adr, &lenn)) > 0) {

	if (csd <1)
	{
		perror("accept");
		return -1;
	}

		write(piped[1], adr.sa_data, 35);
		write(csd, "alo\n", 4);
		add_new_task(&(tp->list), tramullo, (void *) &csd, 1);	
	}

	return 0;
}
