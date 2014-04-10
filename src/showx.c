/*
                     showx.c

      to display image and stereo files and animate them

       17 Jun 1998   frame number areas fixed

   Usage: showx name [-b u] [-d d] [-e u] [-f u] [-i] [-l u]
                     [-m u] [-n]   [-o]   [-p]   [-r] [-s u]
                     [-t u] [-x u] [-y u] 

   Flags-
         -b use 'u' to begin displaying from frame name.u (default: 1) 
	 -d set debug information level (default: 1)
         -e show every u'th frame (default: 1)
         -f show at 'u' frames per second (default: 25)
            or abs('u') seconds per frame if u<0
         -i make the display interactive when frames are loaded
         -l show only 'u' frames
            (default: min(1000,highest frame number))
         -m show each pixel as a square of size u (default: 1)
         -n show frame numbers (default: no frame numbers)
         -o show images overlapping (default: not overlapping)
         -p pause at restart for 1 second on first and last frames
            (default: no pause)
         -r reverse intensity levels
         -s use 'u' to start at frame name.u (default: 1) 
         -t set b/w threshold (default: 121)
         -x set upper left x coordinate (default: 0)
            If x and y = 0, use cursor position.
         -y set upper left y coordinate (default: 0)
            If x and y = 0, use cursor position.

      Shows one frame if name is a complete file name,
         else animates name.0001 onwards repeatedly at a
         default speed of 25 frames per second.
      Uses compressed files if these are present (.Z extension).
      Uses name.a if name doesn't work, then tries name.b,
         name.c, etc, then name.A, name.B, name.C, etc .
      Flags and arguements can be in any order.
      Using no flags or arguements gives a listing of
         this program, starting with these informative comments.

   File format -
      3 lines of format data -
	 P3
         width
         height
         maxcols
      then three values per pixel of width*height values.

   subroutines -
      main           - organises things
      getpar         - get invoked parameters
      getfile        - get the image files
      tryfile        - try various file types
      isfile         - find full name of image file
      checkhead      - check header of image file
      doframe        - create a pixmap and load it
      colpoint       - set a pixel
      dropline       - draw out the line buffer
      display        - repeatedly display the animation
      image          - display one image
      msleep         - sleep for some milliseconds
      exec           - execute a system command
      process        - interpret menu command
      getout         - exit gracefully
      startwindows   - start the X-Window system
      createcmndmenu - create the command menu
      redrawmenu     - redraw the command menu
      dostars        - asterisk active menu items
      drawmenu       - draw a menu box and content
      createsegment  - create a menu image segment
      closesegment   - close a menu image segment
      text           - draw a text string
      moverel        - move drawing position by given values
      moveabs        - move drawing position to given values
      linerel        - draw line by given values
      lineabs        - draw line to given values
      awaitpick      - wait for mouse event
      hueset         - find available colours
      allocol        - find nearest available colour

   modified -
       17 Jun 1998   magnification factor added
       17 Jun 1998   frame count report fixed
       12 Jun 1998   heading checked only once
       12 Jun 1998   fix max frame length
       12 Jun 1998   moved asterisks to left of menu items
       12 Jun 1998   stopped image overwriting menu
       12 Jun 1998   extended menu line to top
       12 Jun 1998   swapped event.xkey.x and theevent.xkey.y back
       22 Sep 1996   swapped event.xkey.x and theevent.xkey.y (eXcursions bug)
                     for an Ipex/Prism PC386/40 or an Ipex/Prism PC486DX/33VL
                     using XWindows bitmaps via eXcursions,
	             using only 16 colours
	             allowing keyboard commands
	9 Jul 1996   for ppm P3 images
	6 Jan 1996   buffer output lines
	6 Jan 1996   dithering
	5 Jan 1996   to have internal colour table
       19 May 1994   to use mouse
        7 Apr 1994   for Sun system
       17 Jul 1993   fix bugs
       14 Jun 1993   handle insufficient space nicely
        9 Jan 1992   allow choice of window types
       21 Dec 1991   to do run-length encoding to speed drawing
       28 Nov 1991   to use colour images
        8 Apr 1991   to use X windows on Sun 3/50
       28 Apr 1990   to use X windows
        4 Jul 1989   to show images of arbitrary size
       31 Mar 1989   to show 2 frames for image buffering
        2 Jun 1988   to show frame numbers (Myles Thomas)
       28 Apr 1988   to run interactively
       15 Apr 1988   to clear /tmp first
       25 Oct 1987   written (Don Herbison-Evans)
*/
#include <stdio.h>
#include <values.h>
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/keysym.h"
#include "X11/keysymdef.h"
#include <sys/types.h>
#include <sys/time.h>

#define EXIT       1
#define FORWD      2
#define BACKWD     3
#define HALT       4
#define ANIMATE    5
#define SLOWER     6
#define QUICKER    7
#define NUMBERS    8
#define OFFNUMBERS 9
#define CYCLE     10
#define PAUSE     11
#define TRUNCATE  12
#define SMAX      13        /* number of menu segments */

#define BMAX    256         /* size of string buffers */
#define CMAX    256         /* number of values of each colour */
#define XMAX    1024        /* max width of image */
#define WMAX    65535       /* max value of a colour in XWindows */
#define CFAC    WMAX/CMAX   /* converts local colours to XWindow colours */
#define IMAX    128*256*256 /* max product of number*size of images */
#define MH      20          /* height of menu box */
#define MW      100         /* width of menu box */
#define RATE    25          /* default frames per second display rate */
#define PMAX    1000        /* max number of pictures in animation */
#define TRUE    1
#define FALSE   0
#define EVMASK (ButtonPressMask | \
                ButtonReleaseMask | \
                KeyPressMask)
/*
   X window variables -
*/
   XColor       cell;
   int		thedepth,thescreen;
   int		thex,they;
   Window	thewindow;
   Drawable	pixmap[PMAX];
   XEvent	theevent;
   Display	*thedisplay;
   Visual	*thevisual;
   XVisualInfo  vtemplate;
   XVisualInfo  *vlist;
   XSizeHints	thesizehints;
   XGCValues	thegcvalues;
   GC		thegc;
   XSetWindowAttributes thewindowattributes;
   Colormap             cmap;
   unsigned int		thewidth = XMAX;
   unsigned int         theheight = XMAX;
   unsigned int		borderwidth;
   unsigned int		theclass;
   unsigned long	thevaluemask;
   unsigned long	thewindowmask;
/*
   program variables -
*/
struct Segment {
   Drawable map;
   int w;
   int h;
   int x;
   int y;
   int hit;
};
struct Segment segs[SMAX+1];

char  buf[BMAX];	/* input string buffer */
char  cmnd[BMAX];	/* shell command string buffer */
char  err[BMAX];	/* error message string buffer */
char  filename[BMAX];   /* original image file name */
char  finame[BMAX];	/* root+image type  file name stem */
char  fname[BMAX];	/* root name of image file names */
char  home[BMAX] = "/usr/users/staff/herbisod";
char  keys[SMAX];       /* keys for interactive commands */
char  imst[2][2];       /* the 2 types of images supported */
char  infile[BMAX];     /* current input image file name */
char  stars[BMAX]="*";  /* menu in use indicator */

int   berr[XMAX+1];     /* error of blue pixels */
int   bw;               /* true if image in black and white */
int   colour;           /* true if image has rgb components */
int   cp[CMAX];         /* indices of the colours */
int   ctop;             /* number of available colours */
int   currentx,currenty;/* current drawing position */
int   disopen = FALSE;  /* true if display opened */
int   debug = 1;        /* <= 0 for debugging info to be printed */
int   df;		/* current increment between frames */
int   f;		/* current frame number */
int   fheight;          /* height of the magnified image */
int   first = TRUE;	/* flag for processing first image */
int   fnums;		/* true if frame numbers to be displayed */
int   frame[PMAX];      /* the frame numbers */
int   halt;             /* true if animation halted */
int   fstart = 0;	/* number of first frame for display */
int   fstop;		/* number of last frame for display */
int   fwidth;           /* width of the magnified image */
int   gerr[XMAX+1];     /* error of green pixels */
int   headread;         /* TRUE if heading already read */
int   height;           /* height of the image read from file */
int   hue[CMAX][3];     /* available colours */
int   length;		/* number of frames to be animated */
int   lengthf;		/* number of file frames to be animated */
int   line[XMAX];       /* output line buffer */
int   mag;              /* magnifying factor */
int   nfr;		/* number of current display file frame */
int   nlngth;           /* length of frame number */
int   ok;               /* true if image file obtained  */
int   overlap = FALSE;  /* true if images to be overlapped */
int   pause;		/* true if pausing on first and last frames */
int   rcor,gcor,bcor;   /* colour corrections to be passed on */
int   rerr[XMAX+1];     /* error of red pixels */
int   reverse = FALSE;  /* true if intensities to be inverted */
int   start;		/* number of first frame file */
int   step;		/* increment between frame numbers */
int   stop;             /* number of last frame file */
int   speed;            /* number of frames per second required */
int   thresh;           /* threshold for grey values to be drawn */
int   width;            /* width of the image read from file */
int   xerrcode = 0;     /* to check XCreatePixmap */
FILE  *INFILE;

/************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls  getpar, getfiles, display, getout.
*/
{
   getpar(argc,argv);
   getfiles();
   display();
   getout(0);
} /* main */

/************************************************/

getpar(argc,argv)
int argc;
char *argv[];
/*
   get the parameters

   called by main.
*/
{
   int p;
   int value;

   debug = 1;
   mag = 1;
   headread = FALSE;
   currentx = 0;
   currenty = 0;
   lengthf = PMAX;
   pause = FALSE;
   start = 0;
   step = 1;
   stop = lengthf;
   speed = RATE;
   thresh = 'y'; /* 121 decimal */
   fnums = TRUE;
   imst[0][0] = 'i';
   imst[0][1] = 'm';
   imst[1][0] = 's';
   imst[1][1] = 't';
   if (argc < 2)
   {
       sprintf(cmnd,"more %s/src.nudes/showx.c\n",home);
       exec(cmnd);
       exit(0);
   }
   else
   {
       for ( p = 1; p < argc; ++ p)
       {
          sprintf(buf,"%s",argv[p]);
	  if (debug <= 0)
	     printf("getpara %d %s %c\n",
		p,argv[p],buf[0]);
          if (buf[0] != '-')
              sprintf(fname,"%s",argv[p]);
          else if (buf[1] == 'b')
          {
              if (p < (argc-1))
              {
                 ++ p;
                 sscanf(argv[p],"%d",&start);
              }
              if ((start < 0) || (start > 9999))
              {
                  sprintf(err,"funny -b parameter: %d",start);
                  getout(1);
              }
              pause = TRUE;
          }
          else if (buf[1] == 'd')
	  {
              if (p < (argc-1))
              {
                 ++ p;
                 sscanf(argv[p],"%d",&debug);
              }
	  }
          else if (buf[1] == 'e')
	  {
                if (p <= (argc-1))
                {
		   ++ p;
		   sscanf(argv[p], "%d",&step);
                   if (step < 0) step = -step;
                }
	  } 
          else if (buf[1] == 'f')
          {
              if (p < (argc-1))
              {
                 ++ p;
                 sscanf(argv[p],"%d",&speed);
              }
          }
          else if (buf[1] == 'i')
          {
              halt = TRUE;
          }
          else if (buf[1] == 'l')
          {
              if (p < (argc-1))
              {
                 ++ p;
                 sscanf(argv[p],"%d",&lengthf);
              }
              if (lengthf < 0)
              {
                  lengthf = -lengthf;
                  getout(1);
              }
              pause = TRUE;
          }
          else if (buf[1] == 'm')
          {
              if (p < (argc-1))
              {
                 ++ p;
                 sscanf(argv[p],"%d",&mag);
              }
              if (mag < 0)
              {
                  mag = -mag;
                  getout(1);
              }
          }
          else if (buf[1] == 'n')
              fnums = FALSE;
          else if (buf[1] == 'o')
              overlap = TRUE;
          else if (buf[1] == 'p')
              pause = TRUE;
          else if (buf[1] == 'r')
              reverse = TRUE;
          else if (buf[1] == 's')
          {
              if (p < (argc-1))
              {
                 ++ p;
                 sscanf(argv[p],"%d",&start);
              }
              if ((start < 0) || (start > 9999))
              {
                  sprintf(err,"funny -s parameter: %d",start);
                  getout(1);
              }
              pause = TRUE;
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
		   sscanf(argv[p], "%d",&thex);
                }
                if ((thex < 0) || (thex > 1023))
                {
                  sprintf(err,"funny -x parameter: %d",thex);
                  getout(1);
                }
	  } 
          else if (buf[1] == 'y')
	  {
                if (p < (argc-1))
                {
		   ++ p;
		   sscanf(argv[p], "%d",&they);
                }
                if ((they < 0) || (they > 1023))
                {
                  sprintf(err,"funny -y parameter: %d",they);
                  getout(1);
                }
	  } 
	  else
          {
             sprintf(err,"unrecognized flag: %s",argv[p]);
             getout(1);
          }
       }
   }
   length = (lengthf -1)/step + 1;
   if (length > PMAX)
   {
      length = PMAX;
      lengthf = (length-1)*step+1;
      printf("length changed to %d\n",lengthf);
   }
   stop = start + length ;
   if (debug <= 0)
   {
      printf("data file %s\n",fname);
      printf("reverse, true:   %d, %d\n",reverse,TRUE);
   }
   if (mag == 0) mag = 1;
} /* getpar */

/************************************************/

getfiles()
/*
   run through files

   called by main.
   calls     isfile, tryfile, doframe, getout.
*/
{
   int maxlength;
   int next;
   int tryfile();
   int isfile();
   int doframe();

   if (debug <= 0)
      printf("getfilesa %s %d %d\n",fname,start,fstart);
   f = fstart;
   first = TRUE;
   sprintf(finame,"%s",fname);
   if (start < 0) start = 0;
   if (start == 0)
   {
      if (tryfile(start) == FALSE) start = 1;
   }
   stop = start + lengthf;
   if (debug <= 0)
      printf("getfilesb %d %d\n",start,stop);
   for ( nfr = start; nfr < stop; nfr += step)
   {
      next = tryfile(nfr);
      if (isfile(finame,nfr) == FALSE)
      {
         if (first == FALSE)
            goto dis;
         else
         {
            sprintf(err,
                  "can't open file like %s or %s for reading",
                  fname,finame);
            ok = FALSE;
            if (first == TRUE) getout(1);
            sprintf(cmnd,"rm -rf /tmp/%s.*\n",finame);
	    exec(cmnd);
            ok = doframe();
            if (ok == FALSE) goto dis;
         } 
      }
      else
      {
          ok = doframe();
          if (ok == FALSE) goto dis;
      }
      printf("getfile %s %3d %3d\n",infile,f,nfr);
      sprintf(cmnd,"rm -rf /tmp/%s*\n",finame);
      exec(cmnd);
      if (f == fstart)
      {
         maxlength = IMAX/(thewidth*fheight);
         printf("max length %d frames\n",maxlength);
         if (length > maxlength)
         {
             lengthf = (maxlength-1)*step + 1;
             length = maxlength;
         }
      }
      if (f > length)
      {
          printf("more than %d frames present\n",length);
          ok = FALSE;
          goto dis;
      }
      ++ f;
   }
   
dis:
   fstop = f-1;
   length = f - fstart;
   if (debug <= 0) printf("getfilesz %d %d\n",fstart,fstop);
   if (fstop < 0) fstop = 0;
   if (length != 1) printf("length %d frames\n",length);
      else printf("length %d frame\n",length);
   if ((ok == FALSE) || (fstart == fstop)) pause = TRUE;
   if (fstart >= fstop) fnums = FALSE;
   sprintf(cmnd,"rm -rf /tmp/%s*\n",finame); exec(cmnd);
}  /* getfiles */
/***********************************************/

int tryfile(nfr)
int nfr;
/*
   try various types of files for same root name
   'fname' and frame number 'nfr', leaving name
   in 'finame' if ok.

   called by getfiles
*/
{
   int fig;
   int fmin,fmax;
   char f;

   fmin = 'A';
   fmax = 'z' + 1;
   if (debug <= 0)
         printf("tryfilea %d %s %d %d\n",nfr,fname,fmin,fmax);
   sprintf(finame,"%s",fname);
   if (isfile(finame,nfr) == TRUE) goto gotit;
   for (fig = fmin; fig < fmax ; ++fig)
   {
      f = fig;
      if (debug <= 0)
         printf("tryfileb %d %c %s\n",fig,f,fname);
      sprintf(finame,"%s.%c",fname,f);
      if (isfile(finame,nfr) == TRUE) goto gotit;
   }
   return(FALSE);

gotit:
   fclose(INFILE);
   return(TRUE);
} /* tryfile */
/*************************************************/

int isfile(ftmp1,nfr)
char ftmp1[BMAX];
int nfr;
/*
   check whether there is a file for nfr'th frame,
   and if so, open it, and remove the five descriptor lines.

   called by getfiles.
   calls checkhead, getout.
*/
{
   int  comprd;	/* true if current frame is compressed */
   int  ok;
   char ftmp2[BMAX];
   char ftmp3[BMAX];
   char ftmpz[BMAX];

   ok = FALSE;
   sprintf(ftmp2,"ftmp2");
   sprintf(ftmp3,"ftmp3");
   sprintf(ftmpz,"ftmpz");
   sprintf(filename,"filename");
   comprd = FALSE;
   if (first == TRUE)
   {
      sprintf(filename,"%s",ftmp1);
      if (debug < 0) printf("isfilea trying %s\n",ftmp1);
      if( NULL != (INFILE=fopen(ftmp1,"r")) )
      {
         sprintf(infile,"%s",ftmp1);
         length = 1;
         ok = TRUE;
      }
      else
      {
         sprintf(ftmpz,"%s.Z",ftmp1);
         sprintf(filename,"%s",ftmpz);
         if (debug < 0) printf("isfileb trying %s\n",ftmpz);
         if (NULL != (INFILE=fopen(ftmpz,"r")) )
         {
            sprintf(cmnd,"zcat %s >/tmp/%s\n",ftmpz,ftmp1);
            exec(cmnd);
            sprintf(ftmp2,"/tmp/%s",ftmp1);
            if (debug < 0) printf("isfilec trying %s\n",ftmp2);
            if( NULL == (INFILE=fopen(ftmp2,"r")) )
            {
               sprintf(err,
                   "can't open %s (uncompressed %s)",ftmp2,ftmpz);
               getout(1);
            }
            comprd = TRUE;
            length = 1;
            ok = TRUE;
            sprintf(infile,"%s",ftmpz);
         }
      }
   }
   if (ok == FALSE)
   {
      if ((nfr >= 0 ) && (nfr <= 9 ))
              sprintf(ftmp2,"%s.000%d",ftmp1,nfr);
      if ((nfr >= 10) && (nfr <= 99))
              sprintf(ftmp2,"%s.00%d",ftmp1,nfr);
      if ((nfr >= 100) && (nfr <= 999))
              sprintf(ftmp2,"%s.0%d",ftmp1,nfr);
      if (nfr >= 1000)
              sprintf(ftmp2,"%s.%d",ftmp1,nfr);
      sprintf(filename,"%s.ppm",ftmp2);
      if (debug < 0) printf("isfiled trying %s\n",filename);
      if( NULL == (INFILE=fopen(filename,"r")) )
      {
         sprintf(ftmpz,"%s.Z",filename);
         if (debug < 0) printf("isfilee trying %s\n",ftmpz);
         if( NULL == (INFILE=fopen(ftmpz,"r")) )
         {
               ok = FALSE;
         }
         else
         {
            fclose(INFILE);
            comprd = TRUE;
            sprintf(cmnd,"zcat %s >/tmp/%s\n",ftmpz,ftmp2);
            exec(cmnd);
            sprintf(ftmp3,"/tmp/%s",ftmp2);
            if (debug <= 0) printf("isfilef trying %s\n",ftmp3);
            if( NULL == (INFILE=fopen(ftmp3,"r")) )
            {
               sprintf(err,
                   "cannot open %s (uncompressed %s)",ftmp3,ftmpz);
               getout(1);
            }
            sprintf(infile,"%s",ftmpz);
            ok = TRUE;
         }
      }
      else
      {
         sprintf(infile,"%s",ftmp2);
         ok = TRUE;
      }
   }
   if (debug < 0)
      printf("isfileg %d %d %d %s %s %s %s %s %s %s\n",
	ok,TRUE,nfr,fname,finame,ftmp1,ftmp2,ftmp3,ftmpz,filename);
   if (ok == TRUE) checkhead();
   return(ok);
} /* isfile */

/****************************************************/

checkhead()
/*
   check the heading of an image file

   called by isfile.
   calls getout.
*/
{
   char buf[BMAX];
   int cmax;
   int hdiff;

   fgets(buf,BMAX,INFILE);
   if ((buf[0] != 'P') && (buf[1] != 'S') && (buf[2] != '3'))
   {
      sprintf(err,
              "input header funny, frame %d, file %s\n%s\n",
              f,filename,buf);
      getout(1);
   }
   fscanf(INFILE,"%d",&width);
   fscanf(INFILE,"%d",&height);
   fscanf(INFILE,"%d",&cmax);
   if (headread == FALSE)
   {
      headread = TRUE;
      fwidth = mag*width;
      fheight = mag*height;
      theheight = fheight;
      thewidth = fwidth + MW + 1;
      hdiff = (SMAX-1)*MH - theheight;
      if (hdiff > 0 )
      {
         theheight = (SMAX-1)*MH;
         printf("height changed to %d\n",theheight);
      }
   }
   if (debug <= 0)
	 printf("checkhead: frame %d, height %d, width %d\n",
	    f,theheight,thewidth);
} /* checkhead */
/******************************************/

int doframe()
/*
   create pixmap f, and load it with a file

   called by getfiles.
   calls     startwindows, createcmndmenu, colpoint, getout,
             hueset, allocol, clrsq, redrawmenu, awaitpick.
*/
{
   int allocol();
   int gray;
   int j,k;
   int h,w;
   int c;
   int p;
   int r,g,b;
   char nstr[BMAX];

   if (first == TRUE)
   {
      startwindows();
      XClearWindow(thedisplay,thewindow);
      createcmndmenu();
      hueset();
      first = FALSE;
   }
   else
      redrawmenu();
   pixmap[f] = XCreatePixmap(
             thedisplay,thewindow,fwidth,fheight,thedepth);
   XFlush(thedisplay);
   if (overlap == FALSE) XClearArea(thedisplay,thewindow,
         0,0,fwidth,fheight,FALSE);
   cell.flags = DoRed | DoGreen | DoBlue;
   for ( w = 0; w < width; ++ w)
   {
      rerr[w] = 0;
      gerr[w] = 0;
      berr[w] = 0;
   }
/*
   get the picture -
*/
   for ( h = 0; h < height; ++h)
   {
      rcor = 0;
      gcor = 0;
      bcor = 0;
      for ( w = 0; w < width; ++ w)
      {
         fscanf(INFILE,"%d",&r);
         fscanf(INFILE,"%d",&g);
         fscanf(INFILE,"%d",&b);
         if (reverse == TRUE)
         {
            r = CMAX-r;
            g = CMAX-g;
            b = CMAX-b;
         }
         if (r < 0) r += CMAX;
         if (g < 0) g += CMAX;
         if (b < 0) b += CMAX;
         r += rcor + rerr[w];
         g += gcor + gerr[w];
         b += bcor + berr[w];
         colpoint(h,w,r,g,b);
      }
      dropline(h);
   }
   fclose(INFILE);
   XCopyArea(thedisplay,thewindow,pixmap[f],thegc,
             0,0,fwidth,fheight,0,0);
   c =  allocol(0,0,0);
   XSetForeground(thedisplay,thegc,cp[c]);
   frame[f] = nfr;
   if ((f != fstart) && (fnums == TRUE))
   {
       sprintf(nstr,"%d",nfr);
       nlngth = strlen(nstr);
       clrsq(1,fheight-30,10*(nlngth+2),fheight-1);
       XDrawString(thedisplay,thewindow,thegc,
                    5,fheight-5,nstr,nlngth);
   }
   awaitpick();
   if (debug <= 0) printf("doframea %3d %3d\n",f,nfr);
   return(TRUE);
} /* doframe */
/**********************************/

colpoint(j,k,r,g,b)
int j,k;
int r,g,b;
/*
   colour  point (j,k) to colour (r,g,b)

   called by doframe.
   calls     allocol.
*/
{
   int c;

   c = allocol(r,g,b);
   line[k] = cp[c];
   rcor = (r-hue[c][0])/3;
   gcor = (g-hue[c][1])/3;
   bcor = (b-hue[c][2])/3;
} /* colpoint */ 
/**********************************/

dropline(j)
int j;
/*
   draw line buffer out at y position 'j'.

   called by doframe
*/
{
   int m;
   int w;
   int k;

   k = 0;
   for (w = 1; w < width; ++w)
   {
      if (line[k] != line[w])
      {
         XSetForeground(thedisplay,thegc,line[k]);
         for (m = 0; m < mag; ++m)
            XDrawLine(thedisplay,thewindow,thegc, mag*k,mag*j+m,mag*w,mag*j+m);
	 k = w;
      }
   }
   XSetForeground(thedisplay,thegc,line[k]);
   for (m = 0; m < mag; ++m)
      XDrawLine(thedisplay,thewindow,thegc, mag*k,mag*j+m,fwidth,mag*j+m);
}   /* dropline */
/*************************************/

display()
/*
   repeatedly display the frames

   called by main.
   calls  redrawmenu, image.
*/
{
   int maxseq;
   int seq;

   maxseq = MAXINT;
   if (debug <= 0) printf("displaya %d\n",maxseq);
   f = fstart;
   df = 1;
   for (seq = 0; seq < maxseq; ++seq)
   {
show:
      redrawmenu();
      image(f);
      f += df;
      if (halt == TRUE) df = 0;
      if ((f >= fstart) && (f <= fstop)) goto show;

      if (f < fstart) f = fstop;
      if (f > fstop) f = fstart;
   }
} /* display */
/******************************************/

image(f)
int f;
/*
    show frame f

    called by display.
    calls     clrsq, awaitpick, msleep.
*/
{
   char nstr[BMAX];
   int nlngth;

   XCopyArea(thedisplay,pixmap[f],thewindow,thegc,
             0,0,fwidth,fheight,0,0);
   if (fnums == TRUE)
   {
       sprintf(nstr,"%d",frame[f]);
       nlngth = strlen(nstr);
       clrsq(1,fheight-20,10*(nlngth+1),fheight-1);
       XDrawString(thedisplay,thewindow,thegc,
                    5,fheight-5,nstr,nlngth);
       if (speed > 0) sprintf(nstr,"%d fr/s",speed);
          else sprintf(nstr,"%d s/fr",-speed);
       nlngth = strlen(nstr);
       clrsq(1,1,10*(nlngth+2),20);
       XDrawString(thedisplay,thewindow,thegc,
                    5,15,nstr,nlngth);
   }
   XFlush(thedisplay);
   msleep(speed);
   if ((pause == TRUE) && ((f == fstart) || (f == fstop))
       && (halt != TRUE))
             sleep(1);
   awaitpick();
} /* image */
/*******************************************/

msleep(speed)
int speed;
/*
   to sleep between frames, etc.

   called by   image.

   uses sys/time.h, sys/types.h
*/
{
   int msec;
   static struct timeval tv;

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

exec(cmnd)
char cmnd[BMAX];
/*
   execute a system command with optional echo

   called by isfile, getout, getpar, getfiles.
*/
{
   if (debug <= 0) printf("%s",cmnd);
   system(cmnd);
} /* exec */
/******************************************/

process(n)
int  n;
/*
   called by awaitpick.
*/
{
   if (debug <= 0) printf("processa %d\n",n);
   if (n != 0)
   {
      if (n == EXIT) getout(0);
      else if (n == TRUNCATE)
      {
	 length = f;
	 printf("length changed to %d\n",f);
      }
      else if (n == NUMBERS)
      {
	 fnums = TRUE;
	 printf("showing frame numbers\n");
      }
      else if (n == OFFNUMBERS)
      {
	 fnums = FALSE;
	 printf("not showing frame numbers\n");
      }
      else if (n == PAUSE)
      {
         pause = TRUE;
         printf("pausing on first and last frames\n");
      }
      else if (n == CYCLE)
      {
         pause = FALSE;
         printf("Not pausing on first and last frames\n");
      }
      else if (halt == TRUE)
      {
         if (n == ANIMATE)
         {
            printf("animating\n");
            halt = FALSE;
            df = 1;
         }
         else if (n == BACKWD) df = -1;
         else if (n == FORWD) df = 1;
         else printf("oops\n");
      }
      else /* animating */
      {
         if (n == QUICKER)
         {
            ++speed;
            if (speed == 0) speed = 1;
	    printf("speeding to %d f/s \n",speed);
         }
         else if (n == SLOWER)
         {
            --speed;
            if (speed == 0) speed = -1;
	    printf("slowing to %d f/s \n",speed);
         }
         else if (n == HALT)
         {
            halt = TRUE;
            printf("halt\n");
         }
         else if (n == BACKWD) 
         {
            if (df > 0) df = -df;
	    printf("backwards\n");
         }
         else if (n == FORWD)
         {
            if (df < 0) df = -df;
	    printf("forwards\n");
         }
         else printf("oops\n");
      }
   }
} /* process */
/*******************************************/

getout(v)
int v;
/*
   exit gracefully

   called by doframe, checkhead, isfile, getframes, display, main.
*/
{
   int j;

   if (v != 0) printf("showx: %s\n",err);
   sprintf(cmnd,"rm -rf /tmp/%s*\n",finame); exec(cmnd);
   if (disopen == TRUE)
   {
      XDestroyWindow(thedisplay,thewindow);
      XCloseDisplay(thedisplay);
   }
   exit(v);
} /* getout */
/*******************************************/

startwindows()
/*
   open X window system

   called by doframe.
*/
{
   char title[BMAX];

   thedisplay = XOpenDisplay(NULL);
   if ( thedisplay == NULL )
   {
      printf("showx: cannot open display %s\n",XDisplayName(NULL));
      exit(1);
   }
   thescreen = DefaultScreen(thedisplay);
   thedepth = DefaultDepth(thedisplay,thescreen);
   thewindowattributes.border_pixel
      = BlackPixel(thedisplay,thescreen);
   thewindowattributes.backing_store = Always;
   thewindowattributes.background_pixel
      = WhitePixel(thedisplay,thescreen);
   thewindowattributes.override_redirect = TRUE;
   thewindowmask =
      (CWBackingStore | CWBackPixel |
        CWBorderPixel | CWOverrideRedirect);
   thevisual = CopyFromParent;
   theclass = InputOutput;
   cmap = DefaultColormap(thedisplay,thescreen);
   borderwidth = 1;

   thesizehints.flags = PPosition | PSize;
   thesizehints.x = thex;
   thesizehints.y = they;
   thesizehints.width = thewidth;
   thesizehints.height = theheight;
   if ((thex != 0) || (they != 0))
      thewindow = XCreateWindow(
                  thedisplay,
                  RootWindow(thedisplay,thescreen),
                  thex,they,thewidth,theheight,
                  borderwidth,
                  thedepth,
                  theclass,
                  thevisual,
                  thewindowmask,
                  &thewindowattributes);
   else
      thewindow = XCreateSimpleWindow(
                  thedisplay,
                  RootWindow(thedisplay,thescreen),
                  thex,they,thewidth,theheight,
                  borderwidth,
                  BlackPixel(thedisplay,thescreen),
                  WhitePixel(thedisplay,thescreen));
   sprintf(title,"showx: %s",fname);
   XStoreName(thedisplay,thewindow,title);
   XSetNormalHints(thedisplay,thewindow,&thesizehints);
   thegcvalues.foreground = BlackPixel(thedisplay, thescreen);
   thegcvalues.background = WhitePixel(thedisplay, thescreen);
   thegc = XCreateGC(thedisplay,thewindow,
             GCForeground | GCBackground, &thegcvalues);
   if ( thegc == 0 )
   {
      printf("showx: cannot create gc\n");
      exit(1);
   }
   XClearWindow(thedisplay,thewindow);
   XMapWindow(thedisplay,thewindow);
   XInstallColormap(thedisplay,cmap);
   XFlush(thedisplay);
   XSelectInput(thedisplay,thewindow,EVMASK);
   if ((thex == 0) && (they == 0)) sleep(3);
} /*  startwindows */
/*****************************************/

createcmndmenu()
/*
   called by doframe, awaitpick.
   calls     createsegment, linerel, text, closesegment,
             drawmenu.
*/
{
   moveabs(fwidth+1,0);
   lineabs(fwidth+1,fheight+3);
   segs[EXIT].x = fwidth+1;
   segs[EXIT].y = 0;
   segs[EXIT].h = MH;
   segs[EXIT].w = MW;
   createsegment(EXIT);
   linerel(segs[EXIT].w,0);
   linerel(0,segs[EXIT].h);
   linerel(-segs[EXIT].w,0);
   linerel(0,-segs[EXIT].h);
   moverel(0,3);
   text(" exit");
   closesegment(EXIT);

   drawmenu(FORWD,EXIT," forwd");
   drawmenu(BACKWD,FORWD," backwd");
   drawmenu(HALT,BACKWD," halt");
   drawmenu(ANIMATE,HALT," animate");
   drawmenu(SLOWER,ANIMATE," slower");
   drawmenu(QUICKER,SLOWER," quicker");
   drawmenu(NUMBERS,QUICKER," numbers on");
   drawmenu(OFFNUMBERS,NUMBERS," off numbers");
   drawmenu(CYCLE,OFFNUMBERS," cycle");
   drawmenu(PAUSE,CYCLE," pause");
   drawmenu(TRUNCATE,PAUSE," truncate");
   keys[EXIT] = 'e';
   keys[FORWD] = 'f';
   keys[BACKWD] = 'b';
   keys[HALT] = 'h';
   keys[SLOWER] = 's';
   keys[QUICKER] = 'q';
   keys[NUMBERS] = 'n';
   keys[OFFNUMBERS] = 'o';
   keys[CYCLE] = 'c';
   keys[PAUSE] = 'p';
   keys[TRUNCATE] = 't';
} /*  createcmndmenu */
/******************************************/

dostars()
/*
   asterisk active menu items

   called by createcmndmenu, redrawmenu, 
*/
{
   int black,red;
   int allocol();

   if (debug <= 0) printf("dostarsa %d %d\n",pause,TRUE);
   red = allocol(255,0,0);
   XSetForeground(thedisplay,thegc,cp[red]);
   if (pause == TRUE)
      XDrawString(thedisplay,thewindow,thegc,
         segs[PAUSE].x+3,theheight-segs[PAUSE].y,stars,2);
      else
         XDrawString(thedisplay,thewindow,thegc,
            segs[CYCLE].x+3,theheight-segs[CYCLE].y,stars,2);

   if (halt == TRUE)
      XDrawString(thedisplay,thewindow,thegc,
         segs[HALT].x+3,theheight-segs[HALT].y,stars,2);
      else
         XDrawString(thedisplay,thewindow,thegc,
            segs[ANIMATE].x+3,theheight-segs[ANIMATE].y,stars,2);
   black = allocol(0,0,0);
   XSetForeground(thedisplay,thegc,cp[black]);
   XFlush(thedisplay);
   if (debug <= 0) printf("dostarsb %d %d\n",halt,TRUE);
} /* dostars */
/******************************************/

redrawmenu()
/*
   to redraw the command menu

   called by  display, doframe
   calls  dostars
*/
{
   int s;

   if (debug <= 0) printf("redrawmenua %d %d\n",fwidth,thedepth);
   moveabs(fwidth,0);
   lineabs(fwidth,fwidth+2);
   if (debug <= 0) printf("redrawmenub %d\n",fwidth);
   for (s = 1; s < SMAX; ++s)
   {
      if (debug <= 0) printf("redrawmenuc %d\n",s);
      XCopyArea(
         thedisplay,segs[s].map,thewindow,thegc,
	 0,0,
         segs[s].w,segs[s].h,
         segs[s].x, theheight-segs[s].y-segs[s].h+1);
   }
   dostars();
} /* redrawmenu */
/******************************************/

drawmenu(n,prev,s)
int n,prev;
char s[];
/*
   draw a menu box and content.

   called by createcmndmenu
   calls     createsegment, linerel, text, closesegment,
*/
{
   segs[n].y = segs[prev].y+MH+1;
   segs[n].x = segs[prev].x;
   segs[n].h = MH;
   segs[n].w = MW;
   createsegment(n);
   linerel(segs[n].w,0);
   linerel(0,segs[n].h);
   linerel(-segs[n].w,0);
   linerel(0,-segs[n].h);
   moverel(0,2);
   text(s);
   closesegment(n);
} /* drawmenu */
/******************************************/

createsegment(n)
/*
   called by createcmndmenu.
*/
{
   segs[n].map = XCreatePixmap(
           thedisplay,thewindow,segs[n].w,segs[n].h,
           thedepth);
   currentx = segs[n].x;
   currenty = segs[n].y;
} /*  createsegment */
/******************************************/

closesegment(s)
int s;
/*
   close a segment

   called by  createcmndmenu.
*/
{
   XFlush(thedisplay);
   XCopyArea(
         thedisplay,thewindow,segs[s].map,thegc,
         segs[s].x, theheight-segs[s].y-segs[s].h+1,
         segs[s].w,segs[s].h,
         0,0);
} /* closesegment */
/******************************************/

text(s)
char s[];
/*
   draw some text

   called by createcmndmenu
*/
{
   int l;

   l = strlen(s);
   XDrawString(thedisplay,thewindow,thegc,
      currentx,theheight-currenty,s,l);
} /* text */
/******************************************/

moverel(x,y)
int x,y;
/*
   called by createcmndmenu.
*/
{
   if (debug < 0)
      printf("move rel %d %d %d %d\n",x,y,currentx,currenty);
   currentx += x;
   currenty += y;
} /*  moverel */
/******************************************/

moveabs(x,y)
int x,y;
{
   if (debug < 0)
      printf("move abs %d %d %d %d\n",x,y,currentx,currenty);
   currentx = x;
   currenty = y;
} /*  moveabs */
/******************************************/

linerel(x,y)
int x,y;
/*
   called by createcmdmenu
*/
{
   int okx,oky;

   if (debug < 0)
      printf("line rel %d %d %d %d\n",x,y,currentx,currenty);
   okx = x+currentx; oky = y+currenty;
   if (okx < 0) okx = 0;
   if (oky < 0) oky = 0;
   if (okx > thewidth) okx = thewidth;
   if (oky > theheight) oky = theheight;
   XDrawLine(thedisplay,thewindow,thegc,currentx,theheight-currenty,
                okx,theheight-oky);
   currentx = okx;
   currenty = oky;
} /* linerel */
/******************************************/

lineabs(x,y)
int x,y;
{
   int okx,oky;

   if (debug < 0)
      printf("line abs %d %d %d %d\n",x,y,currentx,currenty);
   okx = x; oky = y;
   if (okx < 0) okx = 0;
   if (oky < 0) oky = 0;
   if (okx > thewidth) okx = thewidth;
   if (oky > theheight) oky = theheight;
   XDrawLine(thedisplay,thewindow,thegc,currentx,theheight-currenty,
      okx,theheight-oky);
   currentx = okx;
   currenty = oky;
} /*  lineabs */
/******************************************/

awaitpick()
/*
   waiting for the mouse button or a keyboard key to be pressed

   called by doframe, image.
   calls     process.
*/
{
   char buf[BMAX];
   int found;
   int maxlen;
   int s;
   int slength;
   int thisw,thish;
   int thisx,thisy;
   int XCheckMaskEvent();
   XEvent theevent;
   KeySym thekeysym;
   XComposeStatus thecomposestatus;

   found = XCheckMaskEvent(thedisplay,EVMASK,&theevent);
   if ((found > 0) && (theevent.type == KeyPress))
   {
      maxlen = BMAX-1;
      if (debug <= 0) printf("awaitpickc %d\n",maxlen);
      slength = XLookupString
         (&theevent,buf,maxlen,&thekeysym,&thecomposestatus);
      if (debug <= 0) printf("awaitpickd %c\n",buf[0]);
      for (s = 1; s < SMAX; ++s)
      {
         if (keys[s] == buf[0])
         {
             process(s);
             if (halt == TRUE) sleep(1);
         }
      } /* s */
   }
   else
   if (theevent.type == ButtonPress)
   {
      thisx = theevent.xkey.x;
      thisy = theheight-theevent.xkey.y;
      for (s = 1; s < SMAX; ++s)
      {
            thisw = thisx-segs[s].x;
            thish = thisy-segs[s].y;
            if ((thisw >= 0) && (thisw <= segs[s].w)
               && (thish >= 0) && (thish <= segs[s].h) )
               {
                  process(s);
                  if (halt == TRUE) sleep(1);
               }
      }
   }
   for (s = 1; s < SMAX; ++s)
   {
      XCopyArea(
         thedisplay,segs[s].map,thewindow,thegc,
         0,0,
         segs[s].w,segs[s].h,
         segs[s].x, theheight-segs[s].y-segs[s].h+1);
   }

   if (pause == TRUE)
      XDrawString(thedisplay,thewindow,thegc,
         segs[PAUSE].x+3,theheight-segs[PAUSE].y,stars,2);
      else
         XDrawString(thedisplay,thewindow,thegc,
            segs[CYCLE].x+3,theheight-segs[CYCLE].y,stars,2);

   if (halt == TRUE)
      XDrawString(thedisplay,thewindow,thegc,
         segs[HALT].x+3,theheight-segs[HALT].y,stars,2);
      else
         XDrawString(thedisplay,thewindow,thegc,
            segs[ANIMATE].x+3,theheight-segs[ANIMATE].y,stars,2);
   
} /* awaitpick */
/*************************************/

clrsq(minx,miny,maxx,maxy)
int minx,miny,maxx,maxy;
/*
   clear square to put frame number in

   called by doframe.
*/
{
   GC		thegc1;
   int y;

/*
       XClearArea(thedisplay,thewindow,minx,miny,maxx,maxy,FALSE);
*/
   thegcvalues.background = BlackPixel(thedisplay, thescreen);
   thegcvalues.foreground = WhitePixel(thedisplay, thescreen);
   thegc1 = XCreateGC(thedisplay,thewindow,
             GCForeground | GCBackground, &thegcvalues);
   for (y = miny; y < maxy; ++y)
       XDrawLine(thedisplay,thewindow,thegc1,minx,y,maxx,y);
} /* clrsq */
/***********************************************/

hueset()
/*
   set up colours that are available

   called by doframe.
*/
{
   int c;
   int cmax;
   int cstep;
   int flag;
   int n;
   int newr,newg,newb;
   int okx1,okx2,oky1,oky2;
   int p;
   int red,green,blue;
   int snag;

   cmax = 16;
   snag = FALSE;
   ctop = DisplayCells(thedisplay,thescreen);
   if (debug < 1) printf("hueseta %d %d %d\n",cmax,ctop,thedepth);
   if ((debug < 1) && (ctop > cmax))
   {
      printf(
	 "showx: hueset: %d colours available, replaced by %d\n",
	    ctop,cmax);
      ctop = cmax;
   }
   cstep = CMAX;
   c = 0;
   for (cstep = CMAX; cstep > 16; cstep/=2)
   {
      if (debug < 1) printf("huesetb %d\n",cstep);
      for (red = 0; red <= CMAX; red += cstep)
      {
         for (green = 0; green <= CMAX; green += cstep)
         {
            for (blue = 0; blue <= CMAX; blue += cstep)
            {
   /*   scale 8 bit colours to 16 bits :-  */
               newr = red*CFAC; newg = green*CFAC; newb = blue*CFAC;
               if (newr < 0) newr = 0;
               if (newg < 0) newg = 0;
               if (newb < 0) newb = 0;
               if (newr > WMAX) newr = WMAX;
               if (newg > WMAX) newg = WMAX;
               if (newb > WMAX) newb = WMAX;
               cell.red = newr;
               cell.green = newg;
               cell.blue = newb;
               flag = XAllocColor(thedisplay,cmap,&cell);
               if ((snag == FALSE) && (debug < 0) && (flag == 0))
               {
		  snag == TRUE;
                  fprintf(stderr,
		     "showx: XAllocColor snag with %d %d %d getting %d %d %d\n",
	                  newr,newg,newb,cell.red,cell.green,cell.blue);
               }
               p = cell.pixel;
	       for (n = 0; n < c; ++n)
               {
		  if (p == cp[n]) goto gotit;
               }
	       cp[c] = p;
               hue[c][0] = cell.red/CMAX;
	       hue[c][1] = cell.green/CMAX;
	       hue[c][2] = cell.blue/CMAX;
	       if (debug <= -1)
		  printf("huesetc %d %d %d    %d %d %d\n",
		     c,cstep,p,red,green,blue);
	       ++c;

gotit:
	       if (c >= ctop) goto gotem;
            } /* blue */
         } /* green */
      } /* red */
   } /* cstep */
gotem:
   if (debug <= 0)
   {
      for (c = 0; c < ctop; ++c)
         printf("huesetd %2d %2d   %d %d %d\n",
	    c,cp[c],hue[c][0],hue[c][1],hue[c][2]);
   }
   if (debug < 1) printf("huesete %d\n",ctop);
} /* hueset */
/*****************************************/

int allocol(r,g,b)
int r,g,b;
/*
   find nearest available colour to (r,g,b) in own table
   ( 0 =< r,g,b <= 255 )

   called by colpoint, doframe.
*/
{
   int dsq;
   int c;
   int dsqmin;
   int cmin;

   dsqmin = CMAX*CMAX*CMAX;
   for (c = 0; c < ctop; ++c)
   {
      dsq  = (hue[c][0]-r)*(hue[c][0]-r);
      dsq += (hue[c][1]-g)*(hue[c][1]-g);
      dsq += (hue[c][2]-b)*(hue[c][2]-b);
      if (dsq < dsqmin)
      {
	 cmin = c;
	 dsqmin = dsq;
      }
   }
   if (debug <= 0)
   {
      printf("allocol %d %d %d   %d   %d %d %d   %d\n",
	 r,g,b,cmin,hue[cmin][0],hue[cmin][1],hue[cmin][2],dsqmin);
   }
   return(cmin);
} /* allocol */
/*****************************************/
