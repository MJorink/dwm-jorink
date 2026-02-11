#
# ~/.bash_profile
#

[[ -f ~/.bashrc ]] && . ~/.bashrc

export PATH=$PATH:/home/jorink/.spicetify
# Auto-restart X when it exits
if [[ -z $DISPLAY ]] && [[ $(tty) == /dev/tty1 ]]; then
    while true; do
        startx
        sleep 1
    done
fi