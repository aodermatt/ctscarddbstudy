# Note: I put in .bashrc on the pi the following LD_LIBRARY_PATH on Jack's SD card
# jlloyd@xtsspi1:[~] $ echo $LD_LIBRARY_PATH
# /opt/Raima/rdm-12.0/target/arm-unknown-linux-gnueabihf/lib
# export LD_LIBRARY_PATH=/opt/Raima/rdm-12.0/target/arm-unknown-linux-gnueabihf/lib
# was necessary to run the raima arm installation on the pi tgt

DB_SCHEMA_NAME = cardsdb
RDM_BIN_INSTALL ?= /opt/raima-x86/rdm_enterprise-14.0/bin

# These schema options do not work!
RDM_SCHEMA_OPTS ?=  --cxx-api --c-structs --catalog --embed --quiet 
#RDM_SCHEMA_OPTS ?=  -q -x #--embed --catalog 


# use rdm-initialize -f dbname to force initialization.
# dbname.rdb is name of the directory - such as cardsdb.rdm however
# rdm-initialize -f cardsdb is what works. 
# rdm-initialize -f cardsdb.rdm will fail with an error - exclude .rdm from
# dbname
gen-db : 
	cd schema/rdm14 \
	&& export LD_LIBRARY_PATH=$(RDM_BIN_INSTALL)/../lib \
	&& $(RDM_BIN_INSTALL)/rdm-compile $(RDM_SCHEMA_OPTS) $(DB_SCHEMA_NAME).sdl \
	&& cp -f *.sdl $(RELATIVE_DEPLOYPATH) \
	&& cp -f *.h $(RELATIVE_PRODPATH) \
	&& cp -f *.c $(RELATIVE_PRODPATH) \
	&& cp -f *.cpp $(RELATIVE_PRODPATH) 

init-db : 
	cd ../deploy \
	&& export LD_LIBRARY_PATH=$(RDM_BIN_INSTALL)/../lib \
	&& $(RDM_BIN_INSTALL)/rdm-initialize -f $(DB_SCHEMA_NAME)




