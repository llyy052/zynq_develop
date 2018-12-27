echo "------start init.sh-----------"

mknod /dev/myled c 244 0
insmod /mnt/myled.ko
#/mnt/ledtest&

echo "------init.sh finish----------"
