CC = g++
CCS = event.cpp
OBJS = event.o

event.o : $(CCS)
	$(CC) -c $(CCS)

event : $(OBJS)
	$(CC) $(OBJS) -o event

clean : 
	del $(OBJS)