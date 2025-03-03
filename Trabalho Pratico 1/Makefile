CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/registro.o $(OBJ)/sort.o
HDRS = $(INC)/registro.h $(INC)/sort.h
CFLAGS = -Wall -pg -c -I$(INC)

EXE = $(BIN)/tp1.out

all: $(EXE)
	./$(EXE) bin/input.xcsv

# Compila o executável final
$(EXE): $(OBJS)
	mkdir -p $(BIN)
	$(CC) -pg -o $(EXE) $(OBJS) $(LIBS)

# Compila o main.c
$(OBJ)/main.o: $(HDRS) $(SRC)/main.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c

# Compila o registro.c
$(OBJ)/registro.o: $(HDRS) $(SRC)/registro.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -o $(OBJ)/registro.o $(SRC)/registro.c

# Compila o sort.c
$(OBJ)/sort.o: $(HDRS) $(SRC)/sort.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -o $(OBJ)/sort.o $(SRC)/sort.c

# Limpa os arquivos objeto e o executável
clean:
	@rm -f $(EXE) $(OBJS) gmon.out
