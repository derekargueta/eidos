
test:
	g++ -lgtest -std=c++14 tests/*.cpp -o bin/test && ./bin/test

kmp:
	g++ -lgtest -std=c++14 tests/kmp.cpp -o bin/driver && ./bin/driver

lint:
	cppcheck --enable=all .
