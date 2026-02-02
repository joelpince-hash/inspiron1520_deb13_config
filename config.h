/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "sans:size=12" };
//static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
/* Couleurs style Google / Material Design */
static const char col_gray1[]       = "#f1f3f4"; /* Fond de la barre (inactif) - Gris clair */
static const char col_gray2[]       = "#dadce0"; /* Bordure fenêtre (inactif) - Gris pierre */
static const char col_gray3[]       = "#5f6368"; /* Texte (inactif) - Gris anthracite */
static const char col_gray4[]       = "#ffffff"; /* Texte (actif) - Blanc pur */
static const char col_cyan[]        = "#4285F4"; /* Fond barre & Bordure (actif) - Bleu Google */
//static const char col_gray1[]       = "#222222";
//static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#bbbbbb";
//static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "W", ">_", "F", "M", "S", "B" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "st-256color",     NULL,       NULL,       1 << 1,            0,           -1 },
	{ "Vivaldi-stable", "play.qobuz.com",   NULL,       1 << 3,       0,           -1 },
	{ "Vivaldi-stable", "vivaldi-stable",    NULL,       1 << 0,       0,           -1 },
	{ "Thunar",	NULL,	NULL,	1 << 2,	0,	-1 },
	{ "HtopTerm",	NULL,	NULL,	1 << 4,	0,	-1 },
	{ "ONLYOFFICE",	NULL,	NULL,	1 << 5,	0,	-1 },
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
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
/* Définition de la commande htopcmd : à l'ouverture du terminal st, la fenêtre s'appelle HtopTerm et htop s'ouvre à l'intérieur. */
static const char *htopcmd[] = { "st", "-c", "HtopTerm", "-e", "htop", NULL };
/* Définition de la commande Google-chrome */
static const char *chromecmd[] = { "vivaldi-stable", NULL };
/* Définition de la commande pour Qobuz dans Chrome*/
static const char *qobuzcmd[] = { "vivaldi-stable", "--app=https://play.qobuz.com", NULL };
/* Définition de la commande Thunar */
static const char *thunarcmd[] = { "Thunar", NULL };
/* Définition de la commande OnlyOffice */
static const char *onlyofficecmd[] = { "onlyoffice-desktopeditors", NULL };
/* Commandes Multimédia (Dell Inspiron 1520) */
static const char *upvol[]   = { "amixer", "set", "Master", "5%+", NULL };
static const char *downvol[] = { "amixer", "set", "Master", "5%-", NULL };
static const char *mutevol[] = { "amixer", "set", "Master", "toggle", NULL };

/* Commandes Lecture (Nécessite playerctl) */
static const char *medplay[] = { "playerctl", "play-pause", NULL };
static const char *mednext[] = { "playerctl", "next", NULL };
static const char *medprev[] = { "playerctl", "previous", NULL };
static const char *medstop[] = { "playerctl", "stop", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_agrave,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* Lancer Google-chrome avec ALT+g sur le bureau 0*/
	{ MODKEY,                       XK_g,      spawn,          {.v = chromecmd } },
	/* Lancer Qobuz dans Google-chrome avec ALT+p sur le bureau 3*/
	{ MODKEY,                       XK_q,      spawn,          {.v = qobuzcmd } },
	/* Lancer Thunar avec ALT+n sur le bureau 2*/
	{ MODKEY,			XK_n,	spawn,	{.v = thunarcmd } },
	/* Lancer Htop avec ALT+SHIFT+h (obersateur de performances) dans un terminal sur le bureau 4 */
	{ MODKEY|ShiftMask,			XK_h,	spawn,		{.v = htopcmd } },
	/* Lancer OnlyOffice avec Alt+o sur le bureau 5*/
	{ MODKEY,	XK_o,	spawn,	{.v = onlyofficecmd } },
	/* Augmenter le volume avec Mod + Flèche Haut */
{ MODKEY,                       XK_Up,     spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },

/* Baisser le volume avec Mod + Flèche Bas */
{ MODKEY,                       XK_Down,   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },
	TAGKEYS(                        XK_ampersand,                      0)
	TAGKEYS(                        XK_eacute,                      1)
	TAGKEYS(                        XK_quotedbl,                      2)
	TAGKEYS(                        XK_apostrophe,                      3)
	TAGKEYS(                        XK_parenleft,                      4)
	TAGKEYS(                        XK_minus,                      5)
	TAGKEYS(                        XK_egrave,                      6)
	TAGKEYS(                        XK_underscore,                      7)
	TAGKEYS(                        XK_ccedilla,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
/* Touches Volume */
    { 0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol } },
    { 0, XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
    { 0, XF86XK_AudioMute,        spawn, {.v = mutevol } },

    /* Touches Média (Façade avant) */
    { 0, XF86XK_AudioPlay,        spawn, {.v = medplay } },
    { 0, XF86XK_AudioNext,        spawn, {.v = mednext } },
    { 0, XF86XK_AudioPrev,        spawn, {.v = medprev } },
    { 0, XF86XK_AudioStop,        spawn, {.v = medstop } },
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

