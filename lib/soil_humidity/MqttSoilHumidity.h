#ifndef MqttSoilHumidity_h
#define MqttSoilHumidity_h

#include "Arduino.h"

class MqttSoilHumidity
{
	public:
	  MqttSoilHumidity(PubSubClient client,const char* mqtt_topic,char* device_id,int pin);
	  boolean readSensor();
	private:
	  PubSubClient _client;
	  const char* _mqtt_topic;
	  char* _device_id;
	  int _pin;
};

#endif
