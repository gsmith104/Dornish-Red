//
//  Server.cpp
//  Dornish-Red
//
//  Created by Gregory Smith on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Server.h"

using namespace std;


ChatServer::ChatServer(){
    
}

ChatServer::ChatServer(int port, char* chatName){
    coder = new RSA();
    chatHandle = chatName;
    createConnection(port);
    connfd = listenFor(srvfd);
    stillChatting = true;
}

void ChatServer::createConnection(int portNum){
    srvfd = listenFor(portNum);
}

bool ChatServer::sendC(){
    long c = coder->getC();
    write(connfd, &c, sizeof(long));
    return true;
}

bool ChatServer::sendPublicKey(){
    long key = coder->getPublicKey();
    write(connfd, &key, sizeof(long));
    return true;
    
}

bool ChatServer::recievePublicKey(){
    read(connfd, &clientKey, sizeof(long));
    return true;
}

bool ChatServer::recieveC(){
    read(connfd, &clientC, sizeof(long));
    return true;

}

bool ChatServer::sendMessage(char * message){
    if (strcmp(message, "Winter is coming")==0){
        stillChatting = false;
    }

    int length = strlen(message);
    int bytesWritten = write(connfd, &length, sizeof(int));
    if (bytesWritten < sizeof(int)){
        return false;
    }
    
    for (int i = 0; i<strlen(message); i++){
        long character = coder->endecrypt((long)message[i], clientKey, clientC);
        bytesWritten = write(connfd, &character, sizeof(long));
        if (bytesWritten < sizeof(long)){
            return false;
        }
    }
    
    return true;
}

bool ChatServer::readMessage(){
    int length = 0;
    int bytesRead = read(connfd, &length, sizeof(int));
    if (bytesRead < sizeof(int)){
        return false;
    }
    
    char message[length + 1];
    for (int i = 0; i<length; i++) {
        long character = read(connfd, &character, sizeof(long));
        if (character < sizeof(long)){
            return false;
        }
        character = coder->endecrypt(character, coder->getPrivateKey(), coder->getC());
        message[i] = (char)character;
    }
    message[length] = '\0';
    if (strcmp(message, "Winter is coming")==0){
        stillChatting = false;
        sendMessage(message);
        
    }
    cout<<message<<endl;
    return true;
}

bool ChatServer::closeConnection(){
    close(connfd);
    close(srvfd);
}

bool ChatServer::getStillChatting(){
    return stillChatting;
}

char* ChatServer::getChatHandle(){
    return chatHandle;
}

ChatServer::~ChatServer(){
    delete coder;
}
