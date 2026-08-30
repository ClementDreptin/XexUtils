# ================================================================
# Project configuration
# ================================================================

PROJECT_NAME := XexUtils
WINDOWS_SHIM := wine
CONFIG := Debug

BUILD_DIR := build
OUT_DIR := $(BUILD_DIR)/$(CONFIG)/bin
INT_DIR := $(BUILD_DIR)/$(CONFIG)/obj

TARGET_NAME := $(PROJECT_NAME)$(if $(filter Debug,$(CONFIG)),d)
TARGET := $(OUT_DIR)/$(TARGET_NAME).lib


# ================================================================
# BearSSL dependency
# ================================================================

BEARSSL_DIR := deps/BearSSL
BEARSSL_TARGET_NAME := BearSSL$(if $(filter Debug,$(CONFIG)),d)
BEARSSL_TARGET := $(BEARSSL_DIR)/$(OUT_DIR)/$(BEARSSL_TARGET_NAME).lib
BEARSSL_INC := $(BEARSSL_DIR)/inc

# ================================================================
# Source files
# ================================================================

SRCS := $(shell find src -name '*.cpp')
OBJS := $(SRCS:%.cpp=$(INT_DIR)/%.obj)


# ================================================================
# XDK Toolchain
# ================================================================

XDK_BIN_DIR := $(XEDK)/bin/win32
XDK_INC_DIR := "$(XEDK)/include/xbox"
XDK_LIB_DIR := "$(XEDK)/lib/xbox"

CXX := "$(XDK_BIN_DIR)/cl.exe"
LD := "$(XDK_BIN_DIR)/lib.exe"


# ================================================================
# Compiler and linker flags
# ================================================================

INCLUDES := $(BEARSSL_INC)

ifeq ($(CONFIG),Debug)
	LIBS := xbdm.lib xjsond.lib xnetd.lib
else ifeq ($(CONFIG),Release)
	LIBS := xjson.lib xnet.lib
else
	$(error Unknown CONFIG=$(CONFIG))
endif

CXX_FLAGS := -c $(addprefix -I ,$(INCLUDES)) -Zi -nologo -W4 -MP -D _XBOX -Gm- -EHsc -GS \
			 -fp:fast -fp:except- -Zc:wchar_t -Zc:forScope -GR- -openmp- \
			 -Fd"$(INT_DIR)/vc100.pdb" -TP -FI"$(XDK_INC_DIR)/xbox_intellisense_platform.h"

LD_FLAGS := -NOLOGO $(LIBS)

ifeq ($(CONFIG),Debug)
	CXX_FLAGS += -WX- -Od -D _DEBUG -MTd -Gy- -GF-
else ifeq ($(CONFIG),Release)
	CXX_FLAGS += -WX -Ox -Oi -Os -D NDEBUG -MT -Gy -GF
else
	$(error Unknown CONFIG=$(CONFIG))
endif


# ================================================================
# Top-level targets
# ================================================================

all: $(TARGET)

clean:
	$(MAKE) -C deps -f BearSSL.mk $@
	rm -rf $(BUILD_DIR)

.PHONY: all clean


# ================================================================
# Final library
# ================================================================

$(TARGET): $(BEARSSL_TARGET) $(OBJS)
	@echo "Linking $(@)..."
	@mkdir -p $(@D)
	@LIB=$(XDK_LIB_DIR) $(WINDOWS_SHIM) $(LD) $(LD_FLAGS) -OUT:"$@" $^


# ================================================================
# Compilation
# ================================================================

$(INT_DIR)/%.obj: %.cpp
	@mkdir -p $(@D)
	@INCLUDE=$(XDK_INC_DIR) $(WINDOWS_SHIM) $(CXX) $(CXX_FLAGS) -Fo"$@" $<


# ================================================================
# BearSSL build
# ================================================================

$(BEARSSL_TARGET):
	$(MAKE) -C deps -f BearSSL.mk
