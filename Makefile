##############################################################################################
# Usage:
# make [opt=dbg]		// -O0, -g (not optimzed, debug symbols)
# make opt=dbgopt		// -O2 -g (optimzed, debug symbols)
# make opt=release		// -O2 optimized, no more debug symbols
##############################################################################################
# Start of user section
#
PROJ = main

# Define linker script file here
LDSCRIPT = config/stm32f411re_flash.lds

# List all user C define here
UDEFS = -DSTM32F411xE

# Define ASM defines here
UADEFS = 

# List C source files here
SRC  = startup/stm32f411_periph.c startup/sys_handlers.c startup/rcc.c \
       startup/system_stm32f4xx.c \
       lib/uart.c lib/term.c \
       src/${PROJ}.c

# List ASM source files here
ASRC = startup/startup_stm32f411xe.s


# List all user directories here
UINCDIR = .

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = libshield/libshield.a lib/libstm32.a

# include external libraries and board drivers
#include libshield/lib.mk

#
# End of user defines
#############################################################################


#############################################################################
# Start of default section
#
ifeq ($(OS),Windows_NT)
    SHELL=C:/Windows/System32/cmd.exe
else
    SHELL=sh
endif

opt ?= dbg

TARGET  = arm-none-eabi-
CC      = $(TARGET)gcc
OBJCOPY = $(TARGET)objcopy
AS      = $(TARGET)gcc -x assembler-with-cpp -c
SIZE    = $(TARGET)size
OBJDUMP = $(TARGET)objdump

ARCH      = armv7e-m
FLOAT-ABI = hard
CPU       = cortex-m4
CPUFLAGS  = -mthumb
FPU       = fpv4-sp-d16

# List all default C defines here, like -D_DEBUG=1
DDEFS = -march=$(ARCH) -mfloat-abi=$(FLOAT-ABI) -mcpu=$(CPU) -mfpu=$(FPU) $(CPUFLAGS)

# List all default ASM defines here, like -D_DEBUG=1
DADEFS = -D__ASSEMBLY__

# List all default directories to look for include files here
DINCDIR = 

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS = 

#
# End of default section
##############################################################################################

INCDIR  = $(patsubst %,-I%,$(DINCDIR) $(UINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))
DEFS    = $(DDEFS) $(UDEFS)
ADEFS   = $(DADEFS) $(UADEFS)
OBJS    = $(SRC:.c=.o) $(ASRC:.s=.o)
LIBS    = $(DLIBS) $(ULIBS)

ifeq (${opt},release)
	OPT= -O2 -fomit-frame-pointer
else ifeq (${opt},dbgopt)
	OPT= -g -O2 -fomit-frame-pointer -D__DEBUG__
else
	OPT= -g -fno-omit-frame-pointer -O0 -D__DEBUG__
endif

ASFLAGS = $(INCDIR) $(DEFS) -Wa,--gdwarf2 $(ADEFS)
CFLAGS = -std=c99 $(INCDIR) $(OPT) $(DEFS) -Wwrite-strings -Wold-style-definition -Wvla
CFLAGS += -pedantic -Wall -Wextra -Wconversion -Wno-sign-conversion
CFLAGS += -Warray-bounds -Wno-unused -Wno-unused-parameter
LDFLAGS = $(DEFS) -T$(LDSCRIPT) -Wl,-Map=$@.map,--gc-sections $(LIBDIR)

# Generate dependency information
CFLAGS += -MD -MP -MF .dep/$(@F).d
ASFLAGS += -MD -MP -MF .dep/$(@F).d

#
# makefile rules
#
all: $(OBJS) main.elf main.bin main.hex

%o: %c
	$(CC) -c $(CFLAGS) $< -o $@

%o: %s
	$(AS) $(ASFLAGS) $< -o $@

%.elf: $(OBJS) $(LDSCRIPT)
	$(CC) -o $@ $(filter-out %.lds, $^) $(LDFLAGS) $(LIBS) -lc -lgcc -lgcov -lm
	$(OBJDUMP) -h $@
	$(SIZE) $@
	
%hex: %elf
	$(OBJCOPY) -O ihex $< $@

%bin: %elf
	$(OBJCOPY) -O binary $< $@
	
clean:
	-rm -f $(OBJS)
	-rm -f *.elf
	-rm -f *.map
	-rm -f *.bin
	-rm -f *.hex
	-rm -fR .dep/*

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

.PHONY: clean all

