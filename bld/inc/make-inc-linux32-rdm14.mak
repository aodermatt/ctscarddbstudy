CC = gcc

CPP = g++

RAIMA_INC = /opt/raima-x86/rdm_enterprise-14.0/include

# I use -std=c++ as an invariant and <random> is found. 
# for some reason I also need -stdlib=libc++ with the Raima includes here. 
# They have defines that force the need for -stdlib=libc++
CPPFLAGS =  -DPACKAGE_NAME=\"rdm_enterprise-obj\" \
            -DPACKAGE_TARNAME=\"rdm_enterprise-obj\" \
            -DPACKAGE_VERSION=\"14.0\" \
            -DPACKAGE_STRING=\"rdm_enterprise-obj\ 14.0\" \
            -DPACKAGE_BUGREPORT=\"http://www.raima.com/support\" \
            -DPACKAGE_URL=\"\" -DPACKAGE=\"rdm_enterprise-obj\" \
            -DVERSION=\"12.0\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 \
            -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 \
            -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 \
            -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 \
            -DLT_OBJDIR=\".libs/\" -DSIZEOF_VOIDP=4  \
            -I$(RAIMA_INC) -I. \
            -DDB_ADDR=uint32_t \
            -DNEED_SETUP_DATABASE -m32  $(DEBUG) -O2

CFLAGS =  -DPACKAGE_NAME=\"rdm_enterprise-obj\" \
            -DPACKAGE_TARNAME=\"rdm_enterprise-obj\" \
            -DPACKAGE_VERSION=\"14.0\" \
            -DPACKAGE_STRING=\"rdm_enterprise-obj\ 14.0\" \
            -DPACKAGE_BUGREPORT=\"http://www.raima.com/support\" \
            -DPACKAGE_URL=\"\" -DPACKAGE=\"rdm_enterprise-obj\" \
            -DVERSION=\"14.0\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 \
            -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 \
            -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 \
            -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 \
            -DLT_OBJDIR=\".libs/\" -DSIZEOF_VOIDP=4  \
            -I$(RAIMA_INC) -I. \
            -DDB_ADDR=uint32_t \
            -DNEED_SETUP_DATABASE -m32  $(DEBUG) -O2

# Not sure I need -std=c++11 in linker line but once again using -stdlib=libc++ 
# is essential or it will not link on Mac OSX but is not relevant on linux. 
# Mac OSX is the only reliable unix I have until the linux machine/VM/Windows
# machine stops rebooting on me randomly in the middle of work.
# The -rpath stuff is PFM but I don't have to set LD_LIBRARY_PATH which is
# good - should work on the PI too - no LD_LIBRARY_PATH required if the 
# rdm package is installed in exactly the same location - /opt as it is when
# the image is built - using rpath makes a lot of sense!
LDFLAGS = -DNEED_SETUP_DATABASE -m32 -DRDM_32BIT \
          -L$(RAIMA_INC)/../lib -lrdmbase -lrdmcppapi -lrdmxml \
          -lrdmutil -lrdmrdm -lrdmddl -lrdmtfs -lrdmhttp -lrdmenc -lrdmbase \
          -lrdmtransport -lrdmpsp -lrdmpsp  -lrdmddl -lpthread -lrdmtfs \
          -lrdmcpptfs \
	  -Wl,-rpath -Wl,$(RAIMA_INC)/../lib 



