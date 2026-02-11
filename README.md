# dwm-jorink
My dwm config with some patches.

## Installing dwm-jorink

`cd ~`

`git clone https://github.com/MJorink/dwm-jorink.git`

`cd dwm-jorink`

`sudo make clean install`

`sudo pacman -S dwmbar` (Change for your distro if you don´t use an arch based distro)

Copy the 'dwmbar' folder from this repo to /usr/share/
`sudo cp -r ~/dwm-jorink/dwmbar /usr/share/`


## Running dwm

Edit the ".xinitrc" file in your /home directory. 

Add 
`exec dwmbar &
exec dwm`

Save and exit the file.

`startx`

## Configuration

The configuration of dwm is done by editing config.h
and (re)compiling the source code. (sudo make clean install)

For wallpapers: install Feh, uncomment and configure the line in .xinitrc

## Related Projects

https://github.com/MJorink/st-jorink

https://github.com/MJorink/dmenu-jorink
