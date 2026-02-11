#include "movestack.c"
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "MesloLGS Nerd Font Mono:size=14:antialias=true:autohint=true:hintstyle=hintfull", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true" };
static const char dmenufont[]       = "MesloLGS Nerd Font Mono:size=14:antialias=true:autohint=true:hintstyle=hintfull";
static const char color1[]       = "#000000"; // Darkest color
static const char color2[]       = "#e1750f"; // Dark color
static const char color3[]       = "#eaaf25"; // Light color
static const char color4[]       = "#fa8e08"; // Custom color, 
static const char color5[]       = "#fca806"; // Active border
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { color3, color1, color2 },
	[SchemeSel]  = { color3, color2,  color5  },
};

/* tagging */
// These are the icons for the tags(workspaces), you can also just use numbers or letters if you want.
// You need a nerd font for the icons to work.
static const char *tags[] = { "[]", "[󰇧]", "[]", "[]", "[/]" };


static const char *const autostart[] = {
	// Spaces are done by quoting every part of a command, 
	// for example normally it would be "brightnessctl set 25%", but now every part is seperated with a comma and quotes.

	"dbus-update-activation-environment", "--all", NULL, // For gnome-keyring
	"gnome-keyring-daemon", "--start", "--components=secrets", NULL, // For gnome-keyring
	"dwmbar", NULL,
	"sh", "-c", "feh --randomize --bg-fill ~/Pictures/Wallpapers/*", NULL,
    "brightnessctl", "set", "25%", NULL,
	"proton-authenticator", NULL
};

static const Rule rules[] = {
	// Find class and instance names by running xprop WM_CLASS, it will show the instance first, then the class.
	// For example: xprop WM_ClASS --> click on vscode window --> output: WM_CLASS(STRING) = "code", "Code"
	// On Arch, the package for xprop is called "xorg-xprop"

	/* class      				instance    							title       tags mask     isfloating   monitor */
	{ "Chromium", 				"chromium", 							NULL,       1<<1,         0,           -1 },
	{ "Chromium", 				"crx_nngceckbapebfimnlniiiahkandclblb", NULL,       1<<1,         1,           -1 }, //Bitwarden pop-up
	{ "Proton-authenticator", 	"proton-authenticator", 				NULL,       1<<3,         0,           -1 },
	{ "Spotify", 				"spotify", 								NULL,       1<<4,         0,           -1 },
	{ "Code", 					"code", 								NULL,       1<<2,         0,           -1 },
	{ "vesktop", 				"vesktop", 								NULL,       1<<4,         0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 144;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", color1, "-nf", color3, "-sb", color2, "-sf", color3, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browser[] = { "chromium", NULL};
static const char *files[] = { "thunar", NULL};
static const char *upvol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *downvol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutevol[] = { "pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle", NULL };
static const char *upbrightness[] = { "brightnessctl", "s", "5%+", NULL };
static const char *downbrightness[] = { "brightnessctl", "s", "5%-", NULL };

static const Key keys[] = {
	/* modifier                     key        				 function        argument */
	{ MODKEY,                       XK_space,  				 spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_q,      				 spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      				 togglebar,      {0} },
	{ MODKEY,                       XK_i,      				 incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      				 incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      				 setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      				 setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 				 zoom,           {0} },
	{ MODKEY,                       XK_Tab,    				 view,           {0} },
	{ MODKEY,                       XK_w,      				 killclient,     {0} },
	//{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  				 togglefloating, {0} },
	{ MODKEY,                       XK_0,      				 view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      				 tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  				 focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 				 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  				 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 				 tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Left,   				 focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Right,  				 focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   				 focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     				 focusstack,     {.i = -1 } },
	{ ALTKEY,                       XK_Tab,    				 focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   				 movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,  				 movestack,      {.i = -1 } },
	{ MODKEY,                       XK_b,      				 spawn,          {.v = browser } },
	{ MODKEY,                       XK_e,      				 spawn,          {.v = files } },
	{ MODKEY|ControlMask,           XK_w,      				 quit,           {0} },
	{ MODKEY,                       XK_f,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_f,                    setlayout,      {.v = &layouts[0]} },
	{ 0,                       		XF86XK_AudioRaiseVolume, spawn,          {.v = upvol} },
    { 0,                       		XF86XK_AudioLowerVolume, spawn,          {.v = downvol} },
    { 0,                       		XF86XK_AudioMute,        spawn,          {.v = mutevol} },
	{ 0,                       		XF86XK_MonBrightnessUp,  spawn,          {.v = upbrightness} },
    { 0,                       		XF86XK_MonBrightnessDown, spawn,          {.v = downbrightness} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_b,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
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
