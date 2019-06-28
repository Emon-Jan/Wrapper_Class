# Wrapper collection in CPP - Mosquitto

Wrapper class of mosquitto-lib in cpp.

## Installation

- libmosquitto

## How To Use

- Include the `MOSQUITTOWrapper` in your project
- Create an instance **MOSQUITTOWrapper mqtt** Default parameters are `host: localhost, port: 1883, client_id: null, keepalive: 60`
- Default topic: **test**
- call the method **mqtt.mosquittoLoop()**

## How to build and run

- In terminal g++ mosq.cpp MOSQUITTOWrapper.cpp MOSQUITTOWrapper.h -o mosqexe
- ./mosqexe
