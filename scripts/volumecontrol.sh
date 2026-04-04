#!/usr/bin/env bash
case $1 in
    up)   amixer set Master 10%+ > /dev/null ;;
    down) amixer set Master 10%- > /dev/null ;;
    mute) amixer set Master 0 > /dev/null ;;
esac
STATUS=$(amixer get Master | awk -F'[][]' '/Left:/ { print $4 }') # [on] or [off]
VOL=$(amixer get Master | awk -F'[][]' '/Left:/ { print $2 }' | tr -d '%')
if [ "$STATUS" = "off" ]; then
    dunstify -h string:x-dunst-stack-tag:vol "Muted" "Audio disabled"
else
    dunstify -h int:value:"$VOL" -h string:x-dunst-stack-tag:vol "Volume" "$VOL%"
fi
