g++ -c .\TComTrQuant.cpp
g++ -shared -o TComTrQuant.dll TComTrQuant.o
g++ -c .\scan.cpp
g++ -shared -o scan.dll scan.o