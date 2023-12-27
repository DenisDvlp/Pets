# Installation
## Install Arduino CLI
Go to arduino-cli [release page](https://github.com/arduino/arduino-cli/releases/). Choose the latest installer. Download and install it.
## Install VS Code (Windows)
Run from terminal:
```
winget install -e --id Microsoft.VisualStudioCode
```
## Install Arduino Extension
Open VS Code. Press `Ctrl+P`. Run:
```
ext install vscode-arduino
```
# Configuration
## Configure Arduino Extension
### Install Board Manager
1. Open VS Code. Press `F1`. Type and run
    ```
    Arduino: Board Manager
    ```
2. Select needed board manager and click `Install` button.
### Configure Board
1. Open VS Code. Press `F1`. Type and run:
    ```
    Arduino: Board Config
    ```
2. Select needed board from dropdown list.

As a successful result `.vscode/arduino.json` file should appear.
# Create a sample project
Note: There is a known limitation in `arduino-cli`. Name of the root directory shall **match** the name of the main `.ino` file. E.g.: `my_sketch/my_sketch.ino`.
## Make a Project
1. Create a main sketch file `my_sketch.ino` in `my_sketch` directory with the following content.
    ```
    void setup() {}
    void loop() {}
    ```
## Verify file
1. Open `my_sketch` directory in VS Code.
2. Press `F1`. Type and run:
    ```
    Arduino: Verify
    ```
3. Choose `my_sketch.ino` from the popup list.

As a successful result `.vscode/c_cpp_properties.json` file should appear and the terminal output should indicate:
```
[Done] Verifying sketch 'my_sketch.ino'
```
