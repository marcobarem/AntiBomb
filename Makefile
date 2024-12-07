# Compilador e flags
CC = gcc
CFLAGS = -Wall -pthread -lncurses -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Arquivos fonte e objetos
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/mural.c $(SRC_DIR)/exibicao.c $(SRC_DIR)/tedax.c $(SRC_DIR)/coordenador.c $(SRC_DIR)/utils.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nome do executável
TARGET = jogo

# Regra padrão
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

# Regra para compilar os arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos objeto e executáveis
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
