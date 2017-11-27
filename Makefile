
test:
	g++ -lgtest -std=c++14 tests/*.cpp -o bin/test && ./bin/test

lint:
	cppcheck --enable=all .
