#ifndef _TG_CLIENT_H
#define _TG_CLIENT_H

#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <td/telegram/td_json_client.h>
#include <openssl/rand.h>
#include <string.h>
#include <pthread.h>


struct TgClient {
    int id, logged_in, log_lvl;
    long long api_id;
    const char *api_hash, *log_file;
    char *database_key;
};


struct TgClient* initClient();
int closeClient(struct TgClient* tg_client);

void sendReq(struct TgClient* client, const char* type, int argc, const char** argv_keys, json_object** argv_vals);

void authPhone(struct TgClient* client, const char* phone);

void getTDatabaseEncryptCode(struct TgClient *client);

int readClientParams(struct TgClient *client);

void setLogsParams(struct TgClient* client);

const char* getStringParam(struct json_object *object, const char *key);
int getIntParam(struct json_object *object, const char* key);
struct json_object* getParam(struct json_object *object, const char *key);


#endif /* _TG_CLIENT_H */
