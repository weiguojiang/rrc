##################################
# (C) Copyright 2016 kkk, Inc.
# All rights reserved.
#
# $DateTime: $
# $Change:  $
#    based on the version of tsheng $

######################################

ifndef TOPDIR
export TOPDIR=$(shell pwd)/..
endif

# What sortof target system shall we compile this for?
ifndef ARCH
export ARCH = i386
endif
ifndef DEVICE
export DEVICE = simulator
endif

ifndef LIBPATH
export LIBPATH = $(TOPDIR)/src/lib
endif

ifndef RTELIBPATH
export RTELIBPATH = $(LIBPATH)/ncp_rte_lib
endif

ifndef RTEINCPATH
export RTEINCPATH = $(TOPDIR)/src/include
endif

ifndef TARGETPATH
export TARGETPATH = $(TOPDIR)/targets
endif

ifndef GDBCFLAG
export GDBCFLAG = TRUE
endif

# app dir
OFAGENT_DIR = $(TOPDIR)/src/apps
OFAGENT_DRIVER_DIR = $(TOPDIR)/src/drivers/ofpsdriver
targets = $(wildcard $(OFAGENT_DIR)/*.c)

# Set the toolchain path
CROSS_COMPILE_X86 =
export CROSS_COMPILE = $(CROSS_COMPILE_X86)

export AR      = $(CROSS_COMPILE)ar
export AS      = $(CROSS_COMPILE)as
export CC      = $(CROSS_COMPILE)gcc
export LD      = $(CROSS_COMPILE)ld
export NM      = $(CROSS_COMPILE)nm
export OBJCOPY = $(CROSS_COMPILE)objcopy
export OBJDUMP = $(CROSS_COMPILE)objdump
export RANLIB  = $(CROSS_COMPILE)ranlib
export STRIP   = $(CROSS_COMPILE)strip

export SED     = sed
export RM      = rm
 
CFLAG := -O2 -W -Wall
ifeq ($(GDBCFLAG),TRUE) 
CFLAG += -g
endif
CFLAG +=-Iinclude -I$(OFAGENT_DRIVER_DIR)/include 
                                                                               
export KERNELPATH= 
                                                                                
# List of subsystem libraties for indigo
INDIGO_LIBS = \
	indigo/submodules/bigcode/modules/uCli/module/uCli \
	indigo/modules/SocketManager/module/SocketManager \
	indigo/modules/Configuration/module/Configuration \
	indigo/modules/OFConnectionManager2/module/OFConnectionManager2 \
	indigo/modules/OFStateManager/module/OFStateManager \
	indigo/modules/minimatch/module/minimatch \
	indigo/submodules/loxigen-artifacts/loci/loci \
	indigo/modules/indigo/module/indigo \
	indigo/submodules/bigcode/modules/IOF/module/IOF \
	indigo/submodules/bigcode/modules/slot_allocator/module/slot_allocator \
	indigo/submodules/bigcode/modules/histogram/module/histogram \
	indigo/submodules/bigcode/modules/BigData/BigList/module/BigList \
	indigo/submodules/bigcode/modules/BigData/BigRing/module/BigRing \
	indigo/submodules/bigcode/modules/BigData/BigHash/module/BigHash \
	indigo/submodules/bigcode/modules/debug_counter/module/debug_counter \
	indigo/submodules/bigcode/modules/cjson/module/cjson \
	indigo/submodules/bigcode/modules/timer_wheel/module/timer_wheel \
	indigo/submodules/bigcode/modules/OS/module/OS \
	indigo/submodules/infra/modules/AIM/module/AIM \

#	indigo/modules/OFConnectionManager/module/OFConnectionManager \

INDIGO_SUBS = $(dir $(sort $(INDIGO_LIBS)))

# List of subsystem include for indigo
INDIGO_INC = \
	indigo/modules/Configuration/module/inc \
	indigo/modules/indigo/module/inc \
	indigo/modules/minimatch/module/inc \
	indigo/modules/OFStateManager/module/inc \
	indigo/modules/OFConnectionManager2/module/inc \
	indigo/modules/SocketManager/module/inc \
	indigo/submodules/infra/modules/AIM/module/inc \
	indigo/submodules/bigcode/modules/BigData/BigList/module/inc \
	indigo/submodules/loxigen-artifacts/loci/inc \
	indigo/submodules/bigcode/modules/uCli/module/inc \
	indigo/modules/drivers/ofpsdriver/include \


#	indigo/modules/OFConnectionManager/module/inc \

# ofagent platform specific
#export OFAGENT_DRIVER_TYPE = NULL
ifeq ($(OFAGENT_DRIVER_TYPE),NULL)
CFLAG += -DOFAGENT_DRIVER_TYPE_NULL
ofagentdriver:
	@echo "skip ofagentdriver build,modify the api null!"
else
ofagentdriver: $(addsuffix -sub,$(OFAGENT_DRIVER_DIR))

$(addsuffix -sub,$(OFAGENT_DRIVER_DIR))::
	$(MAKE) -C $(@:-sub=)
endif


## Default target is to build all cores
all: ofagent

ofagent: $(addsuffix -sub,$(INDIGO_SUBS)) ofagentdriver
	$(CC) $(targets) $(CFLAG) \
	$(addprefix -I,$(INDIGO_INC)) \
	-Bstatic -L$(LIBPATH) $(addprefix -l,$(notdir $(INDIGO_LIBS)) $(if $(OFAGENT_DRIVER_TYPE), ,of_driver)) \
	-Bdynamic $(addprefix -L, $(if $(PRIVLIBPATH),$(PRIVLIBPATH),)) -lssl -lcrypto -lc -lm -lpthread  $(addprefix -l, $(if $(PRIVLIBPATH),rt,)) \
	$(addprefix -L, $(if $(RTELIB),$(RTELIBPATH),))  $(addprefix -l, $(if $(RTELIB),$(RTELIB),)) \
	-o $@
	cp -f $@ $(TARGETPATH)
	@echo "OFagent Build Complete"
	@echo "..................`date +[%Y-%m-%d][%H:%M:%S]`.................."

## Build one subsystem.  Called for each SS.
$(addsuffix -sub,$(INDIGO_SUBS))::
	$(MAKE) -C $(@:-sub=)

## Clean all sub-directories
clean: $(addsuffix -clean,$(INDIGO_SUBS)) driver_clean
	$(RM) -f $(LIBPATH)/*.a
	$(RM) -f ofagent*  $(TARGETPATH)/ofagent*
	@echo "OFagent clean complete"
	@echo "..................`date +[%Y-%m-%d][%H:%M:%S]`.................."


$(addsuffix -clean,$(INDIGO_SUBS))::
	$(MAKE) -C $(@:-clean=) clean

ifeq ($(OFAGENT_DRIVER_TYPE),NULL)
driver_clean:
else
driver_clean:$(addsuffix -clean,$(OFAGENT_DRIVER_DIR))

$(addsuffix -clean,$(OFAGENT_DRIVER_DIR))::
	$(MAKE) -C $(@:-clean=) clean
endif
