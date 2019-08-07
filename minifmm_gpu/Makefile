default: fmm

ifndef COMPILER
define compiler_help
Set COMPILER to change flags (defaulting to GNU).
Available compilers are :
	GNU INTEL

endef
$(info $(compiler_help))
COMPILER=GNU
endif

ifndef TARGET
define target_help
Set TARGET to change device (defaulting to GPU)
Available targets are :
	CPU GPU
endef
$(info $(target_help))
TARGET=GPU
endif

ARCH=native

ARCH=compute_50

CC=nvcc
CFLAGS += -arch=$(ARCH) -O3 -x cu -std=c++11 -dc --use_fast_math -D_FORCE_INLINES

EXE=fmm
TYPE=DOUBLE

ifeq ($(TYPE), DOUBLE)
	CFLAGS += -DUSE_DOUBLE
else
	CFLAGS += -DUSE_FLOAT
endif

LIBS += -lm -arch=$(ARCH)

REF_DIR=$(abspath $(shell pwd)/../ref)
#CFLAGS += -I$(REF_DIR)

HEADERS=$(wildcard include/*.h)
HEADERS+=$(wildcard include/*.hpp)
CFLAGS += -Iinclude/
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

print-%  : ; @echo $* = $($*)

$(EXE): $(OBJS) $(KOKKOS_LINK_DEPENDS)
	$(CC) $(OBJS) $(LINKER_OPTS) $(LIBS) -o $@

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJS)
	-rm -f $(EXE)
