all:
	mkdir -p bin/
	g++ src/Main.cpp src/BlockAlignment.cpp -o bin/BlockAlignment