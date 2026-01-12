# ================================================================
# Project configuration
# ================================================================

PROJECT_NAME := Tests
WINDOWS_SHIM := wine
CONFIG := Debug
CONSOLE_NAME := 192.168.1.14

BUILD_DIR := build
OUT_DIR := $(BUILD_DIR)/$(CONFIG)/bin
INT_DIR := $(BUILD_DIR)/$(CONFIG)/obj

TARGET := $(OUT_DIR)/$(PROJECT_NAME).xex


# ================================================================
# XexUtils dependency
# ================================================================

XEXUTILS_DIR := ..
XEXUTILS_TARGET_NAME := XexUtils$(if $(filter Debug,$(CONFIG)),d)
XEXUTILS_TARGET := $(XEXUTILS_DIR)/$(OUT_DIR)/$(XEXUTILS_TARGET_NAME).lib
XEXUTILS_INC := $(XEXUTILS_DIR)/include


# ================================================================
# Source files
# ================================================================

SRCS := $(shell find . -name '*.cpp')
OBJS := $(SRCS:%.cpp=$(INT_DIR)/%.obj)


# ================================================================
# XDK Toolchain
# ================================================================

XDK_BIN_DIR := $(XEDK)/bin/win32
XDK_INC_DIR := "$(XEDK)/include/xbox"
XDK_LIB_DIR := "$(XEDK)/lib/xbox"

CXX := "$(XDK_BIN_DIR)/cl.exe"
LD := "$(XDK_BIN_DIR)/link.exe"
IMAGEXEX := "$(XDK_BIN_DIR)/imagexex.exe"
XBCP := "$(XDK_BIN_DIR)/xbcp.exe"
XBREBOOT := "$(XDK_BIN_DIR)/xbreboot.exe"


# ================================================================
# Compiler and linker flags
# ================================================================

INCLUDES := $(XEXUTILS_INC)

CXX_FLAGS := -c $(addprefix -I ,$(INCLUDES)) -Zi -nologo -W4 -MP -D _XBOX -Gm- -EHsc -GS \
			 -fp:fast -fp:except- -Zc:wchar_t -Zc:forScope -GR- -openmp- -Fd"$(INT_DIR)/vc100.pdb" \
			 -TP -FI"$(XDK_INC_DIR)/xbox_intellisense_platform.h"

LD_FLAGS := -ERRORREPORT:QUEUE -NOLOGO -MANIFESTUAC:"level='asInvoker' uiAccess='false'" \
			-DEBUG -PDB:"$(OUT_DIR)/$(PROJECT_NAME).pdb" -STACK:"262144","262144" \
			-TLBID:1 -RELEASE -IMPLIB:"$(OUT_DIR)/$(PROJECT_NAME).lib" -XEX:NO

IMAGEXEX_FLAGS := -nologo -config:"config.xml"

ifeq ($(CONFIG),Debug)
	CXX_FLAGS += -WX- -Od -D _DEBUG -MTd -Gy- -GF-
else ifeq ($(CONFIG),Release)
	CXX_FLAGS += -WX -Ox -Oi -Os -D NDEBUG -MT -Gy -GF
	LD_FLAGS += -OPT:REF
else
	$(error Unknown CONFIG=$(CONFIG))
endif


# ================================================================
# Top-level targets
# ================================================================

all: build copy launch

build: $(TARGET)

copy: $(TARGET)
	@echo "Copying $< to console..."
	@$(WINDOWS_SHIM) $(XBCP) -Y -X:$(CONSOLE_NAME) -T "$<" "xE:\$(PROJECT_NAME)\$(PROJECT_NAME).xex"

launch: $(TARGET)
	@echo "Launching $<..."
	@$(WINDOWS_SHIM) $(XBREBOOT) "xE:\$(PROJECT_NAME)\$(PROJECT_NAME).xex"

clean:
	$(MAKE) -C $(XEXUTILS_DIR) $@
	rm -rf $(BUILD_DIR)

.PHONY: all build copy launch clean


# ================================================================
# Final XEX
# ================================================================

$(TARGET): $(OUT_DIR)/$(PROJECT_NAME).exe
	@echo "Creating $(@)..."
	@mkdir -p $(@D)
	@$(WINDOWS_SHIM) $(IMAGEXEX) $(IMAGEXEX_FLAGS) -out:"$@" "$<"

$(OUT_DIR)/$(PROJECT_NAME).exe: $(OBJS) $(XEXUTILS_TARGET)
	@echo "Linking $(@)..."
	@mkdir -p $(@D)
	@LIB=$(XDK_LIB_DIR) $(WINDOWS_SHIM) $(LD) $(LD_FLAGS) -OUT:"$@" $^

$(INT_DIR)/%.obj: %.cpp
	@mkdir -p $(@D)
	@INCLUDE=$(XDK_INC_DIR) $(WINDOWS_SHIM) $(CXX) $(CXX_FLAGS) -Fo"$@" $<


# ================================================================
# XexUtils build
# ================================================================

$(XEXUTILS_TARGET):
	$(MAKE) -C $(XEXUTILS_DIR)
