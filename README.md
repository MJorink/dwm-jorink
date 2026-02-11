# dwm-jorink
My dwm config with some patches.

Meant for personal use, for learning dwm. I have it uploaded here for archival purposes.

## Dependencies
1. yay
2. `yay -Sy --noconfirm base-devel git xorg-server xorg-xinit ttf-meslo-nerd power-profiles-daemon feh dwmbar i3lock-color spotify vesktop brightnessctl gnome-keyring chromium thunar proton-authenticator-bin bitwarden`

## Installing dwm-jorink

- `cd ~`
- `git clone https://github.com/MJorink/dwm-jorink.git`
- `cd dwm-jorink`
- `sudo make clean install`

Copy/move the 'dwmbar' folder from extras to /usr/share/

Copy/move the other stuff in extras to ~/ (Dont forget hidden .files!)

## Running dwm

`startx`

dwm will automatically start when logging into tty1 if you copied the files from extras
- `reboot`
- log in to tty1

## Configuration

The configuration of dwm is done by editing config.h
and (re)compiling the source code. (sudo make clean install)

## Related Projects

https://github.com/MJorink/st-jorink

https://github.com/MJorink/dmenu-jorink
