#! /bin/bash
INCLUDES="-I Collections/include -I Math/include"
LINKS="-LCollections -LMath -lkc -lklm"
echo "RUN CMAKE"
cmake .
make
g++ -c src/main.cpp -o build/main.o $INCLUDES
echo "g++ build/main.o libKGE.a $LINKS -o KGE $INCLUDES"
g++ build/main.o libKGE.a $LINKS -o KGE $INCLUDES
