# **Termalizator**
Termalizator is an embedded system for the ESP8266 which enables user to switch the GPIO pin based on the current temperature. The system has been developed for the DS18B20 temperature sensor.

## **Basic Usage**
In order to manage the system visit its webpage at http://termalizator. There, the user can configure target temperature and working mode.

In order to set Termalizator to active state, the *Power* icon must be active. Flashing built in LED means the system is active and the *Power* icon on the webpage has color green. Only when the system is active the temperature reading occurs. Additionally, the configured target temperature, the measured temperature and the elapsed time since start should pop up at the bottom of the webpage.

### **Working mode**
The temperature is determined based on the selected working mode. By clicking on the *Cog* icon on the webpage the additional options will show up where user can change the working mode. This option is not critical for the operation of the device.
List of the available working modes:
* **MIN** - The minimal temperature of all connected temperature sensors
* **AVG** - ***Default*** - Calculates average of all connected temperature sensors
* **MAX** - The maximal temperature of all connected temperature sensors

## **Typical usage**
Termalizator might come in handy when there is a need to execute an action based on the actual temperature. Usually, the GPIO pin switches on a relay module which then powers some kind of heating element. For example:
1. low temperature long time cooking - Sous vide
2. switching heating at home remotely
3. ...
