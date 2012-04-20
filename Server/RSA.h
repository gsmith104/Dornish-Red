//
//  RSA.h
//  Dornish-Red
//
//  Created by Gregory Smith on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dornish_Red_RSA_h
#define Dornish_Red_RSA_h

class RSA{
private:
    long c, m;
    long publicKey, privateKey;
    long baseTwo[64];
    
public:
    RSA();
    ~RSA();
    long coprime(long x);
    long getPublicKey();
    long getC();
    long getM();
    long getPrivateKey();
    long gcd(long a, long b);
    int endecrypt(long message, long key, long c);
    long modInverse(long base, long m);
    long modulo(long a, long b, long c);
    long totient(long n);
    long generatePrime();
    bool isPrime(long n);
    int toBase2(long n);
};


#endif
