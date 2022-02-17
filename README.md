OKUR is a small and basic Chip8 Emulator written in C++, made for fun and my high school
assignment.


# What is implemented now :

- All Chip8 Instructions.
- Video Output.
- Sound Output.
- Keyboard Input.


# What is not implemented :

- Super Chip48 OPCODES.



If you are on a Linux based system, run these following commands to build the project :



First, you will need SDL2 and SDL2_Mixer :



On Arch :


```
$ pacman -Sy sdl2 sdl2_mixer
```


On Fedora :


```
$ sudo dnf install SDL2 SDL2-devel SLD2_mixer SDL2_mixer-devel
```


On Debian/Ubuntu :


```
$ sudo apt-get install libsdl2 libsdl2-dev libsdl2-mixer libsdl2-mixer-dev
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
$ cd bin
$ ./okur /path/to/the/rom
```


Now, if you are on a Windows system you should use prebuilt binary on the Release section :
(Windows build is out of date ! Don't use it !)


https://github.com/yann-boyer/OKUR/releases/tag/V1.0



Copyright (c) 2022 - Yann BOYER.
