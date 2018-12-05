#KERN_SRC := /home/z/WORK/Linux_Digilent/linux-digilent-3.6-digilent-13.01
#KERN_SRC := /home/user/work/zed/linux
#KERN_SRC := ~/work/digilent/linux-digilent-3.6-digilent-13.01
KERN_SRC := ~/Desktop/2016.04/linux-xlnx-xilinx-v2016.4
obj-m := myled.o
all:
	make -C $(KERN_SRC)   M=`pwd` modules
clean:
	make -C $(KERN_SRC)   M=`pwd=` clean
	
