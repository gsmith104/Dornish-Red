#ifndef MYSOCKET_H_
#define MYSOCKET_H_

// From http://www.linuxhowtos.org/C_C++/socket.htm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

// Given a host and a port number, connect as a client to that host/port
// Return a file descriptor number corresponding to the new socket
// The socket fd number (returned) can be used as follows:
// WRITE:
//    printf("Please enter the message: ");
//    bzero(buffer,256);
//    fgets(buffer,255,stdin);
//    n = write(sockfd,buffer,strlen(buffer));
// READ:
//    bzero(buffer,256);
//    n = read(sockfd,buffer,255);
// Don't forget to close(sockfd) when done
int connectTo(char* host, int portno) {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;    

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(host);
    
    if (server == NULL) {
        printf("No such host\n");
        exit(0);
    }    
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)  {
        printf("Error Connecting\n");
        exit(0);
    }
        
    return sockfd;
}

// Form a server listener that waits for new connections
// One listener can answer many connections
// This returns a file descriptor number that can be used
// to listen for "new connections," and perhaps spawn
// threads corresponding to those connections.
// To listen for a new connection, call (after calling this)
// listenFor(int fd), where fd == the fd returned by this function.
// Don't forget to close this fd when you're done.
int makeListener(int portno) {
     int sockfd;
     struct sockaddr_in serv_addr;
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) {
        printf("ERROR opening socket\n");
        exit(0);
     }
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) {
              printf("ERROR on binding\n");
              exit(0);
     }
              
     return sockfd;
}

// Given an fd number provided by makeListener,
// block until a new connection is received.
// Return the file descriptor number for that 
// new connection (don't forget to close it, as
// always!).  This returned fd number can be
// read and written to in the usual way.
int listenFor(int sockfd) {
    int clilen, newsockfd;
    struct sockaddr_in cli_addr;
    
	listen(sockfd,5);
	
     clilen = sizeof(cli_addr);
     
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 (socklen_t*)&clilen);
     if (newsockfd < 0) 
          printf("ERROR on accept\n");	
          
     return newsockfd;
}
#endif
