#include "include/tg-client.h"

int main(int argc, char **argv) {
    struct TgClient *tg_client = initClient();

    if (tg_client == NULL) {
        printf("Unaviable to create client");
        return 0;
    }

    // authPhone(tg_client, "+79174338380");

    while (true) {
        const char* res = td_receive(10);
        if (res == NULL) continue;

        // json_object *td_receive = json_tokener_parse(res), *type_object;
        // json_object_object_get_ex(td_receive, "@type", &type_object);

        // printf("%s", json_object_to_json_string(type_object));
    }

    closeClient(tg_client);
    return 0;
}
