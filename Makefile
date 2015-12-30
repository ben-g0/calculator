include .knightos/variables.make

#INCLUDE+=add to your include path

HEADERS:=$(wildcard *.h)

ALL_TARGETS:=$(BIN)calculator

$(BIN)calculator: $(OUT)main.o $(OUT)crt0.o $(OUT)functions.o
	mkdir -p $(BIN)
	scas $(ASFLAGS) $(OUT)crt0.o $(LIBRARIES) $(OUT)main.o $(OUT)functions.o -o $(BIN)calculator

include .knightos/sdk.make
