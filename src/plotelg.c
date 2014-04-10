/*                    plotelg

     program to read an ellipse file, and to generate
     from it a postscript file of chords corresponding to
     the arcs of ellipses

         usage: plotelg u filename.2

         produces: filename.ps
         using u chords per ellipse outline
 
     modified -

     29/6/96   postscript output
    21/12/93   nsteps as parameter
      9/6/93   clipping improved
    14/11/92   cleaned up
     8/12/86   converted to c
     1/11/85   version for vax plot format
      3/3/85   compatible with visi and skel (Peter Gummer)
     14/2/83   write out chords
      2/2/83   pascal graphics of Newman/Sproull
      7/7/81   read parameters in tenth degrees (Chris Berry)
     11/6/80   for pussy/pascal/unix/vax11-780
 
     written 27/1/78 Don Herbison-Evans
 
     max number hidden arcs in one ellipse-  20
 
     method -   Cohen  and  and  Nicholson
          x  =  xcen + p*cos( alfa+theta )
          y  =  ycen + q*cos( beta+theta )
     where ( xcen,ycen) is ellipse centre
            theta  runs from 0 to 2pi
            p,q,alfa,beta depend on semiaxis lengths and angles.
 
*/

#include <stdio.h>

#define AMAX 200   /* maximum number of invisible arcs */
#define BMAX 123
#define XMAX 1000
#define TRUE 1
#define FALSE 0

double sqrt(),atan(),atan2(),sin(),cos();
double sqr();

double alfa; /* x parameter addend */
double beta; /* y parameter addend */
double disap[AMAX]; /* parameter value at beginning of jth
                       invisible arc around current ellipse */
double dtheta; /* step size of cohen parameter */
double doub0;
double doub1;
double p;     /* x scaling parameter */
double piby2;
double q;     /* y scaling parameter */
double rad10; /* conversion from 0.1 degree units to radians */
double twopi; /* ratio of circumference to radius of circle */
double theta;
double reapp[AMAX]; /* parameter value at end of jth invisible arc
              around current ellipse */
double xcen,ycen; /* coordinates of centre of current ellipse */
double xmax;
double xold,yold;

int    beam;   /* 0 if no line desired, 1 for line */
int    first;  /* flag for first frame */
int    frame;
int    debug;  /* controls amount of diagnostics printed */
int    m;
int    n;      /* number of current ellipse being drawn */
int    narcs;  /* number of invisible arcs in current ellipse */
int    nels;   /* number of ellipses in current picture */
int    nsteps; /* number of chords used to draw ellipse outline */

char     infile[BMAX],outfile[BMAX];

FILE     *INFILE,*OUTFILE;
/*
  subroutines -
    main
    getpars    - find nsteps and fname
    lineto     - draw a line from current point to new current point
    moveto     - move current point
    startframe - start a new frame
    endframe   - end a frame
    readel     - read data for an ellipse
    process    - generate arcs around an ellipse
    dopart     - generate chords along an arc
    sqr        - square a number

 variables -
   axx    - length of semiminor axis of current ellipse.
   axy    - semimajor axis.
   cphi   - cosine of orientation ( phi).
   phi    - angle of minor axis to coordinate x axis ( radians).
   sphi   - sine of orientation ( phi).
   x,y    - coordinates of next node on ellipse.

**********************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls startframe, readel, proces, endframe.
*/
{
   debug = 1;
   first = TRUE;
   doub1 = (double)1;
   doub0 = (double)0;
   twopi = (double)8*atan(doub1);
   piby2 = twopi/(double)4;
   rad10 = twopi/(double)3600;
   xmax = (double)XMAX;
   if (debug <= 0) fprintf(stderr,"maina %g\n",xmax);
   getpars(argc,argv);
   dtheta = twopi/nsteps;
/*
   run through the pictures -
*/
   while (nels > 0)
   {
      if ( first == TRUE) debug = frame;
      if ( debug <= 0) 
      {
           if ( first == TRUE ) 
                 fprintf(stderr,"mainb %f\n",rad10);
      }
      first = FALSE;
      startframe();
/*
     run thru ellipses in picture-
*/
      for (n = 0; n < nels; ++n)
      {
          readel();
          proces();
      }
      if ( NULL == fscanf(INFILE,"%d %d\n",&nels,&frame) )
      {
         fprintf(stderr,
            "\nERROR plotelg: unexpected EOF in middle of reading file %s\n",infile);
         exit(1);
      }
      if (debug <= 0) fprintf(stderr,"mainc %d %d\n", nels,frame);
      if ((nels < 0) || (nels > BMAX))
      {
         fprintf(stderr,
            "\nERROR plotelg: funny number of ellipsoids %d, max = %d\n",
              nels,BMAX);
         exit(1);
      }
      endframe();
   }
   exit (0);
} /* main */
/**********************************************/

getpars(argc,argv)
int argc;
char *argv[];
/*
   get the parameters : nsteps and fname

   called by main
*/
{
   char fname[BMAX];
   FILE *fopen();


   if (debug <= 0) fprintf(stderr,"getparsa\n");
   sscanf(argv[1],"%d",&nsteps);
   if (debug <= 0) fprintf(stderr,"getparsb %d\n",nsteps);
   if (nsteps < 1)
   {
      fprintf(stderr,
         "\nERROR plotelg nsteps = %d, reset to 1\n",nsteps);
      nsteps = 1;
   }
   if (nsteps > AMAX)
   {
      fprintf(stderr,
         "\nERROR plotelg nsteps = %d, reset to %d\n",
            nsteps,AMAX);
      nsteps = AMAX;
   }

   sprintf(fname,"%s",argv[2]);
   if (debug <= 0) fprintf(stderr,"getparsc %s\n",fname);
   sprintf(outfile,"%s.ps",fname);
   if( NULL == (OUTFILE = fopen(outfile,"w")))
   {
      fprintf(stderr,
         "\nERROR plotelg can't open %s for writing\n",outfile);
      exit(1);
   }
   sprintf(infile,"%s.2",fname);
   if( NULL == (INFILE = fopen(infile,"r")))
   {
      fprintf(stderr,"\nERROR plotelg can't open %s for reading\n",infile);
      exit(1);
   }
   if ( NULL == fscanf(INFILE,"%d %d\n",&nels,&frame) )
   {
      fprintf(stderr,
           "\nERROR plotelg: unexpected EOF reading file %s\n",infile);
      exit(1);
   }
   if (debug <= 0) fprintf(stderr,"getparsd %d %d\n", nels,frame);
   if (nels <= 0) 
   {
      fprintf(stderr,
           "\nERROR plotelg: funny number of ellipsoids %d\n",nels);
      exit(1);
   }
} /* getpars */
/*****************************************/

lineto(x,y)
int x,y;
/*
    called by dopart
*/
{
    fprintf(OUTFILE,"%5d %5d lineto\n",x,y);
} /* lineto */
/**********************************************/
 
moveto(x,y)
int x,y;
/*
    called by dopart
*/
{
      fprintf(OUTFILE,"%5d %5d moveto\n",x,y);
} /* moveto */
/*********************************************/
 
startframe()
/*
   caled by main
*/
{
   fprintf(OUTFILE,"%%!PS %d\nnewpath\n",frame);
} /* startframe */
/***********************************************/

endframe()
/*
   called by main
*/
{
      fprintf(OUTFILE,"closepath\nstroke\nshowpage\n");
} /* endframe */
/**********************************************/
 
readel()
/*
    read stuff for an ellipse.

    called by main
    calls  sqr.
*/
{
   int       j,k;
   int       ixc,iyc,iaxx,iaxy,iphi;
   int       iapp0,iapp1;
   int       iapp2,iapp3;
   double    axx,axy,phi,cphi,sphi ;
/*
    set up position, size  and  and  orientation of ellipse -
*/
   if ( NULL == fscanf(INFILE,"%d %d %d %d %d %d\n",
       &ixc,&iyc,&iaxx,&iaxy,&iphi,&narcs) )
   {
      fprintf(stderr,
         "plotelg: readel found unexpected EOF on file %s\n",infile);
      exit(1);
   }
   if ( debug <= 0)
       fprintf(stderr,"readela %d %d %d %d %d %d\n",
          ixc,iyc,iaxx,iaxy,iphi,narcs);
   xcen = (double)ixc;
   ycen = (double)iyc;
   axx = (double)iaxx;
   axy = (double)iaxy;
   phi = rad10*(double)iphi;
   cphi = cos(phi); sphi = sin(phi);
   p = sqrt(sqr(axx*cphi)+sqr(axy*sphi));
   q = sqrt(sqr(axx*sphi)+sqr(axy*cphi));
   alfa = piby2+atan2(axy*sphi,axx*cphi);
   beta = piby2+atan2(axx*sphi,axy*cphi);
   if (debug <= -1)
      fprintf(stderr,"readelb %f %f %f %f %f %f %f\n",
              xcen,ycen,phi,p,q,alfa,beta);
/*
    get hidden arcs- 
*/
   k = 0;
   if (( narcs > 0) && (narcs < AMAX))
   {
      for (j = 0; j < narcs; ++j )
      {
         if ( NULL == fscanf(INFILE,"%d %d\n",&iapp0,&iapp1) )
         {
            fprintf(stderr,
               "plotelg: found unexpected EOF in file %s\n",
                   infile);
            exit(1);
         }
         if ( debug <= -1) fprintf(stderr,"readelc %d %d %d %f\n",
                j,iapp0,iapp1,rad10);
/*
  convert from 0.1 degree to radians, and eliminate null arcs- 
*/
         if ( iapp0 != iapp1 )
         {
            disap[k] = rad10*(double)iapp0;
            reapp[k] = rad10*(double)iapp1;
            if ( debug <= -1) fprintf(stderr,"readeld %f %d %f %f\n",
                rad10,k,disap[k],reapp[k]);
            k = k+1;
         }
      } /* j loop */
/*
   add an artificial arc to guard the list -
*/
      narcs = k+1;
      disap[k] = twopi+twopi;
      reapp[k] = twopi+twopi+twopi;
      if ( debug <= -1) fprintf(stderr,"readele %f %d %f %f\n",
               rad10,narcs,disap[k],reapp[k]);
   }
   else
   if ((narcs < 0) || (narcs > AMAX))
   {
          fprintf(stderr,"plotelg- bad data in readel\n");
          fprintf(stderr,"   number of hidden arcs %d\n",narcs);
          fprintf(stderr,"  maximum allowed %d\n",AMAX);
          fprintf(stderr," ellipsoid no. %d, frame no. %d\n",n,frame);
          exit(1);
   }
   if (debug <= -1)
   {
      for (k = 0; k < narcs; ++k)
      fprintf(stderr,"    %d %f %f\n",k,disap[k],reapp[k]);
   }
}   /*  readel  */
/****************************************/

proces()
/*
    routine to run a parameter from a min to a max value doing a
    process in steps whilst avoiding a series of ranges of
    parameter values.
 
    formal parameters-
      disap[j],reapp[j] - start  and  end respectively of
                                jth invisible arc.
      minth,maxth - min  and  and  max values of parameter to be run.
      narcs - number of ranges of parameters to be avoided.
      dtheta - step size of parameter.
      debug - zero || negative for diagnostics to be printed.
 
   variables-
      jarc - counter thru ranges in array 'appear'.
      theta - current value of parameter being considered.
 
       called by main
       calls   dopart
 
*/
{
     int       jarc;
     double    minth,maxth;

       minth = 0.0;
       maxth = twopi;
       if ( debug < 0)
          fprintf(stderr,"proces %d %f %f %f\n",
             narcs,minth,maxth,dtheta);
/*
   skip to first point-
*/
       xold = xcen; yold = ycen;
       beam = 0;
       jarc = 0;
       theta = minth;
       if (narcs > 0)
       {
          while (disap[jarc] <= minth)
          {
             theta = reapp[jarc];
             jarc = jarc+1;
          }
       }
       dopart();
/*
   start stepping theta :
*/
       while (theta < maxth)
       {
             theta = theta+dtheta;
             if ( debug <= -1 )
                   fprintf(stderr,"procesa %d %f %f %f\n",
                       jarc,theta,disap[jarc],reapp[jarc]);
             if ( theta > maxth) theta = maxth;
             if ((narcs > 0) && (jarc >= narcs))
             {
                theta = maxth;
                dopart();
             }
             else
             if ((narcs > 0) && (theta > disap[jarc]))
/*
    we have a cut chord, so draw to its start, skip to its end -
*/
             {
                   theta = disap[jarc];
                   dopart();
                   beam = 0;
                   theta = reapp[jarc];
                   dopart();
                   jarc = jarc+1;
             }
             else /* a normal unbroken step- */
                   dopart();
             if (nsteps < 3) theta += maxth;
       } /* theta loop */
}   /* proces */
/**************************************/

dopart()
/*
    draw cut chord up to the point specified by 'theta'+pi/2.

    called by proces
    calls  moveto, lineto
*/
{
    double      a,b;
    double      xnew,ynew;
    double      xa,ya,xb,yb;
    int         ixa,iya;
    int         ixb,iyb;

    if ( debug <= -1)
       fprintf(stderr,"doparta %d %f %f %f %f %f %f %f\n",
          debug,p,q,xcen,ycen,theta,alfa,beta);
    a = alfa+theta;  b = beta+theta;
    /* step around cc sin() bug - */
    if (a < twopi) a += twopi;
    if (b < twopi) b += twopi;
    if (a > twopi) a -= twopi;
    if (b > twopi) b -= twopi;
    xnew = p*cos(a)+xcen;
    ynew = q*sin(b)+ycen;
    ixa = 0; iya = 0;
    ixb = 0; iyb = 0;
    if ( beam == 1)
    {
       xa = xold; ya = yold;
       xb = xnew; yb = ynew;
       if ((xa < doub0) && (xb < doub0)) goto none;
       if ((ya < doub0) && (yb < doub0)) goto none;
       if ((xa > xmax) && (xb > xmax)) goto none;
       if ((ya > xmax) && (yb > xmax)) goto none;
       ixa =  xa; iya = ya;
       ixb =  xb; iyb = yb;
       {
          moveto( ixa,iya);
          lineto( ixb,iyb);
       }
    }
none:
       beam = 1;
       if ( debug <= -1 )
           fprintf(stderr,"dopartb %d %f %f %f %f %f %d %d %d %d\n",
               beam,theta,xold,yold,xnew,ynew,ixa,iya,ixb,iyb);
       xold = xnew; yold = ynew;
}  /*  dopart  */
/****************************************/

double sqr(x)
double x;
/*
   square a value

   called by readel.
*/
{
   return(x*x);
} /* sqr */
/********************************************/

