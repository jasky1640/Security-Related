/*
 * analyze.cpp
 *
 *  Created on: Jan 23, 2010
 *      Author: mike
 */

#include <cfloat>
#include <cmath>
#include "analyze.hpp"
#include "exception.hpp"

using namespace std;

//-------------------------------------------------------------------
Analyze::Analyze() :
    key(AES_128::keyLength), iv(AES_128::blockSize),
    keyIndex1(0), keyIndex2(0) {
    for (unsigned k = 0; k < NUM_SHARES; k++)
        keyShare[k].resize(AES_128::keyLength);
}

//-------------------------------------------------------------------
void Analyze::run(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "usage: " << argv[0] << " freq key in out" << endl;
        return;
    }
    char* freqFile = argv[1];
    char* keyFile = argv[2];
    char* inFile = argv[3];
    char* outFile = argv[4];

    // Get the distribution
    dist.readFreq(freqFile);

    // Get the key shares
    readKeySharesFile(keyFile);

    // Get the iv and ciphertext
    readIVCiphertext(inFile);

    cout << "IV:\n";
    iv.writeHex(cout) << endl;

    // Guess the key
    guessKey();

    // Check that the key works
    cipher.setKey(key);
    cipher.decrypt(ciphertext, plaintext);

    // Print results
    cout << "Guessed key:\n";
    cout << "Indices " << keyIndex1 << " and " << keyIndex2 << endl;

    // Write the plaintext to the output file
    ofstream out(outFile);
    if (!out)
        throw CryptoException(
                "bruteforce: can't open plaintext file for writing");
    out << plaintext;
    out.close();
}

//-------------------------------------------------------------------
void Analyze::guessKey() {

    ByteArray possible; // possible plaintext
    ByteArray trialKey(key);
    double min_divergence = 256;

    cipher.setIV(iv);


    // Try each possible master key
    // Use cipher.setKey(trialKey) to set the AES decryption key
    // Use cipher.decrypt(ciphertext, possible) to get a
    // possible decryption
    // Keep the decryption with the smallest deviation found so far

    for(int key1 = 0; key1 < NUM_SHARES; key1++) {
        for(int key2 = key1 + 1; key2 < NUM_SHARES; key2++) {

            trialKey = keyShare[key1].operator^(keyShare[key2]);

            cipher.setKey(trialKey);
            cipher.decrypt(ciphertext, possible);

            double curr_divergence = divergence(possible);
            if(curr_divergence < min_divergence) {
                min_divergence = curr_divergence;
                key = trialKey;
                keyIndex1 = key1;
                keyIndex2 = key2;
            }
        }
    }
}

// ------------------------------------------------------------------
// Compute divergence of s from dist
double Analyze::divergence(const ByteArray& s) const {

    // Compute letter frequencies in s
    double deviation = 0.0; // Store the output of this function

    int s_freq[256]; // Create a array to store letter frequency of s
    for(int i = 0; i < 256; i++)
        s_freq[i] = 0;

    // Iterate through the byteArray s to fill the freq array
    for(int i = 0; i < s.size(); i++) {
        s_freq[s[i]] += 1;
    }

    double s_prob[256]; // normalize s array's frequency
    for(int i = 0; i < 256; i++)
        s_prob[i] = 0.0;

    for(int i = 0; i < 256; i++) {
        s_prob[i] = double(s_freq[i]) / s.size();
    }

    // Compute and return divergence
    // divergence = summation of b ( (p(b) - qm(b)) ^ 2)
    for(int i = 0; i < 256; i++) {
        double diff = dist.operator[](i) - s_prob[i];
        deviation += pow(diff, 2.0);
    }

    return deviation;
}

//-------------------------------------------------------------------
// Read key from file
void Analyze::readKeySharesFile(const char* keyFile) {
    ifstream in(keyFile);
    if (!in)
        throw CryptoException("analyze: can't open key file");
    for (unsigned k = 0; k < NUM_SHARES; k++)
        keyShare[k].readHex(in);
    in.close();
}

//-------------------------------------------------------------------
// Read IV and ciphertext from file
void Analyze::readIVCiphertext(const char* inFile) {
    ifstream in(inFile);
    if (!in)
        throw CryptoException(
                "analyze: can't open ciphertext file for reading");
    iv.readBytes(in);
    ciphertext.readAllBytes(in);
    in.close();
}
