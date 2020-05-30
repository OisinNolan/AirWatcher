build:
	g++ -w -Wfatal-errors \
	./*.cpp \
	

clean:
	rm ./exec;

run:
	./exec;
