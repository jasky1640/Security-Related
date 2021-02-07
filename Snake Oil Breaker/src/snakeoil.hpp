/*
 * snakeoil.hpp
 *
 *  Created on: Jan 21, 2012
 *      Author: Michael Fischer
 *      Derived from code by Ewa Syta
 */

#pragma once
#include "aes.hpp"

/* SnakeOil class implements Happy Hacker's SnakeOil cryptosystem based on AES-128.
 * It supports three subcommands:
 *
 * SnakeOil -g keyshares generates and stores a random key share file.
 *
 * SnakeOil -e keyshares idx1 idx2 in out
 *      encrypts "in" using key shares idx1 and idx2 to generate an AES key.
 *      It writes the ciphertext to "out".
 *
 * SnakeOil -d keyshares idx1 idx2 in out
 *      decrypts "in" using key shares idx1 and idx2 to generate an AES key.
 *      It writes the plaintext to "out".
 *
 *  File formats:
 *  The key shares file consists of 100 * 16 whitespace-delimited hex bytes.
 *      These are interpreted as 100 key shares of 16 bytes each.
 *  The plaintext and ciphertext files are treated as raw bytes.
 *  The first 16 bytes of the ciphertext are taken as the initialization
 *      vector for AES-128 used in CBC mode.
 *  The remaining bytes are the ciphertext blocks.
 */

#define NUM_SHARES 100

class SnakeOil {
public:
    static unsigned int const defaultSeed = 1234;
private:
    AES_128 cipher;
    Prng rng;
    ByteArray keyShare[NUM_SHARES];
    ByteArray key;
    ByteArray iv;
    unsigned keyIndex1, keyIndex2;
    ByteArray plaintext;
    ByteArray ciphertext;

public:
    SnakeOil() =delete;
    SnakeOil(unsigned int seed = defaultSeed);
    void run(int argc, char* argv[]);

private:
    void readKeySharesFile(const char* keyFile);
    void readPlaintext(const char* inFile);
    void readIVCiphertext(const char* inFile);

    void doKeyGen(const char* keyFile);
    void doEncrypt(const char* inFile, const char* outFile);
    void doDecrypt(const char* inFile, const char* outFile);
};
