build:
	g++ -std=c++11 -w -Wfatal-errors -o exec ./*.cpp 
	

clean:
	rm ./exec;

run:
	./exec;
