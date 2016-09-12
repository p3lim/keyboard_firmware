# Target file name
TARGET = firmware_lufa

# Core top directory
TMK_DIR = tmk_keyboard/tmk_core

# Project directory
TARGET_DIR = .

# Project-specific files
SRC = matrix.c \
	keymap.c \
	common.c

CONFIG_H = config.h

# MCU name
MCU = atmega32u4

# Processor and input frequency (in Hz)
F_CPU = 16000000
F_USB = $(F_CPU)

# Target architecture (LUFA-specific)
ARCH = AVR8

# Interrupt-driven control endpoint
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Boot section size (in bytes)
OPT_DEFS += -DBOOTLOADER_SIZE=512

# Features
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
NKRO_ENABLE = yes

# Search paths for core files
VPATH += $(TARGET_DIR)
VPATH += $(TMK_DIR)

include $(TMK_DIR)/protocol/lufa.mk
include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk
