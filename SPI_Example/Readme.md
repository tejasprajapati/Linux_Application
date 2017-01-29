This application works on almost all linux based embedded device.
On raspberry pi 3 you will have to short GPIO 19 and GPIO 21 to check the loopback connection and its working status.

To compile this application we must use the gcc which is available in the Embedded device otherwise need to use the cross compiler.

To use the application with the available SPI devices,

$ ./<APP_NAME> -D /dev/spiX.x , where X is bus number and x is chip select number

To test this application in loopback mode if driver permits,

$ ./<APP_NAME> -l -D /dev/spiX.x

NOTE: USER MUST USE spidev_test.c ONLY FOR REFERENCE
