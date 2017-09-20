
BR_DIR := /home/andrea/src/buildroot-2017.02/output
CC := $(BR_DIR)/host/usr/bin/arm-linux-gnueabihf-g++
CFLAGS :=-Wall -I$(BR_DIR)/host/opt/ext-toolchain/arm-linux-gnueabihf/include/c++/5.3.1/ -I$(BR_DIR)/host/opt/ext-toolchain/arm-linux-gnueabihf/include/c++/5.3.1/arm-linux-gnueabihf/

TARGET ?= programmer

ifeq ($(shell bash -c 'type -p $(TARGET)'),)
SSH_RASPI ?= ssh root@raspi
else
SSH_RASPI ?= sh -c
endif

$(TARGET): libSunxi.o $(TARGET).cc
	$(CC) -o $(TARGET) -Wall -Os $(TARGET).cc libSunxi.o -lrt -lstdc++

libSunxi.o: libSunxi.cc libSunxi.h
	$(CC) -c -Wall -Os libSunxi.cc -lrt -lstdc++

example.blif: example.v
	yosys -p 'synth_ice40 -blif example.blif' example.v

example.asc: example.blif example.pcf
	arachne-pnr -d 8k -p example.pcf -o example.asc example.blif

example.bin: example.asc
	icepack example.asc example.bin

example_sram: example.bin
	$(SSH_RASPI) '/usr/local/bin/$(TARGET) -p' < example.bin

example_flash: example.bin
	$(SSH_RASPI) '/usr/local/bin/$(TARGET) -f' < example.bin
	$(SSH_RASPI) '/usr/local/bin/$(TARGET) -b'

reset:
	$(SSH_RASPI) '/usr/local/bin/$(TARGET) -f' < example.pcf
	$(SSH_RASPI) '/usr/local/bin/$(TARGET) -b'

install: $(TARGET)
	sudo install $(TARGET) /usr/local/bin/
	sudo chmod u+s /usr/local/bin/$(TARGET)

uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

clean:
	rm -f $(TARGET) *.o example.blif example.asc example.bin

.PHONY: example_sram example_flash reset install clean

