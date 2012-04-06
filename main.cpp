//
//  main.cpp
//  Dornish-Red
//
//  Created by Gregory Smith on 4/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "RSA.h"
#include "Server.h"
#include <string.h>
using namespace std;


void *readit (void* arg) {
    ChatServer *server = (ChatServer *)arg;
    char* message;
    while (server->getStillChatting()){
        cin>>message;
        server->sendMessage(server->getChatHandle());
        server->sendMessage(message);
    }
    
    
}

void *writeit (void *arg) {
    ChatServer *server = (ChatServer *)arg;
    while(server->getStillChatting()){
        server->readMessage();
    }
}


int main (int argc, const char * argv[])
{
    //Write function to validate input

    char * handle;
    strcpy(handle, argv[2]);    
    ChatServer *server = new ChatServer(atoi(argv[1]), handle);
    if (server->recievePublicKey() && server->recieveC()){
        server->sendPublicKey();
        server->sendC();
    }
    
    pthread_t reader, writer;
    pthread_create(&reader, NULL, readit, server);
    pthread_create(&writer, NULL, writeit, server);
    pthread_join(reader, NULL);
    pthread_join(writer, NULL);
    
    pthread_exit(0);

    server->closeConnection();
    delete server;
    return 0;
}

