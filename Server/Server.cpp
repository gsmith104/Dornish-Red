//
//  Server.cpp
//  Dornish-Red
//
//  Created by Gregory Smith on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Server.h"
#include "mysocket.h"

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

/**
 * Opens a connection on a specific port
 */
void ChatServer::createConnection(int portNum){
    srvfd = makeListener(portNum);
}

/**
 * Sends the C value of the RSA object to the client
 */
bool ChatServer::sendC(){
    long c = coder->getC();
    write(connfd, &c, sizeof(long));
    return true;
}

/**
 * Sends the public key value of the RSA object to the client
 */
bool ChatServer::sendPublicKey(){
    long key = coder->getPublicKey();
    write(connfd, &key, sizeof(long));
    return true;
    
}

/**
 * Recieveds the clients public key
 */
bool ChatServer::recievePublicKey(){
    read(connfd, &clientKey, sizeof(long));
    return true;
}

/**
 * Recieveds the clients C value
 */
bool ChatServer::recieveC(){
    read(connfd, &clientC, sizeof(long));
    return true;

}

/**
 * Sends a message to the client through RSA encryption.  Converts characters to long values that are the encrypted
 */
bool ChatServer::sendMessage(char * message){
    if (strcmp(message, "yield")==0){
        stillChatting = false;
    }

    int length = strlen(message);
    int bytesWritten = write(connfd, &length, sizeof(int));
    if (bytesWritten < sizeof(int)){
        return false;
    }
    
    for (int i = 0; i<strlen(message); i++){
        long character = coder->endecrypt((long)message[i], clientKey, clientC);
//        char character = message[i];
        bytesWritten = write(connfd, &character, sizeof(long));
        if (bytesWritten < sizeof(long)){
            return false;
        }
    }
    
    return true;
}

/**
 * Recieves a message from the client as a number of long values.  Decrypts the values and builds them into a char[].
 */
bool ChatServer::readMessage(){
    int length = 0;
    int bytesRead = read(connfd, &length, sizeof(int));
    if (bytesRead < sizeof(int)){
        return false;
    }
    
    char message[length + 1];
    for (int i = 0; i<length; i++) {
        long character;
        int n  = read(connfd, &character, sizeof(long));
        if (n < sizeof(long)){
            return false;
        }
        character = coder->endecrypt(character, coder->getPrivateKey(), coder->getC());
        message[i] = character;
    }
    message[length] = '\0';
    if (strcmp(message, "yield")==0){
        stillChatting = false;
        sendMessage("yield");
        
    }
    cout<<message<<endl;
    return true;
}

/**
 * Closes the connection with the port and client
 */
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

long ChatServer::getClientC(){
    return clientC;
}

long ChatServer::getClientKey(){
    return clientKey;
}

RSA* ChatServer::getRSA(){
    return coder;
}


