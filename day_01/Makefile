OBJ = main.o

%.o : %.c
	gcc -c $^

target: $(OBJ)
	gcc -o $@ $^
	
clean:
	rm -rf $(OBJ) target
