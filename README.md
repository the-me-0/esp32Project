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
* 

## Common problems
* How to get the port of the esp32 connected to your PC/laptop ?
* * Type `ls /dev/tty*` while the esp isn't connected, then execute the command another w/ the esp connected. The new tty* file (probably /dev/ttyUSB0) is your port.
* I managed to finc the port but IDF commands says it doesn't exist ?
* * It can't access th port. Execute the following commands :
* * ```bash sudo adduser <username> dialout && sudo chmod a+rw <your_port>```
