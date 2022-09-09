.PHONY: all check clean debug profile valgrind
CFLAGS := -Wall -Werror -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024
CFLAGS += -Wfloat-equal -Waggregate-return -Winline 
DEBUG_CFLAGS := -g -p -fprofile-arcs -ftest-coverage
PROFILE_CFLAGS := -g -pg
DEBUG_GDB := gdb
CC := gcc

#
# Project Files
#
SRCS := websters.c websters_functions.c 
OBJS := websters.o websters_functions.o  # object files created
EXE := webby  # name of executable
EXE_PROFILE := webby_profile  # name of profile executable
EXE_DEBUG := webby_debug
CLEAN_ALL_FILES := *txt *.o *.out $(EXE) $(EXE_DEBUG) $(EXE_PROFILE)


all: $(EXE)

# creates object files from .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# creates executable from object
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# creates profile executable
$(EXE_PROFILE): $(OBJS)
	$(CC) $(CFLAGS) $(PROFILE_CFLAGS) $^ -o $@ 

# creates EXE_PROFILE executable
profile: CFLAGS += $(PROFILE_CFLAGS)
profile: $(EXE_PROFILE)

# creates debug executable
$(EXE_DEBUG): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) $^ -o $@ 

#creates EXE_DEBUG executable
debug: CFLAGS += $(DBUG_FLAGS)
debug: $(EXE_DEBUG)

# removes specified file types from directory
clean: 
	rm -f $(CLEAN_ALL_FILES)

# executes EXE
check: all
	@./$(EXE)

# checks for memory leaks from EXE
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE)