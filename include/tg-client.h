#ifndef _TG_CLIENT_H
#define _TG_CLIENT_H

#include <json-c/json.h>
#include <stdio.h>
#include <td/telegram/td_json_client.h>


struct TgClient {
    void* client;
};


struct TgClient* initClient();

int closeClient(struct TgClient* tg_client);

#endif /* _TG_CLIENT_H */
