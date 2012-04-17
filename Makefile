all:	build	run

build:
	g++ -lpthread -g -o client client.cpp ChatClient.cpp RSA.cpp RsaHacker.cpp
	
run:
	./client -h 158.130.106.163 -p 12345 -n reek

clean:
	rm client
