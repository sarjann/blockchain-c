#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <string.h>

#include "hashing.h"
#include "structs.h"

void solve_block(struct Block *block, int target) {
    struct Block current_block = *block;
    char transactions_str[10000];
    char destination[10000] = "";

    char id_sender[50];
    char id_receiver[50];
    char amount[50];
    for (int i=0; i <= (sizeof(current_block.transactions)/sizeof(Transaction))-1; i++) {
        struct Transaction transaction = current_block.transactions[i];

        // String for individual transaction
        char transaction_str[100] = "";

        // Convert transaction vars to strings
        sprintf(&id_sender, "%d", transaction.id_sender);
        sprintf(&id_receiver, "%d", transaction.id_receiver);
        sprintf(&amount, "%d", transaction.amount);

        // Combine together for transaction str
        strcat(transaction_str, id_sender);
        strcat(transaction_str, id_receiver);
        strcat(transaction_str, amount);
        strcat(transaction_str, "/");

        // Append to transactions str to be hashed
        strcat(transactions_str, transaction_str);
    }

    char* transactions_hash = hash(transactions_str);
    // int zeroes = count_zeros(transactions_hash);
    // printf("%d\n", zeroes);

    int nonce;
    int time_stamp;
    char concat_for_hash[100];
    int solved;
    long long int counter = 0;
    int start_time = (unsigned)time(NULL);

    // Cracking hash
    while (1) {
        nonce = 0;
        time_stamp = (unsigned)time(NULL);
        solved = 0;
        while(nonce <= INT_MAX) {
            counter++;
            // strcpy(&concat_for_hash, time_stamp);
            char noncestr[10];
            sprintf(concat_for_hash, "%d", time_stamp);
            sprintf(&noncestr, "%d", nonce);
            
            strcat(concat_for_hash, noncestr);
            strcat(concat_for_hash, transactions_str);

            char* _hash = hash(concat_for_hash);

            int zeroes = count_zeros(_hash);

            if (zeroes >= target) {
                printf("\n%d\n", zeroes);
                printf("\nNonce is: %d\n", nonce);
                int total_time = (unsigned)time(NULL) - start_time;
                printf("\nTotal hashes: %lli\n", counter);
                if (total_time == 0) {
                    total_time = 1;
                }
                printf("Time: %d\n", total_time);
                int hashes_s = (counter/total_time)/1000;
                printf("%dkH/s\n\n", hashes_s);

                printf("%s \n\n",_hash);
                block->nonce = nonce;
                block->hash = _hash;
                block->time_stamp = time_stamp;
                solved=1;
                break;
            }

            free(_hash);

            nonce++;
        }
        
        if (solved) {
            break;
        }
    }
}
