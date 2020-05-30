build:
	g++ -w -Wfatal-errors -o exec ./*.cpp 
	

clean:
	rm ./exec;

run:
	./exec;
