#!/usr/bin/env bash

# Colors
GREEN="\e[1;32m"
CYAN="\e[1;36m"
YELLOW="\e[1;33m"
RED="\e[1;31m"
RESET="\e[0m"

# Title
echo -e "${CYAN}=========================================${RESET}"
echo -e "${GREEN}     Installing Sava's Arch Build ${RESET}"
echo -e "${CYAN}=========================================${RESET}"
read -p "This will install dwm, slstatus, mpd and everything in packages.txt. Proceed with installation? [y/N]: " confirm

if [[ ! "$confirm" =~ ^[Yy]$ ]]; then
    echo -e "${RED}Installation cancelled.${RESET}"
    exit 0
fi

# Check for packages.txt
if [[ ! -f packages.txt ]]; then
    echo -e "${RED}Error: packages.txt not found!${RESET}"
    exit 1
fi

# Read packages into array (ignore comments and empty lines)
mapfile -t PACKAGES < <(grep -vE '^\s*#|^\s*$' packages.txt)

if [[ ${#PACKAGES[@]} -eq 0 ]]; then
    echo -e "${RED}No packages found in packages.txt${RESET}"
    exit 1
fi

# Show package list
echo -e "${YELLOW}The following packages will be installed:${RESET}"
for pkg in "${PACKAGES[@]}"; do
    echo "  - $pkg"
done

echo
read -p "Proceed with installation? [y/N]: " confirmpackages

if [[ ! "$confirmpackages" =~ ^[Yy]$ ]]; then
    echo -e "${RED}Installation cancelled.${RESET}"
    exit 0
fi

# Update database
echo -e "${GREEN}Updating package database...${RESET}"
sudo pacman -Sy

# Install packages with progress counter
TOTAL=${#PACKAGES[@]}
COUNT=0

for pkg in "${PACKAGES[@]}"; do
    ((COUNT++))
    echo -e "${CYAN}[$COUNT/$TOTAL] Installing: $pkg${RESET}"
    sudo pacman -S --noconfirm "$pkg"
done
echo -e "${GREEN}Installation of $TOTAL packages complete!${RESET}"
echo -e "${CYAN}Enabling services${RESET}"
echo -e "${YELLOW}Enabling mpd [user]${RESET}"
systemctl enable --user --now mpd.service mpd.socket mpd-mpris
echo -e "${YELLOW}Enabling bluetooth${RESET}"
sudo modprobe btusb
sudo systemctl enable bluetooth
echo -e "${GREEN}Done!${RESET}"

# dwm & slstatus

# dwm installation
echo -e "${YELLOW}Installing dwm${RESET}"
cd "dwm"
sudo make clean install
echo -e "${GREEN}Done!${RESET}"

# slstatus installation
echo -e "${YELLOW}Installing slstatus${RESET}"
cd "../slstatus"
sudo make clean install
echo -e "${GREEN}Done!${RESET}"
echo -e "${CYAN}Remember to start slstatus and dwm from .xinitrc${RESET}"
echo "-----------"
echo "slstatus &"
echo "exec dwm"
echo "-----------"
# Reboot
echo -e "${RED}You should reboot ! Do you want to do that now ?${RESET}"
read -rp "Do you want to reboot now? [y/N]: " rebootnow
if [[ "$rebootnow" =~ ^([yY][eE][sS]|[yY])$ ]]; then
    echo -e "${GREEN}Rebooting...${RESET}"
    sudo reboot
else
    echo "Reboot cancelled."
fi
