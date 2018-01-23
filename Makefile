TARGET = $(shell ls -t | sed -n '/\.cpp$$/{s/.cpp$$//;p;q;}')
CC = $(shell if command -v clang++ >/dev/null 2>&1; then echo "clang++"; else echo "g++"; fi)
CFLAGS = -O3 -std=c++14 -Wall
DFLAGS = -O0 -std=c++14 -Wall -Wextra -g -fsanitize=integer -DDEBUG

.PHONY: debug run edit clean

$(TARGET).exe: $(TARGET).cpp
	$(CC) $(CFLAGS) $(TARGET).cpp -o $(TARGET).exe

debug: $(TARGET).cpp
	$(CC) $(DFLAGS) $(TARGET).cpp -o $(TARGET).exe

run: $(TARGET).exe
	./$(TARGET).exe

edit:
	vim $(TARGET).cpp

clean:
	-rm -f *.stackdump *.exe *.o .*.swp
