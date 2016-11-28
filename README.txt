Directory structure: 
[~/cubic/db2] $ tree -d
.
|-- bld - all makefile builds done from here. 
|----- inc - includes for makefile not for code - make-inc-<..>.mak make includes
|----- rsp - contains generated response files for compiler settings. 
|-- sled - slickedit workspace and project files
|-- dbcmn - database common core code. 
|-- mco - mcobject implementation files.
|-- rdm12 - raima data manager implementation files. 
|-- rdm14 - raima data manager implementation files. 
|-- sqlite - sqlite implementation files.

Plan : 
    bld - $ make help shows options where tgt and prod are implicit or explicit

Implementation:
1 change, 1 place drives toward single point control and with it minimalism.
Patterns used are Bridge and Factory with concepts from the Template pattern. 

The strategy employed with a bridge pattern around an impl based on salted
key's as invariants is better expressed as a class abstraction around
record types and a transaction type.

To use raima tools such as 
make gen-db 
you must export the path to its shared libraries until they come out with a 
static library version of their tools or if you install to /opt/Raima where
the tools were built with -rpath
I use -rpath myself with the linker line for RDM however the tools were build
presuming that /opt/Raima is the install location. Therefore its necessary to
export LD_LIBRARY_PATH=/opt/raima-x86/rdm_enterprise-14.0/lib

The Pi3 location of the install is
export LD_LIBRARY_PATH=/opt/raima-arm/rdm_enterprise-14.0/lib
if one uses the tools directly on the Pi 3 this path must be set on the PI. 
Its useful to do an initdb (Raima v12) or rdm-initialize -f (Raima v14) on the
Pi 3

On the PI copy over
scp -R /opt/raima-arm/* PI3-dir
and you must 
export LD_LIBRARY_PATH=/opt/raima-arm/rdm_enterprise-14.0/lib
and the image.

$[cubic/bld] make build-gen-init-run 
sets your env vars like LD_LIBRARY_PATH for you.

The database can be copied over with RDM14 or just run the image and it will
create the database from the image if one is not already created.
This is rdm14 only.
With rdm12 a database must be created before hand and while it is little endian
like the PI and the iMx7 - if the endian on the target does differ then one 
can not copy the database files over. 
However has to have an empty or no database in any case to get the data needed.

$ make build-run [XTGT=pi]
-or equivalently - 
$ make bld-run [XTGT=pi]

builds all the software for the default's - in the case of the VM, this is
tgt=linux32 and prod=rdm14 are the defaults and XTGT isn't required. 

Note that the PI3 is considered a very limited environment where 
transaction length does matter:
#ifndef DEFAULT_DB_TRANS_LENGTH
#if defined(MCO) || defined(mco)
    #define DEFAULT_DB_TRANS_LENGTH (1 * 1000)
#elif defined(RDM14) || defined(rdm14)
    #define DEFAULT_DB_TRANS_LENGTH (100 * 1000)
#elif defined(RDM12) || defined(rdm12)
    #define DEFAULT_DB_TRANS_LENGTH (25 * 1000)
#elif defined(SQLITE) || defined(sqlite)
    #define DEFAULT_DB_TRANS_LENGTH (50 * 1000)
#else
    #error "Database Product ID not set- build error"
#endif
#endif

Note that RDM12 will run out of memory if a transaction length of 25000 isn't 
provided on the PI3. RDM14 on the other hand tolerates larger transaction
lengths. 

SQLite transaction length allows for gaps in time - its very limited in that
reads are locked out while writes are in progress which makes it unsuitable 
for the primary use case of an update list file import simulation while the
gate is required to be operational and continue to do card read validations. 

sudo apt-get install sqlite
sudo apt-get install sqlite-dev


