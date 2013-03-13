TOP=$(shell pwd)
BIN_PATH=$(TOP)/bin
C_PATH=$(TOP)/c
DRIVER_PATH=$(TOP)/driver
UTILS_PATH=$(TOP)/utils
DMEM_PATH=$(TOP)/dmem


CC=gcc

SOURCES=$(C_PATH)/gaussian5x5int.c $(DRIVER_PATH)/gaussian5x5int.drv.c $(UTILS_PATH)/driver_common.c 
EXECUTABLE=$(BIN_PATH)/gaussian5x5int
INPUT=$(DMEM_PATH)/gaussian5x5int.dmem_init $(DMEM_PATH)/gaussian5x5int.dmem_meta
OUTPUT=$(DMEM_PATH)/gaussian5x5int.result

DMEM_INIT_EXECUTABLE=$(BIN_PATH)/dmem_init
DMEM_INIT_SOURCES=$(DRIVER_PATH)/dmem_init.c $(UTILS_PATH)/pgm.c
DMEM_INIT_INPUT=$(DMEM_PATH)/lenna.pgm
DMEM_INIT_OUTPUT=$(DMEM_PATH)/gaussian5x5int.dmem_init $(DMEM_PATH)/gaussian5x5int.dmem_meta

DMEM_DUMP_EXECUTABLE=$(BIN_PATH)/dmem_dump
DMEM_DUMP_SOURCES=$(DRIVER_PATH)/dmem_dump.c $(UTILS_PATH)/pgm.c  $(UTILS_PATH)/driver_common.c 
DMEM_DUMP_INPUT=$(DMEM_PATH)/gaussian5x5int.result $(DMEM_PATH)/gaussian5x5int.dmem_meta
DMEM_DUMP_OUTPUT=$(DMEM_PATH)/out.pgm


all: run_dmem_init run_driver run_dmem_dump

run_dmem_init: $(DMEM_INIT_EXECUTABLE)
	$(DMEM_INIT_EXECUTABLE) $(DMEM_INIT_INPUT) $(DMEM_INIT_OUTPUT)

$(DMEM_INIT_EXECUTABLE): $(DMEM_INIT_SOURCES) 
		$(CC) $(LDFLAGS) $(DMEM_INIT_SOURCES) -I$(UTILS_PATH) -o $@

run_driver: $(EXECUTABLE)
	$(EXECUTABLE) $(INPUT) $(OUTPUT)
	
$(EXECUTABLE): $(SOURCES) 
		$(CC) $(LDFLAGS) $(SOURCES) -I$(UTILS_PATH) -o $@

run_dmem_dump: $(DMEM_DUMP_EXECUTABLE)
	$(DMEM_DUMP_EXECUTABLE) $(DMEM_DUMP_INPUT) $(DMEM_DUMP_OUTPUT)

$(DMEM_DUMP_EXECUTABLE): $(DMEM_DUMP_SOURCES) 
		$(CC) $(LDFLAGS) $(DMEM_DUMP_SOURCES) -I$(UTILS_PATH) -o $@

clean:
	rm -f $(EXECUTABLE) $(OUTPUT) $(DMEM_INIT_EXECUTABLE) $(DMEM_DUMP_EXECUTABLE) $(DMEM_DUMP_OUTPUT)


