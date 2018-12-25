#https://github.com/hivesolutions/patches/blob/master/python/   ---->patchs
#https://blog.csdn.net/guchengmike/article/details/51462301 	---->follow instructions

tar jxf Python-3.2.2.tar.bz2
cd Python-3.2.2
./configure
make python Parser/pgen
mv python hostpython
mv Parser/pgen Parser/hostpgen
make distclean
patch -p1 < ../Python-3.2.2-xcompile.patch

CC=arm-xilinx-linux-gnueabi-gcc CXX=arm-xilinx-linux-gnueabi-g++ AR=arm-xilinx-linux-gnueabi-ar RANLIB=arm-xilinx-linux-gnueabi-ranlib ./configure --host=arm-none-linux-gnueabi --prefix=/python make

make HOSTPYTHON=./hostpython HOSTPGEN=./Parser/hostpgen BLDSHARED="arm-xilinx-linux-gnueabi-gcc -shared" CROSS_COMPILE=arm-xilinx-linux-gnueabi- CROSS_COMPILE_TARGET=yes

sudo mkdir ../python3.2.2-bin
sudo chmod -R 777 ../python3.2.2-bin

#make install HOSTPYTHON=./hostpython BLDSHARED="arm-xilinx-linux-gnueabi-gcc -shared" CROSS_COMPILE=arm-xilinx-linux-gnueabi- CROSS_COMPILE_TARGET=yes prefix=~/work/zynq/zynq_develop/install-python/python3.2.2-bin
make install HOSTPYTHON=./hostpython BLDSHARED="arm-xilinx-linux-gnueabi-gcc -shared" CROSS_COMPILE=arm-xilinx-linux-gnueabi- CROSS_COMPILE_TARGET=yes prefix=../python3.2.2-bin
cd ..
zip -r python3.2.2-bin.zip python3.2.2-bin/*
sudo rm -rf python3.2.2-bin
sudo rm -rf Python-3.2.2
