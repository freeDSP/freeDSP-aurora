SET port=COM7

ECHO OFF
ECHO "Connect pin 5 with pin 6 on X504. Then press and release SW501 before you continue"
PAUSE

esptool.exe --chip esp32 --port %1 --baud 921600 erase_flash

ECHO "Press and release SW501 before you continue"
PAUSE

esptool.exe --chip esp32 --port %1 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0xe000 boot_app0.bin 0x1000 bootloader_qio_80m.bin 0x10000 aurora.ino.esp32.bin 0x8000 aurora.ino.partitions.bin

ECHO ON