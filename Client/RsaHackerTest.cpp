/**
 *RSA Hacker tester
 *Charlie Milner
 *CIT 595
 *April 20th, 2012
 */


#include "RsaHacker.h"
#include "RSA.h"
#include <iostream>

using namespace std;

int main() {
    //generate a random public encryption key.
    RSA * rsa = new RSA();
    long n = rsa->getC();
    long e = rsa->getPublicKey();
    cout<<"n = "<<n<<endl;
    cout<<"e = "<<e<<endl;
    //hack the encryption key.
    RsaHacker * hack = new RsaHacker(e, n);
    //the private key, as determined by the encryption object.
    long expected_d = rsa->getPrivateKey();
    //the private key, as determined by the hacker object.
    long hack_d = hack->getAdversaryKey()[0];
    if (expected_d == hack_d) cout<<"test1 passed: ";
    else cout<<"TEST1 FAILED: ";
    cout<<"expected = "<<expected_d<<" actual = "<<hack_d<<endl;
    delete rsa;
    delete hack;
}
