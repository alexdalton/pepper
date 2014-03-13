TARGETS=manager node

CC=g++
CCOPTS=-Wall -Wextra

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

%: %.cpp
	$(CC) $(CCOPTS) -o $@ $<
