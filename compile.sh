#!/bin/bash

# Arquivos fonte
SOURCE="main.cpp grid.cpp position.cpp Block.cpp colors.cpp game.cpp"

# Nome do executável
OUTPUT="tetris"

# Comando de compilação
g++ -o $OUTPUT $SOURCE -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

# Verifica se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida! Para executar, use ./$OUTPUT"
else
    echo "Erro na compilação!"
fi
