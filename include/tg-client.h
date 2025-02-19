#ifndef _TG_CLIENT_H
#define _TG_CLIENT_H

#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <td/telegram/td_json_client.h>
#include <openssl/rand.h>


struct TgClient {
    int id, logged_in;
    long long api_id;
    char *database_key, *api_hash;
};


struct TgClient* initClient();
int closeClient(struct TgClient* tg_client);

void sendReq(struct TgClient* client, const char* type, int argc, const char** argv_keys, json_object** argv_vals);

void authPhone(struct TgClient* client, const char* phone);

void getTDatabaseEncryptCode(struct TgClient *client);

int readApiKeys(struct TgClient *client);

#endif /* _TG_CLIENT_H */
