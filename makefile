CC      := gcc
CFLAGS  := -ansi -pedantic -Wall -DNDEBUG
LDFLAGS	:= -lm -lMLV
INC		:= $(wildcard include/*.h)
OBJ     := obj/main.o $(patsubst include/%.h,obj/%.o,$(INC))
EXE     := bin/stealth

# recompile everything everytime
all:
	make clean
	mkdir -p bin obj data
	touch data/score.bin
	make $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

obj/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf bin/ obj/ data/
