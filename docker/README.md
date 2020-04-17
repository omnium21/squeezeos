# Build squeezeos image

## Build docker image

You need docker up and running on your machine. 

```sh
cd docker
./build_and_run.sh
```

At this point, a docker container will be build bases on Dockerfile. It will download Ubuntu 12.04 aswell as all necessary packages needed to build Squeezeos image.
Once build is done, it should logged in inside the container, and you will be able build squeezeos for you machine.

A dedicated user `squeezeos` is created and he content of the current directory is also mouted inside the container

```
cd poky
source poky-init-build-env

```


# Squeezebox Controller (jive)

By default jive image is built.
```
bitbake squeezeos-image
```

After a long time depending on your machine CPU you should find the final image inside poky/build/tmp-jive/deploy/images

# Squeezebox Radio (baby)
you need to change the MACHINE in local.conf configuration file

```
MACHINE?="baby"
```


# Error during build

If you encountered an error related to -ltinfo not found :

```
| make[1]: Entering directory `/home/squeezeos/poky/build/tmp-jive/work/armv5te-none-linux-gnueabi/alsa-utils-1.0.18-r0/alsa-utils-1.0.18/alsamixer'
| arm-none-linux-gnueabi-gcc -march=armv5te -mtune=arm926ej-s -mthumb-interwork -mno-thumb --sysroot=/home/squeezeos/poky/build/tmp-jive/staging/armv5te-none-linux-gnueabi -DCURSESINC="<ncurses.h>" -fexpensive-optimizations -fomit-frame-pointer -frename-registers -O2 -ggdb -feliminate-unused-debug-types  -Wl,-O1 -o alsamixer alsamixer.o -lncurses -ltinfo -lasound -lm -ldl -lpthread
| /home/squeezeos/poky/build/tmp-jive/cross/armv5te/bin/../lib/gcc/arm-none-linux-gnueabi/4.4.1/../../../../arm-none-linux-gnueabi/bin/ld: cannot find -ltinfo
| collect2: ld returned 1 exit status
| make[1]: *** [alsamixer] Error 1
| make[1]: Leaving directory `/home/squeezeos/poky/build/tmp-jive/work/armv5te-none-linux-gnueabi/alsa-utils-1.0.18-r0/alsa-utils-1.0.18/alsamixer'
| make: *** [all-recursive] Error 1
| FATAL: oe_runmake failed
```

Edit the Makefile :
emacs /home/squeezeos/poky/build/tmp-jive/work/armv5te-none-linux-gnueabi/alsa-utils-1.0.18-r0/alsa-utils-1.0.18/alsamixer/Makefile
and remove all occurence of -ltinfo and relaunch the build.