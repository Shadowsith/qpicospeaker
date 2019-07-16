rm -r ./bin
mkdir bin
cd bin
qmake ../qpicospeaker.pro 
make
sudo mv qpicospeaker /usr/bin/
