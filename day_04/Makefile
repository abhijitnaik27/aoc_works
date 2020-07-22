OBJ = main.o

%.o : %.c
	g++ -Wall -c -g $^

target: $(OBJ)
	g++ -o $@ $^
	
clean:
	rm -rf $(OBJ) target
