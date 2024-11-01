#not using .bin to avoid linking problems
#try to figure out why .elf is better then .bin in linking management

# Compiler settings
CC = avr-gcc
CFLAGS = -mmcu=atmega328p -Wall -Os -Iinc

# Flashing settings
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
AVRDUDE_PORT = /dev/ttyUSB0
AVRDUDE_PROGRAMMER = arduino

# Example file's name
EXAMPLE = pwm_exp

# Directories
SRC_DIR = src
EXAMPLES_DIR = examples
BUILD_DIR = build

# Output files
TARGET = $(BUILD_DIR)/$(EXAMPLE)
HEX = $(BUILD_DIR)/$(EXAMPLE).hex

# Source files
SRCS = $(EXAMPLES_DIR)/$(EXAMPLE).c $(SRC_DIR)/*.c

# Default target
.PHONY: all flash clean

default: clean all flash

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the ELF file
all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Convert ELF to HEX for flashing
$(HEX): $(TARGET)
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET) $(HEX)

# Flash the HEX file to the microcontroller
flash: $(HEX)
	$(AVRDUDE) -F -V -c $(AVRDUDE_PROGRAMMER) -p m328p -P $(AVRDUDE_PORT) -b 115200 -U flash:w:$(HEX)

# Clean up the build directory
clean:
	rm -rf $(BUILD_DIR)














#default: build
##
#build: 
#	avr-gcc -mmcu=atmega328p examples/pwm_exp.c src/fastpwm.c -o Build/test
##
#burn: build
#	avr-objcopy -O ihex -R .eeprom test Build/test.hex
##
#	avrdude -F -V -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:test.hex
#
# Compiler and flashing settings