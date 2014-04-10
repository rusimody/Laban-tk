/*             prfrm.c
              version 03

     This program reads numerically coded specifications of
     actions to be performed in a computer animated movie,
     and performs them to give a set of 3-d specifications
     of ellipsoids and joints in each frame of the movie.

        modified-
   12 Sep 2003 error message contains frame number
   10 Sep 2003 touch using nested search
   24 Jul 2003 extending drag search angle from 10 to 20 degrees
   16 Jun 2003 improving drag
    6 Jun 2003 debugging drag
   17 Jul 1996 print command to standard error output
    7 Feb 1996 clean up dotouch
    3 Feb 1996 clear floating exceptions
   19 Aug 1994 removed some goto's
   13 Aug 1994 cleaning up perfrm
   29 Apr 1994 cleaning up drag
   22 Sep 1993 cleaning up after detach fixed up
   16 Aug 1993 movjnt added
   12 Mar 1993 abut added
   11 Mar 1993 repeat subroutine calls allowed
   17 Feb 1993 touch using Buckdale's algorithm
    4 Feb 1993 touch using scanning
   28 Oct 1992 joint limits added
   15 Oct 1992 viewing transformation separated
   17 Apr 1992 touch fixed
   12 Feb 1992 allow cubic actions
   29 Jul 1991 print variable values nicely
   24 Nov 1988 more ellipsoids accommodated
   10 Dec 1986 translated into c
   29 Nov 1986 write figure for Benesh interpreter
   17 Oct 1986 texturing for ellipsoids
    9 Mar 1986 print statement added
   22 Jun 1985 grofig scales about an ellipsoid (Peter Gummer)
   14 Jun 1985 spinto added (Peter Gummer)
   15 Apr 1985 setels simplified (Peter Gummer)
    3 Apr 1985 world added, refell for spinby,moveby (Peter Gummer)
    3 Jan 1985 attach, detach work properly (Peter Gummer)
    7 May 1984 multiply, subtract, divide, balance added
   12 Dec 1983 variable frame numbers
   25 Nov 1983 rotations stored as twist about axis
   22 Nov 1983 separate error message file
    2 Nov 1983 moved codes for reals to 21-29 (Danuta Kucharska)
   15 Oct 1983 'colour' added, default: flesh (Danuta Kucharska)
   19 Apr 1983 insert axes, link, fix detach, ground
   16 Sep 1982 ellipsoid names put in 1st frame
   19 Jul 1982 tolerance put in subroutine rotput
   31 Mar 1982 observe, all added
   26 Mar 1982 single precision version for speed
    8 Oct 1981 make data structure of figure a list
    2 Oct 1981 add, attach, detach, flex, extend, etc. added
   16 Jul 1981 to negate variables (Nora Neilands)
   16 Jun 1981 to store orientations and positions (Nora Neilands)
   29 May 1980 separate compile and perform
   27 Jul 1979 groell, grojnt added
   20 Feb 1979 subroutines added
    1 Apr 1977 named constants introduced
   17 Jan 1977 bends use arbitrary reference ellipsoid (Bruce McNair)
    4 Jun 1976 made interpretive
   10 May 1976 input trnsltn separated from drawing
    1 Apr 1975 frame numbers used in input language
   28 Oct 1974 to use optionally the plotter
   24 Sep 1974 to verbalize the input language
   11 Apr 1973 to allow more than one figure
    1 Dec 1972 to remove hidden lines

        originated-
     Don Herbison-Evans  1972


     subroutines -
        main    - organises things
        setup   - set up constants
        input   - reads the numerical action specifications
        action  - selects an action to perform
        chckpr  - checks parameters for legality
        getval  - gets a value from constants or variables
        doframes- runs through each frame in turn
        perfrm  - performs each action in turn for a given frame
        rotget  - retrieves rotation matrix from 'quat' array
        rotput  - stores rotation matrix into 'quat' array
        dospinto- spins a set of ellipsoids to a given orientation
        dospinby- spins a set of ellipsoids by a given angle
        twirl   - rotates all ellipsoids and joints in 'elist' and 'jlist'
        matmul  - multiplies 2 matrices together
        matrot  - rotates a single ellipsoid
        vecmul  - multiplies a selected vector by a matrix
        vecmat  - multiplies a vector by a matrix
        mkang   - generates angles from 'quat' array entry
        shift   - moves a set of ellipsoids
        rset    - sets up a primitive rotation matrix
        mkquat  - generates 'quat' array entry from angles
        doground- moves a set of ellipsoids to rest on y = 0
        setels  - finds ellipsoids and joints connected to given ellipsoid
        setjnt  - finds ellipsoids and joints connected to a given joint
        setfrc  - sets proportion of action for current frame
        setper  - decodes the parameters of the current action
        scale   - scale a value by some proportion
        sqr     - square a value
        store3  - writes data about given frame to output file
        ipr     - print out integral parts to six places
        docola  - sets colours of an ellipsoid
        setplc  - sets viewing point (array 'pplace')
        setobs  - sets 3*3 matrix for viewing rotation and place
        enquir  - stores values of centres, joints or axis lengths
        doangles- stores angles of an ellipsoid
        findfg  - finds which figure includes a given ellipsoid
        doattach- joins 2 figures into 1
        dodetach- breaks 1 figure into 2
        domoveby- moves a set of ellipsoids relative to refell
        dogrofig- scales a set of ellipsoids in size
        dogroell- scales axes of an ellipsoid
        dogrojnt- scales set of ellipsoids keeping a joint fixed
        domovjnt- moves a joint
        dobend  - implements flex, rotate, abduct commands
        prinel  - writes out diagnostics about each ellipsoid
        balanc  - balances part of a figure
        dodrag  - keeps an ellipsoid touching ground
        solve   - find zero of 'fun'
        fun     - used by 'solve' for abut
        dotouch - bends a figure to make 2 ellipsoids touch
        surf    - find separation of ellipsoid surfaces
        angsepn - find approx angular separation of ell1 and ell2 from x
        dcen    - find separation of ellipsoid centres
        sepn    - find distance between 2 ellipsoid surfaces
        getmat  - generate matrix of an ellipsoid
        save    - store positions and orientations
        restore - restore positions and orientations
        fndmin  - find minimum of function 'try'.
        try     - 'domoveby' then 'sepn'
        getaxes - find axis lengths of an ellipsoid
        newton  - solve a polynomial
        doabut  - slide figure to touch another

*************************************************************/

#include <stdio.h>
#include <values.h>

#define TRUE    1
#define FALSE   0
#define BMAX  256
#define EMAX 1024
#define KMAX  100
#define NMAX   30
#define PMAX 2345

char    buf[BMAX] ;
char    ename[EMAX][BMAX];
char    fname[EMAX][BMAX] ;
char    jname[EMAX][BMAX];
char    sname[EMAX][BMAX];
char    vname[EMAX][BMAX];

double  fabs(),sqrt(),log(),exp();
double  sin(),cos(),acos(),atan(),atan2();

double  ang[3];
double  ax3[EMAX][3];
double  cen[EMAX][3];
double  censav[EMAX][3];
double  degree;          /* number of degrees in a radian */
double  doub0;
double  doub1;
double  doub2;
double  doub3;
double  doub4;
double  doub10;
double  doubmax;
double  f[3];
double  frac;
double  inv2;
double  inv3;
double  inv6;
double  jnt[EMAX][3] ;
double  jntsav[EMAX][3] ;
double  lim[EMAX][3][2];
double  lg2;
double  maxax[EMAX];
double  minax[EMAX];
double  obs[3][3];
double  oldang[3];
double  pi;
double  piby2;
double  pplace[3] ;
double  pres[EMAX];
double  prop;
double  radian;     /* number of radians in a degree */
double  quat[EMAX+2][5];
double  quasav[EMAX+2][5];
double  rt3;
double  step1,step2;
double  told;
double  twopi;
double  v ;
double  val[EMAX] ;
double  varval;
double  x[3];
double  x1a,x1b,x2a,x2b;
double  y1a,y1b,y2a,y2b;
double  x1s,x2s,y1s,y2s;

float tolr;

   int figure = 1;
   int ellips = 2;
   int joint  = 3;
   int accele = 5;
   int subrou = 6;
   int balanc = 7;
   int attach = 8;
   int detach = 9;
   int decele = 10;
   int grofig = 11;
   int spinto = 12;
   int moveby = 13;
   int add    = 14;
   int touch  = 15;
   int stop   = 16;
   int spinby = 17;
   int ground = 18;
   int bendby = 19;
   int set    = 20;
   int bendto = 21;
   int dodebug= 22;
   int repeat = 23;
   int quadra = 24;
   int linear = 25;
   int observ = 26;
   int moveto = 27;
   int call   = 28;
   int endsub = 29;
   int speed  = 30;
   int invert = 31;
   int variab = 32;
   int view   = 33;
   int groell = 34;
   int grojnt = 35;
   int angles = 36;
   int centre = 37;
   int flex   = 38;
   int rotate = 39;
   int abduct = 40;
   int negate = 41;
   int subtra = 42;
   int divide = 43;
   int multip = 44;
   int cubic  = 46;
   int place  = 47;
   int axes   = 48;
   int linkx  = 49;
   int colour = 50;
   int print  = 51;
   int textur = 52;
   int drag   = 53;
   int limits = 54;
   int abut   = 55;
   int movjnt = 56;

int     perm[3][3][3] = {
      { {2,1,1},{1,3,4},{1,5,3} },
      { {3,1,5},{1,2,1},{4,1,3} },
      { {3,4,1},{5,3,1},{1,1,2} }};

int     axis;
int     cline[PMAX];
int     code[6][KMAX] ;
int     coel[EMAX][2];
int     debug;
int     distrn[PMAX];
int     ecount;
int     elcol[EMAX][3] ;
int     elist[EMAX];
int     ell1;
int     ell2;
int     ellpsd;
int     fast;
int     fig;
int     figell[EMAX] ;
int     first ;
int     fr;
int     frstart[PMAX];
int     frstop[PMAX] ;
int     fslow;
int     intersect;
int     jcount ;
int     jlist[EMAX] ;
int     join;
int     k;
int     knee[EMAX] ;
int     more ;
int     nels;
int     nerrs;
int     newcol[3] ;
int     nfigs;
int     nfiles;
int     nkeys ;
int     nsubs;
int     nvars;
int     njts;
int     npfs ;
int     ok[7] ;
int     pp;
int     pf[PMAX][6];
int     refell;
int     subact[EMAX][2] ;
int     t;
int     type[PMAX] ;
int     var0;
int     var1;
int     var2;
int     vstop ;
int     vstart;
/*
   global variables -
*/
/*  ax[i][j] - length of jth semiaxis of ith ellipsoid  */
/*  cen[i][j] - jth coordinate of centre of ith ellipsoid  */
/*  code[i][j] - type of ith parameter of jth keyword  */
/*  coel[i][] - the 2 ellipsoids at ith joint  */
/*  debug -  <= 0 for voluminous diagnostic output  */
/*  distrn[i] - distribution of ith action over its frames  */
/*  elcol[i][j] - colour of ell i; j = 0 red, 1 green, 2 blue  */
/*  elist - array for lists of ellipsoids in current action  */
/*  err - device for diagnostic printout  */
/*  fast - multiplier of frame numbers  */
/*  figell[i] - first ellipsoid in ith figure  */
/*  first - true when doing first frame */
/*  frstart[i] - frame number of start of ith action  */
/*  frstop[i] - frame number of end of ith action  */
/*  jlist - array for lists of joints in current action  */
/*  knee[j] - true if jth joint is a knee i.e. flexes backwards  */
/*  lg2 - logarithm of 2 */
/*  maxax[j] - largest semiaxis of jth ellipsoid */
/*  nels - number of ellipsoids  */
/*  nfigs - number of figures  */
/*  njts - number of joints  */
/*  nkeys - number of keywords  */
/*  npfs - number of actions  */
/*  nsubs - number of subroutines  */
/*  nvals - number of values in array val  */
/*  nvars - number of variables in array val  */
/*  obs  - rotation matrix applied to all ellipsoids to  */
/*          obtain observers view  */
/*  ok - ok[0] = 0 if ok, otherwise the problem reference number */
/*       ok[1],ok[2],ok[3],ok[4],ok[5] - problem parameters  */
/*  place - position of centre of observers attention  */
/*  pf[i][j] - jth parameter of ith action- */
/*            positive- itself  */
/*            negative- index into array val  */
/*  quat[i][j] - angle of ith ellipsoid  */
/*        j = 0,1,2 - components of direction of rotation axis  */
/*        j = 3,4   - sine and cosine of rotation about axis  */
/*  s - size of ellipsoid arrays (max number of ellipsoids)  */
/*  fslow - frame step size  */
/*  subact[i][] - action numbers of start and end of ith subroutine  */
/*  type[i] - type of ith action  */
/*  val[i] - if i <= nvals then value of ith constant,  */
/*           otherwise (s - i+1)th variable  */
/*  ang[3] - the 3 eulerian angles  */
/*  ell1 - ellipsoid to touch something  */
/*  ell2 - ellipsoid to be touched */
/*  f[3]     - factors in x,y, and z directions  */
/*  fr    - number of current frame   */
/*  frac  - proportion of action to be done in current frame  */
/*  frame - current formal frame number  */
/*  join - joint for current bend command  */
/*  more  - if  > 0 indicates that there remain more actions  */
/*           for which stp  >=  fr .  */
/*  prop  - fractional proportion of action yet to be done  */
/*  pstart - number of earliest action of current subroutine  */
/*  pend   - last action of current subroutine */
/*  radian - number of radians in one degree  */
/*  refell - ellipsoid being used as angular reference  */
/*  t      - type of current action  */
/*  var1   - number of first variable in current action  */
/*  var2   - number of second variable in current action  */
/*  var3   - number of inv3 variable in current action  */
/*  varval - value of variable  */
/*  x[3]   - x,y and z values (x&y used for commands add,  */
/*                            subtract,multiply,divide)  */

/*********************************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls  setup, input, doframes, store3.
*/
{
   int doframes();
   int f;
   int j;
   FILE *erfile;

   setup();
   if (debug <= 0)
      printf("main %9g %9g %9g\n",doubmax,tolr,told);
/*
  read descriptions of required actions -
*/
   input();
/*
  now to perform the required actions -
*/
   if (ok[0] == 0)
      f = doframes();
   if (ok[0] != 0)
   {
      if (nerrs > 6 ) nerrs = 6;
      ok[nerrs] = 12345;
      erfile = fopen("prfrm.mess","w");
      fprintf(erfile,"***error  frame %d   action %d   line %d\n",f,t,cline[pp]);
      for (j = 0; j <=  nerrs ; ++j) fprintf(erfile," %3d",ok[j]);
      fprintf(erfile,"\n");
      if (debug <= 0)
      {
         printf("***error %d %d\n",t,cline[pp]);
         for (j = 0; j <=  nerrs ; ++j) printf(" %3d",ok[j]);
         printf("\n");
      }
      exit(1);
   }
/*
   write null record on output file -
*/
   nels = 1;
   store3(f);
   exit(0);
}  /* main */
/***********************************************/

setup()
/*
   set up constants

   called by main
*/
{
   double doub;
   double doubm;

   debug = 1;
   t = 0;
   nerrs = 2;
   first = TRUE;
   doub0 = (double)0;
   doub1 = (double)1;
   doub2 = (double)2;
   doub3 = (double)3;
   doub4 = (double)4;
   doub10 = (double)10;
   inv2 = doub1/doub2;
   inv3 = doub1/doub3;
   inv6 = doub1/(double)6;
   rt3 = sqrt(doub3);
   piby2 = doub2*atan(doub1);
   pi = piby2+piby2 ;
   twopi = pi+pi;
   radian = twopi/(double)360;
   degree = doub1/radian;
   lg2 = log(doub2);
   doubm = doub1;
   for (doub = inv2; ((doub != doub0)&&(doub < doubm)); doub *= doub)
   {
      doubmax = doubm;
      doubm = doub;
   }
   if (doubmax > doub0) doubmax = doub4/doubmax; else doubmax = 1000000000000;
   for (told = inv2; (doub1+told > doub1+inv2*told); told *= inv2);
   tolr = doub3*sqrt(told);
} /* setup */
/**************************************************/

input()
/*
  read in the numerical specifications of the actions
  to be performed.

  called by main
  calls  rset
*/
{
   float f0,f1,f2,g0,g1,g2;
   float m00,m01,m10,m11,m20,m21;
   int j,k,m,n;
   int coel0,coel1,dummy;
   int nvals ;
   char line[EMAX] ;
   char kneec;
/*
  set up observers matrix as unit matrix at screen centre-
*/
   rset(obs,doub0,1) ;
   pplace[0] = 500.0 ;
   pplace[1] = 500.0 ;
   pplace[2] = 500.0 ;
/*
  clear everything-
*/
   for ( k = 0 ; k < 6; ++k)
      ok[k] = 0;
   for ( j = 0 ; j < EMAX ; ++ j )
   {
      for ( k = 0 ; k < NMAX; ++k)
         fname[j][k] = '\0';
      for ( k = 0 ; k < 3; ++k)
      {
         lim[j][k][0] = -piby2;
         lim[j][k][1] =  piby2;
      }
      val[j] = -doub1 ;
      figell[j] = -1 ;
      knee[j] = FALSE ;
      coel[j][0] = -1 ;
      coel[j][1] = -1 ;
      subact[j][0] = -1 ;
      subact[j][1] = -1 ;

      quat[j][0] = doub1 ;
      quat[j][1] = doub0 ;
      quat[j][2] = doub0 ;
      quat[j][3] = doub0 ;
      quat[j][4] = doub1 ;
/*
  default colour is flesh colour -
*/
      elcol[j][0] = 255 ;
      elcol[j][1] = 128 ;
      elcol[j][2] = 64 ;
   }

   scanf("%d %d %d %d %d %d %d %d %d\n",
      &debug,&njts,&nels,&fast,&fslow,&npfs,&nvals,&nvars,&nfigs );
   if (debug <= 0)
      printf("prfrmz\n");
   if (debug <= -1)
      printf("inputa %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",
          debug,njts,nels,fast,fslow,npfs,nvals,nvars,nfigs );
   scanf("%d %d %d %d %d\n",&nkeys,&nsubs,&vstart,&vstop,&nfiles);
   if (debug <= -1)
      printf("inputb %3d %3d %3d %3d %3d\n",
        nkeys,nsubs,vstart,vstop,nfiles);
   if (nels > EMAX)
   {
      ok[0] = 1 ;
      ok[1] = nels ;
      ok[2] = EMAX ;
      nerrs = 3;
   }
   else
   if (njts > EMAX)
   {
      ok[0] = 2 ;
      ok[1] = njts ;
      ok[2] = EMAX ;
      nerrs = 3;
   }
   else
   if (nkeys > EMAX)
   {
      ok[0] = 3 ;
      ok[1] = nkeys;
      ok[2] = EMAX ;
      nerrs = 3;
   }
   else
   if (npfs > PMAX)
   {
      ok[0] = 4 ;
      ok[1] = npfs ;
      ok[2] = PMAX ;
      nerrs = 3;
   }
   else
   if (nvars+nvals > EMAX)
   {
      ok[0] = 5 ;
      ok[1] = nvals ;
      ok[2] = nvars ;
      ok[3] = EMAX ;
      nerrs = 4;
   }
   else
   if (nsubs > EMAX)
   {
      ok[0] = 6 ;
      ok[1] = nsubs ;
      ok[2] = EMAX ;
      nerrs = 3;
   }
   else
   if (nfigs > EMAX)
   {
      ok[0] = 7 ;
      ok[1] = nfigs ;
      ok[2] = EMAX ;
      nerrs = 3;
   }
   else
   {
      if (debug <= 0)
         printf("inputc %3d subroutines\n",nsubs);
      for (j = 0; j < nsubs; ++j)
      {
         scanf("%d %d\n",&subact[j][0],&subact[j][1]);
         if (debug <= -1)
            printf("inputd %3d %3d %3d\n",
               j,subact[j][0],subact[j][1] );
      }
      if (debug <= 0)
         printf("inpute %3d actions\n",npfs);
      for (j = 0; j < npfs; ++j)
      {
         scanf("%d %d %d %d %d %d %d %d %d %d %d\n",
            &type[j],&frstart[j],&frstop[j],&distrn[j],
            &pf[j][0],&pf[j][1],&pf[j][2],&pf[j][3],&pf[j][4],&pf[j][5],
            &cline[j]);
         if (debug <= -1) printf(
            "inputf %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",
               j,type[j],frstart[j],frstop[j],distrn[j],
               pf[j][0],pf[j][1],pf[j][2],pf[j][3],pf[j][4],pf[j][5],
               cline[j]) ;
      }
      if (debug <= 0) printf("inputg %3d joints\n",njts);
      for (j = 0; j < njts; ++j)
      {
         scanf("%d %d %g %g %g %g %g %g %g %g %g %c\n",
            &coel0,&coel1,&f0,&f1,&f2,
            &m00,&m01,&m10,&m11,&m20,&m21,&kneec);
         coel[j][0] = coel0;
         coel[j][1] = coel1;
         jnt[j][0] = f0; jnt[j][1] = f1; jnt[j][2] = f2;
         lim[j][0][0] = radian*m00; lim[j][0][1] = radian*m01;
         lim[j][1][0] = radian*m10; lim[j][1][1] = radian*m11;
         lim[j][2][0] = radian*m20; lim[j][2][1] = radian*m21;
         if (kneec == 't') knee[j] = TRUE;
         if (debug <= -1)
         {
            printf("inputh %3d %3d %3d\n",
                j,coel[j][0],coel[j][1]);
            printf(" %9g %9g %9g %9g %9g %9g %9g %9g %9g %3d\n",
                jnt[j][0],jnt[j][1],jnt[j][2],
                lim[j][0][0],lim[j][0][1],lim[j][1][0],
                lim[j][1][1],lim[j][2][0],lim[j][2][1],knee[j]);
         }
      }
      if (debug <= 0) printf("inputi %3d figures\n",nfigs);
      for (j = 0; j < nfigs; ++j)
      {
         scanf("%d",&dummy);
         figell[j] = dummy;
         if (debug <= -1)
            printf("inputj %3d %3d ",j,figell[j]) ;
      }
      if (debug <= 0)
         printf("inputk %3d code array\n",nkeys);
      for (j = 0; j < nkeys; ++j)
      {
         for (k = 0; k < 6; ++k)
         {
            scanf("%d",&code[k][j]);
            if (debug <= -1) printf("inputl %3d ",code[k][j]);
         }
         if (debug <= -1) printf("\n");
      }
      if (debug <= 0)
         printf("inputm %3d values\n",nvals);
      for (j = 0, m= 0; j < (1+(nvals-1)/5); ++j)
      {
         for (k = 0; ((k < 5)&&(m < nvals)); ++k, ++m)
         {
             scanf("%g",&f0); val[m] = f0;
             if (debug <= -1)
                printf("inputn %9g  ",val[m]);
         }
         if (debug <= -1)
            printf("\n");
      }
      if (debug <= 0) printf("inputo %3d ellipsoids\n",nels);
      for (j = 0; j < nels; ++j)
      {
         scanf("%g %g %g %g %g %g\n",&f0,&f1,&f2,&g0,&g1,&g2);
         ax3[j][0] = f0; ax3[j][1] = f1; ax3[j][2] = f2;
         cen[j][0] = g0; cen[j][1] = g1; cen[j][2] = g2;
         maxax[j] = f0;
         minax[j] = f0;
         if (f1 < f0) minax[j] = f1;
         if (f1 > f0) maxax[j] = f1;
         if (f2 < minax[j]) minax[j] = f2;
         if (f2 > maxax[j]) maxax[j] = f2;
         if (debug <= -1) printf(
            "inputp %3d %9g %9g %9g %9g %9g %9g\n    %9g %9g\n",
               j,ax3[j][0],ax3[j][1],ax3[j][2],
                  cen[j][0],cen[j][1],cen[j][2],
                     minax[j],maxax[j]);
      }
      if (debug <= 0)
         printf("inputq %3d texture files\n",nfiles);
      for (j = 0; j < nfiles; ++j)
      {
         scanf("%d %s\n",&dummy,buf);
         for(k = 0; buf[k] != '\0'; ++ k)
            fname[j][k] = buf[k];
         if (debug <= -1)
         {
            printf("inputr %3d ",j);
            for(k = 0; fname[j][k] != '\0'; ++ k)
	       printf("%c",fname[j][k]);
            printf("\n");
         }
      }
      if (debug <= 0)
         printf("inputs %3d par array\n",nkeys);
      for (j = 0; j < 6*nkeys; ++j)
      {
         scanf("%d",&dummy);
         if (debug <= -1)
         {
            if (j%6 == 0) printf("\n");
            printf("inputt %3d ",dummy);
         }
      }
      if (debug <= 0) printf("inputu %d keywords\n",nkeys);
      for (j = 1; j < nkeys; ++j)
      {
         scanf("%d %s\n",&dummy,line);
         if (debug <= -1)
            printf("inputv %3d %s\n",dummy,line);
      }
      if (debug <= 0) printf("inputv %d ellnames\n",nels);
      for (j = 0; j < nels; ++j)
      {
         scanf("%d %s\n",&n,ename[j]);
         if (debug <= -1)
            printf("inputw %d %3d %s\n",j,n,ename[j]);
      }
      if (debug <= 0) printf("inputx %d jntnames\n",njts);
      for (j = 0; j < njts; ++j)
      {
         scanf("%d %s\n",&n,jname[j]);
         if (debug <= -1)
            printf("inputy %d %3d %s\n",j,n,jname[j]);
      }
      if (debug <= 0) printf("inputz %d subnames\n",nsubs);
      for (j = 0; j < nsubs; ++j)
      {
         scanf("%d %s\n",&n,sname[j]);
         if (debug <= -1)
            printf("input1 %d %3d %s\n",j,n,sname[j]);
      }
      if (debug <= 0) printf("input0 %d varnames\n",nvars);
      for (j = 0; j < nvars; ++j)
      {
         scanf("%d %s\n",&n,vname[j]);
         if (debug <= -1)
            printf("input1 %d %3d %s\n",j,n,vname[j]);
      }
   }
}  /* input */
/*****************************************/

int doframes()
/*
  calls and performs the actions for each frame in turn.

  calls perfrm, store3.
  called by main
*/
{
   int j;

   if (debug <= 0) printf("doframesa %d\n",vstop);
   t = 1;
   axis = 1;
   join = 1;
   var0 = 1;
   var1 = 1;
   var2 = 1;
   fig = 1;
   ellpsd = 1;
   refell = 1;
   ell1 = 1;
   ell2 = 1;
   for (j = 0; j < 3; ++j)
   {
      newcol[j] = 0;
      oldang[j] = doub0;
      ang[j] = doub0;
      x[j] = doub0;
      f[j] = doub1;
   }
   varval = doub0;
   more = 1 ;
/*
  run thru frames of movie-
*/
   for (fr= 1; ((more > 0)&&(fr<= vstop)); ++fr)
   {
      if (debug <= 0)
         printf("doframesb %d %d\n",fr,more);
      more = 0;
      perfrm(0,fr,0,vstop);
      if ((fr > vstart) && ((fslow == 1) || (fr%fslow == 1)))
         store3(fr);
      if (debug <= 0)
         printf("doframesc %d %d\n",fr,more);
   }
   return(fr);
} /* doframes */
/*********************************************/

perfrm(sub,fr,fstart,fend)
int sub,fr,fstart,fend;
/*
   perform actions of subroutine 'sub' for frame 'fr'
   between frames 'fstart' and 'fend'

   called by doframes
   calls  getval, setfrc, setper, action.
*/
{
   int getval();
   int frame;
   int j;
   int newsub;
   int p;
   int pstart,pend;
   int sstart;
   int start,stp;
   int substart ;

   if (debug <= 0)
      printf("\nperfrma %3d %3d %3d %3d %3d %3d\n",
         sub,fr,fstart,fend,fast,fslow);
   pstart = subact[sub][0] ;
   pend = subact[sub][1] ;
/*
  find 'subfrm', the earliest formal frame number in subroutine
  ignoring unset variable frame numbers ( == -1) -
*/
   substart = MAXINT ;
   for (p = pstart ; p <= pend ; ++p )
   {
      sstart = getval(frstart[p]) ;
      if (ok[0] != 0) goto snag ;
      if (sstart >= 0)
      {
         sstart *= fast ;
         if (sstart < substart) substart = sstart ;
      }
   }
   frame = fr + substart - fstart ;
   if (debug <= 0)
         printf("perfrmb %3d %3d %3d %3d\n",
            pstart,pend,substart,frame);
/*
  run through actions in the subroutine -
*/
  for (p = pstart; p <= pend; ++p)
  {
      pp = p;
      t = type[p] ;
      if (debug <= 0)
         printf("perfrmc %3d %3d %3d %3d %3d %3d\n",
            p,t,pstart,pend,fr,frame);
      if ((t != stop)&&(t != subrou)&&(t != endsub))
      {
         start = getval(frstart[p]) ;
         if (start < 0)
         {
            ok[0] = 46;
            ok[1] = start;
            ok[2] = vstop;
            nerrs = 3;
         }
         if (ok[0] != 0) goto snag ;
         stp = getval(frstop[p]) ;
         if (stp < start)
         {
           ok[0] = 47 ;
           ok[1] = start ;
           ok[2] = stp ;
           nerrs = 3;
         }
         if (ok[0] != 0) goto snag ;
         if (start == stp) ++stp;
         start *= fast ;
         stp *= fast ;
         if ((stp > frame) && (fr < fend)) ++more;
         if (debug <= 0)
            printf(
               "perfrmd %3d %3d %3d %3d\n",frame,start,stp,more);
         if ((frame > start) && (frame <= stp))
         {
            if (t == call)
            {
               newsub = getval(pf[p][0]);
               if (debug <= 0)
                  printf(
                     "perfrme %3d %3d %3d %3d %3d\n",
                         newsub,distrn[p],frame,start,stp);
               if ((newsub <= 0) || (newsub > EMAX))
               {
                  ok[0] = 8 ;
                  ok[1] = newsub ;
                  nerrs = 2;
                  goto snag ;
               }
               if (distrn[p] == call)
                  perfrm(newsub,frame,start,stp);
               else
                  perfrm(newsub,frame,frame-1,frame);
               if (ok[0] != 0) goto rtrn ;
            }
/*
  if not a subroutine call, then do normal action -
*/
            else
            {
               setfrc(frame,start,stp) ;
               if (debug <= 0)
                  printf(
                     "perfrmf %3d %3d %3d %3d %3d %3d %9g %9g\n",
                     fr,frstart[p],frstop[p],frame,start,stp,frac,prop);
               if (ok[0] != 0) goto snag ;
               setper(t);
               if (ok[0] != 0) goto snag ;
               action(t);
               if (ok[0] != 0) goto snag ;
            }
         }
      }
   }
   goto rtrn ;
/*
  snag-
*/
snag: vstop = frame ;
   ok[nerrs] = p+1 ;
   ok[nerrs+1] = frame ;
   nerrs = nerrs+3;
   printf("\nERROR in prfrm\n");
   for (j = 0; j < nerrs; ++j)
      printf("ok[%d] %d\n",j,ok[j]);

rtrn:;
   if (debug <= 0) printf("perfrm\n");
}  /* perfrm */
/*********************************************/

action(t)
int t;
/*
  decode and do an action t.

  called by perfrm
  calls  doground, domoveby, shift,    dogrofig, dogroell,
         dogrojnt, dospinto, dospinby, dobend,   dobalanc,
         dotouch,  setobs,   setplc,   docola,   enquir,
         doangles, doattach, dodetach, dodrag,   doabut,
         domovjnt, prinel.

*/
{
   double min;
   double doground();

   if (debug <= 0)
      printf("actiona %3d %9g %9g\n",t,frac,prop );
   if (debug < 0) prinel();

   if (t < 7)
   {
       ok[0] = 24 ;
       nerrs = 1;
   }
   if (t == 7)    dobalanc();

   if (t == 8)    doattach();

   if (t == 9)    dodetach();

   if (t == 11)   dogrofig(x[0],x[1],x[2]);

   if (t == 12)   dospinto(x,refell,ang,prop);

   if (t == 13)   domoveby(frac*x[0],frac*x[1],frac*x[2],refell);

   if (t == 14)   val[var0] = x[0]+x[1] ;

   if (t == 15)   dotouch();

   if (t == 17)   dospinby(x,refell,ang[0]*frac,axis) ;

   if (t == 18)
     {
        min = doground();
        shift(doub0,-frac*min,doub0);
     }
   if (t == 19)   dospinby(x,refell,ang[0]*frac,axis) ;

   if (t == 20)   val[var0] = varval ;

   if (t == 21)   dospinto(x,refell,ang,prop);

   if (t == 22)   debug = k;

   if (t == 23)
   {
      ok[0] = 25 ;
      nerrs = 1;
   }
   if (t == 24)
   {
     ok[0] = 26 ;
     nerrs = 1;
   }
   if (t == 25)
   {
       ok[0] = 27 ;
       nerrs = 1;
   }
   if (t == observ)   setobs();

   if (t == 27)   shift(prop*x[0],prop*x[1],prop*x[2]);

   if (t == 31)
   {
      if (val[var0] != doub0) val[var0] = doub1/val[var0];
      else val[var0] = doub0;
   }
   if (t == 34)   dogroell(f, ellpsd, ax3);

   if (t == 35)   dogrojnt();

   if (t == 36)   doangles(ellpsd,refell,val,var0,var1,var2);

   if (t == 37)   enquir(ellpsd,cen) ;

   if (t == flex)   dobend(-ang[0]*frac,0) ;

   if (t == rotate)   dobend(ang[0]*frac,1) ;

   if (t == abduct)   dobend(ang[0]*frac,2) ;

   if (t == 41)   val[var0] = -val[var0] ;

   if (t == 42)   val[var0] = x[0]-x[1] ;

   if (t == 43)
   {
      if (x[1] == doub0)
      {
          ok[0] = 30 ;
          ok[1] = EMAX-var0-1 ;
          nerrs = 2;
      }
      else val[var0] = x[0]/x[1] ;
   }
   if (t == 44)   val[var0] = x[0]*x[1] ;

   if (t == 45)
   {
       ok[0] = 28 ;
       nerrs = 1;
   }
   if (t == 46)
   {
       ok[0] = 29 ;
       nerrs = 1;
   }
   if (t == 47)   setplc() ;

   if (t == 48)   enquir(ellpsd,ax3) ;

   if (t == 49)   enquir(join,jnt) ;

   if (t == 50)   docola(prop);

   if (t == 51)
      fprintf(stderr,"frame %d, %s %9g\n",
         fr,vname[EMAX-var0-1],val[var0]);

   if (t == 52)   docola(doub1);

   if (t == drag)   dodrag();

   if (t == abut) doabut();

   if (t == 56)   domovjnt();

   if ((t <= 0) || (t > nkeys))
   {
      ok[0] = 55;
      nerrs = 1;
   }
   if (debug <= 0)
      printf("actionb %3d %9g %9g\n",t,frac,prop );
}  /* action */
/*********************************************************/

chckpr()
/*
  check parameters for legality

  called by setper
*/
{
   if ((njts > 0)&&((join < 0) || (join > njts))) goto lab12 ;
   if ((axis < 0) || (axis > 2)) goto lab13 ;
   if ((ellpsd < 0) || (ellpsd > nels)) goto lab14 ;
   if ((refell < 0) || (refell > nels)) goto lab15 ;
   if ((ell1 < 0) || (ell1 > nels)) goto lab20 ;
   if ((ell2 < 0) || (ell2 > nels)) goto lab21 ;
   if ((fig < 0) || (fig > nfigs)) goto lab16 ;
   if (nvars <= 0) goto lab10 ;
   if ((var0 < 0) || (var0 >= EMAX)) goto lab17 ;
   if ((var1 < 0) || (var1 >= EMAX)) goto lab18 ;
   if ((var2 < 0) || (var2 >= EMAX)) goto lab19 ;
   if (newcol[0] < -nfiles) goto lab45 ;
   if (newcol[0] <= 0)
   {
      if (newcol[1] < 0) goto lab48 ;
      if (newcol[2] < 0) goto lab49 ;
   }
   goto lab10 ;
/*
  data snag-
*/
lab12: ok[0] = 16 ;
   ok[1] = join ;
   goto lab10 ;

lab13: ok[0] = 17 ;
   ok[1] = axis ;
   goto lab10 ;

lab14: ok[0] = 18 ;
   ok[1] = ellpsd ;
   goto lab10 ;

lab15: ok[0] = 19 ;
   ok[1] = refell ;
   goto lab10 ;

lab16: ok[0] = 20 ;
   ok[1] = fig ;
   goto lab10 ;

lab17: ok[0] = 21 ;
   ok[1] = var0 ;
   goto lab10 ;

lab18: ok[0] = 22 ;
   ok[1] = var1 ;
   goto lab10 ;

lab19: ok[0] = 23 ;
   ok[1] = var2 ;
   goto lab10 ;

lab20: ok[0] = 36 ;
   ok[1] = ell1 ;
   goto lab10 ;

lab21: ok[0] = 37 ;
   ok[1] = ell2 ;
   goto lab10 ;

lab45: ok[0] = 45 ;
   ok[1] = newcol[0] ;
   goto lab10 ;

lab48: ok[0] = 48 ;
   ok[1] = newcol[1] ;
   goto lab10 ;

lab49: ok[0] = 49 ;
   ok[1] = newcol[2] ;

lab10:
   if (ok[0] != 0) nerrs = 2;

}  /* chckpr */
/***************************************/

int getval(p)
   int p;
/*
  get value possibly from array val and put it into v and k.
  if p is negative, get value of variable val(abs(p)),
  if p is positive get p directly.

  called by perfrm, inisub, setper
*/
{
   int k;
   int ref ;

   ref = 0 ;
   if (debug  <=  -1)
      printf("getvala %3d\n",p);
/*
  is the parameter a variable or direct reference
*/
   if (p < 0)
   {
/*
  parameter is index into array val-
*/
      ref = -p ;
      if ((ref < 0) || (ref >= EMAX))
      {
         ok[0] = 15 ;
         ok[1] = ref ;
         nerrs = 2;
      }
      else
      {
         v = val[ref] ;
         k = v+inv2 ;
         if (v < doub0) k = v-inv2 ;
      }
   }
   else
/*
  parameter is direct reference, use it-
*/
   {
      k = p ;
      v = k ;
   }
   if (debug <= 0)
      printf("getvalb %3d %3d %9g\n",ref,k,v );
   return(k);
}  /* getval */
/**************************************/

rotget(r,unr,n)
      int n ;
      double r[3][3],unr[3][3] ;
/*
   form a rotation matrix r and its inverse unr
   from the nth entries in quat

   called by  dobalanc, matrot, dospinto, dospinby,
              dogrojnt, domovjnt, doabut, doground.
*/
{
      int i,j ;
      double cp,sp,x,y,z,m,xsp,ysp,zsp,xm,ym,zm,xym,xzm,yzm ;

      if (debug <= -1)
         printf("rotgeta    %3d %9g %9g %9g %9g %9g\n",
          n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      x = quat[n][0] ;
      y = quat[n][1] ;
      z = quat[n][2] ;
      sp = quat[n][3] ;
      cp = quat[n][4] ;
      m = doub1-cp ;
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
      r[0][2] = xzm-ysp ;
      r[1][0] = xym-zsp ;
      r[1][1] = y*ym+cp ;
      r[1][2] = yzm+xsp ;
      r[2][0] = xzm+ysp ;
      r[2][1] = yzm-xsp ;
      r[2][2] = z*zm+cp ;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         for (  j = 0 ; j < 3 ; ++ j )
         {
            if ((r[j][i] > -tolr) && (r[j][i] < tolr)) r[j][i] = 0;
            unr[i][j] = r[j][i] ;
         }
      }
      if (debug <= -1)
      {
         for (j = 0; j < 3; ++j)
         printf("rotgetb    %3d %9g %9g %9g\n",
          n,r[j][0],r[j][1],r[j][2]);
      }
}  /* rotget */
/**************************************/

rotput(r,n)
      int n ;
      double r[3][3] ;
/*
   interpret rotation matrix 'r' as direction cosines of a
   rotation axis, and the sine and cosine of a rotation about
   that axis, and store in array 'quat'.

   uses the fact that any rotation matrix can be written as -

   ( x.x.m+c    x.y.m-z.s  x.z.m+y.s )
   ( x.y.m+z.s  y.y.m+c    y.z.m-x.s )
   ( x.z.m-y.s  y.z.m+x.s  z.z.m+c   )

   where
     x,y,z-components of unit vector along rotation axis
             x=cos(a1)cos(a2)  y=cos(a1)sin(a2)  z=sin(a1)
             a1,a2-azimuth and elevation of axis from x axis
     s,c  -sine and cosine of rotation about that axis
     m     = 1-c

     x,y,z are stored in quat[n,0], quat[n,1], quat[n,2]
     s,c   are stored in quat[n,3], quat[n,4]

   see 'control of round-off propagation in articulating the
        human figure', D.Herbison-Evans and D.S.Richardson
        computer graphics and image processing,
        vol 17 pp 386-393 (1981)

   called by matrot, dospinto, doangles, dolimb,
             getwist, store3.
*/
{
      int j,k ;
      double a[3][3],b[3],d[3],e,f,g,c,s,trace ;
      double csq;
      double acc = {0.000002} ;

      if (debug <= -1)
         printf("rotputa %3d\n",n);
      if (debug <= 0)
      {
         for (k = 0; k < 3; ++k)
            printf("      %9g %9g %9g\n",
               r[k][0],r[k][1],r[k][2]);
      }
      b[0] = r[1][2]-r[2][1] ;
      b[1] = r[2][0]-r[0][2] ;
      b[2] = r[0][1]-r[1][0] ;
      e = b[0]*b[0]+b[1]*b[1]+b[2]*b[2] ;
      trace = r[0][0]+r[1][1]+r[2][2] ;
      if (e > doub0) g = sqrt(e); else g = doub0;
      if (debug <= -1)
           printf("rotputb %9g %9g %9g %9g\n",
               trace,g,e,acc);
      if (e > acc)
      {
         f = doub1/g ;
         quat[n][0] = f*b[0] ;
         quat[n][1] = f*b[1] ;
         quat[n][2] = f*b[2] ;

         if (debug <= -1)
            printf("rotputc %3d %9g %9g %9g %9g\n",
                            debug,f,b[0],b[1],b[2]);
/*
     use g=2s, and trace=1+2c to find s and c -
*/
         s = inv2*g;
         csq = doub1-s*s;
         if (csq > doub0) c = sqrt(csq); else c = doub0;
         if (trace < doub1) c = -c;
         if (debug <= -1) printf("rotputd %9g %9g\n",s,c);
         quat[n][3] = s ;
         quat[n][4] = c ;
      }
      else
/*
   symmetric matrix (180 or 360 degree rotation) -
*/
      {
         if (debug <= -1)
         {
            printf(
               "rotpute symmetric matrix, action %d, ellipsoid %d\n",
                   pp,n);
            printf("   trace %9g, g %9g, e %9g, acc %9g\n",
                   trace,g,e,acc);
            for (k = 0; k < 3; ++k)
               printf("         %9g %9g %9g\n",
                   r[k][0],r[k][1],r[k][2]);
         }
         c = inv2*(trace-doub1);
         for (  j = 0 ; j < 3 ; ++ j )
         {
            d[j] = doub0 ;

/*   run across a row- */

            for (  k = 0 ; k < 3 ; ++ k )
            {
               a[j][k] = r[j][k]+r[k][j] ;
               if (j == k) a[j][j] = doub2*(r[j][j]-c) ;
               d[j] = d[j]+a[j][k]*a[j][k] ;
            }
            if (debug <= -1)
               printf("rotputf %3d %9g %9g %9g %9g\n",
                               j,a[j][0],a[j][1],a[j][2],d[j]);
         }

/*   choose most stable row- */

         j = 0 ;
         if (d[1] > d[0]) j = 1 ;
         if (d[2] > d[j]) j = 2 ;
         if (d[j] > doub0) f = doub1/sqrt(d[j]) ;
         else
         {
            f = doub1;
            a[j][0] = doub1;
         }
         quat[n][0] = f*a[j][0] ;
         quat[n][1] = f*a[j][1] ;
         quat[n][2] = f*a[j][2] ;
         quat[n][3] = inv2*g ;
         quat[n][4] = c ;
         if (debug <= -1)
            printf("rotputg %3d %9g %9g %9g %9g %9g %9g\n",
                               j,a[j][0],a[j][1],a[j][2],d[j],f,g);
      }
      if (debug <= -1)
          printf("rotputh    %3d %9g %9g %9g %9g %9g\n",
              n,quat[n][0],quat[n][1],quat[n][2],
              quat[n][3],quat[n][4]);
      for (k = 0; k < 5; ++k)
      {
         if ((quat[n][k] > -tolr) && (quat[n][k] < tolr))
            quat[n][k] = 0;
         if (quat[n][k] >  doub1) quat[n][k] =  doub1;
         if (quat[n][k] < -doub1) quat[n][k] = -doub1;
      }
}  /* rotput */
/********************************************/

dospinto(x,refell,ang,pro)
double x[3],ang[3],pro;
int refell;
/*
     spins all ellipsoids in 'elist' and joints in 'jlist'
     so that 'ellpsd' is proportion 'pro' of the way to the
     orientation specified as a rotation 'ang' radians
     about axes of the reference ellipsoid 'refell'
     about point 'x'.

   called by  action.
   calls      rotget, rotput, mkquat, matmul, twirl.
*/
{
      int k;
      double alfa,nualfa ;
      double mv[3][3],unmv[3][3];
      double rf[3][3],unrf[3][3];
      double tg[3][3],untg[3][3] ;
      double mt[3][3],nu[3][3] ;

      if (debug < 1 )
      {
         printf("dospintoa %9g %9g %9g %9g\n",
            ang[0],ang[1],ang[2],pro);
         printf("       %3d %3d %3d %9g %9g %9g\n",
            ecount,jcount,refell,x[0],x[1],x[2]);
      }
/*
   set rotation matrices of moving and reference ellipsoids -
*/
      rotget(mv,unmv,ellpsd) ;
      rotget(rf,unrf,refell) ;

/*   find target rotation matrix, and refer to refell- */

      mkquat(EMAX+1,ang[0],ang[1],ang[2]) ;
      if (debug < 1)
      {
         k = EMAX+1;
         printf("dospinto mkquat %9g %9g %9g %9g %9g\n",
            quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      rotget(tg,untg,EMAX+1) ;
      if (debug < 1)
      {
         printf("dospinto tg\n");
         for (k = 0; k < 3; ++k)
            printf("   %9g %9g %9g\n",
              tg[k][0],tg[k][1],tg[k][2]);
         printf("dospinto rf\n");
         for (k = 0; k < 3; ++k)
            printf("   %9g %9g %9g\n",
              rf[k][0],rf[k][1],rf[k][2]);
         printf("dospinto unmv\n");
         for (k = 0; k < 3; ++k)
            printf("   %9g %9g %9g\n",
              unmv[k][0],unmv[k][1],unmv[k][2]);
      }
      matmul(rf,tg,tg) ;

/*   find increment rotation matrix to reach target- */

      matmul(tg,unmv,mt) ;
      rotput(mt,EMAX+1) ;
      if (debug < 1)
         printf("dospinto atan2 %9g %9g\n",
            quat[EMAX+1][3],quat[EMAX+1][4]);
      if (( quat[EMAX+1][3] == doub0 ) && ( quat[EMAX+1][4] == doub0 ))
      {
         ok[0] = 53;
         nerrs = 1;
         alfa = doub0;
      }
      else alfa = atan2(quat[EMAX+1][3],quat[EMAX+1][4]) ;
      nualfa = pro*alfa ;
      if (alfa > pi ) nualfa = pro*(alfa - twopi);
      if (alfa < -pi) nualfa = pro*(alfa + twopi);
      if (debug < 1)
         printf("dospintob %9g %9g %9g %9g\n",
            quat[EMAX+1][3],quat[EMAX+1][4],alfa,nualfa);
      quat[EMAX+1][3] = sin(nualfa) ;
      quat[EMAX+1][4] = cos(nualfa) ;
      rotget(nu,mt,EMAX+1) ;
      if (debug < 1)
      {
         k = ellpsd;
         printf("dospintoc %9g %9g %9g %9g %9g %9g\n",
            nu[0][0],quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      twirl(x[0],x[1],x[2],nu) ;
      if (debug < 1)
      {
         k = ellpsd;
         printf("dospintod %9g %9g %9g %9g %9g\n",
            quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
}  /* dospinto */
/*************************************/

dospinby(x,refell,angl,axis)
      int refell,axis ;
      double angl ;
      double x[3];
/*
   spins all ellipsoids and joints in 'elist' and 'jlist'
   about a point 'x', by an angle 'angl' radians relative to
   an 'axis' of reference ellipsoid 'refell'.

   called by   dobalanc, action, dobend, dotouch, fun, dodrag.
   calls       rset, rotget, matmul, twirl.
*/
{
      int j,k;
      double r[3][3],ro[3][3],unro[3][3] ;
/*
        do transformation on required coordinates
        aligned with axes of the reference ellipsoid-
*/
      if (debug <= 0)
      {
         k = elist[0];
         printf(
           "dospinbya %3d %9g %3d %3d %9g %9g %9g %9g %9g\n",
           refell,angl,axis,k,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      rset(r,angl,axis) ;
      if (debug <= 0)
      {
         k = elist[0];
         printf(
           "dospinbyb %3d %9g %3d %3d %9g %9g %9g %9g %9g\n",
           refell,angl,axis,k,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      rotget(ro,unro,refell) ;
      if (debug <= 0)
      {
         k = elist[0];
         printf(
           "dospinbyc %3d %9g %3d %3d %9g %9g %9g %9g %9g\n",
           refell,angl,axis,k,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      matmul(r,unro,r) ;
      matmul(ro,r,r) ;
      for (j = 0; j < 3; ++j)
         for (k = 0; k < 3; ++k)
            if ((r[j][k] > -tolr) && (r[j][k] < tolr)) r[j][k] = 0;
      twirl(x[0],x[1],x[2],r) ;
      if (debug <= 0)
      {
         k = elist[0];
         printf(
           "dospinbyd %3d %9g %3d %3d %9g %9g %9g %9g %9g\n",
           refell,angl,axis,k,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
}  /* dospinby */
/**********************************************************/

twirl(x,y,z,r)
      double x,y,z ;
      double r[3][3] ;
/*
   rotates all the rotation matrices 'quat', centres 'cen',
   and joint vectors 'jnt', of ellipsoids and joints in lists
   'elist' and 'jlist' about a point 'x,y,z' using rotation
   matrix 'r'.

   called by  dospinto, dospinby.
   calls      shift, matrot, vecmul.
*/
{
      double ra[3][3],rb[3][3];
      int i,k ;

      if (debug <= 0) printf("twirla %3d %3d\n",
         ecount,jcount);
      shift(-x,-y,-z) ;
      if (debug <= -1)
      {
         printf("twirlb\n");
         for (i = 0; i < 3; ++i)
            printf("   %9g %9g %9g\n",
               r[0][i],r[1][i],r[2][i]);
      }
      if (ecount >= 0)
      {

/*   rotate the ellipsoids and their centres- */

         for (  i = 0 ; i < ecount ; ++ i )
         {
            k = elist[i];
/*  don't rotate world ! :- */
            if (k != 0)
            {
               if (debug <= -1)
                  printf("twirld %3d %3d %9g %9g %9g\n",
                  i,k,cen[k][0],cen[k][1],cen[k][2]);
               matrot(r,k) ;
               vecmul(cen,r,k) ;
               if (debug <= -1)
                  printf("twirle %3d %3d %9g %9g %9g\n",
                  i,k,cen[k][0],cen[k][1],cen[k][2]);
            }
         }
      }
/*   now for the joints- */

      if (jcount >= 0)
      {
         for (  i = 0 ; i < jcount ; ++ i )
         {
            k = jlist[i];
            vecmul(jnt,r,k) ;
            if (debug <= -1)
               printf("twirlf %3d %3d %9g %9g %9g\n",
               i,k,jnt[k][0],jnt[k][1],jnt[k][2]);
         }
      }
/*   put body part back where it came from- */

      shift(x,y,z) ;
}  /* twirl */
/*****************************/

matmul(a,b,ans)
      double a[3][3],b[3][3],ans[3][3] ;
/*
     this multiplies matrix 'b' by 'a' and puts the product
     in 'ans'.

     called by  dobalanc, matrot, dospinto, dospinby, getwist.
                getaxes, sepn,  getmat.
*/
{
      int i,j,k ;
      double x,c[3][3] ;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         for (  j = 0 ; j < 3 ; ++ j )
         {
            x=doub0 ;
            for (  k = 0 ; k < 3 ; ++ k )
            {
               x=x+a[i][k]*b[k][j] ;
            }
            c[i][j]=x ;
         }
      }

      for (  i = 0 ; i < 3 ; ++ i )
      {
         for (  j = 0 ; j < 3 ; ++ j )
         {
            ans[i][j]=c[i][j] ;
         }
      }
}  /* matmul */
/**********************************************************/

matrot(r,n)
      int n ;
      double r[3][3] ;
/*
      this rotates the 'n'th ellipsoid by rotation matrix 'r'.

      called by twirl.
      calls     rotget, matmul, rotput.
*/
{
      double ro[3][3],unro[3][3] ;

      if (debug <= 0) printf("matrota    %3d %9g %9g %9g %9g %9g\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      rotget(ro,unro,n) ;
      if (debug < 0) printf("matrotb    %3d %9g %9g %9g %9g %9g\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      matmul(r,ro,ro) ;
      rotput(ro,n) ;
      if (debug < 0) printf("matrotc    %3d %9g %9g %9g %9g %9g\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
}  /* matrot */
/**********************************************/

vecmul(v,m,n)
      int n ;
      double m[3][3] ;
      double v[EMAX][3] ;
/*
   multiply the 'n'th vector from array 'v'
   by matrix 'm'.

   called by  dogrojnt, domovjnt, domoveby, doabut, twirl.
*/
{
      int i,j ;
      double vv[3],x ;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         x = doub0 ;
         for (  j = 0 ; j < 3 ; ++ j )
         {
            x = x+m[i][j]*v[n][j] ;
         }
         vv[i] = x ;
      }

      for (  i = 0 ; i < 3 ; ++ i )
      {
         v[n][i] = vv[i] ;
      }
}  /* vecmul */
/**********************************************/

vecmat(v,m,w)
      double m[3][3] ;
      double v[3],w[3];
/*
   multiply vector 'v' by matrix 'm',
   putting result in 'w'.

   called by  sepn, dobalanc.
*/
{
      int i,j ;
      double vv[3],x ;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         x = doub0 ;
         for (  j = 0 ; j < 3 ; ++ j )
         {
            x = x+m[i][j]*v[j] ;
         }
         vv[i] = x ;
      }
      for (  i = 0 ; i < 3 ; ++ i )
      {
         w[i] = vv[i] ;
      }
}  /* vecmat */
/**********************************************************/

mkang(n)
      int n ;
/*
   get angles from 'n'th entry in 'quat' into array 'ang'.

   called by  doangles, store3.
*/
{
      double x,y,z,s1,c1,m1 ;
      int j;

      x = quat[n][0] ;
      y = quat[n][1] ;
      z = quat[n][2] ;
      s1 = z ;
      m1 = doub1-z*z ;
      if (m1 > doub0) c1 = sqrt(m1) ;
         else c1 = doub0 ;
      if ((x == doub0 ) && ( y == doub0))
          ang[0] = doub0;
             else ang[0] = atan2(y,x) ;
      if ((s1 == doub0 ) && ( c1 == doub0))
      {
          ok[0] = 54;
          ok[1] = n;
          nerrs = 2;
          ang[1] = doub0;
      }
      else ang[1] = atan2(s1,c1) ;
      if ((quat[n][3] == doub0 ) && ( quat[n][4] == doub0))
      {
          ok[0] = 52;
          ok[1] = n;
          nerrs = 2;
          ang[2] = doub0;
      }
      else ang[2] = atan2(quat[n][3],quat[n][4]) ;
      for (j = 0; j < 3; ++j)
         if (ang[j] < doub0) ang[j] += twopi;
      if (debug <= -1)
      {
         printf("atan2 %9g %9g %9g %9g %9g %9g\n",
            y,x,s1,c1,quat[n][3],quat[n][4]);
         printf("mkang %3d %9g %9g %9g\n",
                    n,ang[0],ang[1],ang[2]);
      }
}  /* mkang */
/*****************************************/

shift(x,y,z)
      double x,y,z ;
/*
   this adds 'x,y,z' to all centres and joints in lists
   'elist' and 'jlist'.

   called by  action, dogrofig, dogrojt, domovjnt, twirl, dodrag;
*/
{
      int j,n ;

      if (debug <= 0)
         printf("shifta %3d %3d %9g %9g %9g\n",
            ecount,jcount,x,y,z);
      for (  n = 0 ; n < ecount ; ++ n )
      {
         j = elist[n] ;
         cen[j][0] = cen[j][0]+x ;
         cen[j][1] = cen[j][1]+y ;
         cen[j][2] = cen[j][2]+z ;
      }
      for (  n = 0 ; n < jcount ; ++ n )
      {
         j = jlist[n] ;
         jnt[j][0] = jnt[j][0]+x ;
         jnt[j][1] = jnt[j][1]+y ;
         jnt[j][2] = jnt[j][2]+z ;
      }
}  /* shift */
/*****************************/

rset(r,angl,axis)
      int axis ;
      double angl,r[3][3] ;
/*
   set up the rotation matrix 'r' for a rotation of
   'angl' radians about 'axis'.

   called by  input, setobs, dobalanc, dospinby.
*/
{
      double v[5] ;
      int i,j,k;

      if (debug <= 0) printf("rset %3d %9g\n",axis,angl);
      v[0] = doub0 ;
      v[1] = doub1 ;

/*   fill out values vector with sin and cos- */

      v[2] = cos(angl) ;
      v[3] = sin(angl) ;
      v[4] = -v[3] ;

/*   choose appropriate permutation of values for rotation axis- */

      for (  i = 0 ; i < 3 ; ++ i )
      {
         for (  j = 0 ; j < 3 ; ++ j )
         {
            k = perm[axis][j][i] ;
            r[i][j] = v[k-1] ;
         }
      }
}  /* rset */
/************************************/

mkquat(n,a1,a2,a3)
      int n ;
      double a1,a2,a3 ;
/*
   convert angles a1,a2,a3 (in radians) into quat entries

   called by dospinto
*/
{
      int j;
      double s1,c1,s2,c2,s3,c3 ;

      if (debug <= 0) printf("mkquata %9d %9g %9g %9g\n",n,a1,a2,a3);
      if (debug <= 0)
         printf("mkquatb %9g %9g %9g %9g %9g\n",
             quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
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
      for (j = 0; j < 5; ++j)
         if ((quat[n][j] > -tolr) && (quat[n][j] < tolr)) quat[n][j] = 0;
      if (debug <= 0)
         printf("mkquatc %9g %9g %9g %9g %9g\n",
             quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
}  /* mkquat */
/**********************************************************/

double doground()
/*
   find distance of lowest point above the ground
   of the ellipsoids contained in 'elist'.

   called by  action, dodrag, fun.
   calls      rotget.
*/
{
   int i,n ;
   double toty,x,y,z,r[3][3],unr[3][3] ;
   double val;
   double sq;
   double sqt;
   double rr[3][3],tmp[3][3];
   double r1[3][3],r2[3][3],r3[3][3] ;


   if (debug <= 0)
      printf("dogrounda %3d %3d\n",ecount,jcount);
   val = cen[elist[0]][1];

/*   run through affected ellipsoids finding lowest point- */

   if (ecount < 1)
   {
      ok[0] = 38 ;
      nerrs = 1;
   }
   else
   {
      for (  n = 0 ; n < ecount ; ++ n )
      {
         i = elist[n] ;
         rotget(r,unr,i) ;
         x = unr[0][1]*ax3[i][0] ;
         y = unr[1][1]*ax3[i][1] ;
         z = unr[2][1]*ax3[i][2] ;
	 sq = x*x+y*y+z*z;
         if (sq > doub0) sqt = sqrt(sq); else sqt = doub0;
	 toty = cen[i][1] - sqt ;
         if (toty < val) val = toty ;
         if (debug <= 0)
         {
            printf(
               "dogroundb %3d %9g %9g %9g %9g %9g %9g\n",
            i,ax3[i][0],ax3[i][1],ax3[i][2],unr[0][1],unr[1][1],unr[2][1]);
            printf("    %9g %9g %9g %9g %9g\n",
            x,y,z,cen[i][1],toty);
         }
      }
   }
   return(val);
}  /* doground */
/**********************************************************/

setels(ellpsd,jthis)
      int ellpsd,jthis;
/*
     puts into 'elist' and 'jlist' those ellipsoids and joints
     (if any) connected to 'ellpsd'
     (including 'ellpsd' and 'jthis')
     except those connected through joint 'jthis'

     if 'jthis' is negative, puts all joints and ellipsoids
     connected to 'ellpsd' into lists.
     if 'ellpsd' is zero, puts all joints and ellipsoids into lists,
     except ellipsoid zero (world).

     'ecount' is the number of ellipsoids in the list 'elist'.
     'jcount' is the number of joints in the list 'jlist'.

     called by  setper, findfg, dodetach, dogrojnt, dodrag,
                fun.
*/
{
      int all;
      int e,j,i,jt ;

      if (debug <= 0)
         printf("setelsa %3d %3d\n",ellpsd,jthis);
      if (ellpsd <= 0) goto lab6 ;

      all = -1;
      ecount = 1 ;
      elist[0] = ellpsd ;
      if (jthis < 0)
      {
         for (j = 0; j < njts; ++j)
         {
            if (coel[j][0] == ellpsd)
            {
               jthis = j;
               all = 1;
            }
            if (coel[j][1] == ellpsd)
            {
               jthis = j;
               all = 0;
            }
         }
      }
      jcount = 0 ;

      if ((njts <= 0)||(jthis < 0)) goto rtrn ;
      if ((coel[jthis][0] != ellpsd) && (coel[jthis][1] != ellpsd))
      {
          ok[0] = 50;
          ok[1] = ellpsd;
          ok[2] = jthis;
          ok[3] = coel[jthis][0];
          ok[4] = coel[jthis][1];
          nerrs = 5;
          goto rtrn;
      }
      jcount = 1 ;
      jlist[0] = jthis ;

again:  for (  e = 0 ; e < ecount ; ++ e )
      {

/*   seek joint not in jlist but connected to ellipsoid elist[e]- */

         for (  jt = 0 ; jt < njts ; ++ jt )
         {
            if (jcount > 0)
            {
               for (  j = 0 ; j < jcount ; ++ j )
               {
                  if (jt == jlist[j]) goto lab3 ;
               }
            }
/*
   jt not in list yet-
*/
            i =  -1 ;
            if (coel[jt][0] == elist[e]) i = 1 ;
            if (coel[jt][1] == elist[e]) i = 0 ;
            if (i < 0) goto lab3 ;

/*   store new joint and ellipsoid- */

            if (debug < 0)
               printf(
                  "setelsb %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",
                  e,elist[e],jt,i,ecount,jcount,
                  coel[jt][0],coel[jt][1],all);
            jlist[jcount] = jt ;
            jcount ++;
            elist[ecount] = coel[jt][i] ;
            ecount ++;
lab3: ;
         }
         if (e >= ecount-1)
         {
            if (all < 0) goto rtrn;
            else
            {
               ellpsd = coel[jthis][all];
               elist[ecount] = ellpsd;
               ecount ++;
               all = -1;
               goto again;
            }
         }
     }

/*   set all ellipsoids and joints- */

lab6: jcount = 0 ;

/*   all joints with non-null connections- */

      jcount = 0;
      for (  j = 0 ; j < njts ; ++ j )
      {
         if (coel[j][0] >= 0)
         {
            ++ jcount;
            jlist[jcount-1] = j ;
         }
      }

/*   all ellipsoids- */

      ecount = nels-1 ;
      for (  e = 0 ; e < ecount ; ++ e )
      {
         elist[e] = e+1 ;
      }

rtrn: if (debug <= 0)
      {
         printf("setelsc %3d %3d %3d %3d\n",
            ellpsd,jthis,ecount,jcount);
         printf("   elist");
         for (e = 0; e < ecount; ++e)
            printf(" %3d", elist[e]);
         printf("\n");
         printf("   jlist");
         for (j = 0; j<jcount; ++j)
            printf(" %3d",jlist[j]);
         printf("\n");
      }
}  /* setels */
/*************************************************/

setjnt(ellpsd,jthis)
      int ellpsd,jthis;
/*
     puts into 'elist' and 'jlist' those ellipsoids and joints
     (if any) connected to 'ellpsd'
     (including 'ellpsd' and excluding 'jthis')
     except those connected through joint 'jthis'

     'ecount' is the number of ellipsoids in the list elist.
     'jcount' is the number of joints in the list jlist.

     called by  domovjnt
*/
{
      int done;
      int ell;
      int e,j,i,jt ;

      if (debug <= 0)
         printf("setjnta %3d %3d\n",ellpsd,jthis);
      ecount = 1 ;
      elist[0] = ellpsd ;
      jcount = 0 ;
      if ((coel[jthis][0] != ellpsd) && (coel[jthis][1] != ellpsd))
      {
          ok[0] = 64;
          ok[1] = ellpsd;
          ok[2] = jthis;
          ok[3] = coel[jthis][0];
          ok[4] = coel[jthis][1];
          nerrs = 5;
          goto rtrn;
      }

again:  for (  e = 0 ; e < ecount ; ++ e )
      {
         done = TRUE;

/*   seek joint not in jlist but connected to ellipsoid elist[e]- */

         for (  jt = 0 ; jt < njts ; ++ jt )
         {
            if (jt == jthis) goto lab3;
            if (jcount > 0)
            {
               for (  j = 0 ; j < jcount ; ++ j )
               {
                  if (jt == jlist[j]) goto lab3 ;
               }
            }
/*
   jt not in list yet-
*/
            i =  -1 ;
            if (coel[jt][0] == elist[e]) i = 1 ;
            if (coel[jt][1] == elist[e]) i = 0 ;
            if (debug <= 0)
               printf(
                  "setjntb %3d %3d %3d %3d %3d %3d %3d %3d\n",
                  e,elist[e],jt,i,ecount,jcount,coel[jt][0],coel[jt][1]);
            if (i < 0) goto lab3 ;

/*   store new joint and ellipsoid- */

            jlist[jcount] = jt ;
            jcount ++;
            elist[ecount] = coel[jt][i] ;
            ecount ++;
            done = FALSE;
lab3: ;
         }
         if (done == FALSE) goto again;
     }
rtrn:;
     if (debug <= 0)
     {
         printf("setjntc %d %d\n",ecount,jcount);
         for (e = 0; e < ecount; ++e)
            printf(" %3d", elist[e]);
         printf("\n");
         for (j = 0; j < jcount; ++j)
            printf(" %3d",jlist[j]);
         printf("\n");
      }
}  /* setjnt */
/*************************************************/

setfrc(frame,start,stp)
int frame,start,stp;
/*
  set up prop and frac -  proportion of current action time
  to be done for current frame.

  variables -
     a - number of frames done of current action
     aa - number of increments of current action done
     b - number of frames to be done
     bb - number of increments of current action to be done
     even  - 0 if n is even, 1 if n is odd
     nn - total number of increments in current action

  called by perfrm
*/
{
   double a,aa,b,bb,h,n,nn,even;
   int distrp ;

   distrp = distrn[pp];
   if (debug < 1)
      printf(
         "setfrca %3d %3d %3d %3d %3d\n",fr,frame,start,stp,distrp);
   n = stp-start ;
   nn = n*(n+doub1)*inv2 ;
   a = frame-start ;
   aa = a*(a+doub1)*inv2 ;
   b = stp-frame+1 ;
   bb = b*(b+doub1)*inv2 ;
   even = ((int)n)%2 ;
   h = ((int)n)/2 ;
/*
  repeat command-
*/
   if (distrp == repeat)
   {
      prop = doub1 ;
      frac = doub1 ;
   }
   else
/*
  linear command-
*/
   if (distrp == linear)
   {
      if ((b  == doub0) || (n == doub0))
      {
         ok[0] = 10 ;
         ok[1] = start ;
      }
      else
      {
         frac = doub1/n;
         prop = doub1/b;
      }
   }
   else
/*
  acceleration command-
*/
   if (distrp == accele)
   {
      if ((nn == doub0) || ((nn-aa+a) == doub0))
      {
         ok[0] = 11 ;
         ok[1] = start ;
      }
      else
      {
         frac = a/nn ;
         prop = a/(nn-aa+a) ;
      }
   }
   else
/*
  deceleration command-
*/
   if (distrp == decele)
   {
      if ((nn == doub0) || (bb == doub0))
      {
         ok[0] = 12 ;
         ok[1] = start ;
      }
      else
      {
         frac = b/nn ;
         prop = b/bb ;
      }
   }
   else
/*
  quadratic command-
*/
   if (distrp == quadra)
   {
      nn = (n*(n+doub2)+even)/doub4 ;
      if (nn == doub0)
      {
         ok[0] = 13 ;
         ok[1] = start ;
      }
      else
      {
         frac = a/nn;
         if (a >= b) frac = b/nn ;
      }
      if (bb == doub0)
      {
         ok[0] = 13 ;
         ok[1] = start ;
      }
      prop = b/bb ;
      if (a < b)
      {
         if ((nn-aa+a) == doub0)
         {
            ok[0] = 13 ;
            ok[1] = start ;
         }
         prop = a/(nn-aa+a) ;
      }
   }
   else
/*
   cubic command-
*/
   if (distrp == cubic)
   {
      nn = h*(h+doub1)*(doub2*h+doub1)*inv3 + even*(h+doub1)*(h+doub1);
      aa = a*(a+doub1)*(doub2*a+doub1)*inv6;
      bb = b*(b+doub1)*(doub2*b+doub1)*inv6;
      if ( a < b )
      {
         if (nn > doub0) frac = a*a/nn; else frac = doub1;
         if ((nn-aa+a*a) > doub0) prop = a*a/(nn-aa+a*a); else prop = doub1;
      }
      else
      {
         if (nn > doub0) frac = b*b/nn; else frac = doub1;
         if (bb > doub0) prop = b*b/bb; else prop = doub1;
      }
   }
   if (ok[0] != 0) nerrs = 2;
   if (debug < 1)
         printf(
           "setfrcb %9g %9g %9g %9g %9g %9g %9g %9g %9g %9g\n",
             frac,prop,n,a,b,nn,even,h,aa,bb);
} /* setfrc */
/************************************************************/

setper(t)
int t;
/*
  decodes the parameters of the 'pp'th action using -

     0 - none
     1 - x
     2 - y
     3 - z
     4 - ang1
     5 - ang2
     6 - ang3
     7 - x scaling factor
     8 - y scaling factor
     9 - z scaling factor
    10 - value for a variable
    11,12,13 - red, green and blue colour coords
    14 - the debug parameter
    15 - reference to a file name in list 'fname'
    21 - axis
    22 - joint
    23 - reference ellipsoid
    24 - ellpsd (moving or central ellipsoid)
    25 - fig  (figure)
    27,28,29 - var0,var1,var2 (references to variables)
    30 - ell1 (ellipsoid to touch)
    31 - ell2 (ellipsoid to be touched)

  called by perfrm
  calls  getval, chckpr, findfg, setels
*/
{
   double scale();
   int findfg(),getval();
   int c,j ;
   int fg = 25;

   if ((t < 1) || (t > nkeys))
   {
       ok[0] = 14 ;
       nerrs = 1;
       goto rtrn;
   }
/*
  run thru parameters of 'p'th action-
*/
   for (  j = 0 ; j < 6 ; ++ j )
   {
      c = code[j][t] ;
      if (debug <= 0)
         printf("setpera %3d %3d %3d %3d %3d\n",
            pp,t,j,pf[pp][j],c );
      if (c != 0)
      {
         k = getval(pf[pp][j]) ;
         if (debug <= 0)
            printf("setperb %3d %3d %9g %9g %9g %9g %9g\n",
               ok[0],k,v,frac,f[0],f[1],f[2]);
         if (ok[0] != 0) goto rtrn ;
/*
  set double parameters -
*/
         if (c == 1) x[0] = v ;
         if (c == 2) x[1] = v ;
         if (c == 3) x[2] = v ;
         if (c == 4) ang[0] = v*radian ;
         if (c == 5) ang[1] = v*radian ;
         if (c == 6) ang[2] = v*radian ;
         if (c == 7) f[0] = scale(v);
         if (c == 8) f[1] = scale(v);
         if (c == 9) f[2] = scale(v);
         if (c == 10) varval = v ;
/*
  set int parameters-
*/
         if (c == 11) newcol[0] = k ;
         if (c == 12) newcol[1] = k ;
         if (c == 13) newcol[2] = k ;
         if (c == 14) debug = k ;
         if (c == 21) axis = k ;
         if (c == 22) join = k ;
         if (c == 23) refell = k ;
         if (c == 24) ellpsd = k ;
         if (c == 25) fig = k ;
         if (c == 27) var0 = EMAX-k-1 ;
         if (c == 28) var1 = EMAX-k-1 ;
         if (c == 29) var2 = EMAX-k-1 ;
         if (c == 30)
         {
            ell1 = k ;
            ellpsd = k ;
         }
         if (c == 31) ell2 = k ;
      }
   }
/*
  check for errors-
*/
   chckpr();
   if (ok[0] != 0) goto rtrn ;
/*
  if appropriate, set up lists of ellipsoids and joints
  in affected figures ( NB figell[all] is -1)  -
*/
   if (t == drag)
   {
      if (ellpsd == coel[join][0]) refell = coel[join][1];
         else refell = coel[join][0];
   }
   if (code[0][t] == fg)
   {
      setels(figell[fig],-1);
      if (ok[0] != 0) goto rtrn;
   }
   if ((t == rotate) || (t == abduct)
         || (t == drag ) || (t == abut))
   {
      fig = findfg(ellpsd);
      if (ok[0] != 0) goto rtrn;
   }
   if (t == abut)
   {
      setels(ellpsd,-1);
      if (ok[0] != 0) goto rtrn;
   }
   else if ((t == balanc) || (t == touch) || (t == bendby)
          || (t == bendto) || (t == flex) || (t == rotate)
          || (t == abduct) || (t == drag) || (t == linkx))
   {
      if (t != linkx) setels(ellpsd,join);
      if (ok[0] != 0) goto rtrn;
      x[0] = jnt[join][0] ;
      x[1] = jnt[join][1] ;
      x[2] = jnt[join][2] ;
   }
   if ((t == grofig) || (t == spinto) || (t == spinby)
    || (t == centre))
   {
      x[0] = cen[ellpsd][0] ;
      x[1] = cen[ellpsd][1] ;
      x[2] = cen[ellpsd][2] ;
   }
   else if (t == moveto)
   {
      x[0] = x[0]-cen[ellpsd][0] ;
      x[1] = x[1]-cen[ellpsd][1] ;
      x[2] = x[2]-cen[ellpsd][2] ;
   }

rtrn:
   if (debug <= 0)
   {
      printf("setperc %3d %3d %9g %3d %3d %3d %3d\n",
         pp,t,varval,ecount,jcount,elist[0],jlist[0]);
      printf(
         "          %9g %9g %9g %9g %9g %9g\n       %9g %9g %9g\n",
         f[0],f[1],f[2],x[0],x[1],x[2],ang[0],ang[1],ang[2]) ;
      printf("          %3d %3d %3d %3d %3d %3d %3d %3d\n",
         axis,ellpsd,refell,join,fig,var0,var1,var2);
   }
}  /* setper */
/****************************************************/

double scale(x)
double x;
/*
   scale x by proportion frac

   called by setper.
*/
{
   double v1,v2,v3,v4,v5;

   if (x == doub0)
   {
      ok[0] = 51;
      nerrs = 1;
      v5 = doub0;
   }
   else
   {
      if (x > doub0) v1= x; else v1 = -x;
      if ( v1 > doub0) v2 = log(v1); else v2 = doub0;
      v3 = frac*v2;
      v4 = exp(v3);
      if (x > doub0) v5 = v4; else v5 = -v4;
   }
   if (debug <= 0)
      printf("scale %9g %9g %9g %9g %9g %9g\n",x,v1,v2,v3,v4,v5);
   return(v5);
}  /* scale */
/***************************************/

double sqr(x)
double x;
/*
   called by   surf, angsepn.
*/
{
   return(x*x);
}  /* sqr */
/*******************************************************/

store3(frame)
int frame;
/*
    print out axes, centres, orientations and colours
    of  nels ellipsoids starting at 1 (avoiding  0 = world),
    and the joints too.

    called by main, doframes.
    calls  setels, dospinby, ipr, mkang, rotput.
*/
{
   int   j,k;

   if (debug <= 0)
      printf("store3a %3d %3d %3d\n",frame,nels,njts);
   rotput(obs,nels+1);
   mkang(nels+1);
   printf("%d %d ",nels-1,frame);
   ipr(doub10*pplace[0]);
   ipr(doub10*pplace[1]);
   ipr(doub10*pplace[2]);
   ipr(doub10*ang[0]*degree);
   ipr(doub10*ang[1]*degree);
   ipr(doub10*ang[2]*degree);
   printf("\n");
/*
   print out the ellipsoid details -
*/
   if (nels > 1)
   {
      for (j = 1; j < nels; j++)
      {
         mkang(j);
         if (debug <= -1)
            printf("store3b %d %9g %9g\n",j,ang[0],degree);
         for (k = 0; k < 3; k++) ipr(doub10*ax3[j][k]);
         for (k = 0; k < 3; k++) ipr(doub10*cen[j][k]);
         for (k = 0; k < 3; k++) ipr(doub10*ang[k]*degree);
         for (k = 0; k < 3; k++) printf("%3d ",elcol[j][k]);
         printf("%s ",ename[j]);
         if (elcol[j][0] < 0)
         {
            for ( k = 0; fname[-elcol[j][0]][k] != '\0'; ++k )
	       printf("%c", fname[-elcol[j][0]][k]);
            printf("\n");
         }
         else printf("%d\n",j);
      }
/*
  write the joints out also
  (headed by a negative 1  and the number of joints)
*/
      printf("%d %d\n",-1,njts);
      for (  j = 0 ; j < njts ; ++ j )
      {
         for (  k = 0 ; k < 2 ; ++ k )
            printf("%3d ",coel[j][k]-1) ;
         for (  k = 0 ; k < 3 ; ++ k )
            ipr(doub10*jnt[j][k]);
         printf(" %s\n",jname[j]);
      }
   }
   first = FALSE ;
}  /* store3 */
/***********************************************/

ipr(x)
double x;
/*
    print out integral part of x.

    called by store3.
*/
{
      int k;

      if (x >= doub0) k = (int)(x+inv2);
              else  k = (int)(x-inv2);
      printf("%d ",k);
}  /* ipr */
/********************************************/

docola(prop)
   double prop ;
/*
  sets ellipsoid colour proportionately to the appropriate rgb.

  called by action
*/
{
   elcol[ellpsd][0] += prop*(newcol[0]-elcol[ellpsd][0]) ;
   elcol[ellpsd][1] += prop*(newcol[1]-elcol[ellpsd][1]) ;
   elcol[ellpsd][2] += prop*(newcol[2]-elcol[ellpsd][2]) ;
   if (t == 52) elcol[ellpsd][0] = -newcol[0] ;

   if (debug <= 0)
      printf(" docola %3d %3d %3d\n",
         elcol[ellpsd][0],elcol[ellpsd][1],elcol[ellpsd][2]);

}  /* docola */
/***************************************/

setplc()
/*
  set observers viewing point to new values.

  called by action
*/
{
   if (debug <= 0)
      printf("setplca %9g %9g %9g %9g %9g %9g\n",
         pplace[0],pplace[1],pplace[2],x[0],x[1],x[2]);
   pplace[0] += prop*(x[0]-pplace[0]);
   pplace[1] += prop*(x[1]-pplace[1]);
   pplace[2] += prop*(x[2]-pplace[2]);
   if (debug <= 0)
      printf("setplcb %9g %9g %9g\n",
         pplace[0],pplace[1],pplace[2]);
}  /* setplc */
/***************************************/

setobs()
/*
  set up matrix 'obs' for eulerian angles in 'ang'.

  called by action
  calls  rset, matmul
*/
{
   double newang[3];
   double r1[3][3],r2[3][3],r3[3][3] ;

   newang[0] = oldang[0] + prop*(ang[0]-oldang[0]);
   newang[1] = oldang[1] + prop*(ang[1]-oldang[1]);
   newang[2] = oldang[2] + prop*(ang[2]-oldang[2]);
   rset(r1,newang[0],0) ;
   rset(r2,newang[1],1) ;
   rset(r3,newang[2],2) ;
   matmul(r1,r2,obs) ;
   matmul(obs,r3,obs) ;
   if (debug <= 0)
   {
      printf(" setobs %9g %9g %9g %9g %9g %9g\n",
           ang[0],ang[1],ang[2],obs[0][0],obs[0][1],obs[0][2]);
      printf("                 %9g %9g %9g\n",
           obs[1][0],obs[1][1],obs[1][2]);
      printf("                 %9g %9g %9g\n",
           obs[2][0],obs[2][1],obs[2][2]);
   }
   oldang[0] = newang[0];
   oldang[1] = newang[1];
   oldang[2] = newang[2];
}  /* setobs */
/************************************************************/

enquir(this,array)
   int this ;
   double array[EMAX][3] ;
/*
  store values from 'array' into variables.

  called by action
*/
{
   val[var0] = array[this][0] ;
   val[var1] = array[this][1] ;
   val[var2] = array[this][2] ;
}  /* enquir */
/************************************************************/

doangles(el,re,val,var0,var1,var2)
int el,re,var0,var1,var2;
double val[EMAX];
/*
  store the angles of 'el' relative to 're' in 'val' array.
  in degrees.

  called by action.
  calls  matmul, rotget, rotput, mkang
*/
{
   double mvro[3][3],mvunro[3][3];
   double stro[3][3],stunro[3][3];
   double r[3][3];

   rotget(stro,stunro,re) ;
   rotget(mvro,mvunro,el) ;
   matmul(stunro,mvro,r) ;
   rotput(r,EMAX) ;
   if (ok[0] != 0) ok[0] = 34 ;
   mkang(EMAX) ;
   val[var0] = ang[0]*degree ;
   val[var1] = ang[1]*degree ;
   val[var2] = ang[2]*degree ;
   if (debug <= 0)
      printf("doangles %9g %9g %9g\n",
         val[var0],val[var1],val[var2] );
}  /* doangles */
/*********************************/

int findfg(ell)
int ell;
/*
  find the figure (excluding 'every')
  that includes the ellipsoid 'ell'.

  called by setper, doattach, dodetach
  calls  setels
*/
{
   int e,f;

   if (debug <= 0) printf("findfg %3d\n",ell);
   setels(ell,-1) ;
   for (  f = 1 ; f < nfigs ; ++ f )
   {
      if (debug <= 0)
          printf("findfga %3d %3d\n",f,figell[f]);
      for (  e = 0 ; e < ecount ; ++ e )
         if (figell[f] == elist[e]) return(f);
   }
/*
  snag-
*/
   ok[0] = 35 ;
   ok[1] = ell ;
   nerrs = 2;
   return(-1);
}  /* findfg */
/************************************************/

doattach()
/*
  create a joint 'join' at point 'x,y,z'
  relative to centre of refell.

  called by action
  calls  findfg
*/
{
   int findfg();
   int fig1,fig2,low,high ;

   if ((coel[join][1] != -1) || (coel[join][0] != -1))
   {
      ok[0] = 42 ;
      ok[1] = join ;
      nerrs = 2;
   }
   else
   {
/*
  find lowest ellipsoid of the figures being connected-
*/
      fig1 = findfg(ellpsd);
      fig2 = findfg(refell);
      if (ok[0] == 0)
      {
         high = fig2 ;
         low = fig1 ;
         if (figell[low] > figell[high])
         {
            low = fig2 ;
            high = fig1 ;
         }
         figell[high] = figell[low] ;
         coel[join][0] = ellpsd ;
         coel[join][1] = refell ;
         jnt[join][0] = x[0]+cen[ellpsd][0] ;
         jnt[join][1] = x[1]+cen[ellpsd][1] ;
         jnt[join][2] = x[2]+cen[ellpsd][2] ;
         if (debug <= 1)
         {
            printf("doattacha %d %d %d %d %d %d\n",
               join,ellpsd,refell,fig1,fig2,figell[low]);
            printf("%g %g %g\n%g %g %g\n%g %g %g\n",
               cen[ellpsd][0], cen[ellpsd][1], cen[ellpsd][2],
               cen[refell][0], cen[refell][1], cen[refell][2],
               jnt[join][0], jnt[join][1], jnt[join][2]);
         }
      }
   }
}  /* doattach */
/*************************************/

dodetach()
/*
  split 1 figure into 2.

  called by action
  calls  findfg, setels
*/
{
   int findfg();
   int othere,otherf;
   int j,k;
   int fgk ;
   int fg[2],el[2] ;
/*
  check if the new figure 'fig' is already being used -
*/
   j = figell[fig] ;
   if (j != 0)
   {
      ok[0] = 43 ;
      ok[1] = fig ;
      nerrs = 2;
      goto rtrn ;
   }
/*
   fig ok, so start detaching-
*/
   othere = 0 ;
   if (coel[join][0] == ellpsd) othere = coel[join][1] ;
   if (coel[join][1] == ellpsd) othere = coel[join][0] ;
   if (othere == 0)
   {
      ok[0] = 44 ;
      ok[1] = join ;
      ok[2] = ellpsd ;
      nerrs = 2;
      goto rtrn;
   }
   otherf = findfg(othere);
   if (ok[0] != 0) goto rtrn ;
/*
   move all the joints down one -
*/
   for (j = join; j < njts; ++j)
   {
      coel[j][0] = coel[j+1][0] ;
      coel[j][1] = coel[j+1][1] ;
      jnt[j][0] = jnt[j+1][0];
      jnt[j][1] = jnt[j+1][1];
      jnt[j][2] = jnt[j+1][2];
   }
   --njts;
/*
   find representative ellipsoid of each figure -
*/
   el[0] = ellpsd ;
   el[1] = othere ;
   fg[0] = fig ;
   fg[1] = otherf ;
   for (  k = 0 ; k < 2 ; ++ k )
   {
      setels(el[k],-1);
      fgk = fg[k] ;
      figell[fgk] = EMAX ;
      for (  j = 0 ; j < ecount ; ++ j )
         if (elist[j] < figell[fgk]) figell[fgk] = elist[j] ;
   }
rtrn: ;
}  /* dodetach */
/*******************************/

domoveby(x,y,z,refell)
   int refell;
   double x,y,z;
/*
  moves ellipsoids and joints in lists 'elist' and 'jlist'
  by vector 'x,y,z' relative to the axes of 'refell'.

  called by  try, action, abut, fun.
  calls      rotget, vecmul, shift.
*/
{
   double v[EMAX][3];
   double r[3][3];
   double unr[3][3] ;

   if (debug <= 0)
      printf("domovebya %9g %9g %9g\n",x,y,z);
   v[0][0] = x ;
   v[0][1] = y ;
   v[0][2] = z ;
   rotget(r,unr,refell) ;
   vecmul(v,r,0) ;
   shift(v[0][0],v[0][1],v[0][2]);
   if (debug <= 0)
      printf("domovebyb %9g %9g %9g\n",
         v[0][0],v[0][1],v[0][2]);
}  /* domoveby */
/************************************************************/

dogrofig(x0,x1,x2)
double x0,x1,x2;
/*
  scale parts in 'elist' and 'jlist' about the point 'x0,x1,x2',
  multiplying all semi-axes and coords of centres and joints
  by factors f[0],f[1],f[2] in x,y, and z directions respectively

  called by action, dogrojnt
  calls     shift, dogroell
*/
{
   int e,j,n ;

   if (debug <= 0)
      printf("dogrofig %3d %3d %9g %9g %9g\n",
        ecount,jcount,f[0],f[1],f[2]);
   shift(-x0,-x1,-x2);

   for (  n = 0 ; n < ecount ; ++ n )
   {
      e = elist[n];
      dogroell(f,e,cen) ;
      dogroell(f,e,ax3) ;
      maxax[e] = ax3[e][0];
      minax[e] = ax3[e][0];
      for (j = 1; j < 3; ++j)
      {
         if (ax3[e][j] > maxax[e]) maxax[e] = ax3[e][j];
         if (ax3[e][j] < minax[e]) minax[e] = ax3[e][j];
      }
   }
   for (  n = 0 ; n < jcount ; ++ n )
      dogroell(f,jlist[n],jnt) ;

   shift(x0,x1,x2);
}  /* dogrofig */
/********************************************/

dogroell(f,j,array)
   int j ;
   double f[3],array[EMAX][3] ;
/*
  scales jth member of array by factor 'f'.

  called by action, dogrofig
*/
{
   if (debug <= 0) printf("dogroella %3d %9g %9g %9g %9g %9g %9g\n",
      j,f[0],f[1],f[2],array[j][0],array[j][1],array[j][2]);
   array[j][0] *= f[0] ;
   array[j][1] *= f[1] ;
   array[j][2] *= f[2] ;
   if (debug <= 0) printf("dogroellb %9g %9g %9g\n",
      array[j][0],array[j][1],array[j][2]);
}  /* dogroell */
/***************************************/

dogrojnt()
/*
  scales ellipsoid 'ellpsd' by factors 'f', keeping position
  of joint 'join' fixed and moving all other joints and
  ellipsoids connected to 'ellpsd' appropriately.

  called by action
  calls     rotget, twirl, dogrofig, setels, vecmul, shift
*/
{
   double d[EMAX][3],r[3][3],unr[3][3] ;
   double x0,x1,x2;
   int jscan,othere,dim ;

   if (debug <= 0)
      printf("dogrojnta %3d %3d %9g %9g %9g\n",
         ellpsd,join,f[0],f[1],f[2]);
   if ((njts <= 0) || (njts > EMAX)) goto lab11 ;
   if ((coel[join][0] != ellpsd)&&(coel[join][1] != ellpsd))
      goto lab12 ;

   rotget(r,unr,ellpsd) ;
/*
  scale and shift the growing ellipsoid-
*/
   x0 = jnt[join][0] ;
   x1 = jnt[join][1] ;
   x2 = jnt[join][2] ;
   elist[0] = ellpsd ;
   ecount = 1;
   jcount = 0;
   twirl(x0,x1,x2,unr) ;
   dogrofig(x0,x1,x2) ;
   twirl(x0,x1,x2,r) ;
/*
  now shift everything connected to ellpsd-
*/
   for (  jscan = 0 ; jscan < njts ; ++ jscan )
   {
      if (jscan != join)
      {
         othere = 0 ;
         if (coel[jscan][0] == ellpsd) othere = coel[jscan][1] ;
         if (coel[jscan][1] == ellpsd) othere = coel[jscan][0] ;
         if (othere != 0)
         {
/*
  find parts connected to jscan through othere-
*/
            setels(othere,jscan);
            if (ok[0] != 0) goto lab10 ;
/*
  find out how much to shift things hanging here-
*/
            for ( dim = 0 ; dim < 3 ; ++ dim )
               d[0][dim] = jnt[jscan][dim]-jnt[join][dim] ;
            vecmul(d,unr,0) ;
            for ( dim = 0 ; dim < 3 ; ++ dim )
               d[0][dim] = d[0][dim]*(f[dim]-doub1) ;
            vecmul(d,r,0) ;
            if (debug <= 0)
               printf("dogrojntb %3d %3d %9g %9g %9g\n",
                  jscan,othere,d[0][0],d[0][1],d[0][2]);
            shift(d[0][0],d[0][1],d[0][2]);
         }
      }
   }
   goto lab10 ;
/*
  snags-
*/
lab11: ok[0] = 40 ;
   ok[1] = njts ;
   nerrs = 2;
   goto lab10 ;

lab12: ok[0] = 41 ;
   ok[1] = ellpsd ;
   nerrs = 2;

lab10: ;
}  /* dogrojnt */
/************************************************************/

domovjnt()
/*
  moves joint 'join' by amounts 'x', keeping the position
  of ellipsoid 'ellpsd' fixed and moving all other joints
  and ellipsoids connected to 'join' appropriately.

  called by action
  calls     rotget, setjnt, vecmul, shift
*/
{
   double d[EMAX][3],r[3][3],unr[3][3] ;
   int jscan,othere,dim ;

   if (debug <= 0)
      printf("domovjnt %3d %3d %9g %9g %9g %9g\n",
         ellpsd,join,prop,f[0],f[1],f[2]);
   if ((njts <= 0) || (njts > EMAX)) goto lab11 ;
   othere = 0 ;
   if (coel[jscan][0] == ellpsd) othere = coel[jscan][1] ;
   if (coel[jscan][1] == ellpsd) othere = coel[jscan][0] ;
   if (othere == 0) goto lab11 ;

   rotget(r,unr,ellpsd) ;
/*
  shift the joint -
*/
   for (dim = 0; dim <3; ++dim)
     d[0][dim] = frac*x[dim];
   setjnt(ellpsd,join);
   vecmul(d,unr,0);
   shift(d[0][0],d[0][1],d[0][2]);
   goto lab10 ;
/*
  snags-
*/
lab11: ok[0] = 63 ;
   ok[1] = join ;
   ok[2] = ellpsd;
   nerrs = 3;

lab10: ;
}  /* domovjnt */
/************************************************************/

dobend(angle,axis)
   int axis ;
   double angle ;
/*
  implement flex(38), rotate(39), abduct(40).

  called by action
  calls  dospinby
*/
{
   int refell ;
   int left ;

   refell = ellpsd ;
   if (t == rotate) goto lab1 ;
   if (ellpsd == coel[join][0]) refell = coel[join][1] ;
   if (ellpsd == coel[join][1]) refell = coel[join][0] ;
/*
  assume odd-numbered ellipsoids are on left side of figure-
*/
lab1: if (((ellpsd-figell[fig])%2) == 0)
          left = TRUE; else left = FALSE;
/*
  flex-
*/
   if ((t == flex)&&(knee[join])) angle = -angle ;
/*
  rotate-
*/
   if ((t == rotate)&&( left == FALSE)) angle = -angle ;
/*
  abduct-
*/
   if ((t == abduct)&&(left == TRUE)) angle = -angle ;

   if (debug <= 0)
      printf("dobend %3d %3d %3d %3d %3d %9g\n",
          t,ellpsd,join,axis,refell,angle );
   dospinby(x,refell,angle,axis) ;
}  /* dobend */
/****************************************/

prinel()
/*
  This lists the axis lengths, positions, colours and quaternions
  of all the ellipsoids.

  called by  action, store3
*/
{
   int n ;

   printf("prinel  %3d\n", nels );

   for (  n = 0 ; n < nels ; ++ n )
   {
      printf(
          "%3d %9g %9g %3d %9g %s\n",
          n,ax3[n][0],cen[n][0],elcol[n][0],quat[n][0],ename[n]);
      printf(
          "    %9g %9g %3d %9g\n",
            ax3[n][1],cen[n][1],elcol[n][1],quat[n][1]);
      printf(
          "    %9g %9g %3d %9g %9g %9g\n\n",
            ax3[n][2],cen[n][2],elcol[n][2],quat[n][2],
                quat[n][3],quat[n][4] );
   }
   printf("\n" );
}  /* prinel */
/**************************************/

dobalanc()
/*
  balance part of a figure by bending ellipsoid 'ellpsd' at
  the joint at point 'x' about 'axis' of ellipsoid 'refell'.

  called by action
  calls  rotget, rset, matmul, vecmat, dospinby
*/
{
   double wsum,wmod,uw,vw,alpha,beta,phi,mass;
   double dx[3],u[3],u1[3],u2[3],v[3],w[3],w1[3],ww[3];
   double ro[3][3],unro[3][3],rph[3][3],ralph[3][3],rb[3][3];
   double usq;
   int j,k,thise ;

   rotget(ro,unro,refell) ;
/*
  form unit vector along rotation axis
*/
   for (  k = 0 ; k < 3 ; ++ k )
   {
      ww[k] = doub0;
      u[k] = ro[k][axis] ;
   }
   if (debug <= 0) printf("dobalanca %9g %9g %9g\n",u[0],u[1],u[2]);
/*
  run through moving ellipsoids-
*/
   for (  j = 0 ; j < ecount ; ++ j )
   {
      thise = elist[j] ;
      mass = ax3[thise][0]*ax3[thise][1]*ax3[thise][2] ;
      if (debug <= 0)
         printf( "dobalancb %3d %3d %9g\n", j,thise,mass);
/*
  find vector to jth moving ellipsoid centre-
*/
      for (  k = 0 ; k < 3 ; ++ k )
      {
         dx[k] = cen[thise][k]-x[k];
         ww[k] += mass*dx[k];
         if (debug <= 0) printf("dobalancc %3d %9g %9g %9g %9g\n",
              k,x[k],cen[thise][k],dx[k],ww[k]);
      }
   }
/*
  find vector 'w' to centre of mass of moving parts -
*/
   wsum = doub0;
   for (k = 0; k < 3; ++k)
      wsum += ww[k]*ww[k];
   if (wsum > doub0) wmod = sqrt(wsum); else wmod = doub0;
   for (k = 0; k < 3; ++k)
      if (wmod > doub0) w[k] = ww[k]/wmod; else w[k] = doub0;
/*
   find vector 'v' at point on meridien through u
   equal in distance from u as w is from u -
*/
   uw = doub0;
   for (k = 0; k < 3; ++k)
      uw += u[k]*w[k];
   if (debug <= 0)
      printf( "dobalancd %9g %9g %9g %9g %9g\n",
         wmod,uw,w[0],w[1],w[2]);
   usq = u[0]*u[0] + u[2]*u[2];
   if (usq > doub0) u1[0] = sqrt(usq); else u1[0] = doub0;
   u1[1] = u[1];
   u1[2] = doub0;
   if (debug <= 0)
      printf( "dobalance %9g %9g %9g\n",
         u1[0],u1[1],u1[2]);
   if ((uw < -doub1) || (uw > doub1)) alpha = doub0; else alpha = acos(uw);
   rset(ralph,alpha,2);
   vecmat(u1,ralph,u2);
   if (debug <= 0)
      printf( "dobalancf %9g %9g %9g %9g\n",
         alpha,u2[0],u2[1],u2[2]);
   phi = -atan2(u[2],u[0]);
   rset(rph,phi,1);
   vecmat(u2,rph,v);
   vw = v[0]*w[0] + v[1]*w[1] + v[2]*w[2];
   if ((vw > -doub1) && (vw < doub1)) beta = acos(vw); else beta = doub0;
   rset(rb,beta,axis);
   matmul(rb,unro,rb);
   matmul(ro,rb,rb);
   vecmat(w,rb,w1);
   if (debug <= 0)
      printf( "dobalancg %9g %9g %9g\n",
         w1[0],w1[1],w1[2]);
   if (w[1] > w1[1]) beta = -beta;
   if (debug <= 0)
      printf( "dobalanch %9g %9g %9g %9g %9g %9g\n",
         phi,v[0],v[1],v[2],vw,beta);
   dospinby(x,refell,beta,axis) ;
}  /* dobalanc */
/************************************************************/

dodrag()
/*
   bend 'ellpsd' at joint 'join' with coordinates 'x'
   about 'axis' of 'refell' to make 'ell1' touch the ground

   called by action.
   calls     dospinby, save, restore, shift, doground,
             setels.
*/
{
   double angs;
   double arange;
   double dang;
   double gap;
   double ming;
   double doground();
   int samples = 20;
   int iterations = 3;
   int j;
   int jend;
   int jmin;
   int jstart;
   int k;
   int othere;
/*
   set rest of figure touching the ground -
*/
   if (debug < 1)
	   printf("dodraga %3d %3d %3d %3d %3d %9g %9g %9g\n",
	    ell1,ellpsd,refell,join,axis,x[0],x[1],x[2]);
   othere = 0 ;
   if (coel[join][0] == ell1) othere = coel[join][1] ;
   if (coel[join][1] == ell1) othere = coel[join][0] ;
   if (othere == 0)
   {
        ok[0] = 65 ;
        ok[1] = join ;
        ok[2] = ell1 ;
        nerrs = 2;
	  gap = doub0;
        goto rtrn;
   }
   setels(othere,join);
   gap = doground();
   setels(ell1,-1);
   shift(doub0,-gap,doub0);
   save();
   x[0] = jnt[join][0];
   x[1] = jnt[join][1];
   x[2] = jnt[join][2];
   if (debug < 1)
	   printf("dodragb %3d %3d %3d %9g %9g %9g %9g\n",
	      othere,samples,iterations,gap,x[0],x[1],x[2]);
   arange = radian*(double)samples;
   jstart = -samples/2;
   jend = jstart + samples;
   for (k = 0; k < iterations; ++k)
   {
      dang = arange/(double)samples;
      angs = dang*(double)jstart;
/*
   find where 'ell1' closest to the ground -
*/
      setels(ellpsd,join);
      dospinby(x,refell,angs,axis);
      elist[0] = ell1; ecount = 1;
      ming = doground();
      if (ming < doub0) ming = -ming; 
      jmin = jstart;
      for (j = jstart+1; j < jend+1; ++j)
      {
         angs = dang*(double)j;
         restore();
         setels(ellpsd,join);
         dospinby(x,refell,angs,axis);
         elist[0] = ell1; ecount = 1;
         gap = doground();
         if (gap < doub0) gap = -gap; 
         if (gap < ming)
         {
            ming = gap;
            jmin = j;
         }
         if (debug < 1)
            printf("dodragc %3d %3d %9g %9g %9g %3d %9g\n",
              j,k,angs,gap,cen[ell1][1],jmin,ming);
      } /* j */
/*
   rotate 'ell1' to best position -
*/
      restore();
      angs = dang*(double)jmin;
      setels(ellpsd,join);
      dospinby(x,refell,angs,axis);
      setels(ellpsd,-1);
      gap = doground();
      shift(doub0,-gap,doub0);
      save();
      arange = dang + dang;
      if (debug < 1)
            printf("dodragd %3d %3d %9g %9g %9g %3d %9g\n",
              j,k,angs,gap,cen[ell1][1],jmin,ming);
   } /* k */

rtrn:
   if (debug < 1)
	   printf("dodrage %9g %9g %9g\n",
             prop,angs,gap);
} /* dodrag */
/************************************************************/

double solve(a,b,n)
double a,b;
int n;
/*
   find a zero of 'fun()' in the range 'a' to 'b'
   to an accuracy of 1.0 on fun, using at most 'n' iterations.

   called by doabut.
   calls     fun.
*/
{
   double fun();
   double valab,vala,valb;
   double angab,anga,angb;
   double dval;
   int k;

   if (debug <= 1)
         printf("solvea %9g %9g %d\n",a,b,n);
   angab = a;
   anga = a; vala = fun(a);
   if (debug <= 1)
         printf("solveb %9g %9g %9g %d\n",
            anga,vala,cen[ell1][1],ok[0]);
   if ((vala > -doub1) && (vala < doub1)) goto done;
   if (ok[0] != 0) goto done;
   angab = b;
   angb = b; valb = fun(b);
   if (debug <= 1)
         printf("solvec %9g %9g %9g %d\n",
            angb,valb,cen[ell1][1],ok[0]);
   if (ok[0] != 0) goto done;
   if ((valb > -doub1) && (valb < doub1)) goto done;
   if (vala*valb > doub0)
   {
      if (vala > doub0)
      {
         if (vala < valb) angab = a;
            else angab = b;
      }
      else
      {
         if (vala < valb) angab = b;
            else angab = a;
      }
      anga = doub0; angb = doub0;
      valab = doub0; vala = doub0; valb = doub0;
      goto done;
   }
   if (vala > valb)
   {
      valab = vala;
      vala = valb;
      valb = valab;
      angab = anga;
      anga = angb;
      angb = angab;
      if (debug <= 1)
         printf("solved %9g %9g %9g %9g\n",
            anga,vala,angb,valb);
   }
   for (k = 0; k < n; ++k)
   {
      dval = vala-valb;
      if (dval < doub0) dval = -dval;
      if (debug <= 1)
         printf("solvee %3d %9g %9g %9g %9g %9g\n",
            k,dval,anga,vala,angb,valb);
      if (dval < doub1) goto done;
      angab = inv2*(anga+angb);
      valab = fun(angab);
      if (ok[0] != 0) goto done;
      if (valab < doub0)
      {
         anga = angab;
         vala = valab;
      }
      else
      {
         angb = angab;
         valb = valab;
      }
   }

done:
   return(angab);
} /* solve */
/*******************************************/

double fun(xarg)
double xarg;
/*
   called by solve.
   calls     setels, dospinby, doground, restore, sepn,
             domoveby.
*/
{
   double ans;
   double dx[3];

   double doground();
   double sepn();

   ans = doub0;
   if (t == drag)
   {
      setels(ellpsd,join);
      restore();
      if (debug <= 0)
         printf("funa %d %d %9g %9g %9g\n",
            ellpsd,join,cen[ell1][0],cen[ell1][1],cen[ell1][2]);
      dospinby(x,refell,xarg,axis);
      ecount = 1; elist[0] = ell1;
      ans = doground();
      return(ans);
   }
   else
   if (t == abut)
   {
      dx[0]=doub0;
      dx[1]=doub0;
      dx[2]=doub0;
      dx[axis] = xarg;
      domoveby(dx[0],dx[1],dx[2],refell);
      ans = sepn();
      if (ok[0] != 0) goto out;
      restore();
      if (debug <= 0)
         printf("func %9g %9g\n",xarg,ans);
      return(ans);
   }
   else
   {
      ok[0] = 59;
      nerrs = 2;
   }
out:
   if (debug <= 0) printf("fund %9g %9g\n",x,ans);
} /* fun */
/*******************************************/

dotouch()
/*
  make ellipsoid 'ell1' come as close as possible to 'ell2'
  by bending ellipsoid 'ellpsd' at the joint at point 'x'
  about 'axis' of ellipsoid 'refell'.

  called by action
  calls     angsepn, surf, save, restore, dospinby.
*/
{
   double angs;
   double arange;
   double dang;
   double gap;
   double ming;
   double pro;
   double angsepn();
   int samples = 10;
   int iterations = 3;
   int j;
   int jend;
   int jmin;
   int jstart;
   int k;

   if (debug < 1)
	   printf("dotoucha %3d %3d %9g %9g %9g\n",
	      samples,iterations,x[0],x[1],x[2]);
   save();
   pro = prop;
   prop = doub1;
   arange = angsepn();
   jstart = -samples/2;
   jend = jstart + samples;
   for (k = 0; k < iterations; ++k)
   {
      dang = arange/(double)samples;
/*
   find where 'ell1' closest to ell2 -
*/
      angs = dang*(double)jstart;
      dospinby(x,refell,angs,axis);
      ming = surf();
      if (ming < doub0) ming = -ming; 
      jmin = jstart;
      for (j = jstart+1; j < jend+1; ++j)
      {
         restore();
         angs = dang*(double)j;
         dospinby(x,refell,angs,axis);
         gap = surf();
         if (gap < doub0) gap = -gap; 
         if (gap < ming)
         {
            ming = gap;
            jmin = j;
         }
         if (debug < 1)
            printf("dotouchc %3d %3d %9g %9g %9g %3d %9g\n",
              j,k,angs,gap,cen[ell1][1],jmin,ming);
      } /* j */
/*
   rotate 'ell1' to best position -
*/
      restore();
      angs = dang*(double)jmin;
      dospinby(x,refell,angs,axis);
      gap = surf();
      save();
      arange = dang + dang;
      if (debug < 1)
            printf("dotouchd %3d %3d %9g %9g %9g %3d %9g\n",
              j,k,angs,gap,cen[ell1][1],jmin,ming);
   } /* k */

rtrn:
   prop = pro;
   if (debug < 1)
	   printf("dotouche %9g %9g %9g\n",
             prop,angs,gap);
} /* dotouch */
/************************************************************/

double surf()
/*
   find distance between surfaces of ell1 and ell2
   using Buckdales algorithm (giving answer in
   transformed coordinates).

   called by dotouch.
   calls     sqr, newton, matmul, vecmat, getaxes.
*/
{
   int j,k;
   double p,q,r,l,m,n;
   double pp,qq,rr,ll,mm,nn;
   double lsq,msq,nsq;
   double ans,rsq,s1,s2,s3;
   double rx,tt,tsq;
   double t;
   double init;
   double a[7];
   double d[3],ellax[3],md[3],mx[3],rd[3],tx[3],xx[3];
   double mat[3][3];
   double mat1[3][3];
   double tr1[3][3],untr1[3][3],trtr1[3][3],untrtr1[3][3];
   double mat2[3][3];
   double tr2[3][3],untr2[3][3],trtr2[3][3],untrtr2[3][3];
   double rotn[3][3];
   double matell[3][3];

   double newton();
   double sqr();

/*
   transform ell2 into a unit sphere -
*/
   getmat(mat2,tr2,untr2,trtr2,untrtr2,ell2);
   if (ok[0] != 0)
   {
      ans = doub0;
      goto out;
   }
/*
   find distance apart of centres in transformed coordinates -
*/
   for (j = 0; j < 3; j++)
      d[j] = cen[ell1][j] - cen[ell2][j];
   if (debug <= 0)
      printf("surfa %9g %9g %9g\n",d[0],d[1],d[2]);
   vecmat(d,trtr2,md);
   if (debug <= 0)
      printf("surfb %9g %9g %9g\n",md[0],md[1],md[2]);
/*
   find axes of ell1 in ell2 coordinates -
*/
   getmat(mat1,tr1,untr1,trtr1,untrtr1,ell1);
   if (ok[0] != 0)
   {
      ans = doub0;
      goto out;
   }
   matmul(untr2,mat1,mat);
   matmul(mat,tr2,matell);
   getaxes(matell,ellax,rotn);
   vecmat(md,rotn,rd);
   p = rd[0]; q = rd[1]; r = rd[2];
   if (debug <= 0)
      printf("surfc %9g %9g %9g\n",p,q,r);
   l = ellax[0]; m = ellax[1]; n = ellax[2];
   if (debug <= 0)
      printf("surfd %9g %9g %9g\n",l,m,n);
   ll = l*l;  mm = m*m;  nn = n*n;
   lsq = ll*ll; msq = mm*mm; nsq = nn*nn;
   pp = sqr(p*l); qq = sqr(q*m); rr = sqr(r*n);
   s1 = ll+mm+nn;
   s2 = ll*mm + mm*nn + nn*ll;
   s3 = ll*mm*nn;
   if (debug <= 0)
      printf("surfe %9g %9g %9g\n",s1,s2,s3);
   a[6] = doub1;
   a[5] = doub2*s1;
   a[4] = doub4*s2 + lsq + msq + nsq - (pp+qq+rr);
   a[3] = doub2*(s2*s1 + s3
                - pp*(mm+nn) - qq*(nn+ll) - rr*(ll+mm));
   a[2] = s2*s2 + doub2*s1*s3
          - pp*(msq + doub4*mm*nn + nsq)
          - qq*(nsq + doub4*ll*nn + lsq)
          - rr*(lsq + doub4*ll*mm + msq);
   a[1] = doub2*(s2*s3 - pp*(mm*nsq + nn*msq)
          - qq*(nn*lsq + ll*nsq) - rr*(ll*msq + mm*lsq));
   a[0] = s3*s3 - pp*msq*nsq - qq*nsq*lsq - rr*lsq*msq;
   init = doub0;
   for (j = 0; j < 7; ++j)
      if (a[j] > doub0) init += a[j];
         else init -= a[j];
   tt = newton(7,init,a);
   if (tt < doub0)
   {
      ans = -doub2;
      goto out;
   }
   if ((tt+ll) != doub0) xx[0] = p*ll/(tt+ll); else xx[0] = doub0;
   if ((tt+mm) != doub0) xx[1] = q*mm/(tt+mm); else xx[1] = doub0;
   if ((tt+nn) != doub0) xx[2] = r*nn/(tt+nn); else xx[2] = doub0;
   mx[0] = xx[0]-p;
   mx[1] = xx[1]-q;
   mx[2] = xx[2]-r;
   vecmat(mx,untrtr2,tx);
   if (debug <= 0)
      printf("surff %9g %9g %9g\n",xx[0],xx[1],xx[2]);
   if (debug <= 0)
      printf("surfg %9g %9g %9g\n",mx[0],mx[1],mx[2]);
   if (debug <= 0)
      printf("surfh %9g %9g %9g\n",tx[0],tx[1],tx[2]);
   rsq = sqr(mx[0]) + sqr(mx[1]) + sqr(mx[2]);
   tsq = sqr(tx[0]) + sqr(tx[1]) + sqr(tx[2]);
   if (rsq > doub0) rx = sqrt(rsq); else rx = doub0;
   if (tsq > doub0) t = sqrt(tsq); else t = doub0;
   if (rx > doub0) ans = (rx-doub1)*t/rx; else ans = doub0;
out:
   if (debug <= 0)
      printf("surfi %9g %9g\n",tt,ans);
   return(ans);
} /* surf */
/******************************************************/

double angsepn()
/*
   find approx angular separation of ell1 and ell2 from x
   using minax to avoid going thru onto the wrong side

   called by dotouch
   calls sqr
*/
{
   double dsep;
   double asep;
   double sqdist1, sqdist2;

   if (debug <= 0)
      printf("angsepna %3d %3d %9g %9g %9g\n",ell1,ell2,x[0],x[1],x[2]);
   dsep = minax[ell1] + minax[ell2];
   sqdist1 = sqr(x[0]-cen[ell1][0])+sqr(x[1]-cen[ell1][1])+sqr(x[2]-cen[ell1][2]);
   sqdist2 = sqr(x[0]-cen[ell2][0])+sqr(x[1]-cen[ell2][1])+sqr(x[2]-cen[ell2][2]);
   asep = doub2*dsep/sqrt(sqdist1) + sqrt(sqdist2));
   if (debug <= 0)
      printf("angsepnb %9g %9g %9g %9g %9g\n",
         dsep,sqrt(sqdist1),sqrt(sqdist2),asep);
   return(asep);
} /* angsepn */

/*******************************************************/
double dcen(d)
double d[3];
/*
  find separation between ellipsoid centres

  called by  doabut, sepn.
*/
{
   int j;
   double ans,dsq;

   if (debug <= 0)
         printf("dcena %9g %9g %9g %9g %9g %9g\n",
            cen[ell1][0],cen[ell1][1],cen[ell1][2],
            cen[ell2][0],cen[ell2][1],cen[ell2][2]);
   dsq = doub0 ;
   for (j = 0; j < 3; ++ j)
   {
      d[j] = cen[ell1][j]-cen[ell2][j];
      dsq += d[j]*d[j];
   }
   if (dsq > doub0) ans = sqrt(dsq); else ans = doub0;
   if (debug <= 0)
         printf("dcenb %9g %9g %9g %9g %9g\n",
            d[0],d[1],d[2],dsq,ans);
   return(ans);
}  /* dcen */
/************************************************************/

double sepn()
/*
   find distance between surfaces of ell1 and ell2.

   called by  dotouch, fun, fndmin, doabut, try.
   calls      dcen, surf.
*/
{
   int j;
   double dmid;
   double ans,minsep;
   double d[3];

   double dcen();
   double surf();
/*
   find bounds on separation -
*/
   if (debug <= 0)
      printf("sepna %9g %9g %9g %9g\n",
         minax[ell1],maxax[ell1],minax[ell2],maxax[ell2]);
   dmid = dcen(d);
   minsep = dmid-minax[ell1]-minax[ell2];
   if (debug <= 0)
         printf("sepnb %9g %9g\n",
            dmid,minsep);
   if (minsep <= doub0)
   {
      ans = -doub1;
   }
   else
   {
      ans = surf();
      if (ans < doub0) ans = -doub1;
   }
done:
   if (debug <= 0)
         printf("sepnc %9g %9g %9g\n",
            dmid,minsep,ans);
   return(ans);
} /* sepn */
/**********************************************/

getmat(mat,tr,untr,trtr,untrtr,ell)
int ell;
double mat[3][3],tr[3][3],untr[3][3],trtr[3][3];
double untrtr[3][3];
/*
   for ellipsoid 'ell', find its matrix 'mat',
   also: its transformation matrix 'tr' and
   its transpose 'trtr', and its inverse 'untr'
   and its inverse transpose 'untrtr'.

   called by  surf.
   calls      rotget, matmul.
*/
{
   double r[3][3],unr[3][3];
   double diag[3][3];
   double undiag[3][3];
   int j,k;

   if (debug <= 0)
      printf("getmata %d\n",ell);
/*
   make the matrix -
*/
   rotget(r,unr,ell);
   for (j = 0; j < 3; ++j)
   {
      for (k = 0; k < 3; ++k)
      {
         undiag[j][k] = doub0;
	 diag[j][k] = doub0;
      }
      if (ax3[ell][j] == doub0)
      {
	 ok[0] = 60;
	 ok[1] = j;
	 ok[2] = ell;
	 goto done;
      }
      if (ax3[ell][j] > doub0) undiag[j][j] = doub1/ax3[ell][j];
	 else undiag[j][j] = doub0;
      diag[j][j] = ax3[ell][j];
   }
   matmul(undiag,unr,trtr);
   matmul(r,undiag,untrtr);
   matmul(untrtr,trtr,mat);
   if (debug <= 0)
      printf("getmatb %d\n",ell);
/*
  make the transformation matrices-
*/
   matmul(diag,unr,untr);
   if (debug <= 0)
      printf("getmatc %d\n",ell);
   matmul(r,diag,tr);
done:
   if (debug <= -1)
   {
      printf("getmatd  %9g %9g %9g\n",
           trtr[0][0],trtr[0][1],trtr[0][2]);
      printf("         %9g %9g %9g\n",
           trtr[1][0],trtr[1][1],trtr[1][2]);
      printf("         %9g %9g %9g\n",
           trtr[2][0],trtr[2][1],trtr[2][2]);
   }
} /* getmat */
/***********************************************/

save()
/*
   save positions and orientations

   called by  doabut, dodrag, dotouch.
*/
{
   int j,n;

   for (n = 0; n < nels; ++n)
   {
      for ( j = 0; j < 3; ++j)
      {
         censav[n][j] = cen[n][j];
         jntsav[n][j] = jnt[n][j];
      }
      for ( j = 0; j < 5; ++j)
         quasav[n][j] = quat[n][j];
   }
} /* save */
/***********************************************/

restore()
/*
   restore positions and orientations

   called by   doabut, try, dodrag, fun, dotouch.
*/
{
   int j,n;

   for (n = 0; n < nels; ++n)
   {
      for (j = 0; j < 3; ++j)
      {
         cen[n][j] = censav[n][j];
         jnt[n][j] = jntsav[n][j];
      }
      for ( j = 0; j < 5; ++j)
         quat[n][j] = quasav[n][j];
   }
} /* restore */
/***********************************************/

double fndmin(a,b,n)
double a,b;
int n;
/*
   finds the minimum value of 'try'
   in the range 'a' to 'b' using at most 'n' iterations.

   called by dotouch
   calls     try.
*/
{
   double try();
   double trya,tryb,tryab;
   double olda,oldb;
   double mina,minb,minab;
   int k;

   if (debug <= 0) printf(
         "fndmina %3d %9g %9g\n",n,a,b);
   tryab = doub0;
   olda = a; oldb = b;
   for (k = 0; k < n; ++k)
   {
      trya = olda + (oldb-olda)*inv3;
      mina = try(trya);
      if (ok[0] != 0) goto out;
      tryb = oldb - (oldb-olda)*inv3;
      minb = try(tryb);
      if (ok[0] != 0) goto out;
      if (debug <= 0) printf(
         "fndminb %3d %9g %9g %9g %9g %9g %9g\n",
            k,olda,oldb,trya,mina,tryb,minb);
      if (mina < minb) oldb = tryb;
         else olda = trya;
   }
   if (mina < minb) tryab = trya;
      else tryab = tryb;
out:
   return(tryab);
} /* fndmin */
/*******************************************/

double try(a)
double a;
/*
     function to be found a minimum of,
     called from doabut.

     called by fndmin.
     calls     domoveby, sepn, restore.
*/
{
   double dx[3],s;

   if (t == abut)
   {
      dx[0] = doub0; dx[1] = doub0; dx[2] = doub0;
      dx[axis] = a;
      domoveby(dx[0],dx[1],dx[2],refell);
      s = sepn();
      restore();
   }
   else
   {
      ok[0] = 62;
      nerrs = 1;
      s = doub0;
   }
   return(s);
} /* try */
/***************************************************/

getaxes(m,axes,r)
double m[3][3],axes[3],r[3][3];
/*
   from its matrix 'm', find the 3 semiaxes of an ellipsoid
   and corresponding rotation matrix 'r'.

   called by surf.
   calls     matmul.
*/
{
   double lambda,mu,nu,nusq,numu;
   double s[3][3],t[3][3];
   double st[3][3],tmp[3][3];
   double sn,cs,sig;
   double a,b,c,abc;
   int p,q;
   int j,k,n;

   if (debug <= -1)
   {
      printf("getaxesa %9g %9g %9g\n",
           m[0][0],m[0][1],m[0][2]);
      printf("         %9g %9g %9g\n",
           m[1][0],m[1][1],m[1][2]);
      printf("         %9g %9g %9g\n",
           m[2][0],m[2][1],m[2][2]);
   }
   for (j = 0; j < 3; ++j)
   {
      for (k = 0; k < 3; ++k)
      {
         r[j][k] = doub0;
         t[j][k] = m[j][k];
      }
      r[j][j] = doub1;
   }
/*
   iterate 3 times -
*/
   for (n = 0; n < 3; ++n)
   {
/*
   find largest off-diagonal element -
*/
      a =  t[0][1]; if (a < doub0) a = -a;
      b =  t[0][2]; if (b < doub0) b = -b;
      c =  t[1][2]; if (c < doub0) c = -c;
      abc = a; p = 0; q = 1;
      if (b > abc)
      {
         abc = b;
         q = 2;
      }
      if (c > abc)
      {
         abc = c;
         p = 1;
         q = 2;
      }
      if (abc != doub0)
      {
         lambda = -t[p][q];
         mu = inv2*(t[p][p] - t[q][q]);
         nusq = lambda*lambda + mu*mu;
	 if (nusq > doub0) nu = sqrt(nusq); else nu = doub0;
         if (mu > doub0) sig = doub1; else sig = -doub1;
	 numu = nu + mu*sig;
         if ((nu > doub0) && (numu > doub0)) cs = sqrt((numu)/(doub2*nu));
	    else cs = doub0;
         if ((cs > doub0) && (nu > doub0)) sn = sig*lambda/(cs*doub2*nu);
	    else sn = doub0;
         if (debug <= 0)
            printf("getaxesb %9g %9g %9g %9g %9g\n",
               lambda,mu,nu,sn,cs);
         for (j = 0; j < 3; ++j)
         {
            for (k = 0; k < 3; ++k)
            {
               s[j][k] = doub0;
            }
            s[j][j] = doub1;
         }
         s[p][p] = cs;
         s[q][q] = cs;
         s[p][q] = sn;
         s[q][p] = -sn;
         for (j = 0; j < 3; ++j)
         {
            for (k = 0; k < 3; ++k)
            {
               st[j][k] = s[k][j];
            }
         }
         matmul(st,t,tmp);
         matmul(tmp,s,t);
         matmul(st,r,r);
         if (debug <= -1)
         {
            printf("getaxesc %9g %9g %9g\n",
                 t[0][0],t[0][1],t[0][2]);
            printf("         %9g %9g %9g\n",
                 t[1][0],t[1][1],t[1][2]);
            printf("         %9g %9g %9g\n",
                 t[2][0],t[2][1],t[2][2]);
         }
      }
   }
   for (j = 0; j < 3; ++j)
   {
      if (t[j][j] == doub0)
      {
         ok[0] = 60;
         ok[1] = ell1;
         ok[2] = ell2;
         nerrs = 3;
      }
      else
         if (t[j][j] > doub0) axes[j] = doub1/sqrt(t[j][j]);
	    else axes[j] = doub0;
   }
   if (debug <= -1)
   {
      printf("getaxesd %9g %9g %9g\n",
         axes[0],axes[1],axes[2]);
      printf("         %9g %9g %9g\n",
           r[0][0],r[0][1],r[0][2]);
      printf("         %9g %9g %9g\n",
           r[1][0],r[1][1],r[1][2]);
      printf("         %9g %9g %9g\n",
           r[2][0],r[2][1],r[2][2]);
   }
}  /* getaxes */
/******************************************************/

double newton(n,start,a)
int n;
double start,a[];
/*
   solve the polynomial of degree (n-1):

           n-1           n-2
   a[n-1]*x    + a[n-2]*x    + ... a[1]*x + a[0] = 0

   using 48 Newton-Raphson iterations starting at 'start'.

   called by surf.
*/
{
   double x,xold,num,den;
   int j,k;

   if (debug <= 0)
   {
      printf("newtona %d %9g\n",n,start);
      for (j = 0; j < n; ++j)
         printf("     %d %9g\n",j,a[j]);
   }
   x = start;
   xold = doub2*start+doub1;
   num = doub1;
   for (j = 0;
      ((j < 48) && (num != doub0) && (x != xold)); ++j)
   {
      num = doub0;
      den = doub0;
      for (k = n-1; k >= 0; --k)
      {
         num = x*num + a[k];
         if (k > 0) den = x*den + a[k]*(double)k;
         if (debug <= -1)
            printf("newtonb %d %d %9g %9g %9g\n",
                j,k,x,num,den);
      }
      if (den == doub0)
      {
         ok[0] = 57;
         ok[1] = ell2;
         nerrs = 2;
         x = -doub1;
         xold = -doub1;
      }
      else
      {
         if (debug <= -1)
            printf("newtonc %d %9g %9g %9g\n",
                j,x,num,den);
         xold = x;
         if (den != doub0) x -= num/den;
      }
   }
   if (debug <= 0) printf("newtond %9g %9g\n",x,num);
   return(x);
}  /* newton */
/*******************************************************/

doabut()
/*
   move figure containg ell1 to touch ell1 to ell2
   along direction parallel to given axis of
   reference ellipsoid.

   called by  perfrm.
   calls      save, restore, sepn, dcen,
              rotget, vecmul, domoveby, solve, fndmin.
*/
{
   int j;
   int steps;
   double min,max;
   double mov;
   double dold,dnew;
   double xold,xnew;
   double forward,back;
   double shft;
   double dist;
   double cdist;
   double d[3];
   double dx[3];
   double v[EMAX][3];
   double r[3][3],unr[3][3];

   double dcen();
   double sepn();
   double solve();
   double fndmin();

   if (debug <= 0)
      printf("doabuta %d %d %d %d %9g %9g %9g\n",
       ell1,ell2,refell,axis,cen[ell1][0],cen[ell1][1],cen[ell1][2]);
   save();
   min = minax[ell1];
   if (min < minax[ell2]) min = minax[ell2];
   max = maxax[ell1];
   if (max < maxax[ell2]) max = maxax[ell2];
   if ((max > doub0) && (lg2 != doub0)) steps = doub2 + log(max)/lg2;
      else steps = doub2;
   dist = sepn();
   if (ok[0] != 0) goto out;
   if (debug <= 0)
      printf("doabutb %9g %9g %d %9g\n",
         min,max,steps,dist);
   for (j = 0; j < 3; ++j)
          dx[j] = doub0;
   if (dist == doub0)
/*
   they already just touch -
*/
   {
      if (debug <= 0)
         printf("doabutc %d %d %d %d\n",
           ell1,ell2,refell,axis);
      goto out;
   }
   else
   if (dist < doub0)
/*
   they overlap already, so seek shortest way to separate them -
*/
   {
       mov = doub2*max;
       dx[axis] = mov;
       domoveby(dx[0],dx[1],dx[2],refell);
       forward = sepn();
       if (ok[0] != 0) goto out;
       restore();
       dx[axis] = -mov;
       domoveby(dx[0],dx[1],dx[2],refell);
       back = sepn();
       if (ok[0] != 0) goto out;
       restore();
       if (debug <= 0)
         printf("doabutd %9g %9g %9g %9g\n",
           mov,forward,-mov,back);
       if ((back < doub0) && (forward < doub0))
       {
          ok[0] = 58;
          ok[1] = ell1;
          ok[2] = ell2;
          nerrs = 3;
          goto out;
       }
       else
       if (back > forward) mov = -mov;
       shft = solve(doub0,mov,steps);
   }
   else
/*
  try to overlap them -
*/
   {
      cdist = dcen(d);
      for (j = 0; j < 3; ++ j)
         v[0][j] = d[j] ;
      rotget(r,unr,refell) ;
      vecmul(v,unr,0) ;
      mov = -v[0][axis];
      if (debug <= 0)
            printf("doabute %9g %9g\n",cdist,mov);
      dnew = doubmax;
      xold = mov - max - min;
      for (xnew = mov-max; xnew < (mov+max+min);
              xnew += min*inv2)
      {
         dx[axis] = xnew;
         domoveby(dx[0],dx[1],dx[2],refell);
         dold = dnew;
         dnew = sepn();
	 if (ok[0] != 0) goto out;
         if (debug <= 0)
            printf("doabutf %9g %9g %9g %9g %9g\n",
               cen[ell1][0],cen[ell1][1],cen[ell1][2],xnew,dnew);
         restore();
         if ((mov > doub0) && (dnew < doub0)) goto gotit;
         if ((mov < doub0) && (dnew > dold)) goto gotit;
         xold = xnew;
      }
      shft = xnew;
      goto out;

gotit:
      if ((dold > doub0) && (dnew > doub0)) goto domin;
/*
   they will overlap -
*/
      if (debug <= 0)
         printf("doabutg %9g %9g %9g %9g\n",
                  xold,dold,xnew,dnew);
      shft = solve(xold,xnew,steps);
      goto done;
/*
   they wont overlap so just bring them closest together -
*/
domin:
      if (debug <= 0)
         printf("doabuth %d %9g %9g\n",
           steps,xold-min,xnew);
      shft = fndmin(xold-min,xnew,steps);
   }
/*
   move proportion to abut -
*/
done:
   restore();
   dx[axis] = prop*shft;
   if (debug <= 0)
      printf("doabuti  %9g %9g %9g %9g %9g %9g\n",
        dx[axis],prop,shft,cen[ell1][0],cen[ell1][1],cen[ell1][2]);
   domoveby(dx[0],dx[1],dx[2],refell);

out:
   if (debug <= 0)
      printf("doabutj  %9g %9g %9g %9g %9g %9g\n",
        dx[axis],prop,shft,cen[ell1][0],cen[ell1][1],cen[ell1][2]);
} /* doabut */

