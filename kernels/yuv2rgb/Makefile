TOP=$(shell pwd)
BIN_PATH=$(TOP)/bin
C_PATH=$(TOP)/c
DRIVER_PATH=$(TOP)/driver
UTILS_PATH=$(TOP)/utils
DMEM_PATH=$(TOP)/dmem


CC=gcc

SOURCES=$(C_PATH)/yuv2rgb.c $(DRIVER_PATH)/yuv2rgb.drv.c $(UTILS_PATH)/driver_common.c 
EXECUTABLE=$(BIN_PATH)/yuv2rgb

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(SOURCES) 
		$(CC) $(LDFLAGS) $(SOURCES) -I$(UTILS_PATH) -o $@

compile:
	gcc ./driver/yuv2rgb.drv.c ./c/yuv2rgb.c ./utils/driver_common.c -I./utils -o $(BIN_PATH)/yuv2rgb

run:
	$(EXECUTABLE) $(DMEM_PATH)/yuv2rgb.dmem_init $(BIN_PATH)/yuv2rgb.out

clean:
	rm -f $(EXECUTABLE)

