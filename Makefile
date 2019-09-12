main.exe : voce.o main.o
	g++ voce.o main.o -o main.exe

voce.o : voce.cpp
	g++ -c voce.cpp -o voce.o
	
main.o : main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm *.o *.exe