EXECBIN  = bigint-test

SOURCES  = $(wildcard *.cpp)
OBJECTS  = $(SOURCES:%.cpp=%.o)

CC       = g++ -std=c++17
CFLAGS   = -Wall -Wpedantic -Werror -Wextra
LFLAGS 	 = -lgmpxx -lgmp

.PHONY: all clean

all: $(EXECBIN)

$(EXECBIN): $(OBJECTS)
	$(CC) $^ $(LFLAGS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJECTS)
