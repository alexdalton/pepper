TARGETS=manager distvec linkstate

CC=g++
CCOPTS=-Wall -Wextra

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

%: %.cpp
	$(CC) $(CCOPTS) -o $@ $<
