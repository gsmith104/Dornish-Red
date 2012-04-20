all:	build	run

build:
	g++ -pthread -g -o client client.cpp ChatClient.cpp RSA.cpp RsaHacker.cpp
	
run:
	./client -h 127.0.0.1 -p 12345 -n Reek

test:
	g++ -g -o hackTest RsaHackerTest.cpp RsaHacker.cpp RSA.cpp
	./hackTest

clean:
	rm client hackTest core
