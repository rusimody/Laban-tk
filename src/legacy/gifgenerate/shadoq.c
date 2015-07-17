/*   
         shadoq 
     to add shadows to figures
   
     16 Jan  2003  remove the shadows below ground
     15 Aug  2001  move the shadows below ground
     18 Aug  1993  to accommodate joints
     23 Oct  1992  D.Herbison-Evans  written

   input -  

     a line with number of ellipsoids, frame number
       and 6 viewing parameters,
     then
        lines of numeric data containing the 3d coordinates of 
        the centres, 3 semiaxis lengths and the 3 quaternian angles 
        of the ellipsoids of each picture
   
   output -  
 
     same as input plus extra ellisoids for the shadows
   
     error messages are written to file 'stderr'. 
   
  ******************************************** 
   
     subroutines -

     main   - drives the rest 
     setcns - set up constants pi, etc. 
     input  - read information about current frame from file3 
     mkrotn - convert angles to rotn array entries 
     mkang  - generates angles from rotn array entry 
     shadow - form shadow ellipsoids
     setnup - set up parameters of nth ellipse 
     setmat - find matrix representing an ellipsoid 
     rotget - form a rotation matrix and its inverse 
     matmul - multiply two matrices together 
     setcof - find ellipsoid coefficients from matrix form 
     setaxe - find semiaxes of an ellipse 
     setpro - find orientation and cohen matrix of ellipse 
     store3 - write ellipse parameters on to file 
     ipr    - write out an integer
     ground - find distance of lowest point of ellipsoid from ground
   
  **************************************************** 
   
*/ 
#include <stdio.h>

#define BMAX  256
#define EMAX  1024
#define FMAX  10000
#define TRUE 1
#define FALSE 0

int a1,a2,a3;
int f,h,j,m,n ;
int debug;
int frame;
int nels ;
int njts;
int coel[EMAX][2];
int jnt[EMAX][3];
int vx,vy,vz;
int ok;
int elcol[EMAX+1][4];
int     order[3][3][3] = {
   { {2,1,1},{1,3,4},{1,5,3} },
   { {3,1,5},{1,2,1},{4,1,3} },
   { {3,4,1},{5,3,1},{1,1,2} }};

double sqrt(),atan(),atan2(),cos(),sin();
double ang[4];
double cphi,sphi,phi;
double axxn,axzn;
double ang[4],con[7],elln[4][4],cn[4];
double cen[EMAX+1][4],ax[EMAX+1][4],rotn[EMAX+1][6] ;
double maxax[EMAX+1];
double inv2,doub0,ten,rad10,pi,piby2 ;

char buf[EMAX];
char ename[EMAX][BMAX];
char jname[EMAX][BMAX];
char fname[EMAX][BMAX];

/*****************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
     calls  setcns, input,  shadow, store3.
*/
{
   debug = 1;
   setcns();
      if (debug <= 0) fprintf(stderr,"shadep %d\n",debug);
   ok = TRUE ;
/* 
     read frames, shadow them, and output them -  
*/
   for (  f = 1 ; f <= FMAX ; ++ f )
   {
      input() ;
      if ( ok == FALSE ) goto lab10 ;
      if (nels <= 0) goto lab1 ;
      if (debug <= 0) fprintf(stderr,"maina %s\n",ename[1]);
      shadow();
      if (debug <= 0) fprintf(stderr,"mainb %s\n",ename[1]);
      if ( ok == FALSE ) goto lab10;
      store3();
      if (debug <= 0) fprintf(stderr,"mainc %s\n",ename[1]);
   }
   goto lab1;
/* 
     snags -  
*/
lab10: fprintf(stderr,
      "fail in frame %d\n number of ellipsoids %d\n max number %d\n",
      frame,nels,EMAX);

lab1: nels = 0 ;
   printf(" %5d %5d 0 0 0 0 0 0\n", nels,frame );
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

   if (debug <= 0) fprintf(stderr,"setcnsa %f\n",3.0);
   doub0 = (double)0;
   inv2 = (double)1/(double)2;
   ten = 10.0;
   pi = 4.0*atan(1.0) ;
   piby2 = pi/2.0;
   rad10 = atan(1.0)/450.0 ;
} /* setcns */
/*****************************************/

input()
/* 
        read information about current frame -  
    nels - the number of ellipsoids in it 
         (zero is null as end - of - file marker) 
    frame - the name of the current frame (f is its number) 
         the first frame name is set as the value of debug. 
    vx,vy,vz,a1,a2,a3 - the view,
    then for each ellipsoid, its 3 axis lengths, coordinates 
         of its centre, its angles of orientation, its colours,
         its name, and the name of a possible texture file. 
    
     called by main 
     calls  mkrotn 
*/
{
   int axx,axy,axz,cenx,ceny,cenz,ang1,ang2,ang3;
   int e ;
   int flag;

   scanf("%d %d %d %d %d %d %d %d\n",
      &nels,&frame,&vx,&vy,&vz,&a1,&a2,&a3);
   if (f == 1) 
   {
      debug = frame ;
      if (debug <= 0)
         fprintf(stderr,"inputa %d\n", debug );
   }
   if (debug <= 0)
      fprintf(stderr,
        "inputb pic %d no els %d frame no %d\n",f,nels,frame );
   if (nels > EMAX)
   {
      fprintf(stderr,
          "shade: too many ellipsoids: %d , max %d, frame %d\n",
          nels,EMAX,frame);
      exit(1);
   }
   if (nels <= 0)
   {
      printf("%d %d %d %d %d %d %d %d\n",
         nels,frame,vx,vy,vz,a1,a2,a3);
      exit(0);
   }
/* 
     read ellipsoids in current frame -  
*/
   for (  e = 1 ; e <= nels ; ++ e )
   {
      if ( NULL == gets(buf))
      {
         fprintf(stderr,
           "unexpected eof in reading ellipsoid %d in frame %d\n",
           e,frame);
         exit(1);
      }
      sscanf(buf,"%d %d %d %d %d %d %d %d %d %d %d %d %s %s\n",
         &axx,&axy,&axz,&cenx,&ceny,&cenz,&ang1,&ang2,&ang3,
         &elcol[e][1],&elcol[e][2],&elcol[e][3],ename[e],fname[e]);
      if (debug <= 0)
         fprintf(stderr,"inputc %d %d %d %d %d %d %d %d %d %d %s %s\n",
         e,axx,axy,axz,
         cenx,ceny,cenz,
         ang1,ang2,ang3,ename[e],fname[e]);
/* 
     scale everything back to size -  
*/
      ax[e][1] = 0.1*axx ;
      ax[e][2] = 0.1*axy ;
      ax[e][3] = 0.1*axz ;
      cen[e][1] = 0.1*cenx ;
      cen[e][2] = 0.1*ceny ;
      cen[e][3] = 0.1*cenz ;
      ang[1] = rad10*ang1 ;
      ang[2] = rad10*ang2 ;
      ang[3] = rad10*ang3 ;
      if (debug <= 0)
         fprintf(stderr,"inputd %f %f %f %f %f %f %f %f %f %f\n",
         rad10,ax[e][1],ax[e][2],ax[e][3],
         cen[e][1],cen[e][2],cen[e][3],
         ang[1],ang[2],ang[3]);
      maxax[e] = ax[e][1];
      if (maxax[e] < ax[e][2]) maxax[e] = ax[e][2];
      if (maxax[e] < ax[e][3]) maxax[e] = ax[e][3];
/* 
     set up orientation matrix of current ellipsoid -  
*/
      mkrotn(e,ang[1],ang[2],ang[3]) ;
   }
   scanf("%d %d\n",&flag,&njts);
   if (debug <= 0) fprintf(stderr,"%d %d\n",flag,njts);
   if (flag < 0)
   {
      for (  e = 0 ; e < njts ; ++ e )
      {
         if ( NULL == gets(buf))
         {
            fprintf(stderr,
              "unexpected end of file in reading joint %d in frame %d\n",
              e,frame);
            exit(1);
         }
         sscanf(buf,"%d %d %d %d %d %s\n",
            &coel[e][0],&coel[e][1],
            &jnt[e][0],&jnt[e][1],&jnt[e][2],jname[e]);
      }
   }
} /* input */
/**********************************************/

mkrotn(n,a1,a2,a3)
   int n ;
   double a1,a2,a3 ;
/* 
     convert angles a1,a2,a3 into rotn entries 
   
     called by input, shadow. 
*/
{
   double s1,c1,s2,c2,s3,c3 ;

   if (debug <= 0)
      fprintf(stderr,"mkrotn  %d %f %f %f\n", n,a1,a2,a3 );
   s1 = sin(a1) ;
   c1 = cos(a1) ;
   s2 = sin(a2) ;
   c2 = cos(a2) ;
   s3 = sin(a3) ;
   c3 = cos(a3) ;
   rotn[n][1] = c1*c2 ;
   rotn[n][2] = s1*c2 ;
   rotn[n][3] = s2 ;
   rotn[n][4] = s3 ;
   rotn[n][5] = c3 ;
} /* mkrotn */
/*********************************************/

rotput(r,n)
      int n ;
      double r[3][3] ;
/*
   interpret rotation matrix 'r' as direction cosines of a
   rotation axis, and the sine and cosine of a rotation about
   that axis, and store in array 'rotn'.

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

     x,y,z are stored in rotn[n,0], rotn[n,1], rotn[n,2]
     s,c   are stored in rotn[n,3], rotn[n,4]

   see 'Control of round-off propagation in articulating the
        human figure', D.Herbison-Evans and D.S.Richardson
        Computer Graphics and Image Processing,
        Vol 17 pp 386-393 (1981)

   called by shadow
*/
{
      int j,k ;
      double a[3][3],b[3],d[3],e,f,g,c,s,trace ;
      double csq;
      double acc = {0.000002} ;
      double sqrt();

      if (debug <= 0)
         fprintf(stderr,"rotputa %d\n",n);
      if (debug < 0)
      {
         for (k = 0; k < 3; ++k)
            fprintf(stderr,"      %f %f %f\n",r[k][0],r[k][1],r[k][2]);
      }
      b[0] = r[1][2]-r[2][1] ;
      b[1] = r[2][0]-r[0][2] ;
      b[2] = r[0][1]-r[1][0] ;
      e = b[0]*b[0]+b[1]*b[1]+b[2]*b[2] ;
      trace = r[0][0]+r[1][1]+r[2][2] ;
      g = sqrt(e) ;
      if (debug < 0)
           fprintf(stderr,"rotputb %f %f %f %f\n",trace,g,e,acc);

      if (e <= acc) goto lab1 ;

      f = 1.0/g ;
      rotn[n][1] = f*b[0] ;
      rotn[n][2] = f*b[1] ;
      rotn[n][3] = f*b[2] ;

      if (debug < 0) fprintf(stderr,"rotputc %d %f %f %f %f\n",
                            debug,f,b[0],b[1],b[2]);
/*
     use g=2s, and trace=1+2c to find s and c -
*/
      s = 0.5*g;
      csq = 1.0-s*s;
      if (csq < 0.0) csq = 0.0;
      c = sqrt(csq);
      if (trace < 1.0) c = -c;
      if (debug < 0) fprintf(stderr,"rotputf %f %f\n",s,c);
      rotn[n][4] = s ;
      rotn[n][5] = c ;
      goto lab10 ;
/*
   symmetric matrix (180 or 360 degree rotation) -
*/
lab1: if (debug < 0)
      {
         fprintf(stderr,
            "rotput1 symmetric matrix, frame %d, ellipsioid %d\n",frame,n);
         fprintf(stderr,"trace %f, g %f, e %f, acc %f\n",trace,g,e,acc);
         for (k = 0; k < 3; ++k)
            fprintf(stderr,"      %f %f %f\n",r[k][0],r[k][1],r[k][2]);
      }
      c = 0.5*(trace-1.0);
      for (  j = 0 ; j < 3 ; ++ j )
      {
         d[j] = 0.0 ;

/*   run across a row- */

         for (  k = 0 ; k < 3 ; ++ k )
         {
            a[j][k] = r[j][k]+r[k][j] ;
            if (j == k) a[j][j] = 2.0*(r[j][j]-c) ;
            d[j] = d[j]+a[j][k]*a[j][k] ;
         }
      }

/*   choose most stable row- */

      j = 0 ;
      if (d[1] > d[0]) j = 1 ;
      if (d[2] > d[j]) j = 2 ;
      if (d[j] != 0.0) f = 1.0/sqrt(d[j]) ;
         else
         {
            f = 1.0;
            a[j][0] = 1.0;
         }
      rotn[n][1] = f*a[j][0] ;
      rotn[n][2] = f*a[j][1] ;
      rotn[n][3] = f*a[j][2] ;
      rotn[n][4] = 0.5*g ;
      rotn[n][5] = c ;

  lab10:
      for (k = 1; k <= 5; ++k)
      {
         if (rotn[n][k] >  1.0) rotn[n][k] =  1.0;
         if (rotn[n][k] < -1.0) rotn[n][k] = -1.0;
      }
}  /* rotput */
/********************************************/

rset(r,angl,axis)
      int axis ;
      double angl,r[3][3] ;
/*
   set up the rotation matrix 'r' for a rotation of
   'angl' radians about 'axis'.

   called by  shadow
*/
{
      double v[5] ;
      int i,j,k;

      if (debug <= 0) fprintf(stderr,"rset %d %f\n",axis,angl);
      v[0] = 0.0 ;
      v[1] = 1.0 ;

/*   fill out values vector with sin and cos- */

      v[2] = cos(angl) ;
      v[3] = sin(angl) ;
      v[4] = -v[3] ;

/*   choose appropriate permutation of values for rotation axis- */

      for (  i = 0 ; i < 3 ; ++ i )
      {
         for (  j = 0 ; j < 3 ; ++ j )
         {
            k = order[axis][j][i] ;
            r[i][j] = v[k-1] ;
         }
      }
}  /* rset */
/************************************/

mkang(n)
      int n ;
/*
   get angles from nth entry in rotn 

   called by  store3. 
*/
{
      double x,y,z,s1,c1,m1 ;
      
      x = rotn[n][1] ;
      y = rotn[n][2] ;
      z = rotn[n][3] ;
      s1 = z ;
      m1 = 1.0-z*z ;
      if (m1 > 0.0) c1 = sqrt(m1) ; else c1 = 0.0 ;
      if ((x == 0.0 ) && ( y == 0.0))
          ang[1] = 0.0;
             else ang[1] = atan2(y,x) ;
      ang[2] = atan2(s1,c1) ;
      ang[3] = atan2(rotn[n][4],rotn[n][5]) ;
}  /* mkang */
/**********************************************************/

shadow()
/* 
   find the shadow ellipsoids of each ellsoid in the scene

     called by main 
     calls   setnup, rset, rotput, ground.
*/
{
   int k;
   float y;
   double r[3][3];
   double ground();

   if (debug <= 0)
      fprintf(stderr,"shadowa %d\n", nels );
/* 
     run thru ellipsoids to shadow each in turn -  
*/
    k = nels;
    for (  n = 1 ; n <= nels ; ++ n )
    {
         if (debug <= 0) fprintf(stderr,"shadowb %s\n",ename[1]);
         setnup();
         if (debug <= 0) fprintf(stderr,"shadowc %s\n",ename[1]);
         y = ground(n);
         if (y > 0.0)
         {
            ++k;
	    cen[k][1] = cen[n][1];
            cen[k][2] = -0.2;
            cen[k][3] = cen[n][3];
            ax[k][1] = axxn;
            ax[k][2] = 0.2;
            ax[k][3] = axzn;
            rset(r,phi,1);
            if (debug <= 0) fprintf(stderr,"shadowd %s\n",ename[1]);
            rotput(r,k);
            if (debug <= 0) fprintf(stderr,"shadowe %s\n",ename[1]);
            elcol[k][1] = 25;
            elcol[k][2] = 25;
            elcol[k][3] = 25;
            sprintf(ename[k],"%ssh",ename[n]);
            sprintf(fname[k],"%d",k);
         } /* y > 0 */
    } /* end n loop */
    nels = k;
    if (debug <= 0) fprintf(stderr,"shadowf %d %d %d\n",
         f,frame,nels); 
rtrn:;
} /* shadow */
/******************************************/

setnup()
/* 
     set up parameters of nth ellipsoid relative to own centre. 
   
     called by shadow 
     calls  setmat, setcof, setaxe, setpro 
*/
{
   double axe[3];

   if (debug <= 0) fprintf(stderr,"setnupa  %d\n",n);
   setmat(n,elln) ;
   if ( ok == FALSE ) goto lab1 ;
   setcof(con,elln) ;
   if ( ok == FALSE ) goto lab1 ;
   setaxe(axe,con) ;
   if ( ok == FALSE ) goto lab1 ;
   axxn = axe[1];
   axzn = axe[2];
   if (debug <= 0)
      fprintf(stderr,"setnupb  %f %f %f %f\n",axe[1],axe[2],axxn,axzn);
   setpro(axe,con) ;
   if ( ok == FALSE ) goto lab1 ;
   goto rtrn ;
/* 
     snag -  
*/
lab1: ok = FALSE;
   fprintf(stderr,
      "prog sha   subr setnup  snag in ellipsoid   %d %f\n",n,elln );

rtrn:;
} /* setnup */
/******************************************/

setmat(n,el)
   int n;
   double el[4][4] ;
/* 
     this finds the matrix "el" of the quadratic form of the "n"th 
     ellipsoid by taking the diagonal matrix of inverse square semiaxes, 
     and doing on it a similarity transform for its own rotation. 
   
     called by setnup
     calls  rotget, matmul 
*/
{
   int ii,j ;
   double r[4][4],unr[4][4] ;

   if (debug <= 0)
      fprintf(stderr,"setmat %d %f %f\n", n,rotn[n][1],ax[n][1] );
/* 
     initialise diagonal matrix -  
*/
   for (  ii = 1 ; ii <= 3 ; ++ ii )
   {
      for (  j = 1 ; j <= 3 ; ++ j )
      {
         el[ii][j] = 0.0 ;
      }
      if ( ax[n][ii]*ax[n][ii]  ==  0.0 ) goto lab3 ;
      el[ii][ii] = 1.0/(ax[n][ii]*ax[n][ii]) ;
   }

   rotget(r,unr,n);
/* 
  do similarity transform -  
*/
   matmul(el,unr,el) ;
   matmul(r,el,el) ;
   goto rtrn ;

lab3:  fprintf(stderr," sha   subr setmat  ax[ %d ][ %d ] = 0\n",n,ii );
   ok = FALSE ;
rtrn:;
} /* setmat */
/**********************************************/

rotget(r,unr,n)
   int n ;
   double r[4][4],unr[4][4] ;
/* 
     form a rotation matrix r and its inverse unr 
     from the nth entries in rotn 
   
     called by setmat, ground.
*/
{
   int i,j ;
   double cp,sp,x,y,z,m,xsp,ysp,zsp,xm,ym,zm,xym,xzm,yzm ;

   if (debug <= 0)
      fprintf(stderr,"rotget %d %f %f %f %f %f\n",
         n,rotn[n][1],rotn[n][2],rotn[n][3],rotn[n][4],rotn[n][5]);
   x = rotn[n][1] ;
   y = rotn[n][2] ;
   z = rotn[n][3] ;
   sp = rotn[n][4] ;
   cp = rotn[n][5] ;
   m = 1.0 - cp ;
   xm = x*m ;
   ym = y*m ;
   zm = z*m ;
   xsp = x*sp ;
   ysp = y*sp ;
   zsp = z*sp ;
   xym = x*ym ;
   xzm = x*zm ;
   yzm = y*zm ;
   r[1][1] = x*xm+cp ;
   r[1][2] = xym+zsp ;
   r[1][3] = xzm - ysp ;
   r[2][1] = xym - zsp ;
   r[2][2] = y*ym+cp ;
   r[2][3] = yzm+xsp ;
   r[3][1] = xzm+ysp ;
   r[3][2] = yzm - xsp ;
   r[3][3] = z*zm+cp ;

   for (  i = 1 ; i <= 3 ; ++ i )
   {
      for (  j = 1 ; j <= 3 ; ++ j )
      {
         unr[i][j] = r[j][i] ;
      }
   }

   if (debug <= 0)
   {
      fprintf(stderr,"rotgeta   %f %f %f\n",r[1][1],r[1][2],r[1][3]);
      fprintf(stderr,"          %f %f %f\n",r[2][1],r[2][2],r[2][3]);
      fprintf(stderr,"          %f %f %f\n",r[3][1],r[3][2],r[3][3]);
   }
} /* rotget */
/**********************************************/

matmul(a,b,ans)
   double a[4][4],b[4][4],ans[4][4] ;
/* 
     this multiplies matrix "b" by "a" 
     and puts the product in "ans". 
     it is done via an intermediate matrix "c" to allow matmul 
     to be used with the same matrix for "a\n", "b", and/or "ans". 
   
     called by setmat 
*/
{
   int i,j,k ;
   double x,c[4][4] ;

   for (  i = 1 ; i <= 3 ; ++ i )
   {
      for (  j = 1 ; j <= 3 ; ++ j )
      {
         x = 0.0 ;
         for (  k = 1 ; k <= 3 ; ++ k )
         {
            x = x+a[i][k]*b[k][j] ;
         }
         c[i][j] = x ;
      }
   }
   for (  i = 1 ; i <= 3 ; ++ i )
   {
      for (  j = 1 ; j <= 3 ; ++ j )
      {
         ans[i][j] = c[i][j] ;
      }
   }
} /* matmul */
/******************************************/

setcof(coef,el)
   double coef[7],el[4][4] ;
/* 
     set up coeffs of outline ellipse of an ellipsoid about 
     its own centre in the form -  
   
     coef(1)*x**2 + coef[2]*z**2 + coef[3]*x*z 
         + coef(4)*x + coef[5]*z + coef[6] = 0 
   
     called by setnup
*/
{
   double den ;

   if (debug <= 0)
      fprintf(stderr,"setcof %f\n", el[1][1]);
   if (el[2][2] == 0.0) goto lab1 ;
   den = 1.0/el[2][2] ;
   coef[1] = el[1][1] - el[1][2]*el[1][2]*den ;
   coef[2] = el[3][3] - el[2][3]*el[2][3]*den ;
   coef[3] = 2.0*(el[1][3] - el[1][2]*el[2][3]*den) ;
   coef[4] = 0.0 ;
   coef[5] = 0.0 ;
   coef[6] =  - 1.0 ;
   goto rtrn ;
/* 
     snags -  
*/
lab1:  fprintf(stderr," sha   matrix error in subr setcof\n %f %f %f\n",
      el[1][1],el[1][2],el[1][3]);
   ok = FALSE ;
rtrn:;
} /* setcof */
/************************************************/

setaxe(axe,coef)
   double axe[3],coef[7];
/* 
     find semiminor axis, axe[1], and semimajor axis, axe[2], of ellipse 
     described by coef. 
   
     called by setnup 
*/
{
   double discrt,lamx,lamy,c12,rtdis ;

   lamx = 1 ;
   lamy = 1 ;
   if (debug <= 0)
      fprintf(stderr,"setaxea %f\n", coef[1]);
   discrt = (coef[1] - coef[2])*(coef[1] - coef[2])+ coef[3]*coef[3];
   if (discrt < 0.0) goto lab1 ;
   c12 = 0.5*(coef[1]+coef[2]) ;
   rtdis = 0.5*sqrt(discrt) ;
   lamx = c12+rtdis ;
   lamy = c12 - rtdis ;
   if (lamx <= 0.0) goto lab1 ;
   if (lamy <= 0.0) goto lab1 ;
   axe[1] = 1.0/sqrt(lamx) ;
   axe[2] = 1.0/sqrt(lamy) ;
   goto rtrn ;
/* 
     snags -  
*/
lab1: fprintf(stderr,"sha   subr setaxe snag %f %f %f %d\n",
         lamx,lamy,discrt,n);
   ok = FALSE ;
rtrn:if (debug <= 0) fprintf(stderr,"setaxeb %f %f\n",axe[1],axe[2]);
} /* setaxe */
/******************************************/

setpro(axe,coef)
   double axe[3],coef[7];
/* 
     for the outline of nth ellipsoid, find
     angle between axx axis and scene x axis, phi, 
   
     called by setnup 
*/
{
   double ec,spcp,spsq,cpsq,invec ;

   if (debug <= 0)
      fprintf(stderr,"setpro %f %f\n", axe[1],axe[2] );
/* 
     find orientation of axx axis -  
*/
   phi = pi - 0.5*atan2(coef[3], coef[1] - coef[2]) ;
   if (phi < 0.0) phi = phi+pi+pi ;
} /* setpro */
/******************************************/

store3()
/*
    print out axes, centres, orientations and colours
    of  nels ellipsoids starting at 1

    called by main.
    calls  ipr. 
*/
{
   char name[BMAX];
   int   j,k;
   
   printf("%d %d %d %d %d %d %d %d\n",
      nels,frame,vx,vy,vz,a1,a2,a3);
   
   for (j = 1; j <= nels; j++)
   {
      mkang(j);
      if (debug <= 0) fprintf(stderr,"store3b %d %f\n",j,ang[0]);
      for (k = 1; k <= 3; k++) ipr(ten*ax[j][k]);
      for (k = 1; k <= 3; k++) ipr(ten*cen[j][k]);
      for (k = 1; k <= 3; k++) ipr(ang[k]/rad10);
      for (k = 1; k <= 3; k++) printf("%6d",elcol[j][k]);
      printf(" %s %s\n",ename[j],fname[j]);
   }
   printf("-1 %d\n",njts);
   for (j = 0; j < njts; j++)
   {
      printf("%d %d %d %d %d %s\n",
         coel[j][0],coel[j][1],
         jnt[j][0],jnt[j][1],jnt[j][2],jname[j]);
   }
}  /* store3 */
/************************************************************/

ipr(x)
double x;
/*
    print out integral part

    called by store3.
*/
{
      int k;

      if (x > doub0) k = (int)(x+inv2);
         else k = (int)(x-inv2);
      printf("%d ",k);
}  /* ipr */
/*************************************************************/

double ground(i)
int i;
/*
   find distance of lowest point above the ground
   of the ellipsoid 'i'.

   called by  shadow.
   calls      rotget.
*/
{
   int n ;
   double toty,x,y,z,r[4][4],unr[4][4] ;
   double val;
   double sq;
   double sqt;

   if (debug <= 0)
      printf("grounda %3d\n",i);
   val = cen[i][2];

/*   find lowest point- */

   rotget(r,unr,i) ;
   x = unr[1][2]*ax[i][1] ;
   y = unr[2][2]*ax[i][2] ;
   z = unr[3][2]*ax[i][3] ;
   sq = x*x+y*y+z*z;
   if (sq > doub0) sqt = sqrt(sq); else sqt = doub0;
   val = cen[i][2] - sqt ;
   if (debug <= 0)
   {
      printf(
         "groundb %3d %9g %9g %9g %9g %9g %9g\n",
      i,ax[i][1],ax[i][2],ax[i][3],unr[1][2],unr[2][2],unr[3][2]);
      printf("    %9g %9g %9g %9g %9g\n",
      x,y,z,cen[i][2],val);
   }
   return(val);
}  /* ground */
/**********************************************************/
