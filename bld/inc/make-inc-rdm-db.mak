# Obsolete - do not use this build file.

DB_SCHEMA_NAME = cardsdb
RDM_BIN_INSTALL ?= /opt/Raima/rdm-12.0/bin/

# 	&& cp -f *.lock $(RELATIVE_PRODPATH)
# -rw-r--r--  1 ascheurer  staff      0 Oct 31 02:06 tfserver.lock
# makes no sense to cp over and doesn't appear necessary in any case. 
# run initdb -y cardsdb on target to get an initial database or copying over
# makes no difference.
gen-db : 
	cd $(RELATIVE_SCHEMAPATH) \
	&& ddlp -f -p -m -x -cpp $(DB_SCHEMA_NAME).ddl \
	&& initdb -y $(DB_SCHEMA_NAME) \
	&& mkdir -p $(RELATIVE_DEPLOYPATH)/$(DB_SCHEMA_NAME) \
	&& cp -f $(DB_SCHEMA_NAME)/* $(RELATIVE_DEPLOYPATH)/$(DB_SCHEMA_NAME) \
	&& cp -f *.ddl $(RELATIVE_DEPLOYPATH) \
	&& cp -f *.h $(RELATIVE_PRODPATH) \
	&& cp -f *.cpp $(RELATIVE_PRODPATH)


