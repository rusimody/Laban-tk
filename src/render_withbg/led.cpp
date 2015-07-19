/*
                led : version 120
               a Labanotation editor
          in C++ using OpenGL and glut32
                 for Windows on a PC

   Description at:
     http://linus.it.uts.edu.au/~don/pubs/led.html

	  known bugs:
	  beats extend above stave lines
	  stave lines should end on top bar line
	  bar numbers sometimes wrong

   Email comments and problems to:
     donherbisonevans@yahoo.com

  1 Nov 2009 120 put glClearColor & glColor3f in text()
 27 Oct 2009 119 changed T_CHAR to char
 17 Oct 2007 118 scale Postscript 0.33, deleted extra bar line
 17 Oct 2007 117 fix ticks on Postscript output
  7 Oct 2007 116 fix lineabs, drawsymbol, filledpin for postscript
  6 Oct 2007 115 fix yhigh
  5 Oct 2007 114 fix fixstaff
  2 Oct 2007 113 fix stave in postscript
  1 Oct 2007 112 fix pins in postscript
 27 Sep 2007 111 comments in .ps file, scale 0.7 in .ps, offset x
 25 Sep 2007 110 extra bar line, snap to staff
 19 Aug 2007 109 set text size, fewer movetos
 18 Aug 2007 108 text in postscript output
 13 Jul 2007 107 default name for postscript output
 12 Jul 2007 106 fix newpath, closepath, TEXTL, DELETEL
  2 Apr 2007 105 fix 'clear'
  1 Apr 2007 104 fix highlighting
 19 Mar 2007 103 fix deletes after text
 26 Feb 2007 102 ptitle, addtext, addcomment, target,
 22 Feb 2007 101 added segs.red, prevc
  8 Jul 2006 097 fix seg.length, seg.text, space hold
 24 May 2006 095 fix spurious Way 0 entries
 12 May 2006 v94 fix user size window
 24 Apr 2006 v93 allow dot in circle
 23 Apr 2006 v92 allow entry of filename straight away
  1 Apr 2006 v91 fix 26 bar limit NSYMS->226
 31 Mar 2006 v90 add simultaneous bows in Way menu
 30 Mar 2006 v89 fix snap
 14 Mar 2006 v88 fix barlines
 12 Mar 2006 v87 allow user to size window
 15 Feb 2006 v86 deduce bar spacing from input
 14 Feb 2006 v85 ticks on central stave
  5 Dec 2005 v84 highlight Save when used
  5 Nov 2005 v83 Save and SaveAs
  4 Oct 2005 v82 adding comments at bar lines
 30 Aug 2005 v81 resizing window again
  4 Aug 2005 v80 resizing window
 28 Jun 2005 v77 clearing comments with 'clear' 
 27 Jun 2005 v76 adding newline at end of text comment
 10 Jun 2005 v75 improving hatching of high symbols
  5 Jun 2005 v74 allow comments
 27 May 2005 v73 no snap on pins etc
 27 May 2005 v72 snapping rotation symbols
 25 May 2005 v71 snapping facing symbols to x=50 or 400
 24 May 2005 v70 fix dot positions
 23 May 2005 v69 standardising symbol sizes in lbnread
 22 May 2005 v68 fix copy bug, scaling bug
 21 May 2005 v67 fix pins
 21 May 2005 v66 fix low symbols
 19 May 2005 v65 fix snap
 18 May 2005 v64 fix extended bars
 17 May 2005 v63 fix staff heights
 17 May 2005 v62 set optional output file name
 15 May 2005 v61 fix overlapping symbols bug
 15 May 2005 v60 fix barline bug, click on symbol menu gives copy mode, led.lbn output
 15 May 2005 v59 fix scroll-down bug, centred symbols on cursor
 14 May 2005 v58 added help command
 13 May 2005 v57 fix scrolling/mouse click problem
 13 May 2005 v56 fix barlines bug
 12 May 2005 v55 other commands working
 12 May 2005 v54 scroll up and down working
 11 May 2005 v53 staff, bars, input, clear, postscr: working
 10 May 2005 v52 commands red when active
  9 May 2005 v51 converting to C++ : menus drawn ok
 11 Oct 2004 fix openin = FALSE line (Arnold Wiegert)
  3 Feb 2003 keep bar numbers to the left
 10 Jan 2003 input menu abbreviations
 10 Jan 2003 flag redundant bar lines
 10 Jan 2003 output menu abbreviations
  4 Jan 2003 input menu initials
  4 Jan 2003 output menu initials
  4 Jan 2003 changed SPACE to VOLME, PATH to WAYS
  3 Jan 2003 ouput y and h values as 4 digits
  1 Jan 2003 adding batch mode 
 29 Aug 2002 adding unbar routine
 29 Aug 2002 fix size of rotation symbols
 17 Jan 2002 fix redrawing bar lines and symbol echoes
  6 Dec 2001 fix bar lines 
  2 Dec 2001 cleaning up
 29 Nov 2001 fix 1 & 2 pixel x alignment errors
  6 Dec 1998 fix bug in call to drawdots()
  6 Dec 1998 partly fix bug copying symbols near screen top
  6 Dec 1998 fix bug in key symbol 16 "."
 20 Nov 1998 moved start of bar lines up a bit
  6 Nov 1998 changed scale of PostScript output to 1.0
  9 Oct 1998 fix call to getargs()
 24 Jul 1998 add bar counter to barline 2nd item
 30 Nov 1996 improve contact bows, alter PostScript scale: 3 to 4
 27 Nov 1996 omit font commands from PostScript output
 26 Nov 1996 convert old 'hold' sign
 24 Nov 1996 initials of upper 10 commands used
 23 Nov 1996 make input score bottom = existing score top
 22 Nov 1996 duplicate staff lines removed
 21 Nov 1996 moved hold sign (50/9->125/7)
 20 Nov 1996 fix middle level pins
 19 Nov 1996 pop-up dialog box for input
 12 Nov 1996 key charwayers made up by vectors
 11 Nov 1996 optional height and width
  1 Nov 1996 expose events accommodated
 20 Oct 1996 diagonal lines added to wayh menu
 12 Oct 1996 auto snap/free on some symbol menus
 10 Oct 1996 can change bar lines double/single
  9 Oct 1996 contact bows smoothed
 29 Sep 1996 redraw command added
 26 Sep 1996 symbols sorted, bar lines numbered
 25 Sep 1996 scrolling vertically
 21 Sep 1996 swapped theevent.xkey.x with theevent.xkey.y!
	     (eXcursion 1.2A Win16 bug)
 13 Sep 1996 adapted for PC
  2 Sep 1996 redundant symbol elimination improved
 31 Aug 1996 postscript output improved
 27 Aug 1996 symbol menus improved
 25 Aug 1996 command menu improved
 24 Aug 1996 postscript output
 23 Aug 1996 automatic file write done only if score non-empty
 18 Aug 1996 area, wayh and hook menus added
 17 Aug 1996 menus cleaned up
 14 Aug 1996 staff drawn optionally
 14 Aug 1996 data structure altered
 13 Aug 1996 keyboard menu added
 13 Aug 1996 bar lines extend across used score
 12 Aug 1996 dotted background optional
 10 Aug 1996 fix up reading and writing to a file
  9 Aug 1996 menus shifted to side
        1991 modified for X-Windows: Don Herbison-Evans
        1989 direction symbols corrected: Myles Thomas
        1988 Computer Science Honours project: Simon Hunt
             Basser Department of Computer Science,
             University of Sydney

    subroutines -
      setup             - initialise variables
      moveabs           - move to a given screen position
      lineabs           - draw a line to given screen position
      moverel           - move by given amounts
      linerel           - draw a line by given amounts
      polylineabs       - draw a set of lines with absolute coordinates
      polylinerel       - draw a set of lines with relative coordinates
      sort              - sort an array into ascending order
      hashpolygonabs    - draw a hash filled absolute polygon
      fillpolygonabs    - draw a filled absolute polygon
      dopolygonrel      - draw an empty relative polygon
      setinfile         - open input file
      setoutfile        - open output file
      setpsfile         - open postscript output file
      delseg            - delete a picture
      highesty          - find highest non-staff-bar-barnumber symbol
      lbnsort           - sort score symbols into y order
      getout            - exit gracefully
      text              - draw some text on the display
      createsegment     - create a little picture
      closesegment      - close a picture
      drawbow           - draw contact bows
      setsymbol         - draw a symbol
      drawsymbol        - draw a symbol
      fixstaff          - ensure staff reaches above last symbol
      makebar           - draw a bar line
      digits            - find number of digits in a number
      dobarnumber       - draw bar numbers
      isbarnumber       - find out if a symbol is a bar number
      fixscore          - eliminate redundant symbols
      lbnwrite          - write out a file of the score in 'lbn' format
      drawstaff         - draw the staff
      createlow         - create the low command menu box
      createmiddle      - create the middle command menu box
      createhigh        - create the high command menu box
      createblank       - create the empty command menu box
      createhelp        - create the help command menu box
      createstaff       - create the staff command menu box
      createbars        - create the bars command menu box
      createminus       - create the minus command menu box
      createplus        - create the plus command menu box
      createclear       - create the clear command menu box
      createsnap        - create the snap command menu box
      createfree        - create the free command menu box
      createexpand      - create the expand command menu box
      createcontract    - create the contract command menu box
      createcopy        - create the copy command menu box
      createdel         - create the delete command menu box
      createmove        - create the move command menu box
      createpost        - create the post command menu box
      createinput       - create the input command menu box
      createoutput      - create the output command menu box
      createdirmenu     - create the direction symbol menu
      createfacmenu     - create the facings symbol menu
      createpinmenu     - create the pins symbol menu
      createlimmenu     - create the limbs symbol menu
      createvolmenu     - create the volce symbol menu
      createaremenu     - create the area symbol menu
      createrotmenu     - create the rotation symbol menu
      createkeymenu     - create the keys symbol menu
      createmismenu     - create the miscellaneous symbol menu
      createwaymenu     - create the wayh symbol menu
      createscroll      - create the up and down scroll bar
      create            - create the menus
      createmenus       - create all the menus
      unbar             - remove bar lines and bar numbers
      setbarsp          - find beats per bar
      drawbars          - draw the bar lines
      setxy             - set the coordinates of a symbol
      scale             - change the size of a symbol
      pswrite           - write postscript file of the score
      gettext           - get text to put on score
      lbnread           - read a file in 'lbn' format
      setlevel          - change the level of a symbol
      scrollstaff       - extend staff when scolling up
      makestaff         - create 3 more staff lines
      clear             - clear the score
      help              - list commands
      wait              - do nothing for a while
      addcomment        - add a comment in the .lbn file
      addtext           - add text to the score
      displayscore      - show all display lists
      docommand         - execute an item from the command menu
      dosymbol          - do something to a symbol
      checkeys          - check for a keyboard command
      checkhit          - find target of mouse click
      mouseclick        - process a mouse click
      mousetrack        - track mouse cursor
      doscroll          - scroll the score up and down
      initgraphics      - start the Opengl and glut systems
      t_main            - organises everything
*/
#include <iostream>
#include "glut.h" 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

#define WINDOW_WIDTH 700 
#define WINDOW_HEIGHT 650 
#define WINDOW_Y  20
#define WINDOW_X 300
#define WINDOW_MODE 
#define    ESCAPE     27
#define    MAXINT 1073741824
#define    BMAX      128      /* input text buffer size */
#define    IMAX    65535
#define    SMAX    10000      /* maximum number of symbols on score */
#define    TMAX        7      /* max number of characters in a command box */
#define    VMAX      100      /* max number of staff lines */
#define    HSTEP       6
#define    STEP       12
#define    TRUE        1
#define    FALSE       0
#define    MSIZE      75
#define    LINES      30
#define    NSYMS     226  // number of symbols in a menu */
#define    CH         15  // menu box height
#define    CW         45  // menu box width

#define    DUMMY       0  // menu command segment numbers
#define    CLEAR       1
#define    OPEN        2
#define    SAVE        3
#define    SAVEAS      4
#define    POST        5
#define    STAFF       6
#define    PLUS        7
#define    MINUS       8
#define    BARS        9
#define    TEXTL      10
#define    COMMENT    11

#define    SCROLLBX   12  // scroll box at left hand side */
#define    SCROLLUP   13
#define    SCROLLDN   14

#define    EXPAND     15
#define    CONTRACT   16
#define    COPY       17
#define    MOVE       18
#define    DELETEL    19
#define    LOW        20
#define    MIDDLE     21
#define    HIGH       22
#define    BLANK      23
#define    HELP       24
#define    SNAP       25
#define    FREE       26
#define    COMMANDS   27 /* number of menu commands */

// symbol menus-
#define    DIRN        1
#define    PINS        2
#define    FACE        3
#define    LIMB        4
#define    VOLM        5
#define    AREA        6
#define    ROTN        7
#define    KEYS        8
#define    MISC        9 
#define    WAYS       10
#define    STAF       11
#define    TOP        12

#define    MBARS      21
#define    MDOTS      22
#define    MDIRN       DIRN*NSYMS
#define    MPINS       PINS*NSYMS
#define    MFACE       FACE*NSYMS
#define    MLIMB       LIMB*NSYMS
#define    MVOLM       VOLM*NSYMS
#define    MAREA       AREA*NSYMS
#define    MROTN       ROTN*NSYMS
#define    MKEYS       KEYS*NSYMS
#define    MMISC       MISC*NSYMS
#define    MWAYS       WAYS*NSYMS
#define    MSTAF       STAF*NSYMS
#define    SCORE       TOP*NSYMS+1

char oldkeys[25] = {'#',
		'1','2','3','4','5','[',']','C','6','7','8','9','0',
		'(',')','.','_','+','~','<','>','\/','|','\\'};

char ptitle[BMAX];     // program title

char menutext[NSYMS][4] = {
     {'B','a','r','s'},
     {'D','i','r','n'},
     {'P','i','n','s'},
     {'F','a','c','e'},
     {'L','i','m','b'},
     {'V','o','l','m'},
     {'A','r','e','a'},
     {'R','o','t','n'},
     {'K','e','y','s'},
     {'M','i','s','c'},
     {'W','a','y','s'},
     {'S','t','a','v'} };

struct Segment {
   int w;             /* width */
   int h;             /* height */
   int x;             /* lower left corner x coordinate */
   int y;             /* lower left corner y coordinate */
   int menu;
   int item;
   int step;
   int ok;
   char level;        /* low, middle, high, or blank */
   char text[BMAX];   /* associated text */
   int length;        /* length of text */
   float red;         /* amount of red */
};
struct Segment segs[SMAX+1];

float fac;            /* change in symbol size for expand/contract */
float mfac;           /* scales positions of symbols in menus */
float inv2;
float r=0.0;          /* amount of red in segment */
float scalex;
float scaley;

int again;
int barsp;            /* beats per bar */
int bar0y;            /* y position of bar 0 */
int bar1y;            /* y position of bar 1 */
int bar2y;            /* y position of bar 2 */
int bardif;           /* y spacing between bar lines */
int barn;             /* number of bar lines */
int bary[SMAX];       /* bar height positions */
int beginy;
int button;           /* GLUT_DN or GLUT_UP */      
int currentx = 0;
int currenty = 0;
int dscroll;
int filledpin = FALSE;/* TRUE if filled pin being drawn */
int jx;               /* postscript offset for filled pins */
int mode;
int mousex,mousey;    /* mouse position */
int ncomments;
int oldmode;
int openin = FALSE;
int openout = FALSE;
int openpost = FALSE;
int pfont = 2;       /* size of previous font */
int pmove = TRUE;    /* TRUE if previous command was moveto */
int prevc = COPY;    /* previous command */
int psx,psy;         /* previous postscript moveto */
int saving;
int scoretop;
int snap;
int staffx[LINES];   /* x positions of staff lines */
int staffn;          /* number of staff lines */
int height;          /* height of window */
int width;           /* width of window */
int xw,yw;           /* position of window */
int target;          /* segment hit by mouse */
int xbot,ybot;       /* bottom left of displayed part of score */
int xtop,ytop;       /* top right of displayed part of score */
int xoffset=10;      /* shift all to right */
int yhigh;           /* top of highest symbol that is not a bar or staff */
int ymax;            /* top of score */

/*********************************/

char blank = 'B';
char high = 'H';
char low = 'L';
char middle = 'M';
char buf[BMAX];
char infile[BMAX];
char outfile[BMAX];
char postfile[BMAX]; 
char comments[BMAX][BMAX];
char finname[BMAX];
char foutname[BMAX];
char fpostname[BMAX];
char prevmove[BMAX];    /* previous domove command */
char rootname[BMAX] = {'l','e','d','\0'};

FILE    *INFILE;
FILE    *OUTFILE;
FILE    *POSTFILE;

/*************************************/

int cmdmenudx[LINES] = { 0, CW, 0, -CW, 0 };
int cmdmenudy[LINES] = { 0, 0, CH, 0, -CH };

int   aredx[NSYMS][LINES] = { {0},
         { 0, 2, 0, 0, 2, 0, -4, 0 },
         { 0, 4, 1, -1, 0, -4, 0 },
         { 0, 4, 0, 2, -2, 0, -4, 0 },
         { 0, 4, 0, 1, -1, -4, 0 },
         { 0, 4, 0, -2, 0, 0, -2, 0 },
         { 0, 4, 0, -4, -1, 1, 0 },
         { 0, 4, 0, -4, 0, -2, 2, 0 },
         { 0, 4, 0, -4, 0, -1, 1 },
         { 0, 4, 0, -4, 0 }
      };
int   aredy[NSYMS][LINES] = { {0},
         { 4, 0, 2, -2, 0, -4, 0, 4 },
         { 4, 0, 1, -1, -4, 0, 4, 0 },
         { 4, 0, -2, 0, 0, -2, 0, 4 },
         { 4, 0, -4, -1, 1, 0, 4 },
         { 4, 0, -4, 0, -2, 2, 0, 4 },
         { 4, 0, -4, 0, -1, 1, 4 },
         { 4, 0, -4, 0, 2, 0, 0, 2 },
         { 4, 0, -4, 0, 4, 1, -1 },
         { 4, 0, -4, 0, 4 }
      };
int   aremenudx[5] = { 0, MSIZE, 0, -MSIZE, 0};
int   aremenudy[5] = { 0, 0, MSIZE, 0, -MSIZE};
int   arex[NSYMS] = { 0, 40, 60, 75, 60, 40, 20, 10, 20, 40 };
int   arey[NSYMS] = { 0, 75, 65, 45, 25, 10, 25, 45, 65, 45 };
int   aremx;
int   aremy;
int   arestep = 3;
int   narea = 9;

int dirdx[NSYMS][LINES] = { {0,0,0,0,0,0,0},
   { 0,2,0,-1,0,-1,0 },
   { 0,2,0,-2,0,0,0 },
   { 0,2,-2,0,0,0,0 },
   { 2,0,-2,0,2,0,0 },
   { 0,1,0,1,0,-2,0 },
   { 1,1,0,-2,0,1,0 },
   { 0,2,0,-2,0,0,0 },
   { 2,0,-2,2,0,0,0 },
   { 0,0,2,0,-2,0,0 },
   { 0,2,0,-1,0,-1,0 },
   { 0,2,0,-2,0,0,0 }
      };
int dirdy[NSYMS][LINES] = { {0,0,0,0,0,0,0 },
   { 0,0,4,0,2,0,-6 },
   { 0,0,6,-2,-4,0,0 },
   { 0,3,3,-6,0,0,0 },
   { 0,6,0,-4,-2,0,0 },
   { 0,0,2,0,4,0,-6 },
   { 0,0,6,0,-4,0,-2 },
   { 0,2,4,0,-6,0,0 },
   { 0,6,-3,-3,0,0,0 },
   { 0,6,-2,-4,0,0,0 },
   { 0,0,6,0,-2,0,-4 },
   { 0,0,6,0,-6,0,0 }
      };
int dirmenudx[5] = { 0,MSIZE,0,-MSIZE,0 };
int dirmenudy[5] = { 0,0,2*MSIZE,0,-2*MSIZE };
int dirx[NSYMS] = { 0, 52, 68,76,68,52,36,20,14, 20, 36,46 };
int diry[NSYMS] = { 0,128,122,80,40,30,30,40,80,122,128,80 };
int dirmx;
int dirmy;
int dirstep = STEP/2 - 1;
int ndir = 11;


int   facdx[NSYMS][LINES] = { {0},
         { 4, 8, 0, -8, 0, 0, 8, -4, 0 },
         { 4, 8, 0, -8, 0, 0, 8, -4, 8 },
         { 4, 8, 0, -8, 0, 4, 0, 0, 8 },
         { 4, 8, 0, -8, 0, 8, -4, 8 },
         { 4, 8, 0, -8, 0, 0, 8, -4, 0 },
         { 4, 8, 0, -8, 0, 0, 8, -4, -8 },
         { 4, 8, 0, -8, 0, 4, 0, 0, -8 },
         { 4, 8, 0, -8, 0, 8, -4, -8 }
      };
int   facdy[NSYMS][LINES] = { {0},
         { 4, 0, 8, 0, -8, 4, 0, 0, 8, },
         { 4, 0, 8, 0, -8, 8, -8, 4, 8 },
         { 4, 0, 8, 0, -8, 0, 8, -4, 0 },
         { 4, 0, 8, 0, -8, 8, -4, -8 },
         { 4, 0, 8, 0, -8, 4, 0, 0, -8 },
         { 4, 0, 8, 0, -8, 8, -8, 4, -8 },
         { 4, 0, 8, 0, -8, 0, 8, -4, 0 },
         { 4, 0, 8, 0, -8, 8, -4, 8 }
      };
int   facmenudx[5] = { 0, MSIZE, 0, -MSIZE, 0};
int   facmenudy[5] = { 0, 0, MSIZE, 0, -MSIZE};
int   facx[NSYMS] = { 0, 40, 60, 75, 60, 40, 20, 5, 20 };
int   facy[NSYMS] = { 0, 75, 60, 40, 20, 5, 20, 40, 60 };
int   facmx;
int   facmy;
int   facstep = 1;
int   nfac = 9;

int   keydx[NSYMS][LINES] = { {0},
         { 0, 4, -2, 0, -1 },
         { 4, -3, 0, 3, 0, -1, -1, -1 },
         { 0, 1, 2, 1, 0, -1, -1, 1, 1, 0, -1, -1, -1 },
         { 3, 0, -3, 4 },
         { 0, 1, 1, 1, 0 , -1, -1, 0, 2 },
	 { 2, -2, 0, 2 },
	 { 0, 2, 0, -2 },
	 { 3, -1, -1, -1, 0, 1, 1, 1 },
         { 0, 1, 1, 1, 0, -1, -1, -1, 0, 1, 1, 1 },
	 { 0, 3, -3 },
	 { 1, 1, 0, -1, -1, -1, 0, 1, 1, 1, 0, -1, -1, -1, 0, 1 },
	 { 0, 1, 1, 1, 0, -1, -1, -1, 0, 1, 1, 1 }, 
	 { 0, 1, 1, 1, 0, -1, -1, -1, 0 },
	 { 2, -2, 0, 2 },
	 { 0, 2, 0, -2 },
	 { 2, 0, 1, 0, -1, 1 },
	 { 0, 4 },
	 { 2, 0, 0, -2, 4 },
	 { 1, 1, 2, 1 },
	 { 2, -2, 2 },
	 { 0, 2, -2 },
	 { 0, 4 },
	 { 2, 0 },
	 { 4, -4 }
      };
int   keydy[NSYMS][LINES] = { {0},
         { 0, 0, 0, 6, -1 },
         { 0, 0, 1, 3, 1, 1, 0, -1 },
         { 1, -1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, -1 },
         { 0, 6, -4, 0 },
         { 1, -1, 0, 1, 2, 1, 0, 2, 0 },
	 { 0, 0, 6, 0 },
	 { 0, 0, 6, 0 },
	 { 1, -1, 0, 1, 4, 1, 0, -1 },
         { 2, 1, 0, -1, -1, -1, 0, 1, 4, 1, 0, -1 },
	 { 0, 6, 0 },
	 { 0, 1, 1, 1, 0, 1, 1, 1, 0, -1, -1, -1, 0, -1, -1, -1 },
	 { 1, -1, 0, 1, 4, 1, 0, -1, -1, -1, 0, 1 }, 
	 { 1, -1, 0, 1, 4, 1, 0, -1, -4 },
	 { 0, 2, 2, 2 },
	 { 0, 2, 2, 2 },
	 { 1, 1, 0, -1, 0, 1 },
	 { 0, 0 },
	 { 0, 4, -2, 0, 0 },
	 { 2, 1, -2, 1 },
	 { 0, 3, 3 },
	 { 0, 3, 3 },
	 { 0, 6 },
	 { 1, 4 },
	 { 0, 6 }
      };
int   keymenudx[5] = { 0, MSIZE, 0, -MSIZE, 0};
int   keymenudy[5] = { 0, 0, MSIZE, 0, -MSIZE};
int   keyx[NSYMS] = { 0, 5, 17, 29, 41, 53, 65, 77, 84,
                          5, 17, 29, 41, 53, 65, 77, 89,
                          5, 17, 29, 41, 53, 65, 77, 89 };
int   keyy[NSYMS] = { 0, 20, 20, 20, 20, 20, 20, 20, 20,
                          50, 50, 50, 50, 50, 50, 50, 50,
                          75, 75, 75, 75, 75, 75, 75, 75 };
char  key[NSYMS]= { '1','2','3','4','5','[',']','C',
                    '6','7','8','9','0','(',')','.',
                    '_','+','~','<','>','/','|','\\' };
int   kx[NSYMS] = { 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 3,
						  0, 0, 0, 0, 0, 0, 0, 0 };
int   ky[NSYMS] = { 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 1,
						  0, 0, 0, 0, 0, 0, 0, 0 };
int   keymx;
int   keymy;
int   keystep = 2;
int   nkey = 24;

int   limdx[NSYMS][LINES] = { {0},
         { 1, 1, 0 },
         { 1, 1, 0, -1, 1 },
         { 1, 1, 0, -1, 1, 0, -1 },
         { 1, 1, 0, -1, 1, 0, -1, 1, 0, -1 },
         { 1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1 },
         { 1, 0, 1 },
         { 2, -1, 0, 1 },
         { 2, -1, 0, 1, -1, 0, 1 },
         { 2, -1, 0, 1, -1, 0, 1, -1, 0, 1 },
         { 2, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1 },
         { 2, 0, -1, 1, 0 },
         { 2, 0, -1, 1, 0, -1, 1, 0 },
         { 2, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0 },
         { 2, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0 },
         { 2, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0 },
         { 1, 0, 1, -1, 0 },
         { 1, 0, 1, -1, 0, 1, -1, 0 },
         { 1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0 },
         { 1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0 },
         { 1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0, 1, -1, 0 , 1, -1, 0 },
         { 0, 0, 2, 0 },
         { 0, 0, 0, 2, 0 }
      };
int   limdy[NSYMS][LINES] = { {0},
         { 4, 1, -2 },
         { 2, 1, 2, -1, 1 },
         { 2, 1, 1, -1, 1, 1, -1 },
         { 1, 1, 1, -1, 1, 1, -1, 1, 1, -1 },
         { 0, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1 },
         { 4, 2, -1 },
         { 3, 1, 2, -1 },
         { 3, 1, 1, -1, 1, 1, -1 },
         { 2, 1, 1, -1, 1, 1, -1, 1, 1, -1 },
         { 1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1 },
         { 4, 1, 0, 0, 1 },
         { 3, 1, 0, 0, 1, 0, 0, 1 },
         { 2, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
         { 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
         { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
         { 0, 1, 0, 0, 1 },
         { 0, 1, 0, 0, 1, 0, 0, 1 },
         { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
         { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
         { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
         { 0, 3, 0, -3 },
         { 0, 3, -3, 0, 3 }
      };
int   limmenudx[5] = { 0, MSIZE, 0, -MSIZE, 0};
int   limmenudy[5] = { 0, 0, 2*MSIZE, 0, -2*MSIZE};
int   limx[NSYMS] = { 0,  5, 20, 40, 60, 80, 5,  20, 40, 60, 80,
                          5, 20, 40, 60, 80, 5,  20, 40, 60, 80,
                          10, 30 };
int   limy[NSYMS] = { 0, 10, 10, 10, 10, 10, 30, 35, 40, 45, 50,
                100, 100, 100, 100, 100, 140, 140, 140, 140, 140,
                90, 90 };
int   limmx;
int   limmy;
int   limstep = 4;
int   nlim = 22;


int   misdx[NSYMS][LINES] = { {0},
         { 0, 2, 3, 3, 3, 2 },
         { 0, 0, 1, 1, 1, 0 },
         { 0, 0, 1, 1, 1, 0 },
         { 0, 1, 1, 0 },
         { 2, -1, -1, 0 },
         { 0, 1, 1, 0 },
         { 2, -1, -1, 0 },
         { 2, 0, -1, -1, 1, 1, 0 },
         { 0, 0, 1, 1, -1, -1, 0 }
      };
int   misdy[NSYMS][LINES] = { {0},
         { 3, -1, -1, 0, 1, 1 },
         { 2, -1, -1, 0, 1, 1 },
         { 0, 1, 1, 0, -1, -1 },
         { 0, 0, 1, 1 },
         { 0, 0, 1, 1 },
         { 1, 0, -1, -1 },
         { 1, 0, -1, -1 },
         { 3, -1, -1, 0, 0, -1, -1 },
         { 3, -1, -1, 0, 0, -1, -1 }
      };
int   mismenudx[5] = { 0, MSIZE, 0, -MSIZE, 0};
int   mismenudy[5] = { 0, 0, MSIZE, 0, -MSIZE};
int   misx[NSYMS] = { 0, 20, 10, 10, 35, 40, 55, 55, 75, 75 };
int   misy[NSYMS] = { 0, 10, 40, 70, 40, 70, 45, 73, 40, 70 };
int   mismx;
int   mismy;
int   misstep = 4;
int   nmisc = 9;

int   pindx[NSYMS][LINES] = { {0},
         { 10, 2, 1, -1, -2, 0, 0, -2, -1, 1, 2 },
         { 10, 2, 1, -1, 8, -8, -2, -2, -1, 1, 2 },
         { 10, 2, 1, 8, -8, -1, -2, -2, -1, 1, 2 },
         { 10, 2, 8, -8, 1, -1, -2, -2, -1, 1, 2 },
         { 10, 0, 0, 2, 1, -1, -2, -2, -1, 1, 2 },
         { 10, 2, 1, -1, -2, -2, -1, 1, -8, 8, 2 },
         { 10, 2, 1, -1, -2, -2, -1, -8, 8, 1, 2 },
         { 10, 2, 1, -1, -2, -2, -8, 8, -1, 1, 2 },
	 { 8, 6, -3, 0 },
	 { 8, 5, -2, 4 },
	 { 10, 0, 0, 6 },
	 { 8, 5, -3, 4 },
	 { 8, 6, -3, 0 },
	 { 9, 5, -2, -4 },
	 { 10, 0, 0, -6 },
	 { 9, 5, -3, -4 }
      };
int   pindy[NSYMS][LINES] = { {0},
         { 8, 1, 2, 2, 1, 8, -8, -1, -2, -2, -1 },
         { 8, 1, 2, 2, 8, -8, 1, -1, -2, -2, -1 },
         { 8, 1, 2, 0, 0, 2, 1, -1, -2, -2, -1 },
         { 8, 1, -8, 8, 2, 2, 1, -1, -2, -2, -1 },
         { 8, -8, 8, 1, 2, 2, 1, -1, -2, -2, -1 },
         { 8, 1, 2, 2, 1, -1, -2, -2, -8, 8, -1, },
         { 8, 1, 2, 2, 1, -1, -2, 0, 0, -2, -1 },
         { 8, 1, 2, 2, 1, -1, 8, -8, -2, -2, -1 },
	 { 10, 0, 0, 6 },
	 { 14, -5, 2, 4 },
	 { 8, 6, -3, 0 },
	 { 8, 5, -3, -4 },
	 { 12, 0, 0, -6 },
	 { 14, -5, 2, -4 },
	 { 8, 6, -3, 0 },
	 { 8, 5, -3, 4 }
      };
int   pinmenudx[5] = { 0, MSIZE, 0, -MSIZE, 0};
int   pinmenudy[5] = { 0, 0, MSIZE, 0, -MSIZE};
int   pinx[NSYMS] = { 0, 35, 55, 65, 60, 35, 15, 5, 15,
			 40, 58, 65, 58, 45, 32, 30, 32 };
int   piny[NSYMS] = { 0, 65, 60, 40, 15, 10, 15, 40, 60,
			 65, 65, 50, 35, 30, 35, 50, 65 };
int   pinmx;
int   pinmy;
int   pinstep = 1;
int   npin = 8;

int   rotdx[NSYMS][LINES] = { {0},
         { 2, 0, -2, 0, 2 },
         { 0, 2, 0, -2, 0, 0 },
         { 0, 1, 1, 0, -1, -1 },
         { 1, 1, 0, -1, -1, 0, 1 },
         { 0, 2, 0, -2, 2, -2, 0, 2 },
         { 2, -2, 0, 2, -2, 2, 0, -2 },
         { 0, 1, 1, 0, -1, -1, 0 },
         { 1, 1, 0, -1, -1, 0, 1 }
      };
int   rotdy[NSYMS][LINES] = { {0},
         { 0, 4, 2, -4, -2 },
         { 0, 2, 4, -2, -4, 0 },
         { 0, 1, -1, 5, 1, -1, -5 },
         { 0, 1, 5, -1, 1, -5, -1 },
         { 0, 1, 3, 1, 1, -1, -3, -1 },
         { 0, 1, 3, 1, 1, -1, -3, -1 },
         { 0, 1, -1, 6, -1, 1, -6 },
         { 0, 1, 4, 1, -1, -4, -1 }
      };
int   rotmenudx[5] = { 0, MSIZE, 0, -MSIZE, 0};
int   rotmenudy[5] = { 0, 0, MSIZE, 0, -MSIZE};
int   rotx[9] = { 0, 8, 30, 55, 80, 8, 30, 55, 80 };
int   roty[9] = { 0, 57, 57, 57, 57, 7, 7, 7, 7 };
int   rotmx;
int   rotmy;
int   rotstep = STEP/2;
int   nrot = 8;

int   voldx[NSYMS][LINES] = { {0},
         { 0, 8, -4, -4, 8 },
         { 0, 0, 8, 0 },
         { 0, 8, -2, -2, 8, -6, -2, -4, 8, -2, -2, 8 },
         { 0, 0, 8, 0, 0, -8 },
         { 5, -5, 5, 5, -5 },
         { 4, 2, 1, 6, -6, -1, -2, 0, 0, -2, -1, -6, 6, 1, 2, 0},
         { 4, 2, 2, 0, -2, -2, -2, 0, 2 }
      };
int   voldy[NSYMS][LINES] = { {0},
         { 0, 8, -4, 4, -8 },
         { 8, -8, 8, -8 },
         { 0, 8, -2, 2, -8, 6, -2, 4, -8, 2, -2, 8 },
         { 8, -6, 6, -8, 6, -6 },
         { 0, 7, 7, -7, -7 },
         { 0, 1, 2, 0, 0, 2, 1, 6, -6, -1, -2, 0, 0, -2, -1, -6 },
         { 2, 0, 2, 2, 2, 0, -2, -2, -2 }
      };
int   volmenudx[5] = { 0, MSIZE, 0, -MSIZE, 0};
int   volmenudy[5] = { 0, 0, MSIZE, 0, -MSIZE};
int   volx[NSYMS] = { 0, 15, 15, 45, 45, 75, 75, 36 };
int   voly[NSYMS] = { 0, 20, 70, 20, 70, 20, 70, 42 };
int   volmx;
int   volmy;
int   volstep = 1;
int   nvol = 7;

int   waydx[NSYMS][LINES] = { {0},
         { 0, 2, -1, 0 },
         { 1, 0, -1, 2 },
         { 0, 0 },
         { 1, -1, 1, 1 },
         { 0, 1, 1 },
		 { 3, -1, -1, 0, 1, 1 },
		 { 0, 1, 1, 0, -1, -1 }
      };
int   waydy[NSYMS][LINES] = { {0},
         { 0, 0, 0, 4 },
         { 0, 4, 0, 0 },
         { 0, 4 },
         { 0, 4, -4, 4 },
         { 0, 4, -4 },
		 { 0, 2, 4, 5, 4, 2 },
		 { 0, 2, 4, 5, 4, 2 }
      };
int   waymenudx[5] = { 0, MSIZE, 0, -MSIZE, 0};
int   waymenudy[5] = { 0, 0, MSIZE, 0, -MSIZE};
int   wayx[9] = { 0, 30, 30, 50, 60, 60,  5, 80 };
int   wayy[9] = { 0, 10, 60, 30, 12, 62, 15, 15 };
int   waymx;
int   waymy;
int   waystep = STEP/2;
int   nway = 7;

int   arrowupdx[7] = { 10,  0, 4, -9, -9, 4,  0 };
int   arrowupdy[7] = {  0,  8, 0,  8, -8, 0, -8 };
int   arrowdndx[7] = {  9,  0, 2, -6, -6, 2,  0 };
int   arrowdndy[7] = {  0, -8, 0, -8,  8, 0,  8 };

/************************************************/

void moveabs(int x, int y)
/*
   called by makebar, createscroll, drawsymbol, setsymbol,
             drawbow, createmiddle, createsegment,
             dopolygonrel, fillpolygonabs, hashpolygonabs,
             polylineabs, moverel,
*/
{
   currentx = x;
   currenty = y;
   if (openpost == TRUE)
   {
      psx = x;
      psy = y;
      sprintf(prevmove,"%d %d moveto\n",x+xoffset,y);
      pmove = TRUE;
   }
} /*  moveabs */
/******************************************/

void lineabs(int x, int y)
/*
   called by drawbow, fillpolygonabs, hashpolygonabs,
             polylinerel, polylineabs, linerel,
*/
{
   int a,b;

   a = 0; b = 0;
   if (currentx > x)
      a = 1;
   else
      b = 1;
   glVertex2f(float(currentx+a)*scalex, float(currenty)*scaley);
   glVertex2f(float(x+b)*scalex,float(y)*scaley);
   if (openpost == TRUE)
	{
		if (pmove == TRUE)
			fprintf(POSTFILE,"%s",prevmove);
		if ((psx == x)&&(psy == y)&&(filledpin == TRUE))
		{
			fprintf(POSTFILE,"%d %d lineto\n",x+xoffset+jx,y);
		}
		fprintf(POSTFILE,"%d %d lineto\n",x+xoffset,y);
	}
   currentx = x;
   currenty = y;
	pmove = FALSE;
} /*  lineabs */
/******************************************/

void moverel(int x, int y)
/*
   called by createscroll, createcontract, createexpand,
             createplus, createminus, createbars,
             createmiddle, dopolygonrel, polylinerel,
   calls     moveabs,
*/
{
   currentx += x;
   currenty += y;
   moveabs(currentx,currenty);
} /*  moverel */
/******************************************/

void linerel(int x, int y)
/*
   called by makebar, createscroll, drawsymbol,
             createinput, createpost, createmove,
             createdel, createcopy, createcontract,
             createexpand, createfree, createsnap,
             createclear, createplus, createminus,
             createbars, createstaff, drawstaff,
             fillpolygonabs,
   calls     lineabs,
*/
{
	lineabs(x+currentx,y+currenty);
} /* linerel */
/******************************************/

void polylineabs(int xarray[], int yarray[], int n)
/*
   draw a set of lines

   called by dopolygonrel,
   calls     moveabs, lineabs.
*/
{
   int j;

   moveabs(xarray[0],yarray[0]);
   for (j = 0; j < n; ++j)
   {
      lineabs(xarray[j],yarray[j]);
   }
} /* polylineabs */
/*****************************************/

void polylinerel(int xarray[], int yarray[], int n)
/*
   draw a set of lines

   called by createmismenu, createkeymenu, createrotmenu,
             createaremenu, createvolmenu, createlimmenu,
             createlimmenu, createfacmenu, createdirmenu,
             createcontract, createexpand, createblank,
             createwaymenu,
   calls     moverel, lineabs,
*/
{
   int j;

   moverel(xarray[0],yarray[0]);
   for (j = 1; j < n; ++j)
   {
      lineabs(currentx+xarray[j],currenty+yarray[j]);
   }
} /*   polylinerel */
/*****************************************/

void sort(int a[LINES], int n)
/*
   to sort n entries in array a into ascending order
   using bubble sort.

   called by  setxy, fillpolygonabs, hashpolygonabs,
              makestaff, fixstaff,
*/
{
   int j,k;
   int temp;

   for (j = 0; j < (n-1); ++j)
   {
      for (k = (j+1); k < n; ++k)
      {
         if (a[j] > a[k])
         {
            temp = a[j];
            a[j] = a[k];
            a[k] = temp;
         }
      }
   }
} /* sort */
/***************************************/

void hashpolygonabs(int ax[LINES], int ay[LINES], int n)
/*
   draw a hashed polygon with n sides with
   diagonal lines volced by HSTEP

   called by dopolygonrel,
   calls     moveabs, lineabs, sort,
*/
{
   float dy;
   float hstep;
   int j;
   float maxy,miny;
   int nx;
   float y;
   int xcut[SMAX];
   int xstart,xend;
   float x1[LINES],x2[LINES],y1[LINES],y2[LINES];

   hstep = HSTEP;
   x1[0] = ax[n-1]+ay[n-1];
   y1[0] = ax[n-1]-ay[n-1];
   maxy = y1[0]; 
   miny = y1[0];
   for (j = 0; j < n; ++j)
   {
      x2[j] = ax[j]+ay[j];
      y2[j] = ax[j]-ay[j];
      if (y1[j] > y2[j])
      {
         x2[j] = x1[j]; 
         y2[j] = y1[j];
         x1[j] = ax[j]+ay[j];
         y1[j] = ax[j]-ay[j];
      }
      if (y2[j] > maxy) maxy = y2[j];
      if (y1[j] < miny) miny = y1[j];
      if (j < (n-1))
      {
         x1[j+1] = ax[j]+ay[j];
         y1[j+1] = ax[j]-ay[j];
      }
   }
   for ( y = miny-inv2; y < maxy+inv2; y += hstep)
   {
      nx = 0;
      for (j = 0; j < n; ++j)
      {
         if ((y >= y1[j]) && ( y <= y2[j]))
         {
            dy = y2[j] - y1[j];
            if (dy != 0)
            {
               xcut[nx] = inv2 + x2[j] - (x2[j]-x1[j])*(y2[j]-y)/dy;
               ++nx;
            }
            else
            {
               xcut[nx] = x1[j]; ++nx;
               xcut[nx] = x2[j]; ++nx;
            }
         }
      }
      sort(xcut,nx);
      for (j = 0; j < (nx-1) ; j += 2)
      {
         xstart = xcut[j]; xend = xcut[j+1];
         if (xstart != xend)
         {
            moveabs((xstart+y)/2, (xstart-y)/2);
            lineabs((xend+y)/2,(xend-y)/2);
         }
      }
   }
} /* hashpolygonabs */
/***************************************/

void fillpolygonabs(int ax[LINES], int ay[LINES], int n)
/*
   draw a filled polygon with n sides

   called by dopolygonrel,
   calls     moveabs, lineabs, sort, linerel,
*/
{
   int dyj;
   int j,k;
   int maxy,miny;
   int newn;
   int nx;
   int tempx,tempy;
   int y;
   int xcut[LINES];
   int xstart,xend;
   int x1[LINES],x2[LINES],y1[LINES],y2[LINES];

   x1[0] = ax[n-1];
   y1[0] = ay[n-1];
   j = 0;
   for (k = 0; k < n; ++k)
   {
      x2[j] = ax[k];
      y2[j] = ay[k];
      if ((x1[j] != x2[j]) || (y1[j] != y2[j]))
         ++j;
      x1[j] = ax[k];
      y1[j] = ay[k];
   }
   newn = j;
   maxy = y1[0]; miny = y1[0];
   for (j = 0; j < newn; ++j)
   {
      if (y1[j] > y2[j])
      {
         tempx = x2[j]; tempy = y2[j];
         x2[j] = x1[j]; y2[j] = y1[j];
         x1[j] = tempx; y1[j] = tempy;
      }
      if (y2[j] > maxy) maxy = y2[j];
      if (y1[j] < miny) miny = y1[j];
   } /* j */
   for ( y = miny; y <= maxy; ++y)
   {
      nx = 0;
      for (j = 0; j < newn; ++j)
      {
         if ((y1[j] <= y) && ( y <= y2[j]))
         {
            dyj = y2[j] - y1[j];
            if (dyj == 0)
               xcut[nx] = x1[j];
            else
               xcut[nx] = x2[j] - (x2[j]-x1[j])*(y2[j]-y)/dyj;
            if ((j > 0) && (nx > 0))
            {
               if (xcut[nx-1] != xcut[nx])
                  ++nx; 
            }
            else
               ++nx; 
            if (dyj == 0)
            {
               xcut[nx] = x2[j];
               ++nx;
            } /* dyj == 0 */
         } /* y2 <= y <= y1 */
      } /* j */
      sort(xcut,nx);
      if ((nx > 2) && (nx%2 == 1))
      {
         xcut[nx] = xcut[nx-2]; 
         ++nx;
      }
      if (nx == 0)
      {
         moveabs(xcut[0],y);
         linerel(2,0);
      }
      else
      for (j = 0; j < nx ; j += 2)
      {
         xstart = xcut[j]; xend = xcut[j+1];
         if ((xend > 0) && (xstart < width))
         {
            if (xstart < 0) xstart = 0;
            if (xend > width) xend = width;
            moveabs(xstart,y);
            lineabs(xend,y);
         } /* xstart and xend on screen */
      } /* j */
   } /* y */
} /* fillpolygonabs */
/***************************************/

void dopolygonrel(int s, int ax[LINES], int ay[LINES], int n)
/*
   draw a polygon for segment s,
   defined by ('n'-1) relative moves after an initial move,
   and mark it according to 'level'.

   called by createhigh, createmiddle, createlow,
             createhelp, createblank, setsymbol,
   calls     moverel, fillpolygonabs, hashpolygonabs, 
             polylineabs, moveabs, 
*/
{
   int aax[LINES],aay[LINES];
   int cx,cy;
   int cmx,cmy;
   int h;
   int i;
   int j;
   int m;
   int nn;
   int w;
   char level;

   cx = currentx;
   cy = currenty;
   moverel(ax[0],ay[0]);
   aax[0] = currentx;
   aay[0] = currenty;
   nn = 1;
   h = segs[s].h;
   i = segs[s].item;
   m = segs[s].menu;
   w = segs[s].w;
   level = segs[s].level;
   for (j = 1; j < n; ++j)
   {
      if ((ax[j] == 0) && (ay[j] == 0)) break;
      moverel(ax[j],ay[j]);
      aax[nn] = currentx;
      aay[nn] = currenty;
      ++nn;
   }
   if (level == low)
      fillpolygonabs(aax,aay,nn);
   else
   if (level == high)
   {
      moveabs(cx,cy);
      moverel(ax[0],ay[0]);
      polylineabs(aax,aay,nn);
      hashpolygonabs(aax,aay,nn);
   }
   else
   {
      moveabs(cx,cy);
      moverel(ax[0],ay[0]);
      polylineabs(aax,aay,nn);
      if (level == middle)
      {
         cmx = cx+w/2;
         cmy = cy+h/2;
         if ((m == MDIRN)&&(i == 6))
            ++cmy;
         else
         if ((m == MVOLM)&&(i == 7))
         {
            --cmy;
            --cmx;
         }
         moveabs(cmx,cmy);
         lineabs(cmx,cmy+1);
      }
   }
} /* dopolygonrel */
/*****************************************/

void setinfile(void)
/*
   set up input .lbn file

   called by lbnread,
*/
{
	int  c;
	char key;

	if (rootname[0] != NULL)
	{
	   sprintf(finname,"%s.lbn",rootname);
	   printf("\nCurrent input file name is %s\n",finname);
	   printf("Please hit 'Enter' to use this name\n");
       printf("else type root name of .lbn input file,\n");
	}
	else
		printf("Please type root name of .lbn input file,\n");
	c = 0;
another:
	key = getchar(); 
	if (key == '\n') goto gotit;
	rootname[c++] = key; 
	goto another;
gotit:
	sprintf(finname,"%s.lbn",rootname);
	if ((INFILE = fopen(finname,"r")) == NULL)
	{
           if (INFILE) fclose(INFILE);
		   openin = FALSE;
           printf("\n\n oops: cannot open %s for reading?\n",
			   finname);
		   for (  c = 0 ; c < BMAX ; ++c )
              rootname[c] = NULL;
	}
	else
	{
	   openin = TRUE;
	   printf("\nopened input file %s OK for reading\n",
		   finname);
	}
} /* setinfile */
/***************************************/

void setpsfile(void)
/*
   set up postscript file

   called by pswrite,
*/
{
	int  c;
	char key;

	if (rootname[0] != NULL)
	{
	   sprintf(fpostname,"%s.ps",rootname);
	   printf("\nCurrent Postscript file name is %s\n",fpostname);
	   printf("Please hit 'Enter' to use this name,\n");
       printf("else type root name of required .ps file:\n");
	}
	else
		printf("Please type root name of .ps Postscript file,\n");
	c = 0;
another:
	key = getchar(); 
	if (key == '\n') goto gotit;
	if (c == 0)
	{
		for (  c = 0 ; c < BMAX ; ++c )
           rootname[c] = NULL;
		c = 0;
	}
	rootname[c++] = key; 
	goto another;
gotit:
	sprintf(fpostname,"%s.ps",rootname);
	if ((POSTFILE = fopen(fpostname,"w")) == NULL)
	{
           if (POSTFILE) fclose(POSTFILE);
           printf("\n\n oops, cannot open %s for writing?\n",
              fpostname);
           for (  c = 0 ; c < BMAX ; ++c )
              rootname[c] = NULL;
	}
	else
	   printf("\n opened output postscript file %s OK for writing\n",fpostname);
} /* setpsfile */
/***************************************/

void delseg(int s)
/*
   delete segment 's'

   called by  mouseclick, dosymbol, clear, setlevel,
              scale, fixscore, createbars,
*/
{
    if (s >= SCORE)
    {
       glDeleteLists(s,1);
       segs[s].ok = FALSE;
       segs[s].menu = -1;
       segs[s].length = 0;
       sprintf(segs[s].text," ");
    }
} /* delseg */
/********************************************/

void highesty(void)
/*
   put into yhigh the y+h of highest symbol that
   is not a barline, staff, or bar number

   called by  fixscore, docommand, lbnread,
*/
{
    int m;
    int s;
    int y;

    yhigh = height;
    for (s = SCORE; s < scoretop; ++s)
    {
       m = segs[s].menu;
       if ((segs[s].ok == TRUE)
          &&(m != MBARS)&&(m != MSTAF)
          &&((m != MKEYS)||(segs[s].x > 100)))
       {
          y = segs[s].y+segs[s].h;
          if (yhigh < y) yhigh = y;
       }
    }
} /* highesty */
/************************************/


void copyseg(int n, int s)
/* copy segment s into segment n

   called by fixscore, setlevel, scale, lbnsort,
		mouseclick,
*/
{
   segs[n].ok = TRUE;
   segs[n].x = segs[s].x;
   segs[n].y = segs[s].y;
   segs[n].h = segs[s].h;
   segs[n].w = segs[s].w;
   segs[n].item = segs[s].item;
   segs[n].menu = segs[s].menu;
   segs[n].step = segs[s].step;
   segs[n].level = segs[s].level;
   segs[n].length = segs[s].length;
   segs[n].red = segs[s].red;
   strcpy(segs[n].text,segs[s].text);
} /* copyseg */
/************************************/

void lbnsort(void)
/*
   sort score symbols into ascending order of 'y'
   (bubble sort) and renumber bar lines.
   Also find highest symbol that is not a 
   barline, staff, or bar number.

   called by getout, lbnwrite,
	calls     copyseg,
*/
{
   int prevbar;
   int j;
   int k;

   prevbar = -1;
   for (j = SCORE; j < (scoretop-1); ++j)
   {
      if (segs[j].ok == TRUE)
      {
         for (k = j; k < scoretop; ++k)
         {
            if ((segs[k].y < segs[j].y)
               &&(segs[k].ok == TRUE))
            {
               copyseg(SMAX,k);
               copyseg(k,j);
               copyseg(j,SMAX);
            } /* segs[k].y < segs[j].y  */
         } /* k */
      } /* j ok */
   } /* j */
   k = 0;
   // renumber the bars
   for (j = SCORE; j < scoretop; ++j)
   {
      if ((segs[j].ok == TRUE)&&(segs[j].menu == MBARS))
      {
         if (segs[j].y != prevbar)
            segs[j].item = k++;
         else
         {
            if (k < 3)
               segs[j].item = -1;
            else
               delseg(j);
         }
         prevbar = segs[j].y;
      } /* MBARS */
   } /* j */
}   /* lbnsort */
/************************************************/

void getout(int v)
/*
   exit gracefully

   called by main, checkeys,
   calls     lbnsort, lbnwrite,
*/
{
   printf("getouta %d %d\n",scoretop,SCORE);
   if ( v > 0 ) printf("led error: %d\n",v);
   if (POSTFILE) fclose(POSTFILE);
   if (OUTFILE) fclose(OUTFILE);
   if (INFILE) fclose(INFILE);
again:
   if (v != 0) goto again;
   exit(0);
} /*  getout */
/******************************************/

void text(int s)
/*
   draw some text

   called by  closesegment,
              (createbars, docommand, createcmndmenu).
	GLUT_BITMAP_TIMES_ROMAN_10	0
	GLUT_BITMAP_TIMES_ROMAN_24	1
	GLUT_BITMAP_HELVETICA_10	2
	GLUT_BITMAP_HELVETICA_12	3
	GLUT_BITMAP_HELVETICA_18	4
*/
{
   int j,len,ts;

   len = segs[s].length;
   ts = segs[s].step;
   if (ts < 0) ts = 0;
   if (ts > 4) ts = 4;
   segs[s].step = ts;
   glClearColor(1.0,1.0,1.0,0.0);
   glColor3f(segs[s].red, 0.0, 0.0);
   glRasterPos2f(
		scalex*float(segs[s].x + 2),
		scaley*float(segs[s].y + 2) );
   for (j = 0; j < len; ++j)
   {
      if (ts == 0)
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,segs[s].text[j]);
      else if (ts == 1)
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,segs[s].text[j]);
      else if (ts == 2)
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,segs[s].text[j]);
      else if (ts == 3)
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,segs[s].text[j]);
      else if (ts == 4)
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,segs[s].text[j]);
   }
} /* text */
/******************************************/

void createsegment(int s)
/*
   called by setlevel, makebar, createscroll,
             createwaymenu, createmismenu, createkeymenu,
             createrotmenu, createaremenu, createvolmenu,
             createlimmenu, createlimmenu, createfacmenu,
             createdirmenu, drawsymbol, setsymbol,
             createopen, createpost, createmove,
             createdel, createcopy, createcontract,
             createexpand, createfree, createsnap,
             createclear, createplus, createminus,
             createbars, createstaff, createblank,
             createhigh, createmiddle, createlow,
             drawstaff, createhelp,
   calls     moveabs,
*/
{  
   if ( ((segs[s].y+segs[s].h) > ybot)
     && ((segs[s].y-segs[s].h) < ytop) )
   {
      currentx = segs[s].x;
      currenty = segs[s].y;
   }
   if (s > scoretop) scoretop = s;
   if (scoretop >= SMAX)
   {
      s = -1;
      printf("max %d segments created\n",scoretop);
      getout(2);
   }
   else
   {
      //target = s;
      segs[s].ok = TRUE;
      moveabs(segs[s].x,segs[s].y);
 
      glNewList(s,GL_COMPILE);
      glBegin(GL_LINES);
	  glClearColor(1.0,1.0,1.0,0.0);
      glColor3f(segs[s].red, 0.0, 0.0);
   }
} /*  createsegment */
/******************************************/

void closesegment(int s)
/*
   close a segment

   called by  setlevel, makebar, createscroll,
              createwaymenu, createmismenu, createkeymenu,
              createrotmenu, createaremenu, createvolmenu,
              createlimmenu, createlimmenu, createfacmenu,
              createdirmenu, drawsymbol, setsymbol,
              createinput, createpost, createmove,
              createdel, createcopy, createcontract,
              createexpand, createfree, createsnap,
              createclear, createplus, createminus,
              createbars, createstaff, createblank,
              createhigh, createmiddle, createlow,
              drawstaff, createhelp,
*/
{
	glEnd();
	if (segs[s].length != 0)
	{
		text(s);
		if (openpost == TRUE)
		{
			if (pfont != segs[s].step)
			{
			   fprintf(POSTFILE,
				   "/Times-Roman findfont %d scalefont setfont\n",
					8+2*segs[s].step);
				pfont = segs[s].step;
			}
			fprintf(POSTFILE,"%s",prevmove);
         fprintf(POSTFILE," (%s) show\n",segs[s].text);
		}
	}
	glEndList();
	pmove = FALSE;
} /* closesegment */
/*********************************************/

void drawbow(int s)
/*
   draw contact/approach bows

   called by setsymbol,
   calls     lineabs, moveabs.
*/
{
   char l;
   int a,b,h,w,x,y;
   int j;
   int nbows;
   float xx,yy;
   float doub0,doub1;

   doub0 = float(0);
   doub1 = float(1);
   a = segs[s].x;
   b = segs[s].y;
   h = segs[s].h;
   w = segs[s].w;
   l = segs[s].level;
   if (l == low) nbows = 2;
      else nbows = 1;
   for (j = 0; j < nbows; ++j)
   {
      moveabs(a,b+h+3*j);
      for (x = a; x <= (a+w); x += 3)
      {
         xx = float(2*(x-a))/float(w) - doub1;
         yy = xx * xx * xx;
         if (yy < doub0) yy = -yy;
         y = h*yy + b + float(3*j);
         if ( (l == high) &&
            ( (((x-a)%4) == 2) || (((x-a)%4) == 3) ) )
            moveabs(x,y);
         else
            lineabs(x,y);
      } /* x */
   } /* j */
} /*  drawbow */
/*******************************************/

void setsymbol(int s, int m, int ax[NSYMS][LINES], int ay[NSYMS][LINES], int j, int d, char level)
/*
   set up dx and dy lengths for 'j'th symbol and draw it
   using blank, fill, dot or hash according to 'level'.

   called by setlevel, drawsymbol,
   calls     createsegment, dopolygonrel, moveabs,
             closesegment, drawbow,
*/
{
   int axji,ayji;
   int dx[LINES];
   int dy[LINES];
   int i;
   int doneup;
   int donedn;
   int oldy;
   int newy;
   int dw,dh;

   createsegment(s);
   m = segs[s].menu;
   if (m == MDIRN)
	   dh = (segs[s].h+1)/6;
   else
	   dh = d;
   if ((m == MWAYS)
    || (m == MDIRN)
    || (m == MROTN))
	   dw = dirstep;
   else
   if (m == MAREA)
	   dw = arestep;
   else
	   dw = d;
   doneup = FALSE;
   donedn = FALSE;
   oldy = 0;
   newy = 0;
   for (i = 0; i < LINES; ++i)
   {
      axji = ax[j][i];
      ayji = ay[j][i];
      if ((i != 0) && (axji == 0) && (ayji == 0))
		  break;
      dx[i] = axji*dw;
      dy[i] = ayji*dh;
      oldy = newy;
      newy += dy[i];
      if ((m == MDIRN)&&(i > 0))
      {
         if ((doneup == FALSE)&&(newy < oldy))
         {
            dy[i] += 1-segs[s].h/(2*barsp*STEP);
            doneup = TRUE;
         }
         else
         if ((donedn == FALSE)&&(newy > oldy))
         {
            dy[i] -= 1-segs[s].h/(2*barsp*STEP);
            donedn = TRUE;
         }
      } /* m = MDIRN */
   } /* i */
   if ((m == MMISC) && (j == 1))
      drawbow(s);
   else
	if (m != MKEYS)
      dopolygonrel(s,dx,dy,i);
   closesegment(s);
   segs[s].ok = TRUE;
}/* setsymbol */
/*******************************************/

void drawstaff(int s, int n, int x, int y, int h, char level)
/*
   draw nth staff line at given 'x,y' in segment 's'.

   called by makestaff, scrollstaff, drawsymbol,
   calls     createsegment, linerel, closesegment,
*/
{
   int j,yy;

   if (( x > xbot) && (x < xtop))
   {
      staffx[n] = x;
      if (staffn > VMAX)
      {
         printf("can only accommodate %d staves\n",VMAX/3);
         getout(1);
      }
      segs[s].x = x;
      segs[s].y = y;
      segs[s].w = 1;
      segs[s].h = yhigh - y;
      segs[s].step = 1;
      segs[s].item = n;
      segs[s].menu = MSTAF;
      segs[s].level = level;
      segs[s].ok = TRUE;
      createsegment(s);
      lineabs(x,yhigh);
      if (level == 'L')
      {
         yy = bar0y;
         for (j = 1; yy < yhigh; ++j)
         {
            yy = bar0y - 1 + 2*j*STEP 
                  + (bar0y + 2*j*STEP)/(2*STEP*barsp+1);
            if (barsp > 3) ++yy;
            if (j > 71) ++yy;
            if (yy < yhigh)
            {
               moveabs(x-3,yy);
               linerel(6,0);
            }
         }
      }
      closesegment(s);
   }
} /* drawstaff */
/************************************************/

void drawsymbol(int s)
/*
   draw the symbol for segment s.

   called by mouseclick, dosymbol, scrollstaff, lbnread,
             pswrite, scale, dobarnumber, fixscore,
             createwaymenu, createmismenu, createkeymenu,
             createrotmenu, createaremenu, createvolmenu,
             createlimmenu, createlimmenu, createfacmenu,
             createdirmenu, fixstaff,
   calls     drawstaff, linerel, moveabs, createsegment,
	          closesegment, setsymbol,
*/
{
   int m;
   int j;

   m = segs[s].menu;
   j = segs[s].item;

   if ( (j >= 0) && (j <= NSYMS) && (m >= 0) && (m <= SCORE)
	 && (m != SCROLLUP) && (m != SCROLLDN))
   {
      if (m == MSTAF)
      {
         drawstaff(s,segs[s].item,segs[s].x,segs[s].y,
				segs[s].h,segs[s].level);
      }
      else
      if (m == MBARS)
      {
         createsegment(s);
         linerel(segs[s].w,0);
         if (segs[s].level == low)
         {
            moveabs(segs[s].x,segs[s].y-2);
            linerel(segs[s].w,0);
         }
         closesegment(s);
      }
      else
      if (m == MDIRN)
         setsymbol(s,m,dirdx,dirdy,j,segs[s].step,segs[s].level);
      else
      if (m == MFACE)
         setsymbol(s,m,facdx,facdy,j,segs[s].step,segs[s].level);
      else
      if (m == MPINS)
		{
			if (segs[s].level == 'L')
				filledpin = TRUE;
			if (j > 4) jx = 1; else jx = -1;
         setsymbol(s,m,pindx,pindy,j,segs[s].step,segs[s].level);
			filledpin = FALSE;
		}
      else
      if (m == MLIMB)
         setsymbol(s,m,limdx,limdy,j,segs[s].step,segs[s].level);
      else
      if (m == MVOLM)
         setsymbol(s,m,voldx,voldy,j,segs[s].step,segs[s].level);
      else
      if (m == MAREA)
         setsymbol(s,m,aredx,aredy,j,segs[s].step,segs[s].level);
      else
      if (m == MROTN)
         setsymbol(s,m,rotdx,rotdy,j,segs[s].step,segs[s].level);
      else
      if (m == MKEYS)
         setsymbol(s,m,keydx,keydy,j,segs[s].step,segs[s].level);
      else
      if (m == MMISC)
         setsymbol(s,m,misdx,misdy,j,segs[s].step,segs[s].level);
      else
      if (m == MWAYS)
         setsymbol(s,m,waydx,waydy,j,segs[s].step,segs[s].level);
   }
} /* drawsymbol */
/***************************************/

void fixstaff(void)
/*
   ensure staff extends to just beyond top symbol
   and find left, right, and centre lines.

   called by fixscore,
   calls     drawsymbol, sort,
*/
{
   int bar0;
   int m;
   int s;
   int y;

   bar0 = ymax;
   for (s = SCORE; s < scoretop; ++s)
   {
      m = segs[s].menu;
      y = segs[s].y;
      if ((m == MBARS) && (y < bar0))
         bar0 = y;
   }
   if ((bar0 == ymax)||(bar0 < STEP)) bar0 = STEP;

   staffn = 0;
   for (s = SCORE; s < scoretop; ++s)
   {
      if (segs[s].menu == MSTAF)
      {
         if ((segs[s].level == 'L') && (bar0 != ymax))
            segs[s].y = bar0;
         else
            segs[s].y = STEP;
         segs[s].h = yhigh - segs[s].y;
         drawsymbol(s);
         staffx[staffn++] = segs[s].x;
      }
   }
   sort(staffx,staffn);
} /* fixstaff */
/*********************************/

void makebar(int s, int j, int x, int y, int w, char l)
/*
   create a bar line

   called by setlevel, drawbars,
   calls     createsegment, moveabs, linerel, closesegment,
*/
{
   segs[s].y = y;
   segs[s].x = x;
   segs[s].w = w;
   segs[s].h = 3;
   segs[s].step = 1;
   segs[s].item = j;
   segs[s].menu = MBARS;
   segs[s].ok = TRUE;
   createsegment(s);
   segs[s].level = l;
   linerel(w,0);
   if (l == low)
   {
      moveabs(x,y-2);
      linerel(w,0);
   }
   closesegment(s);
   bary[barn++] = y;
   if (barn > NSYMS)
      printf("oops: currently limited to %d bar lines\n",
         NSYMS);
} /* makebar */
/**********************************************/

int digits(int n)
/*
   find number of digits in "n"

   called by dobarnumber,
*/
{
   int k;
   int tens;

   k = 0;
   for (tens = 1; tens <= n; tens *= 10)
   {
      ++k;
   }
   return(k);
} /* digits */
/**************************************************/

void dobarnumber(int n, int x, int y)
/*
    draw the bar number above left-hand
    end of bar line

    called by drawbars,
    calls     drawsymbol, 
*/
{
      int s;

      s = scoretop++;
      sprintf(segs[s].text,"%d",n);
      segs[s].length = int(strlen(segs[s].text));
      segs[s].x = x - segs[s].length*STEP;
      segs[s].y = y;
      //segs[s].w = STEP;
		segs[s].w = segs[s].length*CH*segs[s].step/6;
      segs[s].h = STEP;
      segs[s].level = 'B';
      segs[s].item = 1;
      segs[s].step = keystep;
      segs[s].menu = MKEYS;
      segs[s].ok = TRUE;
      drawsymbol(s);
} /* dobarnumber */
/*******************************************/

void createbars(void)
/*
   called by create, clear, setbarsp,

   calls     delseg, createsegment, closesegment,
             linerel, moverel,
*/
{
   if (barsp < 1)
   {
      printf("min bar spacing = 1\n");
      barsp = 1;
   }
   if (barsp > 99)
   {
      printf("max bar spacing = 99\n");
      barsp = 99;
   }
   delseg(BARS);
   sprintf(segs[BARS].text,"Bars %2d",barsp);
   segs[BARS].length = int(strlen(segs[BARS].text));
   segs[BARS].x = width-CW-2;
   segs[BARS].y = height-CH-BARS*CH-2;
   segs[BARS].h = CH;
   segs[BARS].w = CW;
   segs[BARS].step = 1;
   segs[BARS].menu = BARS;
   segs[BARS].item = 0;
   createsegment(BARS);
   linerel(segs[BARS].w,0);
   linerel(0,segs[BARS].h);
   linerel(-segs[BARS].w,0);
   linerel(0,-segs[BARS].h);
   closesegment(BARS);
} /* createbars */
/**********************************************/

void unbar(void)

/*
   remove bar lines and numbers

   called by drawbars,
   calls     delseg,
*/

{
   int j;
   int i,m;
	int xlimit;

	xlimit = staffx[0]/2;
   for (j = SCORE; j < scoretop; ++j)
   {
      m = segs[j].menu;
      if (m == MBARS)
      {
         delseg(j);
      }
      else
      if ( (m == MKEYS) && ( (segs[j].x < xlimit) || (segs[j].level == 'B')) )
      {
	i = segs[j].item;
	if( ((i>5) && (i<8)) || (i>13) && (i!=17) ) //numbers, C, _ symbols wont disappear
	  delseg(j);
      }
   }
   barn = 0;
}


 /* unbar */
/***************************************************/

void setbarsp(void)
/*
    find spacing between bar lines using first two

	 called by lbnread,
	 calls creatbars, create,
*/
{
	int s;

	bar1y = 0;
	bar2y = 0;
	for (s = SCORE; s < scoretop; ++s)
   {
	   if (segs[s].menu == MBARS)
      {
         if (segs[s].item == 0) bar0y = segs[s].y;
			if (segs[s].item == 1) bar1y = segs[s].y;
         if (segs[s].item == 2) bar2y = segs[s].y;
      }
	}
	bardif = bar2y - bar1y;
   if (bardif > 0)
   {
      barsp = (bardif)/(2*STEP);
      createbars();
   }
} /* setbarsp */
/****************************************************/
	  
void drawbars(void)
/*
   draw bar lines

   called by checkeys, docommand, lbnread,
   calls     unbar, highesty, makebar, dobarnumber,

*/
{
   int bleft;
   int bot;
   int bntop;
   int bytop;
   int j;
   int p;
   int q;
   int r;
   int left;
   int right;
   int s;
   int top;


   bot = 4*STEP;
   top = (height - bot - STEP + 1)/(2*barsp*STEP + 1);
   left = 2*CH;
   right = 0;
   r = 0;
   bytop = -1;
   bntop = -1;
   bleft = xbot;
   unbar();
// find right end of bar lines -
   for (j = SCORE; j < scoretop; ++j)
   {
      r = segs[j].x + segs[j].w;
      if (segs[j].menu == MSTAF) r += 3*STEP;
      if (r > right)  right = r;
   }
   if ((right <= left) || (right >= xtop))
      right = xtop - 1;
	// make initial bar lines -
   if (bytop < 0)
   {
      s = scoretop++;
      makebar(s,0,left,bot,right-left,blank);
      s = scoretop++;
      makebar(s,1,left,2*bot,right-left,low);
      bar0y = 2*bot;
      bntop = 1;
      bytop = segs[s].y;
      dobarnumber(1,left,bytop+2);
      bytop += 2*barsp*STEP + 1;
   }
   p = digits(bntop);
   left += (p-1)*STEP;
   for (j = 2; bytop < (yhigh + barsp*STEP + 1); j++ )
   {
      q = digits(j);
      s = scoretop++;
      makebar(s, j, left, bytop, right-left, blank);
      dobarnumber(j,left+(q-1)*STEP,bytop+1);
      bytop += 2*barsp*STEP + 1;
   }
   /* lift centre staff line - */
   for (j = SCORE; j < scoretop; ++j)
   {
      if ((segs[j].menu == MSTAF)
         && (segs[j].level == low))
      {
         segs[j].y = bary[0];
         segs[j].h -= bary[0];
      }
   }
} /* drawbars */
/**********************************************/

void fixscore(void)
/*
   eliminate redundant symbols,

   called by lbnwrite, lbnread, docommand,
   calls     fixstaff, delseg,  drawsymbol, copyseg,
*/
{
   int s;
   int n;
   int top;

	n = SCORE;
   fixstaff();
   top = scoretop;
   // are any symbols weird or duplicated?
   for (s = SCORE; s < scoretop; ++s)
   {
      if (segs[s].ok == TRUE)
      {
         if ((segs[s].x > xtop)||(segs[s].x < xbot)
            ||(segs[s].w < 1)||(segs[s].w > (xtop-xbot))
            ||(segs[s].h < 1)||(segs[s].y < 1))
			{
               segs[n].ok = FALSE;
			}
         else
         {
            for (n = (s+1); n < scoretop; ++n)
            {
               if (  (segs[s].x == segs[n].x)
                  && (segs[s].menu == segs[n].menu)
                  && (segs[s].item == segs[n].item)
                  && (segs[s].w == segs[n].w)
                  && (segs[s].y == segs[n].y)
                  && (segs[s].h == segs[n].h) )
               {
                  segs[n].ok = FALSE;
               }
               if (  (segs[s].menu != MBARS)
                  && (segs[s].menu != MSTAF)
						&& (segs[s].menu != MKEYS)
                  && (segs[s].item < 1)  )
               {
                  segs[n].ok = FALSE;
               }
            } /* n */
         } /* segs[s] NBG */
      } /* segs[n].ok == TRUE */
   } /* s*/
   n = SCORE;
   for (s = SCORE; s < scoretop; ++s)
   {
      if (segs[s].ok == FALSE)
		{
         delseg(s);
		}
      else
      {
         if (n != s)
         {
            copyseg(n,s);
            delseg(s);
         } /* if */
         drawsymbol(n);
         ++n;
      } /* if */
   } /* s */
   scoretop = n;
   highesty();
} /* fixscore */
/************************************************/

void lbnwrite(void)
/*
   store the score in a "outfile".

   called by checkeys, docommand, getout, saveas,
   calls     fixscore, lbnsort, highesty, 
*/
{
   int count;
   int j;
   int s;
   int nbar;

   count = 0;
   nbar = 0;
   fixscore();
   lbnsort();
   for (s = 0; s < ncomments; ++s)
      fprintf(OUTFILE,"%s",comments[s]);
   for (s = SCORE; s < scoretop; ++s)
   {
      j = segs[s].menu/NSYMS;
      if ((segs[s].ok == TRUE)
         &&(((segs[s].y+segs[s].h) <= yhigh)
         ||(segs[s].menu == MSTAF)))
      {
            ++count;
            fprintf(OUTFILE,
               "%c%c%c%c %3d %3d %4d %3d %3d %4d %c %s # %d",
               menutext[j][0],menutext[j][1],
               menutext[j][2],menutext[j][3],
               segs[s].item,segs[s].x,segs[s].y,
               segs[s].step,segs[s].w,segs[s].h,segs[s].level,
               segs[s].text,count);
            if (segs[s].menu == MBARS)
               fprintf(OUTFILE," # bar %d\n",nbar++);
            else
               fprintf(OUTFILE,"\n");
       } /* seg OK */
    } /* s */
    if (count == 1)
	    printf("lbnwrite: %d item written to file %s\n",
               count,foutname);
    else
	    printf("lbnwrite: %d items written to file %s\n",
               count,foutname);
   if (OUTFILE) fclose(OUTFILE);
} /* lbnwrite */
/************************************************/

void saveas(void)
/*
   set up output .lbn file

   called by docommand,
*/
{
	int  c;
	char key;

start:
	sprintf(foutname,"%s.lbn",rootname);
	printf("\nCurrent output file name is %s\n",foutname);
	printf("Please hit 'Enter' to use this name\n");
    printf("else type root name of .lbn output file,\n");
	c = 0;
another:
	key = getchar(); 
	if (key == '\n') goto gotit;
	if (c == 0)
	{
		for (  c = 0 ; c < BMAX ; ++c )
           rootname[c] = NULL;
		c = 0;
	}
	rootname[c++] = key; 
	goto another;
gotit:
	sprintf(foutname,"%s.lbn",rootname);
	if ((OUTFILE = fopen(foutname,"w")) == NULL)
	{
           if (OUTFILE) fclose(OUTFILE);
           printf("\n\n oops: cannot open file %s for writing?\n",
			   foutname);
		   for (  c = 0 ; c < BMAX ; ++c )
              rootname[c] = NULL;
           goto start;
	}
	printf("\nopened output file %s OK for writing\n",foutname);
	openout = TRUE;
	lbnwrite();
} /* saveas */
/***************************************/

void createlow(void)
/*
   called by create,

   calls     createsegment, closesegment,
             dopolygonrel,
*/
{
   segs[LOW].x = width-CW-2;
   segs[LOW].y = height-CH-LOW*(CH+1)-2;
   segs[LOW].h = CH;
   segs[LOW].w = CW;
   segs[LOW].menu = LOW;
   segs[LOW].item = 0;
   segs[LOW].step = 1;
   segs[LOW].level = low;
   sprintf(segs[LOW].text,"");
   segs[LOW].length = 0;
   createsegment(LOW);
   dopolygonrel(LOW,cmdmenudx,cmdmenudy,5);
   closesegment(LOW);
} /* createlow */
/**********************************************/

void createmiddle(void)
/*
   called by create,

   calls     createsegment, closesegment,
             dopolygonrel, moveabs, moverel,
*/
{
   segs[MIDDLE].x = width-CW-2;
   segs[MIDDLE].y = height-CH-MIDDLE*(CH+1)-2;
   segs[MIDDLE].h = CH;
   segs[MIDDLE].w = CW;
   segs[MIDDLE].step = 1;
   segs[MIDDLE].menu = MIDDLE;
   segs[MIDDLE].item = 0;
   segs[MIDDLE].level = middle;
   sprintf(segs[MIDDLE].text,"");
   segs[MIDDLE].length = 0;
   createsegment(MIDDLE);
   dopolygonrel(MIDDLE,cmdmenudx,cmdmenudy,5);
   closesegment(MIDDLE);
} /* createmiddle */
/**********************************************/

void createhigh(void)
/*
   called by create,

   calls     createsegment, closesegment,
             dopolygonrel,
*/
{
   segs[HIGH].x = width-CW-2;
   segs[HIGH].y = height-CH-HIGH*(CH+1)-2;
   segs[HIGH].h = CH;
   segs[HIGH].w = CW;
   segs[HIGH].step = 0;
   segs[HIGH].menu = HIGH;
   segs[HIGH].item = 0;
   segs[HIGH].level = high;
   sprintf(segs[HIGH].text,"");
   segs[HIGH].length = 0;
   createsegment(HIGH);
   dopolygonrel(HIGH,cmdmenudx,cmdmenudy,5);
   closesegment(HIGH);
} /* createhigh */
/**********************************************/

void createblank(void)
/*
   called by create,
   calls     createsegment, closesegment,
             dopolygonrel,
*/
{
   sprintf(segs[BLANK].text,"Blank ");
   segs[BLANK].length = int(strlen(segs[BLANK].text));
   segs[BLANK].x = width-CW-2;
   segs[BLANK].y = height-CH-BLANK*(CH+1)-2;
   segs[BLANK].h = CH;
   segs[BLANK].w = CW;
   segs[BLANK].step = 1;
   segs[BLANK].menu = BLANK;
   segs[BLANK].item = 0;
   createsegment(BLANK);
   dopolygonrel(BLANK,cmdmenudx,cmdmenudy,5);
   closesegment(BLANK);
} /* createblank */
/**********************************************/

void createhelp(void)
/*
   called by create,
   calls     createsegment, closesegment,
             dopolygonrel,
*/
{
   sprintf(segs[HELP].text,"Help ");
   segs[HELP].length = int(strlen(segs[HELP].text));
   segs[HELP].x = width-CW-2;
   segs[HELP].y = height-CH-HELP*(CH+1)-2;
   segs[HELP].h = CH;
   segs[HELP].w = CW;
   segs[HELP].step = 1;
   segs[HELP].menu = HELP;
   segs[HELP].item = 0;
   createsegment(HELP);
   dopolygonrel(HELP,cmdmenudx,cmdmenudy,5);
   closesegment(HELP);
} /* createhelp */
/**********************************************/

void createstaff(void)
/*
   called by create,
   calls     createsegment, closesegment,
             linerel, 
*/
{
   sprintf(segs[STAFF].text,"Staff ");
   segs[STAFF].length = int(strlen(segs[STAFF].text));
   segs[STAFF].x = width-CW-2;
   segs[STAFF].y = height-CH-STAFF*CH-2;
   segs[STAFF].h = CH;
   segs[STAFF].w = CW;
   segs[STAFF].step = 1;
   segs[STAFF].menu = STAFF;
   segs[STAFF].item = 0;
   createsegment(STAFF);
   linerel(segs[STAFF].w,0);
   linerel(0,segs[STAFF].h);
   linerel(-segs[STAFF].w,0);
   linerel(0,-segs[STAFF].h);
   closesegment(STAFF);
} /* createstaff */
/**********************************************/

void createtext(void)
/*
   called by create,

   calls     delseg, createsegment, closesegment,
             linerel, moverel,
*/
{
   delseg(TEXTL);
   sprintf(segs[TEXTL].text,"Text");
   segs[TEXTL].length = int(strlen(segs[TEXTL].text));
   segs[TEXTL].x = width-CW-2;
   segs[TEXTL].y = height-CH-TEXTL*CH-2;
   segs[TEXTL].h = CH;
   segs[TEXTL].w = CW;
   segs[TEXTL].step = 1;
   segs[TEXTL].menu = TEXTL;
   segs[TEXTL].item = 0;
   createsegment(TEXTL);
   linerel(segs[TEXTL].w,0);
   linerel(0,segs[TEXTL].h);
   linerel(-segs[TEXTL].w,0);
   linerel(0,-segs[TEXTL].h);
   closesegment(TEXTL);
} /* createtext */
/**********************************************/

void createcomment(void)
/*
   called by create,

   calls     delseg, createsegment, closesegment,
             linerel, moverel,
*/
{
   delseg(COMMENT);
   sprintf(segs[COMMENT].text,"Comment");
   segs[COMMENT].length = int(strlen(segs[COMMENT].text));
   segs[COMMENT].x = width-CW-2;
   segs[COMMENT].y = height-CH-COMMENT*CH-2;
   segs[COMMENT].h = CH;
   segs[COMMENT].w = CW;
   segs[COMMENT].step = 1;
   segs[COMMENT].menu = COMMENT;
   segs[COMMENT].item = 0;
   createsegment(COMMENT);
   linerel(segs[COMMENT].w,0);
   linerel(0,segs[COMMENT].h);
   linerel(-segs[COMMENT].w,0);
   linerel(0,-segs[COMMENT].h);
   closesegment(COMMENT);
} /* createcomment */
/**********************************************/

void createminus(void)
/*
   called by create,

   calls     createsegment, closesegment,
             linerel, moverel,
*/
{
   sprintf(segs[MINUS].text,"Bar -");
   segs[MINUS].length = int(strlen(segs[MINUS].text));
   segs[MINUS].x = width-CW-2;
   segs[MINUS].y = height-CH-MINUS*CH-2;
   segs[MINUS].h = CH;
   segs[MINUS].w = CW;
   segs[MINUS].step = 1;
   segs[MINUS].menu = MINUS;
   segs[MINUS].item = 0;
   createsegment(MINUS);
   linerel(segs[MINUS].w,0);
   linerel(0,segs[MINUS].h);
   linerel(-segs[MINUS].w,0);
   linerel(0,-segs[MINUS].h);
   closesegment(MINUS);
} /* createminus */
/**********************************************/

void createplus(void)
/*
   called by create,

   calls     createsegment, closesegment,
             linerel, moverel,
*/
{
   sprintf(segs[PLUS].text,"Bar +");
   segs[PLUS].length = int(strlen(segs[PLUS].text));
   segs[PLUS].x = width-CW-2;
   segs[PLUS].y = height-CH-PLUS*CH-2;
   segs[PLUS].h = CH;
   segs[PLUS].w = CW;
   segs[PLUS].step = 1;
   segs[PLUS].menu = PLUS;
   segs[PLUS].item = 0;
   createsegment(PLUS);
   linerel(segs[PLUS].w,0);
   linerel(0,segs[PLUS].h);
   linerel(-segs[PLUS].w,0);
   linerel(0,-segs[PLUS].h);
   closesegment(PLUS);
} /* createplus */
/**********************************************/

void createclear(void)
/*
   called by create,

   calls     createsegment, closesegment, linerel,
*/
{
   sprintf(segs[CLEAR].text,"Clear");
   segs[CLEAR].length = int(strlen(segs[CLEAR].text));
   segs[CLEAR].x = width-CW-2;
   segs[CLEAR].y = height-CH-CLEAR*CH-2;
   segs[CLEAR].h = CH;
   segs[CLEAR].w = CW;
   segs[CLEAR].step = 1;
   segs[CLEAR].menu = CLEAR;
   segs[CLEAR].item = 0;
   createsegment(CLEAR);
   linerel(segs[CLEAR].w,0);
   linerel(0,segs[CLEAR].h);
   linerel(-segs[CLEAR].w,0);
   linerel(0,-segs[CLEAR].h);
   closesegment(CLEAR);
} /* createclear */
/**********************************************/

void createsnap(void)
/*
   called by create,

   calls     createsegment, closesegment, linerel, 
*/
{
   sprintf(segs[SNAP].text,"Snap");
   segs[SNAP].length = int(strlen(segs[SNAP].text));
   segs[SNAP].x = width-CW-2;
   segs[SNAP].y = CH+3;
   segs[SNAP].h = CH;
   segs[SNAP].w = CW;
   segs[SNAP].step = 1;
   segs[SNAP].menu = SNAP;
   segs[SNAP].item = 0;
   createsegment(SNAP);
   linerel(segs[SNAP].w,0);
   linerel(0,segs[SNAP].h);
   linerel(-segs[SNAP].w,0);
   linerel(0,-segs[SNAP].h);
   closesegment(SNAP);
} /* createsnap */
/**********************************************/

void createfree(void)
/*
   called by create,

   calls     createsegment, closesegment, linerel,
*/
{
   sprintf(segs[FREE].text,"Free");
   segs[FREE].length = int(strlen(segs[FREE].text));
   segs[FREE].x = width-CW-2;
   segs[FREE].y = 2;
   segs[FREE].h = CH;
   segs[FREE].w = CW;
   segs[FREE].step = 1;
   segs[FREE].menu = FREE;
   segs[FREE].step = 0;
   createsegment(FREE);
   linerel(segs[FREE].w,0);
   linerel(0,segs[FREE].h);
   linerel(-segs[FREE].w,0);
   linerel(0,-segs[FREE].h);
   closesegment(FREE);
} /* createfree */
/**********************************************/

void createexpand(void)
/*
   called by create,

   calls     createsegment, closesegment,
             linerel, moverel, polylinerel,
*/
{
   segs[EXPAND].x = width-CW-2;
   segs[EXPAND].y = height-CH-EXPAND*(CH+1)-2;
   segs[EXPAND].h = CH;
   segs[EXPAND].w = CW;
   segs[EXPAND].step = 1;
   segs[EXPAND].menu = EXPAND;
   segs[EXPAND].item = 0;
   sprintf(segs[EXPAND].text,"");
   segs[EXPAND].length = 0;
   createsegment(EXPAND);
   linerel(segs[EXPAND].w,0);
   linerel(0,segs[EXPAND].h);
   linerel(-segs[EXPAND].w,0);
   linerel(0,-segs[EXPAND].h);
   moverel(segs[EXPAND].w/3,0);
   polylinerel(arrowupdx,arrowupdy,7);
   closesegment(EXPAND);
} /* createexpand */
/**********************************************/

void createcontract(void)
/*
   called by create,

   calls     createsegment, closesegment,
             linerel, moverel, polylinerel.
*/
{
   segs[CONTRACT].x = width-CW-2;
   segs[CONTRACT].y = height-CH-CONTRACT*(CH+1)-2;
   segs[CONTRACT].h = CH;
   segs[CONTRACT].w = CW;
   segs[CONTRACT].step = 1;
   segs[CONTRACT].menu = CONTRACT;
   segs[CONTRACT].item = 0;
   sprintf(segs[CONTRACT].text,"");
   segs[CONTRACT].length = 0;
   createsegment(CONTRACT);
   linerel(segs[CONTRACT].w,0);
   linerel(0,segs[CONTRACT].h);
   linerel(-segs[CONTRACT].w,0);
   linerel(0,-segs[CONTRACT].h);
   moverel(segs[CONTRACT].w/3,segs[CONTRACT].h);
   polylinerel(arrowdndx,arrowdndy,7);
   closesegment(CONTRACT);
} /* createcontract */
/**********************************************/

void createcopy(void)
/*
   called by create,

   calls     createsegment, closesegment, linerel,
*/
{
   sprintf(segs[COPY].text,"Copy");
   segs[COPY].length = int(strlen(segs[COPY].text));
   segs[COPY].x = width-CW-2;
   segs[COPY].y = height-CH-COPY*(CH+1)-2;
   segs[COPY].h = CH;
   segs[COPY].w = CW;
   segs[COPY].step = 1;
   segs[COPY].menu = COPY;
   segs[COPY].item = 0;
   createsegment(COPY);
   linerel(segs[COPY].w,0);
   linerel(0,segs[COPY].h);
   linerel(-segs[COPY].w,0);
   linerel(0,-segs[COPY].h);
   closesegment(COPY);
} /* createcopy */
/**********************************************/

void createdel(void)
/*
   called by create,

   calls     createsegment, closesegment, linerel,
*/
{
   sprintf(segs[DELETEL].text,"Delete");
   segs[DELETEL].length = int(strlen(segs[DELETEL].text));
   segs[DELETEL].x = width-CW-2;
   segs[DELETEL].y = height-CH-DELETEL*(CH+1)-2;
   segs[DELETEL].h = CH;
   segs[DELETEL].w = CW;
   segs[DELETEL].step = 1;
   segs[DELETEL].menu = DELETEL;
   segs[DELETEL].item = 0;
   createsegment(DELETEL);
   linerel(segs[DELETEL].w,0);
   linerel(0,segs[DELETEL].h);
   linerel(-segs[DELETEL].w,0);
   linerel(0,-segs[DELETEL].h);
   closesegment(DELETEL);
} /* createdel */
/**********************************************/

void createmove(void)
/*
   called by create,

   calls     createsegment, closesegment, linerel,
*/
{
   sprintf(segs[MOVE].text,"Move");
   segs[MOVE].length = int(strlen(segs[MOVE].text));
   segs[MOVE].x = width-CW-2;
   segs[MOVE].y = height-CH-MOVE*(CH+1)-2;
   segs[MOVE].h = CH;
   segs[MOVE].w = CW;
   segs[MOVE].step = 1;
   segs[MOVE].menu = MOVE;
   segs[MOVE].item = 0;
   createsegment(MOVE);
   linerel(segs[MOVE].w,0);
   linerel(0,segs[MOVE].h);
   linerel(-segs[MOVE].w,0);
   linerel(0,-segs[MOVE].h);
   closesegment(MOVE);
} /* createmove */
/**********************************************/

void createpost(void)
/*
   called by create, pswrite,

   calls     createsegment, closesegment, linerel, 
*/
{
   sprintf(segs[POST].text,"Postscr");
   segs[POST].length = int(strlen(segs[POST].text));
   segs[POST].x = width-CW-2;
   segs[POST].y = height-CH-POST*CH-2;
   segs[POST].h = CH;
   segs[POST].w = CW;
   segs[POST].step = 1;
   segs[POST].menu = POST;
   segs[POST].item = 0;
   createsegment(POST);
   linerel(segs[POST].w,0);
   linerel(0,segs[POST].h);
   linerel(-segs[POST].w,0);
   linerel(0,-segs[POST].h);
   closesegment(POST);
} /* createpost */
/**********************************************/

void createopen(void)
/*
   called by create,

   calls     createsegment, closesegment, linerel,
*/
{
   sprintf(segs[OPEN].text,"Open");
   segs[OPEN].length = int(strlen(segs[OPEN].text));
   segs[OPEN].x = width-CW-2;
   segs[OPEN].y = height-CH-OPEN*CH-2;
   segs[OPEN].h = CH;
   segs[OPEN].w = CW;
   segs[OPEN].step = 1;
   segs[OPEN].menu = OPEN;
   segs[OPEN].item = 0;
   createsegment(OPEN);
   linerel(segs[OPEN].w,0);
   linerel(0,segs[OPEN].h);
   linerel(-segs[OPEN].w,0);
   linerel(0,-segs[OPEN].h);
   closesegment(OPEN);
} /*  createopen */
/**********************************************/

void createsave(void)
/*
   called by create,

   calls     createsegment, closesegment, linerel,
*/
{
   sprintf(segs[SAVE].text,"Save");
   segs[SAVE].length = int(strlen(segs[SAVE].text));
   segs[SAVE].x = width-CW-2;
   segs[SAVE].y = height-CH-SAVE*CH-2;
   segs[SAVE].h = CH;
   segs[SAVE].w = CW;
   segs[SAVE].step = 1;
   segs[SAVE].menu = OPEN;
   segs[SAVE].item = 0;
   createsegment(SAVE);
   linerel(segs[SAVE].w,0);
   linerel(0,segs[SAVE].h);
   linerel(-segs[SAVE].w,0);
   linerel(0,-segs[SAVE].h);
   closesegment(SAVE);
} /*  createsave */
/**********************************************/

void createsaveas(void)
/*
   called by create,

   calls     createsegment, closesegment, linerel,
*/
{
   sprintf(segs[SAVEAS].text,"SaveAs");
   segs[SAVEAS].length = int(strlen(segs[SAVEAS].text));
   segs[SAVEAS].x = width-CW-2;
   segs[SAVEAS].y = height-CH-SAVEAS*CH-2;
   segs[SAVEAS].h = CH;
   segs[SAVEAS].w = CW;
   segs[SAVEAS].step = 1;
   segs[SAVEAS].menu = OPEN;
   segs[SAVEAS].item = 0;
   createsegment(SAVEAS);
   linerel(segs[SAVEAS].w,0);
   linerel(0,segs[SAVEAS].h);
   linerel(-segs[SAVEAS].w,0);
   linerel(0,-segs[SAVEAS].h);
   closesegment(SAVEAS);
} /*  createsaveas */
/**********************************************/

void createdirmenu(int x, int y)
/*
   calls     createsegment, polylinerel, drawsymbol,
             closesegment,
   called by createmenus.
*/
{
   int j,s;

   dirmx = x;
   dirmy = y;
   segs[MDIRN].x = dirmx;
   segs[MDIRN].y = dirmy;
   segs[MDIRN].w = MSIZE;
   segs[MDIRN].h = 2*MSIZE;
   sprintf(segs[MDIRN].text,"");
   segs[MDIRN].length = 0;
   createsegment(MDIRN);
   polylinerel(dirmenudx,dirmenudy,5);
   closesegment(DIRN);
   for (j = 1; j <= ndir; j++)
   {
      s = j + MDIRN;
      segs[s].x = dirmx + mfac*dirx[j];
      segs[s].y = dirmy + mfac*diry[j] + 1;
      segs[s].w = STEP - 2;
      segs[s].h = 2*STEP-1;
      segs[s].item = j;
      segs[s].menu = MDIRN;
      segs[s].level = middle;
      segs[s].step = (segs[s].h+1)/6;
      segs[s].ok = TRUE;
      sprintf(segs[s].text,"");
      segs[s].length = 0;
      drawsymbol(s);
   }
   segs[MDIRN].step = segs[s].step;
} /*  createdirmenu */
/**********************************************/

void createfacmenu(int x, int y)
/*
   calls     createsegment, polylinerel, closesegment,
             drawsymbol,
   called by createmenus,
*/
{
   int   j,s;

   facmx = x;
   facmy = y;
   segs[MFACE].x = facmx;
   segs[MFACE].y = facmy;
   segs[MFACE].w = MSIZE;
   segs[MFACE].h = 2*MSIZE;
   segs[MFACE].step = facstep;
   segs[MFACE].level = blank;
   sprintf(segs[MFACE].text,"");
   segs[MFACE].length = 0;
   createsegment(MFACE);
   polylinerel(facmenudx,facmenudy,5);
   closesegment(MFACE);

   for (j = 1; j <= nfac; j++)
   {
      s = j + MFACE;
      segs[s].x = facmx + mfac*facx[j];
      segs[s].y = facmy + mfac*facy[j];
      segs[s].w = (3*STEP)/2;
      segs[s].h = (3*STEP)/2;
      segs[s].item = j;
      segs[s].menu = MFACE;
      segs[s].step = facstep;
      segs[s].level = blank;
      segs[s].ok = TRUE;
      sprintf(segs[s].text,"");
      segs[s].length = 0;
      drawsymbol(s);
   }
} /* createfacmenu */
/**********************************************/

void createpinmenu(int x, int y)
/*
   calls     createsegment, polylinerel, closesegment,
             drawsymbol,
   called by createmenus,
*/
{
   int   j,s;

   pinmx = x;
   pinmy = y;
   segs[MPINS].x = pinmx;
   segs[MPINS].y = pinmy;
   segs[MPINS].w = MSIZE;
   segs[MPINS].h = 2*MSIZE;
   segs[MPINS].step = pinstep;
   sprintf(segs[MPINS].text,"");
   segs[MPINS].length = 0;
   createsegment(MPINS);
   polylinerel(pinmenudx,pinmenudy,5);
   closesegment(MPINS);

   for (j = 1; j <= npin; j++)
   {
      s = j + MPINS;
      segs[s].x = pinmx + mfac*pinx[j];
      segs[s].y = pinmy + mfac*piny[j];
      segs[s].w = (3*STEP)/2;
      segs[s].h = (3*STEP)/2;
      segs[s].item = j;
      segs[s].menu = MPINS;
      segs[s].step = pinstep;
      segs[s].level = low;
      segs[s].ok = TRUE;
      sprintf(segs[s].text,"");
      segs[s].length = 0;
      drawsymbol(s);
   }
} /* createpinmenu */
/**********************************************/

void createlimmenu(int x, int y)
/*
   calls     createsegment, polylinerel, drawsymbol,
             closesegment,
   called by createmenus,
*/
{
   int   j,s;

   limmx = x;
   limmy = y;
   segs[MLIMB].x = limmx;
   segs[MLIMB].y = limmy;
   segs[MLIMB].step = limstep;
   segs[MLIMB].w = MSIZE;
   segs[MLIMB].h = 2*MSIZE;
   sprintf(segs[MLIMB].text,"");
   segs[MLIMB].length = 0;
   createsegment(MLIMB);
   polylinerel(limmenudx,limmenudy,5);
   closesegment(MLIMB);

   for (j = 1; j <= nlim; j++)
   {
      s = j + MLIMB;
      segs[s].x = limmx + mfac*limx[j];
      segs[s].y = limmy + mfac*limy[j];
      segs[s].w = STEP;
      segs[s].h = 2*STEP;
      segs[s].level = blank;
      segs[s].step = limstep;
      segs[s].item = j;
      segs[s].menu = MLIMB;
      segs[s].ok = TRUE;
      sprintf(segs[s].text,"");
      segs[s].length = 0;
      drawsymbol(s);
   }
} /* createlimmenu */
/**********************************************/

void createvolmenu(int x, int y)
/*
   calls     createsegment, polylinerel, drawsymbol,
             closesegment,
   called by createmenus,
*/
{
   int   j,s;

   volmx = x;
   volmy = y;
   segs[MVOLM].x = volmx;
   segs[MVOLM].y = volmy;
   segs[MVOLM].w = MSIZE;
   segs[MVOLM].h = MSIZE;
   segs[MVOLM].step = volstep;
   sprintf(segs[MVOLM].text,"");
   segs[MVOLM].length = 0;
   createsegment(MVOLM);
   polylinerel(volmenudx,volmenudy,5);
   closesegment(MVOLM);

   for (j = 1; j <= nvol; j++)
   {
      s = j + MVOLM;
      segs[s].x = volmx + mfac*volx[j];
      segs[s].y = volmy + mfac*voly[j];
      segs[s].w = STEP;
      segs[s].h = STEP;
      segs[s].level = blank;
      segs[s].item = j;
      segs[s].step = volstep;
      segs[s].menu = MVOLM;
      segs[s].ok = TRUE;
      sprintf(segs[s].text,"");
      segs[s].length = 0;
      drawsymbol(s);
   }
} /* createvolmenu */
/**********************************************/

void createaremenu(int x, int y)
/*
   calls     createsegment, polylinerel, drawsymbol,
             closesegment,
   called by createmenus,
*/
{
   int   j,s;

   aremx = x;
   aremy = y;
   segs[MAREA].x = aremx;
   segs[MAREA].y = aremy;
   segs[MAREA].w = MSIZE;
   segs[MAREA].h = MSIZE;
   sprintf(segs[MAREA].text,"");
   segs[MAREA].length = 0;
   segs[MAREA].step = arestep;
   createsegment(MAREA);
   polylinerel(aremenudx,aremenudy,5);
   closesegment(MAREA);

   for (j = 1; j <= narea; j++)
   {
      s = j + MAREA;
      segs[s].x = aremx + mfac*arex[j];
      segs[s].y = aremy + mfac*arey[j];
      segs[s].w = arestep+STEP;
      segs[s].h = arestep+STEP;
      segs[s].level = blank;
      segs[s].item = j;
      segs[s].step = arestep;
      segs[s].menu = MAREA;
      segs[s].ok = TRUE;
      sprintf(segs[s].text,"");
      segs[s].length = 0;
      drawsymbol(s);
   }
} /* createaremenu */
/**********************************************/

void createrotmenu(int x, int y)
/*
   calls     createsegment, polylinerel, drawsymbol,
             closesegment,
   called by createmenus,
*/
{
   int   j,s;

   rotmx = x;
   rotmy = y;
   segs[MROTN].x = rotmx;
   segs[MROTN].y = rotmy;
   segs[MROTN].w = MSIZE;
   segs[MROTN].h = MSIZE;
   segs[MROTN].menu = MROTN;
   segs[MROTN].item = 0;
   segs[MROTN].level = middle;
   sprintf(segs[MROTN].text,"");
   segs[MROTN].length = 0;
   createsegment(MROTN);
   polylinerel(rotmenudx,rotmenudy,5);
   closesegment(MROTN);

   for (j = 1; j <= nrot; j++)
   {
      s = j + MROTN;
      segs[s].x = rotmx + mfac*rotx[j];
      segs[s].y = rotmy + mfac*roty[j];
      segs[s].w = STEP-2;
      segs[s].item = j;
      segs[s].menu = MROTN;
      segs[s].step = 4;
      segs[s].h = 6*segs[s].step - 2;
      segs[s].level = middle;
      segs[s].ok = TRUE;
      sprintf(segs[s].text,"");
      segs[s].length = 0;
      drawsymbol(s);
   }
   segs[MROTN].step = segs[s].step;
} /* createrotmenu */
/**********************************************/

void createkeymenu(int x, int y)
/*
   calls     createsegment, polylinerel, drawsymbol,
             closesegment,
   called by createmenus,
*/
{
   int   j,s;

   keymx = x;
   keymy = y;
   segs[MKEYS].x = keymx;
   segs[MKEYS].y = keymy;
   segs[MKEYS].w = MSIZE;
   segs[MKEYS].h = MSIZE;
   segs[MKEYS].menu = MKEYS;
   segs[MKEYS].item = 0;
   segs[MKEYS].step = keystep;
   sprintf(segs[MKEYS].text,"");
   segs[MKEYS].length = 0;
   createsegment(MKEYS);
   polylinerel(keymenudx,keymenudy,5);
   closesegment(MKEYS);

   for (j = 1; j <= nkey; j++)
   {
      s = j + MKEYS;
      segs[s].x = keymx + mfac*keyx[j];
      segs[s].y = keymy + mfac*keyy[j];
      segs[s].w = STEP;
      segs[s].h = STEP;
      segs[s].level = blank;
      segs[s].item = j;
      segs[s].step = keystep;
      segs[s].menu = MKEYS;
      segs[s].ok = TRUE;
      segs[s].text[0] = oldkeys[j];
      segs[s].length = 1;
      drawsymbol(s);
   }
} /* createkeymenu */
/**********************************************/

void createmismenu(int x, int y)
/*
   calls     createsegment, polylinerel, drawsymbol,
             closesegment,
   called by createmenus,
*/
{
   int   j,s;

   mismx = x;
   mismy = y;
   segs[MMISC].x = mismx;
   segs[MMISC].y = mismy;
   segs[MMISC].w = MSIZE;
   segs[MMISC].h = MSIZE;
   segs[MMISC].menu = MMISC;
   segs[MMISC].item = 0;
   segs[MMISC].step = misstep;
   sprintf(segs[MMISC].text,"");
   segs[MMISC].length = 0;
   createsegment(MMISC);
   polylinerel(mismenudx,mismenudy,5);
   closesegment(MMISC);

   for (j = 1; j <= nmisc; j++)
   {
      s = j + MMISC;
      segs[s].x = mismx + mfac*misx[j];
      segs[s].y = mismy + mfac*misy[j];
      if (j == 1)
      {
         segs[s].w = 4*STEP;
         segs[s].h = segs[s].w/6;
      }
      else
      {
         segs[s].w = STEP;
         segs[s].h = STEP;
      }
      segs[s].level = blank;
      segs[s].item = j;
      if ((j == 2) || (j == 3))
         segs[s].step = misstep/2;
      else
         segs[s].step = misstep;
      segs[s].menu = MMISC;
      segs[s].ok = TRUE;
      drawsymbol(s);
   }
} /* createmismenu */
/**********************************************/

void createwaymenu(int x, int y)
/*
   calls     createsegment, polylinerel, drawsymbol,
             closesegment,
   called by createmenus,
*/
{
   int   j,s;

   waymx = x;
   waymy = y;
   segs[MWAYS].x = waymx;
   segs[MWAYS].y = waymy;
   segs[MWAYS].w = MSIZE;
   segs[MWAYS].h = MSIZE;
   segs[MWAYS].menu = MWAYS;
   segs[MWAYS].item = 0;
   segs[MWAYS].step = waystep;
   sprintf(segs[MWAYS].text,"");
   segs[MWAYS].length = 0;
   createsegment(MWAYS);
   polylinerel(waymenudx,waymenudy,5);
   closesegment(MWAYS);

   for (j = 1; j <= nway; j++)
   {
      s = j + MWAYS;
      segs[s].x = waymx + mfac*wayx[j];
      segs[s].y = waymy + mfac*wayy[j];
      segs[s].h = 2*STEP;
      segs[s].w = STEP;
      segs[s].level = blank;
      segs[s].item = j;
      if ((j == 6)||(j == 7))
      {
         segs[s].h = 4*STEP;
         segs[s].step = waystep/2;
      }
      else
         segs[s].step = waystep;
      segs[s].menu = MWAYS;
      segs[s].ok = TRUE;
      drawsymbol(s);
   }
} /* createwaymenu */
/**********************************************/

void createscroll(void)
/*
   create scroll bar

   calls     createsegment, moveabs, linerel, moverel,
             closesegment,
   called by createmenus,
*/
{
   segs[SCROLLUP].x = 1;
   segs[SCROLLUP].y = height-CW;
   segs[SCROLLUP].h = CW;
   segs[SCROLLUP].w = CH;
   segs[SCROLLUP].step = 1;
   segs[SCROLLUP].menu = SCROLLUP;
   segs[SCROLLUP].item = 0;
   segs[SCROLLUP].level = 'B';
   sprintf(segs[SCROLLUP].text,"");
   segs[SCROLLUP].length = 0;
   createsegment(SCROLLUP);
   moveabs(segs[SCROLLUP].x,segs[SCROLLUP].y);
   linerel(segs[SCROLLUP].w,0);
   linerel(0,segs[SCROLLUP].h);
   linerel(-segs[SCROLLUP].w,0);
   linerel(0,-segs[SCROLLUP].h);
   moverel(1,CW/2);
   linerel(CH/2-1,CW/2);
   linerel(CH/2-1,-CW/2);
   moverel(1-CH/2,CW/2);
   linerel(0,2-CW);
   closesegment(SCROLLUP);

   segs[SCROLLDN].x = 1;
   segs[SCROLLDN].y = 1;
   segs[SCROLLDN].h = CW;
   segs[SCROLLDN].w = CH;
   segs[SCROLLDN].step = 1;
   segs[SCROLLDN].menu = SCROLLDN;
   segs[SCROLLDN].item = 0;
   sprintf(segs[SCROLLDN].text,"");
   segs[SCROLLDN].length = 0;
   createsegment(SCROLLDN);
   moveabs(segs[SCROLLDN].x,segs[SCROLLDN].y);
   linerel(segs[SCROLLDN].w,0);
   linerel(0,segs[SCROLLDN].h);
   linerel(-segs[SCROLLDN].w,0);
   linerel(0,-segs[SCROLLDN].h);
   moverel(1,CW/2);
   linerel(CH/2-1,-CW/2);
   linerel(CH/2-1,CW/2);
   moverel(1-CH/2,-CW/2);
   linerel(0,CW-2);
   closesegment(SCROLLDN);

   segs[SCROLLBX].x = 1;
   segs[SCROLLBX].y = 1;
   segs[SCROLLBX].h = height-2;
   segs[SCROLLBX].w = CH;
   segs[SCROLLBX].step = 1;
   segs[SCROLLBX].menu = SCROLLBX;
   segs[SCROLLBX].item = 0;
   createsegment(SCROLLBX);
   moveabs(segs[SCROLLBX].x,segs[SCROLLBX].y);
   linerel(segs[SCROLLBX].w,0);
   linerel(0,segs[SCROLLBX].h);
   linerel(-segs[SCROLLBX].w,0);
   linerel(0,-segs[SCROLLBX].h);
   closesegment(SCROLLBX);

} /* createscroll */
/**********************************************/

void create(int s)
/*
   called by createmenus, docommand, mouseclick,
   calls     createblank, createstaff, createlow, createmiddle,
             createhigh, createbars, createplus, createminus,
             createclear, createsnap, createfree, createexpand,
             createcontract, createcopy, createdel, createmove,
             createpost, createopen, createhelp, createsaveas,
             createtext, createcomment,
*/
{
   int y1,y2;

   y1 = ybot;
   y2 = ytop;
   ybot = 0;
   ytop = height;
	if (s == CLEAR) createclear();
   else if (s == OPEN) createopen();
   else if (s == SAVE) createsave();
   else if (s == SAVEAS) createsaveas();
   else if (s == POST) createpost();
   else if (s == STAFF) createstaff();
   else if (s == PLUS) createplus();
   else if (s == MINUS) createminus();
   else if (s == BARS) createbars();
   else if (s == TEXTL) createtext();
   else if (s == COMMENT) createcomment();
   else if (s == EXPAND) createexpand();
   else if (s == CONTRACT) createcontract();
   else if (s == COPY) createcopy();
   else if (s == DELETEL) createdel();
   else if (s == MOVE) createmove();
   else if (s == LOW) createlow();
   else if (s == MIDDLE) createmiddle();
   else if (s == HIGH) createhigh();
   else if (s == BLANK) createblank();
   else if (s == HELP) createhelp();
   else if (s == SNAP) createsnap();
   else if (s == FREE) createfree();
   ybot = y1;
   ytop = y2;
} /*  create */
/**********************************************/

void createmenus(void)
/*
   calls create, createscroll, createkeymenu, createpinmenu,
         createfacmenu, createvolmenu, createlimmenu,
         createrotmenu, createmismenu, createwaymenu,
         createaremenu, createdirmenu,

   called by main,
*/
{
   int s;
   int x1,x2;

   for (s = 0; s < COMMANDS; ++s)
      create(s);

   createscroll();

   x1 = xtop + MSIZE + 5;
   x2 = xtop;
   createkeymenu(x1,2);
   createpinmenu(x1,keymy+MSIZE+2);
   createfacmenu(x1,pinmy+MSIZE+2);
   createvolmenu(x1,facmy+MSIZE+2);
   createlimmenu(x1,volmy+MSIZE+2);
   createrotmenu(x2,2);
   createmismenu(x2,rotmy+MSIZE+2);
   createwaymenu(x2,mismy+MSIZE+2);
   createaremenu(x2,waymy+MSIZE+2);
   createdirmenu(x2,aremy+MSIZE+2);
} /* createmenus */
/******************************************/

void setxy(int s)
/*
   set x and y values of segment 's'.

   called by mouseclick,
   calls     sort,
*/
{
   int j;
   int best;
   int diffmin;
   int diffj;
   int difu,difd;
   int m;
   int thej;
   int topj,topbest;
   int top,bot;

   thej = -1;
   m = segs[s].menu;
   if (snap == TRUE)
   {
      if (m == MFACE)
      {
         if (segs[s].x < 100)
            segs[s].x = 50;
         if ((segs[s].x > 300)&&(segs[s].x < 500))
            segs[s].x = 400;
      }
      else
      if ((m == MROTN)||(m == MDIRN))
      {
         if (barn > 1)
         {
            bot = segs[s].y;
            top = bot + segs[s].h;
            topj = TRUE;
            topbest = FALSE;
            best = bot;
            diffmin = ytop;
            for (j = 0; j < barn; ++j)
            {
               difd = bot - bary[j];
               if (difd < 0) 
                  difd = -difd;
               difu = bary[j] - top;
               if (difu < 0) 
                  difu = -difu;
               if (difu < difd)
               {
                  topj = TRUE;
                  diffj = difu;
               }
               else
               {
                  topj = FALSE;
                  diffj = difd;
               }
               if (diffj < diffmin)
               {
                  best = bary[j];
                  topbest = topj;
                  diffmin = diffj;
                  thej = j;
               }
            } /* j */
            if (diffmin < segs[s].h)
            {
               if (topbest == FALSE)
               {
                  segs[s].y = best + 1;
               }
               else
               {
                  segs[s].y = best - segs[s].h - 1;
                  if (thej == 1)
                     segs[s].y -=2;
                  if ((segs[s].menu == MDIRN)&&
                     ((segs[s].item == 3)||(segs[s].item == 8)
                     ||(segs[s].item == 2)||(segs[s].item == 9)))
                        ++segs[s].y;
               } /* topbest != FALSE */
            } /* diffmin < segs[s].h*/
         } /* barn > 1*/

         if (staffn > 1)
         {
            bot = segs[s].x;
            top = bot + segs[s].w;
            sort(staffx,staffn);
            topj = TRUE;
            topbest = FALSE;
            best = bot;
            diffmin = xtop;
            for (j = 0; j < staffn; ++j)
            {
               difd = bot - staffx[j];
               if (difd < 0) 
                  difd = -difd;
               difu = staffx[j] - top;
               if (difu < 0) 
                  difu = -difu;
               if (difu < difd)
               {
                  topj = TRUE;
                  diffj = difu;
               }
               else
               {
                  topj = FALSE;
                  diffj = difd;
               }
               if (diffj < diffmin)
               {
                  best = staffx[j];
                  topbest = topj;
                  diffmin = diffj;
               }
            } /* j */
            if (diffmin < segs[s].w)
            {
               if (topbest == FALSE)
                  segs[s].x = best + 1;
               else
                  segs[s].x = best - segs[s].w - 1;
            }
         } /* staffn > 1 */
      } /* MROTN or MDIRN */
   } /* snap = TRUE */
} /* setxy */
/***************************************/

void scale(int n)
/*
   make symbol 'n' larger or smaller, e.g. 
   by adding/subtracting STEP to/from the height/width,
   or scaling it by 1/2 or 2.

   called by dosymbol,
   calls     delseg, drawsymbol, copyseg,
	MPINS MFACE	MLIMB MVOLM	MKEYS MMISC 
*/
{
   int j;
   int m;
   int s;
   int midn;
   int mids;

   s = scoretop++;
   m = segs[n].menu;
   j = segs[n].item;
	copyseg(s,n);
   if ((m == MAREA) || (m == MWAYS) || (m == MDIRN) 
	   || (m == MROTN))
   {
      if (mode == EXPAND)
      {     
         if (segs[s].step < 2)
         {
            segs[s].h = 5;
            segs[s].step = 1;
         }
         if (segs[s].h >= STEP)
            segs[s].h = segs[n].h + STEP;
         else
            segs[s].h = 2*segs[n].h + 1;
      }
      else // contract
      {
         if (segs[n].h >= 2*(STEP-1))
            segs[s].h = segs[n].h - STEP;
         else
            segs[s].h = (segs[n].h+2)/2 - 2;
      }
      segs[s].step = inv2 +
      float(segs[n].step)*float(segs[s].h)/float(segs[n].h);
      if (segs[s].step < 2)
      {
         segs[s].h = 5;
         segs[s].step = 1;
      }
      else
      if (segs[s].step < 4)
      {
         segs[s].h = 11;
         segs[s].step = 2;
      }
      else
      if (segs[s].step == 4)
         segs[s].h = 23;
   } //MAREA MWAYS MDIRN MROTN
   else
   if (m == MBARS)
   {
      if (mode == EXPAND)
      {
         segs[s].step = segs[n].step + segs[m].step;
         if ((segs[n].x+segs[n].w) < (xtop - STEP) )
            segs[s].w = segs[n].w + STEP;
         else
            printf(
               "led: cannot expand symbol %d any more\n",n);
      }
      else //contract
      {
         if (segs[n].w > STEP)
            segs[s].w = segs[n].w - STEP;
         else
            printf(
               "led: cannot contract symbol %d any more\n",n);
         if (segs[n].step > segs[m].step)
            segs[s].step = segs[n].step - segs[m].step;
         else
            segs[s].step = float(segs[n].step)*fac;
      }
   } //MBARS
   else
   if (m == MSTAF)
   {
      if (mode == EXPAND)
      {
			segs[s].step = segs[n].step + segs[m].step;
         if (segs[n].y > STEP)
         {
            segs[s].y = segs[n].y - STEP;
            segs[s].h = segs[n].h + STEP;
         }
         else
            printf(
               "led: cannot expand STAFF symbol %d  any more\n",n);
      }
      else // contract
      {
         if (segs[n].step > segs[m].step)
            segs[s].step = segs[n].step - segs[m].step;
         else
            segs[s].step = float(segs[n].step)*fac;
         if (segs[n].h > STEP)
         {
            segs[s].y = bary[0];//segs[n].y + STEP;
            segs[s].h = segs[n].h - STEP;
         }
         else
            printf(
               "led: cannot contract STAFF symbol %d any more\n",n);
      }
   } // MSTAF
   else if (m == MMISC)
   {
      if (mode == EXPAND)
      {
         if (j == 1)
         {
            segs[s].w = segs[n].w + STEP;
            segs[s].y = segs[n].y - 2;
            segs[s].step = segs[n].step + 1;
         }
         else // j != 1
         {
            segs[s].h = float(segs[n].h)*fac;
            segs[s].w = float(segs[n].w)*fac;
            segs[s].step = segs[n].step + segs[m].step;
         }
      }
      else // contract
      {
         if (j == 1)
         {
            segs[s].w = segs[n].w - STEP;
            segs[s].y = segs[n].y + 3;
            segs[s].step = segs[n].step - 1;
         }
         else // j != 1
         {
            if (segs[n].h >= 2*STEP)
               segs[s].h = float(segs[n].h)/fac;
            if (segs[n].w >= 2*STEP)
               segs[s].w = float(segs[n].w)/fac;
            if (segs[n].step > segs[m].step)
               segs[s].step = segs[n].step - segs[m].step;
            else
               segs[s].step = float(segs[n].step)*fac;
            if (segs[s].step == segs[n].step) --segs[s].step;
         }
      }
      segs[s].h = segs[n].w/6;
      if (segs[s].h < 3) segs[s].h = 3;
   }
   else if (m == MKEYS)
   {
      if (mode == EXPAND)
      {
         ++segs[s].step;
      }
      else // contract
      {
         --segs[s].step;
      }
		segs[s].w = segs[s].length*CH*segs[s].step/6;
   }
   else  // MPINS MFACE MLIMB MVOLM
   {
      if (mode == EXPAND)
      {
         segs[s].h = float(segs[n].h)*fac;
         segs[s].w = float(segs[n].w)*fac;
         segs[s].step = segs[n].step + segs[m].step;
      }
      else // contract
      {
         if (segs[n].h >= 2*STEP)
            segs[s].h = float(segs[n].h)/fac;
         if (segs[n].w >= 2*STEP)
            segs[s].w = float(segs[n].w)/fac;
         if (segs[n].step > segs[m].step)
            segs[s].step = segs[n].step - segs[m].step;
         else
            segs[s].step = float(segs[n].step)*fac;
         if (segs[s].step == segs[n].step) --segs[s].step;
      }
      mids = segs[s].x + segs[s].w/2;
      midn = segs[n].x + segs[n].w/2;
      segs[s].x = segs[n].x - (mids-midn);
      mids = segs[s].y + segs[s].h/2;
      midn = segs[n].y + segs[n].h/2;
      segs[s].y = segs[n].y - (mids-midn);
   }
   if (segs[s].w < (STEP-2)) segs[s].w = STEP-2;
   if (segs[s].step < 1) segs[s].step = 1;
   delseg(n);
   segs[s].ok = TRUE;
   drawsymbol(s);
} /* scale */
/************************************************/

void pswrite(void)
/*
   write out the score in postscript format in
   the file "led.ps".

   called by checkeys, docommand,
   calls     setpsfile, drawsymbol,
*/
{
   int j,s;
	int yb,yt;

   setpsfile();
   openpost = TRUE;
	yb = ybot;
	yt = ytop;
	ybot = 0;
	ytop = ymax;
   fprintf(POSTFILE,
      "%%!PS  postscript of labanotation score\n");
	fprintf(POSTFILE,"%% from %s.cpp\n",ptitle);
   fprintf(POSTFILE,"newpath\n");
	fprintf(POSTFILE,"/Times-Roman findfont 12 scalefont setfont\n");
   fprintf(POSTFILE,"0.33 0.33 scale\n");
	pfont = 3;
   for (s = SCORE; s < scoretop; ++s)
   {
      if (segs[s].ok == TRUE)
      {
			j = segs[s].menu/NSYMS;
			fprintf(POSTFILE,
               "%% %c%c%c%c %3d %3d %4d %3d %3d %4d %c %s\n",
               menutext[j][0],menutext[j][1],
               menutext[j][2],menutext[j][3],
               segs[s].item,segs[s].x,segs[s].y,
               segs[s].step,segs[s].w,segs[s].h,
					segs[s].level,segs[s].text);
			if (segs[s].menu == MKEYS)
			{
				fprintf(POSTFILE,
					"/Times-Roman findfont %d scalefont setfont\n",
					3*(segs[s].step-2)+12);
			}
         drawsymbol(s);
      }
   }
	fprintf(POSTFILE,"stroke\n");
   fprintf(POSTFILE,"showpage\n");
   fclose(POSTFILE);
   openpost = FALSE;
   printf("%d symbols written to Postscript file %s\n",
	   scoretop-SCORE,fpostname);
	ybot = yb;
	ytop = yt;
} /* pswrite */
/************************************************/

void fixsymbol(void)
/*
   standardise sizes of symbols created using 
   old versions of LED

   called by lbnread
*/
{
   int h;
   int i;
   int m;
   int s;
   int nb;
   int b1,b2,ydif;

   b1 = 0; b2 = 1;
   for (s = SCORE; s < scoretop; ++s)
   {
      m = segs[s].menu;
      h = segs[s].h;
      i = segs[s].item;
      if (m == MBARS)
      {
         if (i == 1)
            b1 = segs[s].y;
         else
         if (i == 2)
            b2 = segs[s].y;
      }

      if ((m == MWAYS) || (m == MDIRN) || (m == MROTN))
      {
         segs[s].w = 10;
         if (segs[s].step < 2)
         {
            h = 5;
            segs[s].step = 1;
         }
         else
         if (segs[s].step < 4)
         {
            h = 11;
            segs[s].step = 2;
         }
         else
         if (segs[s].step == 4)
            h = 23;
         else
         if (h < 30) 
            h = 23;
         else
         if (h < 40)
            h = 35;
         else
         if (h < 60)
            h = 47;
         else
         if (h < 90)
            h = 71;
         segs[s].h = h;
			if (i < 1) segs[s].ok = FALSE;
      } /* mdirn mrotn mways*/
   } /* s */
   ydif = b2 - b1;
   nb = (ydif-1)/STEP;
   for (s = SCORE; s < scoretop; ++s)
   {
      m = segs[s].menu;
      i = segs[s].item;
      if ((m == MBARS)&&(i > 0))
      {
         bary[i] = (i-1)*(nb*STEP + 1) + b1;
         segs[s].y = bary[i];
      }
   }
} /* fixsymbol */
/*********************************************/

void gettext(int s, char buf[BMAX])
/*
   get text to put on score from .lbn file

   called by lbnread,
*/
{
   int gotsp;
   int spcount;
   int k;
   int tstart;

   gotsp = FALSE;
   spcount = 0;
   for (k = 0; ((k < BMAX)&&(spcount < 8)); ++k)
   {
      if (buf[k] == ' ')
		{
         gotsp = TRUE;
		}
      else
      {
         if (gotsp == TRUE)
			{
            ++spcount;
			}
         gotsp = FALSE;
      }
   }
   tstart = k-1;
   segs[s].length = 0;
   for (k = tstart; ((k < BMAX)&&(buf[k] != '#')); ++k)
   {
      segs[s].text[k-tstart] = buf[k];
      ++segs[s].length;
   }
} /* gettext */
/********************************************/

void lbnread(void)
/*
   read in a score

   called by checkeys,   docommand, main,
   calls     setinfile,  fixsymbol, fixscore,  
             drawbars,   gettext, setbarsp, highesty,
*/
{
   int d;
   int line;
   int h;
   int j;
   int k;
   int m;
	int mu;
   int newtop,oldtop;
	int oldy;
   int s;
   int w;
   int x;
   int y;
   char b0;
   char lev;
   char men[4];
   char buf[BMAX];

   if (openin == FALSE)
	   setinfile();
   s = scoretop;
   oldtop = scoretop;
	oldy = 0;
	if (oldtop > SCORE)
		oldy = segs[oldtop-1].y;
   if  (openin == TRUE)
   {
      line = 0;
      while (fgets(buf,BMAX,INFILE) != NULL)
      {
         b0 = buf[0];
         ++line;
         mu = -1;
         for (k = 0; k < NSYMS; ++k)
         {
            if (b0 == menutext[k][0])
               mu = k;
         }
         if ((mu < 0) || (mu > STAF))
         {
            printf("%s",buf);
            if (ncomments < BMAX)
               strcpy(comments[ncomments++],buf);
            else
               printf("oops: more comment lines than %d\n",BMAX);
         } /* comment */
         else
         {
            sscanf(buf,"%c%c%c%c %d %d %d %d %d %d %c",
               &men[0],&men[1],&men[2],&men[3],
               &j,&x,&y,&d,&w,&h,&lev);
            if ((x < xbot)||((x+w) > xtop)||(y < 1)
               ||(w < 1)||(w > xtop)||(h < 1))
            {
               printf(
                  "lbnread: funny line %d %d %d %d %d %d %d\n",
                  line,x,y,w,h,xbot,xtop);
               printf("     %s\n",buf);
            } /* symbol wrong */
            else
            {
               m = mu*NSYMS;
               if (men[0] == 'B') m = MBARS;
               segs[s].ok = TRUE;
               segs[s].x = x;
               segs[s].y = y+oldy;
               segs[s].w = w;
               segs[s].h = h;
               segs[s].item = j;
               segs[s].level = lev;
               segs[s].step = d;
               segs[s].menu = m;
               if (m == MKEYS)
               {
                  segs[s].level = 'L';
                  if (j == 0)
                     gettext(s,buf);
                  else
                  {
                     segs[s].text[0] = oldkeys[j];
                     segs[s].length = 1;
                     if ((((0 < j)&& (j < 6))
                        ||((8 < j)&&(j < 14)))
                        &&(segs[s].x < staffx[0]/2))
                           segs[s].level = 'B';
                  }
                  if (d > 4) segs[s].step = 2;
                  segs[s].w = segs[s].length*CH*segs[s].step/6;
               }	
               if ((m == MPINS)&&(j == 9)&&(lev != MIDDLE))
               {
                     segs[s].menu = MVOLM;
                     segs[s].item = 7;
                     segs[s].x += 4;
               }
               if ((m == MDIRN) && ((j ==3)||(j == 8)))
					   --segs[s].h;
               if ((m == MMISC) && (j == 1))
                     segs[s].h = w/6;
               if (m == MSTAF)
               {
                  segs[s].item = staffn;
                  ++ staffn;
               }
               ++s;
            } /* x ok */ 
         } /* not comment */
      } /* while not eof */
   } /* openin true */
   //if (INFILE) fclose(INFILE);
   openin = FALSE;
   scoretop = s;
   newtop = s;
   printf("lbnread: %d items input from file %s\n",
      newtop-oldtop,infile);
   highesty();
   fixsymbol();
   fixscore();
   setbarsp();
   drawbars();
   fixscore();
   sprintf(foutname,finname);
   if (INFILE) fclose(INFILE);
   createopen();
} /* lbnread */
/**************************************/

void getsize(void)
/*
    initialise window size

	called by  main,
*/
{
   int c;
   int setf,seth,setw;
   char first,second;
   char key;

   c = 0;
   setw = FALSE;
   seth = FALSE;
   setf = TRUE;
   height = WINDOW_HEIGHT;
   width = WINDOW_WIDTH;
   printf("window size: width %d, height %d\n",
      width,height);
   printf("to change width: hit 'w' followed by the required dimension\n");
   printf("to change height: hit 'h' followed by the required dimension\n");
   printf("to accept: just hit 'Enter'\n");
   printf("to accept and read an lbn file: type filename root\n");
   first = getchar(); 
   if (first == '\n')
   {
      setf = FALSE;
      goto done;
   }
   if (first == 'w')
   {
      setw = TRUE;
      setf =  FALSE;
   }
   if (first == 'h')
   {
      seth = TRUE;
      setf = FALSE;
   }
   second = getchar(); 
   if (second == '\n')
   {
      setf = TRUE;
	  for (  c = 0 ; c < BMAX ; ++c )
           rootname[c] = NULL;
	  rootname[0] = first;
      goto done;
   }
   else
   if (second == ' ')
   {
      setf = FALSE;
      if (seth == TRUE)
         height = 0;
      else
      if (setw == TRUE)
         width = 0;
   } /* second = space */
   else
   {
      setf = TRUE;
      setw = FALSE;
      seth = FALSE;
	  for (  c = 0 ; c < BMAX ; ++c )
        rootname[c] = NULL;
	  rootname[0] = first;
      rootname[1] = second;
	  c = 2;
   } /* second != space */

another:
   key = getchar(); 
   if (key == '\n')  goto done;
   if (setw == TRUE)
      width = 10*width+(key-'0');
   else
   if (seth == TRUE)
      height = 10*height+(key-'0');
   else
      rootname[c++] = key;
   goto another;

done:
   scalex = 1.0/float(width);
   scaley = 1.0/float(height);
   xbot = CH;
   xtop = width - CW - 2*MSIZE - 10;
   ybot = 0;
   ytop = height-1;
   ymax = ytop;
   if (setf == TRUE)
   {
      sprintf(finname,"%s.lbn",rootname);
      if ((INFILE = fopen(finname,"r")) == NULL)
      {
         if (INFILE) fclose(INFILE);
             printf("\n\n oops: cannot open %s for reading?\n",
				 finname);
         for (  c = 0 ; c < BMAX ; ++c )
            rootname[c] = NULL;
         goto out;
      }
      printf("\n opened input file %s OK for reading\n",finname);
      openin = TRUE;
   }
   else
     for (  c = 0 ; c < BMAX ; ++c )
        rootname[c] = NULL;
out:
	;
} /* getsize */
/*********************************************/

void setup(void)
/*
    initialise variables

	called by main,
*/
{
	int s;

	inv2 = float(1)/float(2);
	fac = float(3)/float(2);
	for (s = 0; s < SMAX; ++s)
	{
	  segs[s].length = 0;
	  segs[s].ok = FALSE;
	  segs[s].menu = -1;
	  segs[s].step = 2;
	  segs[s].red = 0.0;
	  strcpy(segs[s].text," ");
	}
	staffx[0] = 0;
	staffn = 0;
	ncomments = 0;
	mode = COPY;
	oldmode = COPY;
	segs[COPY].red = 1.0;
	snap = TRUE;
	segs[SNAP].red = 1.0;
	openin = FALSE;
	openout = FALSE;
	openpost = FALSE;
	scoretop = SCORE;
	barn = 0;
	barsp = 2;
	bar0y = STEP;
	bar1y = STEP;
	bar2y = STEP;
	mfac = float(MSIZE)/float(100);
	again = FALSE;
	target = -1;
	button = GLUT_UP;
	saving = FALSE;
	sprintf(prevmove,"100 100 moveto\n");
	sprintf(foutname,"led.lbn");
} /* setup */
/****************************************/

void setlevel(int n, char lev)
/*
   set segment 'n' to have level 'lev'.

   called by dosymbol,
   calls     makebar, delseg, createsegment, setsymbol, 
             closesegment, copyseg,
*/
{
   int j;
   int m;
   int s;

   s = scoretop++;
   m = segs[n].menu;
   j = segs[n].item;
   if (m == MBARS)
   {
      delseg(n);
      makebar(s,j,segs[n].x,segs[n].y,segs[n].w,lev);
   }
   else
   if (  (m == MDIRN) || (m == MROTN) || (m == MPINS) || (m == MAREA)
     || ((m == MVOLM) && (j > 4)) || ((m == MMISC) && (j == 1))  )
   {
      copyseg(s,n);
      segs[s].level = lev;
      if (m == MPINS)
      {
	    if ((lev == middle) && (segs[n].level != middle))
	       j += 8;
	    if ((lev != middle) && (segs[n].level == middle))
	       j -= 8;
      }
      segs[s].item = j;
      delseg(n);
      createsegment(s);
      if (m == MDIRN)
         setsymbol(s,m,dirdx,dirdy,j,segs[s].step,lev);
      else
      if (m == MROTN)
         setsymbol(s,m,rotdx,rotdy,j,segs[s].step,lev);
      else
      if (m == MMISC)
         setsymbol(s,m,misdx,misdy,j,segs[s].step,lev);
      else
      if (m == MAREA)
         setsymbol(s,m,aredx,aredy,j,segs[s].step,lev);
      else
      if (m == MVOLM)
         setsymbol(s,m,voldx,voldy,j,segs[s].step,lev);
      else
      if (m == MPINS)
         setsymbol(s,m,pindx,pindy,j,segs[s].step,lev);
      closesegment(s);
   }
   else
   if (m == MFACE)
      printf("oops, cannot reset level of FACE item\n");
   else
   if (m == MMISC)
      printf("oops, cannot reset level of MISC item\n");
   else
   if (m == MWAYS)
      printf("oops, cannot reset level of WAYS item\n");
   else
   if (m == MKEYS)
      printf("oops, cannot reset level of KEYS item\n");
   else
   if (m == MVOLM)
      printf("oops, cannot reset level of this VOLM item\n");
   else
   if (m == MLIMB)
      printf("oops, cannot reset level of LIMB item\n");
} /* setlevel */
/******************************************/


void scrollstaff(void)
/*
   extend staff lines to new top of screen
   when scrolling up

   called by docommand,
   calls     drawstaff,
*/
{
   int s;
   int y;

   for (s = SCORE; s < scoretop; ++s)
   {
      if ((segs[s].ok == TRUE) && (segs[s].menu == MSTAF))
      {
         y = ytop-segs[s].y-1;
         if (segs[s].h < y) segs[s].h = y;
            drawstaff(s,segs[s].item,segs[s].x,y,
               segs[s].h,segs[s].level);
      }
   }
} /* scrollstaff*/
/***********************************************/

void makestaff(void)
/*
   create three more staff lines on the score.

   called by checkeys, docommand,
   calls     drawstaff, sort,
*/
{
   int h;
   int s;
   int xstart;
   int y;

   h = height - STEP;
   s = scoretop++;
   if (staffn > 0)
   {
      sort(staffx,staffn);
      xstart = staffx[staffn-1];
   }
   else
   {
      xstart = 0;
      staffn = 3;
   }
   drawstaff(s,staffn-3,(xstart+8*STEP),STEP,h,blank);
   s = scoretop++;
   y = STEP;
   if (barn > 0)
   {
      y = bary[0];
      h = height - y;
   }
   drawstaff(s,staffn-2,(staffx[staffn-3]+3*STEP+1),y,h,low);

   h = height - STEP;
   s = scoretop++;
   drawstaff(s,staffn-1,(staffx[staffn-2]+3*STEP+1),STEP,h,blank);
} /* makestaff */
/**********************************************/

void clear(void)
/*
   clear the score of all symbols

   called by checkeys, docommand.
   calls     delseg, createbars,
*/
{
   int s;

   for (s = SCORE; s < scoretop; ++s)
      delseg(s);
   scoretop = SCORE;
   staffn = 0;
   barn = 0;
   barsp = 2;
   createbars();
   ytop = height-1;
   ymax = ytop;
   ybot = 0;
   ncomments = 0;
} /* clear */
/**************************************************/

void help(void)
/* 
   print helpful list of commands
   
   called by checkeys
 */
{
	printf("\nKeyboard commands :-\n");
	printf("   b - draw barlines\n");
	printf("   c - copy next symbol hit\n");
	printf("   d - delete next symbol hit\n");
	printf("   f - free placing of symbol\n");
	printf("   h - list these comments\n");
	printf("   i - read in a .lbn file\n");
	printf("   m - move next symbol hit\n");
	printf("   p - write out a posttscript .ps file\n");
	printf("   q - write out %s file, then quit\n",foutname);
	printf("   s - snap placing of symbol\n");
	printf("   w - write out %s file\n\n",foutname);
	printf("\nright-hand side Commands :-\n");
	printf("clear     - clear all symbols from the score\n");
	printf("input     - read a .lbn file in\n");
	printf("output    - set the name of the output .lbn file (default: led.lbn)\n");
	printf("postscr   - write a postscript file out\n");
	printf("staff     - add a triple staff to the score (only room for 2)\n");
	printf("bar +     - increase bar line spacing\n");
	printf("bar -     - decrease bar line spacing\n");
	printf("bars n    - draw barlines with spacing 'n', extend staff if scrolled up\n");
	printf("up arrow  - increase size of next symbol hit\n");
	printf("down arrow- decrease size of next symbol hit\n");
	printf("copy      - copy next symbol hit\n");
	printf("move      - move next symbol hit\n");
	printf("delete    - delete next symbol hit\n");
	printf("black/red - make next symbol hit low level\n");
	printf("white+dot - make next symbol hit middle level\n");
	printf("hash      - make next symbol hit high level\n");
	printf("blank     - make next symbol hit blank\n");
	printf("snap      - make next symbol hit touch staff/bar lines\n");
	printf("free      - make next symbol hit stay where it is put\n");
} /* help */
/************************************************/

void wait(int m)
/*
   wait a while

   called by do command
*/
{
   double a,b;
   int j,k;

   a = 1.5;
   b = 2.5;
   for (j = 0; j < 10*m; ++j)
      for (k = 0; k < 1000000; ++k)
         a += b/double(j*k);
   if ( a < 0.0) printf("wait %f\n",a);
} /* wait */
/***********************************************/

void addtext(void)
/*
   add text to the score
	
	called by docommand,
*/
{
   int n;

   printf("type characters to go on score: \n");
   gets(buf);
   n = scoretop++;
   segs[n].x = 100;
   segs[n].y = 100;
   segs[n].ok = TRUE;
   strcpy(segs[n].text,buf);
   segs[n].length = int(strlen(segs[n].text));
   segs[n].level = 'L';
	segs[n].step = 2;
	segs[n].h = CH;
   segs[n].w = segs[n].length*CH*segs[n].step/6;
   segs[n].menu = MKEYS;
   segs[n].item = 0;
   createsegment(n);
   closesegment(n);
} /* addtext */
/*************************************************/

void addcomment(void)
/*
   add comment to .lbn file
	
	called by docommand,
*/
{
   printf("type a line of comment for .lbn output file: \n");
   gets(buf);
   if (ncomments >= BMAX)
      printf("oops: more comment lines than %d\n",BMAX);
   else
   if (buf[0] == '#')
      sprintf(comments[ncomments++],"%s\n",buf);
   else
      sprintf(comments[ncomments++],"# %s\n",buf);
   drawsymbol(COMMENT);
} /* addcomment */
/*************************************************/

void displayscore(void)
/* 
     show all the display list segments
	 
	 called by  doscroll, docommand, main (glutDisplayFunc)
*/
{
   int s;

   glClear(GL_COLOR_BUFFER_BIT);
   glClearColor(1.0,1.0,1.0,0.0); 
   glPushMatrix();
   for (s = 0; s < SCORE; ++s)
   {
      if (segs[s].ok == TRUE)
         glCallList(s);
   }
   glTranslatef(0.0,-float(ybot)/float(height),0.0);
   for (s = SCORE; s < scoretop; ++s)
   {
      if (segs[s].ok == TRUE)
         glCallList(s);
   }
   glPopMatrix();
   glutSwapBuffers();
   glFlush();
} /* displayscore */
/************************************************/

void docommand(int c)
/*
    execute a command from command menu

    called by mouseclick,
    calls     makestaff, create, lbnread, pswrite, lbnwrite,
              clear, drawbars, scrollstaff, help, highesty,
              setoutfile, fixscore, displayscore,
*/
{	int s;

	if ((c > SCROLLDN)&&(c < HELP))
	{
		if ((prevc != SNAP)&&(prevc != FREE))
		{
			segs[prevc].red = 0.0;
			create(prevc);
		}
		for (s = 1; s < SNAP; ++s)
		{
			segs[s].red = 0.0;
			create(s);
		}
	}
   if (c > CLEAR)
	{
		segs[c].red = 1.0;
		create(c);
	}
   switch(c)
   {  
      case TEXTL:
		  printf("text\n");
		  segs[oldmode].red = 0.0;
		  create(oldmode);
		  displayscore();
		  addtext();
		  segs[MOVE].red = 1.0;
		  create(MOVE);
		  printf("move\n");
		  oldmode = mode;
		  mode = MOVE;
		  break;

      case COMMENT:
		  printf("comment\n");
		  displayscore();
		  addcomment();
		  break;

      case STAFF:
		  printf("staff\n");
		  makestaff();
		  break;

      case EXPAND: 
		  oldmode = mode;
		  mode = EXPAND;
		  if (oldmode != mode) printf("expand\n");
		  break;

      case CONTRACT: 
		  oldmode = mode;
		  mode = CONTRACT;
		  if (oldmode != mode) printf("contract\n");
		  break;

      case DELETEL: 
		  oldmode = mode;
		  mode = DELETEL;
		  if (oldmode != mode) printf("delete\n");
		  break;

      case MOVE: 
		  oldmode = mode;
		  mode = MOVE;
		  if (oldmode != mode) printf("move\n");
		  break;

      case COPY: 
		  oldmode = mode;
		  mode = COPY;
		  if (oldmode != mode) printf("copy\n");
		  break;

      case LOW: 
		  oldmode = mode;
		  mode = LOW;
		  if (oldmode != mode) printf("low\n");
		  break;

      case MIDDLE: 
		  oldmode = mode;
		  mode = MIDDLE;
		  if (oldmode != mode) printf("middle\n");
		  break;

      case HIGH:
		  oldmode = mode;
		  mode = HIGH;
		  if (oldmode != mode) printf("high\n");
		  break;
      
      case BLANK: 
		  oldmode = mode;
		  mode = BLANK;
		  if (oldmode != mode) printf("blank\n");
		  break;

      case HELP: 
		  printf("help\n");		  		  		  
		  help();
		  break;

      case BARS: 
		  printf("bars\n");
		  printf("bar lines drawn\n");
		  drawbars();
		  break;

      case PLUS: 
		  printf("plus\n");
		  ++barsp;
		  printf("bar spacing increased to %d\n",barsp);
		  segs[BARS].red = 1.0;
		  create(BARS);
		  break;

      case MINUS:
		  printf("minus\n");
		  --barsp;
		  printf("bar spacing decreased to %d\n",barsp);
		  segs[BARS].red = 1.0;
		  create(BARS);
		  break;

      case POST:
		  printf("postscript\n");
		  printf("write postscript file\n");
		  pswrite();
		  break;

      case OPEN:
		  printf("open file\n");
		  printf("read input file\n");
		  lbnread();
		  break;

      case SAVE:
		  printf("save back into input file %s\n",finname);
		  sprintf(foutname,"%s",finname);
		  openout = TRUE;
		  if ((OUTFILE = fopen(foutname,"w")) == NULL)
		  {
             if (OUTFILE) fclose(OUTFILE);
             printf("\n\n oops: cannot open %s for writing?\n",
				 foutname);
             openout = FALSE;
		  }	
		  if (openout == TRUE)
		  {
			  saving = TRUE;
			  lbnwrite();
		  }
		  break;
	  
      case SAVEAS:
		  printf("save as\n");
		  saveas();
		  break;
		  
      case CLEAR: 
		  printf("clear score\n");
		  clear();
		  break;

      case SNAP:
		  if (snap == FALSE) printf("snap symbol placings\n");
		  snap = TRUE;
		  segs[FREE].red = 0.0;
		  segs[SNAP].red = 1.0;
		  break;

      case FREE:
		  if (snap == TRUE) printf("free symbol placings\n");
		  snap = FALSE;
		  segs[FREE].red = 1.0;
		  segs[SNAP].red = 0.0;
		  break;
   }
   create(SNAP);
   create(FREE);
	target = c;
   prevc = c;
	highesty();
   fixscore();
	if (c != CLEAR)
		drawbars();
} /* docommand*/
/*******************************/

void dosymbol(int t)
/*
    do something to symbol t

    called by mouseclick,
    calls     delseg, scale, drawsymbol, setlevel,
*/
{
   if (mode == DELETEL)
      delseg(t);
   else
   if (mode == EXPAND)
      scale(t);
   else
   if (mode == CONTRACT)
      scale(t);
   else
   if (mode == COPY)
   {
      segs[t].ok = TRUE;
      drawsymbol(t);
   }
   else
   if (mode == MOVE)
   {
      segs[t].ok = TRUE;
      drawsymbol(t);
   }
   else
   if (mode == LOW)
      setlevel(t,low);
   else
   if (mode == MIDDLE)
      setlevel(t,middle);
   else
   if (mode == HIGH)
      setlevel(t,high);
   else
   if (mode == BLANK)
      setlevel(t,blank);
   else
      printf("dosymbol snag %d %d\n",mode,t);
} /* dosymbol */
/**********************************************/

void checkeys(unsigned char key, int x, int y) 
/*
   called by main
   calls  getout, drawbars, lbnwrite, lbnread, pswrite,
          help, clear, makestaff.
*/
{ 
	if (key == 'b')
	{
		printf("key 'b': draw barlines\n");
		drawbars();
	}
	if (key == 'c')
	{
		printf("key 'c': COPY\n");
		oldmode = mode;
		mode = COPY;
		glColor3f(1.0, 0.0, 0.0);
		create(COPY);
		glColor3f(0.0, 0.0, 0.0);
		create(oldmode);
	}
	if (key == 'd')
	{
		printf("key 'd': DELETEL\n");
		oldmode = mode;
		mode = DELETEL;
		glColor3f(1.0, 0.0, 0.0);
		create(DELETEL);
		glColor3f(0.0, 0.0, 0.0);
		create(oldmode);	
	}
	if (key == 'f')
	{
		printf("key 'f': free positioning\n");
		snap = FALSE;
		glColor3f(1.0, 0.0, 0.0);
		create(FREE);
		glColor3f(0.0, 0.0, 0.0);
		create(SNAP);
	}
	if (key == 'h') help();
	if (key == 'i')
	{
		printf("key 'i': input a file\n");
		lbnread();
	}
	if (key == 'm')
	{
		printf("key 'm': MOVE\n");
		oldmode = mode;
		mode = MOVE;
		glColor3f(1.0, 0.0, 0.0);
		create(MOVE);
		glColor3f(0.0, 0.0, 0.0);
		create(oldmode);
	}
	if (key == 'q') getout(0);
	if (key == 'p')
	{
		printf("key 'p': write Postscript file\n");
		pswrite();
	}
	if (key == 's')
	{
		printf("key 's': snap positioning\n");
		snap = TRUE;
		glColor3f(1.0, 0.0, 0.0);
		create(SNAP);
		glColor3f(0.0, 0.0, 0.0);
		create(FREE);
	}
	if (key == 'w')
	{
		printf("key 'w': write %s file\n",foutname);
		lbnwrite();
	}
	if (key == ESCAPE) getout(0);
} /* checkeys */
/***************************************/

int checkhit(int mx, int my)
/*
    find target of mouse click

    called by mouseclick,
*/
{
   int j;
   int hit;
   int hitseg;

   hitseg = -1;
   for (j = 1; j < scoretop; ++j)
   {
      if (segs[j].ok == TRUE)
      {
         hit = TRUE;
			
         if (mx < segs[j].x) hit = FALSE;
         if (mx > (segs[j].x+segs[j].w)) hit = FALSE;
         if (my < segs[j].y) hit = FALSE;
         if (my > (segs[j].y+segs[j].h)) hit = FALSE;
         if (hit == TRUE)
         {
            hitseg = j;
            //return highest segment number hit
         }
      }
   }
   return(hitseg);
} /* checkhit */
/*************************************************/

void mouseclick(GLint b, GLint action, GLint mx, GLint mmy)
/*
    check a mouse click

	calls checkhit, delseg, drawsymbol, docommand, setxy,
	      dosymbol, copyseg,  create,
	called by main, (gluMouseFunc)
*/
{
   int n;
   int my;
   int s;
   int segdown;
   int segup;
   int tj,tm;

   my = height-mmy;
   mousey = my;
   mousex = mx;
   n = scoretop;
   if ((mx > segs[SCROLLUP].w) && (mx < xtop)) 
      my += ybot;
   if (action == GLUT_DOWN)
   {
		for (s = 1; s <= COMMENT; ++s)
		{
			segs[s].red = 0.0;
			create(s);
		}
      saving = FALSE;
      create(SAVE);
      button = GLUT_DOWN;
      segdown = checkhit(mx,my);
      target = segdown;
      tm = segs[target].menu;
      tj = segs[target].item;
      
      printf("\n----MOUSECLICK---down---menu--target----> %d - %d \n",tm,tj);

      if ((target <= 0) || (target >= scoretop)
         || (tj < 0) || (tm < 0) || (tm > SCORE)
         || ((tj > NSYMS)&&(tm != MBARS)))
            printf("%d %d mouseclick down: no item\n",
               mx,my);
      else
      {
         if ((target > COMMANDS) && (target < SCORE))
         {
            docommand(COPY);
         }
         target = segdown;
         if ((target > COMMANDS) && (mode == COPY))
         {
            n = scoretop++;
            copyseg(n,target);
            segs[n].x = mx - segs[target].w/2;
            segs[n].y = my - segs[target].h/2;
            segs[n].ok = TRUE;
            drawsymbol(n);
            target = n;
         }
      }
   }
   else //mouse button up
   {
      button = GLUT_UP;
      segup = checkhit(mx,my);
      if ((segup < 0) || (segup >= scoretop))
         printf("%d %d mouseclick up: no item\n",
            mx,my);
      else
      if (target == segup)
      {
         if (target < COMMANDS)
            docommand(target);
         else
         if (mx < xtop)
         {
            setxy(target);
            dosymbol(target);
         }
         else
            delseg(target);
      }
   }
} /* mouseclick */
/*************************************************/

void mousetrack(GLint mx, GLint mmy)
/*
   track mouse while dragging a symbol

   called by main, (glutMotionFunc)
*/
{
   int my;

   my = height-mmy;
   if ((mx > segs[SCROLLUP].w) && (mx < dirmx)) 
      my += ybot;
   if (segs[target].ok == TRUE)
   {
      segs[target].x = mx - segs[target].w/2;
      segs[target].y = my - segs[target].h/2;
      drawsymbol(target);
   }
} /* mousetrack*/
/**************************************************/

void doscroll()
/*
   scroll while cursor is in scroll boxes

   called by main, (glutIdleFunc)
   calls     displayscore,
*/
{
   int s;
	int yscroll;

	yscroll = ybot;
	dscroll = 1;
   if ((button == GLUT_DOWN) && (target == SCROLLDN))
   {
      yscroll -= dscroll;
      if (yscroll < 0) yscroll = 0;
      ybot = yscroll;
      ytop = ybot+height-1;
   }
   if ((button == GLUT_DOWN) && (target == SCROLLUP))
   {
      yscroll += dscroll;
      ybot = yscroll;
      ytop = ybot+height-1;
      ymax = ytop;
      for (s = SCORE; s < scoretop; ++s)
      if (segs[s].menu == MSTAF)
         segs[s].h = ytop;
   }
   displayscore();
} /* doscroll*/
/**************************************************/

void initgraphics(void) 
/*
   initialise OpenGl and glut graphics systems

      called by main,
*/
{ 
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
   glutInitWindowSize(width, height); 
   glutInitWindowPosition(WINDOW_X,WINDOW_Y); 
   glutCreateWindow(ptitle);
/* background color */ 
   glClearColor(1.0, 1.0, 1.0, 0.5); 
   glShadeModel(GL_SMOOTH); 
/* init viewing matrix */ 
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity(); 
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); 
} /* initgraphics */
/***************************************/ 

int main(int argc, char* argv[])
/*
    calls setup, setoutfile, initgraphics, createmenus,
	      displayscore, mouseclick, mousetrack,
		  checkeys, doscroll,
*/
{
   sprintf(ptitle,"led120");
   printf("%s\n",ptitle);
   setup();
   getsize();
   glutInit(&argc, argv);
   initgraphics();
   createmenus();
   segs[COPY].red = 1.0;
   create(COPY);
   if (openin == TRUE)
	   lbnread();
   glutDisplayFunc(displayscore);/* register Display handler */ 
   glutMouseFunc(mouseclick);    /* register Mouse button handler */
   glutMotionFunc(mousetrack);   /* register Mouse tracker */
   glutKeyboardFunc(checkeys);   /* register Keyboard handler */
   glutIdleFunc(doscroll);
   glutMainLoop();
   getout(0);
   return(0);
}





