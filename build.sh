#! /bin/bash
INCLUDES="-I Collections/include -I Math/include"
LINKS="-LCollections -LMath -lkc -lklm"
FLAGS="-Wall -Wextra -Wpedantic"
make clean

TARGET=$1
if [[ $TARGET = emcc ]]; then
	echo "build for emscripten"
	echo "emcc $FLAGS Collections/src/*.c Math/src/*.c src/*.c $INCLUDES -o wasm/KGE.js"
	emcc src/main.cpp Collections/src/*.c Math/src/*.c src/*.c $INCLUDES -o KGE.js \
		-sEXPORTED_FUNCTIONS=_main,_kge_init,_kge_update,_kge_cleanup -sEXPORTED_RUNTIME_METHODS=cwrap \
		--js-library jslib/lib.js
	mv KGE.js wasm/KGE.js
	mv KGE.wasm wasm/KGE.wasm
elif [[ $TARGET = cheerp ]]; then
	echo "build for cheerp"
	echo "/opt/cheerp/bin/clang++ -target cheerp-wasm src/main.cpp Collections/src/*.c Math/src/*.c src/*.c $INCLUDES -o KGE.js"
	/opt/cheerp/bin/clang++ -O0 -target cheerp-wasm -cheerp-linear-output=wasm -cheerp-linear-heap-size=64 src/*.cpp Collections/src/*.cpp Math/src/klm.cpp $INCLUDES -o KGE.js
	mv KGE.js wasm/KGE.js
	mv KGE.wasm wasm/KGE.wasm
	mv KGE.js.map wasm/KGE.js.map
else
	echo "build for term"
	echo "RUN CMAKE"
	cmake . && cmake --build .
	g++ -c src/main.cpp -o build/main.o $INCLUDES

	echo "g++ build/main.o libKGE.a $LINKS -o KGE $INCLUDES"
	g++ $FLAGS build/main.o libKGE.a $LINKS -o KGE $INCLUDES
fi


