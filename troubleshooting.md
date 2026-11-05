# Troubleshooting

## Relay never turns ON
- Confirm relay VCC and GND.
- Confirm the relay input is connected to D8.
- Verify whether the module is active-LOW or active-HIGH.
- Verify that the sensor reading crosses `DRY_THRESHOLD`.
- Check that the relay input is compatible with Arduino logic levels.

## Relay never turns OFF
- Check whether the sensor reading falls below `WET_THRESHOLD`.
- Confirm sensor AO is connected to A0.
- Recalibrate thresholds using real soil.
- Check for a stuck relay or incorrect active level.

## Relay chatters rapidly
- Increase the gap between dry and wet thresholds.
- Ensure sensor wiring is secure.
- Avoid calibrating while the probe is moving between media.

## Arduino resets when pump starts
- Do not power the pump from Arduino 5V or USB.
- Use a separate pump supply with sufficient startup current.
- Keep motor wiring away from sensor wiring.
- Check relay contact ratings and motor suppression.

## Power bank switches off
Some power banks shut down when the load is very small. Try another USB output or a regulated 5V supply that remains on at low load. Do not add improvised dummy loads without checking their power dissipation and safety.
