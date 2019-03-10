#include "header.h"

void setup()
{
    pinMode(EXTRACTOR_PORT, OUTPUT);
    pinMode(HUMIDIFIER_PORT, OUTPUT);
    Serial.begin(115200);
    setup_wifi();
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);
    Serial.setDebugOutput(true);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}