if [ $1 == "--uninstall" ]; then
    sudo rm /usr/bin/qpicospeaker
    rm -r ~/.config/qpicospeaker
    sudo rm /usr/share/applications/qpicospeaker.desktop
    sudo rm /usr/share/pixmaps/qpicospeaker.png
else
    git submodule update --init --recursive
    rm -r ./bin
    mkdir bin
    cd bin
    qmake ../qpicospeaker.pro 
    make
    sudo mv qpicospeaker /usr/bin/
    cd ..
    sudo cp data/desktop/qpicospeaker.desktop /usr/share/applications/qpicospeaker.desktop
    sudo cp data/icons/128x128/qpicospeaker.png /usr/share/pixmaps/qpicospeaker.png
fi
