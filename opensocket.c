#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include "tramullator.h"

int opensocket () {

	int sd, s;
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	struct sockaddr_in6 dir = {};

	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;


	s = getaddrinfo(NULL, "3000", &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}



	for (rp = result; rp != NULL; rp = rp->ai_next) {
		printf("%d\n", rp->ai_family);
		printf("%d\n", AF_INET);

		sd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sd == -1)
			continue;
		//rp->ai_addr.sin_port = htons(atoi("3000"));
		if (bind(sd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;                  /* Success */

		close(sd);
	}
	printf ("sd: %d\n", sd);

	int opt=1;
	//setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof (opt));
//	setsockopt(sd, IPPROTO_TCP, TCP_NODELAY , (char *) &opt, sizeof (opt));
	return sd;
}
