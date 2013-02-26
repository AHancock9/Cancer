#DEFINE TOOLs
TOOL_DIR := D:\Program Files (x86)\CodeSourcery\Sourcery_CodeBench_Lite_for_ARM_GNU_Linux\bin
GCC := $(TOOL_DIR)\arm-none-linux-gnueabi-gcc.exe
LD := $(TOOL_DIR)\arm-none-linux-gnueabi-ld.exe
OBYCOPY := $(TOOL_DIR)\arm-none-linux-gnueabi-objcopy
AR := $(TOOL_DIR)\arm-none-linux-gnueabi-ar.exe
MAKE := @cs-make
MKDIR := @mkdir
DELETE := @del
PLATFORM_LIB :=-lgcc
#DEFINE DIRs
OS_BASE_DIR := $(TOP_DIR)\OS
RULE_DIR := $(TOP_DIR)\OS
INCLUDES_DIR := $(OS_BASE_DIR)\include
#DEFINE INCLUDEs
INCLUDES_LIB := $(INCLUDES_DIR)\lib
INCLUDES_KERNEL := $(INCLUDES_DIR)\kernel
INCLUDES_KERNEL_LIB :=  $(INCLUDES_DIR)\kernel\lib
INCLUDES_HAL := $(INCLUDES_DIR)\hal
INCLUDES_CONFIG := $(INCLUDES_DIR)\configs
INCLUDES_ARCH := $(INCLUDES_DIR)\arch\ok6410
INCLUDES := -I $(INCLUDES_LIB) -I $(INCLUDES_KERNEL) -I $(INCLUDES_KERNEL_LIB)
INCLUDES += -I $(INCLUDES_HAL) -I $(INCLUDES_CONFIG) -I $(INCLUDES_DIR)
INCLUDES += -I $(INCLUDES_ARCH)
#DEFINE OUTPUT
TARGET_DIR := $(TOP_DIR)\target
LDS_FILE := E:\codeblocks\cancer-test\OS\ld.lds
OPTION := -fno-builtin -nostdinc -nostartfiles -march=armv6
#EXPORTs
export LDS_FILE
export MAKE
export MKDIR
export OS_BASE_DIR
export OPTION
export TOOL_DIR
export GCC
export LD
export OBYCOPY
export TARGET_DIR
export RULE_DIR
export INCLUDES
export AR
export PLATFORM_LIB
export DELETE
#PRIVATEs
RULE_TARGET_DIR := $(TARGET_DIR)
RULE_SUB_SYSTEM := arch lib hal kernel user

include $(RULE_DIR)\rule.mk
