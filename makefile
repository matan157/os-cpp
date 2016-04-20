FLAGS = -o run
EXEC = g++ $(FLAGS) os.cpp sos.o
DEP = sos.o PCB.h freespace.h

run: $(DEP)
	$(EXEC)

clean:
	rm run
