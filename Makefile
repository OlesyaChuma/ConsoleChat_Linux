CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS = -lstdc++fs
TARGET = console_chat

SRC = src/main.cpp src/Chat.cpp src/FileStorage.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f src/*.o $(TARGET)

rebuild: clean all

check-data:
	@if [ -d data ]; then ls -ld data; else echo "Каталог data ещё не создан"; fi
	@if [ -f data/users.txt ]; then ls -l data/users.txt; else echo "Файл users.txt ещё не создан"; fi
	@if [ -f data/messages.txt ]; then ls -l data/messages.txt; else echo "Файл messages.txt ещё не создан"; fi

.PHONY: all run clean rebuild check-data
