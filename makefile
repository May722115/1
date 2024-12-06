generate_hard.o: generate_hard.cpp generate_hard.h
	g++ -c generate_hard.cpp

generate_function.o: generate_function.cpp generate_function.h
	g++ -c generate_function.cpp

play_game.o: play_game.cpp play_game.h generate_hard.h
	g++ -c play_game.cpp

main.o: main.cpp generate_hard.h generate_function.h play_game.h
	g++ -c main.cpp

main: generate_hard.o generate_function.o play_game.o main.o
	g++ generate_hard.o generate_function.o play_game.o main.o -o main

clean:
	rm -f generate_hard.o generate_function.o play_game.o main.o main
