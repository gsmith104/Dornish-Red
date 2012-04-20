//
//  RSA.cpp
//  Dornish-Red
//
//  Created by Gregory Smith on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "RSA.h"
#include <math.h>
using namespace std;


RSA::RSA(){
    srand(time(0));
    long a = generatePrime();
    long b = generatePrime();
    while (a == b) b = generatePrime();
    c = a * b;
    m = (a-1)*(b-1);
    publicKey = coprime(m);
    privateKey = modInverse(publicKey, m);
}

RSA::~RSA(){
    
}

long RSA::getM(){
    return m;
}

/**
 * Finds a coprime number to the given parameter x
 */
long RSA::coprime(long x){
    long random;
    while (true){
        random = abs(rand() % 50);
        if (gcd(random, x) == 1 && random > 5){
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
        if (possiblyPrime < 100) continue;
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
int RSA::endecrypt(long message, long key, long c){
    int conversion = modulo(message, key, c);
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
 * Calculates modulo of the exponent
 */
long RSA::modulo(long a, long b, long c){
    
    int length = toBase2(b) + 1;
    
    //get mod values of a to the power of 2
    long modValues[length];
    long tempBase = a % c;
    modValues[0] = tempBase;
    for (int i = 1; i < length; i++) {
        modValues[i] = (tempBase * tempBase) % c;
        tempBase = modValues[i];
    }
    //multiply modValues together that are relevant
    long total = 1;
    if (length == 0){
        return 1;
    }
    else {
        for (int i = 0; i < length; i++){
            if(baseTwo[i] == 1){
                total = (total * modValues[i]) % c;
            }
        }
        return total;    
    }

}

/**
 * Calculates Euler's totient
 */
long RSA::totient(long n){
    long totient = n;
    long limit = n/2;
    for (long i = 2; i<limit; i++){
        if (isPrime(i)){
            if (n % i == 0){
                totient *= (1 - 1.0/i);
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

long RSA::getPrivateKey(){
    return privateKey;
}

/**
 * Generate array of 0's and 1's representing the binary value of n, reversed.
 */
int RSA::toBase2(long n){
    int i = 0;
    while (n/2>0) {
        baseTwo[i] = n%2;
        i++;
        n = n/2;
        if (n == 1){
            baseTwo[i] = 1;
        }
    }
    return i;
}











