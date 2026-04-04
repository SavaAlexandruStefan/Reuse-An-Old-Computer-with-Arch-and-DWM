# Sava's DWM build

## With dwm-status2d-6.5 patch for a colored slstatus

![dwm.png](dwm.png)

[Original README](README)

## Screenshot

![Sava's DWM Build Preview](sava.rocks-dwm-preview.jpg)

Uses JetBrainsMono Nerd Font Propo and alacritty as the default terminal. 

## Installation

Should be started from the install.sh script from the install repos at:

- https://git.sava.rocks/Sava/install
```
git clone https://git.sava.rocks/Sava/install.git .
```
- https://github.com/SavaAlexandruStefan/install
```
git clone https://github.com/SavaAlexandruStefan/install .
```

## Standalone

These should be installed before cloning and installing with **sudo make clean install**

```
sudo pacman -S xorg-xinit xorg xorg-server stow slock ripgrep fzf gvim mpd noto-fonts-emoji ncmpcpp mpd mpc mpd-mpris dmenu base-devel ttf-jetbrains-mono-nerd ttf-nerd-fonts-symbols ttf-nerd-fonts-symbols-common alacritty picom
```

### Slstatus

Clone the repo:
```
git clone https://git.sava.rocks/Sava/slstatus
```

Install slstatus
```
cd slstatus
sudo make clean install
```

### .xinitrc
Edit your .xinitrc and add these lines:
```
slstatus &
exec dwm 
```

## Shortcuts

### Personal

| Shortcut      | Action         | Comment                         |
|:--------------|:---------------|:--------------------------------|
| `Win + Enter` | open terminal  | Open terminal: alacritty        |
| `Win + Space` | open dmenu     | Application finder/launcher     |
| `Win + x`     | open Projects  | Open my projects                |
| `Win + c`     | open Bookmarks | Open my bookmarks               |
| `Win + v`     | open weechat   | Open my irc client              |
| `Win + b`     | open brave     | Open brave browser              |
| `Win + e`     | open yazi      | Open yazi file manager in kitty |

### Music

| Shortcut          | Action         | Comment                        |
|:------------------|:---------------|:-------------------------------|
| `Win + m `        | open ncmpcpp   | Open music app: ncmpcpp        |
| `Win + Vol UP `   | next track     | plays next track in ncmpcpp    |
| `Win + Vol DOWN ` | previous track | play previous track in ncmpcpp |
| `Vol UP `         |  Volume +10%   | Increase volume by 10%         |
| `Vol DOWN `       |  Volume -10%   | Decrease volume by 10%         |

### DWM defaults

| Shortcut            | Action                         | Comment                                                             |
|:--------------------|:-------------------------------|:--------------------------------------------------------------------|
| `Win + q`           | kills selected application     | Kills the current selected application                              |
| `Win + 1`           | open workspace 1               | Switches to workspace #1                                            |
| `Win + 2`           | open workspace 2               | Switches to workspace #2                                            |
| `Win + 3`           | open workspace 3               | Switches to workspace #3                                            |
| `Win + 4`           | open workspace 4               | Switches to workspace #4                                            |
| `Win + 5`           | open workspace 5               | Switches to workspace #5                                            |
| `Win + Shift + 1`   | move app to workspace 1        | Moves app to workspace #1                                           |
| `Win + Shift + 2`   | move app to workspace 2        | Moves app to workspace #2                                           |
| `Win + Shift + 3`   | move app to workspace 3        | Moves app to workspace #3                                           |
| `Win + Shift + 4`   | move app to workspace 3        | Moves app to workspace #4                                           |
| `Win + Shift + 5`   | move app to workspace 5        | Moves app to workspace #5                                           |
| `Win + z`           | switch zoom                    | switches between apps in the same workspace / focus                 |
| `Win + h`           | decrease selected window size  | Decreases selected window size                                      |
| `Win + l`           | increase selected window size  | Increases selected window size                                      | 
| `Win + j`           | move to window: left           | Switches to another app to the left                                 |
| `Win + k`           | move to window: right          | Switches to another app to the right                                |
| `Win + Shift + b`   | toggle bar - slstatus          | shows or hides the bar at the top - slstatus                        |
| `Win + d`           | horizontal split               | splits open applications horizontaly                                |
| `Win + i`           | vertical split                 | splits open application vertically                                  |
| `Win + TAB`         | switch between workspaces      | switches between current and previously selected workspace          |
| `Win + Shift + q`   | close DWM                      | Closes DWM - useful if dwm is recompiled again                      |
