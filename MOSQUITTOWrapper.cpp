#include <iostream>
#include "MOSQUITTOWrapper.h"

void MOSQUITTOWrapper::mosquittoCallbackSet()
{
    mosquitto_log_callback_set(mosq, on_log);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);
    mosquitto_subscribe_callback_set(mosq, on_subscribe);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
}

MOSQUITTOWrapper::MOSQUITTOWrapper()
{
    mosquitto_lib_init();

    mosq = mosquitto_new(client_id, clean_session, nullptr);
    if (!mosq)
    {
        fprintf(stderr, "Error: Out of memory.\n");
    }

    this->mosquittoCallbackSet();

    if (mosquitto_connect(mosq, host, port, keepalive))
    {
        fprintf(stderr, "Unable to connect.\n");
    }
}

MOSQUITTOWrapper::MOSQUITTOWrapper(
    const char *host, int port,
    const char *client_id,
    int keepalive,
    bool clean_session)
    : host{host}, port{port}, client_id{client_id},
      keepalive{keepalive}, clean_session{clean_session}
{
    mosquitto_lib_init();

    mosq = mosquitto_new(client_id, clean_session, nullptr);
    if (!mosq)
    {
        fprintf(stderr, "Error: Out of memory.\n");
    }

    this->mosquittoCallbackSet();

    if (mosquitto_connect(mosq, host, port, keepalive))
    {
        fprintf(stderr, "Unable to connect.\n");
    }
}

MOSQUITTOWrapper::~MOSQUITTOWrapper()
{
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

void MOSQUITTOWrapper::mosquittoLoop()
{
    while (true)
    {
        mosquitto_loop(mosq, -1, 1);
    }
}

void MOSQUITTOWrapper::on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    if (message->payloadlen)
    {
        printf("Message received: %s %s\n", message->topic, (char *)message->payload);
    }
    else
    {
        printf("%s (null)\n", message->topic);
    }
    fflush(stdout);
}

void MOSQUITTOWrapper::on_connect(struct mosquitto *mosq, void *userdata, int result)
{
    int i;
    if (!result)
    {
        mosquitto_subscribe(mosq, NULL, "test", 1); // test is topic
    }
    else
    {
        fprintf(stderr, "Connect failed\n");
    }
}

void MOSQUITTOWrapper::on_disconnect(struct mosquitto *mosq, void *userdata, int result)
{
    std::cout << "Disconnected from broker!!!" << std::endl;
}

void MOSQUITTOWrapper::on_subscribe(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
    int i;
    printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
    for (i = 1; i < qos_count; i++)
    {
        printf(", %d", granted_qos[i]);
    }
    printf("\n");
}

void MOSQUITTOWrapper::on_log(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
    /* Pring all log messages regardless of level. */
    printf("LOG: %s\n", str);
}