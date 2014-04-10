/*
   rasts.c

       prog to convert a primitive postscript file
                  into ppm image file.

    Only 'scale', 'lineto', and 'moveto' commands accommodated. 
    Lines beginning with anything other than 's','l', and 'm'
                       are ignored.

      Usage: rasts basename [xtop] < postscriptfile

      If 'xtop' <= 0, then size of picture is changed to
      accommodate all the vectors.
      Default 'xtop' = 256, with a square picture.
          
 modified
    255 max colours            20 Apr 1998
    automatic picture framing  26 Nov 1996
    accommodated scale command 20 Oct 1996
    fixed bug in convert       18 Oct 1996
    fixed y1 also in lib       14 Sep 1996
    fixed neg input bug        27 Jul 1996
    postscript input           16 Jul 1996
    output file name           17 Jun 1996
    ppm output                  6 Jun 1996
    modularised                 6 Aug 1993
    for Sun 3/50               11 Nov 1987
    arbitrary picture size      5 Jun 1986
    to speed it up             12 Feb 1986
    written                    16 Jan 1986 Don Herbison-Evans

  subroutines
    main     - organises things
    getargs  - get invocation arguements
    readfile - get chords from file
    checkxy  - find slopes of chords
    convert  - turn chords into a raster image
    getactive- find vectors intersecting current scan line
    shift    - fit pictureframe to vectors

 input
    The first is assumed to be '%!PS ddd' where ddd identifies the frame number.
    Each following line holds a coordinate pair (each in range 0 - 1000)
    followed by either 'moveto' or 'lineto' (for move or draw respectively).
    Other lines without this format are ignored.
*/

#include <stdio.h>
#include <values.h>

#define BMAX 256    /* max length of file name */
#define CMAX 256    /* max number of colours */
#define VMAX 20000  /* max number of vectors in picture */
#define TRUE 1
#define FALSE 0

int   adjust;       /* if true, scale the frame to fit all vectors */
int   black;
int   count;        /* counter through lines of output file */
int   debug;        /* <= 0 for diagnostic information */
int   fcount;       /* frame number */
int   hori[VMAX];   /* true if vector is horizontal */
int   nvecs;        /* number of vectors in picture */
int   white;
int   xhii[VMAX];   /* ends of intersections of vectors
                     with current scan line */
int   xloi[VMAX];   /* starts of intersections of vectors
                     with current scan line */
int   xmin;         /* lowest intersection on current scan line */
int   xmax;         /* highest intersection on current scan line */
int   xtop;         /* width of window */
int   ytop;         /* height of window */
int   y;            /* current scan line */

double doub0;
double doub1;
double doub10;
double doubmax;     /* a large number */
double dxdy[VMAX];  /* slopes of vectors */
double facx,facy;   /* scaling factors from world to screen */
double inv2;
double invthou;
double maxx,maxy;   /* largest values encoutered */
double minx,miny;   /* lowest values encountered */
double xold[VMAX];  /* intersections with previous scan line */
double xnew[VMAX];  /* intersections with currebt scan line */
double xx1[VMAX];   /* )                                    */
double xx2[VMAX];   /* )                                    */
                    /*    vectors: (xx1,yy1) to (xx2,yy2)   */
double yy1[VMAX];   /* )                                    */
double yy2[VMAX];   /* )                                    */

char  buf[BMAX];    /* input line buffer */
char  c;            /* first character of new line */
char  outfile[BMAX];/* output file name */

FILE  *OUTFILE,*fopen();

/*******************************************/

main(argc,argv)
int	argc;
char	*argv[];
/*
   calls getargs, readfile, convert.
*/
{
   debug = 2;
   adjust = FALSE;
   black = 0;
   white = 255;
   doub0 = (double)0;
   doub1 = (double)1;
   doub10 = (double)10;
   doubmax = (double)1000000 * (double)1000000;
   inv2 = doub1/(double)2;
   invthou = doub1/(double)1000;
   fcount = 1;
   getargs(argc,argv);
/*
     read frame -
*/
   readfile(argv);
   if (adjust == TRUE) shift();
   if (debug <= 1) fprintf(stderr,"rasts: image %d x %d\n",xtop,ytop);
   fprintf(OUTFILE,"P3\n %d\n %d\n %d\n",xtop,ytop,CMAX-1);
   convert();
   if (count > 0) fprintf(OUTFILE,"\n");
   fclose(OUTFILE);
   exit(0);
} /* main  */
/*******************************************/

getargs(argc,argv)
int	argc;
char	*argv[];
/*
   get arguements to initial program invocation

   called by main.
*/
{
   int w;

   if( argc < 2 )
   {
      fprintf(stderr,"Usage: rasts basename [xtop] < plotfile\n");
      exit(1);
   }
   xtop = 256;
   if (argc > 2) sscanf(argv[2],"%d",&w);
   if (w < 1)
      adjust = TRUE; 
   else
      xtop = w;
   facx = xtop*invthou;
   facy = facx;
   ytop = xtop;
   if (debug <= 0) fprintf(stderr,"getargsa %d\n",xtop);
} /* getargs */
/**********************************************/

readfile(argv)
char	*argv[];
/*
   read vector information

   called by main
*/
{
   int  frame;
   int  i;
   int  j;
   int  x,y;
   float fx,fy;
   char c;
   char junk[BMAX];
   char word[BMAX];
   double prevx,prevy;
/*
    get the frame number -
*/
   if (gets(buf) == NULL )
   {
      fprintf(stderr,
         "ERROR: rasts: input file empty\n");
      exit(1);
   }
   if ((buf[0] != '%') || (buf[1] != '!'))
   {
      fprintf(stderr,
         "ERROR: rasts: input not a postscript file\n");
      exit(1);
   }
   sscanf(buf,"%s %d\n",junk,&frame);
   if (debug < 0) fprintf(stderr,"readfilea %s %d\n",junk,frame);
/*
      create the output file name -
*/
   if ((fcount >= 0 ) && (fcount <= 9 ))
           sprintf(outfile,"%s.000%d.ppm",argv[1],fcount);
   if ((fcount >= 10) && (fcount <= 99))
           sprintf(outfile,"%s.00%d.ppm",argv[1],fcount);
   if ((fcount >= 100) && (fcount <= 999))
           sprintf(outfile,"%s.0%d.ppm",argv[1],fcount);
   if (fcount >= 1000)
           sprintf(outfile,"%s.%d.ppm",argv[1],fcount);
   if( NULL == (OUTFILE=fopen(outfile,"w+")) )
   {
      fprintf(stderr,
         "ERROR: rasts: can't open/create %s for writing\n",
            outfile);
      exit(1);
   }
   count = 0;
   if (debug < 0) fprintf(stderr,"readfileb %s\n",outfile);
/*
    read vectors -
*/
   j = 0;
   c = 'm';
   prevx = doub0;
   prevy = doub0;
   maxx = -doubmax;
   maxy = -doubmax;
   minx = doubmax;
   miny = doubmax;

   while (c != 'z')
   {
      if (gets(buf) == NULL )
      {
         c = 'z';
         goto done;
      }
      i = 0;
      for (i = 0; buf[i] == ' '; ++i);
      if ( (buf[i] == '-') || (buf[i] == '.') || (buf[i] == '+')
       || ((buf[i] >= '0') && (buf[i] <= '9')) )
      {
         sscanf(buf,"%g %g %s",&fx,&fy,word);
         x = fx; y = fy;
         if (debug < 0)
            fprintf(stderr,"readfilec %s %d %d %g %g\n",word,x,y,prevx,prevy);
         if  (strcmp(word,"scale") == 0) 
	 {
	    facx *= fx;
	    facy *= fy;
	 }
	 else
         if ( ( strcmp(word,"moveto")  == 0)
	   || ( strcmp(word,"lineto")  == 0) )
         {
            if (debug < 0)
               fprintf(stderr,"readfiled %c %d %d\n",word[0],x,y);
            if ( word[0] == 'l' )
            {
               xx1[j] = prevx;     yy1[j] = prevy;
               xx2[j] = x*facx;     yy2[j] = y*facy;
               checkxy(j);
               ++j;
               if (j >= VMAX)
               {
                  fprintf(stderr,
                     "ERROR: rasts: more vectors than %d\n",VMAX);
                  c = 'z';
                  goto done;
               }
            }
            prevx = x*facx;
            prevy = y*facy;
         }
      }
      else
         if (debug <= 1) fprintf(stderr,"ignored '%s'\n",buf);
   }
done:
   nvecs = j;
   if (debug <= 0) fprintf(stderr,"readfilef %d %s\n",
      nvecs,outfile);
} /* readfile */
/************************************/

checkxy(j)
int j;
/*
   put vectors the right way round,
   find min and max values of x and y,
   and find slope

   called by readfile.
*/
{
   double t;

   if (debug < 0) fprintf(stderr,"checkxya %d %g %g %g %g\n",
      j,xx1[j],yy1[j],xx2[j],yy2[j]);
   if (yy1[j] > yy2[j])
   {
      t=xx1[j]; xx1[j]=xx2[j]; xx2[j]=t;
      t=yy1[j]; yy1[j]=yy2[j]; yy2[j]=t;
   }
   if ( ( xx1[j] != xx2[j] ) || ( yy1[j] != yy2[j] ) )
   {
      if ((yy2[j]-yy1[j]) != doub0)
      {
         hori[j] = FALSE;
         dxdy[j] = (xx2[j]-xx1[j])/(yy2[j]-yy1[j]);
      }
      else
      {
         hori[j] = TRUE;
         dxdy[j] = doub0;
      }
   }
   if (xx1[j] < minx) minx = xx1[j];
   if (xx2[j] < minx) minx = xx2[j];
   if (yy1[j] < miny) miny = yy1[j];
   if (yy2[j] < miny) miny = yy2[j];
   if (xx1[j] > maxx) maxx = xx1[j];
   if (xx2[j] > maxx) maxx = xx2[j];
   if (yy1[j] > maxy) maxy = yy1[j];
   if (yy2[j] > maxy) maxy = yy2[j];
} /* checkxy */
/****************************************************/

convert()
/*
    convert vectors to raster format

    called by main.
*/
{

   int   j;
   int   nactive;
   int   x;
   int   bit;
   int   getactive();

   if (debug < 0) fprintf(stderr,
	 "converta %d %d\n", black,white);
/*
   find intersections of vectors with top scan line -
*/
   for ( j = 0; j < nvecs; ++j)
      if ( hori[j] == TRUE )
         xnew[j] = xx1[j];
      else
         xnew[j] = xx1[j] + (ytop-yy1[j])*dxdy[j];
/*
   do rest of scan lines -
*/
   for ( y = ytop; y > 0; --y)
   {
      nactive = getactive();
/*
     run across scan line -
*/
      if (debug < 0) fprintf(stderr,
	 "convertb %d %d\n", y,nactive);
      for (x = 0; x < xtop; ++ x)
      {
         bit = white;
         if ((x > xmin) && (x <  xmax))
         {
            for ( j=0; ( (j < nactive) && (bit == white) ); ++j)
            {
                if (( x < xhii[j]) && ( x >= xloi[j]) ) bit = black;
            }
         }
         fprintf(OUTFILE,"%3d %3d %3d ",bit,bit,bit);
         count += 12;
         if (count > 57)
         {
            count = 0;
            fprintf(OUTFILE,"\n");
         }
      }
   }
} /* convert */
/******************************************/

int getactive()
/*
   find the vectors intersecting current scan line

   called by convert
*/
{
   double xlo,xhi;
   int j;
   int k;

   k = 0;
   xmin = xtop; xmax = 0;
   for (j = 0; j < nvecs; ++j)
   {
      if ( hori[j] == TRUE )
      {
         xold[j] = xx1[j];
         xnew[j] = xx2[j];
      }
      else
      {
         xold[j] = xnew[j];
         xnew[j] = xx2[j] - (yy2[j]-y)*dxdy[j];
      }

      if (( (y+1) > yy1[j]) && (y <= yy2[j]))
      {
         xlo = xold[j];
         xhi = xnew[j];
         if (xlo > xhi)
         {
            xlo = xnew[j];
            xhi = xold[j];
         }
         if ((xlo < xx1[j] ) && (xx1[j] < xx2[j])) xlo = xx1[j];
         if ((xlo < xx2[j] ) && (xx2[j] < xx1[j])) xlo = xx2[j];
         if ((xhi > xx1[j] ) && (xx1[j] > xx2[j])) xhi = xx1[j];
         if ((xhi > xx2[j] ) && (xx2[j] > xx1[j])) xhi = xx2[j];
         xloi[k] = xlo-inv2;
         xhii[k] = xhi+inv2;
         if (xloi[k] < xmin) xmin = xloi[k];
         if (xhii[k] > xmax) xmax = xhii[k];
         ++k;
      }
   }
   xmin = xmin-1;
   if (debug < 0) fprintf(stderr,"getactivea %d %d\n",xmin,xmax);
   return(k);
} /* getactive */
/*******************************************/

shift()
/*
   adjust vectors and picture size to accommodate
   all the vectors.

   called by main.
*/
{
   int j;

   if (minx < doub0)
   {
      for (j = 0; j < nvecs; ++j)
      {
	 xx1[j] -= minx;
	 xx2[j] -= minx;
      }
      maxx -= minx;
   }
   if (miny < doub0)
   {
      for (j = 0; j < nvecs; ++j)
      {
	 yy1[j] -= miny;
	 yy2[j] -= miny;
      }
      maxy -= miny;
   }
   if (maxx > (double)xtop) xtop = (int)(maxx + doub10);
   if (maxy > (double)ytop) ytop = (int)(maxy + doub10);
} /* shift */

