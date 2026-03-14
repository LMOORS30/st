/* See LICENSE for license details. */

typedef XftColor Color;

/* Purely graphic info */
typedef struct {
	int tw, th; /* tty width and height */
	int w, h; /* window width and height */
	int cw; /* char width */
	int ch; /* char height */
	int cyo; /* char y offset */
	int mode; /* window state/mode flags */
	int cursor; /* cursor style */
} TermWindow;

typedef struct {
	Display *dpy;
	Colormap cmap;
	Window win;
	Drawable buf;
	XftGlyphFontSpec *specbuf; /* font spec buffer used for rendering */
	Atom xembed, wmdeletewin, netwmname, netwmiconname, netwmpid;
	struct {
		XIM xim;
		XIC xic;
		XPoint spot;
		XVaNestedList spotlist;
	} ime;
	XftDraw *draw;
	Visual *vis;
	XSetWindowAttributes attrs;
	int scr;
	int isfixed; /* is fixed geometry? */
	int l, t; /* left and top offset */
	int gm; /* geometry mask */
} XWindow;

/* Font structure */
#define Font Font_
typedef struct {
	int height;
	int width;
	int ascent;
	int descent;
	int badslant;
	int badweight;
	short lbearing;
	short rbearing;
	XftFont *match;
	FcFontSet *set;
	FcPattern *pattern;
} Font;

/* Drawing Context */
typedef struct {
	Color *col;
	size_t collen;
	Font font, bfont, ifont, ibfont;
	GC gc;
} DC;

void boxdraw_xinit(XWindow *);
void drawboxes(int, int, int, int, Color *, Color *, const XftGlyphFontSpec *, int);

void undercurl_xinit(DC *, XWindow *, TermWindow *);
void drawlines(int, int, int, Color *, Color *, Glyph, int);

/* config.h globals */
extern int boxdraw;
extern int boxdraw_bold;
extern int boxdraw_braille;
