/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 20;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *spotify[] = {"alacritty", "-e", "startSpotify", NULL};
static const char *qutebrowser[] = {"qutebrowser", NULL};
static const char *code[] = {"code", NULL};

#include "shiftview.c"
static Key keys[] = {
	/* modifier			key			function			argument					description */

	{ 0,				XK_Menu,	spawn,				{.v = dmenucmd } },			/* dmenu */

	LAUNCH(				XK_t,							termcmd)					/* terminal */
	LAUNCH(				XK_s,							spotify)					/* spotify  */ 
	LAUNCH(				XK_r,							qutebrowser)				/* qutebrowser */
	LAUNCH(				XK_a,							code)						/* code  */

 /* { MODKEY,			XK_b,		togglebar,			{0} },*/
	{ MODKEY,			XK_n,		focusstack,			{.i = +1 } },				/* change stack focus */
	{ MODKEY,			XK_e,		focusstack,			{.i = -1 } },				/* change stack focus */
 /* { MODKEY,			XK_i,		incnmaster,			{.i = +1 } },*/				/* change layout */
 /* { MODKEY,			XK_d,		incnmaster,			{.i = -1 } },*/				/* change layout */
	{ MODKEY|MODKEY2,	XK_m,		setmfact,			{.f = -0.05} },				/* change horizontal size of focused */
	{ MODKEY|MODKEY2,	XK_i,		setmfact,			{.f = +0.05} },				/* change horizontal size of focused */
	{ MODKEY,			XK_space,	zoom,				{0} },						/* swaps with largest */
 /* { MODKEY,			XK_Tab,		view,				{0} }, */					/* tab 0 */
	{ MODKEY,			XK_Menu,	killclient,			{0} },						/* kills window */
 /* { MODKEY,			XK_t,		setlayout,			{.v = &layouts[0]} },
	{ MODKEY,			XK_f,		setlayout,			{.v = &layouts[1]} },
	{ MODKEY,			XK_m,		setlayout,			{.v = &layouts[2]} }, */	/* sets layout */
 /* { MODKEY,			XK_space,	setlayout,			{0} }, */					/* toggle layouts */
	{ MODKEY|MODKEY2,	XK_Return,	togglefloating,		{0} },						/* toggle wmindow float / tile */
	{ MODKEY,			XK_o,		focusmon,			{.i = -1 } },				/* change monitor focus */
 /* { MODKEY,			XK_period,	focusmon,			{.i = +1 } }, */			/* change monitor focus */
	{ MODKEY|MODKEY2,	XK_o,		tagmon,				{.i = -1 } },				/* move to monitor */
 /* { MODKEY|ShiftMask,	XK_period,	tagmon,				{.i = +1 } }, */			/* move to monitor */
 /* { MODKEY,			XK_0,		view,				{.ui = ~0 } }, */			/* view all tabs */
 /* { MODKEY,           XK_minus,   setgaps,            {.i = -1 } }, */            /* change gap size */
 /* { MODKEY,           XK_equal,   setgaps,            {.i = +1 } }, */            /* change gap size */
 /* { MODKEY|ShiftMask, XK_equal,   setgaps,            {.i = 0  } }, */            /* change gap size */
 /* { MODKEY|MODKEY2,	XK_0,		tag,				{.ui = ~0 } }, */			/* move to all tabs */
	{ MODKEY,			XK_i,		shiftview,			{.i = +1} },					/* view next tab */
	{ MODKEY,			XK_m,		shiftview,			{.i = -1} },					/* view prev tab */
	TAGKEYS(			XK_1,							0)							/* keybinds for tag 1 */
	TAGKEYS(			XK_2,							1)							/* keybinds for tag 2 */
	TAGKEYS(			XK_3,							2)							/* keybinds for tag 3 */
	TAGKEYS(			XK_4,							3)							/* keybinds for tag 4 */
	TAGKEYS(			XK_5,							4)							/* keybinds for tag 5 */
	TAGKEYS(			XK_6,							5)							/* keybinds for tag 6 */
	TAGKEYS(			XK_7,							6)							/* keybinds for tag 7 */
	TAGKEYS(			XK_8,							7)							/* keybinds for tag 8 */
	TAGKEYS(			XK_9,							8)							/* keybinds for tag 9 */
	{ MODKEY|MODKEY2,	XK_q,		quit,				{0} },						/* quit dwm */
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

 