#!/usr/bin/env bash
while true; do
    # Wait for the next player event
    mpc idle player > /dev/null

    # Get current state: playing, paused, or [stopped]
    STATE=$(mpc status %state%)

    if [ "$STATE" == "playing" ]; then
        TITLE=$(mpc -f %title% current)
        ARTIST=$(mpc -f %artist% current)
        DURATION=$(mpc -f %time% current)
        dunstify -h string:x-dunst-stack-tag:music "Now Playing" "$ARTIST - $TITLE [ $DURATION ]"
    elif [ "$STATE" == "paused" ]; then
        dunstify -h string:x-dunst-stack-tag:music "Music Paused" "Playback has been paused."
    else
        # This covers the "stopped" state
        dunstify -h string:x-dunst-stack-tag:music "Music Stopped" "Playback has ended."
    fi
done

