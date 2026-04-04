/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gap between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Propo:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Propo:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#03b3ff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_cyan,  col_gray1, col_gray2  },
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5"};
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
     *	0 means wherever you are
     *	1 << 1 means 2
     *	1 << 2 means 3
     *	1 << 3 means 4
	 */
	/* class           instance    title       tags mask     isfloating   monitor */
	{ "alacritty",     NULL,       NULL,            0,       0,           -1 },
	{ "firefox",       NULL,       NULL,            0,       0,           -1 },
	{ "kitty",         NULL,       NULL,       1 << 2,       0,           -1 },
	{ "lagrange",      NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/alacritty", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray1, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *filebrowsercmd[]  = { "kitty", "-e", "yazi", NULL };
static const char *weechatcmd[]  = { "alacritty", "-e", "weechat", NULL };
static const char *calccmd[]  = {"galculator", NULL };
static const char *prtscncmd[]  = {"/home/sava/.config/scripts/screenshot.sh", NULL };
static const char *musiccmd[]  = { "alacritty", "-e", "ncmpcpp", NULL };
static const char *reposcmd[] = { "/home/sava/.config/scripts/repos.sh", NULL };
static const char *bookmarkscmd[] = { "/home/sava/.config/scripts/bookmarks.sh", NULL };
static const char *vol_up[] = { "/home/sava/.config/scripts/volumecontrol.sh", "up", NULL };
static const char *vol_down[] = { "/home/sava/.config/scripts/volumecontrol.sh", "down", NULL };
static const char *vol_mute[] = { "/home/sava/.config/scripts/volumecontrol.sh", "mute", NULL };
static const char *logout[] = { "slock", NULL};
static const char *brupcmd[] = { "brightnessctl", "set", "+10%", NULL };
static const char *brdowncmd[] = { "brightnessctl", "set", "10%-", NULL };
static const char *playpausecmd[] = { "playerctl", "play-pause", NULL };
static const char *nextsongcmd[] = { "playerctl", "next", NULL };
static const char *prevsongcmd[] = { "playerctl", "previous", NULL };


static const Key keys[] = {
	/* modifier                     key        function        argument */
    { 0,             XF86XK_MonBrightnessUp,   spawn,          {.v = brupcmd } },
    { 0,             XF86XK_MonBrightnessDown, spawn,          {.v = brdowncmd } },
	{ 0,             XF86XK_AudioMute,         spawn,          {.v = vol_mute } },
    { 0,             XF86XK_AudioLowerVolume,  spawn,          {.v = vol_down } },
    { 0,             XF86XK_AudioRaiseVolume,  spawn,          {.v = vol_up } },
    { 0,             XF86XK_AudioPlay,         spawn,          {.v = playpausecmd } },
    { MODKEY,        XF86XK_AudioLowerVolume,  spawn,          {.v = prevsongcmd } },
    { MODKEY,        XF86XK_AudioRaiseVolume,  spawn,          {.v = nextsongcmd } },
    { 0,             XF86XK_Calculator,        spawn,          {.v = calccmd } },
    { 0,             XK_Print,                 spawn,          {.v = prtscncmd } },
    { MODKEY|ShiftMask,             XK_l,      spawn,          {.v = logout} },
    { MODKEY,                       XK_m,      spawn,          {.v = musiccmd } },
    { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_x,      spawn,          {.v = reposcmd } },
    { MODKEY,                       XK_c,      spawn,          {.v = bookmarkscmd } },
    { MODKEY,                       XK_v,      spawn,          {.v = weechatcmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = filebrowsercmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_p,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_p,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


