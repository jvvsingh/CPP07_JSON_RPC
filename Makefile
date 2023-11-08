# Makefile for HW3 Web Report, ecs36b, f2020
#

CC = g++ -std=c++14
CFLAGS = -g -g -I/opt/homebrew/include

# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

# CORE_INCS =	Core.h Transaction.h Person.h
# CORE_OBJS =	Core.o Transaction.o Person.o
# SHADOW_INCS = Shadow_Flight.h Shadow_Person.h
# SHADOW_OBJS = Shadow_Flight.o Shadow_Person.o 

LDFLAGS = -L/opt/homebrew/lib -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

# rules.
all: 	wrclient wrserver

#
#

wrclient.h:		ecs36b_wr.json
	jsonrpcstub ecs36b_wr.json --cpp-server=wrServer --cpp-client=wrClient

wrserver.h:		ecs36b_wr.json
	jsonrpcstub ecs36b_wr.json --cpp-server=wrServer --cpp-client=wrClient

wrclient.o:		wrclient.h wrclient.cpp
	$(CC) -c $(CFLAGS) wrclient.cpp

wrserver.o:		wrserver.h wrserver.cpp
	$(CC) -c $(CFLAGS) wrserver.cpp

wrclient:		wrclient.o
	$(CC) -o wrclient wrclient.o $(LDFLAGS)

wrserver:		wrserver.o
	$(CC) -o wrserver wrserver.o $(LDFLAGS)

clean:
	rm -f *.o *~ core wrclient wrserver wrclient.h wrserver.h
