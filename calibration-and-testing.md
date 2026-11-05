# Calibration and Testing

## 1. Test the sensor first

1. Disconnect the pump supply.
2. Power the Arduino and sensor.
3. Open Serial Monitor at 9600 baud.
4. Record the raw reading with the probe in dry soil.
5. Record the raw reading in adequately moist soil.
6. Repeat a few times and note the typical range.

The example firmware assumes higher readings mean drier soil. If your module behaves in the opposite direction, reverse the comparison logic.

## 2. Choose thresholds

For a sensor that reads higher when dry, choose:
- `DRY_THRESHOLD`: a value above the adequately-moist reading.
- `WET_THRESHOLD`: a lower value at which watering should stop.

Keep a gap between thresholds (hysteresis) so small fluctuations do not repeatedly toggle the relay.

Do not assume the example values (650 and 450) are correct for your setup.

## 3. Test relay without pump

1. Keep the pump battery disconnected.
2. Run the firmware.
3. Simulate dry and moist soil conditions.
4. Confirm the relay clicks ON and OFF at the intended thresholds.
5. Confirm the pump state printed in Serial Monitor matches the relay state.

## 4. Test pump

Only after sensor and relay tests pass:
1. Disconnect all power.
2. Wire the pump supply through relay COM and NO.
3. Check polarity, voltage rating, and supply current capability.
4. Secure and insulate all connections.
5. Power the Arduino first, then connect the pump supply.
6. Test briefly while supervising the system and checking for leaks or overheating.

## Test log

| Test | Soil condition | Raw reading | Expected relay | Result |
|---|---|---:|---|---|
| 1 | Dry soil | Add value | ON | Pending |
| 2 | Moist soil | Add value | OFF | Pending |
| 3 | Intermediate | Add value | Retain previous state | Pending |
