#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include "lib/pthread_pool.h"
#include "tramullator.h"
#include "string.h"

#include <stdio.h>

int main (int argc, char *argv[]) {
	pthread_pool *tp = NULL;
	int  piped[2]
	  , sd
	  , csd;

	/*   log   */
	if(pipe(piped) < 0) {
		printf("NOp!!\n");
		return 0;	
	}
	

	if(fork() == 0) {
		int readed = 0
		  , logd;
		char buffer[1024]
		   , *datestring;

		time_t date;

		memset(buffer, '\0', 1024);

		logd = open("log.out", O_RDWR | O_CREAT | O_APPEND, 0644);
		if(logd < 0) {
			printf("Nop!!!\n");
			return -1;
		}

		close(piped[1]);

		while((readed = read(piped[0], buffer, 1024)) > 0) {
			time(&date);
			datestring = ctime((const time_t *)&date);
			// -1 to avoit the \n at the end of datestring
			write(logd, datestring, (strlen(datestring) - 1));
			write(logd, buffer, readed);
		}
		return 0;
	}

	close(piped[0]);
	/* end log */

	sd = opensocket();

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

	while ((csd = accept(sd, NULL, NULL)) > 0) {

		if (csd <1)
		{
			perror("accept");
			return -1;
		}
		
		write(piped[1], " Request Received\n", 19);

		add_new_task(&(tp->list), tramullo, (void *) &csd, 1);	
	}

	return 0;
}
