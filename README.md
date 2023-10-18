# OneWire Serial Port Via CH32V003

* [Introduction](https://github.com/TianpeiLee/OneWireUSART#Introduction)<br>
* [Hardware Connection](https://github.com/TianpeiLee/OneWireUSART#Hardware-Connection)<br>


## Introduction

This is an example of converting a two line serial port to a single line bidirectional serial port via CH32V003,
You can also refer to this [link](https://github.com/AlkaMotors/AM32-MultiRotor-ESC-firmware/wiki/Arduino-PC-Link) to implement with an Arduino by BLHeliSuite, 
or refer to [BLHheli 1wire code](https://drive.google.com/file/d/1mNtyFT8vCCuluOSboFM-9JDNLDlwlLS8/view) to implement with other chips.



## Hardware Connection

USB serial port adapter --- CH32V003 <br>
 VCC     ---     VCC<br>
 GND     ---     GND<br>
 RX      ---     PD5<br>
 TX      ---     PD6<br>
 
 CH32V003   ---      ESC<br>
 GND        ---      GND<br>
 PC1        ---      SI<br>