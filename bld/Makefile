# Post to ctscarddbstudy :ctscarddbstudy.slack.com

# Note: I'm not using makedepend 
# or http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/#traditional
# to generate header file dependencies. I'll get to this later. 

V = @ 	# comment out @ or make V= to see all the steps along with make -n 
VV = # @ # uncomment to make super silent or make VV=@ 

# todo - ask shell - see notes and get OS and then if condition to set the
# tgt value to osx, linux, pi
# tgt?=osx
prod?=rdm14
UC_PROD = $(shell echo $(prod) | tr a-z A-Z)

# Pi3 has to be explicity named - it can't be inferred and besides not
# building on Pi3 in any case - using cross compiler for that. 
# Default build is the machine you're using - linux or Mac
UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
NBIT := $(shell uname -m)
ifeq ($(NBIT),i686)
tgt?=linux32
else
tgt?=linux64
endif
else ifeq ($(UNAME),Darwin)
tgt?=osx
endif

# make tgt=pi prod=rdm
# targets recurse on makefile - call make again. 
ifndef tgt
$(error usage error: tgt=pi|linux|osx is not set)
endif

ifndef prod
$(error usage error: prod=sqlite|rdm|mco is not set)
endif

O = o
L = a
E = # .out, .elf

include inc/make-inc-$(tgt)-$(prod).mak

LD = $(CPP)

# dbcmn: database common code and product code (expected to be portable)
GEN_SRC_PATH1 = ../dbcmn
GEN_SRC_PATH2 = ../$(prod)

# object files have an explicit path but sources need to be found to resolve
# the implicit rules.
vpath %.c $(GEN_SRC_PATH1):$(GEN_SRC_PATH2)
vpath %.cpp $(GEN_SRC_PATH1):$(GEN_SRC_PATH2)
vpath %.h $(GEN_SRC_PATH1):$(GEN_SRC_PATH2)
vpath %.hpp $(GEN_SRC_PATH1):$(GEN_SRC_PATH2)

OBJBASEDIR = ../obj
OBJDIR = $(OBJBASEDIR)/$(prod)/$(tgt)
DEPLOYDIR = ../deploy
GITIGNORE = ../.gitignore

# paths relative to ./schema/$(rdm) - subdir within this bld directory
RELATIVE_SCHEMAPATH = schema/$(prod)
RELATIVE_PRODPATH = ../../../$(prod)
RELATIVE_DEPLOYPATH = ../../../deploy

SRCS = $(wildcard $(GEN_SRC_PATH1)/*.c*)
SRCS += $(wildcard $(GEN_SRC_PATH2)/*.c*)

# probably a better way to do this - come back to this
# objective is to prepend the obj dir path to the object file list members. 
OBJS1 = $(SRCS:.c=.$O) 
OBJS2 = $(OBJS1:.cpp=.$O)
OBJS3 = $(notdir $(OBJS2))
OBJS = $(OBJS3:%=$(OBJDIR)/%)

DEBUG = -g
OPT = -O2

CFLAGS_RSP_FILE = rsp/cflags-$(tgt)-$(prod).rsp
CPPFLAGS_RSP_FILE = rsp/cppflags-$(tgt)-$(prod).rsp
LDFLAGS_RSP_FILE = rsp/ldflags-$(tgt)-$(prod).rsp
LDOBJS_RSP_FILE = rsp/ldobjs-$(tgt)-$(prod).rsp

# @TODO: would be nice to run $(IMAGE1) through $(IMAGE1_GLOB) without
# $(IMAGE1) existing and throwing an $(error ...) if they don't match.
IMAGE1 = $(DEPLOYDIR)/main-$(prod)-$(tgt)-benchmark$E
IMAGE1_GLOB = main-*-*-benchmark*

#------------------------------------------------------------------

all : gen-env $(IMAGE1) $(GITIGNORE)
	@echo '$(IMAGE1) up to date: warning no Makefile hdr dependencies yet!'
	@echo \'make todo\' shows todo items
	@echo

$(IMAGE1) : $(OBJS)
	@echo
	@echo Linking $@
	@echo $^ > $(LDOBJS_RSP_FILE)
	$(LD) @$(LDOBJS_RSP_FILE) @$(LDFLAGS_RSP_FILE) -o $@
	ls -la $@
	@echo

# Generate Git ignore file for the project from the build system since it
# depends on some names defined here.  Note we do NOT ignore a lot of
# auto-generated files (including the ignore file!), as a check on auto-gen
# bugs.  One can also see this as a feature:  the VCS lets you know when stuff
# you normally ignore is changing on you.  But we still ignore "auto-gen files"
# from that menace, gcc =).
#
# For vimers:  you should add the following to .git/info/exclude:
#
# 	.*.sw[p-z]
#
# slick editors get mention in this file since they love their project and
# workspace files so much...
$(GITIGNORE) : $(MAKEFILE_LIST)
	@echo 'Generating $@'
	@echo '# Generated from build system, but also version controlled' >$@
	@echo 'sled/' >>$@
	@echo '!sled/*.vp[wj]' >>$@
	@echo '$(notdir $(OBJBASEDIR))/' >>$@
	@echo '$(notdir $(DEPLOYDIR))/$(IMAGE1_GLOB)' >>$@
	@echo '$(notdir $(DEPLOYDIR))/*.sks' >>$@

#------------------------------------------------------------------

# implicit rules 
$(OBJDIR)/%.$O: %.c
	@echo
	@echo Compiling $<
	$(VV) $(CC) @$(CFLAGS_RSP_FILE) -c $< -o $(OBJDIR)/$(notdir $@) 

$(OBJDIR)/%.$O: %.cpp
	@echo
	@echo Compiling $<
	$(VV) $(CPP) @$(CPPFLAGS_RSP_FILE) -c $< -o $(OBJDIR)/$(notdir $@)

compile : gen-env
	make -B $(OBJDIR)/$(object_module).$O

gen-env : 
	$V echo $(XCFLAGS) -D$(UC_PROD) -DPROD=$(prod) $(DEBUG) $(OPT) -I$(GEN_SRC_PATH1) -I$(GEN_SRC_PATH2) $(CFLAGS) > $(CFLAGS_RSP_FILE)
	$V echo $(XCFLAGS) -D$(UC_PROD) -DPROD=$(prod) -std=c++11 $(DEBUG) $(OPT) -I$(GEN_SRC_PATH1) -I$(GEN_SRC_PATH2) $(CPPFLAGS) > $(CPPFLAGS_RSP_FILE)
	$V echo $(DEBUG) $(OPT) $(LDFLAGS) > $(LDFLAGS_RSP_FILE)
	$V test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	$V test -d $(DEPLOYDIR) || mkdir -p $(DEPLOYDIR)

print-vars : 
	@echo ------------------------------------------------------------------
	@echo tgt=$(tgt)
	@echo ------------------------------------------------------------------
	@echo prod=$(prod)
	@echo ------------------------------------------------------------------
	@echo CC = $(CC)
	@echo ------------------------------------------------------------------
	@echo CPP = $(CPP)
	@echo ------------------------------------------------------------------
	@echo CFLAGS = $(CFLAGS)
	@echo ------------------------------------------------------------------
	@echo CPPFLAGS = $(CPPFLAGS)
	@echo ------------------------------------------------------------------
	@echo LDFLAGS = $(LDFLAGS)
	@echo ------------------------------------------------------------------
	@echo SRCS = $(SRCS)
	@echo ------------------------------------------------------------------
	@echo OBJS = $(OBJS)

show-rsp : 
	@echo ------------------------------------------------------------------
	--cat $(CFLAGS_RSP_FILE)
	@echo ------------------------------------------------------------------
	--cat $(CPPFLAGS_RSP_FILE)
	@echo ------------------------------------------------------------------
	--cat $(LDFLAGS_RSP_FILE)
	@echo ------------------------------------------------------------------

show : print-vars show-rsp

clean : 
	@echo clean only a particular db product and target os
	--rm $(OBJDIR)/*.$O
	--rm $(IMAGE1)

clean-all superclean : 
	@echo clean up all sets of objs and images for all products and targets
	--rm -fr $(OBJBASEDIR)
	--rm -fr $(DEPLOYDIR)

todo : 
	@echo
	@echo TODO: add lint and pmccabe later to source build for .c and .cpp
	@echo TODO: abstract initialize/copy of db directory or files to ../deploy
	@echo TODO: add dependency checking per url at top of file for hdrs 
	@echo

# utilities for build machine
# DHCP assigned - may change. Env var overrides. 
BLD_MACHINE_PWD = cubic2016
BLD_MACHINE_IP ?= 192.168.1.8
BLD_MACHINE_USR = cubic

BLD_ZIP_FILE?=db-trade-study-bld
SRC_MASK = *.cpp *.hpp *.c *.h
MAKE_MASK = bld/Makefile sorted-pop-file/makefile *.mak 
DB_MASK = *.ddl *.sdl *.sql *.mco
MISC_MASK = *.rsp *.txt *.csv *.log
ZIP_SRC_CMD = zip -r $(BLD_ZIP_FILE) . -i $(SRC_MASK) $(MAKE_MASK) $(DB_MASK) $(MISC_MASK)
zip-bld bld-zip : 
	cd ..;$(ZIP_SRC_CMD)
	mv ../$(BLD_ZIP_FILE).zip ~

cp2bm : 
	pscp -pw $(BLD_MACHINE_PWD) $(PSCP_FILE) $(BLD_MACHINE_USR)@$(BLD_MACHINE_IP):$(PSCP_FILE)

tx-bld-package : zip-bld cp2bm

help : 
	@echo $$ "make tgt=pi|linux|osx prod=rdm|mco|sqlite [-B|-i|-k] [clean|superclean|all|tx-bld-package|show|todo|zip-bld|bld-zip|cp2bm|gen-db|init-db|build-gen-init-run|bld-gen-init-run|run|...]"

build-all : 
	make -B prod=mco -f Makefile all
	make -B prod=rdm14 -f Makefile all
	make -B prod=sqlite -f Makefile all

run :
	export LD_LIBRARY_PATH=$(RDM_BIN_INSTALL)/../lib \
	&& cd ../deploy \
	&& ./main-$(prod)-$(tgt)-benchmark -f sorted.sks

XTGT ?= $(tgt)
build-gen-init-run bld-gen-init-run : 
	make tgt=$(XTGT) -B -f Makefile all
	make tgt=$(XTGT) -f Makefile gen-db
	make tgt=$(XTGT) -f Makefile init-db
	make tgt=$(XTGT) -f Makefile run


.PHONY : all gen-env print-vars show-rsp show clean clean-all superclean todo \
	 zip-bld bld-zip cp2bm tx-bld-package help build-all run \
	 build-run bld-run

# Rebuild OBJS and image if Makefile is updated. 
$(OBJS) : Makefile

$(OBJDIR)/database_profiler.o : database_profiler.hpp dbexception.hpp
$(OBJDIR)/main-db-metrics.o : database_profiler.hpp
$(OBJDIR)/rdm14-db.o : rdm14-db.hpp cardsdb_api.h cardsdb_cat.h cardsdb.h \
		       cardsdb_embed.h cardsdb_structs.h
$(OBJDIR)/oosqlite3.o : oosqlite3.hpp
$(OBJDIR)/sqlite-db.o : oosqlite3.hpp sqlite-db.hpp

# rules for building a product db and generating source files describing the db
# target rule is consistent for each product and same target name
# make gen-db is the rule that generates source and database files to ../deploy
# make gen-db will execute the rules
include inc/make-inc-$(prod)-db.mak
