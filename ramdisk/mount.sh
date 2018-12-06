

mount_ramdisk()
{
	echo "mount_ramdisk"
	gunzip ramdisk.image.gz

	chmod u+rwx ramdisk.image
	mkdir tmp_mnt/
	sudo mount -o loop ramdisk.image tmp_mnt/
	sudo chmod -R 777 tmp_mnt/
}

umount_ramdisk()
{
	echo "umount_ramdisk"
	sudo umount tmp_mnt/
	gzip ramdisk.image
	rm -rf tmp_mnt
	#rm tmp_mnt
	#mkimage -n 'uboot ext2 ramdisk' -A arm -O linux -T ramdisk -C gzip -d ramdisk.image.gz ../gen/uramdisk.image.gz
	mkdir gen
	sudo chmod 777./gen
	mkimage -n 'uboot ext2 ramdisk' -A arm -O linux -T ramdisk -C gzip -d ramdisk.image.gz ./gen/uramdisk.image.gz
}


case "$1" in
	"-u")
		umount_ramdisk
		;;
	*)
	mount_ramdisk
esac


