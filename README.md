# udp-echo

## Install Visual Code with ESP-IDF extension

- Run Visual Code
- Install ESP-IDF extension
- Press F1
- Select ESP-IDF: Configure ESP-IDF extension

On Windows install Silicon Labs C210X USB to UART bridge driver.

## Revise hardcoded constants

- Open main/platform-defs.h
- Edit values

## Build using Visual Code

- Open project directory in the Visual Code/
- Press F1
- Select ESP-IDF: Set Espressif device target, e.g. EPS32, USB bridge
- Press F1
- Select ESP-IDF: Build your project
- Press F1
- Select ESP-IDF: Select port to use (COM, tty, usbserial)
- Press F1
- Select ESP-IDF: Flash (UART) your project

Test progrtam

Run listener
```
nc -l -u 84.237.104.128 4200
```
