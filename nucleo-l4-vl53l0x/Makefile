default: all

Makefile_path := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

Toolchain = arm-none-eabi-

CFlags =
LFlags =

# Generic flags
CFlags += \
	-fdiagnostics-color=always \
	-Wall \
	-Wextra \
	-g \
	-Os \
	-ffunction-sections \
	-fdata-sections \
	-fno-common \
	-fno-exceptions

LFlags += \
	-Wl,--gc-sections \
	--static \
	-nostartfiles \
	-Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

	# -lm \
	# -lstdc++_nano \
	# -lc \
	# -lg \
	# -lrdimon


# MCU specific flags (stm32l476rg)
LINKER_SCRIPTS_DIR = $(Makefile_path)/../linker_scripts

CFlags += \
	-mcpu=cortex-m4 \
	-mthumb \
	-mfloat-abi=hard -mfpu=fpv4-sp-d16

LFlags += \
	-T $(LINKER_SCRIPTS_DIR)/stm32l476.ld


# Use LibOpenCm3
LIBOPENCM3_DIR = $(Makefile_path)/../libopencm3
CFlags += -I $(LIBOPENCM3_DIR)/include -DSTM32L4
LFlags += -L $(LIBOPENCM3_DIR)/lib -lopencm3_stm32l4

libopencm3:
	$(MAKE) -C $(LIBOPENCM3_DIR) -j

# Openocd configuration
OPENOCD_CFG = /usr/share/openocd/scripts/board/st_nucleo_l4.cfg




all: test.hex

%.cpp.o: %.cpp Makefile
	$(Toolchain)g++ $(CFlags) $< -o $@ -c

%.c.o: %.c Makefile
	$(Toolchain)gcc $(CFlags) $< -o $@ -c


test.elf: main.c.o i2c.c.o usart_usb.c.o
	$(Toolchain)gcc $(CFlags) $^ $(LFlags) -o $@

uart.elf: main_usart_usb_shell.c.o
	$(Toolchain)gcc $(CFlags) $^ $(LFlags) -o $@


%.hex: %.elf
	arm-none-eabi-objcopy -Oihex $^ $@



%.flash: %.hex
	sudo openocd -f $(OPENOCD_CFG) \
		-c "init" \
		-c "reset init" \
		-c "flash write_image erase $^" \
		-c "reset" \
		-c "shutdown"


clean:
	rm -f *.o *.a *.hex *.elf
