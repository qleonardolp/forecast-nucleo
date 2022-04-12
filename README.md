# ForecastNucleoFramework test

## Get the build system
1. Install [Visual Studio Code](https://code.visualstudio.com/). On Ubuntu 20.04 or later an easy to install snap is also available

    ```bash
    sudo snap install code --classic
    ```
    Notice the sudo command which will ask for root user privileges

2. Get the [PlatformIO](https://platformio.org/platformio-ide) VSCode extension following the instructions on the given link.

    If you are having issues on this step please ensure you have python3 and python3-venv installed.
    ```bash
    sudo apt install python3-venv
    ```
3. Install Git.
    To get the firmware you are required to clone and navigate git repositories. Ensure you machine has Git installed by typing
    ```bash
    git --version
    ```
    If you get an error message make sure to install git. For example on Ubuntu it's sufficient to type
    ```bash
    sudo apt install git
    ```

## Get the firmware

1. Clone this repository and enter the directory. Do so by typing in the terminal:
```bash
git clone -b NEXT https://gitlab.com/altairLab/elasticteam/ForecastNucleoFramework-test.git forecast-mbed

cd forecast-mbed
```

2. Enter the 'lib' directory and clone the main framework
```bash
cd lib

git clone -b develop-next https://gitlab.com/altairLab/elasticteam/forecastnucleoframework
```

## Start VSCode

Open VSCode and then File > Open Folder...
Select the forecast-mbed directory created beforehand (the root of the PlatformIO project, NOT the one in the 'lib' directory).

## Upload the code

When you are done developing, make sure to upload the firmware.
Do so by accessing the PlatformIO extension from the VSCode Extension Toolbar and then:
1. Select 'workbench-release' from the Project Tasks menu.
2. Select General > Upload
3. Wait for the upload to be completed.
4. Connect to the board from the user interface.