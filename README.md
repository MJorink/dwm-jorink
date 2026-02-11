# dwm-jorink
My dwm config with some patches.

## Installing dwm-jorink

`git clone https://github.com/MJorink/dwm-jorink.git`

`cd dwm-jorink`

`sudo make clean install`

`yay -S dwmbar` (Change for your distro if you don´t use an arch based distro)


## Running dwm

Edit the ".xinitrc" file in your /home directory. 

Add `exec dwm`

Save and exit the file.

`startx`

## Configuration

The configuration of dwm is done by editing config.h
and (re)compiling the source code. (sudo make clean install)

## Related Projects

https://github.com/MJorink/st-jorink

https://github.com/MJorink/dmenu-jorink
