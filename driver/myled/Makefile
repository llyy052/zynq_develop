#KERN_SRC := /home/z/WORK/Linux_Digilent/linux-digilent-3.6-digilent-13.01
#KERN_SRC := /home/user/work/zed/linux
#KERN_SRC := ~/work/digilent/linux-digilent-3.6-digilent-13.01
KERN_SRC := ~/work/zynq/linux
obj-m := myled.o
all:
	make -C $(KERN_SRC)   M=`pwd` modules
clean:
	make -C $(KERN_SRC)   M=`pwd=` clean
	
