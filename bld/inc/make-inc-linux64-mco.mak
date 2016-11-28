CC = gcc

CPP = g++ 

INSTALL = /opt/extremedb-x86

CFLAGS = -fPIC -m64 -Wall -Wno-unused-variable -Wno-unused-function   \
         -MMD -D_GNU_SOURCE -D_LINUX  -D_SMP -D_Ix86 -DMCO_PLATFORM_X64 \
         -DMCO_LARGE_DATABASE_SUPPORT -DMCO \
         -I. -I$(INSTALL)/include  -I$(INSTALL)/include/ha  \
         -I$(INSTALL)/include/ws -I/usr/include/malloc \
         -Iobj/db/ -I$(INSTALL)/include/sql -I$(INSTALL)/include/sql/odbc


CPPFLAGS = -fPIC -m64 -Wall -Wno-unused-variable -Wno-unused-function \
           -std=gnu++11 -MMD -D_GNU_SOURCE -D_LINUX  -D_SMP -DMCO \
           -D_Ix86 -DMCO_PLATFORM_X64 -DMCO_LARGE_DATABASE_SUPPORT\
           -I. -I$(INSTALL)/include  -I$(INSTALL)/include/ha -I$(INSTALL)/tests/thlib \
           -I$(INSTALL)/include/ws -I/usr/include/malloc \
           -Iobj/db/  -I$(INSTALL)/include/sql -I$(INSTALL)/include/sql/odbc


LDFLAGS = -m64 -fPIC --static  -MMD -D_GNU_SOURCE \
          -DDISK_DATABASE -L$(INSTALL)/target/bin \
          -lmcolib  -lmcomem  -lmcovtdsk  -lmconet  -lmcosmp  -lmcomem \
          -lmcostrerror  -lmcoslnxp  -lmcomconv  -lmcofu98zip  -lmcotmursiw \
          -lmcolib  -lmcomem  -lmcouwrt -lpthread -lm -ldl

#          -lmcolib  -lmcomem  -lmcovtdsk  -lmconet  -lmcosmp  -lmcomem  \
#          -lmcostrerror  -lmcoslnxp  -lmcomconv  -lmcofu98zip  -lmcotmvcc  \
#          -lmcolib  -lmcomem  -lmcouwrt -lpthread -lm -ldl


