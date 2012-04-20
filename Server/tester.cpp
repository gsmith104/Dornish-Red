//
//  main.cpp
//  RSATester
//
//  Created by Gregory Smith on 4/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "RSA.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main (int argc, const char * argv[])
{

    RSA* test1 = new RSA();
    char message[] = "W";
    
    cout<<"The original message is: "<<message<<endl;
    int encrypted = test1->endecrypt(message[0], test1->getPublicKey(), test1->getC());
    int decrypted = test1->endecrypt(encrypted, test1->getPrivateKey(), test1->getC());
    
//    long tester = test1->modulo(87, 5, 51757);
//    long mtotient = test1->totient(test1->getM());
//    cout<<"Tester is "<<tester<<endl;
//    cout<<"Totien of M is: "<<mtotient<<endl;
    
    cout<<"Public key is: "<<test1->getPublicKey()<<endl;
    cout<<"Private key is: "<<test1->getPrivateKey()<<endl;
    cout<<"C is: "<<test1->getC()<<endl;
    cout<<"M is: "<<test1->getM()<<endl;
    
    printf("%d\n",encrypted);
    printf("%d\n",decrypted);
    printf("The decrypted message is: %c\n",(int)decrypted);

    return 0;
}

