#include "include/tg-client.h"

int main(int argc, char **argv) {
    struct TgClient *tg_client = initClient();

    closeClient(tg_client);
    return 0;
}
