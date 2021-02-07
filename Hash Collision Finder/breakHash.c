//
// Created by Jiaqi Yang on 11/10/2020.
//
#include "hw8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 40
#define NUMBER_OF_PAIR 20
#define MAX_PAIR_SIZE 20

int main(void)
{
    /* Step 1: Read the H-collisions file to get all the collision pairs */

    FILE *collisions_file = fopen("H-collisions", "r");
    char buffer[BUFFER_LEN];
    char collision_1[NUMBER_OF_PAIR][MAX_PAIR_SIZE]; // First item in the collision pair
    char collision_2[NUMBER_OF_PAIR][MAX_PAIR_SIZE]; // Second item in the collision pair
    // Initialize both String array
    for(int k = 0; k < NUMBER_OF_PAIR; k++) {
        for(int j = 0; j < MAX_PAIR_SIZE; j++) {
            collision_1[k][j] = '\0';
            collision_2[k][j] = '\0';
        }
    }

    // Read through H-collison file and store in String arrays
    int i = 0;
    while(fgets(buffer, BUFFER_LEN, collisions_file)) {
        for(int k = 0; k < 18; k++)
            collision_1[i][k] = buffer[k];
        for(int k = 0; k < 18; k++)
            collision_2[i][k] = buffer[k + 19];
        i++;
    }
    fclose(collisions_file);

    // Traverse all the pairs stored
    for(int j = 0; j < NUMBER_OF_PAIR; j++) {
        /* Step 2: Determine the collision type */

        // m1 is pair_1_first_half in string form, pair_1_first_half_val in u32 form (32 bit), h(m1) is pair_1_first_half_hash (16 bit)
        char pair_1_first_half[MAX_PAIR_SIZE / 2];
        for(int k = 0; k < MAX_PAIR_SIZE / 2; k++)
            pair_1_first_half[k] = '\0';
        strncpy(pair_1_first_half, collision_1[j] + 2, 8);
        u32 pair_1_first_half_val = (unsigned int) strtol(pair_1_first_half, NULL, 16);
        u16 pair_1_first_half_hash = hash32(pair_1_first_half_val);

        // m2 is pair_1_second_half in string form, pair_1_second_half_val in u32 form (32 bit), h(m2) is pair_1_second_half_hash (16 bit)
        char pair_1_second_half[MAX_PAIR_SIZE / 2];
        for(int k = 0; k < MAX_PAIR_SIZE / 2; k++)
            pair_1_second_half[k] = '\0';
        strncpy(pair_1_second_half, collision_1[j] + 10, 8);
        u32 pair_1_second_half_val = (unsigned int) strtol(pair_1_second_half, NULL, 16);
        u16 pair_1_second_half_hash = hash32(pair_1_second_half_val);

        // m1' is pair_2_first_half in string form, pair_2_first_half_val in u32 form (32 bit), h(m1') is pair_2_first_half_hash (16 bit)
        char pair_2_first_half[MAX_PAIR_SIZE / 2];
        for(int k = 0; k < MAX_PAIR_SIZE / 2; k++)
            pair_2_first_half[k] = '\0';
        strncpy(pair_2_first_half, collision_2[j] + 2, 8);
        u32 pair_2_first_half_val = (unsigned int) strtol(pair_2_first_half, NULL, 16);
        u16 pair_2_first_half_hash = hash32(pair_2_first_half_val);

        // m2' is pair_2_second_half in string form, pair_2_second_half_val (32 bit) in u32 form, h(m2') is pair_2_second_half_hash (16 bit)
        char pair_2_second_half[MAX_PAIR_SIZE / 2];
        for(int k = 0; k < MAX_PAIR_SIZE / 2; k++)
            pair_2_second_half[k] = '\0';
        strncpy(pair_2_second_half, collision_2[j] + 10, 8);
        u32 pair_2_second_half_val = (unsigned int) strtol(pair_2_second_half, NULL, 16);
        u16 pair_2_second_half_hash = hash32(pair_2_second_half_val);

        /* Step 3: Calculate the collision pair and output the result */

        // Case 1: h(m1) =/= h(m1') or h(m2) =/= h(m2'), then collision pair is ( h(m1)h(m2), h(m1')h(m2') )
        if(pair_1_first_half_hash != pair_2_first_half_hash || pair_1_second_half_hash != pair_2_second_half_hash) {
            u32 res_1 = cat16(pair_1_first_half_hash, pair_1_second_half_hash); // h(m1)h(m2)
            u32 res_2 = cat16(pair_2_first_half_hash, pair_2_second_half_hash); // h(m1')h(m2')
            printf("Original Colliding Pair: %s, %s; Case: 1; Colliding Pair: 0x%08x, 0x%08x\n", collision_1[j], collision_2[j], res_1, res_2);
        }

        // Case 2: h(m1) = h(m1') and h(m2) = h(m2'), then collision pair is (m1, m1') or (m2, m2‘), whichever is not equal
        else {
            // If m1 is not equal to m1', then collision pair is (m1, m1') at least
            if(strcmp(pair_1_first_half, pair_2_first_half) != 0) {
                printf("Original Colliding Pair: %s, %s; Case: 2; Colliding Pair: 0x%s, 0x%s\n", collision_1[j], collision_2[j], pair_1_first_half, pair_2_first_half);
            }
            // If m1 is equal to m1', then collision pair is (m2, m2')
            else {
                printf("Original Colliding Pair: %s, %s; Case: 2; Colliding Pair: 0x%s, 0x%s\n", collision_1[j], collision_2[j], pair_1_second_half, pair_2_second_half);
            }
        }
    }
}