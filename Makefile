CC = clang
CFLAGS = -g -O0 -Wall -Wextra -fsanitize=address
OBJ = main.o vector.o sort.o search.o list.o

build: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o build

# общее правило: любой X.o собирается из X.c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# зависимости от заголовков (без команд, команду берёт правило выше)
main.o:   main.c vector.h sort.h search.h list.h
vector.o: vector.c vector.h
sort.o:   sort.c sort.h
search.o: search.c search.h
list.o:   list.c list.h

run: build
	./build

clean:
	rm -rf build build.dSYM *.o

.PHONY: run clean