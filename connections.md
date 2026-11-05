# Hardware Connections

## Pin map

| Signal | Arduino Uno |
|---|---|
| Moisture sensor AO | A0 |
| Moisture sensor GND | GND |
| Moisture sensor VCC | 3.3V only if supported by module; otherwise rated supply |
| Relay IN | D8 |
| Relay VCC | 5V |
| Relay GND | GND |

## Pump contact wiring

```text
Pump supply (+) ---- Relay COM
Relay NO ------------ Pump (+)
Pump (-) ------------ Pump supply (-)

Relay NC: unused
```

The pump supply is separate from the Arduino supply. The relay's contact side switches the pump supply; do not connect the pump supply positive to the Arduino.
<img width="1385" height="753" alt="image" src="https://github.com/user-attachments/assets/a9e95fb8-acad-4f01-b082-3ad34c496092" />


## Notes

- Verify the pin labels printed on your actual modules; board layouts vary.
- Confirm the relay is active-LOW or active-HIGH before using the firmware.
- Confirm the relay module's input compatibility and current requirements.
- The sensor's AO output must remain within the Arduino Uno analog input range (0–5V).
- Disconnect all power before changing wiring.
