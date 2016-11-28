CC = cc

CPP = c++

# I get the following error using ~ to mean home directory
# the c++ and g++ compiler do not like using ~ instead of /home/ascheurer or
# on the Mac /Users/ascheurer - hence do not suggest using home directory for
# installs. I'll be moving this install to /opt/eXtremeDB on the Mac later on.
# ../mco/testdb.h:15:10: fatal error: 'mco.h' file not found
#INSTALL = ~/Downloads/extremedb/extremedb-macos/eXtremeDB
INSTALL = /Users/ascheurer/Downloads/extremedb/extremedb-macos/eXtremeDB

#CFLAGS' = -O2 -Wall -Wno-unused-variable -Wno-unused-function -m64 -MMD -D_GNU_SOURCE -DDISK_DATABASE -D_LINUX -D_SMP -D_Ix86 -DMCO_PLATFORM_X64 -DMCO_LARGE_DATABASE_SUPPORT -I. -I../../include -I../../include/ha -I../../tests/thlib -I../../include/ws -I/usr/include/malloc -I../../samples/native/common -Iobj/db/ -I../../include/sql -I../../include/sql/odbc

CFLAGS = -Wall -Wno-unused-variable -Wno-unused-function -m64 \
         -MMD -D_GNU_SOURCE -DDISK_DATABASE -D_LINUX -D_SMP -D_Ix86 \
		 -DMCO_PLATFORM_X64 -DMCO_LARGE_DATABASE_SUPPORT \
         -I. -I$(INSTALL)/include  -I$(INSTALL)/include/ha \
         -I$(INSTALL)/include/ws -I/usr/include/malloc \
         -Iobj/db/ -I$(INSTALL)/include/sql -I$(INSTALL)/include/sql/odbc \
		 -I$(INSTALL)/samples/native/common

#CPPFLAGS' = -O2 -std=c++11 -MMD -fexceptions -ftemplate-depth-99 -Wall -Wno-unused-variable -Wno-unused-function -m64 -D_GNU_SOURCE -DDISK_DATABASE -D_LINUX -D_SMP -D_Ix86 -DMCO_PLATFORM_X64 -DMCO_LARGE_DATABASE_SUPPORT -I. -I../../include -I../../include/ha -I../../tests/thlib -I../../include/ws -I/usr/include/malloc -I../../samples/native/common -Iobj/db/ -I../../include/sql -I../../include/sql/odbc

CPPFLAGS = -m64 -Wall -Wno-unused-variable -Wno-unused-function \
		   -fexceptions -ftemplate-depth-99 \
		   -DDISK_DATABASE -MMD -D_GNU_SOURCE -DMCO_PLATFORM_X64 \
		   -DMCO_LARGE_DATABASE_SUPPORT -D_SMP \
           -D_Ix86 \
           -I. -I$(INSTALL)/include  -I$(INSTALL)/include/ha \
		   -I$(INSTALL)/tests/thlib \
           -I$(INSTALL)/include/ws -I/usr/include/malloc \
           -Iobj/db/  -I$(INSTALL)/include/sql -I$(INSTALL)/include/sql/odbc \
		   -I$(INSTALL)/samples/native/common


#LDFLAGS' = c++ -O2 -std=c++11 -MMD -m64 -fexceptions -L../../target/bin -D_GNU_SOURCE -DDISK_DATABASE  main.o testdb.o ../../samples/native/common/common.o ../../samples/native/common/initos.o -lmcolib  -lmcomem  -lmcovtdsk  -lmconet  -lmcosmp  -lmcomem -lmcostrerror  -lmcoslnxp  -lmcomconv  -lmcofu98zip  -lmcotmvcc -lmcolib  -lmcomem  -lmcouwrt -lpthread -lm -ldl -o poc

LDFLAGS = -MMD -m64 -fexceptions -MMD -D_GNU_SOURCE \
          -DDISK_DATABASE -L$(INSTALL)/target/bin \
		   $(INSTALL)/samples/native/common/common.o \
		   $(INSTALL)/samples/native/common/initos.o \
          -lmcolib  -lmcomem  -lmcovtdsk  -lmconet  -lmcosmp  -lmcomem  \
          -lmcostrerror  -lmcoslnxp  -lmcomconv  -lmcofu98zip -lmcotmvcc \
		  -lmcolib  -lmcomem -lmcouwrt -lpthread -lm -ldl


