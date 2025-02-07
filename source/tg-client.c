#include "../include/tg-client.h"

struct TgClient* initClient() {
    struct TgClient* tg_client = malloc(sizeof(struct TgClient));
    tg_client->client_id = td_create_client_id();

    if (tg_client->client_id == 0) {
        free(tg_client);
        return NULL;
    }
    
    return tg_client;
}

int closeClient(struct TgClient* tg_client) {
    free(tg_client);
    tg_client = NULL;

    return 0;
}
