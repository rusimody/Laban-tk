/*
                 drawelx.c

      Interactive commands :-
          a - continue animating (opp. of 'i')
          b - if frozen, go back one frame (opp. of 'f')
              else run backwards (opp. of 'f')
          c - continue through restart at full rate (opp. of 'p')
          d - shift down 1% (opp. of 'u')
          f - if frozen, show next forward frame (opp.of 'b')
              else run forwards (opp.of 'b')
          g - grow scene by 10% (opp. of 's')
          h - show these instructions
          i - freeze (opp. of 'a')
          j = double the number of polygons per sphere {opp. of 'k')
          k - halve the number of polygons per sphere {opp. of 'j')
          l - shift scene left 1% (opp. of 'r')
          n - display of frame numbers (opp. of 'o')
          o - do not display frame numbers (opp. of 'n')
          p - pause on first and last frames (opp. of 'c')
          q - quit
          r - shift scene right 1% (opp. of 'l')
          s - shrink scene by 10% (opp. of 'g')
          t - shift scene away by 10 (opp. of 'T')
          u - shift up 1% (opp. of 'd')
          v - use filled  drawings (opp. of 'w')
          w - use wireframe drawings (opp. of 'v')
          x - rotate 10 degrees about x (left - right) axis (opp. of 'X')
          y - rotate 10 degrees about y (vertical) axis (opp. of 'Y')
          z - rotate 10 degrees about z (front - back) axis  (opp. of 'Z')
          0 - reset parameters to default values
          - - speed up by 1 frame per second
          + - slow down by 1 frame per second
          return - if frozen, show next frame

      display and animate 3D ellipsoid NUDES files
             under Unix with XWindows

    usage: drawelx [-b u] [-d u] [-e u] [-f u] [-h u] [-i u] [-l u]
             [-k u] [-n] [-p] [-s u] [-v] [-w] [-x u] [-y u] nudes3file

       23 Apr 1998   display speed
       17 Apr 1998   t for translate in z, +/- for speed
       10 Sep 1993   accommodates joint information
       26 Feb 1992   written : Don Herbison-Evans

      Flags :-
         -b begin at frame u (default: 1) 
         -d set debug value to u (default: 1: no debug information)
         -e show every u'th frame (default: 1)
         -f show at u frames per second (default: 25)
         -h height u pixels (default: 512, or 1000 for video)
         -i width u pixels (default: 512, or 1200 for video)
         -k use polygons of u sides (default: 12)
         -l show only u frames (default: highest frame number)
         -n show frame numbers (default: do not show frame numbers)
         -p pause for one second on first and last frames
            (default: no pause)
         -s start at frame u (default: 1) 
         -v make video at VisLab
         -w use wireframe drawings (default: filled)
         -x set lower left x coordinate (default: 10)
         -y set lower left y coordinate (default: 10)

      Flags and arguements can be in any order.
      Using no flags or arguements gives a listing of these comments.

   Input -  
     The parameter 'nudes3file' is assumed to be .3 file from
     NUDES containing information about each frame-
     Each frame is headed by a line containing:
        the number of ellipsoids in that frame,
        the frame number, and
        the 6 viewing parameters.
     This is followed by a line of integer numeric data
     for each ellipsoid containing:-
        the 3 coordinates of the centre,
        the 3 semiaxis lengths,
        the 3 quaternion angles and
        the red, green, blue colours 
        its name,
        and the name of its texture map file
     Then there is a line with -1 and the number of joints.
     This is followed with one line for each joint containing:-
        the 2 ellipsoids joined
        the 3 coordinates
        and its name

     (assumes the picture is 10000 units wide,
      and angles in tenths of a degree) 
   
   Subroutines:
      main
      initialise
      initiris
      initsphere
      getpar
      loadfr
      getells
      mkrotn
      rotget
      image
      mkr
      matmul
      checkeys
      rget
      drawsphere
      display
      systry
      getout
      reset

*/

#include <stdio.h>
#include <math.h>
#include <values.h>
#include <gl.h>
#include <device.h>
/***
#define WHITE 0
#define TRUE 1
#define FALSE 0
#define RED 1
#define MATERIAL 0
#define DEFMATERIAL 0
#define KEYBD 0
#define LMODEL 0
#define LIGHT0 0
#define DEFLIGHT 0
#define DEFLMODEL 0
#define MVIEWING 0
#define DIFFUSE 0
#define AMBIENT 0
#define EMISSION 0
#define SPECULAR 0
#define SHININESS 0
#define LMNULL 0
#define POSITION 0
#define LCOLOR 0
#define GD_YPMAX 0
#define GD_XPMAX 0
#define GD_BITS_NORM_DBL_RED 0
#define GD_BITS_NORM_DBL_GREEN 0
#define GD_BITS_NORM_DBL_BLUE 0
***/

#define ELL     WHITE+2  /* start of user defined colours */
#define BMAX    256      /* size of character buffer */
#define CMAX    256      /* maximum number of colours */
#define EMAX    1024     /* maximum number of ellipsoids per frame */
#define NMAX    256      /* maximum number of frames */
#define PMAX    128      /* size of arrays of facets of sphere */
#define ZERO      0
#define RATE     25
#define MILLION 1000000

char  err[BMAX];          /* error message */
char  num[BMAX];          /* digits of current frame number */
char  fname[BMAX];        /* name of nudes.3 file */

short  value;             /* latest interrupt value */
short  indx,nm,nl,null;   /* parameters of lmdef etc */
short  col[EMAX][3];      /* colours in use */
int   ci;          /* current colour index */

int   angx,angy,angz;     /* interactive rotation angles
                                   (tenths of a degree) */
int   begin = TRUE;       /* True while reading data file */
int   c[3];               /* current RGB values */
int   dang = -50;         /* interactive angle increment
                                   (tenths of a degree) */
int   debug = 1;          /* controls diagnostic output */
int   dev;                /* holds latest interrupt device  */
int   df = 1;             /* increment for next frame number */
int   dofr = FALSE;       /* true if frame numbers to be shown */
int   elcol[NMAX][EMAX];  /* colour of each ellipsoid */
int   f;                  /* current frame number */
int   fill = TRUE;        /* false for wireframe drawings */
int   flag;               /* -1 if joints found in frame */
int   frame[NMAX];        /* name of current frame of input */
int   freeze = FALSE;     /* true for interactive display */
int   frstart = 1;        /* name of first frame */
int   fstop;              /* index of last frame */
int   gid;                /* identifier of window */
int   height = 512;       /* height  of window in pixels */
int   infound = FALSE;    /* true if input file found,
                             false for standard input  */
int   ia1[NMAX],ia2[NMAX],ia3[NMAX]; /* viewing angles */
int   ivx[NMAX],ivy[NMAX],ivz[NMAX]; /* viewing position */
int   length = NMAX;      /* number of frames to be shown */
int   hold = FALSE;       /* true to pause on first & last frame */
int   maxr,maxg,maxb;     /* number of bits for each colour */
int   maxw,maxh;          /* size of screen */
int   ncols = ELL;        /* number of colours in use */
int   nels[NMAX];         /* number of ellipsoids in each frame */
int   nsph;               /* number of chords around sphere */
int   nfaces;             /* number of faces on sphere */
int   speed = RATE;       /* number of frames per second */
int   step = 1 ;
int   video = FALSE;      /* if TRUE make video at VisLab */
int   width = 512;        /* height  of window */
int   x = 10;
int   y = 10;             /* lower left corner of window */
long   white[3] = {255,255,255};
long   purple[3] = {255,0,255};
long   red[3] = {255,0,0};
float sx,sy,sz; /* interactive scaling factors */
float tx,ty,tz; /* interactive translations */
float pi,twopi,radian;    /* 3.14159 etc */
float sph[PMAX*PMAX][4][3];  /* vertices of facets of  sphere */
float norm[PMAX*PMAX][3]; /* normals of sphere faces */
float cen[NMAX][EMAX][3]; /* coordinates of ellipsoid centres */
float ax[NMAX][EMAX][3];  /* lengths of semiaxes of ellipsoids */
float rotn[NMAX][EMAX][4][4];/* orientation matrix of ellipsoid */
float material[] = 
              {
                DIFFUSE,  0.9,0.9,0.9,
                AMBIENT,  0.9,0.9,0.9,
                EMISSION, 0.0,0.0,0.0,
                SPECULAR, 0.1,0.1,0.1,
                SHININESS, 0.5, LMNULL};
static float light[] =
              { POSITION, 0.0,1.0,0.0,0.0,
                AMBIENT,  0.1,0.1,0.1,
                LCOLOR,   0.9,0.9,0.9, LMNULL};
                 
FILE *infile;

/************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls   getpar, initialise, initiris, initsphere,
           loadfr, and display.
*/
{
   if (debug <= 2) printf("drawelx\n");
   initialise();
   getpar(argc,argv);
   initiris();
   initsphere(1.0, 0.0,0.0,0.0);
   loadfr();
   begin = FALSE;
   display();
   exit(0);
} /* main */
/***********************************/

initialise()
/*
   set up constants to default values

   called by main.
*/
{
   if (debug <= 2) printf("initialisea\n");
   df = 1;
   speed = RATE;
   freeze = FALSE;
   nsph = 8;
   hold = FALSE;
   sx = 1.0; sy = 1.0; sz = 1.0;
   angx = 0; angy = 0; angz = 0;
   tx = 0.0; ty = 0.0; tz = 0.0;
   pi = 4.0*atan(1.0);
   twopi = pi+pi;
   radian = twopi/3600.0;
} /* initialise */
/************************************/

initiris()
/*
   open iris graphics system -
*/
{
   int wider;

   indx = 1;
   nm = 19;
   nl = 14;
   null = 0;
   if (width > height) wider = TRUE;
      else wider = FALSE;
   if (debug <= 0)
      printf("initiris %d %d %d\n",x,y,height);
   maxh = getgdesc(GD_YPMAX);
   maxw = getgdesc(GD_XPMAX);
   maxr = getgdesc(GD_BITS_NORM_DBL_RED);
   maxg = getgdesc(GD_BITS_NORM_DBL_GREEN);
   maxb = getgdesc(GD_BITS_NORM_DBL_BLUE);
   if (((x+width) > maxw) || ((y+height) > maxh))
   {
      sprintf(err,"draweln: screen only %d by %d, not %d by %d\n",
         maxw,maxh,x+width,y+height);
      getout(1);
   }
   if (width > maxw) width = maxw;
   if (height > maxh) height = maxh;
   if ((maxr == 0) || (maxb == 0) || (maxg == 0))
   {
       if (fill == TRUE)
          printf("draweln: too few colour planes to fill polygons\n");
       fill = FALSE;
   }
   prefposition(x,x+width,y,y+height);
   gid = winopen("draweln");
   doublebuffer();
   if (fill == TRUE) RGBmode();
   gconfig();
   if (fill == TRUE) c3i(purple);
      else
   {
      mapcolor(WHITE+1, 90,0,90);
      color(WHITE+1);
   }
   clear();
   mmode(MVIEWING);
   viewport(1,width-1,1,height-1);
   if (wider)
     ortho(-10.0,width*1000.0/height, -10.0,1000.0, 0.0,-10000.0);
   else
     ortho(-10.0,1000.0, -10.0,height*1000.0/width, 0.0,-10000.0);
   lookat( 0.0,0.0,1.0, 0.0,0.0,-1.0, 0);
   zbuffer(fill);
   lmdef(DEFLIGHT,indx,nl,light);
   lmdef(DEFLMODEL,indx,null,NULL);
   lmbind(LIGHT0,indx);
   lmbind(LMODEL,indx);
   qdevice(KEYBD);
} /* initiris */
/****************************************/

initsphere(rad,x,y,z)
float rad,x,y,z;
{
   int i,j,k,m,n;
   float dlat,dlong;
   float inclat,jj;
   float dval,magnitude;
   float sum;
   float point[PMAX][PMAX][3];

   if (debug <= 0)
      printf("initspherea  %d %f %f %f %f\n",nsph,rad,x,y,z);
   dlat = (float)nsph;
   dlong = (float)nsph;
   inclat = pi/2.0;
/*
   set up vertices -
*/
   for (i = 0; i < nsph; i++)
   {
      magnitude = cos(inclat)*rad;
      dval = sin(inclat)*rad;
      for ( j = 0; j < nsph; ++ j)
         point[i][j][1] = (float)dval + y;;
      for ( j = 0; j < nsph; ++ j)
      {
         jj = (float)j;
         dval = cos(twopi*jj/dlong)*magnitude;
         point[i][j][0] = (float)dval + x;
         dval = sin(twopi*jj/dlong)*magnitude;
         point[i][j][2] = (float)dval + z;
         if (debug < 0) printf("initsphereb %d %d %f %f %f\n",
            i,j,point[i][j][0],point[i][j][1],point[i][j][2]);
      }
      inclat = inclat-(pi/(dlat-1.0));
   }
/*
   set up faces aand their normals -
*/
   m = 0;
   for (i = 0; i < (nsph-1); ++i)
   {
      for (j = 0; j < (nsph-1); ++j)
      {
         for (k = 0; k < 3; ++k)
         {
            sph[m][0][k] = point[i][j+1][k];
            sph[m][1][k] = point[i+1][j+1][k];
            sph[m][2][k] = point[i+1][j][k];
            sph[m][3][k] = point[i][j][k];
            sum = 0.0;
            for (n = 0; n < 4; ++n)
               sum += sph[m][n][k];
            norm[m][k] = sum/4.0; 
         }
         ++m;
      }
   }
   for (i = 0; i < (nsph-1); ++i)
   {
         for (k = 0; k < 3; ++k)
         {
            sph[m][0][k] = point[i][0][k];
            sph[m][1][k] = point[i+1][0][k];
            sph[m][2][k] = point[i+1][nsph-1][k];
            sph[m][3][k] = point[i][nsph-1][k];
            sum = 0.0;
            for (n = 0; n < 4; ++n)
               sum += sph[m][n][k];
            norm[m][k] = sum/4.0; 
         }
         ++m;
   }
   nfaces = m;
   if (debug <= 0) printf("initspherec %d\n",nfaces);
}   /* initsphere */
/***********************************/

getpar(argc,argv)
int argc;
char *argv[];
/*
   get the parameters

   called by main.
*/
{
   int p;
   char  buf[BMAX];
   char  cmnd[BMAX];

   if (debug <= 2) printf("getpara\n");
   if (argc < 2)
   {
       sprintf(cmnd,"more /rose/don/src/draweln.c\n");
       systry(cmnd);
       getout(0);
   }
   else
   {
       for ( p = 1; p < argc; ++ p)
       {
          if (debug < 0) printf("%d %s\n",p,argv[p]);
          sprintf(buf,"%s",argv[p]);
          if (buf[0] != '-')
          {
             sprintf(fname,"%s.3",buf);
             if (NULL == (infile = fopen(fname,"r")))
             {
                sprintf(err,"cannot find input file %s",fname);
                getout(1);
             }
             infound = TRUE;
          }
          else
          switch(buf[1])
          {
             case 'b': ++ p;
                       sscanf(argv[p],"%d",&frstart);
                       if ((frstart < 0) || (frstart > NMAX) || (p >= argc))
                       {
                           printf("draweln: funny -b parameter- %d\n",frstart);
                           exit(1);
                       }
                       break;
             case 'd': ++ p;
		       sscanf(argv[p], "%d",&debug);
                       break;
             case 'e': ++ p;
		       sscanf(argv[p], "%d",&step);
                       printf("draweln: funny -e step size: %d ",step);
                       if (step < 1) step = -step;
                       if (step < 1) step = 1;
                       printf("         reset to %d\n",step);
                       break;
             case 'f': ++ p;
                       sscanf(argv[p],"%d",&speed);
                       if (p >= argc)
                       {
                           printf("draweln: no -f parameter value\n");
                           getout(1);
                       }
                       break;
             case 'h': ++p;
                       sscanf(argv[p],"%d",&height);
                       break;
             case 'i': ++p;
                       sscanf(argv[p],"%d",&width);
                       break;
             case 'k': ++p;
                       sscanf(argv[p],"%d",&nsph);
                       if ((nsph >= PMAX) || (nsph < 1))
                       {
                           printf(
                              "draweln: funny -k parameter- %d (max %d)\n",
				  nsph,PMAX-1);
                           exit(1);
                       }
                       break;
             case 'l': ++ p;
                       sscanf(argv[p],"%d",&length);
                       if ((length < 0) || (length > NMAX) || (p >= argc))
                       {
                           printf(
                              "draweln: funny -l parameter- %d (max %d)\n",length,NMAX);
                           exit(1);
                       }
                       break;
             case 'n': dofr = TRUE;
                       break;
             case 'p': hold = TRUE;
                       break;
             case 's': ++ p;
                       sscanf(argv[p],"%d",&frstart);
                       if ((frstart < 0) || (frstart > NMAX) || (p >= argc))
                       {
                           printf("draweln: funny -s parameter- %d",frstart);
                           exit(1);
                       }
                       break;
             case 'v': video = TRUE;
                       height = 1000;
                       width = 1200;
                       break;
             case 'w': fill = FALSE;
                       break;
             case 'x': ++ p;
		       sscanf(argv[p], "%d",&x);
                       if (x < 0)
                       {
                           printf("draweln: funny -x parameter- %d",x);
                           exit(1);
                       }
                       break;
             case 'y': ++ p;
		       sscanf(argv[p], "%d",&y);
                       if (y < 0)
                       {
                           printf("draweln: funny -y parameter- %d",y);
                           exit(1);
                       }
                       break;
          }
       }
   }
   if (length == NMAX) length = (length-1)*step+1;
   if (debug <= 0)
      printf("getpar %d %d %d %d %d %d %d %d %d %d\n",
         TRUE,hold,dofr,frstart,length,speed,fill,nsph,x,y);
} /* getpar */
/****************************************************/

loadfr()
/*
   get ellipsoids in each frame.

   called by main.
   calls  getells, image, checkeys, getout.
*/
{
   int j,k,n;
   int njts;
   int show;
   char buf[BMAX];

   f = 1;
   flag = -1;
   for (n = 1; n < NMAX; ++n)
   {
      checkeys();
      if (flag == -1)
      {
         if (infound == TRUE)
         {
            if (fgets(buf,BMAX,infile) == NULL)
            {
               sprintf(err,
                  "unexpected end of file %s at start of frame %d",
                     fname,f);
               getout(1);
            }
         }
         else
            gets(buf);
      }
      sscanf(buf,"%d %d %d %d %d %d %d %d\n",
           &nels[f],&frame[f],&ivx[f],&ivy[f],&ivz[f],
           &ia1[f],&ia2[f],&ia3[f]);
      show = TRUE;
      if (frame[f] < frstart) show = FALSE;
      if ((frame[f] - frstart)%step != 0) show = FALSE;
      if ((show == TRUE) && (debug <= 1))
         printf("load frame %d\n", frame[f]);
      if ((frame[f]-frstart) >= length) goto out;
      if (nels[f] <= 0) goto out;
      if (nels[f] > EMAX)
      {
         sprintf(err,"too many ellipsoids: %d > %d, frame %d\n",
            nels[f],EMAX,frame[f]);
         getout(1);
      }
      getells();
      if (infound == TRUE)
      {
         if (fgets(buf,BMAX,infile) == NULL)
         {
            sprintf(err,
            "unexpected eof %s, frame %d, reading number of joints\n",
                  fname,f);
            getout(1);
         }
      }
      else
         gets(buf);
      sscanf(buf,"%d %d", &flag,&njts);
      if (flag < 0)
      {
         for (j = 0; j < njts; ++j)
         {
            if (infound == TRUE)
            {
               if (fgets(buf,BMAX,infile) == NULL)
               {
                  sprintf(err,
                     "unexpected end of file %s at frame %d joint %d",
                     fname,f,j);
                  getout(1);
               }
            }
            else
               gets(buf);
         }
      }
      if (show == TRUE)
      {
         if (debug <= 0)
            printf("loadfrb %d %d %d\n",f,nels[f],frame[f] );
         image(f);
         ++f;
      }
   }
out:
   fstop = f;
   if (debug <= 0)
   {
      printf("loadfrc %d\n",fstop);
      for (j = 0; j < ncols; ++j)
         printf("   colour %d = %d %d %d\n",
            j,col[j][0],col[j][1],col[j][2]);
   }
}  /* loadfr */
/*******************************************/

getells()
/* 
    read information about current frame f -  

    nels[f] - the number of ellipsoids in it
              (0 is used as End-of-File marker) 
    frame[f] - the name of the current frame (f is its number) 
    then for each ellipsoid, its 3 axis lengths, coordinates 
         of its centre, and its angles of orientation. 
 
    called by loadfr 
*/
{
   int axx,axy,axz,cenx,ceny,cenz,ang1,ang2,ang3;
   int c[3];
   int j,k,m;
   char buf[BMAX];
   char str2[BMAX],str3[BMAX];

/* 
     read ellipsoids in current frame -  
*/
   if (debug <= 0) printf("getellsa %d %d\n",f,nels[f]);
   for (m = 0; m < nels[f]; ++ m)
   {
      if (debug <= 0)
         printf("getellsaa %d %d %d\n",m,infound,TRUE);
      if (infound == TRUE)
      {
         if (fgets(buf,BMAX,infile) == NULL)
         {
            sprintf(err,
               "unexpected end of file %s at frame %d ellipsoid %d",
               fname,f,m);
            getout(1);
         }
      }
      else
         gets(buf);
      sscanf(buf,"%d %d %d %d %d %d %d %d %d %d %d %d %s %s\n",
            &axx,&axy,&axz,&cenx,&ceny,&cenz,
            &ang1,&ang2,&ang3,&c[0],&c[1],&c[2],str2,str3);
      if (debug <= 0) printf(
         "getellsb %d %d %d %d %d %d %d %d %d %d %d %d %d %s %s\n",
            m,axx,axy,axz, cenx,ceny,cenz,
            ang1,ang2,ang3, c[0],c[1],c[2],str2,str3);
/* 
     scale everything back to size -  
*/
      ax[f][m][0] = 0.1*axx ;
      ax[f][m][1] = 0.1*axy ;
      ax[f][m][2] = 0.1*axz ;
      cen[f][m][0] = 0.1*cenx ;
      cen[f][m][1] = 0.1*ceny ;
      cen[f][m][2] = 0.1*cenz ;
      mkrotn(f,m,ang1,ang2,ang3);
      for (j = 0; j < ncols; ++j)
      {
          if ( (c[0] == col[j][0])
            && (c[1] == col[j][1])
            && (c[2] == col[j][2]))
               goto gotit;
      }
      j = ncols;
      col[j][0] = c[0];
      col[j][1] = c[1];
      col[j][2] = c[2];
      if (ncols < (CMAX-1)) ++ncols;
         else printf(
           "\nOOPS: more then %d colours at ellipsoid %d frame %d\n",
               CMAX,m,f);

gotit:   elcol[f][m] = j;

      if (debug < 0)
      {
         printf("getellsc %d %d %d %d %d\n",
            m,j,col[j][0],col[j][1],col[j][2]);
         printf("getellsd %f %f %f\n",
            ax[f][m][0],ax[f][m][1],ax[f][m][2]);
         printf("getellse %f %f %f\n",
            cen[f][m][0],cen[f][m][1],cen[f][m][2]);
         printf("getellsf %f %f %f %f\n",
            rotn[f][m][0][0],rotn[f][m][0][1],
            rotn[f][m][0][2],rotn[f][m][0][3]);
      }
   }
} /* getells */
/**********************************************/

mkrotn(f,m,ia1,ia2,ia3)
int f,m;
int ia1,ia2,ia3;
/*
   convert angles a1,a2,a3 into
   quaternion and then matrix entries
   for frame f and ellipsoid m

   called by getells
   calls rotget;
*/
{
      float s1,c1,s2,c2,s3,c3 ;
      float a1,a2,a3;
      float quat[5];

      a1 = ia1*radian;
      a2 = ia2*radian;
      a3 = ia3*radian;
      if (debug < 0) printf("mkrotn %f %f %f\n",a1,a2,a3);
      s1 = sin(a1) ;
      c1 = cos(a1) ;
      s2 = sin(a2) ;
      c2 = cos(a2) ;
      s3 = sin(a3) ;
      c3 = cos(a3) ;
      quat[0] = c1*c2 ;
      quat[1] = s1*c2 ;
      quat[2] = s2 ;
      quat[3] = s3 ;
      quat[4] = c3 ;
      rotget(f,m,quat);
}  /* mkrotn */
/**********************************************************/

rotget(f,m,quat)
int f,m;
float quat[4];
/*
   form a rotation matrix rotn
   from the quaternion entries
   for frame f and ellipsoid m

   called by  mkrotn.
*/
{
      float cp,sp,x,y,z,mm,xsp,ysp,zsp,xm,ym,zm,xym,xzm,yzm ;

      if (debug < 0)
         printf("rotgeta %f %f %f %f %f\n",
          quat[0],quat[1],quat[2],
          quat[3],quat[4]);
      x = quat[0] ;
      y = quat[1] ;
      z = quat[2] ;
      sp = quat[3] ;
      cp = quat[4] ;
      mm = 1.0-cp ;
      xm = x*mm ;
      ym = y*mm ;
      zm = z*mm ;
      xsp = x*sp ;
      ysp = y*sp ;
      zsp = z*sp ;
      xym = x*ym ;
      xzm = x*zm ;
      yzm = y*zm ;
      rotn[f][m][0][0] = x*xm+cp ;
      rotn[f][m][0][1] = xym-zsp ;
      rotn[f][m][0][2] = xzm+ysp ;
      rotn[f][m][1][0] = xym+zsp ;
      rotn[f][m][1][1] = y*ym+cp ;
      rotn[f][m][1][2] = yzm-xsp ;
      rotn[f][m][2][0] = xzm-ysp ;
      rotn[f][m][2][1] = yzm+xsp ;
      rotn[f][m][2][2] = z*zm+cp ;
      rotn[f][m][0][3] = 0.0;
      rotn[f][m][1][3] = 0.0;
      rotn[f][m][2][3] = 0.0;
      rotn[f][m][3][0] = 0.0;
      rotn[f][m][3][1] = 0.0;
      rotn[f][m][3][2] = 0.0;
      rotn[f][m][3][3] = 1.0;
}  /* rotget */
/**************************************/

mkr(r,angx,angy,angz)
float r[4][4];
int angx,angy,angz;
/*
   form rotation matrix for given angles about each axis

   called by image
*/
{
   float rx[4][4],ry[4][4],rz[4][4];
   float rxy[4][4];
   float cx,cy,cz,sx,sy,sz;
   int j,k;

   for (j = 0; j < 4; ++j)
   {
      for (k = 0; k < 4; ++k)
      {
         rx[j][k] = 0.0;
         ry[j][k] = 0.0;
         rz[j][k] = 0.0;
      }
     rx[j][j] = 1.0;
     ry[j][j] = 1.0;
     rz[j][j] = 1.0;
   }
   cx = cos((float)angx*radian);
   sx = sin((float)angx*radian);
   cy = cos((float)angy*radian);
   sy = sin((float)angy*radian);
   cz = cos((float)angz*radian);
   sz = sin((float)angz*radian);
   rx[1][1] = cx; rx[2][2] = cx;
   rx[1][2] = sx; rx[2][1] = -sx;
   ry[0][0] = cy; ry[2][2] = cy;
   ry[0][2] = sy; ry[2][0] = -sy;
   rz[0][0] = cz; rz[1][1] = cz;
   rz[0][1] = sz; rz[1][0] = -sz;
   matmul(rx,ry,rxy);
   matmul(rxy,rz,r);
} /* mkr */
/**********************************/

matmul(a,b,c)
float a[4][4],b[4][4],c[4][4];
/*

   multiply matrix a onto matrix b
   putting answer in c

   called by mkr
*/
{
   int p,q,r;
   float rr;

   for (p = 0; p < 4; ++p)
   {
      for (q = 0; q < 4; ++q)
      {
         rr = 0.0;
         for (r = 0; r< 4; ++r)
            rr += a[r][p]*b[r][q];
         c[p][q] = rr;
      }
   }
} /* matmul */
/**************************************/

checkeys()
/*
   see if there has been any keyboard input lately

   called by loadfr, image.
   calls     reset.
*/
{
   int count;

   count = 0;
   if (debug <= 0) printf("checkeysa %d\n",f);
   while (qtest() != 0)
   {
      ++ count;
      dev = qread(&value);
      if (debug <= 0)
         printf("checkeysb %d %d %d %d %c\n",
            f,count,dev,KEYBD,value);
      if (dev == KEYBD)
      {
         if (debug <= 0)
            printf("checkeysc %d %d %d %d %c\n",
               f,count,dev,KEYBD,value);
         switch (value)
         {
         case 'a': freeze = FALSE;
              df = 1;
              break;
         case 'b': df = -1;
              break;
         case 'c': hold = FALSE;
              break;
         case 'd': ty -= 10;
              break;
         case 'f': df = 1;
              break;
         case 'g': sx *= 1.1;
              sy *= 1.1;
              sz *= 1.1;
              break;
         case 'h': system("more /rose/don/src.nudes/draweln.c\n");
              break;
         case 'i': freeze = TRUE;
              df = 0;
              break;
         case 'j': nsph *= 2;
              if (nsph > PMAX-1) 
              {
                 printf("oops max= %d\n",PMAX);
                 nsph = PMAX/2;
              }
              initsphere(1.0, 0.0,0.0,0.0);
              break;
         case 'k': nsph /= 2;
              if (nsph < 3) nsph = 3;
              initsphere(1.0, 0.0,0.0,0.0);
              break;
         case 'l': tx -= 10;
              break;
         case 'n': if (dofr == TRUE) dofr = FALSE;
              else dofr = TRUE;
              break;
         case 'p': if (hold == FALSE) hold = TRUE;
              break;
         case 'q': getout(0);
         case 'r': tx += 10;
              break;
         case 's': sx /= 1.1;
              sy /= 1.1;
              sz /= 1.1;
              break;
         case 't': tz += 10;
              break;
         case 'T': tz -= 10;
              break;
         case 'u': ty += 10;
              break;
         case 'v': fill = TRUE;
              initiris();
              break;
         case 'w': fill = FALSE;
              initiris();
              break;
         case 'x': angx += dang;
              break;
         case 'X': angx -= dang;
              break;
         case 'y': angy += dang;
              break;
         case 'Y': angy -= dang;
              break;
         case 'z': angz += dang;
              break;
         case 'Z': angz -= dang;
              break;
         case '0': reset();
              break;
         case '-': --speed;
              if (speed < 1) speed = 1;
              break;
         case '+': ++speed;
              break;
         }
         if (debug <= 0)
            printf("checkeysd %d %c %f %d %d %d %d %d %d %d\n",
               f,value,tz,freeze,dang,dofr,hold,df,speed,TRUE);
      }
   }
   if (debug <= 0)
      printf("checkeyse %d %c %d %d %d %d %d %d\n",
         f,value,freeze,dofr,hold,df,speed,TRUE);
} /* checkeys */
/***********************************/

rget(r,f,m)
int f,m;
float r[4][4];
/* 
   get rotation matrix of mth ellipsoid in fth frame

   called by image.
*/
{
   int i,j;

   if (debug < 0) printf("rget %d %d %f %f %f %f\n",
      f,m,rotn[f][m][0][0],rotn[f][m][0][1],
          rotn[f][m][0][2],rotn[f][m][0][3]);
   for (i = 0; i < 4; ++i)
      for (j = 0; j < 4; ++j)
         r[i][j] = rotn[f][m][i][j];
} /* rget */
/***********************************/

drawsphere(f,m)
int f,m;
/*
   draw a sphere

   called by image.
*/
{
   int i,j,k;
   float p[3];

   if (debug < 0) printf("drawspherea %d %d %d %d %d %d %d %d\n",
      f,m,ci,col[ci][0],col[ci][1],col[ci][2],fill,TRUE);

   if (fill == TRUE)
   {
      for (k = 0; k < 3; ++k)
      {
         material[k+1] = ((float)col[ci][k])/255.0;
         material[k+5] = ((float)col[ci][k])/255.0;
      }
      lmdef(DEFMATERIAL,indx,nm,material);
      lmbind(MATERIAL,indx);
   }
   else
   {
      mapcolor(ci, col[ci][0],col[ci][1],col[ci][2]);
      color(ci);
   }

   for (i = 0; i < nfaces; ++ i)
   {
      if (fill == TRUE)
      {
         bgnpolygon();
         n3f(norm[i]);
      }
        else bgnclosedline();
      for (j = 0; j < 4; ++j)
      {
         v3f(sph[i][j]);
      }
      if (fill == TRUE) endpolygon();
         else endclosedline();
   } 
}   /* drawsphere */
/**************************************/

image(f)
int f;
/*
   draw frame f, or a blank frame if f<=0.

   called by loadfr, display, 
   calls     checkeys, drawsphere, rget, getout.
*/
{
   int   tim;
   int j,m;
   float r[4][4];
   float vx,vy,vz;

   if (debug <= 0) printf(
      "imagea %d %d %d %d %d %d %d %d\n",
         f,ivx[f],ivy[f],ivz[f],angx,angy,angz,dofr);
   if (fill == TRUE) c3i(white);
     else color(WHITE);
   clear();
   if (fill == TRUE) zclear();
   if (f > 0)
   {
      vx = (float)ivx[f]*0.1;
      vy = (float)ivy[f]*0.1;
      vz = (float)ivz[f]*0.1;
      mkr(r,angx,angy,angz);
      pushmatrix();
      translate(vx,vy,vz);
      translate(tx,ty,tz);
      multmatrix(r);
      scale(sx,sy,sz);
      for (m = 0; m < nels[f]; ++m)
      {
         ci = elcol[f][m];
         if (debug < 0)
            printf("imagec %d %d %d %d %d %d %f %f %f %f %f %f\n",
               f,m,ci,col[ci][0],col[ci][1],col[ci][2],
               ax[f][m][0],ax[f][m][1],ax[f][m][2],
               cen[f][m][0],cen[f][m][1],cen[f][m][2]);
         pushmatrix();
         translate(cen[f][m][0]-vx,cen[f][m][1]-vy,cen[f][m][2]-vz);
         rget(r,f,m);
         multmatrix(r);
         scale(ax[f][m][0],ax[f][m][1],ax[f][m][2]);
         drawsphere(f,m);
         popmatrix();
      }
      translate(-vx,-vy,-vz);
      popmatrix();
   }
   if (dofr == TRUE)
   {
      if (fill == TRUE)
         c3i(red);
      else
      {
         mapcolor(RED, red[0],red[1],red[2]);
         color(RED);
      }
      sprintf(num,"%d",frame[f]);
      cmov(x+100.0,y+15.0,2.0);
      charstr(num);
      sprintf(num,"%d",speed);
      cmov(x+100.0,y+950.0,2.0);
      charstr(num);
   }
   swapbuffers();
   if (speed > 0) tim = 100/speed;
      else tim = -speed*100;

   if ((begin == FALSE) && (video == TRUE))
   {
      printf("vdrec %d\n",f);
      system("vdrec 1\n");
      sleep(1);
   }
   else if ( (hold == TRUE) && ((f == 0) || (f == (fstop-1))) )
      sleep(1);
   else sginap(tim);

   checkeys();
} /* image */
/**********************************/

display()
/*
   display sequence repeatedly.

   called by main.
   calls image.
*/
{
   int seq;
   int maxseq;
   int j;

   if (debug <= 1) printf("displaya %d %d\n",frstart,fstop);
   maxseq = MAXINT;
   if (video == TRUE)
   {
      image(0);
      maxseq = 1;
   }
   f = 1; df = 1;
   for (seq = 0; seq < maxseq; ++seq)
   {
      if (debug <= 1) printf("displayb %d\n",seq);

   show:
         image(f);
         f += df;
         if (freeze == TRUE) df = 0;
         if ((f >= 1) && (f < fstop)) goto show;

      if (f < 1) f = fstop-1;
      if (f >= fstop) f = 1;
   }
   if (video == TRUE) image(0);
} /* display */
/****************************************/

systry(str)
char *str;
/*
   echo and then execute a system command

   called by getpar.
*/
{
   if (debug <= 0) sprintf("%s",str);
   system(str);
} /* systry */
/**************************************/

getout(v)
int v;
/*
   exit gracefully

   called by image, loadfr, checkeys, main.
*/
{
   if (v != 0) printf("draweln problem: %s %d\n",err,v);
   exit(1);
} /* getout */
/********************************************/

reset()
/*
   reset interactive constants to default values

   called by checkeys.
*/
{
   df = 1;
   speed = RATE;
   nsph = 12;
   hold = FALSE;
   sx = 1.0; sy = 1.0; sz = 1.0;
   angx = 0; angy = 0; angz = 0;
   tx = 0.0; ty = 0.0; tz = 0.0;
} /* reset */
/************************************/
/*** dummies for Sun -
endpolygon(){}
c3i(){}
mmode(){}
color(){}
lookat(){}
zclear(){}
lmbind(){}
doublebuffer(){}
charstr(){}
popmatrix(){}
RGBmode(){}
translate(){}
viewport(){}
zbuffer(){}
lmdef(){}
mapcolor(){}
qdevice(){}
prefposition(){}
multmatrix(){}
cmov(){}
sginap(){}
bgnpolygon(){}
ortho(){}
pushmatrix(){}
scale(){}
gconfig(){}
winopen(){}
bgnclosedline(){}
swapbuffers(){}
n3f(){}
v3f(){}
clear(){}
endclosedline(){}
int qread(){return(1);}
int qtest(){return(0);}
int getgdesc(){return(1024);}
***********/
