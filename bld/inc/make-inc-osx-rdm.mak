CC = gcc

CPP = g++

CFLAGS =  

RAIMA_INC = /opt/Raima/rdm-12.0/include

# I use -std=c++ as an invariant and <random> is found. 
# for some reason I also need -stdlib=libc++ with the Raima includes here. 
# They have defines that force the need for -stdlib=libc++
CPPFLAGS = -stdlib=libc++ -I$(RAIMA_INC) -DPACKAGE_NAME=\"RDM-obj\" -DPACKAGE_TARNAME=\"rdm-obj\" -DPACKAGE_VERSION=\"12.0\" -DPACKAGE_STRING=\"RDM-obj\ 12.0\" -DPACKAGE_BUGREPORT=\"http://www.raima.com/support\" -DPACKAGE_URL=\"\" -DPACKAGE=\"rdm-obj\" -DVERSION=\"12.0\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 -DLT_OBJDIR=\".libs/\" -DSIZEOF_VOIDP=8 -I. -DNEED_SETUP_DATABASE -arch x86_64 -mmacosx-version-min=10.7 -DRDM_64BIT $(DEBUG) -O2 -MT $@ -MD -MP -MF $*.Tpo 

# Not sure I need -std=c++11 in linker line but once again using -stdlib=libc++ is essential or it will not link. 
LDFLAGS = -stdlib=libc++ -I./../../../../include -DNEED_SETUP_DATABASE -arch x86_64 -mmacosx-version-min=10.7 -DRDM_64BIT -I/opt/Raima/rdm-12.0/include -g -O2 -Wl,-bind_at_load -L/opt/Raima/rdm-12.0/lib /opt/Raima/rdm-12.0/lib/librdmcppapi.dylib /opt/Raima/rdm-12.0/lib/librdmdbimp_tool.dylib /opt/Raima/rdm-12.0/lib/librdmxml.dylib /opt/Raima/rdm-12.0/lib/librdmutil.dylib /opt/Raima/rdm-12.0/lib/librdmrdm.dylib /opt/Raima/rdm-12.0/lib/librdmddl.dylib /opt/Raima/rdm-12.0/lib/librdmtfs.dylib /opt/Raima/rdm-12.0/lib/librdmhttp.dylib /opt/Raima/rdm-12.0/lib/librdmenc.dylib /opt/Raima/rdm-12.0/lib/librdmbase.dylib /opt/Raima/rdm-12.0/lib/librdmha.dylib /opt/Raima/rdm-12.0/lib/librdmtransport.dylib /opt/Raima/rdm-12.0/lib/librdmpsp.dylib -lstdc++ -lm -ltermcap -framework Foundation


