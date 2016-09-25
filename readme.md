# Solid Humidity MQTT Sensor

Publish the Solid Humidity Information all minute to a central MQTT topic `/iot/flower`, after than the NodeMCU go in the DeepSleep mode.

```json
{"soil_humidity":362,"device_id":"flower-livingroom","sensor":17}
```

## Dependencies

 - [MQTT Client](http://platformio.org/lib/show/89/PubSubClient)
 - [Arduino Json](http://platformio.org/lib/show/64/ArduinoJson)
 - [MQTT Device Alive](http://platformio.org/lib/show/365/MQTT%20Device%20Alive)

## Wiring

<img src="doc/project_bb.png" alt="breadboard" width="250" />

## Hardware

 - NodeMCU Deleloper Board
 - SODIAL (R) Boden Hygrometer
