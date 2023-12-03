#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <string.h>

#include "main.h"
#include "hashing.h"
#include "block.h"
#include "structs.h"

#define MAXBUFLEN 1000000

int target = 4;

void write_first_block(){
    Transaction my_trans_0;
    my_trans_0.id_sender=1;
    my_trans_0.id_receiver=2;
    my_trans_0.amount=4;

    Transaction my_trans_1;
    my_trans_1.id_sender=3;
    my_trans_1.id_receiver=6;
    my_trans_1.amount=12;

    Block my_block;
    my_block.prev_hash = "0000000000000000000000000000000000000000000000000000000000000000";
    my_block.transactions[0] = my_trans_0;
    my_block.transactions[1] = my_trans_1;

    my_block.block_number = 0;
    my_block.time_stamp = (unsigned)time(NULL);

    solve_block(&my_block, target);

    // printf("my_block.hash");
    // printf(my_block.hash);
    // printf("my_block.hash");

    write_file(&my_block);
}
int main(int argc, char **argv) {
    read_datafile();
    // write_first_block();
    
    solve_block(&my_block, target);
    // printf("\n\nval: %d\n\n", val);
    // printf("%d", my_block.nonce);
    printf(my_block.hash);
    return 0;
}

void read_datafile() {
    char source[MAXBUFLEN + 1];
    FILE *fptr = fopen("data/block.dat", "r");
    
    if(fptr == NULL) {
      printf("Error!");   
      exit(1);             
      }
    
    size_t newLen = fread(source, sizeof(char), MAXBUFLEN, fptr);
    if ( ferror( fptr ) != 0 ) {
        fputs("Error reading file", stderr);
    } else {
        source[newLen++] = '\0'; /* Just to be safe. */
    }

    fclose(fptr);
    printf(source);
    }

void write_file(struct Block *block) {
    struct Block current_block = *block;

    FILE *fptr;
    fptr = fopen("data/block.dat", "a");

    if(fptr == NULL) {
      printf("Error!");   
      exit(1);             
      }

    fprintf(fptr, "block_number:%d\n", current_block.block_number);
    fprintf(fptr, "time_stamp:%d\n", current_block.time_stamp);
    fprintf(fptr, "nonce:%d\n", current_block.nonce);
    fprintf(fptr, "hash:%s\n", current_block.hash);
    fprintf(fptr, "prev_hash:%s\n", current_block.prev_hash);

    // Transactions str
    int length_transactions = sizeof(current_block.transactions)/sizeof(Transaction);
    printf("\n!!!!!%d!!!!!\n", length_transactions);
    for (int i=0; i<length_transactions;i++) {
        printf("\n------------%d-----------\n", i);
        char temp_string[100];
        char transaction_string[10000] = "";
        struct Transaction transaction = current_block.transactions[i];
        
        if (!transaction.id_sender) {
            break;
        }
        sprintf(&temp_string, "transaction_%d\nid_sender:%d,id_receiver:%d,amount:%d\n",
                i, transaction.id_sender, transaction.id_receiver, transaction.amount);
        strcat(transaction_string, temp_string);
        fprintf(fptr, temp_string);
    }
    //
    fprintf(fptr, "\n");
    fclose(fptr);
}
