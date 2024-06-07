HOST_TRIPLET=x86_64-w64-mingw32
sudo apt-get install mingw-w64
./autogen.sh
./configure --host $HOST_TRIPLET
make -j
