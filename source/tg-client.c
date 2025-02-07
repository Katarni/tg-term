#include "../include/tg-client.h"

struct TgClient* initClient() {
    struct TgClient* tg_client = malloc(sizeof(struct TgClient));
    tg_client->client = td_json_client_create();

    if (tg_client->client == NULL) {
        free(tg_client);
        return NULL;
    }
    
    return tg_client;
}

int closeClient(struct TgClient* tg_client) {
    td_json_client_destroy(tg_client->client);
    free(tg_client);
    tg_client = NULL;

    return 0;
}
