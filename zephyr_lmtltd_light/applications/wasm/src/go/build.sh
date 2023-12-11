# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

WAMR_DIR=${PWD}/../../..

# /Users/mkolchurin/Projects/wasi-sdk-19.0/bin/clang -O3 -nostdlib \                                                                                                    
#     -z stack-size=8192 -Wl,--initial-memory=65536 \
#     -o test.wasm main.c \
#     -Wl,--export=main -Wl,--export=__main_argc_argv \
#     -Wl,--export=__heap_base -Wl,--export=__data_end \
#     -Wl,--no-entry -Wl,--strip-all -Wl,--allow-undefined

echo "Build wasm app .."
# tinygo build -no-debug -panic=trap -scheduler=none -o test.wasm -target wasm ./main.go 
GOOS=js GOARCH=wasm go build -o test.wasm  -ldflags "-s -w" main.go
# -compiler=gccgo
# -gcflags "-s -w"  
# -ldflags "-s -w"
# echo "Build binarydump tool .."
# rm -fr build && mkdir build && cd build
# cmake ../../../../../../../test-tools/binarydump-tool
# make
# cd ..

echo "Generate test_wasm.h .."
./binarydump -o test_wasm.h -n wasm_test_file test.wasm
cp -a test_wasm.h ../test_wasm.h

cd ../..
west flash

echo "Done"
