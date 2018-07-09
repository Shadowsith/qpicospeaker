# QPicoSpeaker

QPicoSpeaker is a Qt text to speech (TTS) GUI for the pico2wave console application.

<div align="center">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker.png" width="300px" heigth="300px">
</div>

---

## Third party requirements:
* pico2wave
* sox

## Install requirements:
### Debian
<code>sudo apt-get install sox libttspico-utils</code>

### Ubuntu
<code>sudo apt-get install sox libttspico-utils</code>

### Arch Linux
From AUR: [svox-pico-bin](https://aur.archlinux.org/packages/svox-pico-bin/)<br>
E.g. <code>trizen -S svox-pico-bin && sudo pacman -S sox</code>

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

## Upcomming features
* Load/save textfile form/to textinput field
* Save output file to the location what you want
* Logo/Icon

## Future features
* Translation to other languages
* Other Linux TTS engines:
    * Connection to Google Translate TTS
    * eSpeak

## Screenshots
<div style="display: block;">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker_example1.png" width="300px" heigth="400px">
   <img src="https://shadowsith.de/qpicospeaker/qpicospeaker_example2.png" width="300px" heigth="400px">
</div>


