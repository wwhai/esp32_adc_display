#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__
//******************NETWORK-CONFIG*****************
// WIFI SSID
#define WIFI_SSID "nilyouth"
// WIFI 密码
#define WIFI_PASSWORD "665544332211"
//******************SERVER-CONFIG******************
// MQTT Server
#define MQTT_HOST IPAddress(81, 71, 10, 205)
// MQTT 端口
#define MQTT_PORT 1883
//
//********************MQTT-ARGS********************
const char *PRODUCT = "p9fedd4fd4eb640b5b3950437c4b23623";
const char *DEVICEID = "dfc76d23a39e8405ea933cfb75afd8492";
const char *CLIENTID = "dfc76d23a39e8405ea933cfb75afd8492";
const char *USERNAME = "dfc76d23a39e8405ea933cfb75afd8492";
const char *PASSWORD = "a1a99584518d43e2b474cdcb8d4f563a";
//
//********************MQTT-ARGS********************
// 属性上报
const char *PROPERTY_UP = "$thing/up/property/p9fedd4fd4eb640b5b3950437c4b23623/dfc76d23a39e8405ea933cfb75afd8492";
// 属性下发
const char *PROPERTY_DOWN = "$thing/down/property/p9fedd4fd4eb640b5b3950437c4b23623/dfc76d23a39e8405ea933cfb75afd8492";
// 属性回复
const char *PROPERTY_REPLY = "$thing/property/reply/p9fedd4fd4eb640b5b3950437c4b23623/dfc76d23a39e8405ea933cfb75afd8492";
// 属性下发
const char *ACTION_DOWN = "$thing/down/action/p9fedd4fd4eb640b5b3950437c4b23623/dfc76d23a39e8405ea933cfb75afd8492";
// 动作回复
const char *ACTION_REPLY = "$thing/action/reply/p9fedd4fd4eb640b5b3950437c4b23623/dfc76d23a39e8405ea933cfb75afd8492";
#endif