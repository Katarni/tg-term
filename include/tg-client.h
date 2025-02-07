#ifndef _TG_CLIENT_H
#define _TG_CLIENT_H

#include <json-c/json.h>
#include <stdio.h>
#include <td/telegram/td_json_client.h>


struct TgClient {
    int id;
};


struct TgClient* initClient();
int closeClient(struct TgClient* tg_client);

void sendReq(struct TgClient* client, const char* type, int argc, const char** argv_keys, json_object** argv_vals);

#endif /* _TG_CLIENT_H */
