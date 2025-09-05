compile_prod:
	clang++ main.cpp -o ./out/main.exe -Wall -Wextra -std=c++20

compile_debug:
	clang++ -DDEBUG main.cpp -o ./out/main_debug.exe -Wall -Wextra -std=c++20
