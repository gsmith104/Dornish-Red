/*
 * main.cpp
 *
 *  Created on: Apr 6, 2012
 *      Author: cmilner
 */

#include "ChatClient.h"
#include "RsaHacker.h"
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

void usage();
void * listen(void *);
void * reply(void *);

int main (int argc, char * argv[]) {
	//check that there are command line arguments
	if (argc < 5) {
        usage();
        return 0;
    }

	//parse command line arguments
	char * host;
	int port;
	char * name = new char[20];
    for (int i = 1; i + 1 < argc; i += 2) {
    	char * token = argv[i];
    	int flag = (int) token[1];
    	switch (flag) {
    	case 'p':
    		port = atoi(argv[i+1]);
    		break;
    	case 'h':
    		host = argv[i+1];
    		break;

    	case 'n':
    		name = strcpy(name, argv[i+1]);
    		break;
    	}
    }
    ChatClient * client = new ChatClient(host, port, name);

    //exchange keys
    bool success = client->sendPublicKey();
    success = client->receiveServerKey();
    cout<<"My public key: "<<client->getPublicKey()<<endl;
    cout<<"Adversary Public Key: "<<client->getServerKey()[0]<<endl;

    RsaHacker * hack = 
         new RsaHacker(client->getServerKey()[0], client->getServerKey()[1]);
    long adversaryKey = (hack->getAdversaryKey())[0];
    cout<<"My private key: "<<client->getPrivateKey()<<endl;
    cout<<"Adversary private Key: "<<adversaryKey<<endl;
    

    pthread_t writer;
    pthread_t reader;

    pthread_create(&writer, 0, reply, client);
    pthread_create(&reader, 0, listen, client);

    pthread_join(writer, 0);
    pthread_join(reader, 0);

    delete client;
    delete name;
    delete hack;

    return 0;
}

void * listen(void * args) {
	ChatClient * client = (ChatClient *) args;
	while (client->isChatting()){
		client->receiveMessage();
	}
}

void * reply(void * args) {
	ChatClient * client = (ChatClient *) args;
	while (client->isChatting()){
		char message[1024];
		cout<< client->getHandle() << ":\n";
		cin.getline(message, 1024);
		client->sendMessage(client->getHandle());
		client->sendMessage(message);
	}
}

void usage() {
    cout << "Usage:\n -h <HostName> -p <PortNumber>\n";
    cout << "<PortNumber> must be a positive integer\n";
}
