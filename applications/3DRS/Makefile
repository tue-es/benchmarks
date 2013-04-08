# Use GCC
CC				:= g++
#CFLAGS			:= -O3 -c -fopenmp -ftree-vectorize -ffast-math -msse2 -ftree-vectorizer-verbose=5
CFLAGS			:= -O3 -c -fopenmp -fno-tree-vectorize

# Set sources and directories
GCC_SOURCES		:= main.c kernel_cpu.c bitmap.c
OBJDIR			:= obj
OBJECTS_GCC		:= $(GCC_SOURCES:%.c=$(OBJDIR)/%.o)
EXECUTABLE		:= executable

all: $(GCC_SOURCES) $(EXECUTABLE)

$(EXECUTABLE):  $(OBJECTS_GCC)
	$(CC) $(OBJECTS_GCC) -o $@

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJECTS_GCC) 
	rm -f $(EXECUTABLE)
	rm -f ./images/o*.bmp


run: all
	./$(EXECUTABLE)

$(OBJDIR)/main.o: config.h 
$(OBJDIR)/kernel_cpu.o: config.h
