FLAGS = -o run
EXEC = g++ $(FLAGS) os.cpp sos.o

run: sos.o
	$(EXEC)

clean:
	rm run
