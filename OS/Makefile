MAKE := make
INCLUDE_LIB := $(TOP_DIR)\include\lib -I $(TOP_DIR)\include
INCLUDE_DIR := $(INCLUDE_LIB)
TARGET_DIR := $(TOP_DIR)
CC := cc
AR := ar
unexport INCLUDE_LIB
export TARGET_DIR
export AR
export TOPDIR
export INCLUDE_DIR
BUILD_OS: BUILD_LIB
BUILD_LIB:
	cd .\lib && $(MAKE) && cd..
	
include $(TOP_DIR)\rule.mk