CC = g++
CCS = semaphore.cpp
OBJS = semaphore.o

semaphore.o : $(CCS)
	$(CC) -c $(CCS)

semaphore : $(OBJS)
	$(CC) $(OBJS) -o semaphore

clean : 
	del $(OBJS)