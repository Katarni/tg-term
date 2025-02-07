#include "../include/tg-client.h"

struct TgClient* initClient() {
    struct TgClient* tg_client = malloc(sizeof(struct TgClient));
    tg_client->id = td_create_client_id();

    if (tg_client->id == 0) {
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

void sendReq(struct TgClient* client, const char* type, int argc, const char** argv_keys, json_object** argv_vals) {
    json_object *req = json_object_new_object();
    json_object_object_add(req, "@type", json_object_new_string(type));
    for (int i = 0; i < argc; ++i) {
        json_object_object_add(req, argv_keys[i], argv_vals[i]);
    }
    td_send(client->id, json_object_to_json_string(req));
}
