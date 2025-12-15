# Installation
## Install Arduino CLI
Go to arduino-cli [release page](https://github.com/arduino/arduino-cli/releases/). Choose the latest installer. Download and install it.
## Install VS Code (Windows)
Run from terminal:
```
winget install -e --id Microsoft.VisualStudioCode
```
## Install Platform Extension
Open VS Code. Press `Ctrl+P`. Run:
```
ext install platformio.platformio-ide
```

# Configuration the board

Connect the board and choose 1200 bitrate in the assigned COM port through Device Manager.

# Configuration VS Code project

Click on PlatformIO button on the right panel. Choose "Open" button in the appeared window. Create new project. Choose board "Arduino Leonardo".

# Notes

https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/all
