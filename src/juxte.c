/*
                     juxte.c

   juxtapose 2 sets of images to make stereo pairs

   Usage: juxte infileleft infileright outfile [-b n] [-d n] [-l n] [-s n]

   Flags-
	 -b : begin at frame "n"
	 -d : set debug parameter to "n".
	 -s : separate images by "n" pixels.
	 -l : do "n" images


   File format (ppm) -
      4 initial lines of format data -
	 P3
         width
         height
         colmax
      then three integers per pixel of width*height values.

   subroutines -
      main           - organises things
      getpar         - get invoked parameters
      getfile        - get the image files
      tryfile        - try various file types
      isfile         - find full name of image file
      checkhead      - check header of image file
      doframe        - load line buffer and print it
      exec           - execute a system command
      getout         - exit gracefully
      combine        - print combined image line out
      openout        - open output file

       21 Apr 1998   cleaned up
        7 Jun 1996   converted to ppm format input and output
        4 Apr 1996   written (Don Herbison-Evans)
*/
#include <stdio.h>
#include <values.h>
#include "X11/Xlib.h"
#include "X11/Xutil.h"

#define BMAX    256        /* size of string buffers */
#define FMAX    10         /* number of figure types */
#define PMAX    1000       /* max number of frames */
#define XMAX    1024       /* max width of image */
#define TRUE    1
#define FALSE   0

char  buf[BMAX];	/* input string buffer */
char  cmnd[BMAX];	/* shell command string buffer */
char  err[BMAX];	/* error message string buffer */
char  filelname[BMAX];  /* original left image file name */
char  filername[BMAX];  /* original right image file name */
char  finame[BMAX];     /* current input file name */
char  fliname[BMAX];	/* root+image type left file name stem */
char  friname[BMAX];	/* root+image type right file name stem */
char  flname[BMAX];	/* root name of left image file names */
char  frname[BMAX];	/* root name of right image file names */
char  foname[BMAX];     /* root name of output files */
char  home[BMAX]        = "/rose/don";
char  infile[BMAX];     /* current input image file name */
char  outfile[BMAX];    /* output image file name */

int   black;
int   blank;            /* blanks to separate images */
int   bgr,bgl;          /* backgrounds of images */
int   cmax;             /* maximum colour index */
int   count;            /* output file line counter */
int   debug;            /* <= 0 for debugging info to be printed */
int   f;		/* current frame number */
int   fheight;          /* height of the frame */
int   flheight;         /* height of the left image */
int   frheight;         /* height of the right image */
int   first = TRUE;     /* true when doing first frame */
int   fwidth;           /* width of the current image */
int   flwidth;          /* width of the left image */
int   frwidth;          /* width of the right image */
int   height;           /* height of output image */
int   length;		/* number of frames to be processed */
int   line[XMAX];       /* output line buffer */
int   nfr;		/* number of current frame */
int   ok;               /* true if image file obtained  */
int   sepn;             /* separation of images */
int   start;		/* number of first frame file */
int   step;		/* increment between frame numbers */
int   stop;             /* number of last frame file */
int   width;            /* width of output image */
int   xspot;            /* width of focussing spot */
int   yspot;            /* height of focussing spot */
int   white;

FILE  *INFILE;
FILE  *INFILEL;
FILE  *INFILER;
FILE  *OUTFILE;

/************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls  getpar, getfiles, getout.
*/
{
   xspot = 10; yspot = 10;
   black = 0; white = 255;
   getpar(argc,argv);
   getfiles();
   getout(0);
} /* main */

/************************************************/

getpar(argc,argv)
int argc;
char *argv[];
/*
   get the parameters

   called by main.
   calls     getout.
*/
{
   int p;
   int x;
   int value;

   debug = 1;
   sepn = 0;
   start = 0;
   step = 1;
   length = PMAX;
   stop = length;
   blank = 255;
   if (argc < 4)
   {
       sprintf(cmnd,"more %s/src.nudes/juxte.c\n",home);
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
	  {
	     if (p == 1)
                sprintf(flname,"%s",argv[p]);
	     else
	     if (p == 2)
                sprintf(frname,"%s",argv[p]);
	     else
	     if (p == 3)
                sprintf(foname,"%s",argv[p]);
             else
	     {
		sprintf(err,"juxte: funny %dth parameter:%s",p,argv[p]);
		getout(1);
	     }
	  } /* buf0 != - */
	  else
          if (buf[1] == 'b')
	  {
	     ++p;
	     sscanf(argv[p],"%d",&start);
	  }
	  else
          if (buf[1] == 'd')
	  {
	     ++p;
	     sscanf(argv[p],"%d",&debug);
	  }
	  else
          if (buf[1] == 'l')
	  {
	     ++p;
	     sscanf(argv[p],"%d",&length);
	  }
          else
	  if (buf[1] == 's')
	  {
	     ++p;
	     sscanf(argv[p],"%d",&sepn);
	  }
	  else
          {
             sprintf(err,"unrecognized flag: %s",argv[p]);
             getout(1);
          }
       }
   }
   if (length == PMAX)
   {
      length = (length-1)*step+1;
      if (step != 1) printf(
        "max length changed to %d\n",length);
   }
   stop = start + step*length ;
   if (debug <= 0)
   {
      printf("left file %s\n",flname);
      printf("right file %s\n",frname);
   }
} /* getpar */

/************************************************/

getfiles()
/*
   run through files

   called by main.
   calls     isfile, tryfile, doframe, getout.
*/
{
   int nextl,nextr;
   int tryfile();
   int isfile();

   if (debug <= 0)
      printf("getfilesa %s %s %d\n",flname,frname,start);
   f = 0;
   first = TRUE;
   sprintf(fliname,"%s",flname);
   sprintf(friname,"%s",frname);
   if (start < 0) start = 0;
   if (start == 0)
   {
      if ((tryfile(start,flname,fliname) == FALSE)
       || (tryfile(start,frname,friname) == FALSE))
	  start = 1;
   }
   stop = start+step*length;
   if (debug <= 0)
      printf("getfilesb %d %d\n",start,stop);
   for ( nfr = start; nfr < stop; nfr += step)
   {
      if (debug <= 0) printf("getfilesc %d\n",nfr);
      nextl = tryfile(nfr,flname,fliname);
      nextr = tryfile(nfr,frname,friname);
      if (debug <= 0) printf("getfilesd %d\n",nfr);
      nextl = isfile(fliname,nfr);
      INFILEL = INFILE; 
      bgl = 255;
      flwidth = fwidth; flheight = fheight;
      nextr = isfile(friname,nfr);
      INFILER = INFILE;
      bgr = 255;
      frwidth = fwidth; frheight = fheight;
      if (debug <= 0)
         printf("getfilese %d %d\n",flwidth,frwidth);
      if ((nextl == TRUE) && (nextr == TRUE))
      {
	  openout(nfr);
	  width = flwidth+sepn+frwidth;
	  if (flheight > frheight) height = flheight;
	     else height = frheight;
          fprintf(OUTFILE,"P3\n %d\n %d\n %d\n",
	     width,height,cmax);
          doframe();
          if (count != 0) fprintf(OUTFILE,"\n");
	  fclose(OUTFILE);
	  sprintf(cmnd,"chmod 775 %s\n",outfile);
	  exec(cmnd);
      } /* next true */
      else
      {
         if (nfr == start)
         {
            sprintf(err,
                  "can't open file like %s or %s for reading",
                  fliname,friname);
            sprintf(cmnd,"rm -rf /tmp/%s.*\n",fliname);
	    exec(cmnd);
            sprintf(cmnd,"rm -rf /tmp/%s.*\n",friname);
	    exec(cmnd);
            getout(1);
         } /* nfr = start */ 
         else
	 {
            sprintf(cmnd,"rm -rf /tmp/%s.*\n",fliname);
	    exec(cmnd);
            sprintf(cmnd,"rm -rf /tmp/%s.*\n",friname);
	    exec(cmnd);
	    goto dis;
	 } /* nfr = start */
      } /* next false */
      sprintf(cmnd,"rm -rf /tmp/%s*\n",fliname);
      exec(cmnd);
      sprintf(cmnd,"rm -rf /tmp/%s*\n",friname);
      exec(cmnd);
      if (f > length)
      {
          printf("more than %d frames\n",length);
          ok = FALSE;
          goto dis;
      } /* f > length */
      ++ f;
   } /* nfr */
   
dis:
   if (f > 1) printf("%d frames written\n",f);
      else printf("%d frame written\n",f);
   sprintf(cmnd,"rm -rf /tmp/%s*\n",fliname); exec(cmnd);
   sprintf(cmnd,"rm -rf /tmp/%s*\n",friname); exec(cmnd);
   if (debug <= 0) printf("getfilesf %d %d\n",start,stop);
}  /* getfiles */
/***********************************************/

int tryfile(nfr,fname,finame)
int nfr;
char fname[BMAX];
char finame[BMAX];
/*
   try various types of files for same root name
   'fname' and frame number 'nfr', leaving name
   in 'finame' if ok.

   called by getfiles.
   calls     isfile.
*/
{
   int k;
   int type;

   if (debug < 0)
         printf("tryfilea %d %d %s\n",nfr,type,fname);
   sprintf(finame,"%s",fname);
   if (isfile(finame,nfr) == TRUE) goto gotit;
   return(FALSE);

gotit:
   fclose(INFILE);
   if (debug <= 0)
         printf("tryfileb %s %d %d %d\n",fname,nfr,fwidth,fheight,cmax);
   return(TRUE);
} /* tryfile */
/*************************************************/

int isfile(ftmp1,nfr)
char ftmp1[BMAX];
int nfr;
/*
   check whether there is a file for nfr'th frame,

   called by getfiles, tryfile.
   calls     checkhead, getout.
*/
{
   int  comprd;	/* true if current frame is compressed */
   int  ok;
   char filename[BMAX];
   char ftmp2[BMAX];
   char ftmp3[BMAX];
   char ftmpz[BMAX];

   ok = FALSE;
   fwidth = -1;
   fheight = -1;
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
              sprintf(ftmp2,"%s.000%d.ppm",ftmp1,nfr);
      if ((nfr >= 10) && (nfr <= 99))
              sprintf(ftmp2,"%s.00%d.ppm",ftmp1,nfr);
      if ((nfr >= 100) && (nfr <= 999))
              sprintf(ftmp2,"%s.0%d.ppm",ftmp1,nfr);
      if (nfr >= 1000)
              sprintf(ftmp2,"%s.%d.ppm",ftmp1,nfr);
      sprintf(filename,"%s",ftmp2);
      if (debug < 0) printf("isfiled trying %s\n",ftmp2);
      if( NULL == (INFILE=fopen(ftmp2,"r")) )
      {
         sprintf(ftmpz,"%s.Z",ftmp2);
         sprintf(filename,"%s",ftmpz);
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
            if (debug < 0) printf("isfilef trying %s\n",ftmp3);
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
	ok,TRUE,nfr,fliname,friname,ftmp1,ftmp2,ftmp3,ftmpz,filename);
   if (ok == TRUE) checkhead();
   if (debug < 0)
      printf("isfileh %d %d %d\n",fwidth,fheight,cmax);
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
   char buf1[BMAX];
   int k;
   int temp;

   if (debug < 0) printf("checkheada\n");
   for (k = 0; k < 4; ++k)
   {
      fscanf(INFILE,"%s\n",buf1);
      if (debug < 0) printf("checkheadb %s\n",buf1);
      if (k != 0)
      {
	   sscanf(buf1,"%d",&temp);
           if (k == 1) fwidth = temp;
           else
	   if (k == 2) fheight = temp;
	   else
           if (k == 3) cmax = temp;
           else
	   {
	      sprintf(err,
                 "input header funny, frame %d\n%s\n",
		    f,buf1);
              getout(1);
	   }
      }
   }
   if (debug <= 0)
	 printf("checkheadc %d %d %d\n",
	    fheight,fwidth,cmax);
} /* checkhead */
/******************************************/

doframe()
/*
   load line buffer from image files
   and print it out.

   called by getfiles.
   calls     getout.
             
*/
{
   int c;
   int gray;
   int j,k;
   int p;
   int rl[XMAX],gl[XMAX],bl[XMAX];
   int rr[XMAX],gr[XMAX],br[XMAX];
   int x;
   int y;

   if (debug <= 0)
      printf("doframea %d %d %d %d\n",flwidth,frwidth,sepn,width);
   for (y = 0; y < height; ++y)
   {
      if (y < flheight)
      {
         for ( x = 0; x < flwidth; ++ x)
            fscanf(INFILEL,"%d %d %d",&rl[x],&gl[x],&bl[x]);
      }
      else
      for ( x = 0; x < flwidth; ++ x)
      {
	 rl[x] = blank;
	 gl[x] = blank;
	 bl[x] = blank;
      }

      if (y < frheight)
      {
         for ( x = 0; x < fwidth; ++ x)
            fscanf(INFILER,"%d %d %d",&rr[x],&gr[x],&br[x]);
      }
      else
      for ( x = 0; x < frwidth; ++ x)
      {
	 rr[x] = blank;
	 gr[x] = blank;
	 br[x] = blank;
      } /* x */
      combine(y,flwidth,rl,gl,bl,sepn,frwidth,rr,gr,br);
   } /* y */
   fclose(INFILEL);
   fclose(INFILER);
   if (debug <= 0) printf("doframeb %d %d\n",width,height);
} /* doframe */
/**********************************/

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

getout(v)
int v;
/*
   exit gracefully

   called by main, getpar, doframe, checkhead, isfile,
	     getframes, openout.
*/
{
   int j;

   if (v != 0) printf("juxte: %s\n",err);
   sprintf(cmnd,"rm -rf /tmp/%s*\n",fliname); exec(cmnd);
   sprintf(cmnd,"rm -rf /tmp/%s*\n",friname); exec(cmnd);
   exit(v);
} /* getout */
/*******************************************/

combine(y,lwidth,rl,gl,bl,sepn,rwidth,rr,gr,br)
int y,lwidth,sepn,rwidth;
int rl[XMAX],gl[XMAX],bl[XMAX];
int rr[XMAX],gr[XMAX],br[XMAX];
/*
   write line out

   called by  doframe.
*/
{
   int xx;
   int x;
   int xw;
   int xbl,xtl,xbr,xtr;
   int yb;
   int r,g,b;

   if (debug < 0)
      printf("combinea  %d %d\n",width,sepn);
   xx = 0;
   xbl = (lwidth-xspot)/2;
   xtl = (lwidth+xspot)/2;
   xbr = lwidth+sepn+(rwidth-xspot)/2;
   xtr = lwidth+sepn+(rwidth+xspot)/2;
   yb = height - yspot;
   if (sepn >= 0)
   {
      for (x = 0; x < lwidth; ++x)
      {
	 if ((xx > xbl) && (xx < xtl) && (y > yb))
            fprintf(OUTFILE,"%3d %3d %3d ",black,black,black);
         else
	    fprintf(OUTFILE,"%3d %3d %3d ",rl[x],gl[x],bl[x]);
	 if ((y == 100) && (debug < 0))
            printf("combineb %d %3d %3d %3d\n",x,rl[x],gl[x],bl[x]);
	 ++xx;
         count += 12;
         if (count > 57)
         {
            count = 0;
            fprintf(OUTFILE,"\n");
         }
      }
      for (x = 0; x < sepn; ++x)
      {
         fprintf(OUTFILE,"%3d %3d %3d ",blank,blank,blank);
	 ++xx;
         count += 12;
         if (count > 57)
         {
            count = 0;
            fprintf(OUTFILE,"\n");
         }
      }
      for (x = 0; x < rwidth; ++x)
      {
	 if ((xx > xbr) && (xx < xtr) && (y > yb))
            fprintf(OUTFILE,"%3d %3d %3d ",black,black,black);
         else
            fprintf(OUTFILE,"%3d %3d %3d ",rr[x],gr[x],br[x]);
         count += 12;
         if (count > 57)
         {
            count = 0;
            fprintf(OUTFILE,"\n");
         }
	 if ((y == 100) && (debug < 0))
            printf("combinec %d %d %3d %3d %3d\n",xx,x,rr[x],gr[x],br[x]);
	 ++xx;
      }
   } /* sepn >= 0 */
   else
   {
      xw = lwidth+sepn;
      for (x = 0; x < xw; ++x)
      {
	 if ((xx > xbl) && (xx < xtl) && (y > yb))
            fprintf(OUTFILE,"%3d %3d %3d ",black,black,black);
         else
	 if ((xx > xbr) && (xx < xtr) && (y > yb))
            fprintf(OUTFILE,"%3d %3d %3d ",black,black,black);
         else
            fprintf(OUTFILE,"%3d %3d %3d ",rl[x],gl[x],bl[x]);
         count += 12;
         if (count > 57)
         {
            count = 0;
            fprintf(OUTFILE,"\n");
         }
	 ++xx;
      }
      for (x = 0; x < -sepn; ++x)
      {
	 if ((rl[xw+x] == bgl) && (gl[xw+x] == bgl) && (bl[xw+x] == bgl))
	 {
	    r = rr[x]; g = gr[x]; b = br[x];
         }
	 else
	 if ((rr[x] == bgr) && (gr[x] == bgr) && (br[x] == bgr))
	 {
	    r = rl[xw+x]; g = gl[xw+x]; b = bl[xw+x];
         }
	 else
	 if (random() > 128)
	 {
	    r = rl[xw+x];
	    g = gl[xw+x];
	    b = bl[xw+x];
	 }
	 else
	 {
	    r = rr[x];
	    g = gr[x];
	    b = br[x];
	 }
	 if ((xx > xbl) && (xx < xtl) && (y > yb))
            fprintf(OUTFILE,"%3d %3d %3d ",black,black,black);
         else
	 if ((xx > xbr) && (xx < xtr) && (y > yb))
            fprintf(OUTFILE,"%3d %3d %3d ",black,black,black);
         else
            fprintf(OUTFILE,"%3d %3d %3d ",r,g,b);
         count += 12;
         if (count > 57)
         {
            count = 0;
            fprintf(OUTFILE,"\n");
         }
	 ++xx;
      } /* x */
      for (x = -sepn; x < rwidth; ++x)
      {
	 if ((xx > xbl) && (xx < xtl) && (y > yb))
            fprintf(OUTFILE,"%3d %3d %3d ",black,black,black);
         else
	 if ((xx > xbr) && (xx < xtr) && (y > yb))
            fprintf(OUTFILE,"%3d %3d %3d ",black,black,black);
         else
         fprintf(OUTFILE,"%3d %3d %3d ",rr[x],gr[x],br[x]);
         count += 12;
         if (count > 57)
         {
            count = 0;
            fprintf(OUTFILE,"\n");
         }
	 ++xx;
      }
      if (debug <= 0)
         printf("combinec  %d\n",xx);
   } /* sepn < 0 */
} /* combine */
/************************************************/

openout(nfr)
int nfr;
/*
   open output file

   called by getfiles.
   calls     getout.
*/
{
   if (debug <= 0) printf("openouta %d %s\n",nfr,foname);
   if ((nfr >= 0 ) && (nfr <= 9 ))
           sprintf(outfile,"%s.000%d.ppm",foname,nfr);
   if ((nfr >= 10) && (nfr <= 99))
           sprintf(outfile,"%s.00%d.ppm",foname,nfr);
   if ((nfr >= 100) && (nfr <= 999))
           sprintf(outfile,"%s.0%d.ppm",foname,nfr);
   if (nfr >= 1000)
           sprintf(outfile,"%s.%d.ppm",foname,nfr);
   if( NULL == (OUTFILE=fopen(outfile,"w+")) )
   {
      sprintf(err,"cannot open output file %s\n",outfile);
      getout(1);
   }
   count = 0;
} /* openout */
/************************************************/
 
int random()
/*
    return a random integer in the range 0 to 255.
 note : that a=123465,b=54321,c0=34567 gives a regular grid

 called by combine.
*/
{
   int ans;
   static unsigned int a=1234589,b=3432,c=4567;

   c = (b*c)%a;
   ans = 256*c/a;
   if (debug < -1)
         fprintf(stderr,"random %d %d %d %d\n",a,b,c,ans);
   return(ans);
} /* random */
/***************************************************/
