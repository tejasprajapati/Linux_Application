i2c_dev.h file is required only when we are using smbus protocol, smbus protocol will make it easy to handle things on i2c bus as you are required to send any kind address and data with start and stop signals.

SMBUS protocol is preferable over RAW i2c. Have no idea for BBB but it has to support, moreover if it does not by default then we can use the provided i2c_dev.h file.
