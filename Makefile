CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = reproductor.exe

SRC = src/main.cpp \
      src/Cancion.cpp \
      src/Node.cpp \
      src/List.cpp \
      src/Reproductor.cpp \
      src/FileManager.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	if exist $(TARGET) del /Q $(TARGET)