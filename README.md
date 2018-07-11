# QPicoSpeaker

QPicoSpeaker is a Qt text to speech (TTS) GUI for the pico2wave console application.

<div align="center">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker.png" width="300px" heigth="300px">
</div>

---

## Third party requirements:
* qt5 + qt5-multimedia
* pico2wave
* sox

## Install requirements:
### Debian/Ubuntu
<code>sudo apt-get install sox libttspico-utils</code>

For building you also need qt5 + multimedia packages:
<code>sudo apt-get install qt5-default qtmultimedia5-dev</code>

### Arch Linux
Form AUR e.g: <code>sudo trizen -S qpicospeaker-git</code>

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

## Future planned
* Other Linux TTS engines:
    * Connection to Google Translate TTS
    * eSpeak

## Screenshots
<div style="display: block;">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker_example1.png" width="300px" heigth="400px">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker_example2.png" width="300px" heigth="400px">
</div>


