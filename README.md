# ArduinoTimeLapse
Use Arduino as a camera remote to create time lapses. <br>
This code is for Nikon cameras only.

## Usage
You can set the time between photos changing the `LapseTime` value which is expressed in milliseconds.
Default is set to 5 seconds.

## Arduino Setup

The final setup looks like this:

[![ArduinoSetup](https://s29.postimg.org/6hazrmfp3/Nikon_Time_Lapse.png)](https://postimg.org/image/pme91ducz/)

Arduino has a normal LED connected to pin 5 (you can change it throug `LEDPin`) with a small resistence, and an IR LED connected to pin 3 (you can change it throug `IRPin`) also with a small resistence.

The IR LED should be directed to the IR sensor of the camera.
The colored LED signals to the user the moment the IR signal is sent.

This is the setup:

[![Final Setup](https://s27.postimg.org/z0lf8jaz7/2016_05_28_19_33_25.jpg)](https://postimg.org/image/e3p73vcy7/)
