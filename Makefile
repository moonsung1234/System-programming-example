
CC = g++
CCS = init_register.cc
OBJS = init_register.o

init_register.o : $(CCS)
	$(CC) -c $(CCS)

init_register : $(OBJS)
	$(CC) $(OBJS) -o init_register

clean : 
	del $(OBJS)