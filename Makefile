CC = gcc
CFLAGS = -Wall -g

SRC = \
     main.c \
     # utilities/pwd.c \

OBJ = $(SRC:.c=.o)

OUTPUT = myshell

$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
.PHONY: clean
clean:
	rm -f $(OBJ) $(OUTPUT)

