if [ $1 == "--uninstall" ]; then
    sudo rm /usr/bin/qpicospeaker
    rm -r ~/.config/qpicospeaker
else
    git submodule update --init --recursive
    rm -r ./bin
    mkdir bin
    cd bin
    qmake ../qpicospeaker.pro 
    make
    sudo mv qpicospeaker /usr/bin/
fi
