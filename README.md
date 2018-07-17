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

## Install requirements:
### Debian/Ubuntu
<code>sudo apt-get install sox libttspico-utils</code>

For building you also need qt5 + multimedia packages:<br>
<code>sudo apt-get install qt5-default qtmultimedia5-dev</code>

If the project is in a more finished state there will be a package in the Ubuntu launchpad too.

### Arch Linux
There is a offical maintained package in the AUR:
<code>trizen -S qpicospeaker-git</code>

### Tested Systems
* Manjaro/Arch Linux
* Ubuntu 18.04

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

## Upcomming features
* Translation to other languages
* Connection to Google Translate TTS

## Future planned
* eSpeak speech synthesizer as alternative to pico2wave and Google

## Screenshots
<div style="display: block;">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker_example1.png" width="300px" heigth="400px">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker_example2.png" width="300px" heigth="400px">
</div>

## License
* Source code is licensed under MIT 
* Logo and GIMP Project are public domain (CC0)

