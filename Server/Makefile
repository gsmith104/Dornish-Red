all:	run

run:	build
	./dornish 12345 Ned:

build:
	g++ -pthread -o dornish main.cpp RSA.cpp Server.cpp RsaHacker.cpp

clean:
	rm dornish