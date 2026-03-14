/* See LICENSE for license details. */
#include <X11/Xft/Xft.h>

#include "st.h"
#include "util.h"
#include "win.h"
#include "x.h"

static DC *dc;
static XWindow *xw;
static TermWindow *win;

static uint buflen;
static XftGlyphFontSpec *ucbuf;

static XGlyphInfo info;
static XftFont *ucfont;
static FT_UInt curl;

static const Rune cc = '~';

void
undercurl_xinit(DC *xdc, XWindow *xwin, TermWindow *twin)
{
	dc = xdc; xw = xwin; win = twin;
}

void
drawlines(int x, int y, int width, Color *fg, Color *bg, Glyph base, int len) {
	XRenderColor ucolor;
	Color *uc, truec;
	int i, height;

	height = (win->ch / 24) + 1;

	if (base.mode & ATTR_STRUCK)
		XftDrawRect(xw->draw, fg, x, y + 2 * (dc->font.ascent + height) / 3, width, height);

	if (!(base.mode & ATTR_UNDERLINE))
		return;

	if ((base.mode & ATTR_INVISIBLE) || (base.mode & ATTR_BLINK && win->mode & MODE_BLINK)) {
		uc = bg;
	} else if (IS_TRUECOL(base.uc)) {
		ucolor.alpha = 0xffff;
		ucolor.red = TRUERED(base.uc);
		ucolor.green = TRUEGREEN(base.uc);
		ucolor.blue = TRUEBLUE(base.uc);
		XftColorAllocValue(xw->dpy, xw->vis, xw->cmap, &ucolor, &truec);
		uc = &truec;
	} else {
		uc = &dc->col[base.uc];
	}

	if (!(base.mode & ATTR_UNDERCURL)) {
		XftDrawRect(xw->draw, uc, x, y + dc->font.ascent + height, width, height);
		return;
	}

	if (len > buflen) {
		buflen = MAX(MAX(32, len), buflen + buflen / 2);
		ucbuf = xrealloc(ucbuf, buflen * sizeof(XftGlyphFontSpec));
	}

	if (ucfont != dc->bfont.match) {
		ucfont = dc->bfont.match;
		curl = XftCharIndex(xw->dpy, ucfont, cc);
		XftGlyphExtents(xw->dpy, ucfont, &cc, 1, &info);
	}

	y += ucfont->ascent + info.y - ucfont->descent;
	for (i = 0; i < len; i++) {
		ucbuf[i].font = ucfont;
		ucbuf[i].glyph = curl;
		ucbuf[i].x = (short)x;
		ucbuf[i].y = (short)y;
		x += win->cw;
	}

	XftDrawGlyphFontSpec(xw->draw, uc, ucbuf, len);
}
