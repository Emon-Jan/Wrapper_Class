#if !defined(MOSQUITTOWRAPPER_H)
#define MOSQUITTOWRAPPER_H

#include <mosquitto.h>

class MOSQUITTOWrapper
{
private:
    const char *host = "localhost";
    int port = 1883;
    int keepalive = 60;
    bool clean_session = true;
    const char *client_id = nullptr;
    const char *topic = "test";

public:
    struct mosquitto *mosq = nullptr;

    void mosquittoCallbackSet();
    static void on_log(struct mosquitto *mosq, void *userdata, int level, const char *str);
    static void on_connect(struct mosquitto *mosq, void *userdata, int result);
    static void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    static void on_subscribe(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos);
    static void on_disconnect(struct mosquitto *mosq, void *userdata, int result);

    void mosquittoLoop();

    MOSQUITTOWrapper();
    MOSQUITTOWrapper(
        const char *host,
        int port,
        const char *client_id,
        int keepalive,
        bool clean_session,
        const char *topic);
    ~MOSQUITTOWrapper();
};

#endif // MOSQUITTOWRAPPER_H
