OBJ = main.o

%.o : %.cpp
	g++ -c -g $^

target: $(OBJ)
	g++ -o $@ $^
	
clean:
	rm -rf $(OBJ) target
