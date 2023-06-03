all: compile link

compile:
	g++ -Isource/include -c *.cpp

link:
	g++ *.o -o main -Lsource/lib -lsfml-graphics -lsfml-window -lsfml-system