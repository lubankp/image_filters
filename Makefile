all: compile link

compile:
	g++ -c main.cpp -I"C:\Users\Dell\Desktop\C++\Libraries\SFML\include"

link:
	g++ main.o -o main -L"C:\Users\Dell\Desktop\C++\Libraries\SFML\lib" -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f main *.o