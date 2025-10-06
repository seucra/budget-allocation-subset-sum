rm -rf build
mkdir build && cd build


cmake ..
cmake --build .

and run ./solver -n 1,2,3,4,5 -t 6 --algo backtrack --find-all

send main.cpp in src to cgpt and ask what else cli it can do
