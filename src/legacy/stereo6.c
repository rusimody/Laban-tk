/*           stereo6.c
         based on stereoj.c

  to create ppm files of autostereogram images of ellipsoids
            from an ellipsoid file,
        in C for X-Windows under Unix.

        21 Apr 1998 255 max colour index used
        25 Jun 1996 texture maps accommodated 
	16 Jun 1996 output file names fixed
	            with ppm images
                    scaling by range of image z values
                    with possible random background
                    possibly in colour
	12 Oct 1995 written by Don Herbison-Evans

  usage:

   stereo6 f [-a a] [-b] [-c] [-d d] [-g g] [-i i] [-m m] [-n n]
             [-o o] [-r r] [-u u] [-x x] [-y y] < e

  where:
   e = input file name (the name of a nudes.3 ellipsoid file)
   f = stem required for output file names

   a = ambient light in range 0 - 1 (default: 0.3)
   b   make background random (default: white background)
   c   make a coloured autostereogram (default: grey scale)
   d = debug value: 2 = none, 1 = some, etc. (default: 2)
   g = depth magnification factor (default: 1)
   i = eye separation in pixels (default: 160)
   m = ratio (maxz/screen) distances (default: 3)
   n = initial frame number (default: 0);
   o = pixel centre offset (default: 0)
   r = percentage of random colours/shades (frame correlated)
   t = y value for testing (default: -1)
   u = percentage of random colours/shades (frame uncorrelated)
   x = width of single eye image (default: 256)
   y = height of image (default: 256)

 input data: taken from standard input as a nudes.3 file :

         number of ellipsoids,  frame number, 6 viewing parameters 

   and then a set of lines, one for each ellipsoid, containing:

         3 semiaxis lengths, 3 coords of centre, 3 angles of
         orientation, 3 colour components, ellipsoid name, and
         texture map file name.
 
 subroutines:-
      main    - organise things
      setup   - set consteants
      opnin   - open input file and set screen size and scalings
      opnout  - initialise each output file in turn
      readells- read ellipsoid data for a frame
      setell  - set ellipsoid's containing box and coefficients 
      mkquat  - convert angles into quaternions
      rotget  - retrieve rotation matrix from quat array
      setmat  - find matrix representing an ellipsoid
      matmul  - multiply two matrices together
      setcof  - find ellipsoid coefficients from matrix form
      setpln  - find coefficients of outline plane
      shadel  - loop through x finding depths and colours
      illum   - find brightness at point on an ellipsoid
      zdepth  - find depth of ellipsoid surface at point x,y
      random  - get a random byte
      putline - print out scanline buffer
      separation - find separation of left and right eye points
      setrand - initialise random numbers
      autost  - make the autostereogram
      setcol  - set up a scanline
      setpnt  - set red,green,blue colour at point x,y on image
      setmaps - set up maps for textured ellipsoid
      domaps  - select map to use
      mtexture- make antialiassed maps
      nextmap - make a map
      texture - interpolate a map
      mapsdone- check if map done
*/
#include <stdio.h>

#define min(a,b)  ( (a)<(b)?(a):(b) )
#define max(a,b)  ( (a)>(b)?(a):(b) )
#define round(x) (int)((float)(x)+0.5)
#define  BMAX   256        /* max size of input buffer */
#define  CMAX   256        /* maximum number of shades */
#define  EMAX  1024        /* max number of ellipsoids in an image */  
#define  XMAX  1024        /* max width and height of image */
#define  TRUE     1
#define FALSE     0

double sin(),cos(),atan2(),sqrt(),acos(),asin();

double ambint;
double ax3[EMAX][3];
double ang[EMAX][3];
double cen[EMAX][3];
double color[EMAX][3];     /* colours of the ellipsoids */
double colr[XMAX];         /* red components of the image */
double colg[XMAX];         /* green components of the image */
double colb[XMAX];         /* blue components of the image */
double coef34[EMAX],coef256[EMAX];
double coef[EMAX][6];
double cpc;
double deg10;
double den[EMAX];
double ell[EMAX][3][3];
double ell2y[EMAX][3];
double doub0;
double doub1;
double doub2;
double doub128;
double doub255;
double eyesep;
double fac;
double far;
double inv2;
double inv3;
double inv10;
double inv255;
double invmu;
double magn;
double maxax[EMAX];
double mu;
double pi;
double plan23[EMAX];
double near;
double plane[EMAX][3];
double rell[EMAX][3][3];
double rpc;               /* fraction of randomness in image */
double twopi;
double xfac,yfac;
double xmax3[EMAX];
double xmin3[EMAX];
double ymax3[EMAX];
double ymin3[EMAX];
double z[XMAX][XMAX];     /* z buffer of scene */
double zbg;               /* distance of background */
double zmax3[EMAX];       /* furthest point on each ellipsoid */
double zmin3[EMAX];       /* nearest point on each ellipsoid */
double zmaxn;             /* furthest point of objects in scene */
double zminn;             /* nearest point of objects in scene */
double zmaxp;             /* furthest point of scene */
double zminp;             /* nearest point of scene */

int    bw;                 /* true if only black and white */
int    cmax;               /* white value */
int    count;              /* ppm image counter of values per line */
double csame[XMAX];        /* counters showing use of various separations */
int    debug;              /* debug value: 0 = some, 1 = none */
int    f;                  /* input frame counter */
int    frame;              /* frame number as read from input file */
int    h;                  /* scan across line of image */
int    inear,ifar;         /* stereo separations of near and far planes */
int    isep;               /* separation of eyes in pixels */
int    line[3][XMAX];      /* scanline buffer */
int    m[XMAX][XMAX];      /* which ellipsoid colours each point */
int    mapdone[EMAX];      /* 1 if map done already */
int    mapsizes[EMAX][10]; /* sizes of maps */
int    maxf;               /* highest frame number accommodated */
int    maxx,maxy;          /* dimensions of stereo image */
int    ncols = 2;          /* number of colours counted so far */
int    nels;               /* number of ellipsoids in current frame */
int    nfr = 0;            /* output image number */
int    offset;
int    rbg;                /* true if random background required */
int    same[XMAX];         /* list of identical pixels */
int    spot;               /* size of focussing spot */
int    width;              /* width of original image */
int    xmin1,xmax1;
int    xmin2,xmax2;
int    xspot;              /* width of focussing spot */
int    xoffset[EMAX];
int    yoffset[EMAX];
int    yspot;              /* height of focussing spot */
int    ytest;              /* debug test scanline */
int    ymax;               /* y position of focussing spots */

char   basename[BMAX];
char   black;
char   buf[BMAX];
char   cmnd[BMAX];
char   fname[BMAX];
char   foname[BMAX];
char   infile[BMAX];
char   mnames[EMAX][BMAX]; /* names of texture files */
char   shade;
char   src[BMAX];          /* source directory */
char   white;

char   *maps[EMAX][10];
unsigned char map[XMAX*XMAX*3]; /* a map */

FILE   *FONAME;

/******************************************************/

main(argc,argv)
char *argv[];
int argc;
/*
   calls  setup, opnin, opnout, readells, setell, depel, shadel,
	  autost, setrand, atan2, sscanf, fprintf, gets.
*/
{
   int    a1,a2,a3;
   int    vx,vy,vz;
   int    y;
   int    x;

   debug = 2;
   setup();
   opnin(argc,argv);
/*
   run through frames of film-
*/
   for (f = 1; f <= maxf ; f++)
   {
      if( NULL == gets(buf) )
      {
         fprintf(stderr,
          "\nERROR stereo6: unexpected EOF frame %d from file\n",f);
         exit(1);
      }
      sscanf(buf,"%d %d %d %d %d %d %d %d",
             &nels,&frame,&vx,&vy,&vz,&a1,&a2,&a3);
      if (debug <= 1)
	 printf("maina %6d %6d\n", nels,frame);
      if (nels <= 0) goto end;
      if (shade == 'u') setrand(frame);
	 else setrand(1);
      opnout(argv);
      readells();
      setell();
      zbg = zmaxn;
      depel();
      fac = (far-near)/(zmaxp-zminp);
      if (debug <= 1)
	 printf("mainb %g %g %g %g %g %g %g\n",
	    mu,eyesep,zminn,zmaxn,zminp,zmaxp,fac);
      for (y = (maxy-1); y >= 0; --y)
      {
         shadel(y);
         autost(y);
      }
      if (debug <= 0)
      {
         for (x = 0; x < maxx; ++x)
            if (csame[x] != 0)
	       printf("mainc %d %g\n",x,csame[x]);
      }
      fclose(FONAME);
      ++nfr;
   }
end:
     exit(0);
} /* main */
/**************************************/

setup()
/*
   set up constants

   called by main.
*/
{
   double doub3;
   int     j;

   doub0 = (double)0;
   doub1 = (double)1;
   doub2 = (double)2;
   doub3 = (double)3;
   doub128 = (double)128;
   doub255 = (double)255;
   inv2 = doub1/doub2;
   inv3 = doub1/(double)3;
   inv10 = doub1/(double)10;
   inv255 = doub1/doub255;
   pi = (double)4*atan2((double)1,(double)1);
   twopi = pi+pi;
   deg10 = pi/(double)1800;
   maxf = 16384*16384;
   bw = TRUE;
   rbg = FALSE;
   spot = 10;
   shade = 'a';
   ytest = -1;
   ambint = doub3*inv10;
   invmu = doub3;
   black = '0';
   white = 'z';
   cmax = CMAX-1;
   isep = 160;
   magn = doub1;
   maxx = 256;
   maxy = 256;
   for (j = 0; j < XMAX; ++j)
         csame[j] = doub0;
   sprintf(src,"/usr/users/staff/herbisod/src.nudes");
   if (debug <= 0) printf("setupa %d\n",maxf);
} /* setup */
/*******************************************/

opnin(argc,argv)
char *argv[];
int argc;
/*

   read flags, open input file, and set screen size and scalings

   called by main.
   calls     separation,
	     system, sscanf, exit, strcpy, sprintf,
	     fprintf, printf.
*/
{
   double separation();
   int j;
   int imagn;
   int irpc;

   irpc = 0;
   if (argc < 2)
   {
       sprintf(cmnd,"more %s/stereo6.c\n",src);
       system(cmnd);
       exit(0);
   }
   for (j = 1; j < argc; ++j)
   {
       strcpy(buf,argv[j]);
       if (debug <= -1)
	  printf("opnina %d %c %c\n",j,buf[0],buf[1]);
       if (buf[0] == '-')
       {
          if (buf[1] == 'a')
          {
             ++j;
             sscanf(argv[j], "%lg", &ambint);
          }
	  else
          if (buf[1] == 'b')
          {
             rbg = TRUE;
          }
	  else
          if (buf[1] == 'c')
          {
             bw = FALSE;
          }
          else
          if (buf[1] == 'd')
          {
             ++j;
             sscanf(argv[j], "%d", &debug);
          }
          else
          if (buf[1] == 'g')
          {
             ++j;
	     printf("opninb %g\n",magn);
             sscanf(argv[j], "%d", &imagn);
	     magn = (double)imagn/(double)100;
	     printf("opninc %g\n",magn);
          }
	  else
          if (buf[1] == 'i')
          {
             ++j;
             sscanf(argv[j], "%d", &isep);
             if (isep < 1)
             {
                fprintf(stderr,
                  "\nERROR stereo6: funny eye separation : %d\n",
                  isep);
                exit(1);
             }
          }
	  else
          if (buf[1] == 'm')
          {
             ++j;
             sscanf(argv[j], "%lg", &invmu);
             if (invmu < doub0)
             {
                fprintf(stderr,
                  "\nERROR stereo6: funny screen separation : %g\n",
                  invmu);
                exit(1);
             }
          }
	  else
          if (buf[1] == 'n')
          {
             ++j;
             sscanf(argv[j], "%d", &nfr);
          }
	  else
          if (buf[1] == 'o')
          {
             ++j;
             sscanf(argv[j], "%d", &offset);
          }
          else
          if (buf[1] == 'r')
          {
             shade = 'r';
             ++j;
             sscanf(argv[j], "%d", &irpc);
          }
	  else
          if (buf[1] == 't')
          {
             ++j;
             sscanf(argv[j], "%d", &ytest);
          }
	  else
          if (buf[1] == 'u')
          {
             shade = 'u';
             ++j;
             sscanf(argv[j], "%d", &irpc);
          }
	  else
	  if (buf[1] == 'x')
          {
	      ++j;
	      sscanf(argv[j], "%d", &maxx);
              if (maxx < 0 ) maxx = -maxx;
          }
          else
          if (buf[1] == 'y')
          {
	      ++j;
	      sscanf(argv[j], "%d", &maxy);
              if (maxy < 0 ) maxy = -maxy;
	      if ((maxy >= XMAX) || (maxy < 1))
              {
                 fprintf(stderr,
                    "\nERROR stereo6: requested image height is %d\n",
                     maxy);
	         fprintf(stderr, "max accommodated is %d\n", XMAX);
	           exit(1);
	      }
          }
          else
          {
	      fprintf(stderr,
                 "\nERROR stereo6: unrecognised flag %s\n", buf);
	      exit (1);
          }
       }
       else
         sprintf(fname,"%s",argv[j]);
   }
   maxx += isep;
   if (maxx >= XMAX)
   {
      fprintf(stderr,
             "\nERROR stereo6: requested image width is %d\n",
                   maxx);
      fprintf(stderr, "max accommodated is %d\n", XMAX-isep);
      exit(1);
   }
   xfac = (double)1000/(double)(maxx-isep);
   yfac = (double)1000/(double)maxy;
   mu = doub1/invmu;
   eyesep = (double)isep;
   far = separation(doub0);
   near = separation(doub1);
   ifar = magn*far+(doub1-magn)*eyesep;
   inear = magn*near;
   rpc = (double)irpc/(double)100;
   cpc = doub1 - rpc;
   xspot = spot;
   yspot = spot;
   xmin1 = (maxx - isep/2 - xspot)/2;
   xmax1 = (maxx - isep/2 + xspot)/2;
   xmin2 = (maxx + isep/2 - xspot)/2;
   xmax2 = (maxx + isep/2 + xspot)/2;
   ymax = maxy - yspot;
   if (debug <= 1)
      printf("opnind %d %d %d %g %g %g %g %g\n",
	 isep,inear,ifar,magn,invmu,ambint,rpc,cpc);
} /* opnin */
/***********************************/

opnout()
/*
    create new file and send header for frame.
 
    called by main.
*/
{
   sprintf(foname,"%s.0000.ppm",fname);
   if ((debug <= 1) && (bw == TRUE))
      printf("opnouta %s, bw = true\n",foname);
   if ((debug <= 1) && (bw == FALSE))
      printf("opnouta %s, bw = false\n",foname);
   if( NULL == (FONAME=fopen(foname,"w+")) )
   {
       fprintf(stderr,
          "\nERROR stereo6: can't open/create %s for writing\n",
          foname);
       exit(1);
   }
   fprintf(FONAME,"P3\n");
   fprintf(FONAME," %d\n",maxx);
   fprintf(FONAME," %d\n",maxy);
   fprintf(FONAME," %d\n",CMAX-1);
   count = 0;
} /* opnout */
/*************************************************/

readells()
/*
   run through ellipsoids of frame, reading and setting them up 

   called by main.
*/

{
   int    k,n;
   int    axn[3],angn[3];
   int    cenn[3];
   int    cn[3];
   char   enames[BMAX];

   if (debug <= 1) printf("readellsa %d\n",nels);
   for (n = 0; n < nels ; n++)
   {
      if( NULL == gets(buf) )
      {
         fprintf(stderr,
           "\nERROR stereo6: EOF frame %d ellipsoid %d\n",
             frame,n);
         exit(1);
      }
      sscanf(buf,"%d %d %d %d %d %d %d %d %d %d %d %d %s %s\n",
          &axn[0],&axn[1],&axn[2],
          &cenn[0],&cenn[1],&cenn[2],
          &angn[0],&angn[1],&angn[2],
          &cn[0],&cn[1],&cn[2],
          enames,mnames[n]);
      if (debug <= 0)
      {
         printf(
            "readellsb %d %s %d %d %d %d %d %d %d %d %d %d %d %d\n",
            n,enames,axn[0],axn[1],axn[2],
            cenn[0],cenn[1],cenn[2],
            angn[0],angn[1],angn[2],
            cn[0],cn[1],cn[2]);
      }
      for (k = 0; k < 3; ++k)
      {
         ax3[n][k] = inv10*axn[k];
         cen[n][k] = inv10*cenn[k];
         ang[n][k] = deg10*angn[k];
	 color[n][k] = (double)cn[k];
      }
      if (cn[0] < 0) setmaps(n);
   }
} /* readells */
/***************************************************/

setell()
/*
    for each ellipsoid-
	set up containing box (xmin3,xmax3,ymin3,ymax3,zmin3,zmax3)
	set up coefficients of
	   matrix representation
	   polynomial representation
	   plane of outline
 
    calls  rotget, setmat, setcof, setpln
    called by main
*/
{
   int j,k,n;
   double extent[3],r[3][3],quat[5],unr[3][3];

   for (n = 0; n < nels; n++)
   {
        if (debug <= -1) printf("setella %d %g %g %g %g %g %g\n",
   	   n,ax3[n][0],ax3[n][1],ax3[n][2],
             ang[n][0],ang[n][1],ang[n][3]);
       mkquat(quat,ang[n][0],ang[n][1],ang[n][2]);
       rotget(quat,r,unr);

       for (k = 0; k < 3; k++)
       {
          extent[k]=doub0;
       	  for (j = 0; j < 3; j++)
          {
             extent[k]=extent[k]+(ax3[n][j]*r[k][j])
   				    *(ax3[n][j]*r[k][j]);
          }
       	  extent[k]=sqrt(extent[k]);
       }
       maxax[n] = ax3[n][0];
       if (maxax[n] < ax3[n][1]) maxax[n] = ax3[n][1];
       if (maxax[n] < ax3[n][2]) maxax[n] = ax3[n][2];
       xmin3[n]=cen[n][0]-extent[0];
       xmax3[n]=cen[n][0]+extent[0];
       ymin3[n]=cen[n][1]-extent[1];
       ymax3[n]=cen[n][1]+extent[1];
       zmin3[n]=cen[n][2]-extent[2];
       zmax3[n]=cen[n][2]+extent[2];
       if (debug <= -1) printf("setellb %d %g %g %g %g %g\n",
   	   n,xmin3[n],xmax3[n],ymin3[n],ymax3[n],zmin3[n]);
       setmat(r,n,ell,ax3,den);
       setcof(n);
       setpln(n);
   }
   zminn = zmin3[0];
   zmaxn = zmax3[0];
   for (n = 1; n < nels; n++)
   {
       if (zmax3[n] > zmaxn) zmaxn = zmax3[n];
       if (zmin3[n] < zminn) zminn = zmin3[n];
   }
   if (debug <= 1) printf("setellc %g %g\n",zminn,zmaxn);
} /* setell */
/******************************************/

mkquat(quat,a1,a2,a3)
double quat[5],a1,a2,a3;
/*
 
    convert angles a1,a2,a3 into quat entries
 
    called by input
 
*/
{
   double s1,c1,s2,c2,s3,c3;

      if (debug <= -1)
	 printf("mkquata %12.4g %12.4g %12.4g\n",a1,a2,a3);
      s1=sin(a1);
      c1=cos(a1);
      s2=sin(a2);
      c2=cos(a2);
      s3=sin(a3);
      c3=cos(a3);
      quat[0]=c1*c2;
      quat[1]=s1*c2;
      quat[2]=s2;
      quat[3]=s3;
      quat[4]=c3;
} /* mkquat */
/**********************************************/

rotget(quat,r,unr)
double   quat[5],r[3][3],unr[3][3];
/*
    form a rotation matrix r and its inverse unr
    from the entries in quat

    called by  setell
*/
{
   int i,j;
   double m;
   double cp,sp;
   double x,y,z;
   double xsp,ysp,zsp;
   double xm,ym,zm,xym,xzm,yzm;

      if (debug <= -1) 
	printf("rotgeta %f %f %f %f %f\n",
		 quat[0],quat[1],quat[2],quat[3],quat[4]);
      x = quat[0];
      y = quat[1];
      z = quat[2];
      sp = quat[3];
      cp = quat[4];
      m = doub1-cp;
      xm = x*m;
      ym = y*m;
      zm = z*m;
      xsp = x*sp;
      ysp = y*sp;
      zsp = z*sp;
      xym = x*ym;
      xzm = x*zm;
      yzm = y*zm;
      r[0][0] = x*xm+cp;
      r[0][1] = xym+zsp;
      r[0][2] = xzm-ysp;
      r[1][0] = xym-zsp;
      r[1][1] = y*ym+cp;
      r[1][2] = yzm+xsp;
      r[2][0] = xzm+ysp;
      r[2][1] = yzm-xsp;
      r[2][2] = z*zm+cp;
 
      for ( i = 0; i < 3; i++)
	 for (j = 0; j < 3; j++)
             unr[i][j] = r[j][i];
 
      if (debug <= -1)
      {
	 printf("rotgetb \n");
	 for (i = 0; i < 3; i++)
         {
	     printf("          ");
	     printf("%f %f %f\n",r[i][0],r[i][1],r[i][2]);
          }
       }
} /* rotget */
/**********************************************/
 
setmat(r,n,ell,ax3,den)
int   n;
double ell[EMAX][3][3],ax3[EMAX][3],r[3][3],den[EMAX];
/*
    this finds the matrix "ell" of the quadratic form of the "n"th
    ellipsoid by taking the diagonal matrix of inverse square semiaxes,
    and doing on it a similarity transform for its own rotation.
 
    called by setell
    calls matmul
*/
{
   int j,k;
   double el[3][3],rr[3][3],rel[3][3];

      if (debug <= -1)
	 printf("setmata %d %f %f %f %f\n",
            n,r[0][0],ax3[n][0],ax3[n][1],ax3[n][2]);
/*
    initialise diagonal matrix-
 
*/
      for (j = 0; j < 3; j++)
      {
	 for (k = 0; k < 3; k++)
         {
            rel[j][k] = doub0;
            el[j][k] = doub0;
         }
         if ( (ax3[n][j]*ax3[n][j]) ==  doub0 )  
         {
	    fprintf(stderr,
               "\nERROR stereo6 subr setmat ax3[%d][%d]=0\n\n",n,j);
            exit(1);
         }
	 rel[j][j] = doub1/ax3[n][j] ;
	 el[j][j] = doub1/( ax3[n][j]*ax3[n][j] );
      }
/*
    form inverse of r-
*/
      for (j = 0; j < 3; j++)
         for (k = 0; k < 3; k++)
            rr[j][k] = r[k][j];
/*
    do similarity transform-
*/
      matmul(el,rr,el);
      matmul(r,el,el);
      matmul(rel,rr,rel);
      for (j = 0; j < 3; j++)
      {
         for (k = 0; k < 3; k++)
         {
            ell[n][j][k] = el[j][k];
            rell[n][j][k] = rel[j][k];
         }
         if (debug <= -1)
            printf("setmatb %d %f %f %f %f %f %f\n",
               n,rr[j][0],rr[j][1],rr[j][2],rel[j][0],rel[j][1],rel[j][2]);
      }
      if (ell[n][2][2] != doub0)
      	 den[n]=doub1/ell[n][2][2];
      else
         fprintf(stderr,
            "\nERROR stereo6 subr setmat, ell[%d][2][2]=0\n\n",n);
} /* setmat */
/******************************************************/

matmul(a,b,c)
double a[3][3], b[3][3], c[3][3];
/*
    multiply matrix a by matrix b to give matrix c,
    allowing for the possibility that any 2 or all 3
    of the arrays a,b,c may be the same.
 
    called by setmat.
*/
{
   register int i,j,k;
   double x,ans[3][3];

   for (i = 0; i < 3; i++)
   {
      for (j = 0; j < 3; j++)
      {
         x = doub0;
         for (k = 0; k < 3; k++)
           x += ( a[i][k]*b[k][j] );
         ans[i][j] = x;
      }
   }

   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
         c[i][j] = ans[i][j];
} /* matmul */
/************************************************/

setcof(n)
int n;
/*
    set up coefficients of polynomial form of n'th ellipsoid
    relative to origin.
 
    called by setell
*/
{
      coef[n][0] = ell[n][0][0]-ell[n][0][2]*ell[n][0][2]*den[n];
      coef[n][1] = ell[n][1][1]-ell[n][1][2]*ell[n][1][2]*den[n];
      coef[n][2] = doub2*(ell[n][0][1]-ell[n][0][2]*ell[n][1][2]*den[n]);
      coef[n][3] = (-doub2)*coef[n][0]*cen[n][0]-coef[n][2]*cen[n][1];
      coef[n][4] = (-doub2)*coef[n][1]*cen[n][1]-coef[n][2]*cen[n][0];
      coef[n][5] = coef[n][0]*cen[n][0]*cen[n][0]
		   +coef[n][1]*cen[n][1]*cen[n][1]
		   +coef[n][2]*cen[n][0]*cen[n][1] - doub1;
      if (debug <= -1) printf("setcofa %d %f %f %f %f %f %f\n",
          n,coef[n][0],coef[n][1],coef[n][2],coef[n][3],coef[n][4],coef[n][5]);
} /* setcof */
/******************************************************/

setpln(n)
int n;
/*
    set coefficients of plane of outline of nth ellipsoid
 
    called by setell
*/
{
      plane[n][0]=ell[n][0][2]*den[n];
      plane[n][1]=ell[n][1][2]*den[n];
      plane[n][2]= (-cen[n][2])-plane[n][0]*cen[n][0]-plane[n][1]*cen[n][1];
      if (debug <= -1)
	 printf("setplna %d %f %f %f\n",
		   n,plane[n][0],plane[n][1],plane[n][2]);
} /* setpln */
/******************************************************/

depel()
/*
    find depths at each pixel
 
    called by main.
    calls     zdepth.
*/
{
   double zdepth();

   double zxymin;
   double xx,yy;
   double zxy;
   int    j,step;
   int    active[EMAX],nactiv;
   int    x,y;
   int    mxy;
   int    n;

   zmaxp = zminn;
   zminp = zmaxn;
   for (y = 0; y < maxy; ++y)
   {
      step = 1;
      yy = yfac*(double)y;
      nactiv = 0;
      active[0] = 0;
/*
   do as much calculation as possible for this y scanline-
*/ 
      for (n = 0; n < nels; n++)
      {
         if ( (yy < ymax3[n]) && (yy > ymin3[n]) )
         {
            active[nactiv] = n;
            plan23[n] = plane[n][2]+plane[n][1]*yy;
            coef34[n] = coef[n][2]*yy+coef[n][3];
            coef256[n] = yy*(coef[n][1]*yy+coef[n][4])+coef[n][5];
            ++nactiv;
         } /* if yy */
      } /* n */
      if (debug <= 0)
	 printf("depela %d %d %d %g %g %g %g %g\n",
	    y,nactiv,active[0],yy,
	    ymin3[active[0]],ymax3[active[0]],
	    xmin3[active[0]],xmax3[active[0]]);
/*
   scan in x across scanline-
*/
      for (x = 0; x < maxx; x+=step)
      {
	 mxy = -1;
         zxymin = zbg;
         if (nactiv > 0) 
         {
            xx = xfac*(double)x;
            n = -1;
/* 
         check ellipsoids that colour this point-
*/ 
            for (j = 0; j < nactiv; j++)
            {
               n = active[j];
               if ( (xx < xmax3[n]) && (xx > xmin3[n]) && (zmin3[n] < zxymin) )
               {
                   zxy = zdepth(n,xx,yy);
                   if (zxy < zxymin) 
                   {
                      zxymin = zxy;
		      mxy = n;
                   } /* if zxy */
               } /* if xx */
            } /* j */
            if (debug <= 0)
	       printf("depelc %d %d %d %g\n",x,y,n,zxymin);
         } /* if nactive */
         z[x][y] = zxymin;
	 m[x][y] = mxy;
	 if ((zxymin > zmaxp) && (zxymin != zbg)) zmaxp = zxymin;
	 if (zxymin < zminp) zminp = zxymin;
      } /* x */
   } /* y */
   if (zminp < doub0) zminp = doub0;
} /* depel */
/********************************************************/

shadel(y)
int y;
/*
    loop through x finding colours
 
    called by main.
    calls     illum, random, texture.
*/
{
   int random();
   double illum();

   double cr,cg,cb;
   double light;
   double xx,yy;
   int    j;
   int    n;
   int    step;
   int    x;

   if (debug <= 0)
      printf("shadela %g %g %c %d %d\n",rpc,cpc,shade,n,h);
   step = 1;
   yy = yfac*(double)y;
   for (n = 0; n < nels; n++)
      for (j = 0; j < 3; j++)
         ell2y[n][j] = ell[n][1][j]*(yy-cen[n][1]);
/*
   scan in x across scanline-
*/
   for (x = 0; x < maxx; x+=step)
   {
      n = m[x][y];
      if (n >= 0)
      {
	 xx = xfac*(double)x;
	 cr = color[n][0];
	 cg = color[n][1];
	 cb = color[n][2];
         light =  illum(n,y,xx-cen[n][0],yy-cen[n][1],z[x][y]-cen[n][2],ell2y);
	 if (cr < doub0)
	    texture(xx-cen[n][0],yy-cen[n][1],z[x][y]-cen[n][2],n,
	       &cr,&cg,&cb);
         colr[x] = cpc*cr*light + rpc*(double)random();
         colg[x] = cpc*cg*light + rpc*(double)random();
         colb[x] = cpc*cb*light + rpc*(double)random();
      }
      else
      {
         if (rbg == FALSE)
         {
            colr[x] = cmax;
            colg[x] = cmax;
            colb[x] = cmax;
         }
         else
         {
            colr[x] = random();
            colg[x] = random();
            colb[x] = random();
         }
      }
      if (h == ytest)
	    printf("shadelb %3d %3d %7.3g %7.3g %7.3g\n",
	       x,n,colr[x],colg[x],colb[x]);
   } /* x */
} /* shadel */
/***********************************************/
 
double illum(n,iy,x,y,z,ell2y)
int   n,iy;
double ell2y[EMAX][3];
double x,y,z;
/*
   find relative brightness of point (x,y,z) on surface
   of nth ellipsoid.
 
   called by  shadel.
*/
{ 
   int j;
   double light;
   double grad[3],tgrad;
   double f0,f1,f2,f3;
 
   light= doub0;
   tgrad=doub0;
   for (j = 0; j < 3; j++)
   {
       grad[j] = ell[n][0][j]*x+ell2y[n][j]+ell[n][2][j]*z;
       tgrad += (grad[j]>0? grad[j]:(-grad[j]));
   } 
   if (tgrad > doub0)
   {
      f0 =grad[1]/tgrad;
      f1 = doub2*f0/(doub1+f0*f0);
      f2 = doub2*f1/(doub1+f1*f1);
      f3 = (doub1+f2)*inv2;
      light = ambint+(doub1-ambint)*f3;
   }
   if (light < doub0) light = doub0;
   if (light > doub1) light = doub1;
   if (iy == ytest) printf(
      "illuma %3d %7.2g %7.2g %7.2g %7.2g %7.2g %7.2g %7.2g %7.2g\n",
         n,f0,f2,x,light,grad[0],grad[1],grad[2],tgrad);
   return(light);
} /* illum */
/***********************************************/

double zdepth(n,x,y)
int   n;
double x,y;
/*
    find the depth z of the nearer surface of the n'th ellipsoid
    at point x,y

   called by depel.
*/
{
   double z;
   double discrt;
 
   z = zbg;
   discrt = (-((coef[n][0]*x+coef34[n])*x+coef256[n])*den[n]);
   if (discrt > doub0)
	   z = (-plan23[n]-plane[n][0]*x-sqrt(discrt));
   if (debug <= -1) printf(
              "zdepth %d %g %g %g %g %g %g %g %g\n",
              n,x,y,coef[n][0],coef34[n],coef256[n],den[n],discrt,z);
   return(z);
} /* zdepth */
/************************************************/
 
int random()
/*
    return a random integer in the range 0 to 255.
 note : that a=123465,b=54321,c0=34567 gives a regular grid

 called by shadel, setrand.
*/
{
   int ans;
   static unsigned int a=1234589,b=3432,c=4567;

   c = (b*c)%a;
   ans = 256*c/a;
   if (debug <= -1)
         fprintf(stderr,"random %d %d %d %d\n",a,b,c,ans);
   return(ans);
} /* random */
/****************************************************/

putline()
/*
   print out scanline buffer

   called by autost.
*/
{
   int x;

   if (debug <= 1) printf("putlinea %s\n",foname);
   for (x = 0; x < maxx; ++x)
   {
      fprintf(FONAME,"%3d %3d %3d ",line[0][x],line[1][x],line[2][x]);
      count += 12;
      if (count > 57)
      {
         count = 0;
         fprintf(FONAME,"\n");
      }
   }
} /* putline */
/******************************************/

double separation(z)
double z;
/*
    find separation of corresponding points
    in autostereogram

    called by opnin.
*/
{
   double s;

   s = round((doub1 - mu*z)*eyesep/(doub2 - mu*z));
   return(s);
} /* separation */
/**************************************************/

setrand(n)
int n;
/*
    initialise random() for 'n' frames

    called by main.
*/
{
   int random();
   int j,k,r;

   for (j = 0; j < n; ++j)
      k = random();
   for (j = 0; j < k; ++j)
      r = random();
}  /* setrand */
/*********************************************/

autost(y)
int y;
/*
    compose the stereogram image

    see:  Thimbleby, H.W., Inglis, S., and Witten, I.H.:
	 "Displaying 3D Images: Algorithms for Single-Image
	  Random-Dot Stereograms"
	  Computer, October 1994, pp 38-48.

    called by main.
    calls     setcol, setpnt.
*/
{
   int dx;
   int k;
   int s;
   int left,right;
   int t;
   int x;
   double zt;
   double cr,cg,cb;

   for (x = 0; x < maxx; ++x)
   {
      if (debug <= 0)
	    printf("autosta %d %d %d %g %g %g %g\n",
	       y,x,m[x][y],z[x][y],colr[x],colg[x],colb[x]);
      /* if ((x+ifar) < maxx) same[x] = x+ifar; else same[x] = x; */
      same[x] = x + ifar;
   }
   for (x = 0; x < maxx; ++x)
   {
      if (m[x][y] >= 0)
      {
         s = near + fac*(z[x][y] - zminp);
         left = x;
         right = left + s;
         if (( 0 <= left) && (right < maxx))
         {
            same[left] = right;
            csame[s] += doub1;
         }
      }
   }
   setcol(y);
   putline();
} /* autost */
/***********************************************/

setcol(y)
int y;
/*
   set the colours along a scanline

   called by autost.
   calls setpnt.
*/
{
   int ell[XMAX];
   int sx;
   int mx;
   int x;
   double maxaxxy;
   double cr,cg,cb;
   double zmin;

   for (x = 0; x < maxx; x++)
   {
      ell[x] = -1;
   }
   for (x = 0; x < maxx; x++)
   {
      cr = colr[x];
      cg = colg[x];
      cb = colb[x];
      if (ell[x] < 0)
      {
	 zmin = doub2*zmaxn;
	 for (sx = x;
	    (same[sx] != sx) && (sx >= 0) && (sx < maxx); sx = same[sx])
	 {
	    if (z[sx][y] < zmin)
	    {
               cr = colr[sx];
               cg = colg[sx];
               cb = colb[sx];
	       zmin = z[sx][y];
               mx = m[sx][y];
	    }
            if (debug <= 0)
	       printf("setcola %d %d %d %d %g %g %d %d %g %g %g %g %g %g\n",
	          x,y,sx,same[sx],z[sx][y],zmin,m[sx][y],mx,
		  colr[sx],colg[sx],colb[sx],
		  cr,cg,cb);
	 } /* sx */
	 for (sx = x;
	    (same[sx] != sx) && (sx >= 0) && (sx < maxx); sx = same[sx])
	 {
	    if (ell[sx] == -1)
	    {
	       colr[sx] = cr;
	       colg[sx] = cg;
	       colb[sx] = cb;
	       ell[sx] = mx;
	    }
	 } /* sx */
	 if ((same[sx] >= 0) && (same[sx] < maxx))
	    sx = same[sx];
	 if (ell[sx] == -1)
	 {
	    colr[sx] = cr;
	    colg[sx] = cg;
	    colb[sx] = cb;
	    ell[sx] = mx;
	 }
         if (debug <= 0)
           printf("setcold %d %d %d %d %g %g %g\n",
              x,y,sx,ell[sx],colr[sx],colg[sx],colb[sx]);
      } /* if ell[x] */
      if (debug <= 0)
        printf("setcole %d %d %d %g %g %g\n",
           x,y,ell[x],colr[x],colg[x],colb[x]);
   } /* x */
   for (x = 0; x < maxx; ++x)
   {
         if ((y > ymax) && (x > xmin1) && (x < xmax1))
            setpnt(x,doub0,doub0,doub0);
         else
         if ((y > ymax) && (x > xmin2) && (x < xmax2))
            setpnt(x,doub0,doub0,doub0);
         else
	 if (y == ytest)
            setpnt(x,doub0,doub0,doub0);
         else
            setpnt(x,colr[x],colg[x],colb[x]);
   } /* x */
} /* setcol */
/************************************************/
 
setpnt(x,cr,cg,cb)
int    x;
double cr,cg,cb;
/*
   set the point at 'x' to colour (cr,cg,cb).

   called by autost.
*/
{
   double gray;

   if (debug <= -1) printf("setpnta %d %g %g %g\n",x,cr,cg,cb);
   if (bw == TRUE)
   {
      gray = (cr+cg+cb)*inv3;
      if (gray > doub128)
      {
         line[0][x] = white;
         line[1][x] = white;
         line[2][x] = white;
      }
      else
      {
         line[0][x] = black;
         line[1][x] = black;
         line[2][x] = black;
      }
   }
   else
   {
      line[0][x] = cr;
      line[1][x] = cg;
      line[2][x] = cb;
   }
} /* setpnt */
/****************************************/

setmaps(n)
int n;
/*
   set up maps for a textured ellipsoid

   called by readells.
   calls     mtexture, domaps.
*/
{
   int e,k;

   if (debug < 1)
      printf("setmapsa %d %g %g\n",n,color[n][1],color[n][2]);
   xoffset[n] = color[n][1];
   yoffset[n] = color[n][2];
   k = -color[n][0];
   if (mapdone[k] == 0)
   {
      mapdone[k] = 1;
      mtexture(n);
      domaps(n);
   }
   else
   {
      for (e = 0; ((e < n)&&(color[e][0] != color[n][0])); e++);
      for (k = 0; k <= 9; ++k)
      {
         maps[n][k] = maps[e][k];
         mapsizes[n][k] = mapsizes[e][k];
      }
   }
} /* setmaps */
/*********************************************/

domaps(n)
int n; /* ellipsoid number n */
/*
   select size and name of image file to map onto ellipsoid n.

   called by setmaps
*/
{
   char inmap[BMAX];
   char *mptr;
   int start;
   int i,j;
   FILE *INMAP;

   for (j = 0, start = width; start > 0; j++, start /= 2)
   {
	if (start < 10)
           sprintf(inmap,
              "%s.00%1d",mnames[n],start); /* path of map */
	else if (start < 100)
           sprintf(inmap,"%s.0%2d",mnames[n],start);
	else
           sprintf(inmap,"%s.%3d",mnames[n],start);
        if (debug <= 0)
           printf(
              "domaps: ellipsoid %d uses map %s\n",n,inmap);
	INMAP = fopen(inmap,"r");
	if (INMAP == NULL)
        {
           printf("\nERROR raseln: no map file %s\n",
                inmap);
           printf("domaps: INMAP = null\n");
           exit(1);
        }
        mptr = (char *) (malloc(start*start*3) );
	if (mptr == NULL)
        {
           printf(
               "\nERROR raseln: domaps: no memory left ");
           printf("ellipsoid %d\n",n);
           exit(1);
        }
        maps[n][j] = mptr;
	mapsizes[n][j] = start;
	for (i = 0; i < (start*start*3); i++)
           mptr[i] = (char)getc(INMAP);
	fclose(INMAP);
   }
} /* domaps */
/******************************************/

mtexture(n)
int n;
/*
     make pre-antialiased texture maps
        John Chapman  1985

   input:  a 'ppm' image texture map

   output: unheaded files: map.512, map.256, map.128, .... map.001
           which are anti-aliased texture maps of the
           indicated size.

   called by setmaps.
   calls  nextmap.
*/
{
   char buf[BMAX];
   char comprname[BMAX];  /* the compressed input file name */
   char command[BMAX];
   char inname[BMAX];
   char outmap[BMAX];     /* the current output file name */
   char title[BMAX];
   unsigned char *outptr;
   int cmax;
   int i;
   int frno;
   int height;
   int red,green,blue;
   FILE *INFILE;
   FILE *OUTMAP;

   for (i = 0; i < BMAX; ++i) infile[i] = '\0';
   for (i = 0; mnames[n][i] != '\0'; ++i)
      infile[i] = mnames[n][i];
   if (NULL == ( INFILE = fopen(infile,"r")))
   {
      sprintf(comprname,"%s.Z",infile);
      if (NULL == (INFILE = fopen(comprname,"r")))
      {
         printf(
            "\nERROR raseln cannot open %s for reading\n",
                comprname);
         printf("for ellipsoid %d frame %d\n",
                n+1,frame);
         exit(1);
      }
      else
      {
         fclose(INFILE);
         sprintf(command,"uncompress %s\n",infile);
         system(command);
         if (NULL == ( INFILE = fopen(infile,"r")))
         {
            printf(
               "\nERROR raseln cannot find uncompressed %s.Z\n",
                   infile);
            printf(
               "for reading for ellipsoid %d frame %d\n",
                   n+1,frame);
            exit(1);
         }
      }
   }
   if (debug <= 0) printf("mtexture opened %s\n",infile);
/*
    read in the base map, check and remove its header, and create infile.512 -
*/
   fscanf(INFILE,"%s\n",buf);
   fscanf(INFILE,"%d\n",&width);
   fscanf(INFILE,"%d\n",&height);
   fscanf(INFILE,"%d\n",&cmax);
   
   if ( (width > XMAX) || (width != height) || (width < 1))
   {
      printf(
         "\nERROR raseln: texture map file %s funny size: %d %d\n",
         infile,width,height);
      exit(1);
   }
   if (mapsdone(width) == TRUE) fclose(INFILE);
   else
   {
      sprintf(outmap,"%s.%d",infile,width);
      if (NULL == (OUTMAP=fopen(outmap,"w")))
      {
         printf(
            "\nERROR raseln cannot open %s for writing\n",outmap);
         perror("mtexture ");
         exit(1);
      }
      else
      {
         if (debug <= 0) printf(
            "mtexture writing %s\n",outmap);
         outptr=map;
         for (i = 0; i < (width*width); i++)
         {
            fscanf(INFILE,"%d %d %d",&red,&green,&blue);
            *outptr++ = red;
            *outptr++ = green;
            *outptr++ = blue;
            putc(red,OUTMAP);
            putc(green,OUTMAP);
            putc(blue,OUTMAP);
         }
         fclose(OUTMAP);
         for (i = width/2; i > 0; i /= 2)
         {
            if (i > 999)
            {
               printf("\nERROR raseln: width %d too big\n",
                  width);
               exit(1);
            }
            else
            if (i > 99)
               sprintf(buf,"%d",i);
            else
            if (i > 9)
               sprintf(buf,"0%d",i);
            else
               sprintf(buf,"00%d",i);
            nextmap(map,buf,i,infile);
         }
      }
      fclose(INFILE);
   }
} /* mtexture */
/***********************************************/

nextmap(map,suff,msize,infile)
unsigned char *map;
char *suff;
int  msize;
char infile[BMAX];
/*
   called by mtexture.
*/
{
   FILE *OUTF;
   char outf[BMAX];
   unsigned register char *srcptr,*src2,*dstptr;
   unsigned int  red, green, blue;
   int  i,j;

   sprintf(outf,"%s.%s",infile,suff);
   if (debug <= 0) printf("nextmap %s\n",outf);
   OUTF= fopen(outf,"w");

   srcptr = dstptr = map;
   src2 = srcptr + ((msize + msize) * 3 );

   for (i=0; i<msize; i++)
   {
      for (j=0; j<msize; j++)
      {
	 red = (*srcptr++) + (*src2++);
	 green = (*srcptr++) + (*src2++);
	 blue = (*srcptr++) + (*src2++);
	 red += (*srcptr++) + (*src2++);
	 green += (*srcptr++) + (*src2++);
	 blue += (*srcptr++) + (*src2++);

	 if (debug < 0)
            printf("%d %d %d %d %d %d\n",msize,i,j,red,green,blue);
         red = (red+1)/4;
	 green = (green+1)/4;
	 blue = (blue+1)/4;
	
         putc(red,OUTF);
         putc(green,OUTF);
         putc(blue,OUTF);

	 *dstptr++ = red;
	 *dstptr++ = green;
	 *dstptr++ = blue;
 
      }
      srcptr += (3 * (msize+msize));
      src2   += (3 * (msize+msize));
   }
   fclose(OUTF);
} /* nextmap */
/**********************************************/

texture(dx,dy,dz,n,red,green,blue)
double dx,dy,dz;
int n;
double *red,*green,*blue;
/*
   find colour from appropriate texture map of point on
   ellipsoid n at (dx,dy,dz) wrt its centre.
   Maps ellipsoid to sphere, and uses longitude and
   latitude of point (theta,phi) as (x,y) into map.

   called by  shadel
*/
{
   double cx,cy,cz; /* the coords of the corresponding points on a sphere */
   double theta,phi;
   unsigned char *ptr;
   int xp,yp;  /* indices into the texture map */
   int tz,j,mapno,mapsize;

   if (debug < 0)
   {
      printf("texturea %d %f %f %f\n",n,dx,dy,dz);
      for (j = 0; j < 3; ++j)
         printf("      %f %f %f\n",
             rell[n][j][0],rell[n][j][1],rell[n][j][2]);
   }
   cx = dx*rell[n][0][0] + dy*rell[n][0][1] +dz*rell[n][0][2];
   cy = dx*rell[n][1][0] + dy*rell[n][1][1] +dz*rell[n][1][2];
   cz = dx*rell[n][2][0] + dy*rell[n][2][1] +dz*rell[n][2][2];
   theta = asin(cy);
   theta = pi/doub2 - theta;
   phi = atan2(cx,cz);
   tz = (int) (max( max(ax3[n][0],ax3[n][1]), ax3[n][2]) );

   for (mapno = 9; ((mapsizes[n][mapno] < tz) && (mapno > 0));
           mapno--);
   mapsize = mapsizes[n][mapno];
   xp = (int)(mapsize*(doub1-(phi/twopi)
           -((double)xoffset[n]/(double)width)));
   if (xp < 0) xp += mapsize;
   if (mapsize != 0) xp = xp%mapsize;
   yp = (int)(mapsize*((theta/pi)
           +((double)yoffset[n]/(double)width)));
   if (yp < 0) yp += mapsize;
   if (mapsize != 0) yp = yp%mapsize;
   if (debug < 0)
      printf(
         "textureb %d %d %d %f %f %f %f %f %d %d %d %d %d\n",
         n,xoffset[n],yoffset[n],theta,phi,cx,cy,cz,
         mapno,mapsize,tz,xp,yp);
   ptr = (unsigned char *) maps[n][mapno];
   ptr += ((mapsize*yp + xp) * 3);
   *red = (int ) *ptr++;
   *green = (int ) *ptr++;
   *blue = (int ) *ptr;
} /* texture */
/*************************************************/

int mapsdone(width)
int width;
/*
   check whether maps already done
*/
{
   char buf[BMAX];
   FILE *INFILE;
   int i;

   for (i = width/2; i > 0; i /= 2)
   {
      if (i > 999)
      {
         printf("\nERROR raseln: width %d too big\n",
            width);
         exit(1);
      }
      else
      if (i > 99)
         sprintf(buf,"%s.%d",infile,i);
      else
      if (i > 9)
         sprintf(buf,"%s.0%d",infile,i);
      else
         sprintf(buf,"%s.00%d",infile,i);
      if ((INFILE = fopen(buf,"r")) == NULL)
         return(FALSE);
           else fclose(INFILE);
   }
   return(TRUE);
} /* mapsdone */
/*****************************************************/
