# esp32Project
First try out of the esp32 : get the co2, humidity, and temperature from sensors. More features later



# How to create a new project
*This list will help create a new project using esp-idf and visual studio code*
*https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html*
### Platform : Linux Kubuntu KDE plasma 5.25.5

* Installing needed packages
`sudo apt-get install git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0`
* Install IDF
```bash
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```
* Add the target chip(s)
```bash
cd ~/esp/esp-idf
./install.sh esp32,esp32s2
```
* Place yourself in the directory where you're gonna use IDF and execute this command
`. $HOME/esp/esp-idf/export.sh`
* That's it !

# Using IDF in a project
* You can flash (the flash command build, then flashes) your project using the command : `idf.py -p <your_port> flash`
* You can monitor your project using : `idf.py -p <your_port> monitor` then leave using **Ctrl+]** (your project need to be flashed first)
* You can use idf inside **VS Code** by adding the extension *Espressif IDF* and setting up the [extension](https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md).
* You can try this example project to blink the integrated led : https://github.com/espressif/esp-idf/tree/master/examples/get-started/blink

## IDF in command lines
* `. $HOME/esp/esp-idf/export.sh`
* `idf.py create-project` *this line creates an empty project*
* `idf.py set-target <your-target>` *target can be esp32, esp32s2...*
* `idf.py -p <your port> build` *builds the project*
* `idf.py -p <your port> flash` *build & flash the project on the esp*
* `idf.py -p <your port> flash monitor` *build & flash & monitor the project, viewing what the esp code returns in a terminal*

## Common problems
* How to get the port of the esp32 connected to your PC/laptop ?
* * Type `ls /dev/tty*` while the esp isn't connected, then execute the command another w/ the esp connected. The new tty* file (probably /dev/ttyUSB0) is your port.
* I managed to finc the port but IDF commands says it doesn't exist ?
* * It can't access th port. Execute the following commands :
* * ```bash sudo adduser <username> dialout && sudo chmod a+rw <your_port>```