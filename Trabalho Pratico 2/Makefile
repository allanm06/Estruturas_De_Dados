# Configurações de compilação
CC = gcc
CFLAGS = -Wall -g -Iinclude
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/tp2.out

# Lista de arquivos fonte e objeto
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Regra padrão
run: $(TARGET)

# Linkagem final
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compilação dos objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Criação dos diretórios
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Limpeza dos arquivos compilados
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Execução do programa
all: $(TARGET)
	$(TARGET) 20242TP22.csv
