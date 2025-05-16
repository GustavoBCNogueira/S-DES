CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iheaders
SRC_DIR = src
OBJ_DIR = obj
BIN = main

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Regra padrão
all: $(BIN)

# Linkagem
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criação da pasta obj/
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean
