/*
 * aes.hpp
 *
 *  Created on: Jan 19, 2012
 *      Author: Michael Fischer
 *      Derived from code by Ewa Syta
 *      Updated Oct 6, 2020 by Ning Luo
 */

#pragma once
#include <botan/symkey.h>
#include <botan/pipe.h>
#include <botan/cipher_mode.h>
#include <botan/filters.h>
#include "bytearray.hpp"
using namespace std;

#include "bytearray.hpp"
#include "prng.hpp"

/* Wrapper class for Botan's implementation of AES-128/CBC.
 * It encrypts and decrypts raw ByteArray data.
 * Must set the key and initialization vector before calling encrypt
 * or decrypt.
 */

class AES_128 {
public:
    static const unsigned int keyLength;
    static const unsigned int blockSize;
private:
    ByteArray key;
    ByteArray iv;

public:
    AES_128() =default;
    void encrypt( const ByteArray& plaintext, ByteArray& ciphertext );
    void decrypt( const ByteArray& ciphertext, ByteArray& plaintext );
    void zeroPad(ByteArray& plaintext);
    void zeroUnPad(ByteArray& plaintext);

    void setKey( const ByteArray& keyx ) { AES_128::key = keyx; }

    void setIV( const ByteArray& iv ) { AES_128::iv = iv; }
};
