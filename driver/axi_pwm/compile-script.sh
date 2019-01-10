
make ARCH=arm   CROSS_COMPILE=arm-xilinx-linux-gnueabi-  


rm ./*.symvers
rm ./*.order
rm ./*.o
rm ./*.mod.c
#rm ./*.cmd
rm -rf ./.*

cd test
sh compile.sh
cd ..
