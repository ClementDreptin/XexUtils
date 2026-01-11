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

ALL_SRCS := $(shell find src -name '*.cpp')

# Precompiled header sources
PCH_HEADER := pch.h
PCH_SRC := src/pch.cpp
PCH_OBJ := $(INT_DIR)/src/pch.obj
PCH_FILE := $(INT_DIR)/$(TARGET_NAME).pch

# Normal (non-PCH) sources
NORMAL_SRCS := $(filter-out $(PCH_SRC),$(ALL_SRCS))
NORMAL_OBJS := $(NORMAL_SRCS:%.cpp=$(INT_DIR)/%.obj)

# All objects that make up the final library
OBJS := $(NORMAL_OBJS) $(PCH_OBJ)


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
LIBS := xnet$(if $(filter Debug,$(CONFIG)),d).lib

CXX_FLAGS := -c $(addprefix -I ,$(INCLUDES)) -Zi -nologo -W4 -MP -D _XBOX -Gm- -EHsc -GS \
			 -fp:fast -fp:except- -Zc:wchar_t -Zc:forScope -GR- -openmp- -Fp"$(PCH_FILE)" \
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

$(TARGET): $(OBJS) $(BEARSSL_TARGET)
	@echo "Linking $(@)..."
	@mkdir -p $(@D)
	@LIB=$(XDK_LIB_DIR) $(WINDOWS_SHIM) $(LD) $(LD_FLAGS) -OUT:"$@" $^


# ================================================================
# Precompiled header
# ================================================================

# pch.obj CREATES the .pch file
$(PCH_OBJ): $(PCH_SRC) src/$(PCH_HEADER)
	@mkdir -p $(@D)
	@INCLUDE=$(XDK_INC_DIR) $(WINDOWS_SHIM) $(CXX) $(CXX_FLAGS) -Yc"$(PCH_HEADER)" -Fo"$@" $<

# Tell make that the .pch exists because pch.obj was built
$(PCH_FILE): $(PCH_OBJ)
	@:


# ================================================================
# Normal compilation (uses the PCH)
# ================================================================

$(INT_DIR)/%.obj: %.cpp $(PCH_FILE)
	@mkdir -p $(@D)
	@INCLUDE=$(XDK_INC_DIR) $(WINDOWS_SHIM) $(CXX) $(CXX_FLAGS) -Yu"$(PCH_HEADER)" -Fo"$@" $<


# ================================================================
# BearSSL build
# ================================================================

$(BEARSSL_TARGET):
	$(MAKE) -C deps -f BearSSL.mk
