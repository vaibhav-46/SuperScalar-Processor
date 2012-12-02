CC = g++
CFLAGS = -g -Wall

processor: main.o processor.o instructions.o registerFile.o reservationStation.o storeBuffer.o branch.o rob.o
	$(CC) $(CFLAGS) -o processor main.o processor.o instructions.o registerFile.o reservationStation.o storeBuffer.o branch.o rob.o

processor.o : processor.cpp processor.h
	g++ -g -Wall -c processor.cpp -o processor.o

instructions.o : instructions.cpp instructions.h
	g++ -g -Wall -c instructions.cpp -o instructions.o

registerFile.o : registerFile.cpp registerFile.h
	g++ -g -Wall -c registerFile.cpp -o registerFile.o

reservationStation.o : reservationStation.cpp reservationStation.h
	g++ -g -Wall -c reservationStation.cpp -o reservationStation.o

storeBuffer.o : storeBuffer.cpp storeBuffer.h
	g++ -g -Wall -c storeBuffer.cpp -o storeBuffer.o

branch.o : branch.cpp branch.h
	g++ -g -Wall -c branch.cpp -o branch.o

rob.o : rob.cpp rob.h
	g++ -g -Wall -c rob.cpp -o rob.o

main.o : main.cpp 
	g++ -g -Wall -c main.cpp -o main.o

clean : 
	rm -rf *.o processor
