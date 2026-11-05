
This document explains the embedded-systems concepts used in the Arduino Uno smart irrigation prototype.

## 1. Analog-to-Digital Conversion (ADC)

The soil-moisture sensor produces an analog voltage. The Arduino Uno's 10-bit ADC converts that voltage into a digital value the firmware can process.

A 10-bit ADC provides \(2^{10} = 1024\) levels, numbered from 0 to 1023.

With the default 5 V analog reference:

\[
ADC \approx \frac{V_{in}}{V_{ref}} \times 1023
\]

For example, an input of approximately 2.5 V produces an ADC reading near 512.

In the firmware:

```cpp
int moisture = analogRead(A0);
```

This reads the analog signal connected to A0. The returned value is a raw ADC count, not a calibrated moisture percentage. The relationship between the reading and soil moisture depends on the particular sensor, its supply voltage, soil type, and probe condition.

**Key point:** ADC allows a microcontroller to measure changing analog sensor voltages as digital numbers.

## 2. GPIO — General-Purpose Input/Output

GPIO pins are configurable microcontroller pins used to communicate with external circuits.

- An input pin reads a logic level from an external device.
- An output pin drives a logic level to control another circuit.

In this project:

| Arduino pin | Use |
|---|---|
| A0 | Reads the sensor's analog output |
| D8 | Controls the relay module input |

Example:

```cpp
pinMode(8, OUTPUT);
digitalWrite(8, LOW);
```

`pinMode()` configures D8 as an output. `digitalWrite()` sets its logic level.

On an Arduino Uno, a digital HIGH is approximately 5 V and LOW is approximately 0 V. GPIO pins have strict current limits; they must not power a pump or other high-current load directly.

**Key point:** GPIO provides the basic digital interface between firmware and external hardware.

## 3. Relay Operation

A relay is an electrically controlled switch. A typical electromechanical relay contains a coil and movable contacts.

Common contact terminals are:

- **COM:** Common contact.
- **NO:** Normally Open; disconnected from COM when the relay is idle.
- **NC:** Normally Closed; connected to COM when the relay is idle.

When the relay coil is energized, COM changes from NC to NO. In this project, the pump supply is routed through COM and NO so the pump normally remains off.

The Arduino controls the relay module's input. The relay contacts switch the pump's separate supply. The relay module's input polarity must be verified: some modules are active-LOW, while others are active-HIGH.

**Why use a relay?** An Arduino GPIO cannot safely provide the current required by a DC pump. The relay allows a low-current control signal to switch a separate load circuit, provided the relay's contact voltage and current ratings are suitable.

## 4. Separate Power Supplies and Electrical Isolation

The Arduino and sensor use low-voltage electronics power, while the pump needs a separate supply within its rated 6–9 V range.

A separate pump supply helps prevent the motor's startup or stall current from pulling down the Arduino supply and resetting the controller.

A relay has a coil/control side and a contact/load side. The relay mechanism separates these circuits. This is galvanic isolation only when the relay module's PCB layout and wiring preserve that separation. Do not assume every relay board provides fully isolated input circuitry.

Recommended arrangement:

| Part | Supply |
|---|---|
| Arduino Uno | Regulated 5 V USB power bank or adapter |
| Relay module | Arduino 5 V, if within the board and USB current budget |
| Moisture sensor | Voltage supported by the specific sensor module |
| Pump | Separate regulated 6–9 V supply with sufficient startup current |

Do not connect the pump supply positive to the Arduino 5 V pin. Do not power the pump from an Arduino GPIO or the Arduino 5 V rail.

For a DC motor, a suitably rated flyback/suppression diode across the motor terminals can reduce inductive voltage spikes. Follow the diode's polarity and current rating requirements.

**Key point:** Separate load power improves supply stability; relay contacts can provide electrical separation between the control and pump circuits when wired correctly.

## 5. Hysteresis

Sensor readings can fluctuate because of electrical noise, movement of the probe, and changes in the soil. If the pump uses one threshold for both starting and stopping, small fluctuations around that threshold can make the relay switch repeatedly.

Hysteresis uses two thresholds:

- If the reading reaches the dry threshold, turn the pump on.
- If the reading reaches the wet threshold, turn the pump off.
- Between the thresholds, keep the previous state.

Example for a sensor whose reading is higher in dry soil:

```cpp
if (!pumpIsOn && moisture >= DRY_THRESHOLD) {
    setPump(true);
} else if (pumpIsOn && moisture <= WET_THRESHOLD) {
    setPump(false);
}
```

The example thresholds must be calibrated using the actual sensor and soil. If the sensor reading decreases as the soil dries, the comparison directions must be reversed.

**Key point:** Hysteresis prevents rapid relay chatter when the sensor value fluctuates near a switching point.

## 6. Hardware Debugging

Embedded debugging should be systematic. Check the signal path and power path separately instead of changing code at random.

| Symptom | Checks |
|---|---|
| ADC reading stays at 0 or 1023 | Sensor supply, GND, AO-to-A0 wiring, and input voltage range |
| Reading does not respond to soil | Probe connection, sensor operation, and calibration |
| Relay does not click | Relay supply, input pin, active polarity, and trigger compatibility |
| Relay clicks but pump does not run | Pump supply, battery capability, relay contacts, polarity, and wiring |
| Arduino resets when pump starts | Pump startup current, supply voltage drop, wiring layout, and motor suppression |

The Serial Monitor is useful for observing raw ADC readings and state changes:

```cpp
int moisture = analogRead(A0);
Serial.print("Soil reading: ");
Serial.println(moisture);
```

A useful test sequence is:

1. Test the sensor with the pump supply disconnected.
2. Record readings in dry and moist soil.
3. Calibrate the thresholds.
4. Test relay switching with the pump disconnected.
5. Connect and test the pump only after the control circuit works correctly.

**Key point:** Good debugging isolates one subsystem at a time and uses measurements to locate the fault.

## 7. Interview Summary

| Concept | What it demonstrates in this project |
|---|---|
| ADC | Reading an analog sensor signal |
| GPIO | Controlling an external device with a digital output |
| Relay | Switching a load using a control signal |
| Power design | Managing separate controller and motor supplies |
| Hysteresis | Preventing unstable switching |
| Debugging | Testing and diagnosing hardware systematically |

## Notes Before Publishing

- Replace example thresholds with measured values from your own sensor and soil.
- Confirm the sensor module's supported supply voltage.
- Confirm the relay module's trigger polarity and input compatibility.
- Record actual test results rather than presenting example readings as measured data.
- Do not leave a water pump unattended until the system has been tested for leaks, sensor faults, relay faults, and dry running.

