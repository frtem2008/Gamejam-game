git clone https://github.com/frtem2008/Gamejam-game
cd Gamejam-game
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel 8
cd ..\out
GamejamProg-Release.exe
