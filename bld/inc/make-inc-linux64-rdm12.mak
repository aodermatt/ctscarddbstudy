CC = gcc

CPP = g++

RAIMA_INC = /opt/raima-x86/rdm-12.0/include

# I use -std=c++ as an invariant and <random> is found. 
# for some reason I also need -stdlib=libc++ with the Raima includes here. 
# They have defines that force the need for -stdlib=libc++
CPPFLAGS =  -DPACKAGE_NAME=\"RDM-obj\" \
            -DPACKAGE_TARNAME=\"rdm-obj\" \
            -DPACKAGE_VERSION=\"12.0\" \
            -DPACKAGE_STRING=\"RDM-obj\ 12.0\" \
            -DPACKAGE_BUGREPORT=\"http://www.raima.com/support\" \
            -DPACKAGE_URL=\"\" -DPACKAGE=\"rdm_enterprise-obj\" \
            -DVERSION=\"12.0\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 \
            -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 \
            -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 \
            -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 \
            -DLT_OBJDIR=\".libs/\" -DSIZEOF_VOIDP=8  \
            -I$(RAIMA_INC) -I. \
            -DNEED_SETUP_DATABASE -m64  $(DEBUG) -O2 


# Not sure I need -std=c++11 in linker line but once again using -stdlib=libc++ is essential or it will not link. 
LDFLAGS = -DNEED_SETUP_DATABASE -m64 -DRDM_64BIT \
          -L$(RAIMA_INC)/../lib -lrdmbase -lrdmcppapi -lrdmxml \
          -lrdmutil -lrdmrdm -lrdmddl -lrdmtfs -lrdmhttp -lrdmenc -lrdmbase \
          -lrdmtransport -lrdmpsp -lrdmpsp  -lrdmddl -lrdmha -lpthread
# \
#  -Wl,-rpath -Wl,$(RAIMA_INC)/../lib 




