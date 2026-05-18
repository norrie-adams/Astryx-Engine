@echo off
g++ src/*.cpp src/glad.c -Iinclude -Llib -lglfw3 -lopengl32 -lgdi32 -o engine.exe
engine.exe