build:
	g++ -std=c++11 -w -o exec ./*.cpp 
	

clean:
	rm ./exec;

run:
	./exec;
