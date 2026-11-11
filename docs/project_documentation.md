# Project Documentation
## IoT-Based Environmental & Safety Monitoring System Using ESP8266

### 1. Introduction

The IoT-Based Environmental and Safety Monitoring System is an embedded systems project developed using the NodeMCU ESP8266 microcontroller.

The system monitors temperature, humidity, gas-related sensor readings, and flame detection status. It uses Wi-Fi connectivity to transmit sensor data to the ThingSpeak cloud platform for remote monitoring and graphical visualization.

An LED provides a local visual warning indication based on configured sensor conditions.

### 2. Objectives

- Monitor temperature and humidity.
- Detect changes in gas and smoke-related sensor readings.
- Detect flame sensor activation.
- Transmit sensor readings to the cloud using Wi-Fi.
- Display real-time sensor data through ThingSpeak graphs.
- Implement a basic local warning indicator.

### 3. Hardware Requirements

| Component | Description |
|---|---|
| NodeMCU ESP8266 ESP-12E | Main controller with Wi-Fi |
| DHT11 | Temperature and humidity sensor |
| MQ-2 | Gas and smoke-related sensor |
| Flame Sensor | Digital flame detection module |
| LED | Visual warning indicator |
| 220–330Ω resistor | LED current limiting |
| Breadboard | Circuit assembly |
| Jumper wires | Electrical connections |
| USB cable | Power and programming |

### 4. Software Requirements

- Arduino IDE
- ESP8266 board package
- DHT sensor library
- Adafruit Unified Sensor library
- ThingSpeak account and channel
- Wi-Fi connection

### 5. Pin Configuration

| Component | ESP8266 Pin |
|---|---|
| DHT11 DATA | D2 |
| MQ-2 Analog Output | A0 |
| Flame Sensor DO | D5 |
| LED | D7 |

The MQ-2 analog output must be scaled to remain within the actual A0 input limit of the NodeMCU board. The flame sensor output must also be compatible with 3.3V GPIO logic.

### 6. Working Principle

The system operates through the following sequence:

1. The DHT11 measures ambient temperature and humidity.
2. The MQ-2 sensor provides an analog reading related to gas and smoke exposure.
3. The flame sensor provides a digital detection signal.
4. The ESP8266 reads the sensor outputs.
5. The controller processes the readings and evaluates configured warning conditions.
6. The LED indicates a warning condition.
7. The ESP8266 connects to Wi-Fi and sends the collected data to ThingSpeak.
8. ThingSpeak displays the received values through graphical visualizations.

### 7. System Architecture

Sensors → ESP8266 NodeMCU → Wi-Fi → ThingSpeak Cloud → Monitoring Dashboard

### 8. ThingSpeak Cloud Integration

Four ThingSpeak fields are configured:

| Field | Parameter | Unit |
|---|---|---|
| Field 1 | Temperature | °C |
| Field 2 | Humidity | % |
| Field 3 | MQ-2 Reading | ADC |
| Field 4 | Flame Status | Digital status |

The ESP8266 uses HTTP communication to upload sensor readings to the ThingSpeak channel.

### 9. Testing and Validation

The following modules were tested during implementation:

- ESP8266 Wi-Fi connectivity.
- DHT11 temperature and humidity readings.
- MQ-2 analog output.
- Flame sensor digital output.
- LED warning output.
- ThingSpeak data transmission.
- Cloud dashboard graph updates.

### 10. Observed Sensor Readings

An example diagnostic reading recorded during testing:

| Parameter | Observed Value |
|---|---:|
| Temperature | 28.7 °C |
| Humidity | 39.70% |
| MQ-2 ADC | 118 |
| Flame Sensor | LOW during normal condition |

These values are sample observations from one test session, not guaranteed operating values or calibration limits.

### 11. Applications

- Educational IoT demonstrations.
- Environmental monitoring experiments.
- Basic laboratory monitoring prototypes.
- Embedded systems and wireless communication learning.

### 12. Limitations

- MQ-2 readings are raw ADC values, not calibrated gas concentrations.
- Sensor readings depend on environmental conditions and calibration.
- Flame detection depends on sensor placement and module characteristics.
- Wi-Fi availability is required for cloud data transmission.
- This educational prototype is not a certified fire or gas safety device.

### 13. Future Scope

- Mobile application integration.
- Email or mobile notification alerts.
- Improved MQ-2 calibration.
- Additional environmental sensors.
- Historical data analysis.
- Improved fault detection and warning logic.

### 14. Conclusion

The project demonstrates the practical integration of sensors, a Wi-Fi-enabled microcontroller, and an IoT cloud platform.

The ESP8266 collects environmental and safety-related sensor readings and transmits them to ThingSpeak for remote visualization. This project provides practical experience in embedded programming, sensor interfacing, wireless communication, and IoT-based monitoring.

### 15. Project Repository

Source code, circuit diagrams, images, and supporting documentation are maintained in the project repository.