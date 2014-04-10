/*     hideo

   modified -  
     25 Jun 1996  fix textured ellipsoid problem
      7 Feb 1996  improved quartic routines
      5 Dec 1994  fixed bug in "chkrts"
      1 Jul 1994  use best quartic roots
     18 Aug 1993  accommodate joints
     23 Jul 1993  index arrays from 0
     25 Jun 1993  simplify cos(acos(x)/3)
     26 May 1993  simplify cube root
      3 Jun 1992  fix debugs
     22 May 1992  fix curoot
     27 Mar 1989  clean up chkrts
     10 Feb 1989  choose Ferrari or Neumark.
     30 Jan 1989  cubic and quartic algorithms improved
     18 Sep 1987  translated into C
    19 Jan  1987  ignore ellipsoids in front of z = 0 
     31 Jul 1986  cope with identical ellipsoids 
     22 Feb 1986  cubic stabilised more 
      1 Jan 1986  a and b intersection logic improved  (peter Gummer)
     30 Sep 1985  four0a and four0b separated 
     15 Jul 1985  windowing stabilised 
     14 Jul 1985  new quartic algorithm 
     10 Jul 1985  improved  output of semiaxes,phi 
     25 Nov 1983  angles give rotation about axis 
     17 Aug 1983  allow for intersection value errors 
     28 Sep 1982  restrict appear array to 20 
     18 Aug 1982  refer equns to centre of nth ellpsd 
     15 Jan 1982  use tan half Cohens parameter
     23 Dec 1981  hidden arc calcs include topology 
     15 Dec 1981  cubic and quartic stabilised 
     16 Jul 1981  table look-up for sine and cosine  (Chris Berry)
      1 Jun 1981  table look-up for cube roots  (Charles Prineas)
     26 May 1981  reduce number of divisions 
     24 May 1981  non-intersections saved in hash table 
     15 May 1981  new quartic and cubic algorithms  (Charles Prineas)
     30 Nov 1977  include windowing 
     26 May 1977  precalculate intersections 
     10 May 1976  to separate translation/drawing 

     copyright (c)  Don Herbison-Evans  1972 

     This program takes 3d specifications of ellipsoids in a 
     series of frames of a movie, and projects them into 2d, 
     giving specifications of the ellipsoid outline ellipses, 
     and their hidden arcs. 

     The projections of the ellipsoids are ellipses which are 
     drawn with Cohen's parametric algorithm using 2x2 matrix 
     updating ( Proc. Comp. Graphics 70, Brunel Uni.). 

     The intersections of the outline of each ellipsoid with 
     the outlines of the other ellipsoids are calculated, and 
     the hidden arcs kept as a list for use in finally drawing 
     that outline. 

     The centre to centre separation of any two ellipsoids is 
     used as an initial filter to avoid intersection calcula -  
     tions where intersection is clearly impossible. 

     The outlines are clipped against 2 infinite ellipses 
     constituting a square window. 

     The picture is 1000 units wide. 

   input  -  

     Data about each frame in sequence. Each frame is headed
     by a line containing the number of ellipsoids in that frame
     and then the frame number. This line is followed by
     lines of numeric data containing the 3d coordinates of 
     the centres, 3 semiaxis lengths and the 3 quaternian angles 
     of the ellipsoids in the frame.
     The rest of each line is ignored. 

   output  -  

     The 2d coordinates of the centres, the two semi - axis 
     lengths, the orientation of the semi - minor axis, the 
     number of hidden arcs, and pairs of parameter values 
     bounding these hidden arcs for each ellipse outline of 
     each picture are written to the output file. 

     error messages are written to file 'stderr'. 

  ******************************************** 

   subroutines -

     main   - run through frames of animation
     setcns - set up constants pi, etc. 
     input  - read ellipsoid debugrmation about a frame from a file 
     mkquat - convert angles to quat array entries 
     setwdw - set up viewing window parameters 
     drawel - test each ellipse outline against all the others 
     setnup - set up parameters of "n"th ellipse 
     chkwdw - check "n"th ellipse against window 
     chkell - check "n"th ellipse against "j"th ellipse 
     copcof - make a copy of a set of ellipsoid coefficients 
     minmax - store the max and min ellipsoid semiaxes 
     prinel - print out the parameters of the ellipsoids 
     setmat - find matrix representing an ellipsoid 
     rotget - form a rotation matrix and its inverse 
     matmul - multiply two matrices together 
     setcof - find ellipsoid coefficients from matrix form 
     setpln - find coefficients of outline plane 
     setax2 - find semiaxes of an ellipse 
     setphi - find orientation and Cohen matrix of ellipse 
     shfcof - find coefficients of shifted ellipse 
     rotcof - find coefficients of rotated ellipse 
     ellpln - find coefficients of cut ellipsoid ellipse 
     ellcut - find intersections of 2 ellipses 
     order  - find hidden arcs 
     two0a  - find hidden arcs when 2 of 'a' type and 0 of 'b' 
              type of intersection 
     two0b  - find hidden arcs when 2 of 'b' type and 0 of 'a' 
              type of intersection 
     four0a - find hidden arcs when 4 of 'a' type and 0 of 'b' 
              type of intersection 
     four0b - find hidden arcs when 4 of 'b' type and 0 of 'a' 
              type of intersection 
     both   - find hidden arcs when a and b type intersections 
     chkrts - check topology of a and b type intersections 
     allarc - find hidden arcs when a - b topology wrong 
     obscur - check point on "n"th outline against "j"th ellipsoid 
     insert - put a hidden arc in a list of hidden arcs 
     sort   - sort two arrays  into ascending order 
     store2 - write ellipse debugrmation to a file 
     best   - select best quartic roots
     acos3  - find cos(arccos(x)/3) by table lookup 
     curoot - find cube root
     errors - find errors of quartic roots.
     quadratic - solve a quadratic equation 
     cubic  - solve special cubic equation 
     descartes-solve quartic using Descartes' algorithm
     ferrari- solve quartic using Ferrari's algorithm
     neumark- solve quartic equation using Neumark's algorithm

*****************************************************/ 

#include <stdio.h>
#include <values.h>

#define AMAX  4096    /* max number of hidden arcs */
#define BMAX   256    /* size of input buffer */
#define EMAX  1024    /* max number of ellipsoids */
#define TRUE     1
#define FALSE    0

double sqrt(),atan(),atan2(),fabs();
double acos(),cos(),sin(),exp(),log();

double aerr[4];       /* errors on atheta  */
double appear[AMAX][2];/* values of Cohens parameter at 
                              dis-  and re- appearance respectively
                              of invisible arc of current
                              ellipsoid outline */ 
double atheta[4];     /*  parameter values on "n"th outline where it 
                          is intersected by "j"th*/
double axxn;          /* semiminor axis of "n"th ellipsoid outline */
double axyn;          /* semimajor axis of "n"th ellipsoid outline */
double ax3[EMAX][3];  /* semiaxis lengths of ellipsoids */
double berr[4];       /* errors on btheta */
double btheta[4];     /* parameter values on "n"th outline where it 
                         is intersected by ellipse of intersection
                         of "j"th ellipsoid and plane of outline of
                         the "n"th */ 
double cen[EMAX][3];  /* centres of ellipsoids */
double cow0[6];       /* coefficients of infinite ellipse with
                         x = 0,1000 */ 
double cow1[6];       /* coefficients of infinite ellipse with
                         y = 0,1000 */ 
double coj[6];        /* coeffs of outline ellipse of "j"th
                         ellipsoid about centre and axes of "n"th
                         ellipse outline */ 
double con[6];        /* coeffs of elliptical outline of "n"th
                         ellipsoid about its own centre in form -  
                           con[1]*x*x + con[2]*y*y + con[3]*x*y 
                           + con[4]*x + con[5]*y + con[6] = 0 */
double cj[3];         /* coeffs of plane of outline of "j"th
                         ellipsoid about centre of "n"th */ 
double cn[3];         /* coeffs of plane of outline of "n"th
                         ellipsoid about own centre, in form -  
                          cn[0]*x + cn[1]*y + cn[2] + z = 0 */
double doub0;
double doub1,doub2;   /* double versions of integers */
double doub3,doub4;
double doub6,doub12;
double doub24;
double doubmax;       /* approx square root of max double number */
double doubmin;       /* smallest double number */
double doubtol;       /* tolerance of double numbers */
double ellj[3][3];    /* matrix of "j"th ellipsoid */
double elln[3][3];    /* matrix of "n"th ellipsoid */ 
double ellj22;        /* normalizing coeff for polynomial of "j"th
                         outline */ 
double inv2,inv3,inv4;/* inverses of integers */
double inv10;
double jnt[EMAX][3];  /* coordinates of joints */
double maxax[EMAX];   /* largest  semiaxis of ellipsoids */
double minax[EMAX];   /* smallest semiaxis of ellipsoids */ 
double mcn[5] ;       /* coeffs of sin(theta) in Cohen's matrix
                         for outline of "n"th ellipsoid */ 
double maxval;        /* tangent of half minimum stored angle
                         increment */ 
double phi,cphi,sphi; /* angle of orientation of major axis of 
                         "n"th ellipsoid outline to 'x' axis */ 
double pi,piby4,twopi;/*  3.14 etc.  */
double rcoj[6];
double rt3;           /* square root of 3 */
double quat[EMAX][5]; /* quaternions of ellipsoids */ 
double rad10;         /* conversion factor from tenths of a
                        degree to radians */
double rterr[4];
double sqsep;         /* square of separation of centres of
                        ellipsoids j and n */ 
double sqmax;         /* square of maximum separation of centres
                        of ellipsoids n and j that will still
                        allow them to overlap */ 
double theta[4];      /* starts and ends of possible hidden arcs */
double tstval;
double wmax[2];       /* maximum coordinates of window */ 
double wmin[2];       /* minimum coordinates of window */ 
double wndwcn[2];     /* coordinates of window centre */ 
double xstrt[2];      /* initial point on outline of "n"th ellipsoid 
                         relative to its own centre */
double xm[2];         /* partial projections of xstrt by mc */ 


char buf[BMAX];       /* input buffer */

int debug;            /* zero to get debugging debugrmation */
int f;                /* counter through frames */ 
int flag = 1;         /* negative if joint debugrmation in file */
int frame;            /* holds original frame numbers */ 
int hash[EMAX][EMAX]; /* zero when outlines "n" and "j" have no intersection */ 
int hidden;           /* true if point on "n"th outline hidden
                         by "j"th ellipsoid */
int inside;           /* true if point on "n"th outline is inside
                         "j"th ellipsoid */
int j;                /* ellipsoid whose outline may intersect
                         that of "n"th */
int n;                /* ellipsoid about to be drawn */ 
int nels ;            /* number of ellipsoids */
int njts;             /* number of joints */
int nrtsa;            /* number of intersection points of 
                         outlines of ellipsoids "n" and 'j' */
int nrtsb;            /* number of intersections of outline of
                         ellipsoid "n" with projection of ellipse
                         of intersection of "j"th ellipsoid with plane
                         of outline of "n"th ellipsoid */ 
int narcs;            /* number of visible arcs in outline of
                         "n"th ellipsoid */ 
int ok;               /* false if snag encountered */ 
int outsid;           /* true if ellipsoid totally outside */
int valid ;           /* true if order of 'a' and 'b' type
                         intersections is valid */

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

   int b[5][5][6] = {{
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

/************************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
     calls  setcns, input, setwdw, minmax, drawel 
*/
{
   setcns();
   for (  f = 1 ; nels > 0 ; ++ f )
   {
      input() ;
      if ( (ok == TRUE) && (f == 1) ) setwdw() ;
      if (ok == TRUE) minmax() ;
      if (ok == TRUE) drawel();
      if (ok == FALSE) goto lab1;
   }
lab1:
   printf("0 0\n");
   exit(0);
} /* main */
/**********************************************/

setcns()
/* 
     set up constants 

     called by main 
*/
{
      int j,k;

      debug = 2;
      for ( j = 0 ; j < EMAX ; ++ j )
         for ( k = 0 ; k < EMAX ; ++ k )
            hash[j][k] = -1 ;
      nels = 1;
      ok = TRUE ;
      doub0 = (double)0;
      doub1 = (double)1;
      doub2 = (double)2;
      doub3 = (double)3;
      doub4 = (double)4;
      doub6 = (double)6;
      doub12 = (double)12;
      doub24 = (double)24;
      inv2 = doub1/(double)2;
      inv3 = doub1/(double)3;
      inv4 = doub1/(double)4;
      inv10 = doub1/(double)10;
      maxval = (double)10000;
      piby4 = atan(doub1) ;
      pi = doub4*piby4;
      twopi = pi+pi;
      rad10 = pi/(double)1800;
      rt3 = sqrt(doub3) ;

      doubtol = doub1;
      for (  j = 1 ; doub1+doubtol > doub1 ; ++ j )
      {
          doubtol *= inv2;
      }
      doubtol = sqrt(doubtol);

      doubmin = inv2 ;
      for (  j = 1 ; j <= 100 ; ++ j )
      {
          doubmin=doubmin*doubmin ;
          if (debug < 0)
             fprintf(stderr,"doubmin %d %9g\n",j,doubmin);
          if ((doubmin*doubmin) <= (doubmin*doubmin*inv2))
              break;
      }
      doubmax=0.7/sqrt(doubmin) ;

} /* setcns */
/****************************************************/

input()
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
    
     called by main 
     calls  mkquat 
*/
{
   double dang1,dang2,dang3;
   int axx,axy,axz,cenx,ceny,cenz,ang1,ang2,ang3;
   int jntx,jnty,jntz;
   int col1,col2,col3;
   int k ;
   int vx,vy,vz,a1,a2,a3;
   char name[BMAX];
   char nn[BMAX];

   if (flag > 0)
      scanf("%d %d %d %d %d %d %d %d\n",
         &nels,&frame,&vx,&vy,&vz,&a1,&a2,&a3);
   else
   {
      nels = flag;
      frame = njts;
   }
   if (f == 1) 
   {
      debug = frame ;
      if (debug < 0)
         fprintf(stderr,"prog -  hideo  debug = %d\n", debug );
   }
   if (debug < 0)
      fprintf(stderr,"inputa %d %d %d\n",f,nels,frame );
   if (nels <= 0)
      ok = FALSE;
   else
   if (nels > EMAX)
   {
      fprintf(stderr,"\nERROR in hideo : frame %d\n",frame);
      fprintf(stderr,"number of ellipsoids %d\n max number %d\n",
         nels,EMAX);
      ok = FALSE;
   }
   else
   {
/* 
     read ellipsoids in current frame -  
*/
      for ( k = 0 ; k < nels ; ++ k )
      {
         if (doub0 ==
         scanf("%d %d %d %d %d %d %d %d %d %d %d %d %s %s",
            &axx,&axy,&axz,&cenx,&ceny,&cenz,&ang1,&ang2,&ang3,
            &col1,&col2,&col3,name,nn) )
         {
            fprintf(stderr,"\nERROR in hideo: possible end of file\n");
            fprintf(stderr,"reading %s ellipsoid %d in frame %d\n",
                name,k,frame);
            exit(1);
         }
         if (debug < 0)
            fprintf(stderr,"inputb %d %d %d %d %d %d %d %d %d %d\n",
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
         dang1 = rad10*ang1 ;
         dang2 = rad10*ang2 ;
         dang3 = rad10*ang3 ;
         if (debug < 0)
            fprintf(stderr,"inputc %9g %9g %9g %9g %9g %9g %9g %9g %9g %9g\n",
            rad10,ax3[k][0],ax3[k][1],ax3[k][2],
            cen[k][0],cen[k][1],cen[k][2],
            dang1,dang2,dang3);
         mkquat(k,dang1,dang2,dang3) ;
      }
/*
     read joints -
*/
      scanf("%d %d\n",&flag,&njts);
      if (debug < 0)
         fprintf(stderr,"inputd %d %d\n",flag,njts);
      if (flag < 0)
      {
         flag = 1;
         for ( k = 0 ; k < njts ; ++ k )
         {
            if (NULL == gets(buf))
            {
               fprintf(stderr,"unexpected end of file\n");
               fprintf(stderr,"reading joint %d in frame %d\n",
                   k,frame);
               exit(1);
            }
         }
      }
   }
} /* input */
/**********************************************/
 
mkquat(n,a1,a2,a3)
   int n ;
   double a1,a2,a3 ;
/* 
     convert angles a1,a2,a3 into quat entries 

     called by input 
*/
{
   double s1,c1,s2,c2,s3,c3 ;

   if (debug < 0)
      fprintf(stderr,"mkquat  %d %9g %9g %9g\n", n,a1,a2,a3 );
   s1 = sin(a1) ;
   c1 = cos(a1) ;
   s2 = sin(a2) ;
   c2 = cos(a2) ;
   s3 = sin(a3) ;
   c3 = cos(a3) ;
   quat[n][0] = c1*c2 ;
   quat[n][1] = s1*c2 ;
   quat[n][2] = s2 ;
   quat[n][3] = s3 ;
   quat[n][4] = c3 ;
} /* mkquat */
/**********************************************/

setwdw()
/* 
     set up viewing window ellipse parameters. 

     called by main 
*/
{
   int j ;
   double minx,miny,maxx,maxy ;

   minx = 2.5 ;
   miny = 2.5 ;
   maxx = 998.5 ;
   maxy = 998.5 ;
   wmin[0] = minx ;
   wmin[1] = miny ;
   wmax[0] = maxx ;
   wmax[1] = maxy ;
   wndwcn[0] = (maxx+minx)*inv2 ;
   wndwcn[1] = (maxy+miny)*inv2 ;
   for (  j = 0 ; j < 6 ; ++ j )
   {
      cow0[j] = 0 ;
      cow1[j] = 0 ;
   }
   cow0[0] = 1 ;
   cow1[1] = 1 ;
   cow0[3] =  - maxx - minx ;
   cow1[4] =  - maxy - miny ;
   cow0[5] = maxx*minx ;
   cow1[5] = maxy*miny ;
   if (debug < 0)
      fprintf(stderr,"setwdw %9g %9g %9g %9g %9g %9g %9g\n",
          wmin[0],wmin[1],wmax[0],wmax[1],wndwcn[0],wndwcn[1]);
} /* setwdw */
/**********************************************/

drawel()
/* 
     This draws the outline of each ellipsoid in turn. 
     Each is approximated by a series of chords, 
     plotted with respect to Cohen's parameter. 
     Before plotting an ellipse, the intersection points 
     of all other ellipses are calculated in terms of the 
     plotting parameter, and these are ordered and the 
     hidden arcs calculated. 
     On plotting, the hidden arcs are skipped. 

     called by main 
     calls  (prinel), setnup, chkwdw, chkell, setpln, obscur, 
         order, store2 
*/
{
   int k;

   if (debug < 0)
      fprintf(stderr,"drawela %d\n", nels );
/* 
     write start of new picture -  
*/
    printf(" %5d %5d\n", nels,frame );
    if (debug < 0) prinel() ;
/* 
     run thru ellipsoids to draw each in turn -  
*/
    for ( n = 0 ; n < nels ; ++ n )
    {
         if (debug < 0) fprintf(stderr,"drawelb %d %9g %9g %9g\n",
            n,cen[n][0],cen[n][1],cen[n][2]);
         j = 0 ;
         if ((cen[n][2]+maxax[n])  <  doub0) goto allhid ;
         setnup();
         if ( ok == FALSE ) goto snag ;
         if (debug < 0) fprintf(stderr,"drawelc %d %9g %9g %9g\n",
            n,axxn,axyn,phi);
/* 
     check ellipsoid n against windows -  
*/
         chkwdw();
         if ( ok == FALSE ) goto snag ;
         if ( outsid == TRUE ) goto allhid ;
/* 
     run thru other ellipsoids to find obscured arcs of the "n"th -  
*/
         for (  j = 0 ; j < nels ; ++ j )
         {
            if (debug < 0)
               fprintf(stderr,"draweld  %d %d %d %9g %9g\n",
                  nels,j,n,cen[n][0],cn[0]);
            if (j == n) goto endj ;
            if ((cen[j][2]+maxax[j]) < doub0) goto endj ;
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
diff:      if ((cen[n][2]+maxax[n]) < (cen[j][2]-maxax[j]))
              goto endj ;
           sqsep = (cen[n][0]-cen[j][0])*(cen[n][0]-cen[j][0])
                 + (cen[n][1]-cen[j][1])*(cen[n][1]-cen[j][1]) ;
           sqmax = (axyn + maxax[j])*(axyn + maxax[j]) ;
           if (debug < 0)
             fprintf(stderr,"drawele %d %d %9g %9g %9g %9g %9g %9g\n",
                n,j,cen[n][0],cen[j][0],
                axyn,maxax[j],sqsep,sqmax );
           if (sqsep > sqmax)
           {
              hash[n][j] = 0 ;
              hash[j][n] = 0 ;
              goto endj ;
           }
           chkell();
           if ( ok == FALSE ) goto snag ;
           setpln(cj,j,n,ellj);
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
              order();
              if ( ok == FALSE ) goto snag ;
              if (appear[1][1] >= maxval) goto done ;
           }
endj: ;
      } /* end j loop */
      goto done ;
/* 
     ellipsoid is completely hidden -  
*/
allhid: appear[1][0] = -maxval ;
      appear[1][1] =  maxval ;
      narcs = 1 ;
/* 
     send this ellipse to the output device -  
*/
done: store2() ;
      if ( ok == FALSE ) goto snag ;
    } /* end n loop */

   goto rtrn ;
/* 
     snags -  
*/
snag: fprintf(stderr,"hideo snag in drawel %d %d %d %d\n",
         f,frame,n,j); 
rtrn: ;
} /* drawel */
/******************************************/

setnup()
/* 
     set up parameters of "n"th ellipsoid relative to own centre. 

     called by drawel 
     calls  setmat, setcof, setpln, setax2, setphi 
*/
{
   double axes[2];

   if (debug < 0)
      fprintf(stderr,"setnupa %d\n", n );
   narcs = 2 ;
   appear[1][0] =  -maxval ;
   appear[1][1] =  -maxval ;
   appear[2][0] = maxval ;
   appear[2][1] = maxval ;
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
   setphi(axes,con,mcn) ;
   if ( ok == FALSE ) goto snag ;
   xstrt[0] = axxn*cphi ;
   xstrt[1] = axxn*sphi ;
   xm[0] = xstrt[0]*mcn[1]+xstrt[1]*mcn[2] ;
   xm[1] = xstrt[0]*mcn[3]+xstrt[1]*mcn[4] ;
   goto rtrn ;
/* 
     snag -  
*/
snag: ok = FALSE;
   fprintf(stderr,
      "prog hideo   subr setnup  snag in ellipsoid   %d %9g\n",
          n,elln );

rtrn:
   if (debug < 0)
      fprintf(stderr,"setnupb %9g %9g %9g %9g %9g %9g\n",
         axxn,axyn,xstrt[0],xstrt[1],xm[0],xm[1] );
} /* setnup */
/******************************************/

chkwdw()
/* 
     check ellipsoid n against viewing window ellipse -  

     called by drawel 
     calls  copcof, shfcof, rotcof, ellcut, order 
*/
{
   int ellcut();
   int k,w;

   if (debug < 0)
      fprintf(stderr,"chkwdwa  %d %9g %9g %9g\n", n,axxn,axyn,sphi );
   outsid = FALSE ;
/* 
     is ellipsoid entirely outside window - 
*/
   for (  w = 0 ; w < 2 ; ++ w )
   {
      if (wmin[w] > cen[n][w] + axyn) goto lab7 ;
      if (wmax[w] < cen[n][w] - axyn) goto lab7 ;
   }
/* 
     is ellipsoid entirely within window - 
*/
   if ((wmin[0] < cen[n][0] - axyn) && (wmax[0] > cen[n][0]+axyn)
    && (wmin[1] < cen[n][1] - axyn) && (wmax[1] > cen[n][1]+axyn))
      goto lab4 ;
/* 
     seek intersection of ellipsoid with windows - 
*/
   cj[0] = doub0 ;
   cj[1] = doub0 ;
   cj[2] = doub2*(maxax[n]+cen[n][2]) ;
/* 
     run thru window frames -  
*/
   for ( w = 0 ; w < 2 ; ++ w )
   {
      nrtsa = 0 ;
      if (w == 0) copcof(cow0,coj) ;
      if (w == 1) copcof(cow1,coj) ;
      shfcof(coj,cen[n][0],cen[n][1]) ;
      copcof(coj,rcoj) ;
      rotcof(rcoj,cphi, -sphi) ;
      nrtsa = ellcut(axxn,axyn,rcoj,atheta,aerr) ;
      if ((nrtsa == 0)
         && ((wmin[w] > cen[n][w]) || ( wmax[w] < cen[n][w])))
            outsid = TRUE;
      if (nrtsa <= 0) goto lab8 ;
      nrtsb = 0;
      for (k = 0; k < 4; k++)
      {
         btheta[k] = doub0;
         berr[k] =doub0;
      }
      ellj22 = -doub1;
      order();
      if ( ok == FALSE ) goto lab1 ;
lab8: ;
   }

lab4: ;
   if (debug < 0)
      fprintf(stderr,"chkwdwb  %d %9g %9g\n", outsid,wmin[1],wmax[1]);
   goto rtrn ;

lab7: outsid = TRUE ;
   goto lab4 ;
/* 
     snag -  
*/
lab1: fprintf(stderr,
      "\nERROR hideo : chkwdw - window  %d,  ellipsoid  %d\n",w,n );
rtrn:;
} /* chkwdw */
/****************************************/
 
chkell()
/* 
     checks whether ellipsoid n outline is obscured by 
     ellipsoid j. 

     find coj - coeffs of "j"th ellipsoid outline shifted,
     and rcoj - rotated wrt axes of "n"th outline. 

     called by drawel 
     calls  setmat, setcof, shfcof, copcof, rotcof, ellcut, ellpln 
*/
{
   double cop[6],sqmin,absj,absp,scale ;
   int flag ;
   int ellcut();

   flag = 0 ;
   nrtsa = 0 ;
   nrtsb = 0 ;
   if (debug < 0)
      fprintf(stderr,"chkella %9g %9g %9g %d %d %d\n",
         cn[0],axxn,axyn,n,j,hash[j][n]);
   setmat(j,ellj) ;
   ellj22 = ellj[2][2];
   if (debug < 0)
      fprintf(stderr,"chkellb  %9g %9g\n", ellj[0][0],quat[n][0]);
   if ( ok == FALSE ) goto snag ;
   flag = 1 ;
   setcof(coj,ellj) ;
   if (  ok == FALSE ) goto snag ;
   shfcof(coj,cen[n][0]-cen[j][0],cen[n][1]-cen[j][1]) ;
   copcof(coj,rcoj) ;
   rotcof(rcoj,cphi, -sphi) ;
/* 
     have outlines been found before not to intersect -  
*/
   if (hash[n][j] != 0)
   {
/* 
     if ellipse "j" does not surround "n"th ellipse, 
     find intersections using shifted and rotated coefficients -  
*/
      sqmin = (minax[j] - axyn)*(minax[j] - axyn) ;
      if (debug < 0)
         fprintf(stderr,"chkellc  %9g %9g %9g %9g\n",
             sqmin,minax[j],axyn,sqsep );
      if ((sqmin < sqsep) || (minax[j] < axyn))
         nrtsa = ellcut(axxn,axyn,rcoj,atheta,aerr) ;
      if (debug < 0) fprintf(stderr,"chkelld nrtsa %d\n",nrtsa);
      if (nrtsa == 0)
      {
         hash[n][j] = 0 ;
         hash[j][n] = 0 ;
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
      absj = inv2*fabs(rcoj[0]+rcoj[1]) + fabs(rcoj[0]-rcoj[1])+fabs(rcoj[2]);
      absp = inv2*fabs(cop[0]+cop[1]) + fabs(cop[0]-cop[1])+fabs(cop[2]) ;
      if (debug < 0)
         fprintf(stderr,"chkelle  %9g %9g\n", absj,absp );
      if (absj > absp)
      {
         scale = 1.01*absj/absp ;
         cop[0] = scale*cop[0] ;
         cop[1] = scale*cop[1] ;
         cop[2] = scale*cop[2] ;
      }
      nrtsb = ellcut(axxn,axyn,cop,btheta,berr) ;
   }
   goto rtrn ;
/* 
     snag -  
*/
snag: fprintf(stderr,"\nERROR hideo chkell - ellipsoid %d, %d %d\n",
     j,flag,ok );

rtrn:;
} /* chkell */
/******************************************/

copcof(old,new)
   double old[6],new[6] ;
/* 
     make a copy of the 6 element array old into new. 

     called by chkwdw, chkell 
*/
{
   int j ;

   if (debug < 0)
      fprintf(stderr,"copcof %9g\n", old[0] );

   for (  j = 0 ; j < 6 ; ++ j )
   {
      new[j] = old[j] ;
   }
} /* copcof */
/******************************************/

minmax()
/* 
     find maximum semiaxis of each ellipsoid. 

     called by main 
*/
{
   int j,k ;

   for ( j = 0 ; j < nels ; ++ j )
   {
      maxax[j] = ax3[j][0] ;
      minax[j] = ax3[j][0] ;

      for ( k = 1 ; k < 3 ; ++ k )
      {
         if (ax3[j][k] > maxax[j]) maxax[j] = ax3[j][k] ;
         if (ax3[j][k] < minax[j]) minax[j] = ax3[j][k] ;
      }
      if (debug < 0)
         fprintf(stderr,"minmax %d %9g %9g\n",j,minax[j],maxax[j] );
   }
} /* minmax */
/************************************************/

prinel()
/* 
     this lists the axis lengths, positions and quaterions of 
     all the ellipsoids. 

     called by drawel 
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
     ellipsoid by taking the diagonal matrix of inverse square semiaxes, 
     and doing on it a similarity transform for its own rotation. 

     called by setnup, chkell 
     calls  rotget, matmul 
*/
{
   int j,k ;
   double r[4][4],unr[4][4] ;

   if (debug < 0)
      fprintf(stderr,"setmata %d %9g %9g\n",n,quat[n][0],ax3[n][0] );
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
          "\nERROR hideo: subr setmat ax3[%d][%d] = 0\n",n,j);
   ok = FALSE ;

rtrn: if (debug < 0)
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

     called by setnup, chkell 
*/
{
   double den ;

   if (debug < 0)
      fprintf(stderr,"setcofa %9g\n", el[0][0]);
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
         "\nERROR hideo : matrix error in subr setcof\n %9g %9g %9g\n",
         el[0][0],el[0][1],el[0][2]);
      ok = FALSE ;
   }
   if (debug < 0)
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

     called by setnup, drawel 
*/
{
   double cc,cx,cy;
   double el22,den ;

   if (debug < 0)
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
      if (debug < 0)
         fprintf(stderr,"setplnb %9g %9g %9g\n",cx,cy,cc);
   }
   else
   {
      ok = FALSE ;
      fprintf(stderr,"\nERROR hideo setpln -  el no   %d\n",
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
   double axx,axy;
   double discrt,lamx,lamy,c12,rtdis ;

   lamx = 1 ;
   lamy = 1 ;
   if (debug < 0)
      fprintf(stderr,"setax2a %9g\n", coef[0]);
   discrt = (coef[0] - coef[1])*(coef[0] - coef[1])+ coef[2]*coef[2];
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
snag: fprintf(stderr,"hideo   subr setax2 snag %9g %9g %9g %d\n",
         lamx,lamy,discrt,n);
   ok = FALSE ;
rtrn:if (debug < 0) fprintf(stderr,"setax2b %9g %9g\n",axes[0],axes[1]);
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

   if (debug < 0)
      fprintf(stderr,"setphia %9g %9g\n", axes[0],axes[1] );
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
      mc[3] = -spsq*ec - cpsq*invec ;
      mc[4] = -mc[1] ;
      if (debug < 0)
         fprintf(stderr,"setphib %9g %9g %9g %9g %9g %9g %9g %9g\n",
            axxn,axyn,phi,sphi,cphi,ec,x,y);
   }
   else
   {
      fprintf(stderr,"\nERROR hideo : setphi %9g %9g %9g\n",
         axes[0],axes[1],phi );
      ok = FALSE ;
   }
} /* setphi */
/******************************************/

shfcof(coef,x,y)
   double coef[6],x,y ;
/* 
     reset coeffs of ellipse by shifting its origin by (x,y). 

     called by  chkwdw, chkell, ellpln 
*/
{
   double x1,y2,x3 ;

   if (debug < 0)
      fprintf(stderr,"shfcofa %9g %9g \n        %9g %9g %9g %9g %9g %9g\n",
        x,y,coef[0],coef[1],coef[2],coef[3],coef[4],coef[5]);
   x1 = x*coef[0] ;
   y2 = y*coef[1] ;
   x3 = x*coef[2] ;
   coef[5] = coef[5]+x*(x1+coef[3])+y*(y2+coef[4]+x3) ;
   coef[4] = coef[4]+y2+y2+x3 ;
   coef[3] = coef[3]+x1+x1+coef[2]*y ;
   if (debug < 0)
      fprintf(stderr,"shfcofb %9g %9g %9g %9g %9g %9g\n",
        coef[0],coef[1],coef[2],coef[3],coef[4],coef[5]);
} /* shfcof */
/**********************************************/

rotcof(coef,c,s)
   double coef[6],s,c ;
/* 
     reset coeffs of ellipse by rotating about origin by angle phi, 
     where c = cos(phi) and s=sin(phi). 

     called by chkwdw, chkell 
*/
{
   int j ;
   double new[6],sc,ssq,csq,cs2 ;

   if (debug < 0)
      fprintf(stderr,"rotcofa %9g %9g\n",c,s);
   sc = s*c ;
   ssq = s*s ;
   csq = doub1 - ssq ;
   cs2 = coef[2]*sc ;
   new[0] = coef[0]*csq + coef[1]*ssq - cs2 ;
   new[1] = coef[0]*ssq + coef[1]*csq + cs2 ;
   new[2] = (coef[0]-coef[1])*(sc+sc) + coef[2]*(csq-ssq) ;
   new[3] = coef[3]*c - coef[4]*s ;
   new[4] = coef[3]*s + coef[4]*c ;
   new[5] = coef[5] ;

   for (  j = 0 ; j < 6 ; ++ j )
   {
      coef[j] = new[j] ;
   }
   if (debug < 0)
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

   if (debug < 0)
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

int ellcut(axx,axy,coef,theta,rterr)
   double axx,axy,coef[6],theta[4],rterr[4] ;
/* 
     find Cohen parameter values at intersections of the
     ellipse centred on the origin having semiaxes
     lengths "axx,axy" aligned with xy axes 
     with the ellipse whose equation is -  

     coef[0]*x**2 + coef[1]*y**2 + coef[2]*x*y
              + coef[3]*x + coef[4]*y + coef[5] = 0 

     called by chkwdw, chkell 
     calls  quadratic, best, sort. 
*/
{
   int best();

   int nrts ;
   int j ;
   double a,b,c,d;
   double at,bt,ct,dt,et,rts[4];
   double den,x1,xsq1,x4,xy3,y5,ysq2 ;

   if (debug < 0)
      fprintf(stderr,"ellcuta %9g %9g\n        %9g %9g %9g %9g %9g %9g\n",
        axx,axy,coef[0],coef[1],coef[2],coef[3],coef[4],coef[5]);
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
   bt = bt+bt ;
   ct = -xsq1+ysq2+ysq2+coef[5] ;
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
             nrts = quadratic(dt/ct,et/ct,rts,
                       (dt/ct)*(dt/ct)-doub4*(et/ct));
             rterr[0] = doub0; rterr[1] = doub0;
             a = bt; b = ct; c = dt; d = et;
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
      nrts = best(a,b,c,d,rts,rterr) ;
/* 
     find chords intersected -  
*/
      if (nrts > 0)
      {
         for (  j = 0 ; j < nrts ; ++ j )
         {
            theta[j] = rts[j] ;
            if (theta[j] > maxval) theta[j] = maxval ;
            if (theta[j] <  - maxval) theta[j] =  - maxval ;
         }
         sort(theta,rterr,nrts) ;
      }
   }
   if (debug < 0)
      fprintf(stderr,"ellcutb %9g %9g %9g %9g %9g %d\n",
         at,bt,ct,dt,et,nrts );
   return(nrts);
} /* ellcut */
/*************************************************/

order()
/* 
     finds arcs of outline of ellipsoid "n" that are hidden by
     ellipsoid "j", and adds them into array "appear". 

     called by chkwdw, drawel 
     calls  two0a, two0b,, four0a, four0b,, both 
*/
{
   if (debug < 0)
      fprintf(stderr,"ordera %d %d %d %d %d\n",
         j,n,narcs,nrtsa,nrtsb);
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
      fprintf(stderr,"hideo   subr order -  snag %d %d %d %d %9g\n",
         nrtsa,nrtsb,n,j,ellj22 );
      ok = FALSE ;
   }
   else
      if (debug < 0) fprintf(stderr,"orderb %d %d %d %d\n",
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
   if (debug < 0)
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
      insert(val[0],val[1],appear) ;
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
   if (debug < 0)
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
      insert(val[0],val[1],appear) ;
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

   if (debug < 0)
      fprintf(stderr,"four0a  %9g\n", theta[0]);
   val0 = theta[0] - maxval ;
   val1 = theta[3]+maxval ;
   tstval = val0 ;
   if (fabs(tstval) > fabs(val1)) tstval = val1 ;
   obscur(inv2*tstval);
   if ( hidden == TRUE )
   {
      insert( -maxval,theta[0],appear) ;
      if (ok == FALSE) goto rtrn;
      insert(theta[3],maxval,appear) ;
      if (ok == FALSE) goto rtrn;
      obscur(inv2*(theta[1]+theta[2]));
      if (hidden == TRUE) insert(theta[1],theta[2],appear);
   }
   else
   {
      obscur(inv2*(theta[0]+theta[1]));
      if (hidden == TRUE)
      {
         insert(theta[0],theta[1],appear);
         if (ok == FALSE) goto rtrn;
         obscur(inv2*(theta[2]+theta[3]));
         if (hidden == TRUE)
            insert(theta[2],theta[3],appear) ;
            if (ok == FALSE) goto rtrn;
      }
      else
      {
         obscur(inv2*(theta[1]+theta[2]));
         if ( hidden == TRUE )
            insert(theta[1],theta[2],appear) ;
            if (ok == FALSE) goto rtrn;
         else
         {
            obscur(inv2*(theta[2]+theta[3]));
            if ( hidden == TRUE )
               insert(theta[2],theta[3],appear) ;
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

   if (debug < 0)
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
            insert( -maxval,maxval,appear) ;
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
         insert(theta[0],theta[3],appear) ;
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
            insert( -maxval,maxval,appear) ;
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
         insert( -maxval,theta[0],appear) ;
         if (ok == FALSE) goto rtrn;
         val[0] = theta[1] ;
         val[1] = theta[2] ;
         val[2] = theta[3] ;
         val[3] = maxval ;
      }
   }
lab6:  for (  j = 0 ; j < 3 ;  j  +=  2 )
       {
          insert(val[j],val[j+1],appear) ;
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

   if (debug < 0)
      fprintf(stderr,"botha %d %d %d\n",t[27],t[123],t[133]);
   class = -1;
   chkrts();
   if (debug < 0) fprintf(stderr,"bothb %d %d\n",valid,TRUE);
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
   if (debug < 0)
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
         if (k < 10) goto lab5 ;
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
         if (debug < 0) fprintf(stderr,"bothd %d %d %d\n",j,basej,k);
      } /* end j loop */

      if (debug < 0)
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
         if (debug < 0)
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
         if (t[which] != 0) insert(val[also],val[also+1],appear);
         if (ok == FALSE) goto lab18;
lab8: ;
      } /* end lim loop */
      insert(arc[1],arc[2],appear);
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
   if (debug < 0) fprintf(stderr,"chkrtsa %d %d %d\n",nrtsa,nrtsb,nrts);
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
      if (debug < 0)
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
      if (j != 0)
      {
         toterr = doub2*(verr[j-1] + verr[j] + doubtol);
         if ((val[j] - val[j-1]) < toterr) valid = FALSE;
      }
      if (debug < 0)
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

   if(debug < 0)
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
      if ( hidden == TRUE ) insert(val[j],val[j+1],appear) ;
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
     cj - coefficients of plane of "j"th outline wrt centre of "n"th 
     cn - coefficients of plane of "n"th outline wrt its own centre 
     xstrt - coords of start of plot of "n"th outline wrt its centre 
     xm - coefficients of sine of Cohen parameter 
     debug - 0 for lots of diagnostics 
     err - device number for output of diagnostics 
     coj - coeffs of "j"th outline wrt centre of "n"th

   output values -  
     hidden - true if point on "n"th outline hidden by "j"th ellipsoid 
     inside - true if point on "n"th outline is inside "j"th ellipsoid 

     called by two0a, two0b, four0a, four0b, both, drawel, allarc 
*/
{
   double x,y,zn,discrt,zj,st,ct,den,tsq,zell ;
   double norm ;

   if (debug < 0)
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
   if (ellj22 > doub0) discrt =  - discrt ;
   if (debug < 0)
      fprintf(stderr,"obscurb %9g %9g %9g %9g\n", x,y,zn,discrt );
   zj =  - cj[2] - cj[0]*x - cj[1]*y ;
   if (debug < 0)
      fprintf(stderr,"obscurc %9g\n", zj );
/* 
   rather than testing -  
     zn - zj < sqrt(discrt/ellj22) 
   test -  
     ellj22*(zn - zj)*(zn - zj) < discrt 
   but avoid overflow by multiplying in stages as abs(ellj22) < 1 
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

   if (debug < 0)
      fprintf(stderr,"obscurd  %9g %9g %9g %d %d %d\n",
        norm,zell,ellj22,hidden,inside,TRUE);
} /* obscur */
/****************************************/

insert(bot,top,a)
   double a[AMAX][2],bot,top ;
/* 
     inserts an arc "bot" to "top" into list of "narcs" arcs
     in array "a". 

     uses separate sections depending on whether list of
     hidden arcs expands, stays the same length or contracts. 

     D.Herbison - Evans     May 1978               ANSI Fortran 

   input parameters -  
     a - array containing previous list of hidden arcs, in 
         ascending order, i.e. -  
         a[j][0] <= a[j][1] <= a[j+1][0] for 1 <= j <= n - 1 
     bot,top - lower and upper limits of new hidden arc which 
               is to be inserted into array a. 
     narcs - number of hidden arcs stored in array a. 

   output parameters -  
     a - updated ordered list of hidden arcs. 
     narcs - updated number of hidden arcs in array a. 
     ok - set to false if a problem encountered 

   variables -  
     j - counter through updated list. 
     jp1 - index of start of changes to list. 
     k - counter through old list seeking end of changes. 
     l - counter for copying unaltered arcs beyond changes. 
     nml - reverse counter for copying from old list. 
     nmj - reverse counter for copying into new list. 
*/
{
   int j,k,l,jp1,nml,nmj ;
/* 
     initialise variables and look for sillies -  
*/
   if (debug < 0)
      fprintf(stderr,"inserta %d %9g %9g %9g %9g\n",
         narcs,bot,top,a[1][0],a[narcs][1]);
   j = 0 ;
   k = 0 ;
   if (bot == top) goto lab9 ;
   if (bot > top) goto lab10 ;
   if (narcs < 1) goto lab10 ;
   if (bot < a[1][0]) goto lab10 ;
   if (top > a[narcs][1]) goto lab10 ;
/* 
     find out where list alterations start -  
*/
   for (  j = 1 ; j <= narcs ; ++ j )
   {
      if (bot <= a[j][1]) goto lab2 ;
   }
/* 
     error -  
*/
   j = narcs+1 ;
   goto lab10 ;
/* 
     find whether list in a must expand, stay same, or contract -  
*/
lab2: jp1 = j+1 ;
   if (top < a[j][0]) goto lab8 ;
   if (j == narcs) goto lab7 ;
   if (top < a[jp1][0]) goto lab7 ;
/* 
     contract -  bot to top spans one or more complete visible arcs. 
*/
   if (debug < 0) fprintf(stderr,"   contract %d %9g %9g %9g\n",
       j,a[j][0],a[j][1],a[jp1][0]);
   if (a[j][0] > bot)  a[j][0] = bot ;
/* 
     find where the new hidden arc ends -  
*/
   for (  k = jp1 ; k <= narcs ; ++ k )
   {
      if (top < a[k][0]) goto lab5 ;
   }
/* 
     special case -  hit the ceiling -  
*/
   k = narcs+1 ;
   narcs = j ;
/* 
     insert new top -  
*/
lab5: a[j][1] = a[k-1][1] ;
   if (top > a[j][1]) a[j][1] = top;
   if (k > narcs) goto lab9 ;
/* 
     move other entries down -  
*/
   for (  l = k ; l <= narcs ; ++ l )
   {
      j = j+1 ;
      a[j][0] = a[l][0] ;
      a[j][1] = a[l][1] ;
   }

   narcs = j ;
   goto lab9 ;
/* 
     stay same length -  bot to top spans only 1 hidden arc -  
*/
lab7: if (debug < 0) fprintf(stderr,"   same %d %9g %9g\n",
         j,a[j][0],a[j][1]);
   if (a[j][0] > bot) a[j][0] = bot ;
   if (a[j][1] < top) a[j][1] = top ;
   goto lab9 ;
/* 
     expand, so move all up 1 place for insertion at j -  
*/
lab8: if (debug < 0) fprintf(stderr,"   expand %d %9g %9g\n",
           j,a[j][0],a[j][1]);
   if ( (narcs+1) > EMAX) goto lab10 ;
   nmj = narcs - j+1 ;

   for (  l = 1 ; l <= nmj ; ++ l )
   {
      nml = narcs - l+2 ;
      a[nml][0] = a[nml - 1][0] ;
      a[nml][1] = a[nml - 1][1] ;
   }
/* 
     insert new hidden arc -  
*/
   a[j][0] = bot ;
   a[j][1] = top ;
   narcs = narcs+1 ;
   goto lab9;
/* 
   snag -
*/
lab10: ;
   fprintf(stderr,
      "\nERROR in hideo: insert snag  %d %d %d %9g %9g\n",
          j,k,narcs,bot,top );
   ok = FALSE;
   debug = -1;

lab9: ;
   if (debug < 0)
      for (j = 1; j <= narcs; ++j)
        fprintf(stderr,"insertb %d %9g %9g\n",j,a[j][0],a[j][1]);
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

   if (debug < 0)
      fprintf(stderr,"sort %9g %9g %d\n",a[0],b[0],nocc);
   if (nocc < 2) goto lab1 ;
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
lab1:;
} /* sort */
/**********************************************/

store2()
/* 
   store on output file the values -  
     (1) coords of centre of ellipse, 
     (2) lengths of semi - axes, 
     (3) angle between semi-minor axis and coordinate x axis, 
     (4) number of hidden arcs, 
     (5) pairs of parameter values at ends of these arcs. 

     called by drawel 
*/
{
   int ixc,iyc,iaxx,iaxy,iphi,arctop ;
   int j,k,m,a[EMAX+1][3],b[EMAX+1][3],a1,a2,jm1 ;
   double deg,deg2,ang1,ang2 ;

   deg = (double)1800/pi ;
   deg2 = deg+deg ;
   if (debug < 0)
      fprintf(stderr,"store2a %9g %9g %9g %9g %9g %d\n",
         cen[n][0],cen[n][1],appear[1][0],axxn,phi,narcs );
   a[1][1] = 0; a[1][2] = 0;
   if (narcs > EMAX) goto lab1 ;
   ixc = cen[n][0] ;
   iyc = cen[n][1] ;
   iaxx = axxn ;
   iaxy = axyn ;
   iphi = phi*deg ;
   if (iaxx <= 0) iaxx = 1 ;
   if (iaxy <= 0) iaxy = 1 ;
   if (iphi < 0) iphi = iphi+3600 ;
   arctop = 0 ;
   if (narcs == 0) goto lab4 ;
   if (narcs < 0) goto lab1 ;
/* 
     convert arctans to tenths of a degree - 
*/
   for (  j = 1 ; j <= narcs ; ++ j )
   {
      ang1 = deg2*(atan(appear[j][0])-piby4) ;
      ang2 = deg2*(atan(appear[j][1])-piby4) ;
      if (ang1 < doub0) a1 = ang1 - inv2 ; else a1 = ang1+inv2 ;
      if (ang2 < doub0) a2 = ang2 - inv2 ; else a2 = ang2+inv2 ;
      if (a1 == a2) goto lab3 ;
      arctop = arctop+1 ;
      a[arctop][1] = a1 ;
      a[arctop][2] = a2 ;
      if (debug < 0)
         fprintf(stderr,"store2b %d %d %d %d\n",j,arctop,a1,a2);
      if (a1 >= 0) goto lab3 ;
      if (a2 < 0) goto lab3 ;
/* 
     an arc straddles the 0 point, so split it -  
*/
      a[arctop][2] = 0 ;
      arctop = arctop+1 ;
      a[arctop][1] = 0 ;
      a[arctop][2] = a2 ;
lab3: ;
   }
   if (arctop < 1) goto lab4 ;
/* 
     change negative angles to positive and reposition them - 
     set j to lowest positive angle -  
*/
   for (  j = 1 ; j <= arctop ; ++ j )
   {
      if (a[j][1] >= 0) goto lab6 ;
   }

   j = arctop+1 ;
   goto lab7 ;
/* 
     move positive ones to front -  
*/
lab6: m = 0 ;
   for (  k = j ; k <= arctop ; ++ k )
   {
      m = m+1 ;
      b[m][1] = a[k][1] ;
      b[m][2] = a[k][2] ;
   }
/* 
     move old negative ones to the end -  
*/
lab7: if (j <= 1) goto lab13 ;
   jm1 = j - 1 ;
   for (  k = 1 ; k <= jm1 ; ++ k )
   {
      m = arctop+k - jm1 ;
      b[m][1] = a[k][1]+3600 ;
      b[m][2] = a[k][2]+3600 ;
   }
/* 
     remove redundant arcs -  
*/
lab13: narcs = arctop ;
   k = 1 ;
   a[1][1] = b[1][1] ;
   a[1][2] = b[1][2] ;
   if (arctop <= 1) goto lab4 ;

   for (  j = 2 ; j <= arctop ; ++ j )
   {
      if (a[k][2] >= b[j][1]) goto lab11 ;
      k = k+1 ;
      a[k][1] = b[j][1] ;
      a[k][2] = b[j][2] ;
      goto lab12 ;

lab11: a[k][2] = b[j][2] ;
      narcs = narcs - 1 ;
lab12: ;
   }

   arctop = narcs ;
/* 
     write the values out - 
*/
lab4: printf(" %5d %5d %5d %5d %5d %5d\n",
               ixc,iyc,iaxx,iaxy,iphi,arctop );
   for (j = 1; j <= arctop; ++j)
   {
      if (debug < 0)
         fprintf(stderr,"store2c %d %d\n", a[j][1],a[j][2] );
      printf("%5d %5d\n",a[j][1],a[j][2]);
   }
   goto rtrn ;
/* 
     snag -  
*/
lab1: fprintf(stderr,"\nERROR hideo : store2 %d %d\n",narcs,EMAX);
   ok = FALSE ;

rtrn: ;
} /* store2 */
/****************************************/

int best(a,b,c,d,rts)
double a,b,c,d,rts[4];
/*
   Solve quartic equation using either
   quadratic, Descartes', Ferrari's or Neumark's algorithm.

   called by  ellcut.
   calls  quadratic, descartes, ferrari, neumark.

     21 Jan 1989  Don Herbison-Evans
*/
{
   int descartes(),quadratic(),ferrari(),neumark();
   int j,k;
   int nd,nf,nn;
   int nr;
   int nq;
   double odd, even;
   double rtsd[4];
   double rtsn[4];
   double rtsf[4];
   double rtsq[4];
   double roots[4];
   double rterd[4];
   double rterf[4];
   double rtern[4];
   double rterq[4];
   double maxq,maxd,maxf,maxn;
   char bst;

   if (a < doub0) odd = -a; else odd = a;
   if (c < doub0) odd -= c; else odd += c;
   if (b < doub0) even = -b; else even = b;
   if (d < doub0) even -= d; else even += d;
   nq = 0;
   if (odd < even*doubtol)
   {
      nq = quadratic(b,d,roots,b*b-doub4*d);
      j = 0;
      for (k = 0; k < nq; ++k)
      {
         if (roots[k] > doub0)
         {
            rtsq[j] = sqrt(roots[k]);
            rtsq[j+1] = -rtsq[j];
            ++j; ++j;
         }
      }
      nq = j;
      errors(a,b,c,d,rtsq,rterq,nq);
   }
/*
   solve 3 ways -
*/
   nn = neumark(a,b,c,d,rtsn) ;
   errors(a,b,c,d,rtsn,rtern,nn);
   nd = descartes(a,b,c,d,rtsd) ;
   errors(a,b,c,d,rtsd,rterd,nd);
   nf = ferrari(a,b,c,d,rtsf) ;
   errors(a,b,c,d,rtsf,rterf,nf);
/*
   find best roots -
*/
   if (nd > 0) maxd = doub0; else maxd = doubmax;
   for (k = 0; k < nd; ++k)
      if (maxd < rterd[k]) maxd = rterd[k];
   if (nn > 0) maxn = doub0; else maxn = doubmax;
   for (k = 0; k < nn; ++k)
      if (maxn < rtern[k]) maxn = rtern[k];
   if (nq > 0) maxq = doub0; else maxq = doubmax;
   for (k = 0; k < nq; ++k)
      if (maxq < rterq[k]) maxq = rterq[k];
   if (nf > 0) maxf = doub0; else maxf = doubmax;
   for (k = 0; k < nf; ++k)
      if (maxf < rterf[k]) maxf = rterf[k];
/*
   return these -
*/
   nr = 0;
   bst = '0';
   if (( nn != 0) || (nd != 0) || (nf != 0) || (nq != 0))
   {
      if ((maxd <= maxq) && (maxd <= maxn) && (maxd <= maxf))
      {
         bst = 'd';
         nr = nd;
         for (k = 0; k < nd; ++k)
            rts[k] = rtsd[k];
      }
      else
      if ((maxq <= maxn) && (maxq <= maxf) && (maxq <= maxd))
      {
         bst = 'q';
         nr = nq;
         for (k = 0; k < nq; ++k)
            rts[k] = rtsq[k];
      }
      else
      if ((maxn <= maxq) && (maxn <= maxf) && (maxn <= maxd))
      {
         bst = 'n';
         nr = nn;
         for (k = 0; k < nn; ++k)
            rts[k] = rtsn[k];
      }
      else
      {
         bst = 'f';
         nr = nf;
         for (k = 0; k < nf; ++k)
            rts[k] = rtsf[k];
      }
   }
   return(nr);
} /* best */
/***********************************/

double acos3(x)
   double x ;
/* 
     find cos(acos(x)/3) 
    
     Don Herbison-Evans   16/7/81 

     called by cubic . 
*/
{
   double value;
   double acos(),cos();

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
   double exp(),log();
   double value;
   double absx;
   int neg;

   neg = 0;
   absx = x;
   if (x < doub0)
   {
      absx = -x;
      neg = 1;
   }
   if (absx != doub0) value = exp( log(absx)*inv3 );
      else value = doub0;
   if (neg == 1) value = -value;
   return(value);
} /* curoot */
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
         test = (((rts[k]+a)*rts[k]+b)*rts[k]+c)*rts[k]+d ;
         if (test == doub0) rterr[k] = doub0;
         else
         {
            deriv =
               ((doub4*rts[k]+doub3*a)*rts[k]+doub2*b)*rts[k]+c ;
            if (deriv != doub0)
               rterr[k] = fabs(test/deriv);
            else
            {
               deriv = (doub12*rts[k]+doub6*a)*rts[k]+doub2*b ;
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
         if (rts[k] != doub0) rterr[k] /= rts[k];
         if (rterr[k] < doub0) rterr[k] = -rterr[k];
      }
   }
   if (debug < 0)
      for (k = 0; k < nrts; ++k)
         printf("       %d  %g %g\n",nrts,rts[k],rterr[k]);
} /* errors */
/**********************************************/

int quadratic(b,c,rts,dis)
   double b,c,rts[4],dis ;
/* 
     solve the quadratic equation - 

         x**2+b*x+c = 0 

     called by  best, descartes, ferrari, neumark.
*/
{
   int j,nquad;
   double rtdis ;
   double ans[2] ;

   if (dis >= doub0)
   {
      nquad = 2 ;
      if (dis == doub0) rtdis = doub0;
	 else rtdis = sqrt(dis) ;
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
   return(nquad);
} /* quadratic */
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
     rt3 - sqrt(3) 
     inv3 - 1/3 
     doubmax - square root of largest number held by machine 

     method - 
     see D.E. Littlewood, "A University Algebra" pp.173 - 6 

     Charles Prineas   April 1981 

     called by  neumark, descartes, ferrari.
     calls      acos3, curoot.
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
   double sqrt(),fabs();

   m = doub0;
   if ((p > doubmax) || (p <  -doubmax)) root = -p;
   else
   if ((q > doubmax) || (q <  -doubmax))
   {
       if (q > doub0) root =  -r/q ;
       else
       if (q < doub0) root =  -sqrt(-q);
       else root =  doub0 ;
   }
   else
   if ((r > doubmax)|| (r <  -doubmax)) root =  -curoot(r) ;
   else
   {
      po3 = p*inv3 ;
      po3q = po3*q ;
      po3sq = po3*po3 ;
      if (po3sq > doubmax) root =  -p ;
      else
      {
         po3cu = po3*po3sq ;
         v = r + po3*(po3sq + po3sq - q) ;
         if ((v > doubmax) || (v < -doubmax)) root = -p ;
         else
         {
            vsq = v*v ;
            qo3 = q*inv3 ;
            uo3 = qo3 - po3sq ;
            u2o3 = uo3 + uo3 ;
            if ((u2o3 > doubmax) || (u2o3 < -doubmax))
            {
               if (p == doub0)
               {
                  if (q > doub0) root =  -r/q ;
		  else
                  if (q < doub0) root =  -sqrt(-q);
                  else root =  doub0 ;
               }
               else root =  -q/p ;
            }
            uo3sq4 = u2o3*u2o3 ;
            if (uo3sq4 > doubmax)
            {
               if (p == doub0)
               {
                  if (q > doub0) root = -r/q ;
                  else
		  if (q < doub0) root = -sqrt(-q) ;
		  else root = doub0;
               }
               else root = -q/p ;
            }
            uo3cu4 = uo3sq4*uo3 ;
            wsq = uo3cu4 + vsq ;
            if (wsq > doub0)
            {
/* 
     cubic has one real root 
*/
               if (v <= doub0) mcube = ( -v + sqrt(wsq))*inv2 ;
               if (v  > doub0) mcube = ( -v - sqrt(wsq))*inv2 ;
               m = curoot(mcube) ;
               if (m != doub0) n = -uo3/m ;
                  else n = doub0;
               root = m + n - po3 ;
            }
            else
            {
/* 
     cubic has three real roots 
*/
               if (uo3 < doub0)
               {
                  muo3 = -uo3;
                  if (muo3 > doub0) s = sqrt(muo3) ;
		     else s = doub0;
                  scube = s*muo3;
		  if (scube == doub0)
		  {
		     printf("scube = 0 in cubic,for %g %g %g\n",
			p,q,r);
                     exit(1);
		  }
                  t =  -v/(scube+scube) ;
                  cosk = acos3(t) ;
                  if (po3 < doub0)
                     root = (s+s)*cosk - po3;
                  else
                  {
                     sinsqk = doub1 - cosk*cosk ;
                     if (sinsqk > doub0)
                        root = s*( -cosk - rt3*sqrt(sinsqk)) - po3 ;
                     else root = -s*cosk - po3;
                  }
               }
               else
/* 
     cubic has multiple root -  
*/
               root = curoot(v) - po3 ;
            }
         }
      }
   }
   if (debug < 0)
      printf("   cubic %g %g %g : %g\n",p,q,r,root);
   return(root);
} /* cubic */
/***************************************/

int descartes(a,b,c,d,rts)
double a,b,c,d,rts[4];
/*
   Solve quartic equation using
   Descartes-Euler-Cardano algorithm

   Strong, T. "Elemementary and Higher Algebra"
      Pratt and Oakley, p. 469 (1859)

     29 Jun 1994  Don Herbison-Evans
*/
{
   int quadratic();
   double cubic();

   int j;
   int nrts;
   int r1,r2;
   double v1[4],v2[4];
   double y;
   double dis;
   double p,q,r;
   double A,B,C;
   double m,n1,n2;
   double d3o8,d3o256;
   double inv8,inv16;
   double asq;
   double Ainv4;
   double Binvm;

   d3o8 = (double)3/(double)8;
   inv8 = doub1/(double)8;
   inv16 = doub1/(double)16;
   d3o256 = (double)3/(double)256;

   if (debug < 0) printf("\nDescartes %g %g %g %g\n",a,b,c,d);
   asq = a*a;

   A = b - asq*d3o8;
   B = c + a*(asq*inv8 - b*inv2);
   C = d + asq*(b*inv16 - asq*d3o256) - a*c*inv4;

   p = doub2*A;
   q = A*A - doub4*C;
   r = -B*B;

/***
   double inv64;
   inv64 = doub1/(double)64;
   p = doub2*b - doub3*a*a*inv4 ;
   q = b*b - a*a*b - doub4*d + doub3*a*a*a*a*inv16 + a*c;
   r = a*b*c - c*c - a*a*a*a*a*a*inv64 - a*a*b*b*inv4
       -a*a*a*c*inv4 + a*a*a*a*b*inv8;
***/

   y = cubic(p,q,r) ;
   if (y <= doub0) 
      nrts = 0;
   else
   {
      m = sqrt(y);
      Ainv4 = a*inv4;
      Binvm = B/m;
      n1 = (y + A + Binvm)*inv2;
      n2 = (y + A - Binvm)*inv2;
      r1 = quadratic(-m, n1, v1, y-doub4*n1);
      r2 = quadratic( m, n2, v2, y-doub4*n2);
      rts[0] = v1[0]-Ainv4;
      rts[1] = v1[1]-Ainv4;
      rts[r1] = v2[0]-Ainv4;
      rts[r1+1] = v2[1]-Ainv4;
      nrts = r1+r2;
   } 
   return(nrts);
} /* descartes */
/****************************************************/

int ferrari(a,b,c,d,rts)
   double a,b,c,d,rts[4];
/* 
     solve the quartic equation - 

   x**4 + a*x**3 + b*x**2 + c*x + d = 0 

   called by quartic
   calls     cubic, quadratic.

     input - 
   a,b,c,e - coeffs of equation. 

     output - 
   nquar - number of real roots. 
   rts - array of root values. 

     method :  Ferrari - Lagrange
     Theory of Equations, H.W. Turnbull p. 140 (1947)

     calls  cubic, quadratic 
*/
{
   double cubic();
   int quadratic();

   int k,nquar,n1,n2 ;
   double asqinv4;
   double ainv2;
   double d4;
   double yinv2;
   double v1[4],v2[4] ;
   double p,q,r ;
   double y;
   double e,f,esq,fsq,ef ;
   double g,gg,h,hh;

   if (debug < 0) printf("\nFerrari %g %g %g %g\n",a,b,c,d);
   ainv2 = a*inv2;
   asqinv4 = ainv2*ainv2;
   d4 = d*doub4;

   p = b ;
   q = a*c-d4 ;
   r = (asqinv4 - b)*d4 + c*c ;
   y = cubic(p,q,r) ;

   yinv2 = y*inv2;
   esq = asqinv4 - b - y;
   fsq = yinv2*yinv2 - d;
   if ((esq < doub0) && (fsq < doub0)) nquar = 0;
   else
   {
      ef = -(inv4*a*y + inv2*c);
      if (debug < 0) printf("   esq %g,   fsq %g,    ef %g\n",
         esq,fsq,ef);
      if ( ((a > doub0)&&(y > doub0)&&(c > doub0))
        || ((a > doub0)&&(y < doub0)&&(c < doub0))
        || ((a < doub0)&&(y > doub0)&&(c < doub0))
        || ((a < doub0)&&(y < doub0)&&(c > doub0))
        ||  (a == doub0)||(y == doub0)||(c == doub0)
         )
/* use ef - */
         {
            if ((b < doub0)&&(y < doub0))
            {
               e = sqrt(esq);
               f = ef/e;
            }
            else if (d < doub0)
            {
               f = sqrt(fsq);
               e = ef/f;
            }
            else
            {
               if (esq > doub0) e = sqrt(esq); else e = doub0;
               if (fsq > doub0) f = sqrt(fsq); else f = doub0;
               if (ef < doub0) f = -f;
            }
         }
         else
/* use esq and fsq - */
         {
            if (esq > doub0) e = sqrt(esq); else e = doub0;
            if (fsq > doub0) f = sqrt(fsq); else f = doub0;
            if (ef < doub0) f = -f;
         }
/* note that e >= doub0 */
         g = ainv2 - e;
         gg = ainv2 + e;
         if ( ((b > doub0)&&(y > doub0))
           || ((b < doub0)&&(y < doub0)) )
         {
            if ((a > doub0) && (e > doub0)
	     || (a < doub0) && (e < doub0) ) g = (b + y)/gg;
            else
	    if ((a > doub0) && (e < doub0)
	     || (a < doub0) && (e > doub0) ) gg = (b + y)/g;
         }

         h = -yinv2 - f;
         hh = -yinv2 + f;
         if ( ((f > doub0)&&(y < doub0))
           || ((f < doub0)&&(y > doub0)) ) h = d/hh;
         else if ( ((f < doub0)&&(y < doub0))
                || ((f > doub0)&&(y > doub0)) ) hh = d/h;
	 if (debug < 0)
	    printf("   hh %g,   h %g,    gg %g,   g %g\n",
	    hh,h,gg,g);
         n1 = quadratic(gg,hh,v1, gg*gg - doub4*hh) ;
         n2 = quadratic(g,h,v2, g*g - doub4*h) ;
         nquar = n1+n2 ;
         rts[0] = v1[0] ;
         rts[1] = v1[1] ;
         rts[n1+0] = v2[0] ;
         rts[n1+1] = v2[1] ;
   }
   return(nquar);
} /* ferrari */
/*****************************************/

int neumark(a,b,c,d,rts)
   double a,b,c,d,rts[4];
/* 
     solve the quartic equation - 

   x**4 + a*x**3 + b*x**2 + c*x + d = 0 

   called by quartic
   calls     cubic, quadratic.

     input parameters - 
   a,b,c,e - coeffs of equation. 

     output parameters - 
   nquar - number of real roots. 
   rts - array of root values. 

     method -  S. Neumark 

     Solution of Cubic and Quartic Equations - Pergamon 1965 
        translated to C with help of Shawn Neely

*/
{
   int k,nquar,n1,n2 ;
   double y,g,gg,h,hh,gdis,gdisrt,hdis,hdisrt,g1,g2,h1,h2 ;
   double bmy,gerr,herr,y4,bmysq ;
   double v1[4],v2[4] ;
   double asq ;
   double d4;
   double p,q,r ;
   double hmax,gmax ;
   double cubic();
   int quadratic();

   if (debug < 0) printf("\nNeumark %g %g %g %g\n",a,b,c,d);
   asq = a*a ;
   d4 = d*doub4;

   p =  -b*doub2 ;
   q = b*b + a*c - d4 ;
   r = (c - a*b)*c + asq*d ;
   y = cubic(p,q,r) ;

   bmy = b - y ;
   y4 = y*doub4 ;
   bmysq = bmy*bmy ;
   gdis = asq - y4 ;
   hdis = bmysq - d4 ;
   if ((gdis <= doub0) || (hdis <= doub0))
      nquar = 0;
   else
   {
      g1 = a*inv2 ;
      h1 = bmy*inv2 ;
      gerr = asq + y4 ;
      herr = hdis ;
      if (d > doub0) herr = bmysq + d4 ;
      if ((y < doub0) || (herr*gdis > gerr*hdis))
      {
         gdisrt = sqrt(gdis) ;
         g2 = gdisrt*inv2 ;
         if (gdisrt != doub0) h2 = (a*h1 - c)/gdisrt ;
            else h2 = doub0;
      }
      else
      {
         hdisrt = sqrt(hdis) ;
         h2 = hdisrt*inv2 ;
         if (hdisrt != doub0) g2 = (a*h1 - c)/hdisrt ;
            else g2 = doub0;
      }
/* 
     note that in the following, the tests ensure non-zero 
     denominators -  
*/
      h = h1 - h2 ;
      hh = h1 + h2 ;
      hmax = hh ;
      if (hmax < doub0) hmax =  -hmax ;
      if (hmax < h) hmax = h ;
      if (hmax <  -h) hmax =  -h ;
      if ((h1 > doub0)&&(h2 > doub0)) h = d/hh ;
      if ((h1 < doub0)&&(h2 < doub0)) h = d/hh ;
      if ((h1 > doub0)&&(h2 < doub0)) hh = d/h ;
      if ((h1 < doub0)&&(h2 > doub0)) hh = d/h ;
      if (h > hmax) h = hmax ;
      if (h <  -hmax) h =  -hmax ;
      if (hh > hmax) hh = hmax ;
      if (hh <  -hmax) hh =  -hmax ;

      g = g1 - g2 ;
      gg = g1 + g2 ;
      gmax = gg ;
      if (gmax < doub0) gmax =  -gmax ;
      if (gmax < g) gmax = g ;
      if (gmax <  -g) gmax =  -g ;
      if ((g1 > doub0)&&(g2 > doub0)) g = y/gg ;
      if ((g1 < doub0)&&(g2 < doub0)) g = y/gg ;
      if ((g1 > doub0)&&(g2 < doub0)) gg = y/g ;
      if ((g1 < doub0)&&(g2 > doub0)) gg = y/g ;
      if (g > gmax) g = gmax ;
      if (g <  -gmax) g =  -gmax ;
      if (gg > gmax) gg = gmax ;
      if (gg <  -gmax) gg =  -gmax ;
 
      n1 = quadratic(gg,hh,v1, gg*gg - doub4*hh) ;
      n2 = quadratic(g,h,v2, g*g - doub4*h) ;
      nquar = n1+n2 ;
      rts[0] = v1[0] ;
      rts[1] = v1[1] ;
      rts[n1+0] = v2[0] ;
      rts[n1+1] = v2[1] ;
   }
   return(nquar);
} /* neumark */
/****************************************************/

