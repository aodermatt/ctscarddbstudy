CC = arm-linux-gnueabihf-gcc

CPP = arm-linux-gnueabihf-g++

MCO_PI_BASE_INSTALL ?= /opt/extremedb-arm

CFLAGS = -fPIC -Wall -Wno-unused-variable -Wno-unused-function   \
         -MMD -D_GNU_SOURCE -D_LINUX  -D_SMP -D_ARM32 -DMCO \
          -I. -I$(MCO_PI_BASE_INSTALL)/include  -I$(MCO_PI_BASE_INSTALL)/include/ha  \
          -I$(MCO_PI_BASE_INSTALL)/include/ws -I/usr/include/malloc \
          -Iobj/db/ -I$(MCO_PI_BASE_INSTALL)/include/sql -I$(MCO_PI_BASE_INSTALL)/include/sql/odbc


CPPFLAGS = -fPIC -Wall -Wno-unused-variable -Wno-unused-function \
           -std=gnu++11 -MMD -D_GNU_SOURCE -D_LINUX  -D_SMP \
           -D_ARM32 -DMCO \
           -I. -I$(MCO_PI_BASE_INSTALL)/include  -I$(MCO_PI_BASE_INSTALL)/include/ha -I$(MCO_PI_BASE_INSTALL)/tests/thlib \
           -I$(MCO_PI_BASE_INSTALL)/include/ws -I/usr/include/malloc \
           -Iobj/db/  -I$(MCO_PI_BASE_INSTALL)/include/sql -I$(MCO_PI_BASE_INSTALL)/include/sql/odbc


LDFLAGS = -fPIC -static  -MMD -D_GNU_SOURCE \
          -DDISK_DATABASE -L$(MCO_PI_BASE_INSTALL)/target/bin \
          -lmcolib  -lmcomem  -lmcovtdsk  -lmconet  -lmcosmp  -lmcomem  \
          -lmcostrerror  -lmcoslnxp  -lmcomconv  -lmcofu98zip  -lmcotmvcc  \
          -lmcolib  -lmcomem  -lmcouwrt -lpthread -lm -ldl


