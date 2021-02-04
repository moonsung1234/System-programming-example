CC = g++
CCS = thread_pool.cpp
OBJS = thread_pool.o

thread_pool.o : $(CCS)
	$(CC) -c $(CCS)

thread_pool : $(OBJS)
	$(CC) $(OBJS) -o thread_pool

clean : 
	del $(OBJS)