#include <Xm/RowColumn.h>
#include <Xm/CascadeB.h>
#include <Xm/SeparatoG.h>
#include <Xm/MainW.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/Form.h>
#include <Xm/DrawingA.h>
#include <Xm/Label.h>
#include "defs.h"
#include "callbacks.h"
#include "procs.h"
#include <stdint.h>

int turn;
Pixmap O_PIXMAP;
Pixmap X_PIXMAP = 0;
Pixmap BLANK_PIXMAP = 0;
GC gc;
Widget grid[3][3];

void main(int argc, char *argv[]) {
  Widget toplevel, MainWindow, MenuBar, GamePullDown, form, draw_a;
  XmString label_str;
  XtAppContext app;
  uint64_t x,y;

  XtSetLanguageProc(NULL,NULL,NULL);
  toplevel = XtVaAppInitialize(&app, "Demo", NULL, 0, &argc, argv, NULL,
			       XmNwidth, 400,
			       XmNheight,400,
			       NULL);
  
  MainWindow = XtVaCreateManagedWidget("main_w",
				       xmMainWindowWidgetClass, toplevel,
				       XmNwidth, 400,
				       XmNheight, 400,
				       NULL);
  form = XtVaCreateManagedWidget("form",
				 xmFormWidgetClass, MainWindow,
				 XmNfractionBase,      3,
				 XmNhorizontalSpacing, 10,
				 XmNverticalSpacing,   10,
				 XmNwidth,             400,
				 XmNheight,            400,
				 NULL);

  //Setup menu bar:
  MenuBar = XmCreateMenuBar(MainWindow, "MenuBar", NULL, 0);

  GamePullDown = XmCreatePulldownMenu(MenuBar, "GamePullDown", NULL, 0);
  label_str = XmStringCreateLocalized("Game");
  XtVaSetValues(GamePullDown, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);
  XtVaCreateManagedWidget("Game",
			  xmCascadeButtonWidgetClass, MenuBar,
			  XmNlabelString,             label_str,
			  XmNmnemonic,                'F',
			  XmNsubMenuId,               GamePullDown,
			  NULL);
  XmStringFree(label_str);
  XtAddCallback(XtVaCreateManagedWidget("Start over", xmPushButtonGadgetClass, 
					GamePullDown,
					XmNmnemonic, 's',
					NULL),
		XmNactivateCallback, filemenu_cb, (XtPointer)GAME_STARTOVER_ITEM);

  XtAddCallback(XtVaCreateManagedWidget("Quit", xmPushButtonGadgetClass, 
					GamePullDown,
					XmNmnemonic, 'q',
					NULL),
		XmNactivateCallback, filemenu_cb, (XtPointer)GAME_QUIT_ITEM);
  //Setup grid
      BLANK_PIXMAP = my_create_gc(form);
  if (BLANK_PIXMAP)
//    printf("Got here\n");
  for (x = 0; x < 3; x++) {
    for (y = 0; y < 3; y++) {
	  grid[x][y] = XtVaCreateManagedWidget(" ", xmPushButtonWidgetClass,
				       form,
				       XmNleftAttachment,  XmATTACH_POSITION,
				       XmNleftPosition,    x,
				       XmNrightAttachment, XmATTACH_POSITION,
				       XmNrightPosition,   x + 1,
				       XmNtopAttachment,   XmATTACH_POSITION,
				       XmNtopPosition,     y,
				       XmNbottomAttachment,XmATTACH_POSITION,
				       XmNbottomPosition,  y + 1,
				       XmNlabelType,       XmPIXMAP,
				       XmNlabelPixmap,     BLANK_PIXMAP,
				       XmNuserData,        UD_BLANK,
				       NULL);
	  XtAddCallback(grid[x][y], XmNactivateCallback, pb_cb, (XtPointer)((x * 10) + y));
	  setletter(grid[x][y], UD_BLANK);
	}
      }
  draw_a = XtVaCreateManagedWidget("da", xmDrawingAreaWidgetClass,
				   form,
				   XmNresizePolicy, XmRESIZE_ANY,
				   XmNwidth, 100,
				   XmNheight, 100,
				   XmNtopAttachment, XmATTACH_FORM,
				   XmNbottomAttachment, XmATTACH_FORM,
				   XmNleftAttachment, XmATTACH_FORM,
				   XmNrightAttachment, XmATTACH_FORM,
				   NULL);
  
  XtAddCallback(draw_a, XmNresizeCallback, resize_cb, (XtPointer)MainWindow);
  XtManageChild(MenuBar);
  XtRealizeWidget(toplevel);
  XtAppMainLoop(app);
}

void dowin() {
  
  
//  char *resp;

  
  do_startover();
}
      


