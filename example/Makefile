
CC = arm-linux-gnueabihf-gcc
CFLAGS = -fpic -DRTI_UNIX -DRTI_LINUX -march=armv7-a  -mlong-calls
CLD = arm-linux-gnueabihf-gcc
CLDFLAGS = -march=armv7-a  -mlong-calls
SYSLIBS = 
INCLUDES =
LIBS = $(SYSLIBS)

SOURCE = hello.c
EXECUTABLE = hello

$(EXECUTABLE):
	$(CC) $(CLDFLAGS) -o $(EXECUTABLE) $(LIBS) $(SOURCE)





