<div align="center">
  <img src="./dwm-logo-bordered.png" alt="dwm-logo-bordered" width="195" height="90"/>

  # dwm - dynamic window manager
  ### dwm is an extremely ***fast***, ***small***, and ***dynamic*** window manager for X.

</div>

---
This is my **HEAVILY MODIFIED** version of dwm. It is based on the original [suckless.org](https://dwm.suckless.org/) dwm window manager but includes a number of patches and customizations to make it more user friendly and functional out of the box.

## 📋 Install
This guide assumes your system has the latest updates before going ahead with the installation on a Arch Linux based system.

1. Launch Linutil Project with the command:
    ```bash
    curl -fsSL https://linutil.github.io/install | bash
    ```
<img width="1839" height="1000" alt="image" src="https://github.com/user-attachments/assets/314f9a40-4ccb-4c34-b3d2-dcfee63c278b" />

2. Enable Multi-Selection with key `v` and select `dwm`, `rofi`, `bash prompt`, and `ghostty` from the list.
  _Note: You can also select other packages as per your requirement._
3. Press `Enter` to start the installation. Follow the on-screen instructions to complete the installation.
4. Clone this repo `git clone https://github.com/MJorink/dwm-jorink.git`
5. `cd dwm-jorink`
6. `sudo make clean install`
7. Reboot system if needed

> [!TIP]
> - (dwm-titus) By default new terminals are opened by using the keyboard shortcut of <kbd>SUPER</kbd> + <kbd>X</kbd> while rofi is started using <kbd>SUPER</kbd>+<kbd>R</kbd>
> - For my config these are <kbd>SUPER</kbd> + <kbd>Q</kbd> for the terminal and <kbd>SUPER</kbd>+<kbd>SPACE</kbd> for rofi.
> - Check `config.h` for the keybindings, and change them according to your preference.
