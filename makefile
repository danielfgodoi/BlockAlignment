all:
	mkdir -p bin/ && g++ src/Main.cpp src/BlockAlignment.cpp -o bin/BlockAlignment -std=c++11
	@echo ""

O2:
	mkdir -p bin/ && g++ src/Main.cpp src/BlockAlignment.cpp -o bin/BlockAlignment -O2 -std=c++11
	@echo ""

O3:
	mkdir -p bin/ && g++ src/Main.cpp src/BlockAlignment.cpp -o bin/BlockAlignment -O3 -std=c++11
	@echo ""

Ofast:
	mkdir -p bin/ && g++ src/Main.cpp src/BlockAlignment.cpp -o bin/BlockAlignment -Ofast -std=c++11
	@echo ""
