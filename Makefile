CC = gcc
CFLAGS = -Wall
LIBS = -pthread
LUUID = -luuid

final: server.c tramullo.c opensocket.c lib/pthread_pool.o lib/task_list.o lib/return_list.o lib/priority_list.o lib/task_queue.o
	$(CC) $(CFLAGS) $(LIBS) -o $@.sh $^ $(LUUID)
	./$@.sh

client: client.c
	$(CC) $(CFLAGS) $(LIBS) -o $@.sh $^
	./$@.sh 100 100

nctest:
	echo "asdasd" | netcat ::1 3000	
	echo "asdasd" | netcat 127.0.0.1 3000
	echo "asdasd" | md5sum

clean: 
	rm *.sh *.out
