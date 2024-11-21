#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/rand.h>
#include <secp256k1.h>
#include <sha3/sph_keccak.h>

void pubkey_wif(uint8_t* privbytes, char* priv, char* pub) {
    secp256k1_pubkey pubkey;
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
    secp256k1_ec_pubkey_create(ctx, &pubkey, (const unsigned char*)privbytes);

    uint8_t pubkey_serialized[65], pubkey_trimmed[64];
    size_t pubkeylen = sizeof(pubkey_serialized);
    secp256k1_ec_pubkey_serialize(ctx, pubkey_serialized, &pubkeylen, &pubkey, SECP256K1_EC_UNCOMPRESSED);
    memcpy(pubkey_trimmed, pubkey_serialized+1, 64);

    uint8_t pubkey_hash[32];

    sph_keccak256_context ctx_keccak;   
    sph_keccak256_init(&ctx_keccak);
    sph_keccak256(&ctx_keccak, pubkey_trimmed, 64);
    sph_keccak256_close(&ctx_keccak, pubkey_hash);

    for (int i=0; i<32; i++)
        sprintf(priv+(i*2), "%02hhx", privbytes[i]);
    for (int i=0; i<20; i++)
        sprintf(pub+(i*2), "%02hhx", pubkey_hash[i+12]);
}

void rand_pair(char *priv, char *pub) {
    uint8_t privbytes[32];
    RAND_bytes(privbytes, 32);
    pubkey_wif(privbytes, priv, pub);
}

int is_hex(char *pub) {
    int count = 0;
    for (int i=0; i<40; i++) {
        if (pub[i] == '0')
            ++count;
        else
            break;
    }
    return count;
}

int best;
pthread_t tid[8];
pthread_mutex_t lock;

void set_best(int b) {
    best = b;
}

int get_best() {
    return best;
}

void worker()
{
    char priv[64], pub[40];
    while (1) {
        rand_pair(priv, pub);
        int attempt = is_hex(pub);
        if (attempt > get_best()) {
            printf("%s %s (%d leading zeroes)\n", priv, pub, attempt);
            set_best(attempt);
        }
    }
}

int main()
{
    int i=0;
    int err;
    set_best(0);
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
    }
    while(i < 8) {
        err = pthread_create(&(tid[i]), NULL, &worker, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
    i=0;
    while(i < 8) {
        pthread_join(tid[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&lock);

    return 1;
}
