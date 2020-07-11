Installing the ESPAsyncWebServer library (if you haven't done yet)

Follow the next steps to install the ESPAsyncWebServer library:

1. Download the ESPAsyncWebServer library from https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip. You should have a .zip folder in your Downloads folder
2. Unzip the .zip folder and you should get ESPAsyncWebServer-master folder
3. Rename your folder from ESPAsyncWebServer-master to ESPAsyncWebServer
4. Move the ESPAsyncWebServer folder to your Arduino IDE installation libraries folder

Installing the Async TCP Library for ESP32 (if you haven't done yet)

The ESPAsyncWebServer library requires the AsyncTCP library to work. Follow the next steps to install that library:

1. Download the AsyncTCP library from https://github.com/me-no-dev/AsyncTCP/archive/master.zip. You should have a .zip folder in your Downloads folder
2. Unzip the .zip folder and you should get AsyncTCP-master folder
3. Rename your folder from AsyncTCP-master to AsyncTCP
4. Move the AsyncTCPfolder to your Arduino IDE installation libraries folder


Installing the Arduino ESP32 Filesystem Uploader (if you haven't done yet)

1. Go to https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/ and click the ESP32FS-1.0.zip file to download.
2. Unzip the .zip folder and you should get ESP32FS folder
3. Move the ESP32FS folder to your Ardino IDE installation tools folder. You should have a similar folder structure: <home_dir>/Arduino-<version>/tools/ESP32FS/tool/esp32fs.jar

Installing the ArduinJSON library (if you haven't done yet)
1. Open the Arduino Library Manager
2. Search for ArduinoJson
3. Select the version: 6.13.0 
4. Click install.

Installing the U8g2 library (if you haven't done yet)
1. Open the Arduino Library Manager
2. Search for U8g2
3. Select the version: 2.27.6
4. Click install.

Installing the IRremote library (if you haven't done yet)
1. Open the Arduino Library Manager
2. Search for IRremote
3. Select the version: 2.2.3
4. Click install.


Uploading Code and Files

Open the file aurora.ino in your ArduinoIDE and click on Upload.
After uploading the code, you need to upload the data files. Go to Tools > ESP32 Data Sketch Upload and wait for the files to be uploaded.