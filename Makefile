EXEC := main
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
HDRS := $(wildcard *.h)

$(EXEC): $(OBJS)
	g++ -g -o $(EXEC) $(OBJS)

%.o: %.cpp $(HDRS)
	g++ -g -c -o $@ $<

clean:
	rm -rf *.o $(EXEC) main.out

.PHONY: clean

