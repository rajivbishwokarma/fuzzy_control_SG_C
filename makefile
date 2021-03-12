CC = gcc
MAIN = c/main.o
OBJS = inc/fuzzification.o inc/defuzzification.o inc/rulebase.o
CFLAGS = -Wall -Werror -Wmissing-prototypes
NAME = exec/fuzzy_control

all: $(NAME)

$(NAME): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

fuzzification.o: inc/fuzzification.h
defuzzification.o: inc/defuzzification.h
rulebase.o: inc/rulebase.h

clean:
	rm -f *~ c/*.o inc/*.o $(PROG) core


