//
//  Server.h
//  Dornish-Red
//
//  Created by Gregory Smith on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dornish_Red_Server_h
#define Dornish_Red_Server_h
#include "mysocket.h"
#include "RSA.h"

class ChatServer{
private:
    int portNum;
    int srvfd;
    bool stillChatting;
    int connfd;
    long clientKey;
    long clientC;
    RSA *coder;
    char* chatHandle;
public:
    ChatServer();
    ChatServer(int port, char* chatName);
    ~ChatServer();
    void createConnection(int portNum);
    bool sendPublicKey();
    bool sendC();
    bool recievePublicKey();
    bool recieveC();
    bool sendMessage(char * message);
    bool readMessage();
    bool closeConnection();
    bool getStillChatting();
    char* getChatHandle();
};



#endif
