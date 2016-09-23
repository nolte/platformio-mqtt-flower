// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <MqttSoilHumidity.h>
#include <MqttDeviceAlliveMessage.h>

WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = WLAN_SSID;
const char* password = WLAN_PASSWORD;

char DEVICE_ID[] = MQTT_DEVICE_ID;

// IP des MQTT Servers
const char* mqtt_server = MQTT_HOST;
char MQTT_DHT_PATH[] = "/iot/flowers";
char MQTT_A_LIVE_PATH[] = "/iot/devices";
const char *features[] = { "soil_humidity" };

#define SLEEP_DELAY_IN_SECONDS  60

int sensorPin = A0;

MqttSoilHumidity mqttSoilHumidity(client,MQTT_DHT_PATH,DEVICE_ID,sensorPin);
MqttDeviceAlliveMessage aliveMessage(client,MQTT_A_LIVE_PATH,DEVICE_ID,features);

long lastMsg = 0;

void setup() {
	Serial.begin(9600);
	Serial.println("soil humidity sensor start");
	setup_wifi();
	client.setServer(mqtt_server, 1883);

}

void setup_wifi() {

	delay(10);
	// We start by connecting to a WiFi network
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect(DEVICE_ID)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void loop() {
	// Wait a few seconds between measurements.

	if (!client.connected()) {
		reconnect();
	}
	client.loop();
	delay(2000);

	boolean state = mqttSoilHumidity.readSensor();
	aliveMessage.sendAliveMessage(WiFi.localIP(),state);
	Serial.println("Closing MQTT connection...");
	client.disconnect();
	delay(100);
	Serial.println("Closing WiFi connection...");
	WiFi.disconnect();
	delay(100);

	ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
	delay(100);

}
