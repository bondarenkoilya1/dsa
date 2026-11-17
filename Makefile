CP=clang

all:
	$(CP) -g -O0 -Wall -Wextra -fsanitize=address main.c vector.c sort.c search.c list.c -o build & ./build