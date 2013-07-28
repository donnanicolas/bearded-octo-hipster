CC = gcc
CFLAGS = -Wall
LIBS = -pthread
LUUID = -luuid
PYTHON = -I /usr/include/python2.7 -lpython2.7

final: server.c tramullo.c lib/pthread_pool.o lib/task_list.o lib/return_list.o lib/priority_list.o lib/task_queue.o
	$(CC) $(CFLAGS) $(LIBS) -o $@.sh $^ $(LUUID) $(PYTHON)
	./$@.sh

client: client.c
	$(CC) $(CFLAGS) $(LIBS) -o $@.sh $^
	./$@.sh 100 100

clean: 
	rm *.sh *.out
