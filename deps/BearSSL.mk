# ================================================================
# Project configuration
# ================================================================

PROJECT_NAME := BearSSL
WINDOWS_SHIM := wine
CONFIG := Debug

BUILD_DIR := $(PROJECT_NAME)/build
OUT_DIR := $(BUILD_DIR)/$(CONFIG)/bin
INT_DIR := $(BUILD_DIR)/$(CONFIG)/obj

TARGET_NAME := $(PROJECT_NAME)$(if $(filter Debug,$(CONFIG)),d)
TARGET := $(OUT_DIR)/$(TARGET_NAME).lib

# ================================================================
# Source files
# ================================================================

# We don't compile all the .c files so we extract the list from the
# .vcxproj file and replace the backslashes with forward slashes
SRCS := $(shell sed -n 's/<ClCompile Include="\([^"]*\)" \/>/\1/p' $(PROJECT_NAME).vcxproj | sed 's/\\/\//g')
OBJS := $(SRCS:%.c=$(INT_DIR)/%.obj)


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

INCLUDES := $(PROJECT_NAME)/inc $(PROJECT_NAME)/src
DEFINES := BR_USE_WIN32_TIME=0 BR_USE_UNIX_TIME=1 inline=__inline

CXX_FLAGS := -c $(addprefix -I ,$(INCLUDES)) -Zi -nologo -W3 -MP -D _XBOX $(addprefix -D ,$(DEFINES)) \
			 -Gm- -EHsc -GS -fp:fast -fp:except- -Zc:wchar_t -Zc:forScope -GR- -openmp- \
			 -Fd"$(INT_DIR)/vc100.pdb" -TC -wd4244 -FI"$(XDK_INC_DIR)/xbox_intellisense_platform.h"

LD_FLAGS := -NOLOGO

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
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean


# ================================================================
# Final library
# ================================================================

$(TARGET): $(OBJS)
	@echo "Linking $(@)..."
	@mkdir -p $(@D)
	@LIB=$(XDK_LIB_DIR) $(WINDOWS_SHIM) $(LD) $(LD_FLAGS) -OUT:"$@" $^

$(INT_DIR)/%.obj: %.c
	@mkdir -p $(@D)
	@INCLUDE=$(XDK_INC_DIR) $(WINDOWS_SHIM) $(CXX) $(CXX_FLAGS) -Fo"$@" $<
