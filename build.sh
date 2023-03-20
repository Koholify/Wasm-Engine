#! /bin/bash
INCLUDES="-I Collections/include -I Math/include"
LINKS="-LCollections -LMath -lkc -lklm"
cmake . && cmake --build .

TARGET=$1
if [[ $TARGET = emcc ]]; then
	echo "build for emscripten"
	echo "emcc Collections/src/*.c Math/src/*.c src/*.c $INCLUDES $LINKS -o wasm/KGE.js"
	emcc src/main.cpp Collections/src/*.c Math/src/*.c src/*.c $INCLUDES $LINKS -o KGE.js \
		-sEXPORTED_FUNCTIONS=_main,_kge_init,_kge_update,_kge_cleanup -sEXPORTED_RUNTIME_METHODS=cwrap
	mv KGE.js wasm/KGE.js
	mv KGE.wasm wasm/KGE.wasm
else
	echo "build for term"
	echo "RUN CMAKE"
	g++ -c src/main.cpp -o build/main.o $INCLUDES

	echo "g++ build/main.o libKGE.a $LINKS -o KGE $INCLUDES"
	g++ build/main.o libKGE.a $LINKS -o KGE $INCLUDES
fi


