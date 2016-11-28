DB_SCHEMA_NAME = testdb
MCO_COMPILER = mcocomp

ifeq ($(tgt),pi)
MCO_BIN_INSTALL ?= /opt/extremedb-arm/host/bin
MCO_TGT_PLATFORM = -x32
else
MCO_BIN_INSTALL ?= /opt/extremedb-x86/host/bin
MCO_TGT_PLATFORM = -x64
endif

MCO_COMPILER_FLAGS = $(MCO_TGT_PLATFORM) -hpp 
gen-db : 
	cd $(RELATIVE_SCHEMAPATH) \
	&& $(MCO_BIN_INSTALL)/$(MCO_COMPILER) $(MCO_COMPILER_FLAGS) $(DB_SCHEMA_NAME).mco \
	&& cp -f $(DB_SCHEMA_NAME).h*  $(RELATIVE_PRODPATH) \
	&& cp -f $(DB_SCHEMA_NAME).c*  $(RELATIVE_PRODPATH) \
	&& cp -f $(DB_SCHEMA_NAME).mco $(RELATIVE_DEPLOYPATH)



