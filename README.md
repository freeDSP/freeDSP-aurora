# aurora
freeDSP with
* Analog Devices ADAU1452, 294.912 MHz, 32-bit SigmaDSP
	* 6144 SIMD instructions per sample @ 48kHz fs
	* 40kWords of data RAM
	* 800ms digital audio delay pool @ 48kHz fs
	* 8 stereo ASRCs with 139dB DNR
* XMOS XE216-512-TQ128 for multichannel bidirectional audio streaming
* ESP32 for WiFi or Bluetooth control
* AKM AK4458 32bit-DAC
* AKM AK5558 32bit-ADC
* Supporting sample rates between 44.1kHz and 192kHz
* 8 analog balanced input channels, +6dBu
* 8 analog balanced output channels, +6dBu
* S/P-DIF input and output
* ADAT input and output
* Wordclock input and output
* Support for display, rotary encoder, volume potentiometer, temperature sensor, PWM controlled fan, IR sensor
* One freeDSP expansion header
* USB Audio Class 2 Bidirectional streaming with 8 channels in and 8 channels out, full-duplex. Works with ASIO driver under Windows 10 and driverless under macOS and Linux.
* Realtime control software for Windows, macOS, Linux, iOS connecting by WiFi or Bluetooth available under an open source license
* Board dimensions: 100mm x 100mm

BOARD STATUS: BETA-TESTING

MAIN COORDINATOR: [dspverden](https://github.com/dspverden)

IMPORTANT:

Please take care on which branch you're currently working!

Branches:

master - this branch always holds the latest released revision

develop - this is the develop branch with new features

## License
This work is licensed under <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons Lizenzvertrag" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />Dieses Werk ist lizenziert unter einer <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz</a>.
