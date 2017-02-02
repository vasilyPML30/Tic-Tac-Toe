all: bin main
main: bin/main.o bin/Board.o bin/BoardView.o bin/NcursesView.o bin/Player.o
	g++ bin/main.o bin/Board.o bin/BoardView.o bin/NcursesView.o bin/Player.o -lncurses -lcurl -o main
bin/Player.o:  src/Player.cpp include/Board.h include/Player.h
	g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/Player.cpp -o bin/Player.o
bin/NcursesView.o:  src/NcursesView.cpp include/Board.h include/NcursesView.h include/Player.h
	g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/NcursesView.cpp -o bin/NcursesView.o
bin/main.o: src/main.cpp include/Board.h include/BoardView.h include/NcursesView.h
	g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/main.cpp -o bin/main.o
bin/Board.o: src/Board.cpp include/Board.h
	g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/Board.cpp -o bin/Board.o
bin/BoardView.o: src/BoardView.cpp include/Board.h include/BoardView.h
	g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/BoardView.cpp -o bin/BoardView.o
clean:
	rm -f -r bin
	rm -f -r main
bin:
	mkdir -p bin
