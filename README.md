OKUR is a small and basic Chip8 Emulator written in C++, made for fun and my high school
assignment.



If you are on a Linux based system, run these following commands to build the project :



First, you will need SDL2 :



On Arch :


```
$ pacman -Sy sdl2
```


On Fedora :


```
$ sudo dnf install SDL2 SDL2-devel
```


On Debian/Ubuntu :


```
$ sudo apt-get install libsdl2 libsdl2-dev
```


Now, you can build the project :


```
$ git clone https://github.com/yann-boyer/OKUR.git
$ cd OKUR
$ chmod +x build_linux.sh
$ ./build_linux.sh
```


Now, you can run OKUR :


```
$ ./okur /path/to/the/rom
```


Now, if you are on a Windows system you should use prebuilt binary on the Release section.



Copyright (c) 2022 - Yann BOYER.
