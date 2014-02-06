TARGETS=client listener server talker

CC=gcc
CCOPTS=-Wall -Wextra -pthread

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

%: %.c
	$(CC) $(CCOPTS) -o $@ $<
