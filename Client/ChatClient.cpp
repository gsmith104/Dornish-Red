/*
 * ChatClient.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: cmilner
 */

using namespace std;
#include "ChatClient.h"
#include "mysocket.h"
#include <iostream>

/**
 * Create a chat client who is connect to server specified by host and port.
 * The handle will be used as an identifier in communications. An RSA
 * encryption object will also be generated.
 */
ChatClient::ChatClient(char * host, int port, char * userHandle) {
    server = connectTo(host, port);
    encoder = new RSA();
    chatting = true;
    handle = userHandle;
}

/**
 * Send public key to server.
 */
bool ChatClient::sendPublicKey() {
	long e = encoder->getPublicKey();
	int bytesWritten = write(server, &e, sizeof(long));
	long n = encoder->getC();
	bytesWritten += write(server, &n, sizeof(long));
	if (bytesWritten < 2 * sizeof(long)) {
		return false;
	}
	return true;
}

/**
 * Receive servers public key.
 */
bool ChatClient::receiveServerKey() {
	int bytesRead = read(server, &serverKey[0], sizeof(long));
	bytesRead += read(server, &serverKey[1], sizeof(long));
	if (bytesRead < 2 * sizeof(long)) {
		return false;
	}
	return true;
}

/**
 * Send message to server.
 */
bool ChatClient::sendMessage(char * msg) {
	if (strcmp(msg, "yield") == 0) {
		chatting = false;
	}

	int length = strlen(msg);
	//send the length of the message first
	int bytesWritten = write(server, &length, sizeof(int));
	if (bytesWritten < sizeof(int)) {
	    return false;
	}

	//send the message, one character at a time
	for (int i = 0; i < length; i++) {
		char c = msg[i];
		long character = encoder->endecrypt(
				(long) msg[i], serverKey[0], serverKey[1]);
		bytesWritten = write(server, &character, sizeof(long));
		if (bytesWritten < sizeof(long)) {
			return false;
		}
	}
	return true;
}

/**
 * Receive a message from the server
 */
bool ChatClient::receiveMessage() {
	int length = 0;
        
        //read the length of the message
	int bytesRead = read(server, &length, sizeof(int));
	if (bytesRead < sizeof(int)) {
	    return false;
        }

	char msg[length+1];

	//read the message, one character at a time
	for (int i = 0; i < length; i++) {
		long character = 0;
		bytesRead = read(server, &character, sizeof(long));
		if (bytesRead < sizeof(long)) {
			return false;
		}
		character = encoder->endecrypt(
				character, encoder->getPrivateKey(), encoder->getC());
		msg[i] = character;
	}
	msg[length] = '\0';

	if (strcmp(msg, "yield") == 0) {
		chatting = false;
		sendMessage("yield");
	}
	cout<<msg<<endl;
	return true;
}

bool ChatClient::isChatting() {
	return chatting;
}

long ChatClient::getPrivateKey() {
	return encoder->getPrivateKey();
}

long * ChatClient::getServerKey() {
        return serverKey;
}

long ChatClient::getPublicKey() {
	return encoder->getPublicKey();
}

char * ChatClient::getHandle() {
	return handle;
}

ChatClient::~ChatClient() {
	close(server);
	delete encoder;
}

