//
//  RSA.cpp
//  Dornish-Red
//
//  Created by Gregory Smith on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "RSA.h"
#include <math.h>
using namespace std;


RSA::RSA(){
    long a = generatePrime();
    long b = generatePrime();
    c = a * b;
    m = (a-1)*(b-1);
    publicKey = coprime(m);
    privateKey = modInverse(publicKey, m);
}

RSA::~RSA(){
    
}

/**
 * Finds a coprime number to the given parameter x
 */
long RSA::coprime(long x){
    long random;
    while (true){
        random = abs(rand()% 1000);
        if (gcd(random, x) == 1){
            return random;
        }
    }
}

long RSA::getC(){
    return c;
}

long RSA::getPublicKey(){
    return publicKey;
}

/**
 * Calculates the greatest common denominator of a and b
 */
long RSA::gcd(long a, long b){
    long temp;
    while (b>0){
        temp = a;
        a = b;
        b = temp%b;
    }
    
    return a;
    
}

/**
 * Generates a prime number up to 1000
 */
long RSA::generatePrime(){
    long possiblyPrime;
    bool isPrime = true;
    while (true) {
        possiblyPrime = abs(rand()%1000);
        for (int i = 2; i<possiblyPrime; i++){
            if (possiblyPrime % i == 0){
                isPrime = false;
                break;
            }
            else {
                isPrime = true;
            }
        }
        if (isPrime){
            return possiblyPrime;
        }
    }
}

/**
 * Reads in a block of longs and encrypts the number with the public key, or decrypts with the private key
 */
long RSA::endecrypt(long message, long key, long c){
    long conversion = modulo(message, key, c);
    return conversion;
    
}

/**
 * Calculates the modular inverse of a number.  Used to generate the private key.
 */
long RSA::modInverse(long base, long m){
    long inverse = modulo(base, totient(m)-1, m);
    return inverse;
    
}

/**
 * Calculates modulo of the exponent (in a really crappy manner)
 */
long RSA::modulo(long a, long b, long c){
    long temp = pow(a,b);
    return temp % c;
}

/**
 * Calculates Euler's totient
 */
long RSA::totient(long n){
    long totient = n;
    long limit = n/2;
//    cout<<"This is the limit: "<<limit<<endl;
    for (long i = 2; i<limit; i++){
        if (isPrime(i)){
            if (n % i == 0){
                totient *= (1 - 1.0/i);
//                cout<<totient<<endl;
            }
        }
    }
    return totient;
}

/**
 * Checks if a number is prime or not
 */
bool RSA::isPrime(long n){
    long limit = floor(sqrt(n));
    if (n == 2){
        return true;
    }
    if (n %2 == 0){
        return false;
    }
    for (long i = 3; i<=limit; i+=2){
        if (n%i == 0){
            return false;
        }
    }
    return true;
}









