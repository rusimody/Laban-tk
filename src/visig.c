/*   program visig   ( c unix vax 780 version ) 

   modified -  

      6 Aug  1993  D.Herbison-Evans  read joints too
     23 Jul  1992  D.Herbison-Evans  index arrays from 0
     16 Jul  1992  D.Herbison-Evans  remove window tests
     13 Nov  1992  D.Herbison-Evans  allow for viewing transform
      3 Oct  1987  D.Herbison-Evans  cube roots done by logarithms
     18 Sep  1987  D.Herbison-Evans  translated into C
     19 Jan  1987  D.Herbison-Evans  ignore ellipsoids in front of z = 0 
     31 Jul  1986  D.Herbison-Evans  cope with identical ellipsoids 
     22 Feb  1986  D.Herbison-Evans  cubic stabilised more 
      1 Jan  1986  P.Gummer          a and b intersection logic improved 
     30 Sep  1985  D.Herbison-Evans  four0a and four0b separated 
     15 Jul  1985  D.Herbison-Evans  windowing stabilised 
     14 Jul  1985  D.Herbison-Evans  new quartic algorithm 
     10 Jul  1985  P.Gummer          reduced output- semiaxes,phi 
     25 Nov  1983  D.Herbison-Evans  angles give rotation about axis 
     17 Aug  1983  D.Herbison-Evans  allow for intersection value errors 
     28 Sep  1982  D.Herbison-Evans  restrict appear array to 20 
     18 Aug  1982  D.Herbison-Evans  refer equns to centre of nth ellpsd 
     15 Jan  1982  D.Herbison-Evans  tan half Cohens parameter used 
     23 Dec  1981  D.Herbison-Evans  hidden arc calcs include topology 
     15 Dec  1981  D.Herbison-Evans  cubic and quartic stabilised 
     16 Jul  1981  C.Berry           table look-up for sine and cosine 
      1 Jun  1981  C.Prineas         table look-up for cube roots 
     26 May  1981  D.Herbison-Evans  reduce number of divisions 
     24 May  1981  D.Herbison-Evans  non-intersections saved in hash table 
     15 May  1981  C.Prineas         new quartic and cubic algorithms 
     30 Nov  1977  D.Herbison-Evans  include windowing 
     26 May  1977  D.Herbison-Evans  precalculate intersections 
     10 May  1976  D.Herbison-Evans  to separate translation/drawing 
 
     copyright (c)  Don Herbison-Evans  1972 

     This program takes 3d specifications of ellipsoids in a 
     series of frames of a movie, and projects them into 2d, 
     giving specifications of the ellipsoid outline ellipses,.

     The projections of the ellipsoids are ellipses which are 
     drawn with Cohen's parametric algorithm using 2x2 matrix 
     updating ( Proc. Comp. Graphics 70, Brunel Uni.). 

     the picture is 1000 units wide. 

   input -  
 
     each frame starts with a line containing the number of
     ellipsoids, the frame number, and the 6 viewing papmeters,
     and then for each ellipsoid, a
     line of numeric data containing the 3d coordinates of 
     the centres, 3 semiaxis lengths, the 3 quaternian angles,
     the 3 colours, the name, and the texture map file name.

   output -  

     the 2d coordinates of the centres, the two semi-axis 
     lengths, the orientation of the semi-minor axis, the 
     number of hidden arcs (0).

     error messages are written to file 'stderr'. 

  ******************************************** 

   subroutines 

     setcns - set up constants pi, etc. 
     input  - read ellipsoid information about a frame from a file 
     mkquat - convert angles to quat array entries 
     drawel - compute each ellipse outline
     setnup - set up parameters of nth ellipsoid 
     prinel - print out the parameters of the ellipsoids 
     setmat - find matrix representing an ellipsoid 
     rotget - form a rotation matrix and its inverse 
     matmul - multiply two matrices together 
     setcof - find ellipsoid coefficients from matrix form 
     setaxe - find semiaxes of an ellipse 
     setpro - find orientation
     store2 - write ellipse information to a file 

  ******************************************** 
*/ 
#include <stdio.h>
#include <values.h>

#define BMAX  128
#define EMAX 1024
#define TRUE    1
#define FALSE   0

double sqrt(),atan(),atan2(),cos(),sin();

double ang[3];
double axxn,axyn;
double ax3[EMAX+1][3];
double cen[EMAX+1][3];
double cn[3];
double con[6];
double doub1;
double elln[3][3];
double ellj33;
double inv2;
double inv10;
double nought;
double phi;
double quat[EMAX+1][5];
double pi;
double deg10;
double rad10 ;

int debug = 2;
int frame;
int f;
int m;
int n;
int nels;
int ok;

char buf[BMAX];

/**************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
     calls  setcns, input, drawel 
*/
{
   setcns();
   ok = TRUE ;
   nels = 1;
/* 
     read pictures and draw them -  
*/
   for (  f = 1 ; ((f <= MAXINT) && (nels > 0)) ; ++ f )
   {
      input() ;
      if ( ok == FALSE )
      {
         fprintf(stderr,
            "ERROR: visig: too many ellipsoids\n");
         fprintf(stderr,"   frame %d, number %d, max %d\n",
            frame,nels,EMAX);
         exit(1);
      }
      if (nels > 0)
         drawel();
      if (ok == FALSE) break;
   }
   nels = 0 ;
   printf("%d %d\n",nels,frame );
   exit (0);
} /* main */
/****************************************************/

setcns()
/* 
     set up constants 

     called by main 
*/
{
   int j ;

   nought = (double)0;
   doub1 = (double)1;
   inv2 = doub1/(double)2;
   inv10 = doub1/(double)10;
   pi = (double)4*atan(doub1) ;
   deg10 = (double)1800/pi;
   rad10 = doub1/deg10 ;
} /* setcns */
/*****************************************/

input()
/* 
        read information about current frame -  
    nels - the number of ellipsoids in it 
         (zero is null as end - of - file marker) 
    frame - the name of the current frame (f is its number) 
         the first frame name is set as the value of debug. 
    vx,vy,vz,a1,a2,a3 - viewing transform
    then for each ellipsoid, its 3 axis lengths, coordinates 
         of its centre, and its angles of orientation. 
    
     called by main 
     calls  mkquat 
*/
{
   int a0,a1,a2;
   int ang0,ang1,ang2;
   int axx,axy,axz;
   int cenx,ceny,cenz;
   int coel0,coel1;
   int col0,col1,col2;
   int jnt0,jnt1,jnt2;
   int n;
   int njts;
   int test;
   int vx,vy,vz;

   char ename[BMAX];
   char fname[BMAX];
   char jname[BMAX];

   scanf("%d %d %d %d %d %d %d %d\n",
      &nels,&frame,&vx,&vy,&vz,&a0,&a1,&a2);
   if (f == 1) 
   {
      debug = frame ;
      if (debug <= 0)
         fprintf(stderr,"inputa %d\n", debug );
   }
   if (debug <= 0)
      fprintf(stderr,"inputb %d %d %d\n",f,nels,frame );
   if (nels > EMAX) goto lab10 ;
   if (nels <= 0) goto rtrn ;
/* 
     read ellipsoids in current frame -  
*/
   for (  n = 1 ; n <= nels ; ++ n )
   {
      if (NULL == scanf("%d %d %d %d %d %d %d %d %d %d %d %d %s %s\n",
                          &axx,&axy,&axz,&cenx,&ceny,&cenz,
                          &ang0,&ang1,&ang2,&col0,&col1,&col2,
                          ename,fname))
      {
         fprintf(stderr,
           "ERROR: visig: unexpected eof reading ellipsoid %d in frame %d\n",
           n,frame);
         exit(1);
      }
      if (debug <= 0)
         fprintf(stderr,"inputc %d %d %d %d %d %d %d %d %d %d\n",
         n,axx,axy,axz,
         cenx,ceny,cenz,
         ang0,ang1,ang2);
/* 
     scale everything back to size -  
*/
      ax3[n][0] = inv10*axx ;
      ax3[n][1] = inv10*axy ;
      ax3[n][2] = inv10*axz ;
      cen[n][0]= inv10*cenx ;
      cen[n][1] = inv10*ceny ;
      cen[n][2] = inv10*cenz ;
      ang[0] = rad10*ang0 ;
      ang[1] = rad10*ang1 ;
      ang[2] = rad10*ang2 ;
      if (debug <= 0)
         fprintf(stderr,
            "inputd %9g %9g %9g %9g %9g %9g %9g %9g %9g %9g\n",
            rad10,ax3[n][0],ax3[n][1],ax3[n][2],
            cen[n][0],cen[n][1],cen[n][2],
            ang[0],ang[1],ang[2]);
/* 
     set up orientation matrix of current ellipsoid -  
*/
      mkquat(n,ang[0],ang[1],ang[2]) ;

lab4: ;
   }
/*
   read joints -
*/
   scanf("%d %d\n", &test,&njts);
   if (test == 0) goto rtrn;
   for (  n = 1 ; n <= njts ; ++ n )
   {
      scanf("%d %d %d %d %d %s\n",
         &coel0,&coel1,&jnt0,&jnt1,&jnt2,jname);
   }
   goto rtrn;
/* 
     snag -  
*/
lab10: ok = FALSE ;

rtrn:;
} /* input */
/**********************************************/

mkquat(n,a0,a1,a2)
   int n ;
   double a0,a1,a2 ;
/* 
     convert angles a0,a1,a2 into quat entries 
     for ellipsoid 'n'

     called by input 
*/
{
   double s0,c0,s1,c1,s2,c2 ;

   if (debug <= 0)
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

drawel()
/* 
     for frame f,
     this draws the outline of each ellipsoid in turn. 
     each is approximated by a series of chords, 
     plotted with respect to Cohen's parameter. 

     called by main 
     calls  prinel, setnup, store2 
*/
{
   int k;

   if (debug <= 0)
      fprintf(stderr,"drawel %d\n", nels );
/* 
     write start of new picture -  
*/
    printf("%d %d\n", nels,frame );
    if (debug <= 0) prinel() ;
/* 
     run thru ellipsoids to draw each in turn -  
*/
    for (  n = 1 ; n <= nels ; ++ n )
    {
         setnup();
         if ( ok == TRUE )
            store2() ;
         if ( ok == FALSE )
         {
            fprintf(stderr,"ERROR: visig subr drawel %d %d %d\n",
               f,frame,n); 
            break;
         }
   }
} /* end drawel */
/******************************************/

setnup()
/* 
     set up parameters of nth ellipsoid relative to own centre. 

     called by drawel 
     calls  setmat, setcof, setaxe, setpro 
*/
{
   double axe[2];

   if (debug <= 0)
      fprintf(stderr,"setnup  %d\n", n );
   setmat(n,elln) ;
   if ( ok == FALSE ) goto lab1 ;
   setcof(con,elln) ;
   if ( ok == FALSE ) goto lab1 ;
   setaxe(axe,con) ;
   if ( ok == FALSE ) goto lab1 ;
   axxn = axe[0];
   axyn = axe[1];
   setpro(con) ;
   if ( ok == FALSE ) goto lab1 ;
   goto rtrn ;
/* 
     snag -  
*/
lab1: ok = FALSE;
   fprintf(stderr,
      "ERROR: visig  setnup ellipsoid %d elln[2][2] = %9g\n",
         n,elln[2][2]);

rtrn:;
} /* setnup */
/******************************************/

prinel()
/* 
     this lists the axis lengths, positions and rotation matrices
     of all the ellipsoids. 

     called by drawel 
*/
{
   int n ;

   fprintf(stderr,"prinel - \n");
   fprintf(stderr,"   el       ax      cen     rot\n");

   for (  n = 1 ; n <= nels ; ++ n )
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
     ellipsoid by taking the diagonal matrix of inverse square semiaxes, 
     and doing on it a similarity transform for its own rotation. 

     called by setnup
     calls  rotget, matmul 
*/
{
   int j,k ;
   double r[3][3],unr[3][3] ;

   if (debug <= 0)
      fprintf(stderr,"setmat %d %9g %9g\n",n,quat[n][0],ax3[n][0] );
/* 
     initialise diagonal matrix -  
*/
   for (  j = 0 ; j < 3 ; ++ j )
   {
      for (  k = 0 ; k < 3 ; ++ k )
      {
         el[j][k] = nought ;
      }
      if ( ax3[n][j]*ax3[n][j]  ==  nought ) goto snag ;
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
         "ERROR: visig in setmat  ax3[%d][%d] = 0\n",n,j );
   ok = FALSE ;
rtrn:;
} /* setmat */
/**********************************************/

rotget(r,unr,n)
   int n ;
   double r[3][3],unr[3][3] ;
/* 
     form a rotation matrix r and its inverse unr 
     from the nth entries in quat 

     called by setmat 
*/
{
   int i,j ;
   double cp,sp,x,y,z,m,xsp,ysp,zsp,xm,ym,zm,xym,xzm,yzm ;

   if (debug <= 0)
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

   for (  i = 0 ; i < 3 ; ++ i )
   {
      for (  j = 0 ; j < 3 ; ++ j )
      {
         unr[i][j] = r[j][i] ;
      }
   }

   if (debug <= 0)
   {
      fprintf(stderr,"rotgetb  %9g %9g %9g\n",
         r[0][0],r[0][1],r[0][2]);
      fprintf(stderr,"         %9g %9g %9g\n",
         r[1][0],r[1][1],r[1][2]);
      fprintf(stderr,"         %9g %9g %9g\n",
         r[2][0],r[2][1],r[2][2]);
   }
} /* rotget */
/**********************************************/

matmul(a,b,ans)
   double a[3][3],b[3][3],ans[3][3] ;
/* 
     this multiplies matrix "b" by "a" 
     and puts the product in "ans". 
     it is done via an intermediate matrix "c" to allow matmul 
     to be used with the same matrix for "a", "b", and/or "ans". 

     called by setmat 
*/
{
   int i,j,k ;
   double x,c[3][3] ;

   for (  i = 0 ; i < 3 ; ++ i )
   {
      for (  j = 0 ; j < 3 ; ++ j )
      {
         x = nought ;
         for (  k = 0 ; k < 3 ; ++ k )
         {
            x = x+a[i][k]*b[k][j] ;
         }
         c[i][j] = x ;
      }
   }
   for (  i = 0 ; i < 3 ; ++ i )
   {
      for (  j = 0 ; j < 3 ; ++ j )
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

     coef(1)*x**2 + coef[2]*y**2 + coef[3]*x*y 
         + coef(4)*x + coef[5]*y + coef[6] = 0 

     called by setnup
*/
{
   double den ;

   if (debug <= 0)
      fprintf(stderr,"setcof %9g\n", el[1][1]);
   if (el[2][2] == nought) goto lab1 ;
   den = doub1/el[2][2] ;
   coef[0] = el[0][0] - el[0][2]*el[0][2]*den ;
   coef[1] = el[1][1] - el[1][2]*el[1][2]*den ;
   coef[2] = 2.0*(el[0][1] - el[0][2]*el[1][2]*den) ;
   coef[3] = nought ;
   coef[4] = nought ;
   coef[5] =  -doub1 ;
   goto rtrn ;
/* 
     snags -  
*/
lab1:  fprintf(stderr,
      "ERROR: visig in setcof\n %9g %9g %9g\n",
      el[0][0],el[0][1],el[0][2]);
   ok = FALSE ;
rtrn:;
} /* setcof */
/************************************************/

setaxe(axe,coef)
   double axe[2],coef[6];
/* 
     find semiminor axis, axe[0], and semimajor axis, axe[1],
     of ellipse described by coef. 

     called by setnup 
*/
{
   double axx,axy;
   double discrt,lamx,lamy,c01,rtdis ;

   lamx = 1 ;
   lamy = 1 ;
   if (debug <= 0)
      fprintf(stderr,"setaxea %9g\n", coef[0]);
   discrt = (coef[0] - coef[1])*(coef[0] - coef[1]) + coef[2]*coef[2];
   if (discrt < nought) goto snag ;
   c01 = inv2*(coef[0] + coef[1]) ;
   rtdis = inv2*sqrt(discrt) ;
   lamx = c01 + rtdis ;
   lamy = c01 - rtdis ;
   if (lamx <= nought) goto snag ;
   if (lamy <= nought) goto snag ;
   axe[0] = doub1/sqrt(lamx) ;
   axe[1] = doub1/sqrt(lamy) ;
   goto rtrn ;
/* 
     snags -  
*/
snag: fprintf(stderr,"ERROR: visig setaxe %9g %9g %9g %d\n",
         lamx,lamy,discrt,n);
   ok = FALSE ;
rtrn:if (debug <= 0) fprintf(stderr,"setaxeb %9g %9g\n",axe[0],axe[1]);
} /* setaxe */
/******************************************/

setpro(coef)
   double coef[6];
/* 
     for the outline of nth ellipsoid, find -  
     angle between axx axis and scene x axis, phi, 

     called by setnup 
*/
{
   double x,y;

   x = coef[2];
   y = coef[0]-coef[1];
   if ((x == nought) && (y == nought)) phi = nought;
      else
         phi = inv2*atan2(x,y) ;
   if (phi < nought) phi = phi+pi+pi ;
} /* setpro */
/******************************************/

store2()
/* 
   store on file the values -  
     (1) coords of centre of ellipse, 
     (2) lengths of semi - axes, 
     (3) angle of semi - minor axis to coordinate x axis, 
     (4) number of hidden arcs (0). 

     called by drawel 
*/
{
   int ixc,iyc,iaxx,iaxy,iphi,arctop ;

   ixc = cen[n][0] ;
   iyc = cen[n][1] ;
   iaxx = axxn ;
   iaxy = axyn ;
   iphi = phi*deg10 ;
   if (iaxx <= 0) iaxx = 1 ;
   if (iaxy <= 0) iaxy = 1 ;
   if (iphi < 0) iphi = iphi+3600 ;
   arctop = 0 ;
   printf("%d %d %d %d %d %d\n",
      ixc,iyc,iaxx,iaxy,iphi,arctop );
} /* store2 */
