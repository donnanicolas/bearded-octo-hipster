#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "md5/md5.c"

void* tramullo (void* param){
	int readed = 0, i=0;
	char buffer[1024], *request = NULL;
	unsigned char result[16];

	int socketfd = *(int *) param;

	MD5_CTX ctx;

	printf("Request recieved\n");

	request = (char *) malloc(sizeof(char) * 1024);

	if(request == NULL) {
		write(socketfd, "Error 500\n", 10);
		return NULL;
	}

	memset(buffer, '\0', 1024);	
	memset(request, '\0', 1024);
	memset(result, '\0', 16);

	MD5_Init(&ctx);

	while((readed = read(socketfd, buffer, 1024)) > 0) {
		buffer[readed] = 0;
		
		MD5_Update(&ctx, buffer, readed);
	}

	MD5_Final(result, &ctx);	

	write(socketfd, result, 16);

	close (socketfd);
	printf("Request handled\n");
	return NULL;
}
