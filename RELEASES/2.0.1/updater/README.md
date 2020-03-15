Updating Aurora DSP with a new binary.

Step 1
Connect your USB2Serial converter to your Aurora DSP. See the UserManual_1.1.1.pdf regarding the required wire connections.

Step 2
Open a terminal and change to directory: <path to repository>/SOURCES/WEBAPP/ESP32/updater

Step 3
On macOS you may have to make the install script executable by typing chmod +x update.sh

Step 4
On macOS execute the firmware update by running ./update.sh <your_com_port>
On Win10 execute the firmware update by running update.bat <your_com_port>
Replace <your_com_port> with the name of your USB2Serial converter, e.g. /dev/cu.SLAB_USBtoUART on macOS or COM7 on Win10.

Step 5
Follow the instructions on your screen.