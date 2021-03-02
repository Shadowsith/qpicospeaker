[![Build status](https://ci.appveyor.com/api/projects/status/c0vgtl5t23s1axq0?svg=true)](https://ci.appveyor.com/project/Shadowsith/qpicospeaker)

# QPicoSpeaker

QPicoSpeaker is a Qt text to speech (TTS) GUI for the pico2wave console application.

<div align="center">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker.png" width="300px" heigth="300px">
</div>

---

## Motivation
I had sound problems with the Gespeaker UI for espeak and I also was unhappy with the robotic sounds from espeak.<br>
As better solution for the unstatisfied TTS situation on the Linux desktop I develop this application.<br>

## Third party requirements:
* qt5 + qt5-multimedia
* pico2wave
* sox
* mplayer for Google TTS

## Install requirements:
### Debian/Ubuntu
<code>sudo apt-get install sox mplayer libttspico-utils</code>
<code>sudo apt-get install libqt5multimedia5-plugins</code>

For building you also need qt5 + multimedia packages:<br>
<code>sudo apt-get install qt5-default qtmultimedia5-dev</code>

* `git clone https://github.com/Shadowsith/qpicospeaker`
* `cd qpicospeaker`
* `sudo ./install.sh`

Install paths:
* Binary: /usr/bin/qpicospeaker
* Config: /home/\<user\>/.config/qpicospeaker/config.xml

To uninstall QPicospeaker write ./install.sh --uninstall

If the project is in a more finished state there will be a package in the Ubuntu launchpad too.

### Arch Linux
There is a offical maintained package in the AUR:
<code>yay -S qpicospeaker-git</code>

### Tested Systems
* Manjaro/Arch Linux (KDE)
* Ubuntu (MATE) 18.04

## Supported languages (TTS):
* English (US)
* English (UK)
* German
* Spain
* French
* Italian

## Implemented features
* Write a text in the textinput and let it say from the TTS engine
* Change **speak, loudness and pitch** form the TTS software
* Load/save textfile form/to textinput field
* Save output file to the location what you want
* Logo/Icon
* Connection to Google Translate TTS engine

## Upcomming features
* Default Settings
* Translation to other languages
* All Languages for Google TTS
* removing mplayer to curl
* resizing UI
* Help documentation

## Future planned
* eSpeak speech synthesizer as alternative to pico2wave and Google
* IBM Watson TTS support

## Restictions
* no male voice for Google TTS (no acces about connection string possible)

## Screenshots
<div style="display: block;">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker_example1.png" width="300px" heigth="400px">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker_example2.png" width="300px" heigth="400px">
</div>

## License
* Project is free software and licensed under GPLv3+
* Logo and GIMP Project are public domain (CC0)

