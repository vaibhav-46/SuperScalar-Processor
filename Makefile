processor: main.o processor.o instructions.o registerFile.o reservationStation.o storeBuffer.o branch.o rob.o
	g++ -o processor main.o processor.o instructions.o registerFile.o reservationStation.o storeBuffer.o branch.o rob.o

%.o: %.c
	g++ -g -c $(input) -o $(output)

clean : 
	rm -rf *.o processor
