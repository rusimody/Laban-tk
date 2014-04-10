/*
                     lentic6.c

   interlace a set of images to make stereo combinations
   for use with a lenticular screen covering.

   Usage: lentic infile1 infile2 .... > outfile

       16 Nov 2002   ensure arrays initialised
       22 Jun 1999   take averages correctly
       21 Jun 1999   to take multiple input files
       20 Jun 1999   written (Don Herbison-Evans)

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
      tryfile        - try to open a file
      checkhead      - check header of image file
      doframe        - run through images
      combine        - print combined image out
      exec           - execute a system command
      getout         - exit gracefully

*/
#include <stdio.h>
#include <values.h>
#include "X11/Xlib.h"
#include "X11/Xutil.h"

#define BMAX    256     /* size of string buffers */
#define FMAX    64      /* max number of input files */
#define TRUE    1
#define FALSE   0

char  buf[BMAX];        /* input string buffer */
char  cmnd[BMAX];       /* shell command string buffer */
char  err[BMAX];        /* error message string buffer */
char  home[BMAX]        = "../src";


int   cmax[FMAX];       /* maximum colour indices */
int   count;            /* output file line counter */
int   debug;            /* <= 0 for debugging info to be printed */
int   height[FMAX];     /* heights of input file images */
int   n;                /* current file number */
int   nfiles;           /* number of input files */
int   width[FMAX];      /* widths of input file images */

FILE  *INFILE[FMAX];

/************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls  getpar, getfiles, doframe, getout.
*/
{
   debug = 1;
   count = 0;
   getpar(argc,argv);
   getfiles(argc,argv);
   doframe(nfiles);
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
   if (argc < 2)
   {
       sprintf(cmnd,"more %s/src/lentic.c\n",home);
       exec(cmnd);
       exit(0);
   }
   else
   if (argc > FMAX)
   {
       sprintf(err," %d more than %d files\n",
          argc,FMAX);
       getout(1);
   }
   nfiles = argc -1;
} /* getpar */

/************************************************/

getfiles(argc,argv)
int argc;
char *argv[];
/*
   run through files

   called by main.
   calls     isfile, tryfile, doframe, getout.
*/
{
   int tryfile();

   if (debug <= 0)
      printf("getfilesa %s %d\n",argv[1],argc);
   width[0] = 1;
   height[0] = 1;
   cmax[0] = 1;

   for ( n = 1; n < argc; ++n )
   {
      if (debug <= 0)
         fprintf(stderr,"getfilesc %d %s\n",n,argv[n]);
      tryfile(n,argv[n]);
   } /* n */
   
   if (debug <= 0)
      fprintf(stderr,"getfilesd %d %d %d\n",width[0],height[0],cmax[0]);
   printf("P3\n");
   printf("%d\n",width[0]);
   printf("%d\n",height[0]);
   printf("%d\n",cmax[0]);
}  /* getfiles */
/***********************************************/

tryfile(n,fname)
int n;
char fname[BMAX];
/*
   try to open file "fname".

   called by getfiles.
   calls     checkhead, getout.
*/
{
   if (debug < 0)
         printf("tryfilea %d %s\n",n,fname);
   if ( NULL != (INFILE[n]=fopen(fname,"r")) )
   {   
         checkhead(n);
         if (width[n] != width[0])
         {
            sprintf(err,"width of %dth file %s : %d != %d\n",
                n,fname,width[n],width[0]);
            getout(n); 
         }
         if (height[n] != height[0])
         {
            sprintf(err,"height of %dth file %s : %d != %d\n",
                n,fname,height[n],height[0]);
            getout(n); 
         }
         if (cmax[n] > cmax[0]) cmax[0] = cmax[n];
   }
} /* tryfile */
/*************************************************/

checkhead(n)
int n;
/*
   check the heading of an image file 'n'

   called by tryfile.
   calls getout.
*/
{
   char buf1[BMAX];
   int k;
   int temp;

   if (debug < 0) printf("checkheada\n");
   for (k = 0; k < 4; ++k)
   {
      fscanf(INFILE[n],"%s\n",buf1);
      if (debug < 0) printf("checkheadb %s\n",buf1);
      if (k != 0)
      {
	   sscanf(buf1,"%d",&temp);
           if (k == 1) width[n] = temp;
           else
	   if (k == 2) height[n] = temp;
	   else
           if (k == 3) cmax[n] = temp;
           else
	   {
	      sprintf(err,
                 "input header funny, file %d\n%s\n",
		    n,buf1);
              getout(1);
	   }
      }
   }
   if ( n == 1)
   {
      width[0] = width[1];
      height[0] = height[1];
      cmax[0] = cmax[1];
   }
   if (debug <= 0)
	 fprintf(stderr,"checkheadc  %d %d %d %d\n",
	    n,height[n],width[n],cmax[n]);
} /* checkhead */
/******************************************/

doframe(nfiles)
int nfiles;
/*
   print result out.

   called by main.
   calls     combine.
             
*/
{
   int r[FMAX],g[FMAX],b[FMAX];
   int x,xx;
   int y;

   if (debug <= 0)
      printf("doframea %d %d\n",width[0],height[0]);
   for ( y = 0; y < height[0]; ++y )
   {
      for ( x = 0; x < width[0]; x += nfiles )
      {
         for ( n = 1; n <= nfiles; ++n )
         {
             for ( xx = 1; xx <= nfiles; ++xx )
                fscanf(INFILE[n],"%d %d %d",&r[xx],&g[xx],&b[xx]);
             combine(nfiles,r,g,b,x);
          }
       }
   } /* y */
   for ( n = 1; n <= nfiles; ++n )
      fclose(INFILE[n]);
} /* doframe */
/**********************************/

combine(nfiles,r,g,b,x)
int nfiles,x;
int r[FMAX],g[FMAX],b[FMAX];
/*
   combine images and write values out

   called by  doframe.
*/
{
   int xx;

   if (debug < 0)
      printf("combinea  %d %d %d %d %d %d %d %d\n",
         nfiles,r[1],g[1],b[1]);
   r[0] = 0; 
   g[0] = 0; 
   b[0] = 0;
   for (xx = 1; xx <= nfiles; ++xx )
   {
      r[0] += r[xx];
      g[0] += g[xx];
      b[0] += b[xx];
   }
   if (debug < -1)
      printf("combineb %d %d %d\n",
         r[0],b[0],g[0]);
   r[0] = r[0]/nfiles;
   g[0] = g[0]/nfiles;
   b[0] = b[0]/nfiles;
   printf("%3d %3d %3d ",r[0],g[0],b[0]);
   count += 12;
   if (count > 57)
   {
      count = 0;
      printf("\n");
   }
} /* combine */

/************************************************/

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
   if (v != 0) printf("lentic: %s\n",err);
   exit(v);
} /* getout */
/*******************************************/

