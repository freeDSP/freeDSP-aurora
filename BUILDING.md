# Software build instructions

If you just want to use the Aurora in your project, please use the pre-built releases instead of building your own firmware (this is **not** necessary for creating your own plugins).
But if you want to assist with development by contributing code, you will find the Aurora actually runs three firmwares:

1. **ESP32**: Runs the primary program which controls everything else, and offers the WiFi interface. Probably the most interesting of the bunch. See [this document](SOURCES/WEBAPP/ESP32/README.md) for more details and how to build.
2. **ADAU1452**: The DSP firmware is build using SigmaStudio. The firmware is stored on the ESP32 as part of the installed plugin.
3. **XMOS**: The USB interface comes with a 7.1 firmware pre-installed; if you want to change this, you need to build your own firmware.

Please note that a complete Aurora Plugin consists of a DSP firmware image, an associated control website and some meta-data.
The actual XMOS and ESP32 firmware are not modified by plugins.
