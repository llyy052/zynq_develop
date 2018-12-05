
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


int main(int argc, char **argv)
{
    int fd;

   int val ;//=0x0AA;

    //fd = open("/dev/myled", O_RDWR);
    fd = open("/sys/module/myled", O_RDWR);

    if (fd<0)
    {
        printf("error, can't open\n");
        return 0;
    }

while(1) {
    read (fd , &val , 4);
    val++;
    write(fd , &val , 4);
    sleep(1);
}
    close (fd);
    return 0;
}



