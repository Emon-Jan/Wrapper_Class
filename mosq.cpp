#include "MOSQUITTOWrapper.h"

int main(int argc, char const *argv[])
{
    MOSQUITTOWrapper mqtt;
    mqtt.mosquittoLoop();
    return 0;
}
