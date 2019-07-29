#include "mqtt.h"


const char* ssid = "esp";
const char* password = "voltmeter";

WiFiClient espClient;
PubSubClient client(espClient);

void sendVoltage()
{
    if (client.connected()) {
        Serial.println(state.voltage);
        String voltage = String(state.voltage);
        client.publish("outTopic", (char*)voltage.c_str());
    }
}


void readCommand()
{
    int command = 0;
    switch (command) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
}

void initMqtt()
{
    setupWifi();
}

void setupWifi()
{
    Serial.begin(460800);
    Serial.setDebugOutput(true);
//system_phy_set_powerup_option(3);
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    randomSeed(micros());
}

void setupMqtt()
{
    client.setServer(WiFi.gatewayIP(), 1883);

    String clientId = "wifi-voltmeter-";
    clientId += String(random(0xffff), HEX);
    client.connect(clientId.c_str());
}

void updateWifiStatus()
{
    switch (WiFi.status()) {
        case WL_CONNECTED:
            state.wifi = 2;
            if (client.connected()) {
                state.wifi=3;
                sendVoltage();
            } else {
                Serial.print("Connecting to MQTT broker at: ");
                Serial.println(WiFi.gatewayIP());
                setupMqtt();
            }
            break;
        case WL_IDLE_STATUS:
            state.wifi = 1;
            break;
        case WL_CONNECT_FAILED:
            state.wifi = 4;
            break;
        default:
            state.wifi = 0;
    }
}