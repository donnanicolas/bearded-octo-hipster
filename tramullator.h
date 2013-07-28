#ifndef _TRAMULLATOR_H_
#define _TRAMULLATOR_H_

	#include <sys/socket.h>
        #include <netinet/in.h>
        #include <netinet/tcp.h>
        #include <signal.h>
        #include <arpa/inet.h>

	void * tramullo (void* param);
	int opensocket (int);



#endif
