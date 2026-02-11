echo "5 Second warning:"
sleep 0.1
echo "This script is experimental, bad, untested, and meant for personal use, there will be configs that are made for my setup that need changing for others!"
sleep 0.1
echo "Also, make sure you have 'yay' installed"
sleep 0.1
echo "Press CTRL+C to quit, or wait 5 seconds to continue."
echo "."
sleep 1
echo ".."
sleep 1
echo "..."
sleep 1
echo "...."
sleep 1
echo "....."
sleep 1

echo ""
echo "Installing dependencies"
sudo pacman -Sy --noconfirm base-devel git xorg-server xorg-xinit ttf-meslo-nerd power-profiles-daemon
yay -Sy --noconfirm feh dwmbar i3lock-color brightnessctl gnome-keyring chromium thunar 

echo ""
echo "Temporarily set power profile to performance"
powerprofilesctl set performance
powerprofilesctl get

echo ""
echo "Building and installing dwm-jorink"
sudo make clean install

echo ""
echo "Setting up configs"
sudo cp -r extras/.config ~/
sudo cp -r extras/.local ~/
sudo cp -r extras/dwmbar /usr/share/dwmbar
sudo cp -r .bash_profile ~/
sudo cp -r .xinitrc ~/
echo ""
echo ""
echo "If you use micro, I have a WIP theme in extras/Amber-Glow-Micro, be sure to read the README.md"
echo ""
echo ""
echo "If you use VSCode, I have a WIP theme in extras/Amber-Glow-VSCode, be sure to read the README.md"
sleep 0.5

echo ""
echo "Setting up service"
systemctl --user enable power-monitor.service
sleep 0.2
systemctl --user start power-monitor.service
sleep 0.2
systemctl --user status power-monitor.service

echo ""
echo "Setting up st-jorink"
cd ~
git clone https://github.com/MJorink/st-jorink
cd st-jorink
sudo make clean install

echo ""
echo "Setting up dmenu-jorink"
cd ~
git clone https://github.com/MJorink/dmenu-jorink
cd dmenu-jorink
sudo make clean install

echo ""
echo "Setting up .bashrc"
cd ~
git clone https://github.com/MJorink/bashrc
cd bashrc
sudo cp -r .bashrc ~/
yay -Sy lolcat toilet

echo ""
echo "Set power profile to balanced"
powerprofilesctl set balanced
powerprofilesctl get

echo ""
echo "Installation done!"
echo "Rebooting in 5"
sleep 1
echo "Rebooting in 4"
sleep 1
echo "Rebooting in 3"
sleep 1
echo "Rebooting in 2"
sleep 1
echo "Rebooting in 1"
sleep 1
echo "Rebooting now"
reboot
