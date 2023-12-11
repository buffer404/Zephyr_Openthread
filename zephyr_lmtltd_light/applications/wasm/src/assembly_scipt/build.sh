npm install
npm run build:main

echo "Generate test_wasm.h .."
./binarydump -o test_wasm.h -n wasm_test_file build/main.wasm
cp -a test_wasm.h ../test_wasm.h