#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void* tramullo (void* param){
	int readed = 0, i=0;
	char buffer[1024], *request = NULL, *result = NULL;

	int socketfd = *(int *) param;

	printf("Request recieved\n");

	request = (char *) malloc(sizeof(char) * 1024);

	if(request == NULL) {
		write(socketfd, "Error 500\n", 10);
		return NULL;
	}

	memset(buffer, '\0', 1024);	
	memset(request, '\0', 1024);

	while((readed = read(socketfd, buffer, 1024)) > 0) {
		buffer[readed] = 0;
		write(socketfd, buffer, readed);
		/*
		if(i > 0) {
			//Considerar asignar solo lo necesario en caso de que sea menor a 1024
			request = (char * ) realloc(request, sizeof(char) * 1024 * i + 1);
			memset((request + (1024 * i)), '\0', 1024);
			strcpy((request + (1024 * i)), buffer);
		} else {
			strcpy(request, buffer);
		}
		i++;
		*/
	}

	//object = PyRun_String(request, Py_file_input, d, d);

	//result = PyString_AsString(object);
	//write(socketfd, result, strlen(result));

	close (socketfd);
	printf("Request handled\n");
	return NULL;
}
