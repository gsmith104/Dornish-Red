Greg Smith & Charles Milner
RSA Chat Server
CIT 595
04/19/12

Approach:
    Both the client and the server were written in C++. Greg was responsible for the server and RSA encrypter; Charlie was responsible for the client and RSA hacker. However, all code was written side by side. Each component had its on class. This allowed for clean main functions since most of the work was handled within classes.
    The protocol for communication goes as follows: when a client connects to the server, it sends its public encryption key (first the exponent, then the large pseudo-prime) to the server. The server responds in kind. These keys are randomly generated when both the server and client boot-up. After this exchange, both client and server spawn threads to allow for asynchronous message passing. One thread listens for input from user, encrypts each character, then sends it over the socket. The other thread listens to the socket, decrypts the message and then prints it out. So the listener knows how many characters will be sent in a message, the length of the message is sent before the encrypted characters. One unique feature, each time a message is sent, the handle for the sender is sent first.
    The RSA and RSA Hacker rely on Euler's totient. The algorithm for computing requires that the number used be of reasonable size.  No 128 bit numbers here!

Usage:
    There are 2 separate Makefiles in the project, in separate directories, 1 for the server and the other for the client.  The client takes 3 command line arguments with flags for each: -h serverIPAddress -p port# -n chatHandle.  The name of the executable is client.  The server takes 2 arguments with no flags.  The are the port# and the chatHandle.  The name of this executable is dornish.  We typically used port 12345.  The server handle is Ned: and the client's handle is Reek (which rhymes with sneak).  

The chatting can be ended gracefully.  When either party types "yield", it will end their own executable and send a message to the other.  

URL to GIT:
https://github.com/gsmith104/Dornish-Red

Test cases:
In the server Makefile, we included a test of the RSA class which can me run with make test.  It reads in a single character, generates an RSA object and then encrypts and decrypts the character, printing the result.  We test this with W.  

For the RsaHacker class, which can be run with make test in the client's makeFile.  It creates an RSA object.  An RsaHacker object is created which then breaks the key and prints out the original key and the cracked key.  Obviously these should be the same.  

We also tested general conversations on the same machine and on separate machines.
Here's output from general tests of the chat server/client on different machines.

From Greg's terminal (server) on MacBook Pro:

My public key is: 31
My private key is: 212671
The adversary's private key is: 85649
Ned:
Reek
what is dead may never die, but rises again, harder and stronger
Winter is coming
Ned:
Reek
the night is dark and full of terrors
I followed you into war, twice. Without doubts, without second thoughts. But I will not follow you now. The Robert I grew up with didn't tremble in the shadow of an unborn child.

Read more: http://www.tvfanatic.com/quotes/characters/eddard-ned-stark/#ixzz1sb647mW4Ned:
Ned:
two in row!
Ned:
Reek
yield
yield

From Charlie's terminal (client) on Moore 207 Machine:
./client -h 158.130.108.242 -p 12345 -n Reek
My public key: 49
Adversary Public Key: 31
My private key: 85649
Adversary private Key: 212671
Reek:
what is dead may never die, but rises again, harder and stronger
Reek:
Ned:
Winter is coming
Reek:
the night is dark and full of terrors
Reek:
Ned:
I followed you into war, twice. Without doubts, without second thoughts. But I will not follow you now. The Robert I grew up with didn't tremble in the shadow of an unborn child.
Ned:

Ned:
Read more: http://www.tvfanatic.com/quotes/characters/eddard-ned-stark/#ixzz1sb647mWtwo in row!
Reek:
yield
yield


We've also included a screenshot in the folder demonstrating conversations on the same machine.  




