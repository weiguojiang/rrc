##################################
# (C) Copyright 2004 kkk, Inc.
# All rights reserved.
#
# $Author: tsheng $
# $DateTime: 2015/04/24 04:14:57 $
# $Change:  $
#
######################################
LIB = libtimer_wheel.a

# sub dirs
$(LIB)DIRS = src
SUBDIRS = src

ifeq ($(GDBCFLAG),TRUE) 
CFLAG += -g
endif

## Sources to compile
targets := $(patsubst %.c, %.o, $(wildcard $(SUBDIRS)/*.c))

## Default target.  Build everything.
all: $(LIB)

## Include generic make rules

INCLUDE_PATH += -I./inc
INCLUDE_PATH += -I./$(SUBDIRS)

#INCLUDE_PATH += -I../../../modules/indigo/module/inc
#INCLUDE_PATH += -I../../../modules/SocketManager/module/inc
#INCLUDE_PATH += -I../../../modules/OFStateManager/module/inc
#INCLUDE_PATH += -I../../../modules/Configuration/module/inc
INCLUDE_PATH += -I$(TOPDIR)/src/indigo/submodules/infra/modules/AIM/module/inc
#INCLUDE_PATH += -I../../../submodules/loxigen-artifacts/loci/inc
#INCLUDE_PATH += -I../../../submodules/bigcode/modules/cjson/module/inc
#INCLUDE_PATH += -I../../../submodules/bigcode/modules/BigData/BigList/module/inc
#INCLUDE_PATH += -I../../../submodules/bigcode/modules/BigData/BigRing/module/inc
#INCLUDE_PATH += -I../../../submodules/bigcode/modules/debug_counter/module/inc

# cflag
CFLAG += -DINDIGO_LINUX_TIME
CFLAG += -DAIM_CONFIG_INCLUDE_MODULES_INIT=1
CFLAG += -DAIM_CONFIG_INCLUDE_MAIN=1


#
# Build the target executables
# The .o files are built by an implicit rule.
#

$(targets):%.o:%.c
#	@echo making $(targets)
	@echo $(shell pwd)
#	$(shell ls ../../../submodules/infra/modules/AIM/module/inc)
	$(CC)  -c $(CFLAG) $(INCLUDE_PATH) $< -o $@
	
$(LIB): $(targets)
	$(AR) ru $@ $^
	cp -f $@ $(LIBPATH)
	
clean:
	rm -f $(SUBDIRS)/*.o $(LIB)
