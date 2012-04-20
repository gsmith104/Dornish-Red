//
//  main.cpp
//  Dornish-Red
//
//  Created by Gregory Smith on 4/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "RsaHacker.h"
#include <stdio.h>
#include <stdlib.h>
#include "RSA.h"
#include "Server.h"
#include <string.h>
using namespace std;

/**
 * Reads a message from the client
 */
void *readit (void* arg) {
    ChatServer *server = (ChatServer *)arg;
    char message[1028];
    while (server->getStillChatting()){
        cout<<server->getChatHandle()<<endl;
        cin.getline(message,1028);
        server->sendMessage(server->getChatHandle());
        server->sendMessage(message);
    }   
}

/**
 * Writes a message to the client
 */
void *writeit (void *arg) {
    ChatServer *server = (ChatServer *)arg;
    while(server->getStillChatting()){
        server->readMessage();
    }
}


int main (int argc, const char * argv[])
{
    //Write function to validate input

    char handle[20];
    strcpy(handle, argv[2]); 
//    cout<<handle<<endl;
    ChatServer *server = new ChatServer(atoi(argv[1]), handle);
    if (server->recievePublicKey() && server->recieveC()){
        server->sendPublicKey();
        server->sendC();
    }
    
    RsaHacker *hacker = new RsaHacker(server->getClientKey(), server->getClientC());
    long*keys = hacker->getAdversaryKey();
    long privateKey = keys[0];
    cout<<"My public key is: "<<server->getRSA()->getPublicKey()<<endl;
    cout<<"My private key is: "<<server->getRSA()->getPrivateKey()<<endl;
    cout<<"The adversary's private key is: "<<privateKey<<endl;
    
    pthread_t reader, writer;
    pthread_create(&reader, NULL, readit, server);
    pthread_create(&writer, NULL, writeit, server);
    pthread_join(reader, NULL);
    pthread_join(writer, NULL);
    
    pthread_exit(0);

    server->closeConnection();
    delete server;
    delete hacker;
    return 0;
}

