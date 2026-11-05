# Smart Irrigation System

An automatic soil-moisture-based irrigation prototype built with an **Arduino Uno**, an **LM393 soil-moisture sensor module**, a **5V relay module**, and a **6–9V DC mini water pump**.

The controller reads the sensor's analog output. When the soil is dry, it energizes the relay to run the pump. When the soil becomes sufficiently wet, it switches the pump off.

> **Project status:** Prototype. Calibrate the sensor in the actual soil before operating the pump unattended. The threshold values in the firmware are examples, not universal moisture percentages.

## Features

- Analog soil-moisture measurement using Arduino Uno ADC (`A0`)
- Relay control using a digital output (`D8`)
- Separate power supply for the pump
- Hysteresis thresholds to reduce rapid relay chatter
- Serial Monitor output for calibration and debugging

## Hardware

- Arduino Uno
- Soil-moisture probe and LM393 comparator module
- 5V single-channel relay module (verify its input trigger compatibility)
- 6–9V DC mini water pump
- Regulated 6–9V pump supply capable of supplying the pump's startup current
- 5V USB power bank or regulated USB supply for the Arduino
- Jumper wires, tubing, and a suitable enclosure

## Wiring

### Sensor to Arduino

| Sensor module | Arduino Uno |
|---|---|
| VCC | 3.3V **only if the specific module supports 3.3V**; otherwise use its rated supply |
| GND | GND |
| AO | A0 |
| DO | Not connected |

The firmware uses `AO`. The `DO` output and onboard potentiometer are not used.

### Relay control to Arduino

| Relay module | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| IN | D8 |

This example assumes an **active-LOW** relay input. If your module is active-HIGH, change `RELAY_ON_LEVEL` and `RELAY_OFF_LEVEL` in the firmware. Confirm the relay input accepts the Arduino's logic level and that the Arduino 5V rail can supply the relay module's coil current.

### Pump through relay contacts

| Connection | Goes to |
|---|---|
| Pump supply positive (+) | Relay COM |
| Relay NO | Pump positive (+) |
| Pump negative (-) | Pump supply negative (-) |
| Relay NC | Leave disconnected |

Use a regulated supply within the pump's 6–9V rating and with adequate startup current. Do **not** power the pump from an Arduino pin, the Arduino 5V pin, or the USB power bank.

The relay contacts switch the pump's separate supply. Keep the pump supply wiring physically separate from low-voltage sensor wiring. A suitable flyback diode across the DC pump terminals can help suppress motor transients: diode cathode (striped end) to pump positive, anode to pump negative. Choose a diode rated for the motor current.

## Power arrangement

- Arduino Uno: 5V from a power bank through a USB-A-to-USB-B cable.
- Relay module: Arduino 5V and GND (subject to current-budget and module requirements).
- Sensor: Arduino 3.3V only if supported by the sensor module; otherwise use its specified voltage.
- Pump: separate regulated 6–9V supply.

Use a standard 5V USB output from the power bank. Do not use a fast-charge 9V/12V mode to power the Arduino USB input. Never connect the pump battery positive to Arduino 5V or VIN.

## Firmware setup

1. Open `firmware/smart_irrigation.ino` in Arduino IDE.
2. Select **Arduino Uno** and the correct port.
3. Upload the sketch.
4. Open Serial Monitor at **9600 baud**.
5. With the pump supply disconnected, record readings in dry soil and adequately moist soil.
6. Set `DRY_THRESHOLD` and `WET_THRESHOLD` based on those readings.
7. Test the relay with the pump still disconnected.
8. Only after confirming correct switching, connect the pump supply through COM and NO.

### Calibration

This code assumes the sensor reading is **higher when dry** and lower when wet. Verify this with your own module. If your readings move in the opposite direction, reverse the comparisons in the firmware.

Set two thresholds with a gap between them:
- Above `DRY_THRESHOLD`: declare soil dry and turn pump ON.
- Below `WET_THRESHOLD`: declare soil wet and turn pump OFF.
- Between the thresholds: retain the previous state (hysteresis).

Do not use water immersion as the sole calibration method. Calibrate in the soil and at the moisture level relevant to the plant.

## Safety

- Keep the Arduino, relay board, power bank, connectors, and exposed wiring away from water.
- Insulate all exposed conductors and use strain relief.
- Do not dismantle a mains adapter or work on mains wiring.
- Confirm pump polarity, voltage rating, and startup current before connecting its supply.
- A small rectangular PP3 9V battery often cannot supply enough current for a pump; use a suitable battery pack or regulated DC supply.
- Do not leave the prototype unattended until it has been tested for leaks, stuck relay conditions, sensor faults, and pump dry-running.
- Disconnect both supplies before changing wiring.

## Repository layout

```text
smart-irrigation-system/
├── README.md
├── firmware/
│   └── smart_irrigation.ino
├── hardware/
│   └── connections.md
├── docs/
│   ├── calibration-and-testing.md
│   └── troubleshooting.md
├── images/
│   └── README.md
├── LICENSE
└── .gitignore
```

## Future improvements

- Add a maximum pump runtime and cooldown period.
- Add a water-level sensor to prevent dry running.
- Add a manual override switch.
- Replace the resistive probe with a capacitive moisture sensor for improved corrosion resistance.
- Design a compact PCB and enclosure.
- Add fault detection and a documented test plan.


