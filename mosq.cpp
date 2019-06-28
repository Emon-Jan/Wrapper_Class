#include "MOSQUITTOWrapper.h"

int main(int argc, char const *argv[])
{
    const char *host = "localhost";
    int port = 1883;
    const char *client_id = nullptr;
    int keepalive = 60;
    bool clean_session = true;
    const char *topic = "test";

    MOSQUITTOWrapper mqtt = MOSQUITTOWrapper(host, port, client_id, keepalive, clean_session, topic);
    mqtt.mosquittoLoop();

    return 0;
}
