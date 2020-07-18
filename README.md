![FreeDSP logo](https://github.com/freeDSP/WIKI-AND-GENERAL-TOPICS/raw/master/LOGOs/freeDSP/freeDSP%20LOGO/freeDSP_LOGO.png)

# freeDSP aurora

An open source and open hardware [freeDSP](https://freedsp.github.io) board based on ADAU1452 with 8 analog I/O, S/P-DIF I/O, ADAT I/O, USB Audio, WiFi, Bluetooth.

It supports various and convenient physical addons and multiple software plugins, and is controlled by web interface.


## Main features

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
* Realtime control software over WiFi or Bluetooth available under an open source license
* THD DAC: -103dB @ 1kHz, 0dBfs, fs=48kHz
* THD ADC: -101dB @ 1kHz, 0dBfs, fs=48kHz
* Latency: 1.125ms (talkthrough ADC->DSP->DAC)
* Board dimensions: 110mm x 110mm

MAIN COORDINATOR: [dspverden](https://github.com/dspverden)


## Contributing

**Please take care on which branch you're currently working!**

Branches:

- *master* - this branch always holds the latest released revision
- *develop* - this is the develop branch with new features. Please base your patches on this branch.

[Build instructions](BUILDING.md) | [Addons](ADDONS/README.md) | [User Documentation](DOCUMENTATION/)


## License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.

## Links

- [Buy Aurora board and addons](https://auverdion.de/)
- [freeDSP](https://freedsp.github.io)
- [Kickstarter campaign](https://www.kickstarter.com/projects/auverdion/freedsp-aurora-dsp)
- [DIYAudio forum (english)](https://www.diyaudio.com/forums/digital-line-level/334055-freedsp-aurora-dsp-8-os-usb-audio-dif-adat-bluetooth-wifi-contro.html)
- [DIYHifi forum (german, features)](https://www.diy-hifi-forum.eu/forum/showthread.php?18572-freeDSP-aurora-Der-Feature-Thread)
- [DIYHifi forum (german, specs)](https://www.diy-hifi-forum.eu/forum/showthread.php?15019-Verst%E4rkermodul-mit-DSP-600W-1-4Kan%E4le-low-budget-high-quality&p=249786&viewfull=1#post249786)
- [Youtube tutorials](https://www.youtube.com/channel/UCGmSGSIjvFPSlGyMbqJgFxw)
- [ADAU1452 at Analog Devices](https://www.analog.com/en/products/adau1452.html)
- [ESP32 at Espressif](https://www.espressif.com/en/products/socs/esp32/overview)
- [XMOS XE216-512-TQ128 datasheet](https://www.xmos.com/file/xe216-512-tq128-datasheet)
- [AKM 4458](https://www.akm.com/us/en/products/audio/audio-dac/ak4458vn/)
- [AKM 5558](https://www.akm.com/us/en/products/audio/audio-adc/ak5558vn/)
