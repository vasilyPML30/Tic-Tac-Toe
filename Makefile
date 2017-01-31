all: bin main
main: bin/main.o bin/Board.o bin/BoardView.o bin/NcursesView.o
	g++ bin/main.o bin/Board.o bin/BoardView.o bin/NcursesView.o -lncurses -o main
bin/NcursesView.o:  src/NcursesView.cpp include/Board.h include/NcursesView.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include src/NcursesView.cpp -o bin/NcursesView.o
bin/main.o: src/main.cpp include/Board.h include/BoardView.h include/NcursesView.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include src/main.cpp -o bin/main.o
bin/Board.o: src/Board.cpp include/Board.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include src/Board.cpp -o bin/Board.o
bin/BoardView.o: src/BoardView.cpp include/Board.h include/BoardView.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include src/BoardView.cpp -o bin/BoardView.o
clean:
	rm -f -r bin
	rm -f -r main
bin:
	mkdir -p bin
