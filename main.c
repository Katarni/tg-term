#include "include/tg-client.h"

int main(int argc, char **argv) {
    struct TgClient *tg_client = initClient();

    if (tg_client == NULL) {
        printf("Unaviable to create client");
        return 0;
    }
    
    while (true) {
        const char* res = td_receive(10);
        if (res == NULL) continue;

        struct json_object *response = json_tokener_parse(res);
        const char* type = getStringParam(response, "@type");
        // printf("%s\n", type);
        
        if (strcmp(type, "\"updateAuthorizationState\"") == 0) {
            printf("%s\n", getStringParam(response, "authorization_state"));
        }
    }

    closeClient(tg_client);
    return 0;
}
