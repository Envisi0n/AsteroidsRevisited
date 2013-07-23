wget -O SFGUI_source.zip http://sfgui.sfml-dev.de/download/14
unzip SFGUI_source.zip
cd SFGUI-0.1.0-source
cmake -G "Unix Makefiles" -DSFGUI_BUILD_EXAMPLES=FALSE
sudo make install
cd ..
rm -rf SFGUI-0.1.0-source
rm SFGUI_source.zip
sudo ldconfig
