/*
 * RsaHacker.cpp
 *
 *  Created on: Apr 6, 2012
 *      Author: cmilner 
 */

#include <cmath>
#include "RsaHacker.h"
#include "RSA.h"

RsaHacker::RsaHacker(long e, long n) {
    adversaryKey[1] = n;
    adversaryKey[0] = hackPrivateKey(e, n);
}

RsaHacker::~RsaHacker() {
}

long* RsaHacker::getAdversaryKey() {
    return adversaryKey;
}

long RsaHacker::hackPrivateKey(long e, long n) {

	//find the prime factors of n
	long primeFactors[2];
	if (n % 2 == 0) {
		primeFactors[0] = 2;
		primeFactors[1] = n / 2;
	} else {
		long limit = floor(sqrt(n));
		for (long i = 3; i <= limit; i+=2) {
			if (n % i == 0) {
				primeFactors[0] = i;
				primeFactors[1] = n / i;
			}
		}
	}

	//find the mod used for computing the decryption key
	long m = (primeFactors[0] - 1) * (primeFactors[1] - 1);

	//find the totient of m using euler's product formula
	long totient =  m;
	long limit = m / 2;
	for (long i = 2; i < limit; i++) {
		if (isPrime(i)) {
			if (m % i == 0) {
				totient *= (1 - 1.0 / i);
			}
		}
	}

	//find the decryption key using the totient
	int d = modExp(e, totient - 1, m);

	return d;
}

bool RsaHacker::isPrime(long n) {
	long limit = floor(sqrt(n));
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (int i = 3; i <= limit; i+=2) {
		if (n % i == 0) return false;
	}
	return true;
}

long RsaHacker::modExp(long base, long exp, long mod) {
    int baseTwo[64]; //64 is the max number of bits in a long

    int length = toBase2(exp, baseTwo) + 1;
    
    //get mod values of a to the power of 2
    long modValues[length];
    long tempBase = base % mod;
    modValues[0] = tempBase;
    for (int i = 1; i < length; i++) {
        modValues[i] = (tempBase * tempBase) % mod;
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
                total = (total * modValues[i]) % mod;
            }
        }
        return total;    
    }
}

/**
 *Convert a long into binary (with the ones place in baseTwo[0], etc)
 *Returns the index of the final value.
 */
int RsaHacker::toBase2(long n, int * baseTwo){
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
