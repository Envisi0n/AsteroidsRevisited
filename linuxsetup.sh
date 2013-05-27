sudo apt-get install cmake libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew-dev libjpeg8-dev libsndfile1-dev libopenal-dev
wget http://www.sfml-dev.org/download/sfml/2.0/SFML-2.0-sources.zip
unzip SFML-2.0-sources.zip
cd SFML-2.0
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=TRUE 
make
sudo make install
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=TRUE
make
sudo make install
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=FALSE
make
sudo make install
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=FALSE
make
sudo make install
cd ..
sudo ldconfig
rm SFML-2.0-sources.zip
rm -rf SFML-2.0
