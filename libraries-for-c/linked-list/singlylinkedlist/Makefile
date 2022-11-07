CFLAGS += -std=c18
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -Waggregate-return -Wwrite-strings -Wfloat-equal -Wvla

TARGET=ll_driver

$(TARGET).o: CPPFLAGS+=-D_POSIX_C_SOURCE=200809L
$(TARGET): $(TARGET).o linkedlist.o

.PHONY: clean

clean:
	$(RM) *.o $(TARGET)
