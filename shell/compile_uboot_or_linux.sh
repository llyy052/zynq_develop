
 #git clone https://github.com/analogdevicesinc/linux.git 
 #git checkout xcomm_zynq 
 #cd linux
 #make zynq_xcomm_adv7511_defconfig
 #make uImage LOADADDR=0x00008000 
 #make zynq-zed-adv7511.dtb

compile_digilent=$1



digilent_uboot_folder=u-boot-digilent-digilent-v2012.04
digilent_linux_folder=linux-digilent-3.6-digilent-13.01

xilinx_uboot_folder=u-boot-xlnx-xilinx-v2016.4
xilinx_linux_folder=linux-xlnx-xilinx-v2016.4


if [ $compile_digilent == 1 ] 
then
	uboot_folder=$digilent_uboot_folder
	linux_folder=$digilent_linux_folder
else
	uboot_folder=$xilinx_uboot_folder
	linux_folder=$xilinx_linux_folder
fi

compile_uboot()
{
 echo "compile uboot"
 #cd u-boot-digilent-digilent-v2012.04
 cd $uboot_folder
 if [ $compile_digilent == 1 ]
 then
	cp ~/shell/uboot-linux-edit-file/uboot/digilent_zynq_zed.h ./include/configs/zynq_zed.h
 else
	#cp ~/shell/uboot-linux-edit-file/uboot/zynq-common.h ./include/configs/zynq-common.h
	echo "cp"
 fi

 make ARCH=arm   CROSS_COMPILE=arm-xilinx-linux-gnueabi-  zynq_zed_config
 make ARCH=arm   CROSS_COMPILE=arm-xilinx-linux-gnueabi-  menuconfig
 make ARCH=arm   CROSS_COMPILE=arm-xilinx-linux-gnueabi-  
 cp u-boot ../gen/u-boot.elf
}

compile_linux()
{
 echo "compile linux"
 cd $linux_folder
 if [ $compile_digilent == 1 ] 
 then
	cp ~/shell/uboot-linux-edit-file/linux/timeconst.pl ./kernel/timeconst.pl
	cp ~/shell/uboot-linux-edit-file/linux/digilent-zed.dts ./arch/arm/boot/dts/digilent-zed.dts
 	make  ARCH=arm  CROSS_COMPILE=arm-xilinx-linux-gnueabi- digilent_zed_defconfig  
 else
	 #cp ~/shell/uboot-linux-edit-file/linux/zynq-zed.dts ./arch/arm/boot/dts/zynq-zed.dts
	 make ARCH=arm CROSS_COMPILE=arm-xilinx-linux-gnueabi- xilinx_zynq_defconfig
 fi

 make  ARCH=arm  CROSS_COMPILE=arm-xilinx-linux-gnueabi- menuconfig
 make  ARCH=arm  CROSS_COMPILE=arm-xilinx-linux-gnueabi- UIMAGE_LOADADDR=0x8000 uImage
 if [ $compile_digilent == 1 ] 
 then
 	./scripts/dtc/dtc -I dts -O dtb -o ../gen/devicetree.dtb arch/arm/boot/dts/digilent-zed.dts
 else
	 make ARCH=arm CROSS_COMPILE=arm-xilinx-linux-gnueabi- dtbs
	 cp arch/arm/boot/dts/zynq-zed.dtb ../gen/
	 mv ../gen/zynq-zed.dtb ../gen/devicetree.dtb
 fi
 cp ./arch/arm/boot/uImage ../gen/
 cp ./arch/arm/boot/zImage ../gen/
}

 export ARCH=arm 
 export CROSS_COMPILE=arm-xilinx-linux-gnueabi-
mkdir gen
sudo chmod 777 gen

 case "$2" in
	"uboot")
		compile_uboot
		;;
	"linux")
		compile_linux
		;;
	"dts")
		cd $linux_folder
		if [ $compile_digilent == 1 ]
		then
			gedit ./arch/arm/boot/dts/digilent-zed.dts
		else
			gedit ./arch/arm/boot/dts/zynq-zed.dts
		fi
		;;
	*)
		echo "para1 error!!!!!!"
 esac

 
 
