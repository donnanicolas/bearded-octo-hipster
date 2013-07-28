#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "tramullator.h"

int opensocket (int ipv){
int sd;

if (ipv == 4)
{
	struct sockaddr_in dir = {};
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
	return sd;
}
else
{
	struct sockaddr_in6 dir = {};
	sd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sd < 0){
		perror("socket");
		return -1;
	}

	int opt=1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof (opt));
//	setsockopt(sd, IPPROTO_TCP, TCP_NODELAY , (char *) &opt, sizeof (opt));

	dir.sin6_family = AF_INET6;
	dir.sin6_port = htons(atoi("3001"));
	inet_pton(AF_INET6, "::", &dir.sin6_addr);
	if (bind(sd , (struct sockaddr *)&dir , sizeof dir) < 0 ){
		perror ("bind");
		return -1;
	}
	return sd;
}
}
