.PHONY: all check clean debug profile valgrind math
# compile flags
CFLAGS := -Wall -Werror -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024
CFLAGS += -Wfloat-equal -Waggregate-return -Winline 
DEBUG_CFLAGS := -g -p -fprofile-arcs -ftest-coverage
PROFILE_CFLAGS := -g -pg
# compile commands
DEBUG_GDB := gdb
CC := gcc
# files
SRCS := filename.c  # source files
OBJS := filename.o  # object files created
# executables created
EXE := filename  # main executable
EXE_PROFILE := filename_profile  # profile executable
EXE_DEBUG := filename_debug  # debug executable
# additional variables
CLEAN_ALL_FILES := *txt *.o *.out $(EXE) $(EXE_DEBUG) $(EXE_PROFILE)
MATH_LINK := -lm  # math.h funcs defined in libm.a. -lm links to libm.a library.
VALGRIND := valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all

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

math: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(EXE) $(MATH_LINK)
	@./$(EXE)

# checks for memory leaks from EXE
valgrind: all
	$(VALGRIND) ./$(EXE)
