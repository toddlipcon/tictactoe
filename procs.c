#include <Xm/XmAll.h>

#include "globals.h"

void setletter();

void
set_color(widget, client_data, call_data)
 Widget widget;
XtPointer client_data;
XtPointer call_data;
{
    String color = (String) client_data;
    Display *dpy = XtDisplay (widget);
    Colormap cmap = DefaultColormapOfScreen (XtScreen (widget));
    XColor col, unused;

    if (!XAllocNamedColor (dpy, cmap, color, &col, &unused)) {
        char buf[32];
        sprintf (buf, "Can't alloc %s", color);
        XtWarning (buf);
        return;
    }
    XSetForeground (dpy, gc, col.pixel);
}


Pixmap my_create_gc(Widget w) {
  Display *dpy;
  Screen  *scr;
  XGCValues gcv;
  unsigned long color;
  dpy = XtDisplay(w);
  scr = XtScreen(w);

  gcv.foreground = BlackPixelOfScreen(scr);
  gc = XCreateGC(dpy,
		 RootWindowOfScreen(scr),
		 GCForeground,
		 &gcv);
  XtVaGetValues(w, XmNbackground, &color, NULL);
  XSetForeground(dpy, gc, color);
  BLANK_PIXMAP = XCreatePixmap(dpy, RootWindowOfScreen(scr), 1, 1,
			       DefaultDepthOfScreen(scr));
  XFillRectangle(dpy, BLANK_PIXMAP, gc, 0, 0, 1, 1);
  return BLANK_PIXMAP;
}
void do_startover() {
  int x, y;
  for (x = 0; x < 3; x++) {
    for (y = 0; y < 3; y++) {
      XtVaSetValues(grid[x][y],XmNlabelPixmap, BLANK_PIXMAP, NULL);
      setletter(grid[x][y],UD_BLANK);
    }
  }
  turn = X_TURN;
}

int letter(Widget w) {
  int i;

  //printf("in letter()\n");
  XtVaGetValues(w, XmNuserData, &i, NULL);
  //printf("i = %d\n", i);
  //printf("out of letter()\n");
  return(i);

}

void setletter(Widget w, int letter) {
  int i = letter;
  
  //printf("setting userData to \"%d\"\n", i);
  XtVaSetValues(w, XmNuserData, i, NULL);
}






