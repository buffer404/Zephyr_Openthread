 
 cd src/wasm-app-riscv64/
 ./build.sh
#  wasm-app-riscv64 or go assembly_scipt/
 cd ../..

 west build -b SOVA427 .\
 -p auto -- \
 -DWAMR_BUILD_TARGET=THUMBV7
#  . 

west flash
# west build -t run
#  nucleo_h743zi