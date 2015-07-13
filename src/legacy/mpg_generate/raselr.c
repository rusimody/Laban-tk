/*
   program raselr   ( C unix )

    to create files of raster shaded images of ellipsoids
    from an ellipsoid file into 'ppm' format
    which can then be displayed by 'xv'
    or converted to gif format by ppmtogif
    (possibly preceeded by ppmquant 256)
    and/or turned into movies by 'movieconverter' in 'media' toolbox

  usage:
   raselr f [-b b] [-c] [-d d] [-l l] [-x x] [-z] < i

  where:
   f = stem required for output file names
   b = number of ellipsoids not to be blurred (default: all)
   d = debug value: 1 = none, 0 = some (default 1)
   l = number of lines to be blurred together (default 10)
   x = number of pixels square (default 256)
   z = shade using z depth
   i = input file name (a nudes.3 type file)

  modified:
     Jun 1999 not to store colours
     Jun 1999 use CMAX for shades if -c parameter is 0 or too big
     Oct 1996 use 0 and 255 for b/w
     Jun 1996 accommodate ppm image maps
     Jun 1996 change output file names
     May 1996 output ppm files
     May 1996 fix blurring errors at edges
     Apr 1996 allow blurring
     Apr 1996 allow z shading
     Feb 1996 to scan y upward
     Jan 1996 to give white background
     Oct 1995 for 5 line image file headings
     May 1993 to accommodate variable length data values
     Nov 1992 to accommodate viewing parameters 
     Jan 1992 to count the colours used 
     Jul 1991 allow arbitrary number of colours 
     Nov 1987 use texture map files of any size 
     Oct 1987 produce colour or b/w images 
     Oct 1987 for Sun 3/50 
     Nov 1986 uses normal 512*512 images 
     Oct 1986 creates and uses antialiassed submaps (John Chapman)
     Oct 1986 allow texture mapping (John Chapman)
     Aug 1986 allows multiple frames 
     Oct 1985 shading removed from inner loop (John Chapman)
     Sep 1985 converted from Unix f77 to C (John Chapman)

     Don Herbison-Evans 1978
 
 input data: taken from standard input as a nudes.3 file :

         number of ellipsoids,  frame number, 6 viewing parameters 

   and then a set of lines, one for each ellipsoid, containing:

         3 semiaxis lengths, 3 coords of centre, 3 angles of
         orientation, 3 colour components, ellipsoid name,
         texture map file name, and a sequence number.
 
 subroutines:-
      main    - organise things
      setup   - set constants
      readells- read ellipsoid data for a frame
      setell  - set ellipsoid's containing box and coefficients 
      mkrotn  - convert angles into rotn array entry
      rotget  - retrieve rotation matrix from rotn array
      setmat  - find matrix representing an ellipsoid
      matmul  - multiply two matrices together
      setcof  - find ellipsoid coefficients from matrix form
      setpln  - find coefficients of outline plane
      shadel  - loop through all x and y, colouring appropriately
      zdepth  - find depth of ellipsoid surface at point x,y
      illum   - find relative brightness of point on surface
      opnin   - open input file and set screen size and scalings
      opnout  - initialise each output  file in turn
      storepnt- store an unblurred pixel
      doblur  - blur the blurable pixels
      setpnt  - set red,green,blue colour at point in image
      setmaps - set up set of texture maps
      domaps  - select size and image file for an ellipsoid
      mtexture- set up antialiased maps for mapping
      nextmap - do next antialiased map
      texture - apply texture map to an ellipsoid surface
      mapsdone- test whether texture maps already made

*/
#include <stdio.h>

#define min(a,b)  ( (a)<(b)?(a):(b) )
#define max(a,b)  ( (a)>(b)?(a):(b) )
#define  BMAX   256
#define  CMAX   256
#define  EMAX  1024  
#define  XMAX  4096
#define  TRUE     1
#define FALSE     0

double sin(),cos(),atan2(),sqrt(),acos(),asin();

double ambint;
double ax3[EMAX][3];
double ang[EMAX][3];
double bg;                 /* components of the background colours */
double bignum;
double cen[EMAX][3];
double coef[EMAX][6];
double den[EMAX];
double deg10;
double doub0;
double doub1;
double doub2;
double doub4;
double doub128;
double ell[EMAX][3][3];
double inv2;
double inv3;
double inv10;
double pi;
double plane[EMAX][3];
double rell[EMAX][3][3];
double twopi;
double xfac,yfac;
double xmax3[EMAX];
double xmin3[EMAX];
double ymax3[EMAX];
double ymin3[EMAX];
double zmax3[EMAX];
double zmin3[EMAX];
double zmax;
double zmin;

int    a1,a2,a3;
int    angn[3];
int    axn[3];
int    blur[XMAX][XMAX][3];/* blur buffer */
int    bw;                 /* true if not in colour */
int    cenn[3];
int    color[EMAX][3];     /* colours of the ellipsoids */
int    count;              /* count of spaces used on a line in output file */
int    f;
int    debug = 1;          /* debug value: 0 = some, 1 = none */
int    frame;
int    lblur;              /* number of lines to be blurred together */
int    m,n;
int    mapsizes[EMAX][10]; /* size of each map */
int    mapdone[EMAX];      /* 1 if map done already */
int    nblur;              /* number of ellipsoids to be blurred */
int    ncols;              /* number of colours used */
int    nels;               /* number of ellipsoids in current frame */
int    nfr = 0;
int    nxy[XMAX][XMAX];    /* blur ellipsoid buffer */
int    shades;             /* number of requested shades of each primary */
int    tmp = FALSE;        /* true if subdirectory tmp used */
int    usey;               /* true if y component of surface normal  used */
int    vx,vy,vz;
int    width;
int    xoffset[EMAX];      /* x offset of centre of each map */
int    yoffset[EMAX];      /* y offset of centre of each map */
int    xtop,ytop;

char   buf[BMAX];
char   cmnd[BMAX];
char   enames[EMAX][BMAX]; /* names of ellipsoids */
char   fname[BMAX];
char   infile[BMAX];
char   mnames[EMAX][BMAX]; /* names of texture files for ellipsoids */
unsigned char map[XMAX*XMAX*3];
char   *maps[EMAX][10];    /* pointers to texture maps */
char   outfile[BMAX];

FILE   *OUTFILE;
FILE   *FCOLS;

/******************************************************/

main(argc,argv)
char *argv[];
int argc;
/*
   calls  opnin, setup, readells, opnout, setell, shadel,
	  doblur,
	  atan2, fprintf, printf, sscanf, gets.
*/
{
   int f;

   setup();
   opnin(argc,argv);
/*
   run through frames of film-
*/
   for (f = 1; f <= bignum ; f++)
   {
      if( NULL == gets(buf) )
      {
         printf(
          "\nERROR raselr: unexpected EOF frame %d from file\n",f);
         exit(1);
      }
      sscanf(buf,"%d %d %d %d %d %d %d %d",
             &nels,&frame,&vx,&vy,&vz,&a1,&a2,&a3);
      if (debug <= 0)
      {
	 if ( bw == TRUE) printf("maina %d %d bw = true\n",nels,frame);
            else printf("maina %d %d bw = false\n",nels,frame);
      }
      if (nels <= 0) goto end;
      opnout(argv);
      readells();
      setell();
      shadel();
      doblur();
      if (count > 0) fprintf(OUTFILE,"\n");
      fclose(OUTFILE);
      nfr ++;
   }
end: if (tmp) system("rm tmp\n");
     exit(0);
} /* main */
/**************************************/

setup()
/*
   set up constants

   called by main.
*/
{
   int     j,k;

   ambint = 0.2;
   doub0 = (double)0;
   doub1 = (double)1;
   doub2 = (double)2;
   doub4 = (double)4;
   doub128 = (double)128;
   inv2 = doub1/doub2;
   inv3 = doub1/(double)3;
   inv10 = doub1/(double)10;
   usey = TRUE;
   ncols = 2;
   nblur = 0;
   lblur = 10;
   bignum = 32768*32768;
   if (bignum < 0) bignum = -bignum;
   bw = TRUE;
   bg = (double)255;
   for (j = 0; j < EMAX; j++) mapdone[j] = 0;
   for (j = 0; j < EMAX; j++) 
   {
      for (k = 0; k < BMAX; ++k)
      {
         enames[j][k] = '\0';
         mnames[j][k] = '\0';
      }
   if (debug <= 0) printf("setupa %d\n",bignum);
   }
   pi = (double)4*atan2(doub1,doub1);
   twopi = pi+pi;
   deg10 = pi/(double)1800;
} /* setup */
/*******************************************/

readells()
/*
   run through ellipsoids of frame, reading and setting them up 

   called by main.
   calls     setmaps.
*/

{
   int j,k,n;

   if (debug <= 0) printf("readellsa %d\n",nels);
   for (n = 0; n < nels ; n++)
   {
      if( NULL == gets(buf) )
      {
         printf(
           "\nERROR raselr: EOF frame %d ellipsoid %d\n",
             frame,n);
         exit(1);
      }
      sscanf(buf,"%d %d %d %d %d %d %d %d %d %d %d %d %s %s\n",
          &axn[0],&axn[1],&axn[2],
          &cenn[0],&cenn[1],&cenn[2],
          &angn[0],&angn[1],&angn[2],
          &color[n][0],&color[n][1],&color[n][2],
          enames[n],mnames[n]);
      if (debug < 0)
      {
         printf(
            "mainb %d %s %d %d %d %d %d %d %d %d %d %d %d %d\n",
            n,enames[n],axn[0],axn[1],axn[2],
            cenn[0],cenn[1],cenn[2],
            angn[0],angn[1],angn[2],
            color[n][0],color[n][1],color[n][2]);
      }
      if (color[n][0] < 0)
      {
         setmaps(n);
         if (debug <= 0) printf("readellsb %s %d %d\n",
               mnames[n],xoffset[n],yoffset[n]);
      }
      for (k = 0; k < 3; ++k)
      {
         ax3[n][k] = inv10*axn[k];
         cen[n][k] = inv10*cenn[k];
         ang[n][k] = deg10*angn[k];
      }
   }
   if (nblur < 1) nblur = nels;
   if (debug <= 0) printf("readellsb %d\n",nels);
} /* readells */
/***************************************************/

setell()
/*
    for each ellipsoid-
	set up containing box (xmin,xmax,ymin,ymax,zmin,zmax)
	set up coefficients of
	   matrix representation
	   polynomial representation
	   plane of outline
 
    calls  rotget, setmat, setcof, setpln
    called by main
*/
{
   int j,k,n;
   double extent[3],r[3][3],rotn[5],unr[3][3];

   if (debug <= 0) printf("setella %d\n",nels);
   zmax = cen[0][2];
   zmin = cen[0][2];
   for (n = 0; n < nels; n++)
   {
        if (debug < 0) printf(
           "setellb %d %g %g %g %g %g %g\n",
   	   n,ax3[n][0],ax3[n][1],ax3[n][2],
             ang[n][0],ang[n][1],ang[n][3]);
       mkrotn(rotn,ang[n][0],ang[n][1],ang[n][2]);
       rotget(rotn,r,unr);

       for (k = 0; k < 3; k++)
       {
          extent[k] = doub0;
       	  for (j = 0; j < 3; j++)
          {
             extent[k]=extent[k]+(ax3[n][j]*r[k][j])
   				    *(ax3[n][j]*r[k][j]);
           }
       	   extent[k]=sqrt(extent[k]);
     	}
        xmin3[n]=cen[n][0]-extent[0];
        xmax3[n]=cen[n][0]+extent[0];
        ymin3[n]=cen[n][1]-extent[1];
        ymax3[n]=cen[n][1]+extent[1];
        zmin3[n]=cen[n][2]-extent[2];
        zmax3[n]=cen[n][2]+extent[2];
	if (zmax < zmax3[n]) zmax = zmax3[n];
	if (zmin > zmin3[n]) zmin = zmin3[n];
        if (debug < 0) printf(
           "setellc %d %g %g %g %g %g\n",
   	      n,xmin3[n],xmax3[n],ymin3[n],ymax3[n],zmin3[n]);
        setmat(r,n,ell,ax3,den);
        setcof(n);
        setpln(n);
    }
   if (debug <= 0) printf("setelld %d %g %g\n",nels,zmin,zmax);
} /* setell */
/******************************************/

mkrotn(rotn,a1,a2,a3)
double rotn[5],a1,a2,a3;
/*
 
    convert angles a1,a2,a3 into rotn entries
 
    called by input
 
*/
{
   double s1,c1,s2,c2,s3,c3;

      if (debug < 0)
	 printf(" mkrotn %12.4g %12.4g %12.4g\n",a1,a2,a3);
      s1=sin(a1);
      c1=cos(a1);
      s2=sin(a2);
      c2=cos(a2);
      s3=sin(a3);
      c3=cos(a3);
      rotn[0]=c1*c2;
      rotn[1]=s1*c2;
      rotn[2]=s2;
      rotn[3]=s3;
      rotn[4]=c3;
} /* mkrotn */
/**********************************************/

rotget(rotn,r,unr)
double   rotn[5],r[3][3],unr[3][3];
/*
    form a rotation matrix r and its inverse unr
    from the entries in rotn

    called by  setell
*/
{
   int i,j;
   double cp,sp,x,y,z,m,xsp,ysp,zsp,xm,ym,zm,xym,xzm,yzm;

      if (debug < 0) 
	printf("rotgeta %f %f %f %f %f\n",
		 rotn[0],rotn[1],rotn[2],rotn[3],rotn[4]);
      x = rotn[0];
      y = rotn[1];
      z = rotn[2];
      sp = rotn[3];
      cp = rotn[4];
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
 
      if (debug < 0)
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

      if (debug < 0)
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
	    printf(
               "\nERROR raselr subr setmat ax3[%d][%d]=0\n\n",n,j);
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
         if (debug < 0)
            printf("setmatb %d %f %f %f %f %f %f\n",
               n,rr[j][0],rr[j][1],rr[j][2],rel[j][0],rel[j][1],rel[j][2]);
      }
      if (ell[n][2][2] != doub0)
      	 den[n]=doub1/ell[n][2][2];
      else
         printf(
            "\nERROR raselr subr setmat, ell[%d][2][2]=0\n\n",n);
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
      if (debug < 0) printf(
          "setcof %d %f %f %f %f %f %f\n",
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
      if (debug < 0) {
	 printf("setpln %d %f %f %f\n",
		   n,plane[n][0],plane[n][1],plane[n][2]);
	 }
} /* setpln */
/******************************************************/

shadel()
/*
    loop through all x and y, coloring as appropriate
 
    calls  zdepth, illum, storepnt
*/
{
   double illum();
   double depth,light,x,y,z,tr,tg,tb;
   double plan23[EMAX],coef34[EMAX],coef256[EMAX],ell2y[EMAX][3];
   int    j,h,w,step,active[EMAX],nactive;
   int    m,n;
   int    noel;

   noel = 2*nels;
   step = 1;
/*
    scan down y direction-
*/
   for (h = 0; h < ytop; h += step)
   {
      if (debug <= -1)
         fprintf(stderr,"shadela %d\n",h);
      y = yfac*(double)h;
      nactive = 0;
/*
   do as much calculation as possible for this y scanline-
*/ 
      for (m = 0; m < nels; m++)
      {
         if ( (y < ymax3[m]) && (y > ymin3[m]) )
         {
            active[nactive] = m;
            plan23[m] = plane[m][2]+plane[m][1]*y;
            coef34[m] = coef[m][2]*y+coef[m][3];
            coef256[m] = y*(coef[m][1]*y+coef[m][4])+coef[m][5];
            for (j = 0; j < 3; j++)
               ell2y[m][j] = ell[m][1][j]*(y-cen[m][1]);
            nactive = nactive+1;
         } /* y in range */
      } /* m */
      if (debug <= 0) printf("shadelb %d %d\n",h,nactive);
/*
   scan in x across scanline-
*/
      for (w = 0; w < xtop; w+=step)
      {
         n = noel;
         tr = bg; tg = bg; tb = bg;
         if (nactive > 0) 
         {
            x = xfac*(double)w;
            depth = zmax;
/* 
         fine nearest ellipsoid coloring this point -
*/ 
            for (j = 0; j < nactive; j++)
            {
               m = active[j];
               if ( (x < xmax3[m]) && (x > xmin3[m]) && (zmin3[m] < depth) )
               {
                   zdepth(m,x,y,&z,plan23,coef34,coef256);
                   if (z <  depth) 
                   {
                      depth = z;
		      n = m;
                   } /* if z < depth */
               } /* if x */
            } /* j */
         } /* nactive > 0 */
         if (n < noel)
         {
            z = depth;
            light = illum(n,x-cen[n][0],y-cen[n][1],z-cen[n][2],
                          ell2y);
            if (color[n][0] >= 0)
            {
               tr = color[n][0];
               tg = color[n][1];
               tb = color[n][2];
            }
            else
               texture(x-cen[n][0],y-cen[n][1],z-cen[n][2],n,&tr,&tg,&tb);
            tr = inv2*(tr*light - doub128) + doub128;
            tg = inv2*(tg*light - doub128) + doub128;
            tb = inv2*(tb*light - doub128) + doub128;
         } /* n < noel */
         if (n > nels) n == -1;
         if (debug <= 0)
	    printf("shadelc %d %d %d %g %g %g %g %g\n",
	       h,w,n,light,depth,tr,tg,tb);
         storepnt(n,w,h,tr,tg,tb);
      } /* w */
   } /* h */
   if (debug <= 0)
      printf("shadeld %d %d\n",xtop,ytop);
} /* shadel */
/***********************************************/
 
zdepth(n,x,y,z,plan23,coef34,cof256)
int   n;
double x,y,*z,plan23[],coef34[],cof256[];
/*
    find the depth z of the nearer surface of the n'th ellipsoid
    at point x,y

   called by shadel
*/
{
   double discrt;
 
   *z = bignum;
   discrt = (-((coef[n][0]*x+coef34[n])*x+cof256[n])*den[n]);
   if (discrt > doub0)
   *z = (-plan23[n]-plane[n][0]*x-sqrt(discrt));
   if (debug < 0)
      printf(
         "zdepth %d %12g %12g %12g %12g %12g %12g %12g %12g\n",
             n,x,y,coef[n][0],coef34[n],cof256[n],den[n],discrt,*z);
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
   double a;
   double grad[3],tgrad,tgradsq;
   double f1,f2;
   double light;
   double zn;
 
   light = doub0;
   tgradsq = doub0;
   zn = z + cen[n][2];
   for (j = 0; j < 3; j++)
   {
       grad[j] = ell[n][0][j]*x+ell2y[n][j]+ell[n][2][j]*z;
       tgradsq += grad[j]*grad[j];
   } 
   if (tgradsq > doub0) 
   {
      tgrad = sqrt(tgradsq);
      a = doub1;
      if (usey == TRUE)
	 f1 = grad[1]/tgrad;
      else
      {
	 f1 = -grad[2]/tgrad;
         a = (zmax - zn)/(zmax - zmin);
      }
      f1 = doub2*f1/(doub1+f1*f1);
      f1 = doub2*f1/(doub1+f1*f1);
      f2 = (doub1 + f1)*inv2;
      light = a*(ambint+(doub1-ambint)*f2);
   }
   if (debug < 0) printf(
      "illumb %d %g %g %g %g %g %g %g\n",
         n,f1,f2,a,light,zmax,zmin,zn);
   return(light);
} /* illum */
/***********************************************/

opnin(argc,argv)
char *argv[];
int argc;
/*

   read flags, open input file, and set screen size and scalings

   called by main.
   calls sscanf, exit, strcpy.
*/
{
   int j;

   if (argc < 2)
   {
       printf(
         "usage: raselr f [-b b] [-c c] [-d d] [-l l] [-x x] [-z] < f.3\n");
       exit(1);
   }
   xtop = 256;
   ytop = 256;
   for (j = 1; j < argc; ++j)
   {
       strcpy(buf,argv[j]);
       if (debug <= 0) printf("opnina %d %s\n",j,buf);
       if (buf[0] == '-')
       {
          if (buf[1] == 'b')
          {
             ++j;
             sscanf(argv[j],"%d",&nblur);
             if (nblur < 1)
             {
                printf(
                  "\nERROR raselr: funny number of blurred ellipsoids : %d\n",
		  nblur);
                exit(1);
             }
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
          if (buf[1] == 'l')
          {
             ++j;
             sscanf(argv[j], "%d", &lblur);
          }
	  else
          if (buf[1] == 'x')
          {
	      ++j;
	      sscanf(argv[j], "%d", &xtop);
              if (xtop < 0 ) xtop = -xtop;
	      if ((xtop >= XMAX) || (xtop < 1))
              {
                 printf(
                    "\nERROR raselr: requested image size is %d\n",
                     xtop);
	         printf( "max accommodated is %d\n", XMAX);
	           exit(1);
	      }
	      ytop = xtop;
          }
	  else
          if (buf[1] == 'z') usey = FALSE;
          else
          {
	      printf(
                 "\nERROR raselr: unrecognised flag %s\n", buf);
	      exit (1);
          }
       } /* buf0 == '-' */
       else
         sprintf(fname,"%s",argv[j]);
   }
   if (xtop != 0) xfac = (double)1000/(double)xtop;
      else xfac = doub4;
   if (ytop != 0) yfac = (double)1000/(double)ytop;
      else yfac = doub4;
} /* opnin */
/***********************************/

opnout()
/*
    create new file and send header for frame.
 
    called by main.
*/
{
   if ((nfr >= 0 ) && (nfr <= 9 ))
              sprintf(outfile,"%s.000%d.ppm",fname,nfr);
   if ((nfr >= 10) && (nfr <= 99))
              sprintf(outfile,"%s.00%d.ppm",fname,nfr);
   if ((nfr >= 100) && (nfr <= 999))
              sprintf(outfile,"%s.0%d.ppm",fname,nfr);
   if (nfr >= 1000)
              sprintf(outfile,"%s.%d.ppm",fname,nfr);
   if( NULL == (OUTFILE=fopen(outfile,"w+")) )
   {
       printf(
          "\nERROR raselr: can't open/create %s for writing\n",
          outfile);
       exit(1);
   }
   fprintf(OUTFILE,"P3\n %d\n %d\n %d\n",xtop,ytop,CMAX-1);
   count = 0;
   ncols = 2;
   if (debug <= 0) printf("opnouta %s\n",outfile);
} /* opnout */
/*************************************************/

storepnt(n,w,h,dr,dg,db)
int    n,w,h;
double dr,dg,db;
/*
   store the colour (dr,dg,db) in blur buffer
   and ellipsoid (n) at point (w,h).

   called by shadel.
*/
{
   unsigned int  ir,ig,ib;

   if (bw == TRUE)
   {
      ir = (dr + dg + db)*inv3;
      ig = ir;
      ib = ir;
   }
   else
   {
      ir = dr;
      ig = dg;
      ib = db;
   }
   blur[h][w][0] = ir;
   blur[h][w][1] = ig;
   blur[h][w][2] = ib;
   nxy[h][w] = n;
} /* storepnt */
/*******************************************/

doblur()
/*
   blur the images of blurrable ellipsoids

   called by main.
   calls setpnt.
*/
{
   double bcount;
   int hlblur;
   int bot,top;
   int j,k;
   int x,y;
   int sumr,sumg,sumb;
   int xk,yj;
   unsigned int ir,ig,ib;

   if (debug <= 0)
       printf("doblura %d\n",lblur);
   hlblur = lblur/2;
   bot = -lblur;
   top = bot+lblur;
   for (y = ytop-1; y >= 0; --y)
   {
      for (x = 0; x < xtop; ++x)
      {
	 ir = blur[y][x][0];
	 ig = blur[y][x][1];
	 ib = blur[y][x][2];
	 if ((nxy[y][x] > nblur) && (nxy[y][x] < nels))
	 {
	    if (debug <= 0)
	       printf("doblurb %d %d %d %d %d %d %d\n",
	          y,x,ir,ig,ib,nxy[y][x],nblur);
	    bcount = doub0;
	    sumr = doub0;
	    sumg = doub0;
	    sumb = doub0;
	    for (j = bot; j < top; ++j);
	    {
	       yj = y+j;
               if ((yj >= 0) && (yj < ytop))
               {
	          for (k = bot; k < top; ++k)
	          {
		     xk = x+k;
                     if ((xk >= 0) && (xk < xtop))
                     {
		        if (nxy[yj][xk] > nblur)
		        {
		           sumr += blur[yj][xk][0];
		           sumg += blur[yj][xk][1];
		           sumb += blur[yj][xk][2];
		           bcount += doub1;;
		        } /* n < nblur */
                     } /* if xk */
	          } /* k */
               } /* if yj */
	    } /* j */
	    if (bcount > doub0)
	    {
	       ir = sumr/bcount;
	       ig = sumg/bcount;
	       ib = sumb/bcount;
	    }
	    if (debug <= -1)
	       printf("doblurb %d %d %d %d %d %d %d %g\n",
	          y,x,ir,ig,ib,nxy[y][x],nblur,bcount);
	 } /* n, x, and y in blurring range  */
	 setpnt(ir,ig,ib);
      } /* x */
      if (debug <= 0)
        printf("doblurc %d %d\n",y,count);
   } /* y */
} /* doblur */
/***********************************************/

setpnt(ir,ig,ib)
unsigned int ir,ig,ib;
/*
   write out a point

   called by doblur.
*/
{
   fprintf(OUTFILE,"%3d %3d %3d ",ir,ig,ib);
   count += 12;
   if (count > 57)
   {
      count = 0;
      fprintf(OUTFILE,"\n");
   }
} /* setpnt */
/***********************************************/

setmaps(n)
int n;
/*
   set up maps for a textured ellipsoid

   called by readells.
   calls     mtexture, domaps.
*/
{
   int e,k;

   if (debug <= 0) printf("setmaps %d\n",n);
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
           printf("\nERROR raselr: no map file %s\n",
                inmap);
           printf("domaps: INMAP = null\n");
           exit(1);
        }
        mptr = (char *) (malloc(start*start*3) );
	if (mptr == NULL)
        {
           printf(
               "\nERROR raselr: domaps: no memory left ");
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
   char outmap[BMAX];    /* the current output file name */
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
            "\nERROR raselr cannot open %s for reading\n",
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
               "\nERROR raselr cannot find uncompressed %s.Z\n",
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
         "\nERROR raselr: texture map file %s funny size: %d %d\n",
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
            "\nERROR raselr cannot open %s for writing\n",outmap);
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
               printf("\nERROR raselr: width %d too big\n",
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

   if (debug <= 0) printf(
      "mapsdone: testing %s.%d\n",infile,width);
   for (i = width/2; i > 0; i /= 2)
   {
      if (i > 999)
      {
         printf("\nERROR raselr: width %d too big\n",
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

