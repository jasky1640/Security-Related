/*
 * hw8.h
 *
 *  Created on: Nov 5, 2013
 *      Author: Michael Fischer
 */

#pragma once

// -----------------------------------------------------------
// 16-, 32-, and 64-bit unsigned integer types
// -----------------------------------------------------------
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long int u64;

// -----------------------------------------------------------
// Some useful macros
// -----------------------------------------------------------
// cat16 packs two 16-bit words into a 32-bit word
#define cat16(x1, x2) (((u32)(x1))<<16 | (x2))
// cat32 packs two 32-bit words into a 64-bit word
#define cat32(x1, x2) (((u64)(x1))<<32 | (x2))
// 16- and 32-bit masks
#define mask16 0xffffU
#define mask32 0xffffffffLU

// Function prototypes for 32-bit and 64-bit hash functions
u16 hash32(u32 x);
u16 hash64(u64 x);
