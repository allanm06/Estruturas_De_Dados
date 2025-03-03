# Configurações de compilação
CC = gcc
CFLAGS = -Wall -g -Iinclude
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/tp3.out

# Lista de arquivos fonte e objeto
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Declaração dos alvos phony
.PHONY: all clean debug

# Regra padrão: compila e executa
all: $(TARGET)
	./$(TARGET) arquivo.xcsv

# Compilação final para gerar o executável
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compilação de cada arquivo objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Criação dos diretórios necessários
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Limpeza de arquivos compilados
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Depuração para listar fontes e objetos
debug:
	@echo "Fontes: $(SOURCES)"
	@echo "Objetos: $(OBJECTS)"
	@echo "Executável: $(TARGET)"
