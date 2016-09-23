
#include "Arduino.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "MqttSoilHumidity.h"

MqttSoilHumidity::MqttSoilHumidity(PubSubClient client,const char* mqtt_topic,char* device_id,int pin)
{
  _client = client;
  _mqtt_topic = mqtt_topic;
  _device_id = device_id;
  _pin = pin;
}

boolean MqttSoilHumidity::readSensor()
{

	int sensorValue = analogRead(_pin);

	// Check if any reads failed and exit early (to try again).
	if (isnan(sensorValue)) {
		Serial.println("Failed to read from DHT sensor!");
		return false;
	} else {


		String json;
		StaticJsonBuffer <200> jsonBuffer;
		JsonObject& root = jsonBuffer.createObject();
		root["soil_humidity"] = sensorValue;
		root["device_id"] = _device_id;
		root["sensor"] = _pin;
		String jsonString = "";
		root.printTo(jsonString);

		Serial.print(jsonString);
		Serial.print("\n");

		int commandLen = jsonString.length() + 1;
		char message_buffCommand[commandLen];
		jsonString.toCharArray(message_buffCommand, commandLen);

		_client.publish(_mqtt_topic, message_buffCommand);
	}


 return true;
}
