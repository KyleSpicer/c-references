.PHONY: all check clean
CFLAGS := -Wall -Werror -Wextra
CC := gcc
EXE := song
OBJS := main.o shout.o let.o 

all: $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o
	rm -f $(EXE)

check: $(EXE)
	@./$(EXE)