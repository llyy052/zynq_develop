
 #git clone https://github.com/analogdevicesinc/linux.git 
 #git checkout xcomm_zynq 
 #cd linux
 #make zynq_xcomm_adv7511_defconfig
 #make uImage LOADADDR=0x00008000 
 #make zynq-zed-adv7511.dtb

compile_digilent=0



digilent_uboot_folder=u-boot-digilent-digilent-v2012.04
digilent_linux_folder=linux-digilent-3.6-digilent-13.01

xilinx_uboot_folder=../../uboot
xilinx_linux_folder=../../linux


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
        #cp ~/shell/uboot-linux-edit-file/uboot/digilent_zynq_zed.h ./include/configs/zynq_zed.h
        echo "cp"
    else
        #cp ~/shell/uboot-linux-edit-file/uboot/zynq-common.h ./include/configs/zynq-common.h
        echo "cp"
    fi

    make ARCH=arm   CROSS_COMPILE=arm-xilinx-linux-gnueabi-  zynq_zed_config
    make ARCH=arm   CROSS_COMPILE=arm-xilinx-linux-gnueabi-  menuconfig
    make ARCH=arm   CROSS_COMPILE=arm-xilinx-linux-gnueabi-  
    
    #cp u-boot ../zynq_develop/file-gen/gen-qflash_boot_img/u-boot.elf
    #cp u-boot ../zynq_develop/file-gen/gen_boot.bin/ramdisk/u-boot.elf
    cp u-boot ../zynq_develop/file-gen/common/u-boot.elf
}

compile_linux()
{
    echo "compile linux"
    cd $linux_folder
    if [ $compile_digilent == 1 ] 
    then
        #cp ~/shell/uboot-linux-edit-file/linux/timeconst.pl ./kernel/timeconst.pl
        #cp ~/shell/uboot-linux-edit-file/linux/digilent-zed.dts ./arch/arm/boot/dts/digilent-zed.dts
        make  ARCH=arm  CROSS_COMPILE=arm-xilinx-linux-gnueabi- digilent_zed_defconfig  
    else
        #cp ~/shell/uboot-linux-edit-file/linux/zynq-zed.dts ./arch/arm/boot/dts/zynq-zed.dts
        make ARCH=arm CROSS_COMPILE=arm-xilinx-linux-gnueabi- xilinx_zynq_defconfig
    fi

    make  ARCH=arm  CROSS_COMPILE=arm-xilinx-linux-gnueabi- menuconfig
    make  ARCH=arm  CROSS_COMPILE=arm-xilinx-linux-gnueabi- UIMAGE_LOADADDR=0x8000 uImage
    if [ $compile_digilent == 1 ] 
    then
        ./scripts/dtc/dtc -I dts -O dtb -o ../zynq_develop/file-gen/gen-qflash_boot_img/devicetree.dtb arch/arm/boot/dts/digilent-zed.dts
        ./scripts/dtc/dtc -I dts -O dtb -o ../zynq_develop/file-gen/sd_image/devicetree.dtb arch/arm/boot/dts/digilent-zed.dts
    else
        make ARCH=arm CROSS_COMPILE=arm-xilinx-linux-gnueabi- dtbs
        
        #cp arch/arm/boot/dts/zynq-zed.dtb ../zynq_develop/file-gen/gen-qflash_boot_img/devicetree.dtb
        #cp arch/arm/boot/dts/zynq-zed.dtb ../zynq_develop/file-gen/sd_image/devicetree.dtb
        cp arch/arm/boot/dts/zynq-zed.dtb ../zynq_develop/file-gen/common/devicetree.dtb
    fi
    
    #cp ./arch/arm/boot/uImage ../zynq_develop/file-gen/gen-qflash_boot_img
    #cp ./arch/arm/boot/zImage ../zynq_develop/file-gen/gen-qflash_boot_img
    
    #cp ./arch/arm/boot/uImage ../zynq_develop/file-gen/sd_image
    #cp ./arch/arm/boot/zImage ../zynq_develop/file-gen/sd_image
    cp ./arch/arm/boot/uImage ../zynq_develop/file-gen/common
}

export ARCH=arm 
export CROSS_COMPILE=arm-xilinx-linux-gnueabi-


    case "$1" in
    "-uboot")
        compile_uboot
        ;;
    "-linux")
        compile_linux
        ;;
    "-dts")
        cd $linux_folder
        if [ $compile_digilent == 1 ]
        then
            gedit ./arch/arm/boot/dts/digilent-zed.dts
        else
            gedit ./arch/arm/boot/dts/zynq-zed.dts &
            gedit ./arch/arm/boot/dts/zynq-7000.dtsi &
            gedit ./arch/arm/boot/dts/zynq-zed-pl.dtsi &
        fi
        ;;
    *)
        echo "para1 error!!!!!!"
    esac

 
 
