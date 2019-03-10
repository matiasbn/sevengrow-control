# Sevengrow Temperature and Humidity Firmware

DHT11 as sensor

### [M3]Transmission

_The Transmission module is the one that is on charge of transmitting the data sensed by the ESP8266 to the server:_

* [MQTT](http://mqtt.org/) (Message Queue Telemetry Transport):

  * Measure devices topic format: 
  ````
  /sevengrow/clientid/sensor/co2
  /sevengrow/clientid/sensor/humidity
  /sevengrow/clientid/sensor/power
  /sevengrow/clientid/sensor/temperature
  ````

  * Control devices topic format:
  ````
  /sevengrow/clientid/control/lights/
  /sevengrow/clientid/control/extractors/
  /sevengrow/clientid/control/humidifier/
  /sevengrow/clientid/control/co2emiiter/