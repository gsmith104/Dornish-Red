/*
 * ChatClient.h
 *
 *  Created on: Apr 20, 2012
 *      Author: cmilner
 */

#ifndef CHATCLIENT_H_
#define CHATCLIENT_H_

#include "RSA.h"

class ChatClient {
	bool chatting;
	int server;
	RSA * encoder;
	char * handle;
	long serverKey[2];

public:
	ChatClient(char*,int,char*);
	bool sendPublicKey();
	bool receiveServerKey();
	bool sendMessage(char *);
	bool receiveMessage();
	bool isChatting();
        long * getServerKey();
        long getPrivateKey();
        long getPublicKey();
	char * getHandle();
	virtual ~ChatClient();
};

#endif /* CHATCLIENT_H_ */
