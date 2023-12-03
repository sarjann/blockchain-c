#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Transaction {
    int id_sender;
    int id_receiver;
    int amount;
} Transaction;

typedef struct Block {
    int block_number;
    int time_stamp;
    int nonce;
    char * hash;
    char * prev_hash;
    struct Transaction transactions[2];
} Block;

#endif /* STRUCTS_H */