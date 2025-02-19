#include "../include/tg-client.h"

struct TgClient* initClient() {
    struct TgClient* tg_client = malloc(sizeof(struct TgClient));
    tg_client->id = td_create_client_id();

    if (tg_client->id == 0) {
        free(tg_client);
        return NULL;
    }
    tg_client->logged_in = 0;

    if (readApiKeys(tg_client)) {
        printf("cant read api kays");
        free(tg_client);
        return NULL;
    }

    const char** argv_keys = malloc(sizeof(char*));
    argv_keys[0] = "parameters";

    json_object** argv_vals = malloc(sizeof(json_object*));
    argv_vals[0] = json_object_new_object();
    json_object_object_add(argv_vals[0], "database_directory", json_object_new_string("tdlib_db"));
    json_object_object_add(argv_vals[0], "use_message_database", json_object_new_boolean(1));
    json_object_object_add(argv_vals[0], "use_secret_chats", json_object_new_boolean(1));
    json_object_object_add(argv_vals[0], "api_id", json_object_new_int(23702440));
    json_object_object_add(argv_vals[0], "api_hash", json_object_new_string("898ac9c8eccbe67a33c0445693bfd505"));
    json_object_object_add(argv_vals[0], "system_language_code", json_object_new_string("en"));
    json_object_object_add(argv_vals[0], "device_model", json_object_new_string("Desktop"));
    json_object_object_add(argv_vals[0], "application_version", json_object_new_string("1.0"));
    json_object_object_add(argv_vals[0], "enable_storage_optimizer", json_object_new_boolean(1));
    json_object_object_add(argv_vals[0], "enable_storage_optimizer", json_object_new_boolean(1));

    sendReq(tg_client, "setTdlibParameters", 1, argv_keys, argv_vals);

    free(argv_keys);

    free(argv_vals[0]);
    free(argv_vals);

    argv_keys = malloc(sizeof(char*));
    argv_keys[0] = "encryption_key";

    argv_vals = malloc(sizeof(json_object*));
    argv_vals[0] = json_object_new_string(getTDatabaseEncryptCode());

    sendReq(tg_client, "checkDatabaseEncryptionKey", 1, argv_keys, argv_vals);
    
    return tg_client;
}

int closeClient(struct TgClient* tg_client) {
    free(tg_client->database_key);
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

void authPhone(struct TgClient* client, const char* phone) {
    const char** argv_keys = malloc(2 * sizeof(char*));
    argv_keys[0] = "phone_number";
    argv_keys[1] = "@extra";
    json_object** argv_vals = malloc(2 * sizeof(json_object*));
    argv_vals[0] = json_object_new_string(phone);
    argv_vals[1] = json_object_new_string("login_phone");

    sendReq(client, "setAuthenticationPhoneNumber", 1, argv_keys, argv_vals);

    free(argv_keys);

    for (int i = 0; i < 2; ++i) {
        free(argv_vals[i]);
    }
    free(argv_vals);
} 

char* getTDatabaseEncryptCode() {
    unsigned char* unsigned_tmp_key = malloc(32);
    RAND_bytes(unsigned_tmp_key, 32);

    char* key = malloc(65);
    for (size_t i = 0; i < 32; i++) {
        sprintf(key + (i * 2), "%02x", unsigned_tmp_key[i]);
    }

    key[64] = '\0';

    free(unsigned_tmp_key);

    return key;
}

int readApiKeys(struct TgClient *client) {
    FILE *keys_storage = fopen("../td-api-key.env", "r");
    if (keys_storage == NULL) {
        fclose(keys_storage);
        return -1;
    }
    
    char *line = NULL;
    int line_len = 0; 

    int read_len = getline(&line, &line_len, keys_storage);

    if (read_len < 1) {
        fclose(keys_storage);
        return -1;
    }



    fclose(keys_storage);
    return 0;
}
