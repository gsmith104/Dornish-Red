/*
 * RsaHacker.h
 *
 *  Created on: Apr 6, 2012
 *      Author: cmilner
 */

#ifndef RSAHACKER_H_
#define RSAHACKER_H_

class RsaHacker {
private:
	long adversaryKey[2];

public:
	RsaHacker(long,long);
        long* getAdversaryKey();
	long hackPrivateKey(long,long);
        long modExp(long,long,long);
        int toBase2(long,int*);
	bool isPrime(long);
	virtual ~RsaHacker();
};

#endif /* RSAHACKER_H_ */
