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
        
        if (strcmp(type, "\"updateAuthorizationState\"") == 0) {
            const char* state_type = getStringParam(getParam(response, "authorization_state"), "@type");
            printf("%s\n", state_type);
            if (strcmp(state_type, "\"authorizationStateWaitPhoneNumber\"") == 0) {
                authPhone(tg_client, "+79174338380");
                printf("phone sent\n");
            }
        }
    }

    closeClient(tg_client);
    return 0;
}
