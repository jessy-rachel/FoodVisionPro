# FoodVision Pro — Arduino Food-Storage Monitoring

An Arduino-based prototype that monitors environmental conditions relevant to food storage using temperature, humidity, light and gas sensors. This repository contains the **Arduino monitoring sketch** developed for the school innovation project; it does **not** contain a trained computer-vision model or mobile application.

## What the supplied sketch does

- Reads temperature and relative humidity from a **DHT22** sensor.
- Reads ambient-light intensity through an analog light sensor.
- Reads an analog gas-sensor signal (identified as **MQ-135** in the sketch).
- Displays temperature and a gas-threshold status on a **16×2 I²C LCD**.
- Activates indicator LEDs for configured temperature/light thresholds and a buzzer for high humidity.
- Prints live measurements to the Arduino Serial Monitor at **9600 baud**.



## Hardware referenced in the sketch

| Component | Arduino connection / reference |
|---|---|
| DHT22 data | Digital pin **D3** |
| Analog light sensor | **A2** |
| MQ-135 analog output | **A0** (`analogRead(0)`) |
| Blue indicator LED | **D2** |
| Red indicator LED | **D4** |
| Yellow indicator LED | **D5** |
| Buzzer | **D7** |
| 16×2 I²C LCD | I²C address **0x27**; Uno wiring document: SDA **A4**, SCL **A5** |

The original wiring guide documents an LDR divider using a **220 Ω** resistor, a **1 kΩ** DHT22 pull-up, and **220 Ω** LED resistors. Verify resistance values and wiring against your actual parts before powering the circuit.

Use suitable current-limiting resistors for LEDs and verify sensor power requirements before wiring. The code doesn't specify a particular Arduino board.

## Software setup

1. Install Arduino IDE and select your board and port.
2. Install **DHT sensor library** and its dependencies, and a compatible **LiquidCrystal_I2C** library.
3. Open [`src/FoodVisionPro.ino`](src/FoodVisionPro.ino), verify the LCD I²C address, and upload.
4. Open Serial Monitor at **9600 baud** to inspect sensor values.
5. Adjust thresholds to match your actual sensors and environment before demonstrating.

## Thresholds currently hard-coded

| Condition | Behavior |
|---|---|
| Temperature below 15°C | Blue LED on |
| Temperature above 30°C | Red LED on |
| Light ADC reading ≥ 130 | Yellow LED on |
| Humidity above 55% | Buzzer tone |
| Gas ADC reading above 600 | LCD displays `Spoilt Food !!!` (indicative alert only) |

## Repository contents

- `src/FoodVisionPro.ino` — original Arduino sketch
- `docs/FoodVision_Arduino_Wiring.pdf` — illustrated pin/wiring reference
- `README.md` and `.gitignore`

## Original hardware documentation

- [Arduino connections and build photographs (PDF)](docs/FoodVision_Arduino_Wiring.pdf) — MQ-135, LDR, DHT22, I²C LCD, three LEDs and buzzer.
- The guide refers to an earlier filename `FINAL_CODE_3`; this repository preserves the supplied `FoodVisionPro.ino`. Pin assignments were cross-checked against the sketch.

## Context and scope

This project began as a sensor-driven food-storage monitoring prototype. The broader **FoodVision Pro** concept later included experimentation with AI/computer-vision-based freshness assessment, but those additional assets are **not included in this code upload**. The original circuit photographs and wiring guidance are provided in `docs/`. A separate AI implementation, trained model and mobile app have not been supplied and can be added later.

## Limitations

Thresholds are fixed and uncalibrated; the code does not handle sensor read failures robustly. Gas readings are not specific to food spoilage and should not be relied upon for consumption decisions.
