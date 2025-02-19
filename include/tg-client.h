#ifndef _TG_CLIENT_H
#define _TG_CLIENT_H

#include <json-c/json.h>
#include <stdio.h>
#include <td/telegram/td_json_client.h>
#include <openssl/rand.h>


struct TgClient {
    int id, logged_in, api_id;
    char* database_key, api_hash;
};


struct TgClient* initClient();
int closeClient(struct TgClient* tg_client);

void sendReq(struct TgClient* client, const char* type, int argc, const char** argv_keys, json_object** argv_vals);

void authPhone(struct TgClient* client, const char* phone);

char* getTDatabaseEncryptCode();

int readApiKeys(struct TgClient *client);

#endif /* _TG_CLIENT_H */
