##################################
# (C) Copyright 2004 Nokia, Inc.
# All rights reserved.
#
# $Author: tsheng $
# $DateTime: 2015/04/29 04:14:57 $
# $Change:  $
#
######################################
of_driver_files = $(wildcard *.c)
LIB = libof_driver.a

OF_AGENT_BASE_DIR := $(TOPDIR)/src/indigo
OF_AGENT_DRIVER_DIR := $(TOPDIR)/src/drivers/ofpsdriver

searchdirs = $(realpath $(OF_AGENT_DRIVER_DIR)) \
						:$(realpath $(RTEINCPATH)) \
						:$(realpath $(OF_AGENT_BASE_DIR)/modules/indigo/module/inc) \
						:$(realpath $(OF_AGENT_BASE_DIR)/submodules/loxigen-artifacts/loci/inc) \
						:$(realpath $(OF_AGENT_DRIVER_DIR)/include) \
						:$(realpath $(OF_AGENT_BASE_DIR)/submodules/infra/modules/AIM/module/inc) \
						:$(realpath $(OF_AGENT_BASE_DIR)/modules/OFStateManager/module/inc)\
						:$(realpath $(OF_AGENT_BASE_DIR)/modules/indigo/module/inc/indigo) \

#vpath %.c $(searchdirs)

#export CPATH += $(searchdirs)
ifeq ($(GDBCFLAG),TRUE) 
CFLAGS += -g
endif
CFLAGS += $(patsubst %,-I%,$(subst :, ,$(searchdirs)))
ifeq  ($(ARCH), arm15) 
CFLAGS += -DRTE_MODE
CFLAGS += -DNCP_LINUX
CFLAGS += -DNCP_TASK_COLLECT_STATS_DISABLED
CFLAGS += -DNCP_CHECK_DISABLED
CFLAGS += -DPROC_ARMA15
CFLAGS += -mcpu=cortex-a15
CFLAGS += -DNCP_ARCH_SUPPORTS_PLDW_INSTRUCTION 
CFLAGS += -mlittle-endian 
CFLAGS += -DNCP_SAL_SHM_NVM 
CFLAGS += -DNCP_NCA_COHERENT_IO
CFLAGS += -D_XOPEN_SOURCE=600
CFLAGS += -DLINUX
endif
.PHONY: all clean

all: $(LIB)

$(LIB): $(of_driver_files:.c=.o)
	$(AR) ru $@ $^
	cp -f $@ $(LIBPATH)


#
# This rule builds the dependency files
#
$(of_driver_files:.c=.o):%.o: %.c
	@echo $(shell pwd)
	$(CC)  -c $(CFLAGS) $< -o $@


clean:
	rm -f *.o $(LIB)
