all: 
	clang++ -std=c++11 -I /usr/local/Cellar/armadillo/7.300.1/include ./src/*.cpp -framework Accelerate -o chemlab
