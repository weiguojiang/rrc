##################################
# (C) Copyright 2004 kkk, Inc.
# All rights reserved.
#
# $Author: tsheng $
# $DateTime: 2015/04/08 04:14:57 $
# $Change:  $
#
######################################
LIB = libOFStateManager.a

# sub dirs
$(LIB)DIRS = src
SUBDIRS = src

ifeq ($(GDBCFLAG),TRUE) 
CFLAG += -g
endif

## Sources to compile
ifeq ($(OFAGENT_DRIVER_TYPE),NULL)
targets := $(patsubst %.c, %.o, $(wildcard $(SUBDIRS)/*.c))
else
targets := $(patsubst %.c, %.o, $(filter-out $(SUBDIRS)/of_port_fwd.c, $(wildcard $(SUBDIRS)/*.c)))
endif

## Default target.  Build everything.
all: $(LIB)

## Include generic make rules

INCLUDE_PATH += -I./inc
INCLUDE_PATH += -I./$(SUBDIRS)

INCLUDE_PATH += -I../../../modules/indigo/module/inc
INCLUDE_PATH += -I../../../modules/SocketManager/module/inc
INCLUDE_PATH += -I../../../modules/OFConnectionManager/module/inc
INCLUDE_PATH += -I../../../modules/Configuration/module/inc
INCLUDE_PATH += -I../../../modules/minimatch/module/inc
INCLUDE_PATH += -I../../../submodules/infra/modules/AIM/module/inc
INCLUDE_PATH += -I../../../submodules/loxigen-artifacts/loci/inc
INCLUDE_PATH += -I../../../submodules/bigcode/modules/cjson/module/inc
INCLUDE_PATH += -I../../../submodules/bigcode/modules/BigData/BigHash/module/inc
INCLUDE_PATH += -I../../../submodules/bigcode/modules/slot_allocator/module/inc
INCLUDE_PATH += -I../../../submodules/bigcode/modules/histogram/module/inc
INCLUDE_PATH += -I../../../submodules/bigcode/modules/BigData/BigList/module/inc
INCLUDE_PATH += -I../../../submodules/bigcode/modules/BigData/BigRing/module/inc
INCLUDE_PATH += -I../../../submodules/bigcode/modules/debug_counter/module/inc
INCLUDE_PATH += -I../../../submodules/bigcode/modules/murmur/module/inc


# cflag
CFLAG += -DINDIGO_LINUX_LOGGING
CFLAG += -DINDIGO_LINUX_TIME
CFLAG += -DINDIGO_FAULT_ON_ASSERT
CFLAG += -DINDIGO_MEM_STDLIB

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
