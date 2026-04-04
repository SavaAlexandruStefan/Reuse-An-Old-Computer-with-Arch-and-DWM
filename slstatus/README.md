# Sava's build of slstatus 1.1 which includes a C component for mpd

[Original README](README)

## Installation

Should be started from the install.sh script

## Standalone

You have to install libmpd client and JetBrainsMono font. On Arch:

```
sudo pacman -S libmpdclient noto-fonts-emoji ttf-jetbrains-mono-nerd ttf-nerd-fonts-symbols ttf-nerd-fonts-symbols-common
```
before

```
sudo make clean install
```
