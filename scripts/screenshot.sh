#!/usr/bin/env bash

# Create Screenshots directory if it doesn't exist
mkdir -p "$HOME/Screenshots"

# Take screenshot
maim -su "$HOME/Screenshots/$(date +%Y-%m-%d-%H-%M-%S).jpg"
