call PATH.bat

cd g++11
g++ LargeVis.cpp main.cpp -o ../LargeVis ANNOY/mman.cpp -Ofast -march=native -ffast-math -DWINDOW
cd ..
pause