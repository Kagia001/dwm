/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "firacode:size=12" };
static const char dmenufont[]       = "firacode:size=12";
static const char col_bg[]	    = "#fafafa";
static const char col_border[]      = "#eff0f0";
static const char col_bg_text[]     = "#8a9199";
static const char col_accent_text[] = "#fafafa";
static const char col_accent[]      = "#ff9940";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_bg_text, col_bg, col_border },
	[SchemeSel]  = { col_accent_text, col_accent,  col_accent  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8"};

static const Rule rules[] = {
	/* xprop(1)
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		instance	title	tags mask	is floating		monitor */
	{ "Gimp",		NULL,		NULL,	0,		1,				-1 },
	{ "discord",		NULL,		NULL,	1 << 7,		0,				 1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY2 ShiftMask

#define  TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|MODKEY2,               KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|MODKEY2,   KEY,      toggletag,      {.ui = 1 << TAG} },
#define LAUNCH(KEY, PROGRAM) \
	{ MODKEY,                       KEY,      spawn,          {.v = PROGRAM}   },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_bg_text, "-sb", col_accent, "-sf", col_accent_text, NULL };
static const char *rofi[] = { "rofi", "-show", "run", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *spotify[] = {"spotify", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *steam[] = {"steam", NULL};
static const char *editor[] = {"emacsclient", "-c", NULL};
static const char *r2modman[] = {"r2modman", NULL};


static const char *upvol[]   = { "amixer", "-c", "HD", "sset", "PCM", "playback", "volume", "-M", "2%+", NULL };
static const char *downvol[] = { "amixer", "-c", "HD", "sset", "PCM", "playback", "volume", "-M", "2%-", NULL };
static const char *mutevol[] = { "amixer", "-c", "HD", "sset", "PCM", "playback", "volume", "-M", "0", NULL };

static const char *screenshot[] = { "maim", "~/Screenshots/$(date", "+%s).png", NULL };

#include "shiftview.c"
#define PrintScreen         0x0000ff61
#include <X11/XF86keysym.h>
static Key keys[] = {
  /* modifier			key			function			argument					description */
  { 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
  { 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
  { 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
  { 0,                       PrintScreen,             spawn, {.v = screenshot}},
  { 0,				XK_Menu,	spawn,				{.v = rofi }},			/* dmenu */

  LAUNCH(				XK_t,							termcmd)					/* terminal */
  LAUNCH(				XK_s,							browser)				/* qutebrowser */
  LAUNCH(				XK_r,							spotify)					/* spotify  */
  LAUNCH(				XK_a,							steam)						/* editor  */
  LAUNCH(                         XK_d,                                                   r2modman)
  LAUNCH(           XK_g,                           editor)
  
  { MODKEY,			XK_n,		focusstack,			{.i = +1 } },				/* change stack focus */
  { MODKEY,			XK_e,		focusstack,			{.i = -1 } },				/* change stack focus */

  { MODKEY|MODKEY2,	XK_m,		setmfact,			{.f = -0.05} },				/* change horizontal size of focused */
  { MODKEY|MODKEY2,	XK_i,		setmfact,			{.f = +0.05} },				/* change horizontal size of focused */
  { MODKEY,			XK_space,	zoom,				{0} },						/* swaps with largest */

  { MODKEY,			XK_Menu,	killclient,			{0} },						/* kills window */
  { MODKEY|MODKEY2,	XK_Return,	togglefloating,		{0} },						/* toggle window float / tile */

  { MODKEY,			XK_o,		focusmon,			{.i = +1 } },				/* change monitor focus */
  { MODKEY|MODKEY2,	XK_o,		tagmon,				{.i = +1 } },				/* move to monitor */
  { MODKEY,			XK_i,		shiftview,			{.i = +1} },				/* view next tab */
  { MODKEY,			XK_m,		shiftview,			{.i = -1} },				/* view prev tab */

  TAGKEYS(			XK_q,							0)							/* keybinds for tag 1 */
  TAGKEYS(			XK_w,							1)							/* keybinds for tag 2 */
  TAGKEYS(			XK_f,							2)							/* keybinds for tag 3 */
  TAGKEYS(			XK_p,							3)							/* keybinds for tag 4 */
  TAGKEYS(			XK_l,							4)							/* keybinds for tag 5 */
  TAGKEYS(			XK_u,							5)							/* keybinds for tag 6 */
  TAGKEYS(			XK_y,							6)							/* keybinds for tag 7 */
  TAGKEYS(			XK_semicolon,					7)							/* keybinds for tag 8 */
  { ControlMask|ShiftMask,	XK_Escape,		quit,				{0} },						/* quit dwm */


 /* { MODKEY,			XK_b,		togglebar,			{0} },*/					/* ???? toggle task bar probably ???? */
 /* { MODKEY,			XK_i,		incnmaster,			{.i = +1 } },*/				/* change layout */
 /* { MODKEY,			XK_Tab,		view,				{0} }, */					/* tab 0 */
 /* { MODKEY,			XK_m,		setlayout,			{.v = &layouts[2]} }, */	/* sets layout */
 /* { MODKEY,			XK_space,	setlayout,			{0} }, */					/* toggle layouts */
 /* { MODKEY,			XK_0,		view,				{.ui = ~0 } }, */			/* view all tabs */
 /* { MODKEY,           XK_minus,   setgaps,            {.i = -1 } }, */            /* change gap size */
 /* { MODKEY|MODKEY2,	XK_0,		tag,				{.ui = ~0 } }, */			/* move to all tabs */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

 
