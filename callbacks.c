#include <Xm/Xm.h>

#include "globals.h"
#include "tictactoe.h"
#include "procs.h"


void reload_pms() {
  int x, y;

  if (X_PIXMAP) 
//    printf("still here\n");
//  printf("In reload_pms\n");
  for (x = 0; x < 3; x++) {
    for (y = 0; y < 3; y++) {
      if (letter(grid[x][y]) == UD_BLANK)
	XtVaSetValues(grid[x][y], XmNlabelPixmap, BLANK_PIXMAP, NULL);
      if (letter(grid[x][y]) == UD_X) 
	XtVaSetValues(grid[x][y], XmNlabelPixmap, X_PIXMAP, NULL);
      if (letter(grid[x][y]) == UD_O)
	XtVaSetValues(grid[x][y], XmNlabelPixmap, O_PIXMAP, NULL);
    }
  }
//  printf("Out of reload_pms\n");
}

void resize_cb(Widget widget, XtPointer client_data, XtPointer call_data) {
  

  Dimension ph, pw, fh, fw, xh;
  Widget tempw = (Widget)client_data;
  Display *dpy;
  int thickness, i;
  unsigned long color;

//  printf("In resize_cb\n");
  dpy = XtDisplay(tempw);
  XtVaGetValues(tempw, XmNwidth, &fw, XmNheight, &fh, NULL);
  //  printf("fw: %d fh: %d\n", fw, fh);
  if (fw < 130 ) {
    fw = 135;
  }
  if (fh < 130) {
    fh = 135;
  }
  ph = fh / 3 - 10;
  pw = fw / 3 - 10;
  if (ph < pw) {
    xh = ph - 30;
  } else {
    xh = pw - 30;
  }
 // printf("Got here, xh = %d\n", xh);
  if (gc != NULL) {
//    printf("GC is fine\n");
  }
  X_PIXMAP = XCreatePixmap(dpy, RootWindowOfScreen(XtScreen(tempw)), xh/2, xh, DefaultDepthOfScreen(XtScreen(tempw)));

  XtVaGetValues(tempw, XmNbackground, &color, NULL);
  XSetForeground(dpy, gc, color);
  XFillRectangle(dpy, X_PIXMAP, gc, 0, 0, xh/2, xh);
  XSetForeground(dpy, gc, BlackPixelOfScreen(XtScreen(tempw)));
//  printf("Got here\n");
  thickness = xh / 8;
  for (i = 0; i <= thickness; i++) {
    XDrawLine(dpy, X_PIXMAP, gc, 0, -1 * (thickness / 2) + i, xh/2, xh + (-1 * (thickness / 2) + i));
  }
  for (i = 0; i <= thickness; i++) {
    XDrawLine(dpy, X_PIXMAP, gc, xh/2, -1 * (thickness / 2) + i, 0, xh + (-1 * (thickness / 2) + i));
  }
  while ((xh % 3 != 0)||(xh % 2 != 0)) {
    xh--;
  }
  O_PIXMAP = XCreatePixmap(dpy, RootWindowOfScreen(XtScreen(tempw)), xh/2, xh, DefaultDepthOfScreen(XtScreen(tempw)));
  XSetForeground(dpy, gc, color);
  XFillRectangle(dpy, O_PIXMAP, gc, 0, 0, xh/2, xh);

  /*corners*/
  XSetForeground(dpy, gc, BlackPixelOfScreen(XtScreen(tempw)));
  XFillArc(dpy, O_PIXMAP, gc, 0, 0, xh/3, xh/3, 90*64, 90*64); /*topleft*/
  XFillArc(dpy, O_PIXMAP, gc, 0, xh/3*2, xh/3, xh/3, 180*64, 90*64);/*botleft*/
  XFillArc(dpy, O_PIXMAP, gc, xh/6, xh/3*2, xh/3, xh/3, 270*64, 90*64);/*botright*/
  XFillArc(dpy, O_PIXMAP, gc, xh/6, 0, xh/3, xh/3, 0*64, 90*64); /*topright*/
  /*sides*/
  XFillRectangle(dpy, O_PIXMAP, gc, 1, xh/6, thickness/2, xh/3*2); /*left*/
  XFillRectangle(dpy, O_PIXMAP, gc, xh/6, xh-thickness/2, xh/6, thickness/2);/*bot side*/
  XFillRectangle(dpy, O_PIXMAP, gc, xh/2-(thickness/2), xh/6, thickness/2, xh/3*2); /*right side*/
  XFillRectangle(dpy, O_PIXMAP, gc, xh/6, 0, xh/6*1, thickness/2);/*top*/
  /*bg cutouts*/
  XSetForeground(dpy, gc, color);
  XFillArc(dpy, O_PIXMAP, gc, thickness/2, thickness/2, xh/3-thickness+2,
	   xh/3-thickness+2, 90*64, 90*64); /*topleft*/
  XFillArc(dpy, O_PIXMAP, gc, thickness/2 , xh*17/24, xh/3 - thickness,
	   xh*11/48, 180*64, 90*64); /*botleft*/
  XFillArc(dpy, O_PIXMAP, gc, thickness/2+xh/6, xh/3*2 + thickness/2,
	   xh/3-thickness, xh/3-thickness, 270*64, 90*64);/*botright*/
  XFillArc(dpy, O_PIXMAP, gc, thickness/2 + xh/6 - 1, thickness/2,
	   xh/3-thickness+2, xh/3-thickness + 2, 0, 90*64);/*topright*/
  reload_pms();
}

void filemenu_cb(Widget widget, XtPointer client_data, XtPointer call_data) {
  int ev  = (int)client_data;
  switch (ev) 
    {
    case GAME_QUIT_ITEM:
      exit(0);
      break;
    case GAME_STARTOVER_ITEM:
      do_startover();
      break;
    default:
      break;
    }    
  
}

void pb_cb(Widget widget, XtPointer client_data, XtPointer call_data) {
  int x,y,data,myname;
  Pixmap the_pixmap;

  data = (int)client_data;
  y = data % 10;
  x = (data - (data % 10)) / 10;
  if (letter(widget) == UD_BLANK) {
    if (turn == X_TURN) {
      the_pixmap = X_PIXMAP;
    } else {
      the_pixmap = O_PIXMAP;
    }
    XtVaSetValues(widget, XmNlabelPixmap, the_pixmap, NULL);
    setletter(widget, turn + 1);
    myname = letter(widget);
    if (
	((letter(grid[2][y]) == myname) &&
	 (letter(grid[1][y]) == myname) &&
	 (letter(grid[0][y]) == myname)) ||
	((letter(grid[x][0]) == myname) &&
	 (letter(grid[x][1]) == myname) &&
	 (letter(grid[x][2]) == myname)) ||
	((letter(grid[0][0]) == myname) &&
	 (letter(grid[1][1]) == myname) &&
	 (letter(grid[2][2]) == myname)) ||
	((letter(grid[2][0]) == myname) &&
	 (letter(grid[1][1]) == myname) &&
	 (letter(grid[0][2]) == myname))
	) {
      dowin();
    } else {   
      turn = abs(turn - 1);
    }
  }
}





