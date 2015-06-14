/*
        edellj.c
    ellipsoid editor

  last modified -
     25 Jun 1996    fix up colours when reading a file

   Usage: edellj [-c u] [-d u] [-h] [-n u] [-r] [-s u]
                 [-t u] [-w u] [-x u] [-y u] [-z u]

   Flags-
         -c use 'u' as threshold ascii value
         -d set debug value to u
            (default: 1: little debug information)
         -h list the comments for help
         -n set number of steps to u (default: 20)
         -r reverse intensity levels
         -t set b/w threshold (default: 121)
         -w set height and width to u (default: 256)
         -x set upper left x coordinate (default: 1)
            If u = 0, use cursor position)
         -y set upper left y coordinate (default: 1)
            If u = 0, use cursor position)
         -z zoom by factor u (default: 1)

   Interactive commands-
      (Capitals for inverse function)

          0 - store a joint
          1 - make ellpsd ellipsoid #1 
          2 - make ellpsd ellipsoid #2
          3 - make ellpsd the reference
          4 - store a potential joint position
          5 - draw wire frames
          6 - remove hidden lines
          8 - use Floyd-Steinberg dithering
          9 - use random dithering

          a - create/delete an ellipsoid
          b - make brighter/darker
          c - set free cursor/put cursor on joint
          d - shift down/up
          e - apply to every ellipsoid/just one
          f - apply to current figure/limb
          g - apply shifts to an ellipsoid/joint
          h - list interactive commands/set ref to world
          i - double/halve increments
          j - join/detach ellipsoids 1 and ellipsoid 2 at cursor
          k - increase/decrease window size
          l - shift left/right
          m - animate (faster) / (slower)
          n - next/previous ellipsoid or joint
          o - increase/decrease threshold
          p - copy/reflect set of ellipsoids
          q - quit/backup one command
          r - decrement/increment debug
          s - store/read
          t - ground a set of ellipsoids
          u - expand/contract x
          v - expand/contract y
          w - expand/contract z
          x - rotate clock/anticlock-wise about x axis
          y - rotate clock/anticlock-wise about y axis
          z - rotate clock/anticlock-wise about z axis
          :;- expand/shrink everything in list
          <>- halve/double number of chords

   history -
       24 Nov 1993   single source file
       12 Nov 1993   aniamtion
       29 Oct 1993   joints
       20 Oct 1993   shading
        8 Oct 1993   hidden lines
       13 Aug 1993   multiple ellipsoids
       11 Aug 1993   written (Don Herbison-Evans)

*/
#include <stdio.h>
#include <values.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <sys/types.h>
#include <sys/time.h>

#define min(a,b) ( (a)<(b)?(a):(b) )
#define max(a,b) ( (a)>(b)?(a):(b) )

#define BMAX   256   /* size of input buffer */
#define CMAX   256   /* number of shades per colour */
#define EMAX  1024   /* max number of ellipsoids */
#define IMAX 65535   /* max value of a colour in XWindows */
#define LMAX    16   /* number of animation frames */
#define VMAX  5000   /* maximum number of vectors in image */
#define XMAX  1200   /* max size of image */
#define TRUE     1
#define FALSE    0
#define AMAX  EMAX   /* max number of hidden arcs */
/*
   variables -
*/
char  bit;
char  bename[EMAX][BMAX];/* backup names of ellipsoids */
char  bjname[EMAX][BMAX];/* backup names of joints */
char  buf[BMAX];        /* input string buffer */
char  cmnd[BMAX];       /* shell command string buffer */
char  err[BMAX];        /* error message string buffer */
char  ename[EMAX][BMAX];/* names of ellipsoids */
char  finame[BMAX];     /* input file name */
char  foutname[BMAX];   /* output file name */
char  jname[EMAX][BMAX];/* names of joints */
char  piccy[XMAX][XMAX];/* image array */

int   bcoel[EMAX][2];   /* backup ellipsoids connecting at joints */
int   bdoing;           /* backup doing scene, ell, fig or limb */
int   becount;          /* backup entries in 'elist' */
int   belist[EMAX];     /* backup ellipsoids to be processed */
int   bell1,bell2;      /* backup ellipsoids to be joined */
int   bellpsd;          /* backup current ellipsoid */
int   bfigure;          /* backup code for type of drawing */
int   bhighlight;       /* backup ellipsoid to be highlighted */
int   bjcount;          /* backup number of entries in 'jlist' */
int   bjcursor;         /* backup joint where curser is */
int   bjlist[EMAX];     /* backup list of joints to be modified */
int   bjoin;            /* backup current joint */
int   bnels;            /* backup number of ellipsoids */
int   bnjts;            /* backup number of joints */
int   brefell;          /* backup current reference ellipsoid */
int   bwidth;           /* backup window width */

int   beam;             /* 0 if no line desired, 1 for line */
int   bgr,bgg,bgb;      /* background colours */
int   coel[EMAX][2];    /* ellipsoids connecting at joints */
int   debug;            /* controls diagnostic output */
int   df;               /* animation speed increment */
int   disopen;          /* true if display opened */
int   doing;            /* doing scene, single ell, fig or limb */
int   ecount;           /* entries in 'elist' */
int   elist[EMAX];      /* ellipsoids to be processed */
int   elcol[EMAX][3];   /* colours of the ellipsoids */
int   ell1,ell2;        /* ellipsoids to be joined */
int   ellpsd;           /* current ellipsoid */
int   figure;           /* code for type of drawing
                           5 - wireframe
                           6 - hidden lines
                           7 - major axes
                           8 - floyd shading
                           9 - random shading */
int   first;            /* true if first write to a file */
int   frame;            /* frame number */
int   freeze;           /* true if animation frozen */
int   frame;            /* holds original frame numbers */ 
int   hash[EMAX][EMAX]; /* 0 when outlines 'n' and 'j' have
                           no intersection */ 
int   hidden;           /* true if point on 'n'th outline hidden
                           by 'j'th ellipsoid */
int   highlight;        /* ellipsoid to be highlighted */
int   height;           /* height of image */
int   hori[VMAX];       /* true if line horizontal */
int   inside;           /* true if point on 'n'th outline is inside
                           'j'th ellipsoid */
int   j;                /* ellipsoid whose outline may intersect
                           that of 'n'th */
int   jcount;           /* number of entries in array 'jlist' */
int   jcursor;          /* joint where curser is */
int   jlist[EMAX];      /* list of joints to be modified */
int   join;             /* current joint */
int   joi1;             /* stored joint */
int   length;           /* number of frames to be animated */
int   n;                /* ellipsoid about to be drawn */ 
int   narcs[EMAX];      /* number of hidden arcs around ellipses */
int   nels;             /* number of ellipsoids */
int   newr,newg,newb;   /* colours of current pixel */
int   njts;             /* number of joints */
int   nrtsa;            /* number of intersection points of 
                           outlines of ellipsoids 'n' and 'j' */
int   nrtsb;            /* number of intersections of outline of
                           ellipsoid 'n' with projection of ellipse
                           of intersection of 'j'th ellipsoid with
                           plane of outline of 'n'th ellipsoid */ 
int   nsteps;           /* number of chords around an ellipse */
int   nvecs;            /* number of vector lines in image */
int   oldfig;           /* previous value of 'figure' */
int   oldk;             /* start of current pixel colours */
int   oldr,oldg,oldb;   /* colours of previous pixel */
int   ok;               /* false if snag encountered */ 
int   outsid;           /* true if ellipsoid totally outside */
int   pmax;             /* maximum colour value */
int   refell;           /* current reference ellipsoid */
int   reverse;          /* true if intensities to be inverted */
int   rolling;          /* true if animating */
int   speed ;           /* animation rate (frames/sec) */
int   thresh;           /* threshold for grey values to be drawn */
int   valid ;           /* true if order of 'a' and 'b' type
                           intersections is valid */
int   width;            /* width of the window */
int   xhii[VMAX],xloi[VMAX];
int   x,y;              /* top left corner coordinates */
int   zoom;             /* zoom factor */

double bax3[EMAX][3];   /* backup axis lengths of ellipsoids */
double baxfac;          /* backup factor for changing axis lengths */
double bcen[EMAX][3];   /* backup centres of the ellipsoids */
double bcursor[3];      /* backup position of cursor */
double bdshift;         /* backup shift amount */
double bjnext[3];       /* backup next potential joint coordinates */
double bjnt[EMAX][3];   /* backup joint coordinates */
double bquat[EMAX+1][5];/* backup orientations of ellipsoids */

double aerr[4];         /* errors on atheta  */
double alfa,beta;       /* x and y parameter addends */
double ang[3];          /* Eulerian angles of current ellipsoid */
double appear[EMAX][AMAX][2];/* values of Cohens parameter at 
                              dis- and re- appearance of invisible
                              arcs of ellipsoid outlines */ 
double atheta[4];       /*  parameter values on 'n'th outline 
                            where it is intersected by 'j'th*/
double axfac;           /* factor for changing axis lengths */
double axxn,axyn;       /* semi-minor and major axes of ellipse */
double ax3[EMAX][3];    /* axis lengths of ellipsoids */
double ax2[EMAX][2];    /* axis lengths of ellipses */
double berr[4];         /* errors on btheta */
double btheta[4];       /* parameter values on 'n'th outline where it 
                           is intersected by ellipse of intersection
                           of 'j'th ellipsoid and plane of outline of
                           the 'n'th */ 
double cen[EMAX][3];    /* centres of the ellipsoids */
double cj[3];           /* coeffs of plane of outline of 'j'th
                           ellipsoid about centre of 'n'th */ 
double cn[3];           /* coeffs of plane of outline of 'n'th
                           ellipsoid about own centre, in form -  
                           cn[0]*x + cn[1]*y + cn[2] + z = 0 */
double coef[EMAX][6];   /* coeffs of outlines of ellipses */
double coj[6];          /* coeffs of outline ellipse of 'j'th
                         ellipsoid about centre and axes of 'n'th
                         ellipse outline */ 
double con[6];          /* coeffs of elliptical outline of 'n'th
                           ellipsoid about its own centre in form -  
                           con[0]*x*x + con[1]*y*y + con[2]*x*y 
                           + con[3]*x + con[4]*y + con[5] = 0 */
double cursor[3];       /* position of cursor */
double dang;            /* angle increment */
double deg;             /* conversion factor radians to degrees */
double den[EMAX];
double dshift;          /* amount ellipsoids to be shifted */
double doub0;          /* double version of 0 */
double doub1;
double doub2;
double doub3;
double doub4;
double doub6;
double doub10;
double doub12;
double doub24;
double doub50;
double doub500;
double doub1000;
double doubmax;         /* approx square root of max double */
double doubmin;         /* smallest double number */
double doubtol;         /* tolerance of double numbers */
double dparam;          /* step size of Cohen parameter */
double dxdy[VMAX];      /* slopes of vectors in picture */
double ell[EMAX][3][3]; /* matrices of ellipsoids */
double ellj[3][3];      /* matrix of 'j'th ellipsoid */
double elln[3][3];      /* matrix of 'n'th ellipsoid */ 
double ellj22;          /* normalizing coeff for polynomial of 'j'th
                           outline */ 
double f[3];            /* grow factors */
double inv2;
double inv3;
double inv4;
double inv10;
double jnext[3];        /* next potential joint coordinates */
double jnt[EMAX][3];    /* joint coordinates */
double maxax[EMAX];     /* largest  semiaxis of ellipsoids */
double minax[EMAX];     /* smallest semiaxis of ellipsoids */ 
double mcn[5] ;         /* coeffs of sin(theta) in Cohen's matrix
                           for outline of 'n'th ellipsoid */ 
double maxval;          /* tangent of half minimum stored angle
                           increment */ 
double p,q;             /* x and y scaling parameters */
double phi,cphi,sphi;   /* angle of orientation of major axis of 
                           'n'th ellipsoid outline to 'x' axis */ 
double phi2[EMAX];      /* orientations of ellipses */
double pi;
double piby2;
double piby4;
double plane[EMAX][3];  /* coefficients of planes of outlines */
double quat[EMAX+1][5]; /* orientations of ellipsoids */
double rad;             /* conversion factor degrees to radians */
double rcoj[6];
double rt3;             /* square root of 3 */
double rterr[4];        /* errors on quartic roots */
double sqsep;           /* square of separation of centres of
                           ellipsoids j and n */ 
double sqmax;           /* square of maximum separation of centres
                           of ellipsoids n and j that will still
                           allow them to overlap */ 
double theta[4];        /* starts and ends of possible hidden arcs */
double tolr;
double tstval;
double twopi;           /* ratio of perimeter to radius of circle */
double wtos;            /* scaling from world to screen */
double xm[2];           /* partial projections of xstrt by mc */ 
double xcen,ycen;       /* coordinates of centre of current ellipse */
double xmax[EMAX];
double xmin[EMAX];
double xold,yold;
double xstrt[2];        /* initial point of 'n'th ellipse 
                           relative to its own centre */
double x1[VMAX],x2[VMAX],y1[VMAX],y2[VMAX];
double ymax[EMAX];
double ymin[EMAX];
double zmin[EMAX];

double sqrt(),atan(),atan2(),fabs();
double acos(),cos(),sin(),exp(),log();
double sqr();

FILE  *infile;
FILE  *outfile;
/*
   X window variables -
*/
   Drawable             pixmap[LMAX];
   XErrorEvent          *error;
   XColor               cell;
   int                  thedepth,thescreen;
   int                  thex,they;
   int                  vmatch,vmask;
   unsigned long        evmask;
   Window               thewindow;
   Window               rootwindow;
   XEvent               theevent;
   Display              *thedisplay;
   Visual               *thevisual;
   XVisualInfo          vtemplate;
   XVisualInfo          *vlist;
   XSizeHints           thesizehints;
   XGCValues            thegcvalues;
   GC                   thegc;
   XSetWindowAttributes thewindowattributes;
   Colormap             cmap;
   unsigned int         thewidth,theheight;
   unsigned int         borderwidth;
   unsigned int         theclass;
   unsigned long        thevaluemask;
   unsigned long        thewindowmask;
/*
   special arrays -
*/
int   perm[3][3][3] = {
      { {2,1,1},{1,3,4},{1,5,3} },
      { {3,1,5},{1,2,1},{4,1,3} },
      { {3,4,1},{5,3,1},{1,1,2} }};
/*
     t - successive sets of ten values mean -   

     (1,2) - arc hidden if (3,4) hidden 
     (3,4) - arc to test to reset arc(1) 
     (4,5) - arc that is always hidden, and whose lower 
             and upper ends may be reset to be (3) 
             or (6) respectively. 
     (5,6) - arc to test to reset upper end of (4,5) 
     (7,8) - arc also hidden if (5,6) is hidden. 

     meaning of values -  
      - 5       - use ( -maxval) 
    +1,+2,+3,+4 - use atheta member 
    11,12,13,14 - use btheta member 
     20         - use  (maxval) 
      0         - skip this test 

     meaning of comments within / - /s - 
      .  this arc may or may not be obscured 
      -  this arc is obscured in all cases 
         this arc is always visible 
*/ 
   int t[420] = { 0,  0,  0,  0,  0,  0,  0,  0,  0, 0, /*   9*/
/* 2 - 2 class 1,  /.b1 - b2.a1 a2./ */
                  1,  2, 20, -5, 11, 12,  1,  0,  0, 0, /*  19 */
/* 2 - 2 class 2  / a1.b1 - b2.a2 / */
                  1,  0,  0,  1, 11, 12,  2,  0,  0, 0, /*  29 */
/* 2 - 2 class 3  /.a1 a2.b1 - b2./ */
                  1,  0,  0,  2, 11, 12, 20, -5,  1, 0, /*  39 */
/* 2 - 2 class 4  / - b1.a1 a2.b2 - / */
                  2,  0,  0,  2, 12, 20,  0,  0,  0, 0, /*  49 */
                  0,  0,  0,  0, -5, 11,  1,  0,  0, 0, /*  59 */
/* 2 - 4  class 1  /.a1 a2.b1 - b2.b3 - b4./ */
                  2,  0,  0,  2, 11, 12, 13,  0,  0, 0, /*  69 */
                  0,  0,  0,  0, 13, 14, 20, -5,  1, 0, /*  79 */
/* 2 - 4  class 2  / - b1.a1 a2.b2 - b3.b4 - / */
                  3,  0,  0,  2, 12, 13, 14,  0,  0, 0, /*  89 */
                  0,  0,  0,  0, 14, 20,  0,  0,  0, 0, /*  99 */
                  0,  0,  0,  0, -5, 11,  1,  0,  0, 0, /* 109 */
/* 2 - 4  class 3  /.b1 - b2.a1 a2.b3 - b4./ */
                  2, 14, 20, -5, 11, 12,  1,  0,  0, 0, /* 119 */
                  0,  0,  0,  2, 13, 14,  0,  0,  0, 0, /* 129 */
/* 2 - 4  class 4  / - b1.b2 - b3.a1 a2.b4 - / */
                  3,  0,  0,  2, 14, 20,  0,  0,  0, 0, /* 139 */
                  0,  0,  0,  0, -5, 11, 12,  0,  0, 0, /* 149 */
                  0,  0,  0,  0, 12, 13,  1,  0,  0, 0, /* 159 */
/* 2 - 4   class 5  /.b1 - b2.b3 - b4.a1 a2./ */
                  2,  2, 20, -5, 11, 12, 13,  0,  0, 0, /* 169 */
                  0,  0,  0,  0, 13, 14,  1,  0,  0, 0, /* 179 */
/* 2 - 4  class 6  /a1.b1 - b2.b3 - b4.a2 / */
                  2,  0,  0,  1, 11, 12, 13,  0,  0, 0, /* 189 */
                  0,  0,  0,  0, 13, 14,  2,  0,  0, 0, /* 199 */
/* 4 - 2  class 1  /.b1 - b2.a1 a2.a3 a4./ */
                  2,  4, 20, -5, 11, 12,  1,  0,  0, 0, /* 209 */
                  0,  0,  0,  0,  2,  2,  3,  0,  0, 0, /* 219 */
/* 4 - 2  class 2  /a1.b1 - b2.a2 a3.a4 / */
                  2,  0,  0,  1, 11, 12,  2,  0,  0, 0, /* 229 */
                  0,  0,  0,  0,  3,  3,  4,  0,  0, 0, /* 239 */
/* 4 - 2  class 3   /.a1 a2.b1 - b2.a3 a4./ */
                  2,  0,  0,  2, 11, 12,  3,  0,  0, 0, /* 249 */
                  0,  0,  0,  0, -5, -5,  1,  4, 20, 0, /* 259 */
/* 4 - 2  class 4   / a1.a2 a3.b1 - b2.a4 / */
                  2,  0,  0,  3, 11, 12,  4,  0,  0, 0, /* 269 */
                  0,  0,  0,  0,  1,  1,  2,  0,  0, 0, /* 279 */
/* 4 - 2  class 5   / .a1 a2.a3 a4.b1 - b2./ */
                  2,  0,  0,  4, 11, 12, 20, -5,  1, 0, /* 289 */
                  0,  0,  0,  0,  2,  2,  3,  0,  0, 0, /* 299 */
/* 4 - 2  class 6  / - b1.a1 a2.a3 a4.b2 - / */
                  3,  0,  0,  0, -5, 11,  1,  0,  0, 0, /* 309 */
                  0,  0,  0,  4, 12, 20,  0,  0,  0, 0, /* 319 */
                  0,  0,  0,  0,  2,  2,  3,  0,  0, 0, /* 329 */
/* 4 - 4  class 1   /.b1 - b2.a1 a2.b3 - b4.a3 a4./ */
                  2,  4, 20, -5, 11, 12,  1,  0,  0, 0, /* 339 */
                  0,  0,  0,  2, 13, 14,  3,  0,  0, 0, /* 349 */
/* 4 - 4  class 2   / a1.b1 - b2.a2 a3.b3 - b4.a4 / */
                  2,  0,  0,  1, 11, 12,  2,  0,  0, 0, /* 359 */
                  0,  0,  0,  3, 13, 14,  4,  0,  0, 0, /* 369 */
/* 4 - 4  class 3  /.a1 a2.b1 - b2.a3 a4.b3 - b4./ */
                  2,  0,  0,  2, 11, 12,  3,  0,  0, 0, /* 379 */
                  0,  0,  0,  4, 13, 14, 20, -5,  1, 0, /* 389 */
/* 4 - 4  class 4  / - b1.a1 a2.b2 - b3.a3 a4.b4 - / */
                  3,  0,  0,  2, 12, 13,  3,  0,  0, 0, /* 399 */
                  0,  0,  0,  0, -5, 11,  1,  0,  0, 0, /* 409 */
                  0,  0,  0,  4, 14, 20,  0,  0,  0, 0 }; /* 419 */

int b[5][5][6] =    {{
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 }  },
                    {
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 }  },
                    {
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {  10,  20,  30,  40,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     { 200, 220, 240, 260, 280, 300 }  },
                    {
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 }  },
                    {
                     {   0,   0,   0,   0,   0,   0 },
                     {   0,   0,   0,   0,   0,   0 },
                     {  60,  80, 110, 130, 160, 180 },
                     {   0,   0,   0,   0,   0,   0 },
                     { 330, 350, 370, 390,   0,   0 } } };

/*********************************************/

/*
   subroutines -

      main           - organises things
      dopic          - draw the picture
      getpar         - get invoked parameters
      setdata        - set the initial data
      doframe        - draw image in window
      coline         - set a pixel, maybe zoomed
      startwindows   - start the X-Window system
      exec           - execute a system command
      checkeys       - check the keyboard for new commands
      nearest        - find nearest element to cursor
      alterw         - change window size
      printstuff     - print out current information
      setjnt         - set cursor to a joint
      setref         - set reference to some ellipsoid
      setcur         - set up curser
      dohelp         - print help information
      copy           - copy set of ellipsoids
      expand         - change increments
      nexthigh       - make ellpsd next ellipsoid
      getout         - exit gracefully
      convert        - convert vectors to raster
      drawcur        - draw cursor

      plotel         - convert ellipses to chords
      shrink         - set up smaller copy of an ellipsoid
      lineto         - draw a line from old point to new point
      moveto         - move current point
      setell         - set data for an ellipse
      proces         - generate arcs around an ellipse
      dopart         - generate chords along an arc
      sqr            - square a number

      mkquat         - convert angles to quat array entries 
      visel          - compute each ellipse outline
      setnup         - set up parameters of nth ellipsoid 
      matmul         - multiply two matrices together 
      setcof         - find coefficients from matrix
      setaxe         - find semiaxes of an ellipse 
      setpro         - find orientation
      dospinby       - spins a set of ellipsoids by a given angle 
      twirl          - does a rotation on all parts in list 
      matrot         - rotates a single ellipsoid 
      vecmul         - multiplies a selected vector by a matrix 
      vecmat         - multiplies a vector by a matrix 
      shift          - moves a set of ellipsoids 
      rset           - sets up a primitive rotation matrix 
      setels         - finds ellipsoids and joints connected to a given 
                         ellipsoid 
      doattach       - joins 2 figures into 1 
      dodetach       - breaks a figure into two 
      domoveby       - moves a set of ellipsoids relative to refell 
      dogrofig       - scales a set of ellipsoids in size 
      dogroell       - scales an ellipsoid's axes 
      rotput         - make quaternion from matrix
      delel          - delete an ellipsoid
      addel          - create another ellipsoid
      store3         - store the scene
      ipr            - print a double as an integer
      mkang          - make angles from quat array
      brighten       - make ellipsoids brighter

      read3          - read an ellipsoid file
      rotget         - form a rotation matrix and its inverse 
      matmul         - multiply two matrices together 
      setcof         - find ellipsoid coefficients from matrix form 
      setpln         - find coefficients of outline plane 
      setax2         - find semi-axes of an ellipse 
      setphi         - find orientation and Cohen matrix of ellipse 
      shfcof         - find coefficients of shifted ellipse 
      rotcof         - find coefficients of rotated ellipse 
      ellpln         - find coefficients of cut ellipsoid ellipse 
      ellcut         - find intersections of 2 ellipses 
      order          - find hidden arcs 
      two0a          - find hidden arcs when 2 of 'a' type and 0 of 'b' 
                       type of intersection 
      two0b          - find hidden arcs when 2 of 'b' type and 0 of 'a' 
                       type of intersection 
      four0a         - find hidden arcs when 4 of 'a' type and 0 of 'b' 
                       type of intersection 
      four0b         - find hidden arcs when 4 of 'b' type and 0 of 'a' 
                       type of intersection 
      both           - find hidden arcs when a and b type intersections 
      chkrts         - check topology of a and b type intersections 
      allarc         - find hidden arcs when a - b topology wrong 
      obscur         - check point on "n"th outline against "j"th ellipsoid 
      insert         - put a hidden arc in a list of hidden arcs 
      sort           - sort two arrays  into ascending order 
      qudrtc         - solve a quadratic equation 
      cubic          - solve special cubic equation 
      acos3          - find cos(arccos(x)/3) by table lookup 
      curoot         - find cube root
      quartic        - arrange solution of quartic equation
      ferrari        - solve quartic using Ferrari's algorithm
      neumark        - solve a quartic equation  using Neumark's algorithm
      errors         - find errors of quartic roots.

      edither        - organise dithering
      dopic          - scan input image
      quantise       - convert a row of input image
      random         - return a random number in range 0 to pmax
      start          - initialise random numbers

      edrasel       - run through ellipsoids
      allcofs       - set ellipsoid's coefficients 
      shadel        - loop through all x and y, colouring appropriately
      zdepth        - find depth of ellipsoid surface at point x,y
      illum         - find relative brightness of point on surface
      setpnt        - setgrey value of a pixel

      edshow         - organises animation
      dopixmap       - create a pixmap and load it
      display        - repeatedly display the animation
      image          - diplay one image
      msleep         - sleep for some milliseconds
      shkeys         - check keyboard

      backup          - store backup values
      dobackup        - restore previous values
      tbackup         - test whether backup needed

************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls  setdata, setels, getpar, startwindows
          read3, dohelp, dopic, checkeys.
*/
{
   int doread;
   int seq;

   fprintf(stderr,"edellj : ellipsoid editor\n");
   oldfig = 0;
   setdata();
   doread = getpar(argc,argv);
   if (doread == TRUE) read3();
   ellpsd = 1;
   setels(1,-1);
   startwindows(x);
   for (seq = 0; seq < MAXINT; ++seq)
   {
      if (debug <= 0) fprintf(stderr,"maina %d\n",seq);
      if (seq != 0) XClearWindow(thedisplay,thewindow);
      dopic();
      XFlush(thedisplay);
      if (seq == 0)
      {
         pixmap[0] = XCreateWindow(thedisplay,rootwindow,
		   thex,they,thewidth,theheight,borderwidth,
                   thedepth,InputOutput,vlist[0].visual,
                   thewindowmask, &thewindowattributes);
         XCopyArea(thedisplay,thewindow,pixmap[0],thegc,
                   0,0,thewidth,theheight,0,0);
         dohelp();
         XFlush(thedisplay);
      }
      XSynchronize(thedisplay,TRUE);
      checkeys(seq);
   }
} /* main */
/************************************************/

dopic()
/*
   draw the picture

   called by main, setframes
   calls visel, plotel, shrink, edhide, edrasel, edither, edskel.
*/
{
      ok = TRUE;
      nvecs = 0;
      if (figure == 5)
      {
         if (oldfig != figure) fprintf(stderr,"wireframe\n");
         visel();
         for (n = 1; n < nels; ++n)
            plotel(n);
         shrink(ellpsd);
      }
      else if (figure == 6)
      {
         if (oldfig != figure) fprintf(stderr,"hiding\n");
         edhide();
         for (n = 1; n < nels; ++n)
            plotel(n);
         shrink(ellpsd);
      }
      else if ((figure == 8) || (figure == 9))
      {
         if (oldfig != figure)
         {
            if (figure == 9) fprintf(stderr,"random dithering\n");
            if (figure == 8)
               fprintf(stderr,"Floyd-Steinberg shading\n");
         }
         edrasel();
         edither(figure);
         doframe();
         visel();
         plotel(ellpsd);
      }
      else
         fprintf(stderr,"unimplemented figure- %c\n",figure);
      oldfig = figure;
      drawcur();
} /* dopic */
/***************************************/

int getpar(argc,argv)
int argc;
char *argv[];
/*
   get the parameters

   called by main.
*/
{
   int doread;
   int p;

   doread = FALSE;
   for ( p = 1; p < argc; ++ p)
   {
          sprintf(buf,"%s",argv[p]);
          if (buf[0] != '-')
          {
              doread = TRUE;
              sprintf(finame,"%s",argv[p]);
          }
          else if (buf[1] == 'c')
	  {
                if (p < (argc-1))
                {
		   ++ p;
		   sscanf(argv[p], "%c",&thresh);
                }
	  } 
          else if (buf[1] == 'd')
	  {
                if (p < (argc-1) )
                {
		   ++ p;
		   sscanf(argv[p], "%d",&debug);
                }
          }
          else if (buf[1] == 'h')
	  {
             sprintf(cmnd,"more ~don/src/edellj.c\n");
             exec(cmnd);
             exit(0);
	  } 
          else if (buf[1] == 'n')
	  {
                if (p < (argc-1) )
                {
		   ++ p;
		   sscanf(argv[p], "%d",&nsteps);
                }
	  } 
          else if (buf[1] == 'r')
              reverse = TRUE;
          else if (buf[1] == 'w')
	  {
                if (p < (argc-1) )
                {
		   ++ p;
		   sscanf(argv[p], "%d",&height);
                }
                width = height;
          }
          else if (buf[1] == 't')
	  {
                if (p < (argc-1))
                {
		   ++ p;
		   sscanf(argv[p], "%d",&thresh);
                }
	  } 
          else if (buf[1] == 'x')
	  {
                if (p < (argc-1))
                {
		   ++ p;
		   sscanf(argv[p], "%d",&x);
                }
                if ((x < 0) || (x > 1023))
                {
                  sprintf(err,"funny -x parameter: %d",x);
                  getout(1);
                }
	  } 
          else if (buf[1] == 'y')
	  {
                if (p < (argc-1))
                {
		   ++ p;
		   sscanf(argv[p], "%d",&y);
                }
                if ((y < 0) || (y > 1023))
                {
                  sprintf(err,"funny -y parameter: %d",y);
                  getout(1);
                }
	  } 
          else if (buf[1] == 'z')
	  {
                if (p < (argc-1))
                {
		   ++ p;
		   sscanf(argv[p], "%d",&zoom);
                }
                if (zoom < 1)
                {
                   sprintf(err,"funny zoom factor: %d");
                   getout(1);
                }
	  } 
	  else
          {
             sprintf(err,"unrecognized flag: %s",argv[p]);
             getout(1);
          }
   }
   wtos = (double)width/doub1000;
   if (debug <= 0) fprintf(stderr,
     "getpar %d %d %d %d %d %d %d %d %d %d\n",
        figure,x,y,width,thresh,zoom,XMAX,length,debug,TRUE);
   return(doread);
} /* getpar */
/************************************************/

setdata()
/*
   set up the initial data

   called by main.
   calls     setels, mkquat.
*/
{
   double doub,doubm;
   int j,k;

   debug = 3;
   if (debug <= 0)
            fprintf(stderr,"setdataa %d\n",TRUE);
   speed = 25;
   rolling = FALSE;
   pmax = CMAX-1;
   doing = 1;
   doub1 = (double)1;
   doub2 = (double)2;
   doub3 = (double)3;
   doub4 = (double)4;
   doub6 = (double)6;
   doub10 = (double)10;
   doub12 = (double)12;
   doub24 = (double)24;
   doub50 = (double)50;
   doub500 = (double)500;
   doub1000 = (double)1000;
   doub0 = (double)0;
   maxval = (double)10000;
   piby4 = atan(doub1) ;
   piby2 = piby4+piby4;
   pi = piby2+piby2 ;
   twopi = pi+pi;
   deg = pi/(double)180;
   rad = (double)180/pi;
   inv2 = doub1/doub2;
   inv3 = doub1/doub3;
   inv4 = doub1/doub4;
   inv10 = doub1/doub10;
   dshift = (double)100;
   dang = pi/(double)8;
   doubm = doub1;
   for (doub = inv2;
      ((doub != doub0) && (doub < doubm));
          doub *= doub)
   {
      doubmin = doubm;
      doubm = doub;
   }
   doubmax = doub4/doubmin;
   for (doubtol = inv2;
          (doub1+doubtol > doub1+inv2*doubtol); doubtol *= inv2);
   tolr = doub3*sqrt(doubtol);
   width = 256;
   height = 256;
   cen[0][0] = doub0;
   cen[0][1] = doub0;
   cen[0][2] = doub0;
   ax3[0][0] = doub1;
   ax3[0][1] = doub1;
   ax3[0][2] = doub1;
   refell = 0;
   ell1 = -1;
   ell2 = -1;
   joi1 = -1;
   nels = 2;
   njts = 0;
   cen[1][0] = doub500;
   cen[1][1] = doub500;
   cen[1][2] = doub500;
   ax3[1][0] = (double)100;
   ax3[1][1] = (double)102;
   ax3[1][2] = (double)101;
   mkquat(0,doub0,doub0,doub0);
   mkquat(1,doub0,doub0,doub0);
   nsteps = 16;
   dparam = twopi/nsteps;
   disopen = FALSE;
   reverse = FALSE;
   jcursor = -1;
   cursor[0] = doub500;
   cursor[1] = doub500;
   cursor[2] = doub500;
   axfac = doub1 + inv2;
   sprintf(finame,"edellj.3");
   sprintf(foutname,"edellj.3");
   first = TRUE;
   for (j = 0; j < EMAX; ++j)
   {
      narcs[j] = 1;
      appear[j][0][0] = -maxval;
      appear[j][0][1] = -maxval;
      elcol[j][0] = 255;
      elcol[j][1] = 128;
      elcol[j][2] =  64;
      sprintf(ename[j],"e%d",j);
      sprintf(jname[j],"j%d",j);
   }
   thresh = 51;
   zoom = 1;
   length = 1;
   figure = 5;
   if (debug <= 0)
      fprintf(stderr,"setdatab %9g %d\n",axfac,zoom);
}  /* setdata */
/***********************************************/

doframe()
/*
   draw image in window

   called by main.
   calls  coline, getout.
*/
{
   int pixel;
   int j,k,m;

   if (debug <= 1)
       fprintf(stderr,"doframea %d %d %d %d %d %d\n",
           width,height,x,y,thresh,zoom);
/*
   draw the picture -
*/
   for ( j = 0; j < height; ++ j)
   {
      if (debug < 0) fprintf(stderr,"doframee %d\n",j);
      oldk = 0;
      oldr = -1; oldg = -1; oldb = -1;
      for ( k = 0; k < width; ++ k)
      {
            pixel = piccy[k][j];
               if (debug <= 0)
                  fprintf(stderr,"doframeg %3d %3d %3d %3d\n",
                     j,k,thresh,pixel);
            if ( ((pixel < thresh) && (reverse == FALSE))
              || ((pixel > thresh) && (reverse == TRUE )) )
            {
               for (m = zoom*j; m < zoom*(j+1); ++m)
                     XDrawLine(thedisplay,thewindow,thegc,
                       zoom*k,m,zoom*(k+1)-1,m);
            }
      }
   }
} /* doframe */
/**********************************/

coline(j,k)
int j,k;
/*
   colour a point, allowing for zoom replication

   called by doframe
*/
{
   int flag;
   int p;

   if (k != 0)
   {
      for (p = zoom*j; p < zoom*(j+1); ++p)
          XDrawLine(thedisplay,thewindow,thegc,
               zoom*oldk,p,zoom*k-1,p);
   }
   oldk = k;
} /* coline */ 
/**********************************/

startwindows(x)
int x;
/*
   open X window system.

   called by main.
*/
{
   thex = x;
   they = y;
   thewidth = zoom*width;
   theheight = zoom*height;
   thedisplay = XOpenDisplay(NULL);
   if ( thedisplay == NULL )
   {
      sprintf(err,"cannot open display");
      getout(1);
   }
   thescreen = DefaultScreen(thedisplay);
   disopen = TRUE;
   thedepth = DefaultDepth(thedisplay,thescreen);
   cmap = DefaultColormap(thedisplay,thescreen);
   thewindowattributes.backing_store = Always;
   thewindowattributes.border_pixel =
             BlackPixel(thedisplay,thescreen);
   thewindowattributes.background_pixel =
             WhitePixel(thedisplay,thescreen);
   thewindowattributes.override_redirect = TRUE;
   thewindowattributes.colormap = cmap;
   thewindowmask = ( CWColormap | CWBackingStore |
             CWBackPixel | CWBorderPixel | CWOverrideRedirect);
   vtemplate.screen = thescreen;
   vtemplate.depth = thedepth;
   vmask = VisualScreenMask | VisualDepthMask;
   vlist = XGetVisualInfo(thedisplay,vmask,&vtemplate,&vmatch);
   if (vmatch <= 0)
   {
      sprintf(err,"no matching visual");
      getout(1);
   }
   theclass = InputOutput;
   borderwidth = 1;
   thesizehints.flags = PPosition | PSize;
   thesizehints.x = thex;
   thesizehints.y = they;
   thesizehints.width = thewidth;
   thesizehints.height = theheight;
   rootwindow = RootWindow(thedisplay,thescreen);
   if ((x == 0) && (y == 0))
   {
      thewindow = XCreateSimpleWindow(thedisplay,rootwindow,
                   thex,they,thewidth,theheight,borderwidth,
                   BlackPixel(thedisplay,thescreen),
                   WhitePixel(thedisplay,thescreen));
      fprintf(stderr,"simple window\n");
   }
   else
   {
      thewindow = XCreateWindow(thedisplay,rootwindow,
		   thex,they,thewidth,theheight,borderwidth,
                   thedepth,InputOutput,vlist[0].visual,
                   thewindowmask, &thewindowattributes);
      fprintf(stderr,"root window\n");
   }
   XStoreName(thedisplay,thewindow,"edellj");
   XMapRaised(thedisplay,thewindow);
   XSetNormalHints(thedisplay,thewindow,&thesizehints);
   if (reverse == FALSE)
   {
      thegcvalues.foreground = BlackPixel(thedisplay, thescreen);
      thegcvalues.background = WhitePixel(thedisplay, thescreen);
   }
   else
   {
      thegcvalues.background = BlackPixel(thedisplay, thescreen);
      thegcvalues.foreground = WhitePixel(thedisplay, thescreen);
   }
   thegc = XCreateGC(thedisplay,thewindow,
             GCForeground | GCBackground , &thegcvalues);
   if ( thegc == 0 )
   {
      sprintf(err,"'startwindows' : cannot create gc");
      getout(1);
   }
   XInstallColormap(thedisplay,cmap);
   evmask = ( KeyPressMask );
   XSelectInput(thedisplay,thewindow,evmask);
   cell.flags = DoRed | DoGreen | DoBlue;
   XClearWindow(thedisplay,thewindow);
   if (debug <= 0) fprintf(stderr,"startwindowsb\n");
} /* startwindows */
/******************************************/

exec(cmnd)
char cmnd[BMAX];
/*
   execute a system command with optional echo

   called by isfile, getout, getpar, getfiles.
*/
{
   if (debug <= 0) fprintf(stderr,"%s",cmnd);
   system(cmnd);
} /* exec */
/******************************************/

checkeys(seq)
int seq;
/*
   check if button or key pressed.

   called by  doframe, display.
   calls      setels, shift, dospinby, setref, setcur, setjnt,
              getout, addel, brighten, expand, nexthigh, store3,
              edshow, alterw, delel, dohelp, doattach, dodetach,
              nearest, dogrofig, tbackup, dobackup.
*/
{
   XEvent theevent;
   KeySym thekeysym;
   XComposeStatus thecomposestatus;
   int nearest();
   int maxlen;
   int slength;
   int j;
   char buf[BMAX];

another:
   if (debug <= 0) fprintf(stderr,"checkeysa %d\n",seq);
   maxlen = BMAX-1;
   XNextEvent(thedisplay,&theevent);
   if (theevent.type == KeyPress)
   {
      slength = XLookupString
         (&theevent,buf,maxlen,&thekeysym,&thecomposestatus);
      fprintf(stderr,"key %c\n",buf[0]);
      tbackup(buf[0]);
           if (buf[0] == '0') {
                                 joi1 = join;
                                 fprintf(stderr,
                                    "joi1 = %s\n",jname[join]);
                              }
      else if (buf[0] == '1') {
                                 ell1 = ellpsd;
                                 fprintf(stderr,
                                    "ell1 = %s\n",ename[ell1]);
                              }
      else if (buf[0] == '2') {
                                 ell2 = ellpsd;
                                 fprintf(stderr,
                                    "ell2 = %s\n",ename[ell2]);
                              }
      else if (buf[0] == '3') setref(ellpsd);
      else if (buf[0] == '4') {
                                 jnext[0] = cursor[0];
                                 jnext[1] = cursor[1];
                                 jnext[2] = cursor[2];
                              }
      else if (buf[0] == '5') figure = 5;
      else if (buf[0] == '6') figure = 6;
      else if (buf[0] == '8') figure = 8;
      else if (buf[0] == '9') figure = 9;

      else if (buf[0] == 'a') addel();
      else if (buf[0] == 'A') delel();
      else if (buf[0] == 'b') brighten(doub2);
      else if (buf[0] == 'B') brighten(inv2);
      else if (buf[0] == 'c') setcur();
      else if (buf[0] == 'C') {
                                 join = nearest(jnt,njts);
                                 setjnt(join);
                              }
      else if (buf[0] == 'd') shift(doub0,-dshift,doub0);
      else if (buf[0] == 'D') shift(doub0, dshift,doub0);
      else if (buf[0] == 'e') {
                                 fprintf(stderr,"SCENE\n");
                                 ellpsd = nearest(cen,nels);
                                 setels(-1,-1);
                                 jcursor = -1;
                                 doing = 0;
                              }
      else if (buf[0] == 'E') {
                                 ellpsd = nearest(cen,nels);
                                 fprintf(stderr, "ELLIPSOID %s\n",
                                    ename[ellpsd]);
                                 for (j = 0; j< 3; ++j)
                                    cursor[j] = cen[ellpsd][j];
                                 elist[0] =ellpsd;
                                 ecount = 1;
                                 jcount = 0;
                                 jcursor = -1;
                                 doing = 1;
                              }
      else if (buf[0] == 'f') {
                                 fprintf(stderr,"FIGURE\n");
                                 ellpsd = nearest(cen,nels);
                                 setels(ellpsd,-1);
                                 jcursor = -1;
                                 doing = 2;
                              }
      else if (buf[0] == 'F') {  if (joi1 < 1) joi1 = join;
                                 if (ell1 < 1) ell1 = ellpsd;
                                 fprintf(stderr,
                                    "LIMB including %s at %s\n",
                                    ename[ell1],jname[joi1]);
                                 setels(ell1,joi1);
                                 jcursor = -1;
                                 doing = 3;
                              }
      else if (buf[0] == 'g') {
                                 ellpsd = nearest(cen,nels);
                                 fprintf(stderr, "ELLIPSOID %s\n",
                                    ename[ellpsd]);
                                 for (j = 0; j< 3; ++j)
                                    cursor[j] = cen[ellpsd][j];
                                 elist[0] = ellpsd;
                                 ecount = 1;
                                 jcount = 0;
                                 jcursor = -1;
                                 doing = 1;
                              }
      else if (buf[0] == 'G') {
                                 join = nearest(jnt,njts);
                                 setjnt(join);
                              }
      else if (buf[0] == 'h') {
                                 dohelp();
                                 goto another;
                              }
      else if (buf[0] == 'H') setref(0);
      else if (buf[0] == 'i') {
                                 expand(doub2);
                                 goto another;
                              }
      else if (buf[0] == 'I') {
                                 expand(inv2);
                                 goto another;
                              }
      else if (buf[0] == 'j') doattach();
      else if (buf[0] == 'J') dodetach(join);
      else if (buf[0] == 'k') alterw(axfac);
      else if (buf[0] == 'K') alterw(doub1/axfac);
      else if (buf[0] == 'l') shift(-dshift,doub0,doub0);
      else if (buf[0] == 'L') shift( dshift,doub0,doub0);
      else if (buf[0] == 'm') edshow();
      else if (buf[0] == 'n') nexthigh(1);
      else if (buf[0] == 'N') nexthigh(-1);
      else if (buf[0] == 'o') thresh += (pmax-thresh)/2;
      else if (buf[0] == 'O') thresh -= (pmax-thresh)/2;
      else if (buf[0] == 'p') copy(FALSE);
      else if (buf[0] == 'P') copy(TRUE);
      else if (buf[0] == 'q') getout(0);
      else if (buf[0] == 'Q') dobackup();
      else if (buf[0] == 'r') {
                                 --debug;
                                 fprintf(stderr,"debug %d\n",debug);
                                 goto another;
                              }
      else if (buf[0] == 'R') {
                                 ++debug;
                                 fprintf(stderr,"debug %d\n",debug);
                                 goto another;
                              }
      else if (buf[0] == 's') store3(1);
      else if (buf[0] == 'S') {  read3();
                                 ellpsd = 1;
                                 setels(ellpsd,-1);
                              }
      else if (buf[0] == 't') doground();
      else if (buf[0] == 'u') dogrofig(axfac,doub1,doub1,
                               cursor[0],cursor[1],cursor[2]);
      else if (buf[0] == 'U') dogrofig(doub1/axfac,doub1,doub1,
                               cursor[0],cursor[1],cursor[2]);
      else if (buf[0] == 'v') dogrofig(doub1,axfac,doub1,
                               cursor[0],cursor[1],cursor[2]);
      else if (buf[0] == 'V') dogrofig(doub1,doub1/axfac,doub1,
                               cursor[0],cursor[1],cursor[2]);
      else if (buf[0] == 'w') dogrofig(doub1,doub1,axfac,
                               cursor[0],cursor[1],cursor[2]);
      else if (buf[0] == 'W') dogrofig(doub1,doub1,doub1/axfac,
                               cursor[0],cursor[1],cursor[2]);
      else if (buf[0] == 'x') dospinby(cursor,refell,dang,0);
      else if (buf[0] == 'X') dospinby(cursor,refell,-dang,0);
      else if (buf[0] == 'y') dospinby(cursor,refell,dang,1);
      else if (buf[0] == 'Y') dospinby(cursor,refell,-dang,1);
      else if (buf[0] == 'z') dospinby(cursor,refell,dang,2);
      else if (buf[0] == 'Z') dospinby(cursor,refell,-dang,2);
      else if (buf[0] == ';') dogrofig(
                                doub1/axfac,doub1/axfac,doub1/axfac,
                                cursor[0],cursor[1],cursor[2]);
      else if (buf[0] == ':') dogrofig(axfac,axfac,axfac,
                                cursor[0],cursor[1],cursor[2]);
      else if (buf[0] == '<') {   nsteps /= 2;
                                  if (nsteps < 1) nsteps = 1;
                                  dparam = twopi/nsteps;
                                  fprintf(stderr,
                                     "nsteps = %d\n",nsteps);
                              }
      else if (buf[0] == '>') {   nsteps *= 2;
                                  dparam = twopi/nsteps;
                                  fprintf(stderr,
                                     "nsteps = %d\n",nsteps);
                              }
      else 
      {
         fprintf(stderr,"oops\n");
         goto another;
      }
      printstuff();
   }
   if (debug <= 0) fprintf(stderr,"checkeysb %d %d %c\n",
      rolling,FALSE,buf[0]);
} /* checkeys */
/*******************************************/

int nearest(a,nocc)
int nocc;
double a[EMAX][3];
/*
   find nearest of 'nocc' members of array 'a' to cursor
   (in x and y only)

   called by checkeys
*/
{
   int j;
   int n;
   double d;
   double dmin;

   dmin = doubmax;
   for (j = 0; j < nocc; ++j)
   {
      d = sqr(cursor[0]-a[j][0])+sqr(cursor[1]-a[j][1]);
      if (d < dmin)
      {
         n = j;
         dmin = d;
      }
   }
   return(n);
} /* nearest */
/*********************************************/

alterw(fac)
double fac;
/*
   change size of window

   called by checkeys, dorestore.
*/
{
   width *= fac;
   height *= fac;
   thewidth = zoom*width;
   theheight = zoom*height;
   fprintf(stderr,"width %d\n",width);
   XDestroyWindow(thedisplay,thewindow);
   thewindow = XCreateWindow(thedisplay,rootwindow,
		   thex,they,thewidth,theheight,borderwidth,
                   thedepth,InputOutput,vlist[0].visual,
                   thewindowmask, &thewindowattributes);
   XStoreName(thedisplay,thewindow,"edellj");
   XMapRaised(thedisplay,thewindow);
   XSetNormalHints(thedisplay,thewindow,&thesizehints);
   XSelectInput(thedisplay,thewindow,evmask);
   thegc = XCreateGC(thedisplay,thewindow,
             GCForeground | GCBackground , &thegcvalues);
   if ( thegc == 0 )
      sprintf(err,"'alterw' : cannot create gc");
} /* alterw */
/*******************************************/

printstuff()
/*
   print information about current ellipsoid or joint

   called by setkeys
   calls mkang
*/
{
   if (doing == 1)
   {
      fprintf(stderr,"ellpsd %s\n",ename[ellpsd]);
      fprintf(stderr,"axes   %f %f %f\n",
                 ax3[ellpsd][0],ax3[ellpsd][1],ax3[ellpsd][2]);
      fprintf(stderr,"centre %f %f %f\n",
                 cen[ellpsd][0],cen[ellpsd][1],cen[ellpsd][2]);
      mkang(ellpsd);
      fprintf(stderr,"angles %f %f %f\n",
                 rad*ang[0],rad*ang[1],rad*ang[2]);
   }
   else if (doing == 4)
   {
      fprintf(stderr,"cursor %f %f %f\n",
         cursor[0],cursor[1],cursor[2]);
   }
   else if (doing == 5)
   {
      fprintf(stderr,"joint %s %f %f %f\n",
         jname[join],jnt[join][0],jnt[join][1],jnt[join][2]);
   }
   else
   {
      fprintf(stderr,"working on %d ellipsoid",ecount);
      if (ecount != 1) fprintf(stderr,"s,   ");
         else fprintf(stderr,",   ");
      fprintf(stderr,"and %d joint",jcount);
      if (jcount != 1) fprintf(stderr,"s\n");
         else fprintf(stderr,"\n");
   }
} /* printstuff */
/*******************************************/

setjnt(j)
int j;
/*
   set cursor to 'j'th joint

   called by checkeys
*/
{
   int k;

   if (njts > 0)
   {
      ellpsd = -1;
      ecount = 0;
      jcount = 1;
      jlist[0] = j;
      doing = 5;
      join = j;
      jcursor = j;
      for (k = 0; k < 3; ++k)
      {
         cursor[k] = jnt[j][k];
      }
      fprintf(stderr,"JOINT %s\n",jname[join]);
   }
   else
      fprintf(stderr,"no joints yet\n");
} /* setjnt */
/*******************************************/

setref(n)
int n;
/*
   set ellipsoid 'n' as reference

   called by checkeys.
*/
{
   refell = n;
   fprintf(stderr,"reference %s\n",ename[n]);
} /* setref */
/*******************************************/

setcur()
/*
   set free cursor up

   called by checkeys.
*/
{
   doing = 4;
   join = -1;
   jcursor = 0;
   ecount = 0;
   jcount = 0;
   fprintf(stderr,"FREE CURSOR\n");
} /* setcur */
/*******************************************/

dohelp()
/*
   print help information

   called by main, checkeys.
*/
{
   fprintf(stderr," Interactive commands -\n");
   fprintf(stderr,"(Capitals for inverse functions)\n");
   fprintf(stderr,"0 - store a joint\n");
   fprintf(stderr,"1 - make ellpsd #1\n");
   fprintf(stderr,"2 - make ellpsd #2\n");
   fprintf(stderr,"3 - make ellpsd the reference\n");
   fprintf(stderr,"4 - store potential joint position\n");
   fprintf(stderr,"5 - draw wireframes\n");
   fprintf(stderr,"6 - remove hidden arcs\n");
   fprintf(stderr,"8 - use Floyd-Steinberg dithering\n");
   fprintf(stderr,"9 - use random dithering\n");
   fprintf(stderr,"\n");
   fprintf(stderr,"a - create/delete another ellipsoid\n");
   fprintf(stderr,"b - make brighter/darker\n");
   fprintf(stderr,"c - set free cursor/put on joint\n");
   fprintf(stderr,"d - shift down/up\n");
   fprintf(stderr,"e - apply to whole scene/just one\n");
   fprintf(stderr,"f - apply to current figure/limb\n");
   fprintf(stderr,"g - apply to an ellipsoid/joint\n");
   fprintf(stderr,
      "h - list interactive commands / set ref to world\n");
   fprintf(stderr,"i - double/halve increments\n");
   fprintf(stderr,"j - join/detach\n");
   fprintf(stderr,"k - expand/contract window\n");
   fprintf(stderr,"l - shift left/right\n");
   fprintf(stderr,"m - animate scene\n");
   fprintf(stderr,"n - next/previous ellipsoid or joint\n");
   fprintf(stderr,"o - increase/decrease threshold\n");
   fprintf(stderr,"p - copy/reflect set of ellipsoids\n");
   fprintf(stderr,"q - exit/restore\n");
   fprintf(stderr,"r - decrement/increment debug\n");
   fprintf(stderr,"s - store/read \n");
   fprintf(stderr,"u - enlarge/shrink x semiaxis\n");
   fprintf(stderr,"v - enlarge/shrink y semiaxis\n");
   fprintf(stderr,"w - enlarge/shrink z semiaxis\n");
   fprintf(stderr,"x - rotate about x axis\n");
   fprintf(stderr,"y - rotate about y axis\n");
   fprintf(stderr,"z - rotate about z axis\n");
   fprintf(stderr,";:- shrink/expand everything in list\n");
   fprintf(stderr,"<>- halve/double number of chords\n");
} /* dohelp */
/***************************************************/

copy(reflect)
int reflect;
/*
   copy a set of ellipsoids and joints
   maybe with reflection

   called by checkeys
*/
{
   int c,e,j,k;

   for (c = 0; c < ecount; ++c)
   {
      e = elist[c];
      for (k = 0; k < 3; ++k)
      {
         ax3[nels][k] = ax3[e][k];
         cen[nels][k] = cen[e][k];
         quat[nels][k] = quat[e][k];
      }
      quat[nels][3] = quat[e][3];
      quat[nels][4] = quat[e][4];
      if (reflect == TRUE)
      {
         cen[nels][0] = doub1000-cen[nels][0];
         quat[nels][3] = -quat[e][3];
      }
         else cen[nels][0] += dshift;
      ++nels;
      if (nels >= EMAX)
      {
         fprintf(stderr,"ERROR - more ellipsoids than %d\n",EMAX);
         goto rtrn;
      }
   }
   for (c = 0; c < jcount; ++c)
   {
      j = jlist[c];
      for (k = 0; k < 2; ++k)
      {
         coel[njts][k] = coel[j][k];
         jnt[njts][k] = jnt[j][k];
      }
      jnt[njts][2] = jnt[j][2];
      if (reflect == TRUE) jnt[njts][0] = doub1000-jnt[njts][0];
         else jnt[njts][0] += dshift;
      ++njts;
      if (njts >= EMAX)
      {
         fprintf(stderr,"ERROR - more joints than %d\n",EMAX);
         goto rtrn;
      }
   }
rtrn:;
} /* copy */
/***************************************************/

expand(fac)
double fac;
/*
   change increments

   called by checkeys
*/
{
   dang *= fac;
   dshift *= fac;
   axfac *= fac;
   fprintf(stderr,"dang %f, dshift %f, axfac %f\n",
      dang*rad,dshift,axfac);
} /* expand */
/*******************************************/

nexthigh(dn)
int dn;
/*
   highlight next ellipsoid/joint

   called by checkeys
   calls     setref, setjnt.
*/
{
   int j;

   if (debug <= 0)
      fprintf(stderr,"nexthigha %d %d %d\n",ellpsd,jcursor,dn);
   if (ellpsd >= 0)
   {
      ellpsd += dn;
      if (ellpsd >= nels) ellpsd = 1;
      if (ellpsd < 1) ellpsd = nels-1;
      for (j = 0; j < 3; ++j)
         cursor[j] = cen[ellpsd][j];
   }
   if (jcursor >= 0)
   {
      jcursor += dn;
      if (jcursor >= njts) jcursor = 0;
      if (jcursor < 0) jcursor = njts-1;
      setjnt(jcursor);
   }
   if (debug <= 0)
      fprintf(stderr,"nexthighb %d %d\n",ellpsd,jcursor);
} /* nexthigh */
/*******************************************/

getout(v)
int v;
/*
   print error message or exit gracefully

   called by  getpar, checkeys, startwindows,
*/
{
   int j;

   if (v != 0) fprintf(stderr,"edellj: %s\n",err);
   if (disopen == TRUE)
   {
      XDestroyWindow(thedisplay,thewindow);
      XCloseDisplay(thedisplay);
   }
   exit(v);
} /* getout */
/*******************************************/

convert()
/*
    convert vectors to raster

    called by main.
*/
{
   double xlo,xhi,ylo,yhi;
   double xold[VMAX],xnew[VMAX];

   int count;
   int ixmin,ixmax;
   int j,k;
   int nactive;
   int x,y;

   if (debug <= 0) fprintf(stderr,"converta %d\n",nvecs);
   count =0;
   p = 0;
/*
   find intersections of vectors with top scan line -
*/
      yhi = height+1;
      for ( j = 0; j < nvecs; ++j)
         if ( hori[j] == TRUE )
            xnew[j] = x1[j];
         else
            xnew[j] = x1[j] + (yhi-y1[j])*dxdy[j];
/*
   find intersections of vectors with rest of scan lines -
*/
      for ( y = height; y > 0; --y)
      {
         ylo = y; yhi = y+1;
         k = 0;
         ixmin = width; ixmax = 0;
         for (j = 0; j < nvecs; ++j)
         {
            if ( hori[j] == TRUE )
            {
               xold[j] = x1[j];
               xnew[j] = x2[j];
            }
            else
            {
               xold[j] = xnew[j];
               xnew[j] = x2[j] - (y2[j]-ylo)*dxdy[j];
            }
            if (debug < 0)
                  fprintf(stderr,"convertb %d %d %9g %9g\n",
                     y,j,xold[j],xnew[j]);
            if (( yhi > y1[j]) && (ylo <= y2[j]))
            {
               xlo = xold[j];
               xhi = xnew[j];
               if (xlo > xhi)
               {
                  xlo = xnew[j];
                  xhi = xold[j];
               }
               if ((xlo < x1[j] ) && (x1[j] < x2[j])) xlo = x1[j];
               if ((xlo < x2[j] ) && (x2[j] < x1[j])) xlo = x2[j];
               if ((xhi > x1[j] ) && (x1[j] > x2[j])) xhi = x1[j];
               if ((xhi > x2[j] ) && (x2[j] > x1[j])) xhi = x2[j];
               xloi[k] = xlo-doub1;
               xhii[k] = xhi;
               if (xloi[k] < ixmin) ixmin = xloi[k];
               if (xhii[k] > ixmax) ixmax = xhii[k];
               if (debug < 0)
                  fprintf(stderr,"convertc %d %d %d %d %9g %9g\n",
                     k,j,ixmin,ixmax,x1[j],x2[j]);
               ++k;
            }
         }
         nactive = k;
         ixmin = ixmin-1;
         if (debug < 0)
             fprintf(stderr,"convertd %d %d\n",y,nactive);
/*
     run across scan line -
*/
         for (x = 0; x < width; ++ x)
         {
            bit = 'z';
            if ((x > ixmin) && (x < ixmax))
            {
               for ( k=0; ( (k < nactive) && (bit == 'z') ); ++k)
               {
                   if (( x < xhii[k]) && ( x >= xloi[k]) )
                   {
                      ++ count;
                      bit= '0';
                      if (debug < 0)
                        fprintf(stderr,"converte %d %d %d %d %d\n",
                           y,x,k,xloi[k],xhii[k]);
                   }
               }
            }
            if (debug < 0)
                fprintf(stderr,"convertf %d %d %d\n",
                  x,y,bit);
            piccy[x][y] = bit;
         }    /* end of x loop */
      } /* end of y loop */
      if (debug <= 0)
          fprintf(stderr,"convertg %d\n",count);
} /* convert */
/************************************/

drawcur()
/*
   draw the cursor

   called by main
*/
{
   if (debug <= 0) fprintf(stderr,"drawcur %9g %9g %9g\n",
      cursor[0],cursor[1],cursor[2]);
   moveto(cursor[0],cursor[1]+doub50);
   lineto(cursor[0],cursor[1]-doub50);
   moveto(cursor[0]+doub50,cursor[1]);
   lineto(cursor[0]-doub50,cursor[1]);
} /* drawcur */
/**********************************/

plotel(n)
int n;
/*
   plots an ellipse as a set of vector chords

   called by dopic.
   calls     setell, proces.
*/
{
   if ( debug < 1 )
       fprintf(stderr,"plotelb %d %9g\n",n,phi2[n]);
   setell(n);
   proces(n);
} /* plotel */
/**********************************************/

shrink(n)
int n;
/*
    set up stuff for shrunken ellipse 'n'

    called by dopic
    calls     sqr, proces.
*/
{
   int       j,k;
   double    phi,sphi,cphi;
   double    axx,axy;
   double    dzoom;

   if (debug <= 0)
       fprintf(stderr,"shrinka %d %9g %9g %9g %9g %9g %d\n",
          n,cen[n][0],cen[n][1],ax2[n][0],ax2[n][1],
          phi2[n],narcs[n]);
   dzoom = (double)zoom;
   xcen = cen[n][0];
   ycen = cen[n][1];
   axx = ax2[n][0]-doub1/(dzoom*wtos);
   axy = ax2[n][1]-doub1/(dzoom*wtos);
   phi = phi2[n];
   cphi = cos(phi); sphi = sin(phi);
   p = sqrt(sqr(axx*cphi)+sqr(axy*sphi));
   q = sqrt(sqr(axx*sphi)+sqr(axy*cphi));
   alfa = atan2(axy*sphi,axx*cphi);
   beta = atan2(axx*sphi,axy*cphi);
   proces(ellpsd);
   if (debug <= 0)
   {
      fprintf(stderr,"shrinkb %9g %9g %9g %9g %9g %9g %9g %9g %9g\n",
              xcen,ycen,axx,axy,phi,p,q,alfa,beta);
      for (k = 0; k < narcs[n]; ++k)
      fprintf(stderr,"    %d %9g %9g\n",
         k,appear[n][k][0],appear[n][k][1]);
   }
}   /* shrink  */
/**********************************************/

lineto(x,y)
double x,y;
/*
    called by dopart
*/
{
    int ix1,ix2,iy1,iy2;

    ix1 = zoom*wtos*x1[nvecs];
    iy1 = zoom*(height-wtos*y1[nvecs]);
    ix2 = zoom*wtos*x;
    iy2 = zoom*(height-wtos*y);
    x1[nvecs] = x;
    y1[nvecs] = y;
    ++ nvecs;
    XDrawLine(thedisplay,thewindow,thegc,
                       ix1,iy1,ix2,iy2);
    if (debug < 0) fprintf(stderr,"lineto %d %d %d %d\n",
                       ix1,iy1,ix2,iy2);
} /* lineto */
/**********************************************/
 
moveto(x,y)
double x,y;
/*
    called by dopart
*/
{
    x1[nvecs] = x;
    y1[nvecs] = y;
} /* moveto */
/**********************************************/
 
setell(n)
int n;
/*
    set up stuff for ellipse 'n'

    called by plotel
    calls  sqr.
*/
{
   int       j,k,m;
   int       nn;
   double    axx,axy;
   double    a0[AMAX],a1[AMAX];
   double    tol;
   double    phi,sphi,cphi;

   if ( debug  <= 0)
   {
       fprintf(stderr,"setella %d %9g %9g %9g %9g %9g %d\n",
          n,cen[n][0],cen[n][1],ax2[n][0],
          ax2[n][1],phi2[n],narcs[n]);
      for (k = 0; k < narcs[n]; ++k)
         fprintf(stderr,"    %d %9g %9g\n",
              k,appear[n][k][0],appear[n][k][1]);
   }
   xcen = cen[n][0];
   ycen = cen[n][1];
   axx = ax2[n][0];
   axy = ax2[n][1];
   phi = phi2[n];
   cphi = cos(phi); sphi = sin(phi);
   p = sqrt(sqr(axx*cphi)+sqr(axy*sphi));
   q = sqrt(sqr(axx*sphi)+sqr(axy*cphi));
   alfa = piby2+atan2(axy*sphi,axx*cphi);
   beta = piby2+atan2(axx*sphi,axy*cphi);
   nn = narcs[n];
   k = 2;
   a0[0] = doub0;
   a1[0] = doub0;
   a0[1] = twopi;
   a1[1] = twopi;
   for (j = 0; j < nn; ++j)
   {
      a0[k] = doub2*(atan(appear[n][j][0])-piby4);
      a1[k] = doub2*(atan(appear[n][j][1])-piby4);
      if (a0[k] < doub0) a0[k] += twopi;
      if (a1[k] < doub0) a1[k] += twopi;
      if (a0[k] > twopi) a0[k] -= twopi;
      if (a1[k] > twopi) a1[k] -= twopi;
      if (a0[k] > a1[k])
      {
         a0[k+1] = doub0;
         a1[k+1] = a1[k];
         a1[k] = twopi;
         ++k;
      }
      ++k;
      a0[k] = twopi+twopi;
      a1[k] = twopi+twopi;
   }
   nn = k;
   if ( debug  <= 0)
   {
      fprintf(stderr,"setellb %d %d\n",n,nn);
      for (k = 0; k < nn; ++k)
         fprintf(stderr,"    %d %9g %9g\n",
              k,a0[k],a1[k]);
   }
   sort(a0,a1,nn);
   if ( debug  <= 0)
   {
      fprintf(stderr,"setellc %d %d\n",n,nn);
      for (k = 0; k < nn; ++k)
         fprintf(stderr,"    %d %9g %9g\n",
              k,a0[k],a1[k]);
   }
   xcen = cen[n][0];
   tol = 0.001;
   k = 0;
   for (j = 0; j < nn; ++j)
   {
      appear[n][k][0] = a0[j];
      for (m = j+1; m < nn; ++m)
        if ((a0[m]-a1[j]) < tol) ++j;
      appear[n][k][1] = a1[j];
      if ( (appear[n][k][1] - appear[n][k][0]) > tol) ++ k;
   }
   narcs[n] = k;
   if (debug  <= 0)
   {
      fprintf(stderr,
          "setelld %9g %9g %9g %9g %9g %9g %9g\n",
              xcen,ycen,axx,axy,phi,p,q,alfa,beta);
      for (k = 0; k < narcs[n]; ++k)
         fprintf(stderr,"    %d %9g %9g\n",
              k,appear[n][k][0],appear[n][k][1]);
   }
}   /* setell  */
/****************************************/

proces(n)
int n;
/*
    routine to run a parameter from a min to a max value doing a
    process in steps whilst avoiding a series of ranges of
    parameter values for ellipse 'n'.
 
    formal parameters-
      appear[n][j][] - start  and  end of "j"th invisible arc
                       of "n"th ellipse.
      minth,maxth - min and and  max values of parameter to be run.
      narcs[n] - number of ranges of parameters to be avoided.
      dparam - step size of parameter.
      debug - zero || negative for diagnostics to be printed.
 
   variables-
      jarc - counter thru ranges in array 'appear'.
      param - current value of parameter being considered.
 
       called by plotel, shrink.
       calls   dopart
 
*/
{
     int       jarc;
     double    param;
     double    minth,maxth;

       minth = doub0;
       maxth = twopi;
       if ( debug < 0)
          fprintf(stderr,"procesa  %s %d %9g %9g %9g\n",
             ename[n],narcs[n],minth,maxth,dparam);
/*
   skip to first point-
*/
       xold = xcen; yold = ycen;
       beam = FALSE;
       jarc = 0;
       param = minth;
       if (narcs[n] > 0)
       {
          while (appear[n][jarc][0] <= minth)
          {
             param = appear[n][jarc][1];
             jarc = jarc+1;
             if ( debug < 0 )
                fprintf(stderr,"procesb %d %9g %9g %9g\n",
                    jarc,param,
                       appear[n][jarc][0],appear[n][jarc][1]);
          }
       }
       dopart(n,param);
/*
   start stepping the parameter -
*/
       while (param < maxth)
       {
             param = param+dparam;
             if ( debug < 0 )
                fprintf(stderr,"procesc %d %9g %9g %9g\n",
                    jarc,param,
                       appear[n][jarc][0],appear[n][jarc][1]);
             if ( param > maxth) param = maxth;
             if ((narcs[n] > 0) && (jarc > narcs[n]))
             {
                param = maxth;
                dopart(n,param);
             }
             else
             if ((narcs[n] > 0) && (param > appear[n][jarc][0]))
/*
    we have a cut chord, so draw to its start, skip to its end -
*/
             {
                   param = appear[n][jarc][0];
                   dopart(n,param);
                   beam = FALSE;
                   param = appear[n][jarc][1];
                   dopart(n,param);
                   jarc = jarc+1;
             }
             else /* a normal unbroken step- */
                   dopart(n,param);
             if (nsteps < 3) param += maxth;
       } /* param loop */
}   /* proces */
/**************************************/

dopart(n,param)
int n;
double param;
/*
    draw cut chord for ellipse "n" up to the point
    specified by "param".

    called by proces
    calls  moveto, lineto
*/
{
    double      a,b;
    double      xnew,ynew;
    double      xa,ya,xb,yb;

    if ( debug < 0)
       fprintf(stderr,
          "doparta %d %9g %d %9g %9g %9g %9g %9g %9g\n",
             n,param,debug,p,q,xcen,ycen,alfa,beta);
    a = alfa+param;  b = beta+param;
    if (b > twopi) b -= twopi; /* step around cc sin() bug */
    xnew = p*cos(a)+xcen;
    ynew = q*sin(b)+ycen;
    if ( beam == TRUE)
    {
       xa = xold; ya = yold;
       xb = xnew; yb = ynew;
       if ((xa < doub0) && (xb < doub0)) goto none;
       if ((ya < doub0) && (yb < doub0)) goto none;
       if ((xa > doub1000) && (xb > doub1000)) goto none;
       if ((ya > doub1000) && (yb > doub1000)) goto none;
       {
          moveto( xa,ya);
          lineto( xb,yb);
       }
    }
none:
    if ( debug < 0 )
        fprintf(stderr,"dopartb %d %d %9g %9g %9g %9g %9g\n",
             beam,TRUE,param,xold,yold,xnew,ynew);
    beam = TRUE;
    xold = xnew; yold = ynew;
}  /*  dopart  */
/****************************************/

double sqr(x)
double x;
/*
   square a value

   called by setell.
*/
{
   return(x*x);
} /* sqr */
/********************************************/

mkquat(n,a0,a1,a2)
   int n ;
   double a0,a1,a2 ;
/* 
     convert angles a0,a1,a2 into quat entries 
     for ellipsoid 'n'.

     called by setdata 
*/
{
   double s0,c0,s1,c1,s2,c2 ;

   if (debug < 0)
      fprintf(stderr,"mkquat  %d %9g %9g %9g\n", n,a0,a1,a2);
   s0 = sin(a0) ;
   c0 = cos(a0) ;
   s1 = sin(a1) ;
   c1 = cos(a1) ;
   s2 = sin(a2) ;
   c2 = cos(a2) ;
   quat[n][0] = c0*c1 ;
   quat[n][1] = s0*c1 ;
   quat[n][2] = s1 ;
   quat[n][3] = s2 ;
   quat[n][4] = c2 ;
} /*mkquat */
/**********************************************/

visel()
/* 
     this calculates the outline of each ellipsoid in turn. 
     each is approximated by a series of chords, 
     plotted with respect to Cohen's parameter. 

     called by dopic 
     calls     setnup
*/
{
   int n;

   if (debug <= 0) fprintf(stderr,"visela %d %d\n",nels,narcs[1]);
/* 
     run thru ellipsoids to draw each in turn  
     except the zeroth one -
*/
   for (  n = 1 ; n < nels ; ++ n )
   {
      setnup(n);
      if (debug < 1)
         fprintf(stderr,
            "viselb %d %9g %9g %9g %d\n",
                n,axxn,axyn,phi2[n],narcs[n]);
   }
} /* end visel */
/******************************************/

dospinby(x,refell,angl,axis)
      int refell,axis ;
      double angl ;
      double x[3];
/*
   moves cursor to 'x', then
   spins all ellipsoids and joints in 'elist' and 'jlist'
   about a point 'x', by an angle 'angl' radians relative to
   an 'axis' of reference ellipsoid 'refell'.

   called by   dobalanc, action, dobend, swing.
   calls  rset, rotget, matmul, twirl.
*/
{
      int j,k;
      double r[3][3],ro[3][3],unro[3][3] ;
/*
        do transformation on required coordinates
        aligned with axes of the reference ellipsoid-
*/
      if (debug <= 0)
      {
         k = elist[0];
         fprintf(stderr,
           "dospinbya %3d %3d %9g %3d %3d\n   %9g %9g %9g %9g %9g\n",
           k,refell,angl,axis,ecount,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      rset(r,angl,axis) ;
      if (debug <= 0)
      {
         k = elist[0];
         fprintf(stderr,
           "dospinbyb %3d %9g %3d %3d\n   %9g %9g %9g %9g %9g\n",
           refell,angl,axis,k,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      rotget(ro,unro,refell) ;
      if (debug <= 0)
      {
         k = elist[0];
         fprintf(stderr,
           "dospinbyc %3d %9g %3d %3d %9g %9g %9g %9g %9g\n",
           refell,angl,axis,k,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      matmul(r,unro,r) ;
      matmul(ro,r,r) ;
      for (j = 0; j < 3; ++j)
         for (k = 0; k < 3; ++k)
            if ((r[j][k] > -tolr) && (r[j][k] < tolr)) r[j][k] = 0;
      twirl(x[0],x[1],x[2],r) ;
      if (debug <= 0)
      {
         k = elist[0];
         fprintf(stderr,
           "dospinbyd %3d %9g %3d %3d\n   %9g %9g %9g %9g %9g\n",
           refell,angl,axis,k,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
}  /* dospinby */
/**********************************************************/

twirl(x,y,z,r)
      double x,y,z ;
      double r[3][3] ;
/*
   rotates all the rotation matrices 'quat', centres 'cen',
   and joint vectors 'jnt', of ellipsoids and joints in lists
   'elist' and 'jlist' about a point 'x,y,z' using rotation
   matrix 'r'.

   called by  dospinby.
   calls  shift, matrot, vecmul.
*/

{
      double ra[3][3],rb[3][3];
      int high;
      int i,k ;

      if (debug <= -1) fprintf(stderr,"twirla %3d %3d\n",
         ecount,jcount);
      high = ellpsd;
      ellpsd = 1;
      shift(-x,-y,-z) ;
      if (debug <= -1)
      {
         fprintf(stderr,"twirlb\n");
         for (i = 0; i < 3; ++i)
            fprintf(stderr,"   %9g %9g %9g\n",
               r[0][i],r[1][i],r[2][i]);
      }
/*
     rotate the ellipsoids and their centres-
*/
      for (  i = 0 ; i < ecount ; ++ i )
      {
         k = elist[i];
/*  don't rotate world ! :- */
         if (k != 0)
         {
            if (debug <= -1)
               fprintf(stderr,"twirld %3d %3d %9g %9g %9g\n",
               i,k,cen[k][0],cen[k][1],cen[k][2]);
            matrot(r,k) ;
            vecmul(cen,r,k) ;
            if (debug <= -1)
               fprintf(stderr,"twirle %3d %3d %9g %9g %9g\n",
               i,k,cen[k][0],cen[k][1],cen[k][2]);
         }
      }
/*
   now for the joints-
*/
      for (  i = 0 ; i < jcount ; ++ i )
      {
         k = jlist[i];
         vecmul(jnt,r,k) ;
         if (debug <= -1)
            fprintf(stderr,"twirlf %3d %3d %9g %9g %9g\n",
            i,k,jnt[k][0],jnt[k][1],jnt[k][2]);
      }

/*   put body part back where it came from- */

lab4: shift(x,y,z) ;
      ellpsd = high;
}  /* twirl */
/*****************************/

matrot(r,n)
      int n ;
      double r[3][3] ;
/*
     rotates the 'n'th ellipsoid by rotation matrix 'r'.

     called by twirl
     calls  rotget, matmul, rotput.
*/
{
      double ro[3][3],unro[3][3] ;

      if (debug <= 0)
            fprintf(stderr,"matrota    %3d %9g %9g %9g %9g %9g\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      rotget(ro,unro,n) ;
      if (debug < 0)
            fprintf(stderr,"matrotb    %3d %9g %9g %9g %9g %9g\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      matmul(r,ro,ro) ;
      rotput(ro,n) ;
      if (debug < 0)
            fprintf(stderr,"matrotc    %3d %9g %9g %9g %9g %9g\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
}  /* matrot */
/**********************************************/

vecmul(v,m,n)
      int n ;
      double m[3][3] ;
      double v[EMAX][3] ;
/*
   multiply the 'n'th vector from array 'v'
   by matrix 'm'.

   called by  domoveby, doabut, twirl.
*/
{
      int i,j ;
      double vv[3],x ;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         x = doub0 ;
         for (  j = 0 ; j < 3 ; ++ j )
         {
            x = x+m[i][j]*v[n][j] ;
         }
         vv[i] = x ;
      }
      
      for (  i = 0 ; i < 3 ; ++ i )
      {
         v[n][i] = vv[i] ;
      }
}  /* vecmul */
/**********************************************/

vecmat(v,m,w)
      double m[3][3] ;
      double v[3],w[3];
/*
   multiply vector 'v' by matrix 'm',
   putting result in 'w'.

   called by  sepn, dobalanc.
*/
{
      int i,j ;
      double vv[3],x ;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         x = doub0 ;
         for (  j = 0 ; j < 3 ; ++ j )
         {
            x = x+m[i][j]*v[j] ;
         }
         vv[i] = x ;
      }
      for (  i = 0 ; i < 3 ; ++ i )
      {
         w[i] = vv[i] ;
      }
}  /* vecmat */
/**********************************************************/

shift(x,y,z)
      double x,y,z ;
/*
   this adds 'x,y,z' to the cursor or to all centres
   and joints in lists 'elist' and 'jlist'.

   called by checkeys, twirl.
*/
{
   int j,n ;
      
   if (debug <= 0)
         fprintf(stderr,"shifta %d %d %d %9g %9g %9g\n",
            ellpsd,ecount,jcount,x,y,z);
   cursor[0] += x;
   cursor[1] += y;
   cursor[2] += z;
   for (  n = 0 ; n < ecount ; ++ n )
   {
      j = elist[n] ;
      cen[j][0] = cen[j][0]+x ;
      cen[j][1] = cen[j][1]+y ;
      cen[j][2] = cen[j][2]+z ;
   }
   for (  n = 0 ; n < jcount ; ++ n )
   {
      j = jlist[n] ;
      jnt[j][0] = jnt[j][0]+x ;
      jnt[j][1] = jnt[j][1]+y ;
      jnt[j][2] = jnt[j][2]+z ;
   }
}  /* shift */
/*****************************/

rset(r,angl,axis)
      int axis ;
      double angl,r[3][3] ;
/*
   set up the rotation matrix 'r' for a rotation of
   'angl' radians about 'axis'.

   called by  dospinby.
*/
{
      double v[5] ;
      int i,j,k;

      if (debug <= 0) fprintf(stderr,"rset %3d %9g\n",axis,angl);
      v[0] = doub0 ;
      v[1] = doub1 ;

/*   fill out values vector with sin and cos- */

      v[2] = cos(angl) ;
      v[3] = sin(angl) ;
      v[4] = -v[3] ;

/*   choose appropriate permutation of values for rotation axis- */

      for (  i = 0 ; i < 3 ; ++ i )
      {
         for (  j = 0 ; j < 3 ; ++ j )
         {
            k = perm[axis][j][i] ;
            r[i][j] = v[k-1] ;
         }
      }
}  /* rset */
/************************************/

doground()
/*
   find distance of lowest point above the ground
   of the ellipsoids contained in elist.

   called by  checkeys
   calls      rotget, getout.
*/
{
   int i,n ;
   double toty,x,y,z,r[3][3],unr[3][3] ;
   double val;
   double rr[3][3],tmp[3][3];
   double r1[3][3],r2[3][3],r3[3][3] ;

 
   if (debug <= 0)
      fprintf(stderr,"dogrounda %3d %3d\n",ecount,jcount);
   val = cen[elist[0]][1];

/*   run through affected ellipsoids finding lowest point- */

   if (ecount < 1)
      fprintf(stderr,"doground ecount = %d",ecount);
   else
   {
      for (  n = 0 ; n < ecount ; ++ n )
      {
         i = elist[n] ;
         rotget(r,unr,i) ;
         x = r[0][1]*ax3[i][0] ;
         y = r[1][1]*ax3[i][1] ;
         z = r[2][1]*ax3[i][2] ;
         toty = cen[i][1]-sqrt(x*x+y*y+z*z) ;
         if (toty < val) val = toty ;
         if (debug <= 0)
            fprintf(stderr,
               "dogroundb %3d %9g %9g %9g %9g %9g %9g %9g %9g\n",
               i,ax3[i][0],ax3[i][1],ax3[i][2],x,y,z,cen[i][1],toty);
      }
      for (  n = 0 ; n < ecount ; ++ n )
      {
         i = elist[n] ;
         cen[i][1] -= val;
      }
   }
}  /* doground */
/**********************************************************/

setels(ellpsd,jthis)
      int ellpsd,jthis;
/*
     puts into 'elist' and 'jlist' those ellipsoids and joints
     (if any) connected to 'ellpsd'
     (including 'ellpsd' and 'jthis')
     except those connected through joint 'jthis'

     if 'jthis' is negative, puts all joints and ellipsoids
     connected to 'ellpsd' into lists.
     if 'ellpsd' is zero, puts all joints and ellipsoids into lists,
     except ellipsoid zero (world).

     'ecount' is the number of ellipsoids in the list 'elist'.
     'jcount' is the number of joints in the list 'jlist'.

     called by  setper, findfg, dodetach, dogrojnt, dodrag.
*/
{
      int all;
      int e,j,i,jt ;

      if (debug <= 0)
         fprintf(stderr,"setelsa %3d %3d\n",ellpsd,jthis);
      if (ellpsd <= 0) goto lab6 ;

      all = -1;
      ecount = 1 ;
      elist[0] = ellpsd ;
      if (jthis < 0)
      {
         for (j = 0; j < njts; ++j)
         {
            if (coel[j][0] == ellpsd)
            {
               jthis = j;
               all = 1;
            }
            if (coel[j][1] == ellpsd)
            {
               jthis = j;
               all = 0;
            }
         }
      }
      jcount = 0 ;

      if ((njts <= 0)||(jthis < 0)) goto rtrn ;
      if ((coel[jthis][0] != ellpsd) && (coel[jthis][1] != ellpsd))
      {
          fprintf(stderr,
             "oops: joint %s joined to %s and %s, not %s\n",
             jname[joi1],ename[coel[joi1][0]],ename[coel[joi1][1]],
             ename[ellpsd]);
          goto rtrn;
      }
      jcount = 1 ;
      jlist[0] = jthis ;

again:  for (  e = 0 ; e < ecount ; ++ e )
      {

/*   seek joint not in jlist but connected to ellipsoid elist[e]- */

         for (  jt = 0 ; jt < njts ; ++ jt )
         {
            if (jcount > 0)
            {
               for (  j = 0 ; j < jcount ; ++ j )
               {
                  if (jt == jlist[j]) goto lab3 ;
               }
            }
/*
   jt not in list yet-
*/
            i =  -1 ;
            if (coel[jt][0] == elist[e]) i = 1 ;
            if (coel[jt][1] == elist[e]) i = 0 ;
            if (debug < 0)
               fprintf(stderr,"setelsb %3d %3d %3d %3d %3d %3d %3d\n",
                  e,jt,i,ecount,jcount,coel[jt][0],coel[jt][1]);
            if (i < 0) goto lab3 ;

/*   store new joint and ellipsoid- */

            jlist[jcount] = jt ;
            jcount ++;
            elist[ecount] = coel[jt][i] ;
            ecount ++;
lab3: ;
         }
         if (e >= ecount-1)
         {
            if (all < 0) goto rtrn;
            else
            {
               ellpsd = coel[jthis][all];
               elist[ecount] = ellpsd;
               ecount ++;
               all = -1;
               goto again;
            }
         }
     }

/*   set all ellipsoids and joints- */

lab6: jcount = 0 ;

/*   all joints with non-null connections- */

      jcount = 0;
      for (  j = 0 ; j < njts ; ++ j )
      {
         if (coel[j][0] >= 0)
         {
            ++ jcount;
            jlist[jcount-1] = j ;
         }
      }

/*   all ellipsoids- */

      ecount = nels-1 ;
      for (  e = 0 ; e < ecount ; ++ e )
      {
         elist[e] = e+1 ;
      }

rtrn: if (debug <= 0)
      {
         fprintf(stderr,"setelsc %3d %3d %3d %3d\n",
            ellpsd,jthis,ecount,jcount);
         fprintf(stderr,"   elist");
         for (e = 0; e < ecount; ++e)
            fprintf(stderr," %3d", elist[e]);
         fprintf(stderr,"\n");
         fprintf(stderr,"   jlist");
         for (j = 0; j<jcount; ++j)
            fprintf(stderr," %3d",jlist[j]);
         fprintf(stderr,"\n");
      }
}  /* setels */
/*************************************************/

doattach()
/* 
  create a joint at cursor position. 
  between ellipsoids ell1 and ell2.

  called by checkeys 
  calls     findfg, getout. 
*/
{
   int findfg();
   int fig1,fig2;
   int nogo;
   int low,high ;

   join = njts;
   nogo = FALSE;
   if (ell1 < 0)
   {
      nogo = TRUE;
      fprintf(stderr,"ell1 not assigned\n");
   }
   if (ell2 < 0)
   {
      nogo = TRUE;
      fprintf(stderr,"ell2 not assigned\n");
   }
   for (j = 0; j < njts; ++j)
   {
      if ( ((coel[j][0] == ell1)&&(coel[j][1] == ell2))
        || ((coel[j][0] == ell1)&&(coel[j][1] == ell2)) )
      {
         nogo = TRUE;
         fprintf(stderr,"%s and %s already joined at %s\n",
            ename[ell1],ename[ell2],jname[join]);
      }
   }
   if (nogo == FALSE)
   {
      coel[join][0] = ell1 ;
      coel[join][1] = ell2 ;
      jnt[join][0] = cursor[0];
      jnt[join][1] = cursor[1];
      jnt[join][2] = cursor[2];
      jcursor = join;
      fprintf(stderr,"joined %s and %s at %s\n",
         ename[ell1],ename[ell2],jname[join]);
      ++ njts;
   }
}  /* doattach */
/*************************************/

dodetach(join)
int join;
/* 
  split 1 figure into 2. 

  called by checkeys 
  calls  findfg, setels, getout. 
*/
{
   int othere;
   int j;

   if (njts <= 0)
   {
      fprintf(stderr,"no joints yet to detach\n");
      goto rtrn;
   }
   othere = 0 ;
   if (coel[join][0] == ellpsd) othere = coel[join][1] ;
   if (coel[join][1] == ellpsd) othere = coel[join][0] ;
   if (othere == 0)
   {
      fprintf(stderr,"joint %s not connected to %s\n",
         jname[join],ename[ellpsd]);
      goto rtrn;
   }
/*
   move all the joints down one -
*/
   for (j = join; j <njts; ++j)
   {
      coel[join][0] = -1 ;
      coel[join][1] = -1 ;
      jnt[j][0] = jnt[j+1][0];
      jnt[j][1] = jnt[j+1][1];
      jnt[j][2] = jnt[j+1][2];
   }
   --njts;
   jcursor = -1;
   join = -1;
rtrn:;
}  /* dodetach */
/*******************************/

domoveby(x,y,z,refell)
   int refell;
   double x,y,z;
/* 
  moves ellipsoids and joints in lists 'elist' and 'jlist' 
  by vector 'x,y,z' relative to the axes of 'refell'. 

  called by  try, action, abut. 
  calls      rotget, vecmul, shift 
*/
{
   double v[EMAX][3];
   double r[3][3];
   double unr[3][3] ;

   if (debug <= 0)
      fprintf(stderr,"domovebya %9g %9g %9g\n",x,y,z);
   v[0][0] = x ;
   v[0][1] = y ;
   v[0][2] = z ;
   rotget(r,unr,refell) ;
   vecmul(v,r,0) ;
   shift(v[0][0],v[0][1],v[0][2]);
   if (debug <= 0)
      fprintf(stderr,"domovebyb %9g %9g %9g\n",
         v[0][0],v[0][1],v[0][2]);
}  /* domoveby */
/************************************************************/

dogrofig(f0,f1,f2,x0,x1,x2)
double f0,f1,f2,x0,x1,x2;
/* 
  scale parts in 'elist' and 'jlist' about the point 'x0,x1,x2', 
  multiplying all semi-axes and coords of centres and joints 
  by factors f0,f1,f2 in x,y, and z directions respectively

  called by checkeys 
  calls  shift, dogroell 
*/
{
   int e,j,n ;
   double f[3];

   if (debug <= 2)
      fprintf(stderr,"dogrofig %3d %3d %9g %9g %9g\n",
         ecount,jcount,f0,f1,f2);
   f[0] = f0;
   f[1] = f1;
   f[2] = f2;
   shift(-x0,-x1,-x2);
   for (  n = 0 ; n < ecount ; ++ n )
   {
      e = elist[n];
      dogroell(f,e,cen) ;
      dogroell(f,e,ax3) ;
   }
   for (  n = 0 ; n < jcount ; ++ n )
      dogroell(f,jlist[n],jnt) ;

   shift(x0,x1,x2);
}  /* dogrofig */
/********************************************/

dogroell(f,j,array)
   int j ;
   double f[3],array[EMAX][3] ;
/* 
  scales jth member of array by factor 'f'. 

  called by action, dogrofig 
*/
{
   if (debug <= 2) fprintf(stderr,"dogroella %3d %9g %9g %9g %9g %9g %9g\n",
      j,f[0],f[1],f[2],array[j][0],array[j][1],array[j][2]);
   array[j][0] *= f[0] ;
   array[j][1] *= f[1] ;
   array[j][2] *= f[2] ;
   if (debug <= 2) fprintf(stderr,"dogroellb %9g %9g %9g\n",
      array[j][0],array[j][1],array[j][2]);
}  /* dogroell */
/***************************************/

rotput(r,n)
      int n ;
      double r[3][3] ;
/*
   interpret rotation matrix 'r' as direction cosines of a
   rotation axis, and the sine and cosine of a rotation about
   that axis, and store in array 'quat'.

   uses the fact that any rotation matrix can be written as -

   ( x.x.m+c    x.y.m-z.s  x.z.m+y.s )
   ( x.y.m+z.s  y.y.m+c    y.z.m-x.s )
   ( x.z.m-y.s  y.z.m+x.s  z.z.m+c   )

   where
     x,y,z-components of unit vector along rotation axis
             x=cos(a1)cos(a2)  y=cos(a1)sin(a2)  z=sin(a1)
             a1,a2-azimuth and elevation of axis from x axis
     s,c  -sine and cosine of rotation about that axis
     m     = 1-c

     x,y,z are stored in quat[n,0], quat[n,1], quat[n,2]
     s,c   are stored in quat[n,3], quat[n,4]

   see 'control of round-off propagation in articulating the
        human figure', D.Herbison-Evans and D.S.Richardson
        computer graphics and image processing,
        vol 17 pp 386-393 (1981)

   called by matrot, dospinto, doangles, dolimb,
             getwist, store3.
*/
{
      int j,k ;
      double a[3][3],b[3],d[3],e,f,g,c,s,trace ;
      double csq;
      double acc = {0.000002} ;

      if (debug <= -1)
         fprintf(stderr,"rotputa %3d\n",n);
      if (debug <= 0)
      {
         for (k = 0; k < 3; ++k)
            fprintf(stderr,"      %9g %9g %9g\n",r[k][0],r[k][1],r[k][2]);
      }
      b[0] = r[1][2]-r[2][1] ;
      b[1] = r[2][0]-r[0][2] ;
      b[2] = r[0][1]-r[1][0] ;
      e = b[0]*b[0]+b[1]*b[1]+b[2]*b[2] ;
      trace = r[0][0]+r[1][1]+r[2][2] ;
      g = sqrt(e) ;
      if (debug <= -1)
           fprintf(stderr,"rotputb %9g %9g %9g %9g\n",trace,g,e,acc);

      if (e <= acc) goto lab1 ;

      f = doub1/g ;
      quat[n][0] = f*b[0] ;
      quat[n][1] = f*b[1] ;
      quat[n][2] = f*b[2] ;

      if (debug <= -1)
         fprintf(stderr,"rotputc %3d %9g %9g %9g %9g\n",
                            debug,f,b[0],b[1],b[2]);
/*
     use g=2s, and trace=1+2c to find s and c -
*/
      s = inv2*g;
      csq = doub1-s*s;
      if (csq < doub0) csq = doub0;
      c = sqrt(csq);
      if (trace < doub1) c = -c;
      if (debug <= -1) fprintf(stderr,"rotputd %9g %9g\n",s,c);
      quat[n][3] = s ;
      quat[n][4] = c ;
      goto lab10 ;
/*
   symmetric matrix (180 or 360 degree rotation) -
*/
lab1: if (debug <= 0)
      {
         fprintf(stderr,
            "rotpute symmetric matrix, frame %3d, ellipsioid %3d\n",
                n);
         fprintf(stderr,"   trace %9g, g %9g, e %9g, acc %9g\n",
             trace,g,e,acc);
         for (k = 0; k < 3; ++k)
            fprintf(stderr,"         %9g %9g %9g\n",
               r[k][0],r[k][1],r[k][2]);
      }
      c = inv2*(trace-doub1);
      for (  j = 0 ; j < 3 ; ++ j )
      {
         d[j] = doub0 ;

/*   run across a row- */

         for (  k = 0 ; k < 3 ; ++ k )
         {
            a[j][k] = r[j][k]+r[k][j] ;
            if (j == k) a[j][j] = doub2*(r[j][j]-c) ;
            d[j] = d[j]+a[j][k]*a[j][k] ;
         }
         if (debug <= -1)
            fprintf(stderr,"rotputf %3d %9g %9g %9g %9g\n",
                               j,a[j][0],a[j][1],a[j][2],d[j]);
      }

/*   choose most stable row- */

      j = 0 ;
      if (d[1] > d[0]) j = 1 ;
      if (d[2] > d[j]) j = 2 ;
      if (d[j] != doub0) f = doub1/sqrt(d[j]) ;
         else
         {
            f = doub1;
            a[j][0] = doub1;
         }
      quat[n][0] = f*a[j][0] ;
      quat[n][1] = f*a[j][1] ;
      quat[n][2] = f*a[j][2] ;
      quat[n][3] = inv2*g ;
      quat[n][4] = c ;
      if (debug <= -1)
         fprintf(stderr,"rotputg %3d %9g %9g %9g %9g %9g %9g\n",
                               j,a[j][0],a[j][1],a[j][2],d[j],f,g);

  lab10: if (debug <= -1)
          fprintf(stderr,"rotputh    %3d %9g %9g %9g %9g %9g\n",
              n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      for (k = 0; k < 5; ++k)
      {
         if ((quat[n][k] > -tolr) && (quat[n][k] < tolr)) quat[n][k] = 0;
         if (quat[n][k] >  doub1) quat[n][k] =  doub1;
         if (quat[n][k] < -doub1) quat[n][k] = -doub1;
      }
}  /* rotput */
/********************************************/

delel()
/*
     delete an ellipsoid

     called by checkeys.
*/
{
   int e,j;

   for (e = ellpsd; e < (nels-1); ++e)
   {
      for (j = 0; j < 3; ++j)
      {
         cen[e][j] = cen[e+1][j];
         ax3[e][j] = ax3[e+1][j];
         quat[e][j] = quat[e+1][j];
      }
      quat[e][3] = quat[e+1][3];
      quat[e][4] = quat[e+1][4];
      sprintf(ename[e],"%s",ename[e+1]);
   }
   --nels;
   jcursor = -1;
   for (j = 0; j < njts; ++j)
   {
      if (coel[j][0] == ellpsd) dodetach(j);
      if (coel[j][1] == ellpsd) dodetach(j);
   }
   ellpsd = -1;
} /* delel */
/*******************************************************/

addel()
/*
     create another ellipsoid

     called by checkeys.
*/
{
   int j;

   for (j = 0; j < 3; ++j)
   {
      cursor[j] = doub500;
      cen[nels][j] = doub500;
   }
   ax3[nels][0] = (double)100;
   ax3[nels][1] = (double)102;
   ax3[nels][2] = (double)101;
   mkquat(nels,doub0,doub0,doub0);
   ellpsd = nels;
   setels(ellpsd,-1);
   ++nels;
   if (nels >= EMAX)
   {
      fprintf(stderr,"ERROR - more ellipsoids than %d\n",EMAX);
      goto rtrn;
   }
   jcursor = -1;
   doing = 1;
rtrn:;
} /* addel */
/*******************************************************/

store3(f)
int f;
/*
    print out axes, centres, orientations and colours
    of  nels ellipsoids starting at 1 (avoiding  0 = world),
    and the joints too.

    called by checkeys
    calls  setels, dospinby, ipr, mkang, rotput.
*/
{
   double pplace[3];
   int   j,k;

   fprintf(stderr,"storing file %s\n",foutname);
   if (debug <= 0)
      fprintf(stderr,"store3a %3d %3d %3d\n",f,nels,njts);
   if (first == TRUE)
   {
      if (NULL == (outfile=fopen(foutname,"w+")))
         fprintf(stderr,"cannot open %s for writing",foutname);
   }
   fprintf(outfile,"%d %d 5000 5000 5000 0 0 0\n",nels-1,f);
/*
   print out the ellipsoid details -
   (avoiding ellipsoid 0 = world)
*/
   if (nels > 1)
   {
      for (j = 1; j < nels; j++)
      {
         mkang(j);
         if (debug <= 0)
            fprintf(stderr,"store3b %d %9g %9g\n",j,ang[0],rad);
         for (k = 0; k < 3; k++) ipr(doub10*ax3[j][k]);
         for (k = 0; k < 3; k++) ipr(doub10*cen[j][k]);
         for (k = 0; k < 3; k++) ipr(doub10*ang[k]*rad);
         for (k = 0; k < 3; k++) fprintf(outfile,"%3d ",elcol[j][k]);
         fprintf(outfile,"%s ",ename[j]);
         fprintf(outfile,"%d\n",j);
      }
/*
  write the joints out also
  (headed by a negative 1  and the number of joints)
*/
      fprintf(outfile,"%d %d\n",-1,njts);
      for (  j = 0 ; j < njts ; ++ j )
      {
         for (  k = 0 ; k < 2 ; ++ k )
            fprintf(outfile,"%3d ",coel[j][k]-1) ;
         for (  k = 0 ; k < 3 ; ++ k )
            ipr(doub10*jnt[j][k]);
         fprintf(outfile," %s\n",jname[j]);
      }
   }
   fprintf(outfile,"0 0 0 0 0 0 0 0\n");
   first = FALSE ;
}  /* store3 */
/***********************************************/

ipr(x)
double x;
/*
    print out integral part of x.

    called by store3.
*/
{
      int k;

      if (x >= doub0) k = (int)(x+inv2);
              else  k = (int)(x-inv2);
      fprintf(outfile,"%5d ",k);
}  /* ipr */
/**********************************************************/

mkang(n)
int n ;
/*
   get angles from 'n'th entry in 'quat' into 'ang' 

   called by store3. 
*/
{
      double x,y,z,s1,c1,m1 ;
      
      x = quat[n][0] ;
      y = quat[n][1] ;
      z = quat[n][2] ;
      s1 = z ;
      m1 = 1.0-z*z ;
      if (debug <  0)
         fprintf(stderr,"mkanga %d %9g %9g %9g %9g %9g\n",
                    n,quat[n][0],quat[n][1],quat[n][2],s1,m1);
      if (m1 > 0.0) c1 = sqrt(m1) ;
         else c1 = 0.0 ;
      if (debug < 0)
         fprintf(stderr,"mkangb %9g %9g %9g\n",
            c1,quat[n][3],quat[n][4]);
      if ((x == 0.0 ) && ( y == 0.0))
          ang[0] = 0.0;
             else ang[0] = atan2(y,x) ;
      if ((s1 == 0.0 ) && ( c1 == 0.0))
          ang[1] = 0.0;
             else ang[1] = atan2(s1,c1) ;
      if ((quat[n][3] == 0.0 ) && ( quat[n][4] == 0.0))
          ang[2] = 0.0;
             else ang[2] = atan2(quat[n][3],quat[n][4]) ;
      if (debug < 0)
         fprintf(stderr,"mkangc %d %9g %9g %9g\n",
                    n,ang[0],ang[1],ang[2]);
}  /* mkang */
/****************************************************/

brighten(fac)
double fac;
/*
    make ellipsoids brighter or darker

    called by checkeys
*/
{
   int col;
   int e,j,n;

   for (e = 0; e < ecount; ++e)
   {
      n = elist[e];
      for (j = 0; j < 3; j ++)
      {
         col = (int)((double)elcol[n][j]*fac);
         col = min(pmax,col);
         elcol[n][j] = max(0,col);
      }
   }
} /* brighten */
/****************************************************/

read3()
/* 
  read information about current frame -  
    nels - the number of ellipsoids in it 
         (zero is null as end - of - file marker) 
    frame - the name of the current frame (f is its number) 
         the first frame name is set as the value of debug,
    view - point and direction of view. 
  then for each ellipsoid, its 3 axis lengths, coordinates 
         of its centre, its angles of orientation, its
         colours, its name, and possibly a texture map fike name. 
  then a flag and the number of joints
  then for each joint, the ellipsoids it joins
         and its coordinates.
    
     called by main, checkeys 
     calls  mkquat 
*/
{
   double dang1,dang2,dang3;
   double deg10;
   int a1,a2,a3;
   int ang1,ang2,ang3;
   int axx,axy,axz;
   int c0,c1;
   int cenx,ceny,cenz;
   int col1,col2,col3;
   int flag;
   int frame;
   int jntx,jnty,jntz;
   int k ;
   int vx,vy,vz;
   char map[BMAX];

   fprintf(stderr,"reading file %s\n",finame);
   ok = TRUE;
   deg10 = pi/(double)1800;
   if (NULL == (infile=fopen(finame,"r")))
   {
      fprintf(stderr,"cannot open %s for reading",finame);
      goto rtrn;
   }
   fscanf(infile,"%d %d %d %d %d %d %d %d\n",
         &nels,&frame,&vx,&vy,&vz,&a1,&a2,&a3);
   fprintf(stderr,"read %d ellipsoids in frame %d\n",nels,frame );
   if (nels <= 0)
      ok = FALSE;
   else
   if (nels > EMAX)
   {
      fprintf(stderr,"\nERROR in read3 : frame %d\n",frame);
      fprintf(stderr,"number of ellipsoids %d\n max number %d\n",
         nels,EMAX);
      ok = FALSE;
      goto rtrn;
   }
   else
   {
/* 
     read ellipsoids in current frame -  
*/
      for ( k = 1 ; k <= nels ; ++ k )
      {
         if (NULL == fscanf(infile,
            "%d %d %d %d %d %d %d %d %d %d %d %d %s %s",
            &axx,&axy,&axz,&cenx,&ceny,&cenz,&ang1,&ang2,&ang3,
            &col1,&col2,&col3,ename[k],map) )
         {
            fprintf(stderr,"\nERROR in read3: end of file\n");
            fprintf(stderr,"reading ellipsoid %d in frame %d\n",
                k,frame);
            ok = FALSE;
            goto rtrn;
         }
         if (debug <= 0)
            fprintf(stderr,"read3b %d %d %d %d %d %d %d %d %d %d\n",
            k,axx,axy,axz,
            cenx,ceny,cenz,
            ang1,ang2,ang3);
/* 
     scale everything back to size -  
*/
         ax3[k][0] = inv10*axx ;
         ax3[k][1] = inv10*axy ;
         ax3[k][2] = inv10*axz ;
         cen[k][0] = inv10*cenx ;
         cen[k][1] = inv10*ceny ;
         cen[k][2] = inv10*cenz ;
         dang1 = deg10*ang1 ;
         dang2 = deg10*ang2 ;
         dang3 = deg10*ang3 ;
         elcol[k][0] = col1;
         elcol[k][1] = col2;
         elcol[k][2] = col3;
         if (debug < 2)
            fprintf(stderr,
               "read3c %s %9g %9g %9g %9g %9g %9g %9g %9g %9g\n",
               ename[k],ax3[k][0],ax3[k][1],ax3[k][2],
               cen[k][0],cen[k][1],cen[k][2],
               dang1,dang2,dang3);
         mkquat(k,dang1,dang2,dang3) ;
      }
      ++nels;
/*
     read joints -
*/
      fscanf(infile,"%d %d\n",&flag,&njts);
      if (debug <= 0)
         fprintf(stderr,"read3d %d %d\n",flag,njts);
      if (flag < 0)
      {
         for ( k = 0 ; k < njts ; ++ k )
         {
            if (NULL == fscanf(infile,"%d %d %d %d %d %s\n",
                &c0,&c1,&jntx,&jnty,&jntz,jname[k]) )
            {
               fprintf(stderr,"unexpected end of file\n");
               fprintf(stderr,"reading joint %d in frame %d\n",
                   k,frame);
               ok = FALSE;
               goto rtrn;
            }
            else
            {
               coel[k][0] = 1+c0;
               coel[k][1] = 1+c1;
               jnt[k][0] = inv10*(double)jntx;
               jnt[k][1] = inv10*(double)jnty;
               jnt[k][2] = inv10*(double)jntz;
               if (debug < 2)
                  fprintf(stderr,
                     "read3d %s %9g %9g %9g\n",
                     jname[k],jnt[k][0],jnt[k][1],jnt[k][2]);
            }
         }
      }
   }
rtrn:;
} /* read3 */
/**********************************************/

edhide()
/* 
     This draws the outline of each ellipsoid in turn. 
     Each is approximated by a series of chords, 
     plotted with respect to Cohen's parameter. 
     Before plotting an ellipse, the intersection points 
     of all other ellipses are calculated in terms of the 
     plotting parameter, and these are ordered and the 
     hidden arcs calculated. 
     On plotting, the hidden arcs are skipped. 

     called by dopic 
     calls  (prinel), minmax, setnup, chkell, setpln,
            obscur, order. 
*/
{
   int j,k;

   if (debug < 1)
      fprintf(stderr,"edhidea %d\n", nels);
   minmax();
/* 
     run thru ellipsoids to draw each in turn
     (avoiding 0) -  
*/
   for ( n = 1 ; n < nels ; ++ n )
   {
       if (debug < 1)
       {
          fprintf(stderr,"edhideb %d %s %9g %9g %9g\n",
             n,ename[n],cen[n][0],cen[n][1],cen[n][2]);
          for (k = 1; k < nels; ++k)
                fprintf(stderr,"   %d %d %d\n",n,k,hash[n][k]);
       }
       if (cen[n][2] < doub0) goto allhid ;
       if ((cen[n][0]+maxax[n]) < doub0 ) goto allhid;
       if ((cen[n][1]+maxax[n]) < doub0 ) goto allhid;
       if ((cen[n][0]-maxax[n]) > doub1000 ) goto allhid;
       if ((cen[n][1]-maxax[n]) > doub1000 ) goto allhid;
       j = 0;
       setnup(n);
       if ( ok == FALSE ) goto snag ;
       if (debug < 1)
          fprintf(stderr,"edhidec %d %9g %9g %9g\n",
                n,axxn,axyn,phi);
/* 
     run thru other ellipsoids to find obscured arcs of the "n"th -  
*/
       for (  j = 1 ; j < nels ; ++ j )
       {
          if (debug < 1)
             fprintf(stderr,"edhidee %d %d %d %9g %9g %9g\n",
                n,j,hash[j][n],cen[j][0],cen[j][1],cen[j][2]);
          if (j == n) goto endj ;
          if (cen[j][2] < doub0) goto endj ;
/* 
     check if identical - 
*/
          for ( k = 0 ; k < 3 ; ++ k )
          {
             if (cen[n][k] != cen[j][k]) goto diff ;
             if (ax3[n][k] != ax3[j][k]) goto diff ;
             if (quat[n][k] != quat[j][k]) goto diff ;
          }
          if (quat[n][3] != quat[j][3]) goto diff ;
          if (quat[n][4] != quat[j][4]) goto diff ;
          if (n > j) goto diff ;
          goto endj ;
/* 
     check whether separation too great for intersection -  
*/
diff:
          if (debug < 1)
              fprintf(stderr,"edhidef %9g %9g\n",
                 maxax[j],maxax[n]);
          if ((cen[n][2]+maxax[n]) > (cen[j][2]-maxax[j]))
          {
             sqsep = (cen[n][0]-cen[j][0])*(cen[n][0]-cen[j][0])
                 + (cen[n][1]-cen[j][1])*(cen[n][1]-cen[j][1]) ;
             sqmax = (axyn + maxax[j])*(axyn + maxax[j]) ;
             if (sqsep > sqmax)
             {
                 hash[n][j] = 0;
                 hash[j][n] = 0;
             }
             else
             {
                chkell(j);
                if ( ok == FALSE ) goto snag ;
                if (debug < 1)
                   fprintf(stderr,"edhideg %d %d %9g %9g\n",
                      nrtsa,nrtsb,atheta[0],btheta[0]);
                setpln(cj,j,n,ellj);
                if (debug < 1)
                     fprintf(stderr,"edhideh %9g %9g\n",
                         atheta[0],btheta[0]);
                if ( ok == FALSE ) goto snag ;
                if ((nrtsa+nrtsb) == 0)
                {
/* 
     if no intersections were found, check for total obscuration 
     by passing whole outline on for testing -  
*/
                    obscur(maxval) ;
                    if ( hidden == TRUE ) goto allhid ;
                }
                else
                {
/* 
     find which arcs are hidden -  
*/
                    order(j);
                    if ( ok == FALSE ) goto snag ;
                    if (appear[n][1][1] > maxval) goto done ;
                 } /* nrts */
              } /* sqsep */
          } /* cen */
endj:
          if (debug < 1)
             fprintf(stderr,"edhidei  %d %d %d %9g %9g %9g\n",
                nels,n,j,cen[n][0],cen[n][1],cen[n][2]);
       } /* j  */
      goto done ;
/* 
     ellipsoid is completely hidden -  
*/
allhid: appear[n][0][0] = -maxval ;
      appear[n][0][1] =  maxval ;
      narcs[n] = 1 ;

done:
      if ( ok == FALSE ) goto snag ;
    } /* end n loop */

   goto rtrn ;
/* 
     snags -  
*/
snag: fprintf(stderr,"snag in edhide %d %d %d %d\n",
         f,frame,n,j); 
rtrn: ;
} /* edhide */
/*************************************************/

setnup(n)
int n;
/* 
     set up parameters of "n"th ellipsoid relative to own centre. 

     called by edhide, edrasel. 
     calls  setmat, setcof, setpln, setax2, setphi 
*/
{
   double axes[2];

   if (debug < 1)
      fprintf(stderr,"setnupa %d %9g %9g %9g\n",
         n,ax3[n][0],ax3[n][1],ax3[n][2]);
   narcs[n] = 2 ;
   appear[n][0][0] =  -maxval ;
   appear[n][0][1] =  -maxval ;
   appear[n][1][0] = maxval ;
   appear[n][1][1] = maxval ;
   setmat(n,elln) ;
   if ( ok == FALSE ) goto snag ;
   setcof(con,elln) ;
   if ( ok == FALSE ) goto snag ;
   setpln(cn,n,n,elln) ;
   if ( ok == FALSE ) goto snag ;
   setax2(axes,con) ;
   if ( ok == FALSE ) goto snag ;
   axxn = axes[0];
   axyn = axes[1];
   ax2[n][0] = axxn;
   ax2[n][1] = axyn;
   if (debug < 1)
      fprintf(stderr,"setnupb %9g %9g\n",
         axxn,axyn);
   setphi(axes,con,mcn) ;
   if ( ok == FALSE ) goto snag ;
   phi2[n] = phi;
   xstrt[0] = axxn*cphi ;
   xstrt[1] = axxn*sphi ;
   xm[0] = xstrt[0]*mcn[1]+xstrt[1]*mcn[2] ;
   xm[1] = xstrt[0]*mcn[3]+xstrt[1]*mcn[4] ;
   if (debug < 1)
      fprintf(stderr,"setnupc %9g %9g %9g %9g %9g %9g\n",
         axxn,axyn,phi2[n],phi,sphi,cphi);
   goto rtrn ;
/* 
     snag -  
*/
snag: ok = FALSE;
   fprintf(stderr,
      "subr setnup  snag in ellipsoid %d %9g\n",n,phi );

rtrn: 
   if (debug < 1)
      fprintf(stderr,"setnupd %9g %9g %9g %9g %9g %9g\n",
         axxn,axyn,xstrt[0],xstrt[1],xm[0],xm[1]);
} /* setnup */
/******************************************/

chkell(j)
int j;
/* 
     checks whether ellipsoid n outline is obscured by 
     ellipsoid j. 

     find coj - coeffs of "j"th ellipsoid outline shifted,
     and rcoj - rotated wrt axes of "n"th outline. 

     called by edhide 
     calls  setmat, setcof, shfcof, copcof, rotcof, ellcut, ellpln 
*/
{
   double cop[6],sqmin,absj,absp,scale ;

   int ellcut();

   nrtsa = 0 ;
   nrtsb = 0 ;
   if (debug < 1)
      fprintf(stderr,"chkella %9g %9g %9g %d %d %d\n",
         cn[0],axxn,axyn,n,j,hash[j][n]);
   setmat(j,ellj) ;
   ellj22 = ellj[2][2];
   if (debug < 1)
      fprintf(stderr,"chkellb  %9g %9g\n", ellj[0][0],quat[n][0]);
   if ( ok == FALSE ) goto snag ;
   setcof(coj,ellj) ;
   if (  ok == FALSE ) goto snag ;
   shfcof(coj,cen[n][0]-cen[j][0],cen[n][1]-cen[j][1]) ;
   copcof(coj,rcoj) ;
   rotcof(rcoj,cphi, -sphi) ;
/* 
     have outlines been found before not to intersect -  
*/
   if (hash[j][n] != 0)
   {
/* 
     if ellipse "j" does not surround "n"th ellipse, 
     find intersections using shifted and rotated coefficients -  
*/
      sqmin = (minax[j] - axyn)*(minax[j] - axyn) ;
      if (debug < 1)
         fprintf(stderr,"chkellc  %9g %9g %9g %9g\n",
             sqmin,minax[j],axyn,sqsep );
      if ((sqmin < sqsep) || (minax[j] < axyn))
         nrtsa = ellcut(axxn,axyn,rcoj,aerr,atheta) ;
      if (nrtsa == 0)
      {
         hash[n][j] = 0;
         hash[j][n] = 0;
      }
      if (debug < 1)
      {
         fprintf(stderr,"chkelld %9g %9g\n", axxn,axyn);
         fprintf(stderr,"    %9g %9g %9g %9g %9g %9g\n",
            rcoj[0],rcoj[1],rcoj[2],rcoj[3],rcoj[4],rcoj[5]);
         fprintf(stderr,"    %9g %9g %9g %9g\n",
            atheta[0],atheta[1],atheta[2],atheta[3]);
         fprintf(stderr,"    %9g %9g %9g %9g\n",
            aerr[0],aerr[1],aerr[2],aerr[3]);
      }
   }
/* 
     check for penetration -  
     set plane of "n"th outline and equation of intersection ellipse 
     of this with "j"th ellipsoid -  
*/
   if ((nrtsa != 0)
        || (sqsep < axyn*axyn)
        || (sqsep < maxax[j]*maxax[j]))
   {
      ellpln(cop,ellj,cn[0],cn[1],cn[2],
         cen[j][0]-cen[n][0],cen[j][1]-cen[n][1],
         cen[j][2]-cen[n][2]);
      rotcof(cop,cphi, -sphi) ;
/* 
     check roughly that the section ellipse minor axis is smaller 
     than that of projected ellipse -  
*/
      absj = inv2*fabs(rcoj[0]+rcoj[1])+fabs(rcoj[0]
             - rcoj[1])+fabs(rcoj[2]) ;
      absp = inv2*fabs(cop[0]+cop[1])+fabs(cop[0]
             - cop[1])+fabs(cop[2]) ;
      if (debug < 1)
         fprintf(stderr,"chkelle  %9g %9g\n", absj,absp );
      if (absj > absp)
      {
         scale = 1.01*absj/absp ;
         cop[0] = scale*cop[0] ;
         cop[1] = scale*cop[1] ;
         cop[2] = scale*cop[2] ;
      }
      nrtsb = ellcut(axxn,axyn,cop,berr,btheta) ;
   }
   goto rtrn ;
/* 
     snag -  
*/
snag: fprintf(stderr,
     "\nERROR edhide chkell - ellipsoids %d %d %d\n",
     n,j,ok );

rtrn:
   if (debug < 1)
      fprintf(stderr,"chkellf %d %9g\n",nrtsb,btheta[0]);
} /* chkell */
/******************************************/

copcof(old,new)
   double old[6],new[6] ;
/* 
     make a copy of the 6 element array old into new. 

     called by  chkell 
*/
{
   int j ;

   if (debug < 1)
      fprintf(stderr,"copcof %9g\n", old[1] );

   for (  j = 0 ; j < 6 ; ++ j )
   {
      new[j] = old[j] ;
   }
} /* copcof */
/******************************************/

minmax()
/* 
     find maximum semiaxis of each ellipsoid,
     and set hash table to null.

     called by edhide, edrasel. 
*/
{
   int j,k ;

   for ( j = 0 ; j < nels ; ++ j )
   {
      maxax[j] = ax3[j][0] ;
      minax[j] = ax3[j][0] ;
      if (ax3[j][1] > maxax[j]) maxax[j] = ax3[j][1];
      if (ax3[j][1] < minax[j]) minax[j] = ax3[j][1];
      if (ax3[j][2] > maxax[j]) maxax[j] = ax3[j][2];
      if (ax3[j][2] < minax[j]) minax[j] = ax3[j][2];
      xmax[j] = cen[j][0]+maxax[j];
      xmin[j] = cen[j][0]-maxax[j];
      ymax[j] = cen[j][1]+maxax[j];
      ymin[j] = cen[j][1]-maxax[j];
      zmin[j] = cen[j][2]-maxax[j];
      for ( k = 0 ; k < nels ; ++ k )
         hash[j][k] = -1;
      for ( k = 1 ; k < 3 ; ++ k )
      {
         if (ax3[j][k] > maxax[j]) maxax[j] = ax3[j][k] ;
         if (ax3[j][k] < minax[j]) minax[j] = ax3[j][k] ;
      }
      if (debug < 1)
         fprintf(stderr,"minmax %d %9g %9g\n",j,minax[j],maxax[j] );
   }
} /* minmax */
/************************************************/

prinel()
/* 
     this lists the axis lengths, positions and quaterions of 
     all the ellipsoids. 

     called by edhide 
*/
{
   int n ;

   fprintf(stderr,"prinel - \n");
   fprintf(stderr,"   el       ax      cen     quat\n");

   for ( n = 0 ; n < nels ; ++ n )
   {
      fprintf(stderr,
         "    %d %9g %9g %9g\n      %9g %9g %9g\n      %9g %9g %9g %9g %9g\n",
         n,ax3[n][0],cen[n][0],quat[n][0],
           ax3[n][1],cen[n][1],quat[n][1],
           ax3[n][2],cen[n][2],quat[n][2],quat[n][3],quat[n][4] );
   }
} /* prinel */
/**********************************************/

setmat(n,el)
   int n;
   double el[3][3] ;
/* 
     this finds the matrix "el" of the quadratic form of the "n"th 
     ellipsoid by taking the diagonal matrix of inverse square
     semi-axes, and doing on it a similarity transform for
     its own rotation. 

     called by setnup, chkell, allcofs. 
     calls  rotget, matmul 
*/
{
   int j,k ;
   double r[4][4],unr[4][4] ;

   if (debug < 1)
      fprintf(stderr,"setmata %d %9g %9g %9g\n",
         n,ax3[n][0],ax3[n][1],ax3[n][2]);
/* 
     initialise diagonal matrix -  
*/
   for ( j = 0 ; j < 3 ; ++ j )
   {
      for ( k = 0 ; k < 3 ; ++ k )
      {
         el[j][k] = doub0 ;
      }
      if ( ax3[n][j]*ax3[n][j]  ==  doub0 ) goto snag ;
      el[j][j] = doub1/(ax3[n][j]*ax3[n][j]) ;
   }

   rotget(r,unr,n);
/* 
  do similarity transform -  
*/
   matmul(el,unr,el) ;
   matmul(r,el,el) ;
   goto rtrn ;

snag:  fprintf(stderr,
          "subr setmat ax3[%d][%d] = 0\n",n,j);
   ok = FALSE ;

rtrn: if (debug < 1)
   {
      fprintf(stderr,"setmatb %9g %9g %9g\n",
         el[0][0],el[0][1],el[0][2] );
      fprintf(stderr,"        %9g %9g %9g\n",
         el[1][0],el[1][1],el[1][2] );
      fprintf(stderr,"        %9g %9g %9g\n",
         el[2][0],el[2][1],el[2][2] );
   }
} /* setmat */
/**********************************************/

rotget(r,unr,n)
   int n ;
   double r[3][3],unr[3][3] ;
/* 
     form a rotation matrix r and its inverse unr 
     from the "n"th entries in quat 

     called by setmat 
*/
{
   int i,j ;
   double cp,sp,x,y,z,m,xsp,ysp,zsp,xm,ym,zm,xym,xzm,yzm ;

   if (debug < 0)
      fprintf(stderr,"rotgeta %d %9g %9g %9g %9g %9g\n",
         n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
   x = quat[n][0] ;
   y = quat[n][1] ;
   z = quat[n][2] ;
   sp = quat[n][3] ;
   cp = quat[n][4] ;
   m = doub1 - cp ;
   xm = x*m ;
   ym = y*m ;
   zm = z*m ;
   xsp = x*sp ;
   ysp = y*sp ;
   zsp = z*sp ;
   xym = x*ym ;
   xzm = x*zm ;
   yzm = y*zm ;
   r[0][0] = x*xm+cp ;
   r[0][1] = xym+zsp ;
   r[0][2] = xzm - ysp ;
   r[1][0] = xym - zsp ;
   r[1][1] = y*ym+cp ;
   r[1][2] = yzm+xsp ;
   r[2][0] = xzm+ysp ;
   r[2][1] = yzm - xsp ;
   r[2][2] = z*zm+cp ;

   for ( i = 0 ; i < 3 ; ++ i )
   {
      for ( j = 0 ; j < 3 ; ++ j )
      {
         unr[i][j] = r[j][i] ;
      }
   }

   if (debug < 0)
   {
      fprintf(stderr,"rotgetb  %9g %9g %9g\n",r[0][0],r[0][1],r[0][2]);
      fprintf(stderr,"         %9g %9g %9g\n",r[1][0],r[1][1],r[1][2]);
      fprintf(stderr,"         %9g %9g %9g\n",r[2][0],r[2][1],r[2][2]);
   }
} /* rotget */
/**********************************************/

matmul(a,b,ans)
   double a[3][3],b[3][3],ans[3][3] ;
/* 
     this multiplies matrix "b" by "a" 
     and puts the product in "ans". 
     it is done via an intermediate matrix "c" to allow matmul 
     to be used with the same matrix for "a\n", "b", and/or "ans". 

     called by setmat 
*/
{
   int i,j,k ;
   double x,c[3][3] ;

   for ( i = 0 ; i < 3 ; ++ i )
   {
      for ( j = 0 ; j < 3 ; ++ j )
      {
         x = doub0 ;
         for ( k = 0 ; k < 3 ; ++ k )
         {
            x = x+a[i][k]*b[k][j] ;
         }
         c[i][j] = x ;
      }
   }
   for ( i = 0 ; i < 3 ; ++ i )
   {
      for ( j = 0 ; j < 3 ; ++ j )
      {
         ans[i][j] = c[i][j] ;
      }
   }
} /* matmul */
/******************************************/

setcof(coef,el)
   double coef[6],el[3][3] ;
/* 
     set up coeffs of outline ellipse of an ellipsoid about 
     its own centre in the form -  

     coef[0]*x**2 + coef[1]*y**2 + coef[2]*x*y 
         + coef[3]*x + coef[4]*y + coef[5] = 0 

     called by setnup, chkell, allcofs.
*/
{
   double den ;

   if (debug < 1)
      fprintf(stderr,"setcofa %9g %9g\n",
         cursor[0],el[0][0]);
   if (el[2][2] != doub0)
   {
      den = doub1/el[2][2] ;
      coef[0] = el[0][0] - el[0][2]*el[0][2]*den ;
      coef[1] = el[1][1] - el[1][2]*el[1][2]*den ;
      coef[2] = doub2*(el[0][1] - el[0][2]*el[1][2]*den) ;
      coef[3] = doub0 ;
      coef[4] = doub0 ;
      coef[5] =  -doub1 ;
   }
   else
   {
      fprintf(stderr,
         "setcof: matrix error %9g %9g %9g\n",
         el[0][0],el[0][1],el[0][2]);
      ok = FALSE ;
   }
   if (debug < 1)
      fprintf(stderr,"setcofb %9g %9g %9g %9g %9g %9g\n",
         coef[0],coef[1],coef[2],coef[3],coef[4],coef[5]);
} /* setcof */
/************************************************/

setpln(c,j,n,el)
   int j,n;
   double c[3],el[3][3];
/* 
     find coeffs of plane of outline of "j"th ellipsoid relative 
     to the centre of the "n"th ellipsoid, in the form -  

     cx*x + cy*y + cc + z = 0 

     called by setnup, edhide, allcofs. 
*/
{
   double cc,cx,cy;
   double el22,den ;

   if (debug < 1)
      fprintf(stderr,"setplna %d %d\n", j,n );
   el22 = el[2][2] ;
   if (el22 != doub0)
   {
      den = doub1/el22 ;
      cx = el[0][2]*den ;
      cy = el[1][2]*den ;
      cc = cx*(cen[n][0]-cen[j][0]) + cy*(cen[n][1]-cen[j][1])
           + (cen[n][2]-cen[j][2]) ;
      c[0] = cx;
      c[1] = cy;
      c[2] = cc;
      if (debug < 1)
         fprintf(stderr,"setplnb %9g %9g %9g\n",cx,cy,cc);
   }
   else
   {
      ok = FALSE ;
      fprintf(stderr,"setpln -  el no %d\n",
         n,"matrix element el[2][2] = 0\n");
   }
} /* setpln */
/******************************************************/

setax2(axes,coef)
   double axes[2],coef[6];
/* 
     find semiminor axis, axes[0], and semimajor axis, axes[1],
     of ellipse described by coef. 

     called by setnup 
*/
{
   double discrt,lamx,lamy,c12,rtdis ;

   lamx = 1 ;
   lamy = 1 ;
   if (debug < 1)
      fprintf(stderr,"setax2a %9g %9g %9g %9g %9g %9g\n",
         coef[0],coef[1],coef[2],coef[3],coef[4],coef[5]);
   discrt = (coef[0]-coef[1])*(coef[0]-coef[1]) + coef[2]*coef[2];
   if (discrt < doub0) goto snag ;
   c12 = inv2*(coef[0]+coef[1]) ;
   rtdis = inv2*sqrt(discrt) ;
   lamx = c12 + rtdis ;
   lamy = c12 - rtdis ;
   if (lamx <= doub0) goto snag ;
   if (lamy <= doub0) goto snag ;
   axes[0] = doub1/sqrt(lamx) ;
   axes[1] = doub1/sqrt(lamy) ;
   goto rtrn ;
/* 
     snags -  
*/
snag: fprintf(stderr,
         "\nERROR edhide subr setax2 snag %9g %9g %9g %d\n",
            lamx,lamy,discrt,n);
   ok = FALSE ;

rtrn:
   if (debug < 1) fprintf(stderr,"setax2b %9g %9g\n",axes[0],axes[1]);
} /* setax2 */
/******************************************/

setphi(axes,coef,mc)
   double axes[2],coef[6],mc[5];
/* 
     for the outline of "n"th ellipsoid, find -  
     (a) angle between axx axis and scene x axis, phi, 
     (b) coeffs of sin(theta) in Cohen matrix, mc(4). 

     called by setnup 
*/
{
   double x,y;
   double ec,spcp,spsq,cpsq,invec ;

   if (debug < 1)
      fprintf(stderr,"setphia %9g %9g\n", axxn,axyn );
/* 
     find orientation of axx axis -  
*/
   x = coef[2];
   y = coef[0]-coef[1];
   if (( x == doub0) && (y == doub0)) phi = doub0;
     else phi = inv2*atan2(x,y) ;
   if (phi < doub0) phi += twopi ;
/* 
     find Cohen matrix coeffs of sin(theta) -  
*/
   sphi = sin(phi) ;
   cphi = cos(phi) ;
   if ( (axes[0] != doub0) && (axes[1] != doub0) )
   {
      ec = axes[0]/axes[1] ;
      invec = axes[1]/axes[0] ;
      spcp = sphi*cphi ;
      spsq = sphi*sphi ;
      cpsq = doub1 - spsq ;
      mc[1] = spcp*( -ec + invec) ;
      mc[2] = cpsq*ec + spsq*invec ;
      mc[3] =  -spsq*ec - cpsq*invec ;
      mc[4] =  -mc[1] ;
      if (debug < 1)
         fprintf(stderr,"setphib %9g %9g %9g %9g %9g %9g\n",
            axxn,axyn,phi,sphi,cphi,ec,x,y);
   }
   else
   {
      fprintf(stderr,"snag in setphi  %d %9g %9g %9g\n",
         n,axes[0],axes[1],phi );
      ok = FALSE ;
   }
} /* setphi */
/******************************************/

shfcof(coef,x,y)
   double coef[6],x,y ;
/* 
     reset coeffs of ellipse by shifting its origin by (x,y). 

     called by  chkell, ellpln 
*/
{
   double x1,y2,x3 ;

   if (debug < 1)
      fprintf(stderr,"shfcofa %9g %9g \n        %9g %9g %9g %9g %9g %9g\n",
        x,y,coef[0],coef[1],coef[2],coef[3],coef[4],coef[5]);
   x1 = x*coef[0] ;
   y2 = y*coef[1] ;
   x3 = x*coef[2] ;
   coef[5] = coef[5]+x*(x1+coef[3])+y*(y2+coef[4]+x3) ;
   coef[4] = coef[4]+y2+y2+x3 ;
   coef[3] = coef[3]+x1+x1+coef[2]*y ;
   if (debug < 1)
      fprintf(stderr,"shfcofb %9g %9g %9g %9g %9g %9g\n",
        coef[0],coef[1],coef[2],coef[3],coef[4],coef[5]);
} /* shfcof */
/**********************************************/

rotcof(coef,c,s)
   double coef[6],s,c ;
/* 
     reset coeffs of ellipse by rotating about origin by angle phi, 
     where c = cos(phi) and s=sin(phi). 

     called by  chkell 
*/
{
   int j ;
   double new[6],sc,ssq,csq,cs2 ;

   if (debug < 1)
      fprintf(stderr,"rotcofa %9g %9g\n",c,s);
   sc = s*c ;
   ssq = s*s ;
   csq = doub1 - ssq ;
   cs2 = coef[2]*sc ;
   new[0] = coef[0]*csq + coef[1]*ssq - cs2 ;
   new[1] = coef[0]*ssq + coef[1]*csq + cs2 ;
   new[2] = (coef[0]-coef[1])*(sc+sc) + coef[2]*(csq - ssq) ;
   new[3] = coef[3]*c - coef[4]*s ;
   new[4] = coef[3]*s + coef[4]*c ;
   new[5] = coef[5] ;

   for (  j = 0 ; j < 6 ; ++ j )
   {
      coef[j] = new[j] ;
   }
   if (debug < 1)
      fprintf(stderr,"rotcofb %9g %9g %9g %9g %9g %9g\n",
         coef[0],coef[1],coef[2],coef[3],coef[4],coef[5]);
} /* rotcof */
/************************************************/

ellpln(cop,el,cnx,cny,c,x,y,z)
   double cop[6],el[3][3],cnx,cny,c,x,y,z ;
/* 
     find coefs "cop" of projection of ellipse of intersection of 
     plane "cnx,cny,c" with ellipsoid "el" centred on "x,y,z". 
     wrt centre of "n"th ellipsoid 

     calls  shfcof 
     called by chkell 
*/
{
   double x20,y21,cnc ;

   if (debug < 1)
      fprintf(stderr,"ellpln %d %9g %9g %9g %9g %9g %9g\n",
         n,cnx,cny,c,x,y,z );
   cnc = c+cnx*x+cny*y+z ;
   x20 = cnx*el[2][2] - el[0][2] ;
   y21 = cny*el[2][2] - el[1][2] ;
   cop[0] = cnx*(x20 - el[0][2])+el[0][0] ;
   cop[1] = cny*(y21 - el[1][2])+el[1][1] ;
   cop[2] = doub2*(cnx*y21 - cny*el[0][2]+el[0][1]) ;
   cop[3] = doub2*cnc*x20 ;
   cop[4] = doub2*cnc*y21 ;
   cop[5] = el[2][2]*cnc*cnc - doub1 ;
   shfcof(cop, -x, -y) ;
} /* ellpln */
/********************************************/

int ellcut(axx,axy,coef,rterr,theta)
   double axx,axy,coef[6],theta[4],rterr[4] ;
/* 
     find Cohen parameter values at intersections of the
     ellipse centred on the origin having semiaxes
     lengths "axx,axy" aligned with xy axes 
     with the ellipse whose equation is -  

     coef[0]*x**2 + coef[1]*y**2 + coef[2]*x*y
              + coef[3]*x + coef[4]*y + coef[5] = 0 

     called by chkell 
     calls  qudrtc, quartic, sort. 
*/
{
   int quartic();

   int nrts ;
   int k ;
   double a,b,c,d;
   double at,bt,ct,dt,et,rts[4];
   double den,x1,xsq1,x4,xy3,y5,ysq2 ;

   if (debug < 1)
      fprintf(stderr,
        "ellcuta %9g %9g %9g\n        %9g %9g %9g %9g %9g %9g\n",
        maxval,axx,axy,
        coef[0],coef[1],coef[2],coef[3],coef[4],coef[5]);
/* 
     set up coeffs of quartic in tan(theta/2) - 
*/
   x1 = coef[0]*axx ;
   xsq1 = x1*axx ;
   x4 = coef[3]*axx ;
   xy3 = coef[2]*axx*axy ;
   y5 = coef[4]*axy ;
   ysq2 = coef[1]*axy*axy ;
   at = xsq1 - x4 + coef[5] ;
   bt = y5 - xy3 ;
   bt = bt + bt ;
   ct =  -xsq1+ysq2+ysq2+coef[5] ;
   ct = ct+ct ;
   dt = y5+xy3 ;
   dt = dt+dt ;
   et = xsq1+x4+coef[5] ;

   if (at == doub0)
   {
       if (bt == doub0)
       {
          if (ct == doub0)
             nrts = 0;
          else
          {
             nrts = qudrtc(dt/ct,et/ct,rts,
                       (dt/ct)*(dt/ct)-doub4*(et/ct));
             rterr[0] = doub0; rterr[1] = doub0;
             a =bt; b = ct; c = dt; d = et;
          }
       }
       else
          nrts = 0;
   }
   else
   {
      den = doub1/at ;
      a = bt*den; b = ct*den;
      c = dt*den; d = et*den;
      nrts = quartic(a,b,c,d,rts,rterr) ;
/* 
     find chords intersected -  
*/
      if (nrts > 0)
      {
         for ( k = 0 ; k < nrts ; ++ k )
         {
            theta[k] = rts[k] ;
            if (theta[k] > maxval) theta[k] = maxval ;
            if (theta[k] <  -maxval) theta[k] =  -maxval ;
            if (debug < 1)
               fprintf(stderr,
                 "ellcutb %d %9g %9g\n",k,rts[k],theta[k]);
         }
         sort(theta,rterr,nrts) ;
      }
   }
   if (debug < 1)
      fprintf(stderr,"ellcutc %d %9g %9g\n",nrts,rts[0],theta[0]);
   return(nrts);
} /* ellcut */
/*************************************************/

order(j)
int j;
/* 
     finds arcs of outline of ellipsoid "n" that are hidden by
     ellipsoid "j", and adds them into array "appear". 

     called by edhide 
     calls  two0a, two0b,, four0a, four0b,, both 
*/
{
   if (debug < 1)
      fprintf(stderr,"ordera %d %d %d %d %d %9g %9g\n",
         j,n,narcs[n],nrtsa,nrtsb,atheta[0],btheta[0]);
   if ( (nrtsa == 2) && (nrtsb == 0))
   {
      theta[0] = atheta[0]; theta[1] = atheta[1];
      two0a();
   }
   else
   if ( (nrtsa == 0) && (nrtsb == 2))
   {
      theta[0] = btheta[0]; theta[1] = btheta[1];
      two0b();
   }
   else
   if ( (nrtsa == 4) && (nrtsb == 0))
   {
      theta[0] = atheta[0]; theta[1] = atheta[1];
      theta[2] = atheta[2]; theta[3] = atheta[3];
      four0a();
   }
   else
   if ( (nrtsa == 0) && (nrtsb == 4))
   {
      theta[0] = btheta[0]; theta[1] = btheta[1];
      theta[2] = btheta[2]; theta[3] = btheta[3];
      four0b();
   }
   else
   both();

   if  ( ok == FALSE )
   {
      fprintf(stderr,
         "\nERROR edhide  subr order -  snag %d %d %d %d %9g\n",
            nrtsa,nrtsb,n,j,ellj22 );
      ok = FALSE ;
   }
   else
      if (debug < 1) fprintf(stderr,"orderb %d %d %d %d\n",
         nrtsa,nrtsb,n,j);
} /* order */
/*****************************************************/

two0a()
/* 
     finds hidden vals when 2 of 'a' type and 0 of 'b' type 
     intersections. 

     called by order 
     calls  obscur, insert 
*/
{
   int nhere,j ;
   double val[2],val0,val1,tstval ;
/* 
     is infinity in  a hidden val -  
*/
   if (debug < 1)
      fprintf(stderr,"two0a  %9g %9g\n", theta[0],theta[1] );
   val0 = theta[0] - maxval ;
   val1 = theta[1] + maxval ;
   tstval = val0 ;
   if (fabs(tstval) > fabs(val1)) tstval = val1 ;
   val[0] =  - maxval ;
   val[1] = theta[0] ;
   nhere = 2 ;
   obscur(inv2*tstval);
   if (hidden == TRUE) goto lab2 ;
/* 
     arc around infinity is visible. check rest of outline -  
*/
   obscur(inv2*(theta[0]+theta[1]));
   if ( hidden == FALSE ) goto lab4 ;
   val[0] = theta[0] ;
   val[1] = theta[1] ;
   nhere = 1 ;
/* 
     insert the vals -  
*/
lab2:  for (  j = 0 ; j < nhere ; ++ j )
   {
      insert(val[0],val[1],appear,n) ;
      if (ok == FALSE) goto lab4;
      val[0] = theta[1] ;
      val[1] = maxval ;
   }

lab4: ;
} /* two0a */
/*****************************************************/

two0b()
/* 
     finds hidden vals when 2 of 'b' type and 0 of 'a' 
     type of intersections 

     called by order 
     calls  obscur, insert 
*/
{
   int nhere,j ;
   double val[2],val0,val1,tstval ;
/* 
     is infinity in  a hidden val -  
*/
   if (debug < 1)
      fprintf(stderr,"two0b  %9g %9g\n", theta[0],theta[1] );
   val0 = theta[0] - maxval ;
   val1 = theta[1] + maxval ;
   tstval = val0 ;
   if (fabs(tstval) > fabs(val1)) tstval = val1 ;
   val[0] = theta[0] ;
   val[1] = theta[1] ;
   nhere = 1 ;
   obscur(inv2*tstval);
   if ( hidden == FALSE ) goto lab2 ;
/* 
     arc around infinity is hidden. check rest of outline -  
*/
   val[0] =  - maxval ;
   val[1] = maxval ;
   obscur(inv2*(theta[0]+theta[1]));
   if ( hidden == TRUE ) goto lab2 ;
   val[1] = theta[0] ;
   nhere = 2 ;
/* 
     insert the vals -  
*/
lab2:for (  j = 0 ; j < nhere ; ++ j )
   {
      insert(val[0],val[1],appear,n) ;
      if (ok == FALSE) goto lab4;
      val[0] = theta[1] ;
      val[1] = maxval ;
   }
lab4: ;
} /* two0b */
/******************************************************/

four0a()
/* 
     find hidden vals when 4 of 'a' type and 0 of 'b' 
     type of intersections 

     called by order 
     calls  obscur, insert 
*/
{
   double val0,val1,tstval ;

   if (debug < 1)
      fprintf(stderr,"four0a  %9g\n", theta[0]);
   val0 = theta[0] - maxval ;
   val1 = theta[3]+maxval ;
   tstval = val0 ;
   if (fabs(tstval) > fabs(val1)) tstval = val1 ;
   obscur(inv2*tstval);
   if ( hidden == TRUE )
   {
      insert( -maxval,theta[0],appear,n);
      if (ok == FALSE) goto rtrn;
      insert(theta[3],maxval,appear,n) ;
      if (ok == FALSE) goto rtrn;
      obscur(inv2*(theta[1]+theta[2]));
      if (hidden == TRUE) insert(theta[1],theta[2],appear,n);
   }
   else
   {
      obscur(inv2*(theta[0]+theta[1]));
      if (hidden == TRUE)
      {
         insert(theta[0],theta[1],appear,n);
         if (ok == FALSE) goto rtrn;
         obscur(inv2*(theta[2]+theta[3]));
         if (hidden == TRUE)
            insert(theta[2],theta[3],appear,n) ;
            if (ok == FALSE) goto rtrn;
      }
      else
      {
         obscur(inv2*(theta[1]+theta[2]));
         if ( hidden == TRUE )
            insert(theta[1],theta[2],appear,n) ;
            if (ok == FALSE) goto rtrn;
         else
         {
            obscur(inv2*(theta[2]+theta[3]));
            if ( hidden == TRUE )
               insert(theta[2],theta[3],appear,n) ;
               if (ok == FALSE) goto rtrn;
         }
      }
   }
rtrn: ;
} /* four0a */
/******************************************************/

four0b()
/* 
     find hidden vals when 4 of 'b' type and 0 of 'a' 
     type of intersections 

     called by order 
     calls  obscur, insert 
*/
{
   double val0,val1,val[4],tstval ;
   int j ;

   if (debug < 1)
      fprintf(stderr,"four0b  %9g\n",theta[0]);
   val0 = theta[0] - maxval ;
   val1 = theta[3] + maxval ;
   tstval = val0 ;
   if (fabs(tstval) > fabs(val1)) tstval = val1 ;
   obscur(inv2*tstval);
   if (inside != TRUE)
   {
/* 
     vals 0 - 1 & 2 - 3 inside and hidden.
     test 1 - 2 & 3 - 0 : -  
*/
      if ( hidden == TRUE )
      {
         obscur(inv2*(theta[1]+theta[2]));
         if ( hidden == TRUE )
         {
            insert( -maxval,maxval,appear,n) ;
            goto rtrn ;
         }
         val[0] =  - maxval ;
         val[1] = theta[1] ;
         val[2] = theta[2] ;
         val[3] = maxval ;
         goto lab6 ;
      }
      obscur(inv2*(theta[1]+theta[2]));
      if ( hidden == TRUE )
      {
         insert(theta[0],theta[3],appear,n) ;
         goto rtrn ;
      }
      val[0] = theta[0] ;
      val[1] = theta[1] ;
      val[2] = theta[2] ;
      val[3] = theta[3] ;
   }
   else
   {
/* 
     vals 3 - 0 and 1 - 2 inside and hidden.
     test 0 - 1 and 2 - 3 : -  
*/
      obscur(inv2*(theta[0]+theta[1]));
      if ( hidden == TRUE )
      {
         obscur(inv2*(theta[2]+theta[3]));
         if ( hidden == TRUE )
         {
            insert( -maxval,maxval,appear,n) ;
            goto rtrn ;
         }
         val[0] =  -maxval ;
         val[1] = theta[2] ;
         val[2] = theta[3] ;
         val[3] = maxval ;
         goto lab6 ;
      }
      obscur(inv2*(theta[2]+theta[3]));
      if ( hidden == TRUE )
      {
         val[0] = -maxval ;
         val[1] = theta[0] ;
         val[2] = theta[1] ;
         val[3] = maxval ;
      }
      else
      {
         insert( -maxval,theta[0],appear,n) ;
         if (ok == FALSE) goto rtrn;
         val[0] = theta[1] ;
         val[1] = theta[2] ;
         val[2] = theta[3] ;
         val[3] = maxval ;
      }
   }
lab6:  for (  j = 0 ; j < 3 ;  j  +=  2 )
       {
          insert(val[j],val[j+1],appear,n) ;
          if (ok == FALSE) goto rtrn;
       }

rtrn:;
} /* four0b */
/*****************************************************/

both()
/* 
     finds hidden arcs when both a and b types present. 

     called by order 
     calls  insert, obscur, chkrts, allarc 
*/
{
   double arc[3] ;
   double val[10];
   int adj;
   int also;
   int base;
   int basej;
   int class;            /* type of hidden arc arrangement */
   int j,k;
   int lim;
   int next;
   int nrts;
   int nhid ;
   int nscans;
   int scan;
   int top;
   int which;

   if (debug < 1)
      fprintf(stderr,"botha %9g %9g\n",atheta[0],btheta[0]);
   class = -1;
   chkrts();
   if (debug < 1)
      fprintf(stderr,"bothb %9g %9g\n",atheta[0],btheta[0]);
   if (valid == TRUE) goto lab16 ;
   allarc();
   goto lab18 ;

lab16: nhid = 0 ;
   nrts = nrtsa+nrtsb ;
   if (nrtsb > nrtsa) goto lab19 ;
   top = nrtsa ;
   if (nrtsb == 4) top = 2 ;
/* 
     types 2 - 2, 4 - 2, and 4 - 4 - 
*/
   for (  class = 0 ; class < top ; ++ class )
   {
      if (btheta[1] < atheta[class]) goto lab2 ;
   }

   class = top ;
   if (atheta[top-1] < btheta[0]) goto lab2 ;
   class = top+1 ;
   goto lab2 ;
/* 
     type 2 - 4 - 
*/
lab19: for (  class = 0 ; class < 4 ; ++ class )
       {
         if (btheta[class] > atheta[1]) goto lab2 ;
       }

   class = 4 ;
   if (btheta[3] < atheta[0]) goto lab2 ;
   class = 5 ;

lab2: base = b[nrtsb][nrtsa][class];
   nscans = t[base] ;
   if (debug < 1)
      fprintf(stderr,"bothc %d %d %d\n", class,nscans,base );
/* 
     set up values for testing for hidden arcs -  
*/
   base = base - 10 ;
   for ( scan = 1 ; scan <= nscans ; ++ scan )
   {
      base = base+10 ;
      for (  j = 1 ; j <= 8 ; ++ j )
      {
         val[j] = doub0 ;
         basej = base+j ;
         k = t[basej] ;
         if (k == 0) goto lab4 ;
         if (k <= 10) goto lab5 ;
         if (k == 20) goto lab6 ;
         val[j] = btheta[k - 11] ;
         goto lab4 ;

lab6:    val[j] = maxval ;
         goto lab4 ;

lab5:    if (k < 0) goto lab7 ;
         val[j] = atheta[k-1] ;
         goto lab4 ;

lab7:    val[j] =  - maxval ;

lab4: ;
         if (debug < 1) fprintf(stderr,"bothd %d %d %d\n",j,basej,k);
      } /* end j loop */

      if (debug < 1)
         fprintf(stderr,"bothe %d %9g %9g %9g %9g\n",
            scan,val[1],val[2],val[3],val[4]);
/* 
     test each a - b arc -  
*/
      for (  lim = 1 ; lim <= 2 ; ++ lim )
      {
         arc[lim] = val[lim+3] ;
         adj = 4 ;
         also = 1 ;
         next = 3 ;
         if (lim == 1) goto lab13 ;

         adj = 5 ;
         also = 7 ;
         next = 6 ;

lab13: which = next+base ;
         if (debug < 1)
           fprintf(stderr,"bothf %d %d %d %d %d\n",
              lim,adj,also,next,which );
         if (t[which] == 0) goto lab8 ;
/* 
     special for 4th arc of 4 - 4 case - 
*/
         if (nrts != 8) goto lab14 ;
         if (lim != 2) goto lab14 ;
         if (scan != 2) goto lab14 ;
         if ((nhid == 1) || (nhid == 3)) hidden = TRUE;
            else hidden = FALSE;
         goto lab15 ;

lab14: tstval = inv2*(val[next]+val[adj]) ;
         obscur(tstval);

lab15: if ( hidden == FALSE ) goto lab8 ;
         arc[lim] = val[next] ;
         nhid = nhid + 1 ;
         which = also + base ;
         if (t[which] != 0) insert(val[also],val[also+1],appear,n);
         if (ok == FALSE) goto lab18;
lab8: ;
      } /* end lim loop */
      insert(arc[1],arc[2],appear,n);
      if (ok == FALSE) goto lab18;
lab3: ;
   } /* end scan loop */

lab18: ;
} /* both */
/**************************************/

chkrts()
/* 
     check if ordering of a and b type intersections is valid 
     and if separation exceeds their errors. 

     called by both 
*/
{
   int count,apntr,bpntr,j,nrts,type[9] ;
   double val[9],verr[9],toterr ;

   valid = TRUE ;
   nrts = nrtsa+nrtsb ;
   apntr = 0 ;
   bpntr = 0 ;
   if (debug < 1)
      fprintf(stderr,"chkrtsa %d %d %d\n",nrtsa,nrtsb,nrts);
/* 
     set up array of types in merged sorted order -  
*/
   for ( j = 0 ; j < nrts ; ++ j )
   {
      if (bpntr >= nrtsb) goto lab2 ;
      if (apntr >= nrtsa) goto lab6 ;
      if (atheta[apntr] < btheta[bpntr]) goto lab2 ;
/* 
     copy b -  
*/
lab6: type[j] = 2 ;
      val[j] = btheta[bpntr] ;
      verr[j] = berr[bpntr] ;
      bpntr = bpntr+1 ;
      goto lab1 ;
/* 
     copy a -  
*/
lab2: type[j] = 1 ;
      val[j] = atheta[apntr] ;
      verr[j] = aerr[apntr] ;
      apntr = apntr+1 ;
lab1: ;
   } /* end j loop */
/* 
     check count of adjacent types -  
*/
   count =  -8 ;
   for ( j = 1 ; j < nrts ; ++ j )
   {
      ++ count;
      if (type[j] != type[j - 1])
      {
         if ((count > 0) && (count%2 == 1))
               valid = FALSE;
         count = 0;
      }
      if (debug < 1)
      fprintf(stderr,"chkrtsb %d %d %d %d %9g %d %9g\n",
            j,count,valid,type[j-1],val[j-1],type[j],val[j]);
   } /* end j loop */
/* 
     check errors against separation -  
*/
   for ( j = 0 ; j < nrts ; ++ j )
   {
      toterr = doubtol;
      if (val[j] >  maxval) val[j] =  maxval ;
      if (val[j] < -maxval) val[j] = -maxval ;
      if (j != 1)
      {
         toterr = doub2*(verr[j-1] + verr[j] + doubtol);
         if ((val[j] - val[j-1]) < toterr) valid = FALSE;
      }
      if (debug < 1)
         fprintf(stderr,"chkrtsc %d %d %9g %9g %9g %d %d\n",
            j,type[j],val[j],verr[j],toterr,valid,nrts);
   } /* end j loop */
} /* chkrts */
/****************************************************/

allarc()
/* 
     test all arcs of "n"th outline for obscuration. 

     called by both 
     calls  obscur, insert 
*/
{
   int apntr,bpntr;
   int j ;
   int top;
   double val[11] ;

   if(debug < 1)
      fprintf(stderr,"allarc %d %d\n",nrtsa,nrtsb);
   top = 1+nrtsa+nrtsb ;
   val[1] =  -maxval ;
   val[top+1] = maxval ;

   apntr = 0 ;
   bpntr = 0 ;

   for (  j = 2 ; j <= top ; ++ j )
   {
      if (bpntr >= nrtsb) goto lab2 ;
      if (apntr >= nrtsa) goto lab4 ;
      if (atheta[apntr] < btheta[bpntr]) goto lab2 ;
/* 
     current b is smaller -  
*/
lab4: val[j] = btheta[bpntr] ;
      bpntr = bpntr+1 ;
      goto lab1 ;
/* 
   current a is smaller -  
*/
lab2: val[j] = atheta[apntr] ;
      apntr = apntr+1 ;
lab1: ;
   }
   for (  j = 1 ; j <= top ; ++ j )
   {
      obscur(inv2*(val[j]+val[j+1]));
      if ( hidden == TRUE ) insert(val[j],val[j+1],appear,n) ;
      if (ok == FALSE) goto rtrn;
   }
rtrn: ;
} /* allarc */
/*******************************************/

obscur(point)
   double point;
/* 
     is point on "n"th outline obscured by "j"th ellipsoid. 

  input parameters -  
     point - tangent of Cohen parameter on point on "n"th outline 
     cj - coefficients of plane of "j"th outline'
             wrt centre of "n"th 
     cn - coefficients of plane of "n"th outline'
             wrt its own centre 
     xstrt - coords of start of plot of "n"th outline'
             wrt its centre 
     xm - coefficients of sine of Cohen parameter 
     debug - 0 for lots of diagnostics 
     err - device number for output of diagnostics 
     coj - coeffs of "j"th outline wrt centre of "n"th

   output values -  
     hidden - true if point on "n"th outline'
             hidden by "j"th ellipsoid 
     inside - true if point on "n"th outline'
             is inside "j"th ellipsoid 

     called by two0a, two0b, four0a, four0b, both, edhide, allarc 
*/
{
   double x,y,zn,discrt,zj,st,ct,den,tsq,zell ;
   double norm ;

   if (debug < 1)
   {
      fprintf(stderr,"obscura  %9g %9g %9g %9g %9g %9g\n",
         point,ellj22,xstrt[0],xstrt[1],xm[0],xm[1]);
      fprintf(stderr,"     %9g %9g %9g %9g %9g %9g\n",
         cn[0],cn[1],cn[2],cj[0],cj[1],cj[2]);
      fprintf(stderr,"     %9g %9g %9g %9g %9g %9g\n",
         coj[0],coj[1],coj[2],coj[3],coj[4],coj[5]);
   }
   norm = doubtol*coj[5] ;
   if (norm < doub0) norm =  - norm ;
/* 
     find x,y,zn, and zj corresponding to "point" on "n"th outline-
*/
   tsq = point*point ;
   den = doub1/(doub1 + tsq) ;
   ct = (doub1 - tsq)*den ;
   st =  -point*(den+den) ;
   x = xm[0]*st + xstrt[0]*ct ;
   y = xm[1]*st + xstrt[1]*ct ;

   zn =  - cn[2] - cn[0]*x - cn[1]*y ;
   discrt = x*(coj[0]*x+coj[3]) + y*(coj[1]*y+coj[2]*x+coj[4])
            + coj[5] ;
   if (ellj22 > doub0) discrt =  -discrt ;
   if (debug < 1)
      fprintf(stderr,"obscurb %9g %9g %9g %9g\n", x,y,zn,discrt );
   zj =  -cj[2] - cj[0]*x - cj[1]*y ;
   if (debug < 1)
      fprintf(stderr,"obscurc %9g\n", zj );
/* 
   rather than testing -  
     (zn - zj) < sqrt(discrt/ellj22) 
   test -  
     ellj22*(zn - zj)*(zn - zj) < discrt 
   but avoid overflow by multiplying in stages using abs(ellj22) < 1 
*/
   zell = (zj - zn)*ellj22 ;
   zell = zell*(zj - zn) ;
   if (ellj22 < doub0) zell =  - zell ;
   if  (( zell  <  discrt ) && ( norm  <  discrt ))
     inside = TRUE; else inside = FALSE;
   hidden = FALSE;
   if (( zj  <  zn ) && ( norm  <  discrt ))
     hidden = TRUE;
   if (inside == TRUE ) hidden = TRUE;

   if (debug < 1)
      fprintf(stderr,"obscurd  %9g %9g %9g %d %d %d\n",
        norm,zell,ellj22,hidden,inside,TRUE);
} /* obscur */
/****************************************/

insert(bot,top,a,n)
   int n;
   double a[EMAX][AMAX][2],bot,top ;
/* 
     inserts an arc (bot,top) into list of narcs[n] arcs in array a. 

     uses separate sections depending on whether list of
     hidden arcs expands, stays the same length or contracts. 

     D.Herbison - Evans     May 1978               ANSI Fortran 

   input parameters -  
     a - array containing previous list of hidden arcs, in 
         ascending order, i.e. -  
         a[n][j][0] <= a[n][j][1] <= a[n][j+1][0] for 1 <= j <= n - 1 
     bot,top - lower and upper limits of new hidden arc which 
               is to be inserted into array a. 
     narcs[n] - number of hidden arcs stored in array a. 

   output parameters -  
     a - updated ordered list of hidden arcs. 
     narcs[n] - updated number of hidden arcs in array a. 
     ok - set to false if a problem encountered 

   variables -  
     j - counter through updated list. 
     jp1 - index of start of changes to list. 
     k - counter through old list seeking end of changes. 
     m - counter for copying unaltered arcs beyond changes. 
*/
{
   int j,k,m,jp1 ;
/* 
     initialise variables and look for sillies -  
*/
   if (debug < 1)
      fprintf(stderr,"inserta %s %d %9g %9g %9g %9g\n",
         ename[n],narcs[n],bot,top,a[n][0][0],a[n][narcs[n]-1][1]);
   j = 0 ;
   k = 0 ;
   if (bot == top) goto rtrn ;
   if (bot > top)
   {
      fprintf(stderr,"\nERROR edhide insert ell %d, %f > %f\n",
         n,bot,top);
      ok = FALSE;
      goto rtrn ;
   }
   if (narcs[n] < 1)
   {
      fprintf(stderr,"\nERROR edhide ell %d, narcs %d\n",n,narcs[n]);
      ok = FALSE;
      goto rtrn ;
   }
   if (top > a[n][narcs[n]-1][1]) goto rtrn ;
/* 
     find out where list alterations start -  
*/
   for (  j = 0 ; j < narcs[n] ; ++ j )
   {
      if (bot <= a[n][j][1]) goto change ;
   }
/* 
     error -  
*/
   fprintf(stderr,"\nERROR edhide ell %d, bot %f\n",n,bot);
   ok = FALSE;
   goto rtrn ;
/* 
     find whether list in a must expand, stay same, or contract -  
*/
change: jp1 = j+1 ;
   if (top < a[n][j][0]) goto expand ;
   if (jp1 == narcs[n]) goto same ;
   if (top < a[n][jp1][0]) goto same ;
/* 
     contract -  bot to top spans one or more whole visible arcs. 
*/
   if (debug < 1) fprintf(stderr,"   contract %d %9g %9g %9g\n",
       j,a[n][j][0],a[n][j][1],a[n][jp1][0]);
   if (a[n][j][0] > bot)  a[n][j][0] = bot ;
/* 
     find where the new hidden arc ends -  
*/
   for (  k = jp1 ; k < narcs[n] ; ++ k )
   {
      if (top < a[n][k][0]) goto gotit ;
   }
/* 
     special case -  hit the ceiling -  
*/
   k = narcs[n]+1 ;
   narcs[n] = jp1 ;
/* 
     insert new top -  
*/
gotit: a[n][j][1] = a[n][k-1][1] ;
   if (top > a[n][j][1]) a[n][j][1] = top;
   if (k > narcs[n]) goto rtrn ;
/* 
     move other entries down -  
*/
   for ( m = k ; m < narcs[n] ; ++ m )
   {
      j = j+1 ;
      a[n][j][0] = a[n][m][0] ;
      a[n][j][1] = a[n][m][1] ;
   }
   narcs[n] = j+1 ;
   goto rtrn ;
/* 
     stay same length -  bot to top spans only 1 hidden arc -  
*/
same: if (debug < 1) fprintf(stderr,"   same %d %9g %9g\n",
         j,a[n][j][0],a[n][j][1]);
   if (a[n][j][0] > bot) a[n][j][0] = bot ;
   if (a[n][j][1] < top) a[n][j][1] = top ;
   goto rtrn ;
/* 
     expand, so move all up 1 place for insertion at j -  
*/
expand: if (debug < 1) fprintf(stderr,"   expand %d %9g %9g\n",
           j,a[n][j][0],a[n][j][1]);
   if ( (narcs[n]+1) > AMAX)
   {
      fprintf(stderr,
         "\nERROR edhide insert snag  ell %d, narcs %d > %d\n",
         n,narcs[n],AMAX);
      ok = FALSE;
      goto rtrn ;
   }
   for ( m = narcs[n] ; m > j ; -- m )
   {
      a[n][m][0] = a[n][m-1][0] ;
      a[n][m][1] = a[n][m-1][1] ;
   }
/* 
     insert new hidden arc -  
*/
   a[n][j][0] = bot ;
   a[n][j][1] = top ;
   narcs[n] = narcs[n]+1 ;

rtrn: ;
   if (ok == FALSE) debug = -1;
   if (debug < 1)
   {
      fprintf(stderr,"insertb %d %d %9g %9g\n",
         n,narcs[n],bot,top);
      for (j = 0; j < narcs[n]; ++j)
        fprintf(stderr,"insertc %d %9g %9g\n",
           j,a[n][j][0],a[n][j][1]);
   }
} /* insert */
/**********************************************/

sort(a,b,nocc)
   int nocc;
   double a[],b[] ;
/* 
     put occupied entries of a and b into ascending order of a. 
    ( uses bubble sort ) 

     called by ellcut 
*/
{
   double temp ;
   int j,k,noccm1 ;

   if (debug < 1)
   {
      for (j = 0; j < nocc; ++j)
         fprintf(stderr,"sort %9g %9g %d\n",a[j],b[j],nocc);
   }
   noccm1 = nocc - 1 ;
   for (  j = 0 ; j < noccm1 ; ++ j )
   {
      for (  k = j ; k < nocc ; ++ k )
      {
         if (a[j] > a[k])
         {
            temp = a[k] ;
            a[k] = a[j] ;
            a[j] = temp ;
            temp = b[k] ;
            b[k] = b[j] ;
            b[j] = temp ;
          }
      }
   }
} /* sort */
/**********************************************/

int qudrtc(b,c,rts,dis)
   double b,c,rts[4],dis ;
/* 
     solve the quadratic equation - 

         x**2+b*x+c = 0 

     called by  quartic, ferrari, neumark, ellcut 
*/
{
   int j,nquad;
   double rtdis ;
   double ans[2] ;

   if (debug < 1)
      fprintf(stderr,"qudrtca %8g %8g %8g\n",b,c,dis);
   if (dis >= doub0)
   {
      nquad = 2 ;
      rtdis = sqrt(dis) ;
      if (b > doub0) rts[0] = ( -b - rtdis)*inv2 ;
         else rts[0] = ( -b + rtdis)*inv2 ;
      if (rts[0] == doub0) rts[1] =  -b ;
      else rts[1] = c/rts[0] ;
   }
   else
   {
      nquad = 0;
      rts[0] = doub0 ;
      rts[1] = doub0 ;
   }
   if (debug < 1)
   {
      if (nquad > 0)
      {
         ans[0] = (rts[0]+b)*rts[0]+c ;
         ans[1] = (rts[1]+b)*rts[1]+c ;
         fprintf(stderr,"qudrtcb %9g %9g  %9g %9g\n",
            rts[0],ans[0],rts[1],ans[1]);
      }
   }
   return(nquad);
} /* qudrtc */
/**************************************************/

double cubic(p,q,r)
double p,q,r;
/* 
     find the lowest real root of the cubic - 
       x**3 + p*x**2 + q*x + r = 0 

   input parameters - 
     p,q,r - coeffs of cubic equation. 

   output- 
     cubic - a real root. 

   global constants -
     pi - 3.14159 etc. 
     rt3 - sqrt(3) 
     inv3 - 1/3 
     doubmax - square root of largest number held by machine 

     method - 
     see D.E. Littlewood, "A University Algebra" pp.173 - 6 

     Charles Prineas   April 1981 

     called by  neumark.
     calls  acos3 
*/
{
   int j ;
   double po3,po3sq,po3cu,qo3,po3q;
   double uo3,u2o3,uo3sq4,uo3cu4 ;
   double v,vsq,wsq ;
   double m,mcube,n;
   double muo3,s,scube,t,cosk,sinsqk ;
   double root;
   double ans ;
   double curoot();
   double acos3();

   if (debug < 1)
      fprintf(stderr,"cubica %9g %9g %9g\n", p,q,r );
   m = doub0;
   if (p > doubmax) goto lab90 ;
   if (p <  - doubmax) goto lab90 ;
   if (q > doubmax) goto lab91 ;
   if (q <  - doubmax) goto lab91 ;
   if (r > doubmax) goto lab92 ;
   if (r <  - doubmax) goto lab92 ;
   root = doub0;
   ans = doub0;
   wsq = doub0 ;
   cosk = doub0 ;
   uo3 = doub0 ;
   v = doub0;
   s = doub0;
   t = doub0;
   uo3cu4 = doub0 ;
   po3 = p*inv3 ;
   po3q = po3*q ;
   po3sq = po3*po3 ;
   if (po3sq > doubmax) goto lab90 ;
   po3cu = po3*po3sq ;
   v = r+po3*(po3sq  + po3sq - q) ;
   if (v > doubmax) goto lab90 ;
   if (v <  - doubmax) goto lab90 ;
   vsq = v*v ;
   qo3 = q*inv3 ;
   uo3 = qo3 - po3sq ;
   u2o3 = uo3+uo3 ;
   if (u2o3 > doubmax) goto lab94 ;
   if (u2o3 <  -doubmax) goto lab94 ;
   uo3sq4 = u2o3*u2o3 ;
   if (uo3sq4 > doubmax) goto lab94 ;
   uo3cu4 = uo3sq4*uo3 ;
   wsq = uo3cu4+vsq ;
   if (debug < 1)
      fprintf(stderr,"cubicb %9g %9g %9g\n",uo3cu4,vsq,wsq);
   if (uo3cu4 > doub0) goto lab8 ;
   if (wsq < doub0) goto lab1 ;
/* 
     cubic has one real root 
*/
lab8: if (debug < 1) fprintf(stderr,"cubicc %9g\n",wsq);
   if (v <= doub0) mcube = ( -v+sqrt(wsq))*inv2 ;
   if (v  > doub0) mcube = ( -v-sqrt(wsq))*inv2 ;
   m = curoot(mcube) ;
   if (m != doub0) n =  - uo3/m ; else n = doub0;
   root = m + n - po3 ;
   goto lab3 ;
/* 
     cubic has three real roots 
*/
lab1: if (uo3 >= doub0) goto lab2 ;
   muo3 = -uo3;
   if (debug < 1) fprintf(stderr,"cubicd %9g\n",muo3);
   s = sqrt(muo3) ;
   scube = s*muo3;
   t =  - v/(scube+scube) ;
   cosk = acos3(t) ;
   if (po3 < doub0)
      root = (s+s)*cosk - po3;
   else
   {
      sinsqk = doub1 - cosk*cosk ;
      if (sinsqk < doub0) sinsqk = doub0 ;
      root = s*( - cosk - rt3*sqrt(sinsqk)) - po3 ;
   }
   goto lab3 ;
/* 
     cubic has multiple root -  
*/
lab2: root = curoot(v) - po3 ;
   goto lab3 ;
/* 
     overflow problems -  

     p or v too big -  
*/
lab90: root =  - p ;
   goto lab3 ;
/* 
     q too large -  
*/
lab91: if (q > doub0) root =  - r/q ;
   if (q <= doub0) root =  - sqrt(fabs(q)) ;
   goto lab3 ;
/* 
     r too big -  
*/
lab92: root =  - curoot(r) ;
   goto lab3 ;
/* 
     p too big -  
*/
lab94: if (p == doub0) goto lab91 ;
   root =  - q/p ;
/* 
     finish off -  
*/
lab3: ;
   if (debug < 1)
   {
      ans = 0 ;
      if ((root >  - doubmax)&&(root < doubmax)) ;
           ans = r+root*(q+root*(p+root)) ;
      fprintf(stderr,"cubice %9g %9g %9g %9g %9g\n",
         root,ans,wsq,cosk,uo3);
   }
   return(root);
} /* cubic */
/***************************************/

double acos3(x)
   double x ;
/* 
     find cos(acos(x)/3) 
    
     Don Herbison-Evans   16/7/81 

     called by cubic . 
*/
{
   double value;

   value = cos(acos(x)*inv3);
   return(value);
} /* acos3 */
/***************************************/

double curoot(x)
   double x ;
/* 
     find cube root of x.
 
     Don Herbison-Evans   30/1/89 

     called by cubic . 
*/
{
   double value;
   double absx;
   int neg;

   neg = FALSE;
   absx = x;
   if (x < doub0)
   {
      absx = -x;
      neg = TRUE;
   }
   value = exp( log(absx)*inv3 );
   if (neg == TRUE) value = -value;
   return(value);
} /* curoot */
/****************************************************/

int quartic(a,b,c,d,rts,rterr)
double a,b,c,d,rts[4],rterr[4];
/*
   Solve quartic equation using either
   quadratic, Ferrari's or Neumark's algorithm.

   called by 
   calls  qudrtc, ferrari, neumark.

     21 Jan 1989  Don Herbison-Evans
*/
{
   int qudrtc(),ferrari(),neumark();
   int j,k,nq,nr;
   double odd, even;
   double roots[4];

   if (debug < 1)
      fprintf(stderr,"quartica %9g %9g %9g %9g\n",a,b,c,d);
   if (a < doub0) odd = -a; else odd = a;
   if (c < doub0) odd -= c; else odd += c;
   if (b < doub0) even = -b; else even = b;
   if (d < doub0) even -= d; else even += d;
   if (odd < even*doubtol)
   {
      nq = qudrtc(b,d,roots,b*b-doub4*d);
      j = 0;
      for (k = 0; k < nq; ++k)
      {
         if (roots[k] > doub0)
         {
            rts[j] = sqrt(roots[k]);
            rts[j+1] = -rts[j];
            ++j; ++j;
         }
      }
      nr = j;
   }
   else
   {
      if (a < doub0) k = 1; else k = 0;
      if (b < doub0) k += k+1; else k +=k; 
      if (c < doub0) k += k+1; else k +=k; 
      if (d < doub0) k += k+1; else k +=k; 
      if (debug < 1) fprintf(stderr,"quarticb %d\n",k);
      switch (k)
      {
              case 0 : nr = neumark(a,b,c,d,rts) ; break;
              case 1 : nr = neumark(a,b,c,d,rts) ; break;
              case 2 : nr = neumark(a,b,c,d,rts) ; break;
              case 3 : nr = ferrari(a,b,c,d,rts) ; break;
              case 4 : nr = ferrari(a,b,c,d,rts) ; break;
              case 5 : nr = neumark(a,b,c,d,rts) ; break;
              case 6 : nr = ferrari(a,b,c,d,rts) ; break;
              case 7 : nr = ferrari(a,b,c,d,rts) ; break;
              case 8 : nr = neumark(a,b,c,d,rts) ; break;
              case 9 : nr = ferrari(a,b,c,d,rts) ; break;
              case 10 : nr = neumark(a,b,c,d,rts) ; break;
              case 11 : nr = neumark(a,b,c,d,rts) ; break;
              case 12 : nr = ferrari(a,b,c,d,rts) ; break;
              case 13 : nr = neumark(a,b,c,d,rts) ; break;
              case 14 : nr = ferrari(a,b,c,d,rts) ; break;
              case 15 : nr = ferrari(a,b,c,d,rts) ; break;
      }
   }
   if (debug < 1) fprintf(stderr,"quarticc %d\n",nr);
   errors(a,b,c,d,rts,rterr,nr);
   return(nr);
} /* quartic */
/*****************************************/

int ferrari(a,b,c,d,rts)
   double a,b,c,d,rts[4];
/* 
     solve the quartic equation - 

   x**4 + a*x**3 + b*x**2 + c*x + d = 0 

   called by quartic
   calls     cubic, qudrtc.

     input - 
   a,b,c,e - coeffs of equation. 

     output - 
   nquar - number of real roots. 
   rts - array of root values. 

     method :  Ferrari - Lagrange
     Theory of Equations, H.W. Turnbull p. 140 (1947)

     calls  cubic, qudrtc 
*/
{
   double cubic();
   int qudrtc();

   int k,nquar,n1,n2 ;
   double asq,y;
   double v1[4],v2[4] ;
   double p,q,r ;
   double e,f,esq,fsq,ef ;
   double g,gg,h,hh;

   if (debug < 1)
      fprintf(stderr,"ferrari coeffs %9g %9g %9g %9g\n",a,b,c,d);
   nquar = 0;
   for ( k = 0 ; k < 4 ; ++ k )
   {
      rts[k] = doub0 ;
   }
   asq = a*a;
   p = b ;
   q = a*c-doub4*d ;
   r = asq*d + c*c - doub4*b*d ;
   y = cubic(p,q,r) ;
   esq = inv4*asq - b - y;
   fsq = inv4*y*y - d;
   ef = -(inv4*a*y + inv2*c);
   if (debug < 1)
      fprintf(stderr,"ferraria %9g %9g %9g\n",esq,fsq,ef);
   if ( ((a > doub0)&&(y > doub0)&&(c > doub0))
     || ((a > doub0)&&(y < doub0)&&(c < doub0))
     || ((a < doub0)&&(y > doub0)&&(c < doub0))
     || ((a < doub0)&&(y < doub0)&&(c > doub0))
     ||  (a == doub0)||(y == doub0)||(c == doub0)
   )
/* use ef - */
   {
      if ((b < doub0)&&(y < doub0)&&(esq > doub0))
      {
         if (debug < 1) fprintf(stderr,"using esq and ef\n");
         e = sqrt(esq);
         f = ef/e;
      }
      else if ((d < doub0) && (fsq > doub0))
      {
         if (debug < 1) fprintf(stderr,"using fsq and ef\n");
         f = sqrt(fsq);
         e = ef/f;
      }
      else
      {
         if (debug < 1) fprintf(stderr,"using esq and fsq\n");
         if (esq > doub0) e = sqrt(esq); else e = doub0;
         if (fsq > doub0) f = sqrt(fsq); else f = doub0;
         if (ef < doub0) f = -f;
      }
   }
   else
   {
      if (debug < 1) fprintf(stderr,"not using ef\n");
      if (esq < doub0) e = doub0; else e = sqrt(esq);
      if (fsq < doub0) f = doub0; else f = sqrt(fsq);
      if (ef < doub0) f = -f;
   }
/* note that e >= doub0 */
   g = inv2*a - e;
   gg = inv2*a + e;
   if ( ((b > doub0)&&(y > doub0))
     || ((b < doub0)&&(y < doub0)) )
   {
      if (( a > doub0) && (e != doub0)) g = (b + y)/gg;
         else if (e != doub0) gg = (b + y)/g;
   }
   if ((y == doub0)&&(f == doub0))
   {
      h = doub0;
      hh = doub0;
   }
   else if ( ((f > doub0)&&(y < doub0))
          || ((f < doub0)&&(y > doub0)) )
   {
      hh = -inv2*y + f;
      h = d/hh;
   }
   else
   {
      h = -inv2*y - f;
      hh = d/h;
   }
   n1 = qudrtc(gg,hh,v1, gg*gg - doub4*hh) ;
   n2 = qudrtc(g,h,v2, g*g - doub4*h) ;
   nquar = n1+n2 ;
   rts[0] = v1[0] ;
   rts[1] = v1[1] ;
   rts[n1] = v2[0] ;
   rts[n1+1] = v2[1] ;
   if (debug < 1)
      fprintf(stderr,"ferrarib %d %9g %9g %9g %9g %9g\n",
         nquar,esq,fsq,ef,e,f);
   return(nquar);
} /* ferrari */
/*****************************************/

int neumark(a,b,c,d,rts)
   double a,b,c,d,rts[4];
/* 
     solve the quartic equation - 

   x**4 + a*x**3 + b*x**2 + c*x + d = 0 

   called by quartic
   calls     cubic, qudrtc.

     input parameters - 
   a,b,c,e - coeffs of equation. 
   debug   - zero or less if diagnostics required. 

     output parameters - 
   nquar - number of real roots. 
   rts - array of root values. 

     method -  
     S. Neumark 

     Solution of Cubic and Quartic Equations - Pergamon 1965 
        translated to C with help of Shawn Neely

*/
{
   int k,nquar,n1,n2 ;

   int qudrtc();
   double cubic();

   double y,g,gg,h,hh,gdis,gdisrt,hdis,hdisrt,g1,g2,h1,h2 ;
   double bmy,gerr,herr,y4,d4,bmysq ;
   double v1[4],v2[4] ;
   double asq,bsq,acd ;
   double p,q,r ;
   double hmax,gmax ;

   if (debug < 1)
      fprintf(stderr,"neumarka  %9g %9g %9g %9g\n", a,b,c,d );
   nquar = 0 ;
   g = doub0 ;
   gg = doub0 ;
   h = doub0 ;
   hh = doub0 ;
   gdisrt = doub0 ;
   hdisrt = doub0 ;
   g2 = doub0 ;
   h2 = doub0 ;
   for (  k = 0 ; k < 4 ; ++ k )
   {
      rts[k] = doub0 ;
   }
   asq = a*a ;
   bsq = b*b ;
   acd = a*c - doub4*d ;
   p =  - (b+b) ;
   q = bsq+acd ;
   r = (c - a*b)*c+asq*d ;
   y = cubic(p,q,r) ;

   bmy = b - y ;
   y4 = y*doub4 ;
   d4 = d*doub4 ;
   bmysq = bmy*bmy ;
   gdis = asq - y4 ;
   hdis = bmysq - d4 ;
   if (gdis < doub0) gdis = doub0 ;
   if (hdis < doub0) hdis = doub0 ;
   g1 = a*inv2 ;
   h1 = bmy*inv2 ;
   if (y < doub0) goto lab1 ;
   if ((b >= doub0)&&(d <= doub0)) goto lab2 ;
   gerr = asq+y4 ;
   herr = hdis ;
   if (d > doub0) herr = bmysq+d4 ;
   if (herr*gdis <= gerr*hdis) goto lab2 ;

lab1: gdisrt = sqrt(gdis) ;
   g2 = gdisrt*inv2 ;
   if (gdisrt != doub0) h2 = (a*h1 - c)/gdisrt ;
     else h2 = doub0;
   goto lab3 ;

lab2: if (hdis <= doub0) goto lab4 ;
   hdisrt = sqrt(hdis) ;
   h2 = hdisrt*inv2 ;
   if (hdisrt != doub0) g2 = (a*h1 - c)/hdisrt ;
/* 
     note that in the following, the tests generate non - zero 
     denominators -  
*/
lab3: h = h1 - h2 ;
   hh = h1+h2 ;
   hmax = hh ;
   if (hmax < doub0) hmax =  - hmax ;
   if (hmax < h) hmax = h ;
   if (hmax <  - h) hmax =  - h ;
   if ((h1 > doub0)&&(h2 > doub0)) h = d/hh ;
   if ((h1 < doub0)&&(h2 < doub0)) h = d/hh ;
   if ((h1 > doub0)&&(h2 < doub0)) hh = d/h ;
   if ((h1 < doub0)&&(h2 > doub0)) hh = d/h ;
   if (h > hmax) h = hmax ;
   if (h <  - hmax) h =  - hmax ;
   if (hh > hmax) hh = hmax ;
   if (hh <  - hmax) hh =  - hmax ;

   g = g1 - g2 ;
   gg = g1+g2 ;
   gmax = gg ;
   if (gmax < doub0) gmax =  - gmax ;
   if (gmax < g) gmax = g ;
   if (gmax <  - g) gmax =  - g ;
   if ((g1 > doub0)&&(g2 > doub0)) g = y/gg ;
   if ((g1 < doub0)&&(g2 < doub0)) g = y/gg ;
   if ((g1 > doub0)&&(g2 < doub0)) gg = y/g ;
   if ((g1 < doub0)&&(g2 > doub0)) gg = y/g ;
   if (g > gmax) g = gmax ;
   if (g <  - gmax) g =  - gmax ;
   if (gg > gmax) gg = gmax ;
   if (gg <  - gmax) gg =  - gmax ;

   n1 = qudrtc(gg,hh,v1, gg*gg - doub4*hh) ;
   n2 = qudrtc(g,h,v2, g*g - doub4*h) ;
   nquar = n1+n2 ;
   rts[0] = v1[0] ;
   rts[1] = v1[1] ;
   rts[n1] = v2[0] ;
   rts[n1+1] = v2[1] ;

lab4: if (debug < 1)
      fprintf(stderr,"neumarkb %d %9g %9g %9g %9g %9g %9g %9g %9g\n",
         nquar,gdis,gdisrt,gerr,hdis,g1,g2,h1,h2);
   return(nquar);
} /* neumark */
/****************************************************/

errors(a,b,c,d,rts,rterr,nrts)
double a,b,c,d,rts[4],rterr[4];
int nrts;
/*
   find the errors

   called by quartic.
*/
{
   int k;
   double deriv,test;
   double fabs(),sqrt(),curoot();

   if (nrts > 0)
   {
      for (  k = 0 ; k < nrts ; ++ k )
      {
         test = (((rts[k]+a)*rts[k]+b)*rts[k]+c)*rts[k]+d;
         if (test == doub0) rterr[k] = doub0;
         else
         {
            deriv =
               ((doub4*rts[k]+doub3*a)*rts[k]+doub2*b)*rts[k]+c;
            if (deriv != doub0)
               rterr[k] = fabs(test/deriv);
            else
            {
               deriv = (doub12*rts[k]+doub6*a)*rts[k]+doub2*b;
               if (deriv != doub0)
                   rterr[k] = sqrt(fabs(test/deriv)) ;
               else
               {
                  deriv = doub24*rts[k]+doub6*a ;
                  if (deriv != doub0)
                     rterr[k] = curoot(fabs(test/deriv));
                  else
                     rterr[k] = sqrt(sqrt(fabs(test)/doub24));
               }
            }
         }
         if (debug < 1)
            fprintf(stderr,"errorsa  %d %9g %9g\n",
               k,rts[k],rterr[k]);
      }
   }
   else if (debug < 1) fprintf(stderr,"errors ans: none\n");
} /* errors */
/********************************************/

edither(figure)
int figure;
/*
   scan input image and quantise it

   called by dopic
   calls start, quantise.
*/
{
   int bits[XMAX][XMAX];
   int row[XMAX][2];
   int x,y;

   if (debug <= 0)
       fprintf(stderr,"edithera %d\n",figure);
   start(figure);
/*
      get 1st row -
*/
   for ( x = 0; x < width ; x++)
   {
      row[x][1] = piccy[0][x];
      row[x][0] = row[x][1];
   }
/*
      get rest of rows, and quantise them -
*/
   for ( y = 1; y < height ; y++)
   {
      for ( x = 0; x < width ; x++)
      {
         row[x][0] = row[x][1];
         row[x][1] = piccy[y][x];
         if (debug <= 0)
            fprintf(stderr,"editherb %d %d %d %d %d\n",
               figure,x,y,row[x][1],row[x][0]);
      }
      quantise(bits,row,figure,y);
   }
/*
      do last row -
*/
   for ( x = 0; x < width ; x++)
      row[x][0] = row[x][1];
   quantise(bits,row,figure,height-1);
/*
   copy them back -
*/
   for ( y = 1; y < height ; y++)
   {
      for ( x = 0; x < width ; x++)
      {
         piccy[y][x] = bits[y][x];
      }
   }
} /* edither */
/**************************************************/

quantise(bits,row,figure,y)
int bits[XMAX][XMAX];
int figure;
int y,row[XMAX][2];
/*
   run across row of row array

   called by edither
*/
{
   static int p3 = 120;
   static int p4 = 16;
   static int p5 = 120;
   int random();
   double c3,c4,c5;
   double dt;
   int phalf;
   int ra;
   int t;
   int x;
/*
   scan across the picture-
*/
   phalf = pmax/2;
   c3 = (double)p3/(double)pmax;
   c4 = (double)p4/(double)pmax;
   c5 = (double)p5/(double)pmax;
   if (debug <= 0)
       fprintf(stderr,"quantisea %d %d %9g %9g %9g %d\n",
                 figure,pmax,c3,c4,c5,thresh);
   for (x = 0; x < width; x ++)
   {
      t = row[x][0];
      if (figure == 9)
      {
         ra = random(figure,x,y)-phalf;
         t += ra/2;
         if (debug <= 0)
            fprintf(stderr,"quantiseb  %d %d %d %d\n",
               piccy[y-1][x],row[x][0],ra,t);
      }
      if (t > thresh) bits[y][x] = pmax;
         else bits[y][x] = 0;
      dt = (double)row[x][0] - (double)bits[y][x];
      if (figure == 8)
      {
         row[x][1] += (int)(dt*c3);
         if (x < (width-1))
         {
            row[x+1][1] += (int)(dt*c4);
            row[x+1][0] += (int)(dt*c5);
         }
      }
      else 
      if (figure != 9)
         fprintf(stderr,"snag in quantise: %d\n",
            figure);
      if (debug <= 0)
         fprintf(stderr,"quantisec %d %d %9g %d %d %d\n",
                     x,y,dt,t,row[x][0],row[x][1],piccy[y-1][x]);
   }
} /* quantise */
/**************************************/

int random(figure,h,w)
int h,w;
int figure;
/*
    return a random number in the range 0 to pmax.
 note : that a=123465,b=54321,c0=34567 gives a regular grid

   called by quantise.
*/
#define c0 4567
{
   int k;
   int ans;
   static unsigned int a=1234589,b=3432,c=c0;

      if ((h == 0) && (w == 0) && (figure == 9))
            c = c0;
      else
         c = (b*c)%a;
      ans = (pmax*c)/a;
      if (debug <= -1)
         fprintf(stderr,"random %d %d %d %d\n",a,b,c,ans);
      return(ans);
} /* random */
/***************************************************/

start(figure)
int figure;
/*
   initialise random numbers

   called by edither.
*/
{
   int j,k,m;
   int random();

   k = random(0,0);
   if (figure == 10)
   {
      for (j = 0; j < frame; ++ j) k = random(1,1);
      for (j = 0; j < k; ++j) m = random(1,1);
   }
}/* start */

/******************************************************/

edrasel()
/*
   calls  minmax, setell, allcofs, shadel
   called by dopic.
*/
{
   int     cenn[3],axn[3],angn[3];
   int     j,k;
   int     vx,vy,vz,a1,a2,a3;
   double  deg10,tenth;
   char    scols[BMAX];

   bgr = pmax; bgg = pmax; bgb = pmax;
   minmax();
   for (n = 0; n < nels ; n++)
   {
      setnup(n);
      allcofs(n);
   }
   shadel();
} /* edrasel */
/**************************************/

allcofs(n)
int n;
/*
   set array of coefficients of 'n'th ellipsoid

   called by edrasel
*/
{
   int j,k;

   for (j = 0; j < 3; ++j)
   {
      for (k = 0; k < 3; ++k)
         ell[n][j][k] = elln[j][k];
      plane[n][j] = cn[j];
   }
   for (k = 0; k < 6; ++k)
      coef[n][k] = con[k];
   den[n] = doub1/elln[2][2];
   if (debug <= 0)
   {
      fprintf(stderr,"allcofs %d %9g %9g %9g\n",
         n,plane[n][0],plane[n][1],plane[n][2]);
      fprintf(stderr,"   %9g %9g %9g %9g %9g %9g\n",
         coef[n][0],coef[n][1],coef[n][2],coef[n][3],
         coef[n][4],coef[n][5]);
   }
} /* allcofs */
/**************************************/

shadel()
/*
    loop through all x and y, coloring as appropriate
 
    calls  zdepth, illum, setpnt
*/
{
   double zdepth();
   double illum();

   double depth;
   double dy;
   double light;
   double x,y,z;
   double tr,tg,tb;
   double plan23[EMAX],coef34[EMAX],coef256[EMAX],ell2y[EMAX][3];
   int    j;
   int    h,w;
   int    step;
   int    active[EMAX];
   int    nactiv;
   int    m,n;
   int    cstep,hcstep;
   int    wmin,wmax;
   int    shades;

   shades = 255;
   cstep = pmax/shades;
   hcstep = cstep/2;
   step = 1;
   if (debug <= 1) printf("shadela %d %f\n",width,wtos);
/*
    scan y direction-
*/
   for (h = 0; h < height; h+=step)
   {
      y = (double)h/wtos;
      wmax = 0;
      wmin = pmax;
      nactiv = 0;
/*
   do as much calculation as possible for this y scanline-
   for all the ellipsoids, avoiding the 0'th -
*/ 
      for (m = 1; m < nels; m++)
      {
         if ( (y < ymax[m]) && (y > ymin[m]) )
         {
            dy = y - cen[m][1];
            active[nactiv] = m;
            plan23[m] = plane[m][2]+plane[m][1]*dy;
            coef34[m] = coef[m][2]*dy+coef[m][3];
            coef256[m] = dy*(coef[m][1]*dy+coef[m][4])+coef[m][5];
            for (j = 0; j < 3; j++)
               ell2y[m][j] = ell[m][1][j]*dy;
            nactiv = nactiv+1;
            if (debug <= 0)
            {
               fprintf(stderr,
                  "shadelb %d%9g %9g %9g %9g %9g %9g\n",
                  m,cen[m][0],cen[m][1],cen[m][2],
                  ax3[m][0],ax3[m][1],ax3[m][2]);
               fprintf(stderr,"%9g %9g %9g %9g %9g %9g\n",
                  ell[m][0][0],ell[m][1][0],ell[m][2][0],
                  ell[m][0][1],ell[m][1][1],ell[m][2][1]);
               fprintf(stderr,"%9g %9g %9g %9g %9g %9g\n",
                  ell[m][0][2],ell[m][1][2],ell[m][2][2],
                  ell2y[m][0],ell2y[m][1],ell2y[m][2]);
            }
         }
      }
/*
   scan in x across scanline-
*/
      for (w = 0; w < width; w+=step)
      {
         tr = bgr; tg = bgg; tb = bgb;
         if (nactiv > 0) 
         {
            x = (double)w/wtos;
            depth = doubmax;
            n = -1;
/* 
         check ellipsoids that colour this point-
*/ 
            for (j = 0; j < nactiv; j++)
            {
               m = active[j];
               if ( (x < xmax[m]) && (x > xmin[m])
                                  && (zmin[m] < depth) )
               {
                   z = zdepth(m,x-cen[m][0],y-cen[m][1],
                                 plan23,coef34,coef256);
                   if (z <  depth) 
                   {
                      depth = z;
		      n = m;
                   }
               }
            }
            if (n >= 0)
            {
               if (debug <= 0)
                  fprintf(stderr,"shadelc %d %d %d %d %d\n",
                     n,nactiv,elcol[n][0],elcol[n][1],elcol[n][2]);
               z = depth;
               light = illum(n,
                      x-cen[n][0],y-cen[n][1],z-cen[n][2],ell2y);
               tr = light*elcol[n][0];
               tg = light*elcol[n][1];
               tb = light*elcol[n][2];
            }
         }
         tr = ((int)((tr+hcstep)/cstep))*cstep;
         tg = ((int)((tg+hcstep)/cstep))*cstep;
         tb = ((int)((tb+hcstep)/cstep))*cstep;
         setpnt(w,(height-h-1),tr,tg,tb);
      }
      if (debug <= 0) printf("\n");
   }
} /* shadel */
/***********************************************/
 
double zdepth(n,x,y,plan23,coef34,cof256)
int   n;
double x,y,plan23[EMAX],coef34[EMAX],cof256[EMAX];
/*
    find the depth z of the nearer surface of the n'th ellipsoid
    at point x,y relative to own centre

   called by shadel
*/
{
   double z;
   double discrt;
 
   z = doubmax;
   discrt = (-((coef[n][0]*x+coef34[n])*x+cof256[n])*den[n]);
   if (discrt > doub0)
      z = (-plan23[n]-plane[n][0]*x-sqrt(discrt));
   if (debug <= 0)
      fprintf(stderr,
         "zdepth %d %12g %12g %12g %12g %12g %12g %12g %12g\n",
            n,x,y,coef[n][0],coef34[n],cof256[n],den[n],discrt,z);
   return(z+cen[n][2]);
} /* zdepth */
/************************************************/
 
double illum(n,x,y,z,ell2y)
int   n;
double ell2y[EMAX][3];
double x,y,z;
/*
   find relative brightness of point (x,y,z) on surface
   of nth ellipsoid.
 
    called by  shadel.
*/
{ 
   int j;
   double grad[3],tgrad;
   double ambint;
   double g1;
   double light;
 
   ambint = doub0;
   light = doub0;
   tgrad = doub0;
   for (j = 0; j < 3; j++)
   {
       grad[j] = ell[n][0][j]*x+ell2y[n][j]+ell[n][2][j]*z;
       if (grad[j]>0) tgrad += grad[j];
          else tgrad -= grad[j];
   } 
   g1 = (tgrad+grad[1])/(tgrad+tgrad);
   light = ambint+(doub1-ambint)*g1;
   if (debug <= 0) fprintf(stderr,
      "illumb %d %f %f %f %f %f %f %f %f %f\n",
      n,x,y,z,light,grad[0],grad[1],grad[2],tgrad,g1);
   return(light);
} /* illum */
/***********************************************/

setpnt(wnew,hnew,cr,cg,cb)
int   wnew,hnew;
double cr,cg,cb;
/*
   set the point at (wnew,hnew) to colour (cr,cg,cb).

   called by shadel
*/
{
   int tr,tg,tb;
   int white;
   int c;

   if (debug <= 0) fprintf(stderr,"setpnta %d %d %f %f %f\n",
          wnew,hnew,cr,cg,cb);
/*
   make sure rgb values in 0 to pmax range -
*/
   tr = cr; tg = cg; tb = cb;
   tr = min(tr,pmax); tr = max(tr,0);
   tg = min(tg,pmax); tg = max(tg,0);
   tb = min(tb,pmax); tb = max(tb,0);
/*
   now store this pixel -
*/
   white = (tr + tg + tb)/3;
   piccy[wnew][hnew] = white;
   if (debug < 0)
      fprintf(stderr,"setpntb %d %d %d %d %d %d %d\n",
         wnew,hnew,thresh,tr,tg,tb,white); 
} /* setpnt */
/***********************************************/
/************************************************/

edshow()
/*
   create animation of scene rotating about y axis

   called by checkeys
   calls  setframes, display.
*/
{
   if (debug <= 0) fprintf(stderr,"edshowa %d\n",LMAX);
   speed = LMAX;
   freeze = FALSE;
   df = 1;
   rolling = TRUE;
   setframes();
   if (debug <= 5) fprintf(stderr,"edshowb %d %d\n",rolling,TRUE);
   if (rolling == TRUE) display(0,LMAX);
   if (debug <= 5) fprintf(stderr,"edshowc %d %d\n",rolling,TRUE);
} /* edshow */

/************************************************/

setframes()
/*
   run through frames

   called by edshow.
   calls     setels, shkeys, dospinby, dopic,
             dopixmap, msleep.
*/
{
   int f;
   double dtheta;
   double xrot[3];

   if (debug <= 0)
            fprintf(stderr,"setframesa %d\n",LMAX);
   dtheta = twopi/(double)LMAX;
   xrot[0] = doub500;
   xrot[1] = doub500;
   xrot[2] = doub500;
   setels(-1,-1);
   for ( f = 0; f < LMAX; ++f)
   {
      XClearWindow(thedisplay,thewindow);
      dospinby(xrot,0,dtheta,1);
      dopic();
      dopixmap(f);
      msleep();
      shkeys(f);
      if (rolling == FALSE) goto rtrn;
   }
rtrn:;
} /*  setframes */
/***********************************************/

dopixmap(f)
int f;
/*
   create pixmap f, and load it with the current window

   called by setframes.
*/
{
   if (debug <= 0)
       fprintf(stderr,
           "dopixmapa %d %d %d %d %d %d %d %d %d\n",
           f,thewidth,theheight,x,y,thex,they,thresh,thedepth);
   pixmap[f] = XCreatePixmap(
             thedisplay,thewindow,thewidth,theheight,thedepth);
   if (debug <= 5) fprintf(stderr, "dopixmapb %d\n",f);
   XFlush(thedisplay);
   XCopyArea(thedisplay,thewindow,pixmap[f],thegc,
         0,0,thewidth,theheight,0,0);
} /* dopixmap */
/**********************************/

display(fstart,fstop)
int fstart,fstop;
/*
   repeatedly display the frames

   called by edshow.
   calls     shkeys, image.
*/
{
   int f;
   int maxseq;
   int seq;

   if (debug <= 0)
      fprintf(stderr,"displaya %d %d\n",fstart,fstop);
   maxseq = MAXINT;
   f = fstart; df = 1;
   for (seq = 0; seq < maxseq; ++seq)
   {
      if (debug <= 0) fprintf(stderr,"displayb %d\n",seq);
show:
      shkeys(seq);
      if (rolling == FALSE) goto rtrn;
      image(f);
      f += df;
      if (freeze == TRUE) df = 0;
      if ((f >= fstart) && (f < fstop)) goto show;

      if (f < fstart) f = fstop-1;
      if (f >= fstop) f = fstart;
   }
rtrn:;
}  /* display */
/******************************************/

image(f)
int f;
/*
    show frame f

    called by display.
*/
{
   if (debug <= 0) fprintf(stderr,"imagea %d\n",f);
   XCopyArea(thedisplay,pixmap[f],thewindow,thegc,
             0,0,thewidth,theheight,0,0);
   XFlush(thedisplay);
   msleep();
} /* image */
/*******************************************/

msleep()
/*
   to sleep between frames

   called by  setframes, image.

   uses sys/time.h, sys/types.h
*/
{
   int msec;
   static struct timeval tv;

   if (debug <= 0)
      fprintf(stderr,"msleep %d\n",speed);
   if (speed == 0) msec = 1;
          else if (speed > 0) msec = 1000/speed;
          else msec = 1000*speed;
   if (msec < 0) msec = -msec;
   tv.tv_usec = msec*1000;
   if (msec < 1000)
      select(0, (fd_set *)0, (fd_set *)0, (fd_set *)0, &tv);
   else sleep(msec/1000);
} /* msleep */
/******************************************/

shkeys(seq)
int seq;
/*
   check if button or key pressed.

   called by  doframe, display.
*/
{
   XEvent theevent;
   KeySym thekeysym;
   XComposeStatus thecomposestatus;
   int maxlen;
   int slength;
   char buf[BMAX];

   if (debug <= 0) fprintf(stderr,"shkeysa %d\n",seq);
   maxlen = BMAX-1;
   XNextEvent(thedisplay,&theevent);
   if (theevent.type == KeyPress)
   {
      slength = XLookupString
         (&theevent,buf,maxlen,&thekeysym,&thecomposestatus);
      fprintf(stderr,"show key %c\n",buf[0]);
           if (buf[0] == '=') speed += 1;
           if (buf[0] == '-') speed -= 1;
           if (buf[0] == 'h') {
                                 fprintf(stderr,"= - speed up\n");
                                 fprintf(stderr,"- - slow down\n");
                                 fprintf(stderr,"h - help\n");
                                 fprintf(stderr,
                                    "t - go forward 1 frame\n");
                                 fprintf(stderr,
                                    "T - go back 1 frame\n");
                                 fprintf(stderr,
                                    "m - continue animating\n");
                                 fprintf(stderr,
                                    "M - stop animating\n");
                              }
      else if (buf[0] == 't') {
                                 df =  1;
                                 freeze = TRUE;
                              }
      else if (buf[0] == 'T') {
                                 df = -1;
                                 freeze = TRUE;
                              }
      else if (buf[0] == 'm') freeze = FALSE;
      else if (buf[0] == 'M') rolling = FALSE;
   }
   if (debug <= 0) fprintf(stderr,"shkeysb %d %d %c\n",
      rolling,FALSE,buf[0]);
} /* shkeys */
/*******************************************/

backup()
/*
     make a copy of everything

     called by tbackup
*/
{
   int e,j,k,n;

   bnels = nels;
   for (e = 0; e < nels; ++e)
   {
      for (k = 0; k < 3; ++k)
      {
         bcen[e][k] = cen[e][k]; 
         bax3[e][k] = ax3[e][k];
         bquat[e][k] = quat[e][k];
      }
      bquat[e][3] = quat[e][3];
      bquat[e][4] = quat[e][4];
      sprintf(bename[e],"%s",ename[e]);
   }
   bnjts = njts;
   for (j = 0; j < njts; ++j)
   {
      for (k = 0; k < 2; ++k)
      {
         bjnt[j][k] = jnt[j][k];
         bcoel[j][k] = coel[j][k];
      }
      bjnt[j][2] = jnt[j][2];
      sprintf(bjname[j],"%s",jname[j]);
   }
   for (k = 0; k < 3; ++k)
   {
      bcursor[k] = cursor[k];
      bjnext[k] = jnext[k];
   }
   becount = ecount;
   for (e = 0; e < ecount; ++e)
      belist[e] = elist[e];
   bjcount = jcount;
   for (j = 0; j < jcount; ++j)
      bjlist[j] = jlist[j];
   bell1 = ell1;
   bell2 = ell2;
   brefell = refell;
   bellpsd = ellpsd;
   bjoin = join;
   bjcursor = jcursor;
   bfigure = figure;
   bhighlight = highlight;
   baxfac = axfac;
   bdshift = dshift;
   bdoing = doing;
   bwidth = width;
} /* backup */
/***************************************************************/

dobackup()
/*
     restore everything

     called by checkeys
     calls     alterw.
*/
{
   int e,j,k,n;

   if (width != bwidth) alterw(doub1/axfac);
   width = bwidth;
   nels = bnels;
   for (e = 0; e < nels; ++e)
   {
      for (k = 0; k < 3; ++k)
      {
         cen[e][k] = bcen[e][k]; 
         ax3[e][k] = bax3[e][k];
         quat[e][k] = bquat[e][k];
      }
      quat[e][3] = bquat[e][3];
      quat[e][4] = bquat[e][4];
      sprintf(ename[e],"%s",bename[e]);
   }
   njts = bnjts;
   for (j = 0; j < njts; ++j)
   {
      for (k = 0; k < 2; ++k)
      {
         jnt[j][k] = bjnt[j][k];
         coel[j][k] = bcoel[j][k];
      }
      jnt[j][2] = bjnt[j][2];
      sprintf(jname[j],"%s",bjname[j]);
   }
   for (k = 0; k < 3; ++k)
   {
      cursor[k] = bcursor[k];
      jnext[k] = bjnext[k];
   }
   ecount = becount;
   for (e = 0; e < ecount; ++e)
      elist[e] = belist[e];
   jcount = bjcount;
   for (j = 0; j < jcount; ++j)
      jlist[j] = bjlist[j];
   ell1 = bell1;
   ell2 = bell2;
   refell = brefell;
   ellpsd = bellpsd;
   join = bjoin;
   jcursor = bjcursor;
   figure = bfigure;
   highlight = bhighlight;
   axfac = baxfac;
   dshift = bdshift;
   doing = bdoing;
} /* dobackup */
/********************************************/

tbackup(c)
char c;
/*
    test to see if backup needed

   called by checkeys
   calls     backup.
*/
{
   if ((c == '1') || (c == '2') || (c == '3')
   ||  (c == '4') || (c == '5') || (c == '6')
   ||  (c == '8') || (c == '9')
   ||  (c == 'a') || (c == 'A')
   ||  (c == 'b') || (c == 'B')
   ||  (c == 'c') || (c == 'C')
   ||  (c == 'd') || (c == 'D')
   ||  (c == 'e') || (c == 'E')
   ||  (c == 'f') || (c == 'F')
   ||  (c == 'g') || (c == 'G')
   ||  (c == 'h') || (c == 'H')
   ||  (c == 'i') || (c == 'I')
   ||  (c == 'j') || (c == 'J')
   ||  (c == 'k') || (c == 'K')
   ||  (c == 'l') || (c == 'L')
   ||  (c == 'm') || (c == 'M')
   ||  (c == 'n') || (c == 'N')
   ||  (c == 'o') || (c == 'O')
   ||  (c == 'p') || (c == 'P')
   ||  (c == 'r') || (c == 'R')
   ||  (c == 's') || (c == 'S')
   ||  (c == 't') || (c == 'T')
   ||  (c == 'u') || (c == 'U')
   ||  (c == 'v') || (c == 'V')
   ||  (c == 'w') || (c == 'W')
   ||  (c == 'x') || (c == 'X')
   ||  (c == 'y') || (c == 'Y')
   ||  (c == 'z') || (c == 'Z')
   ||  (c == '<') || (c == '>')
   ||  (c == ';') || (c == ':') )
      backup();
} /* tbackup */
