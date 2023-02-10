#include <WiFi.h>
#include "server_config.h"
//
//
//
extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#include <AsyncMqttClient.h>

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;
#define TASK(NAME, FUNC) xTimerCreate(NAME, pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(FUNC))

void connectToWifi()
{
  Serial.print("*** Connecting to Wi-Fi:");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqtt()
{
  Serial.print("*** Connecting to MQTT Server: ");
  Serial.println("tcp/81.71.10.205");
  mqttClient.setClientId(CLIENTID);
  mqttClient.setCredentials(USERNAME, PASSWORD);
  mqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event)
{
  // Serial.printf("[WiFi-event] event: %d", event);
  // Serial.println();
  switch (event)
  {
  case SYSTEM_EVENT_STA_GOT_IP:
    Serial.print("*** WiFi connected, IP address: ");
    Serial.println(WiFi.localIP());
    connectToMqtt();
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.println("*** WiFi lost connection");
    xTimerStop(mqttReconnectTimer, 0);
    xTimerStart(wifiReconnectTimer, 0);
    break;
  }
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println("*** Connected MQTT server successfully.");
  mqttClient.subscribe(PROPERTY_DOWN, 1);
  mqttClient.subscribe(ACTION_DOWN, 1);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("*** Disconnected from MQTT.");

  if (WiFi.isConnected())
  {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttMessage(char *topic, char *payload,
                   AsyncMqttClientMessageProperties properties,
                   size_t len, size_t index,
                   size_t total)
{
  Serial.println("*** Publish received.");
  Serial.print("  topic: ");
  Serial.println(topic);
  Serial.print("  payload: ");
  Serial.println(payload);
  Serial.print("  qos: ");
  Serial.println(properties.qos);
  Serial.print("  dup: ");
  Serial.println(properties.dup);
  Serial.print("  retain: ");
  Serial.println(properties.retain);
  Serial.print("  len: ");
  Serial.println(len);
  Serial.print("  index: ");
  Serial.println(index);
  Serial.print("  total: ");
  Serial.println(total);
}

void onMqttPublish(uint16_t packetId)
{
}

void setup()
{
  Serial.begin(115200);
  while (Serial.available())
    ;
  Serial.print("*** Device starting: ");
  Serial.println(DEVICEID);
  Serial.print("*** Device Baud Rate: ");
  Serial.println(115200);
  Serial.print("*** MQTT Server: ");
  Serial.println("81.71.10.205");
  mqttReconnectTimer = TASK("mqttTimer", connectToMqtt);
  wifiReconnectTimer = TASK("wifiTimer", connectToWifi);
  WiFi.onEvent(WiFiEvent);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  connectToWifi();
}
//
static char json[80];
void loop()
{
  if (mqttClient.connected())
  {
    // 读取1 2 3 4 5 的模拟电压值
    float v1 = analogRead(32) * (5.0 / 1023.0);
    float v2 = analogRead(33) * (5.0 / 1023.0);
    float v3 = analogRead(34) * (5.0 / 1023.0);
    float v4 = analogRead(35) * (5.0 / 1023.0);
    float v5 = analogRead(36) * (5.0 / 1023.0);
    sprintf(json, "{\"adc32\":%2f,\"adc33\":%2f,\"adc34\":%2f,\"adc35\":%2f,\"adc36\":%2f}", v1, v2, v3, v4, v5);
    // Serial.println(json);
    mqttClient.publish(PROPERTY_UP, 1, false, json, strlen(json));
  }
  delay(1000);
}