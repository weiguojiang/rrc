
###############################################################################
#
# Inclusive Makefile for the AIM module.
#
# Autogenerated 2016-10-21 20:16:33.902504
#
###############################################################################
AIM_BASEDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include $(AIM_BASEDIR)/module/make.mk
include $(AIM_BASEDIR)/module/auto/make.mk
include $(AIM_BASEDIR)/module/src/make.mk
include $(AIM_BASEDIR)/utest/_make.mk

