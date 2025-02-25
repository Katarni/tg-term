#include "../include/tg-client.h"

struct TgClient* initClient() {
    struct TgClient* client = malloc(sizeof(struct TgClient));
    client->id = td_create_client_id();

    if (client->id == 0) {
        free(client);
        return NULL;
    }
    client->logged_in = 0;

    setLogsParams(client, "../logs.dat");

    if (readApiKeys(client)) {
        printf("cant read api kays\n");
        free(client);
        return NULL;
    }

    getTDatabaseEncryptCode(client);

    const char** argv_keys = malloc(14*sizeof(char*));
    argv_keys[0] = "use_test_dc";
    argv_keys[1] = "database_directory";
    argv_keys[2] = "files_directory";
    argv_keys[3] = "database_encryption_key";
    argv_keys[4] = "use_file_database";
    argv_keys[5] = "use_chat_info_database";
    argv_keys[6] = "use_message_database";
    argv_keys[7] = "use_secret_chats";
    argv_keys[8] = "api_id";
    argv_keys[9] = "api_hash";
    argv_keys[10] = "system_language_code";
    argv_keys[11] = "device_model";
    argv_keys[12] = "system_version";
    argv_keys[13] = "application_version";

    json_object** argv_vals = malloc(14*sizeof(json_object*));
    argv_vals[0] = json_object_new_boolean(0);
    argv_vals[1] = json_object_new_string("tdlib_db");
    argv_vals[2] = json_object_new_string("tdlib_files");
    argv_vals[3] = json_object_new_string(client->database_key);
    argv_vals[4] = json_object_new_boolean(1);
    argv_vals[5] = json_object_new_boolean(1);
    argv_vals[6] = json_object_new_boolean(1);
    argv_vals[7] = json_object_new_boolean(1);
    argv_vals[8] = json_object_new_int(client->api_id);
    argv_vals[9] = json_object_new_string(client->api_hash);
    argv_vals[10] = json_object_new_string("en");
    argv_vals[11] = json_object_new_string("Desctop");
    argv_vals[12] = json_object_new_string("MacOs 15.2");
    argv_vals[13] = json_object_new_string("1.0.0");

    sendReq(client, "setTdlibParameters", 14, argv_keys, argv_vals);

    free(argv_keys);

    for (int i = 0; i < 14; ++i) {
        free(argv_vals[i]);
    }
    free(argv_vals);
    
    return client;
}

int closeClient(struct TgClient* client) {
    free(client->(api_hash);
    free(client->database_key);
    free(client);
    client = NULL;

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

    sendReq(client, "setAuthenticationPhoneNumber", 2, argv_keys, argv_vals);

    free(argv_keys);

    for (int i = 0; i < 2; ++i) {
        free(argv_vals[i]);
    }
    free(argv_vals);
} 

void getTDatabaseEncryptCode(struct TgClient *client) {
    FILE *encrypt_key = fopen("../encrypt-key.env", "r");
    if (encrypt_key == NULL) {
        unsigned char* unsigned_tmp_key = malloc(32);
        RAND_bytes(unsigned_tmp_key, 32);
    
        client->database_key = malloc(65);
        for (size_t i = 0; i < 32; i++) {
            sprintf(client->database_key + (i * 2), "%02x", unsigned_tmp_key[i]);
        }
    
        client->database_key[64] = '\0';
        free(unsigned_tmp_key);

        encrypt_key = fopen("../encrypt-key.env", "w");
        fputs(client->database_key, encrypt_key);
        fclose(encrypt_key);

        return;
    }

    size_t line_len;
    int read_len = getline(&client->database_key, &line_len, encrypt_key);
    fclose(encrypt_key);
}

int readApiKeys(struct TgClient *client) {
    FILE *keys_storage = fopen("../td-api-key.env", "r");
    if (keys_storage == NULL) {
        fclose(keys_storage);
        return -1;
    }
    
    char *line = NULL;
    size_t line_len = 0; 

    int read_len = getline(&line, &line_len, keys_storage);

    if (read_len < 1) {
        fclose(keys_storage);
        return -1;
    }

    client->api_id = atoll(line);    

    free(line);

    if (client->api_id == 0) {
        fclose(keys_storage);
        return -1;
    }

    line = NULL, line_len = 0;

    read_len = getline(&line, &line_len, keys_storage);

    if (read_len < 1) {
        fclose(keys_storage);
        return -1;
    }

    int hash_len = 0;
    while ('0' <= line[hash_len] && line[hash_len] <= '9' ||
             'a' <= line[hash_len] && line[hash_len] <= 'z') ++hash_len;

    client->api_hash = malloc(hash_len + 1);
    memcpy(client->api_hash, line, hash_len);
    client->api_hash[hash_len] = '\0';
    
    free(line);
    fclose(keys_storage);

    return 0;
}

void setLogsParams(struct TgClient* client, const char* log_file) {
    FILE* file = fopen(log_file, "w");
    fclose(file);

    const char** argv_keys = malloc(sizeof(char*));
    argv_keys[0] = "new_verbosity_level";

    json_object** argv_vals = malloc(sizeof(json_object*));
    argv_vals[0] = json_object_new_int(3);

    sendReq(client, "setLogVerbosityLevel", 1, argv_keys, argv_vals);

    free(argv_vals[0]);

    argv_keys[0] = "log_stream";
    argv_vals[0] = json_object_new_object();
    json_object_object_add(argv_vals[0], "@type", json_object_new_string("logStreamFile"));
    json_object_object_add(argv_vals[0], "path", json_object_new_string(log_file));
    json_object_object_add(argv_vals[0], "max_file_size", json_object_new_int(10485760));
    json_object_object_add(argv_vals[0], "redirect_stderr", json_object_new_boolean(1));

    sendReq(client, "setLogStream", 1, argv_keys, argv_vals);

    free(argv_vals[0]);
    free(argv_vals);
    free(argv_keys);
} 

const char* getStringParam(struct json_object *object, const char *key) {
    json_object *extracted;
    if (json_object_object_get_ex(object, key, &extracted)) {
        return json_object_to_json_string(extracted);
    }
    return NULL;
}

struct json_object* getParam(struct json_object *object, const char *key) {
    json_object *extracted;
    if (json_object_object_get_ex(object, key, &extracted)) {
        return extracted;
    }
    return NULL;
}
