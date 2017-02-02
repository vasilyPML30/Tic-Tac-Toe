mkdir bin
g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/Player.cpp -o bin/Player.o
g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/NcursesView.cpp -o bin/NcursesView.o
g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/main.cpp -o bin/main.o
g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/Board.cpp -o bin/Board.o
g++ -c -std=c++14 -Wall -Wextra -Wshadow -Werror -g -I ./include src/BoardView.cpp -o bin/BoardView.o
g++ --static -static-libgcc bin/main.o bin/Board.o bin/BoardView.o bin/NcursesView.o bin/Player.o -lpdcurses -lcurldll -o tic-tac-toe
pause