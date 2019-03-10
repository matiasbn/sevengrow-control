#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>

// #define MQTT_SERVER "192.168.0.12"
// #define MQTT_PORT 1883 // use 8883 for SSL
#define MQTT_SERVER "m13.cloudmqtt.com"
#define MQTT_PORT 16342 // use 8883 for SSL
#define MQTT_USER "jdlolrja"
#define MQTT_PASS "4NlQppdX7Qax"
#define DELIVER_WAIT 5000

// Update these with values suitable for your network.

const char *ssid = "VTR-2778044";
const char *password = "dnn6jtjpXvSq";

const char *EXTRACTOR_TOPIC = "sevengrow/307/control/extractor";
const char *HUMIDIFIER_TOPIC = "sevengrow/307/control/humidifier";

const char *ON_ORDER = "on";
const char *OFF_ORDER = "off";

const int EXTRACTOR_PORT = 4;  //D2 ESP8266
const int HUMIDIFIER_PORT = 5; //D1 ESP8266
const int INTRACTOR_PORT = 0;  //D3 ESP8266

WiFiUDP udp;
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void decideAction(char order[], const char *topic)
{
    if (strcmp(order, ON_ORDER) && strcmp(order, OFF_ORDER))
    {
        Serial.println("Action not valid");
        return;
    }

    if (!strcmp(topic, EXTRACTOR_TOPIC))
    {
        if (!strcmp(order, ON_ORDER))
        {
            digitalWrite(EXTRACTOR_PORT, HIGH);
            Serial.println("Extractor on");
        }
        else
        {
            digitalWrite(EXTRACTOR_PORT, LOW);
            Serial.println("Extractor off");
        }
    }
    else if (!strcmp(topic, HUMIDIFIER_TOPIC))
    {
        if (!strcmp(order, ON_ORDER))
        {
            digitalWrite(HUMIDIFIER_PORT, HIGH);
            Serial.println("Humidifier on");
        }
        else
        {
            digitalWrite(HUMIDIFIER_PORT, LOW);
            Serial.println("Humidifier off");
        }
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    char charPayload[length];
    for (int i = 0; i < length; i++)
    {
        charPayload[i] = (char)payload[i];
    }

    if (!strcmp(topic, EXTRACTOR_TOPIC) || !strcmp(topic, HUMIDIFIER_TOPIC))
    {
        decideAction(charPayload, topic);
    }
    else
    {
        Serial.println("Not found");
    }

    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP8266Client2", MQTT_USER, MQTT_PASS))
        {
            Serial.println("connected");
            client.subscribe(EXTRACTOR_TOPIC);
            client.subscribe(HUMIDIFIER_TOPIC);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
