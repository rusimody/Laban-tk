/*   viewb.c
 
     This program reads a set of 3-d specifications of ellipsoids
     in each frame of the movie, together with viewing transform
     parameters, and then performs the viewing transform,
     outputting another 3-d ellipsoid file. 

    2 Aug 1993 allows joint information
   15 Oct 1992 written : Don Herbison-Evans
   
     subroutines - 
        main  - organises the rest
        rotget- retrieves rotation matrix from quat array 
        rotput- stores rotation matrix into quat array 
        spinto- spins a set of ellipsoids to a given orientation 
        spinby- spins a set of ellipsoids by a given angle 
        twirl - does a rotation on all parts in list 
        matmul- multiplies 2 matrices together 
        matrot- rotates a single ellipsoid 
        vecmul- multiplies a selected vector by a matrix 
        vecmat- multiplies a vector by a matrix 
        mkang - generates angles from quat array entry 
        shift - moves a set of ellipsoids 
        rset  - sets up a primitive rotation matrix 
        mkquat- generates quat array entry from angles 
        store3- stores data onto file3 about given frame 
        ipr   - print out integral parts to six places
   
*************************************************************/

#include <stdio.h>
#include <values.h>

#define TRUE    1
#define FALSE   0
#define BMAX  256
#define EMAX 1024

char    buf[BMAX];
char    ename[EMAX][BMAX];
char    fname[EMAX][BMAX] ;
char    jname[EMAX][BMAX];

double  sin(),cos(),atan(),atan2(),log(),sqrt();

double  ang[3];       /* Eulerian angles of an ellipsoid */
double  ax[EMAX][3];  /* length of semiaxes of ellipsoids  */
double  cen[EMAX][3]; /* coordinates of centres of ellipsoids */
double  doub1;        /* a double constant */
double  inv2;
double  jnt[EMAX][3]; /* coordinates of joints between ellipsoids */
double  doub0;
double  obs[3][3];    /* rotation matrix applied to all ellipsoids
                         to obtain observers view  */
double  place[3];     /* position of centre of observers attention */
double  rad10;        /* conversion factor from tenths of a degree
                         to radians */
double  quat[EMAX+2][5]; /* angles of ellipsoids  */
/*        j = 1,2,3 - components of direction of rotation axis  */
/*        j = 4,5   - sine and cosine of rotation about axis  */
double  ten;
double  tenth;
double  twopi;

int     coel[EMAX][2];   /* ellipsoids meeting at each joint */
int     elcol[EMAX][3] ; /* red, green, blue of each ellipsoid */
int     debug;           /*  <= 0 for diagnostic output  */
int     f;               /* counter through frames */
int     flag1;           /* negative if frame contains joints */
int     flag2;           /* number of joints if joints in file */
int     frame;           /* current actual frame name  */
int     iplx,iply,iplz,iobs0,iobs1,iobs2; /* viewing data */
int     nels;            /* number of ellipsoids  */
int     njts;            /* number of joints */
int     order[3][3][3] = {
      { {2,1,1},{1,3,4},{1,5,3} },
      { {3,1,5},{1,2,1},{4,1,3} },
      { {3,4,1},{5,3,1},{1,1,2} }};

/***************************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
     calls  input, store3. 
*/
{
   debug = 1;
   doub0 = (double)0;
   doub1 = (double)1;
   ten = (double)10;
   tenth = doub1/ten;
   inv2 = doub1/(double)2;
   twopi = (double)8*atan(doub1);
   rad10 = twopi/(double)3600;
   flag1 = -1;
   flag2 = 0;
   njts = 0;
/* 
     read frames and do them -  
*/
   for (  f = 1 ; f < MAXINT ; ++ f )
   {
      input() ;
      store3();
      if (nels <= 0) exit(0);
   }
} /* main */
/****************************************************/

input()
/* 
  read information about current frame -  
    nels - the number of ellipsoids in it 
         (zero is null as end - of - file marker) 
    frame - the name of the current frame (f is its number) 
            (debug is set to the first frame name) 
    place[3] - centre of viewing point.
    obsang[3] - angles of view.

  then for each ellipsoid, its 3 axis lengths, coordinates 
         of its centre, its angles of orientation, its colours,
         its name, and the name of its texture map file. 
    
     called by main 
     calls  mkquat 
*/
{
   int iax[3],icen[3],ijnt[3];
   int ang1,ang2,ang3;
   int j,n;
   double obsang[3];
   double invobs[3][3];

   if (flag1 < 0) scanf("%d %d %d %d %d %d %d %d\n",
      &nels,&frame,&iplx,&iply,&iplz,&iobs0,&iobs1,&iobs2);
   else
   {
      nels = flag1;
      frame = flag2;
   }
   if (f == 1) 
   {
      debug = frame ;
      if (debug < 1)
         fprintf(stderr,"prog -  viewb  debug = %d\n", debug );
   }
   if (debug < 0) fprintf(stderr,"inputa %d %d %d %d %d %d %d %d\n",
      nels,frame,iplx,iply,iplz,iobs0,iobs1,iobs2);
   if (nels > EMAX)
   {
      fprintf(stderr,
         "\nERROR in viewb: too many ellipsoids: %d, max %d\n",
          nels,EMAX);
      exit(1);
   }
   if (nels > 0)
   {
      place[0] = tenth*(double)iplx;
      place[1] = tenth*(double)iply;
      place[2] = tenth*(double)iplz;
      obsang[0] = rad10*(double)iobs0;
      obsang[1] = rad10*(double)iobs1;
      obsang[2] = rad10*(double)iobs2;
      mkquat(nels,obsang[0],obsang[1],obsang[2]);
      rotget(obs,invobs,nels);
/* 
     read ellipsoids in current frame -  
*/
      for ( n = 0 ; n < nels ; ++ n )
      {
         scanf("%d %d %d %d %d %d %d %d %d %d %d %d %s %s\n",
               &iax[0],&iax[1],&iax[2],
               &icen[0],&icen[1],&icen[2],
               &ang1,&ang2,&ang3,
               &elcol[n][0],&elcol[n][1],&elcol[n][2],
               ename[n],fname[n]);
         if (debug <= 0)
         fprintf(stderr,
            "inputb %d %d %d %d %d %d %d %d %d %d %d %d %s %s\n",
               iax[0],iax[1],iax[2],
               icen[0],icen[1],icen[2],
               ang1,ang2,ang3,
               elcol[n][0],elcol[n][1],elcol[n][2],
               ename[n],fname[n]);
/* 
     scale everything back to size -  
*/
         for ( j = 0; j < 3; ++j )
         {
            ax[n][j] = tenth*(double)iax[j] ;
            cen[n][j] = tenth*(double)icen[j] ;
         }
         mkquat(n,
           rad10*(double)ang1,rad10*(double)ang2,rad10*(double)ang3);
      }
/*
     now for the joints, if any, -
*/
      gets(buf);
      sscanf(buf,"%d %d %d %d %d %d %d %d\n",
         &flag1,&flag2,&iplx,&iply,&iplz,&iobs0,&iobs1,&iobs2);
      if (flag1 < 0)
      {
         njts = flag2;
         for ( n = 0 ; n < njts ; ++ n )
         {
            scanf("%d %d %d %d %d %s\n",
                  &coel[n][0],&coel[n][1],
                  &ijnt[0],&ijnt[1],&ijnt[2],jname[n]);
            for(j = 0; j < 3; ++j)
            {
               jnt[n][j] = tenth*(double)ijnt[j] ;
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
      fprintf(stderr,"mkquat  %d %f %f %f\n", n,a1,a2,a3 );
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

rotget(r,unr,n)
      int n ;
      double r[3][3],unr[3][3] ;
/*
   form a rotation matrix r and its inverse unr
   from the nth entries in quat

   called by   matrot, spinto, spinby.
*/
{
      int i,j ;
      double cp,sp,x,y,z,m,xsp,ysp,zsp,xm,ym,zm,xym,xzm,yzm ;

      if (debug <= 0) fprintf(stderr,"rotgeta    %d %f %f %f %f %f\n",
          n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      x = quat[n][0] ;
      y = quat[n][1] ;
      z = quat[n][2] ;
      sp = quat[n][3] ;
      cp = quat[n][4] ;
      m = 1.0-cp ;
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
            unr[i][j] = r[j][i] ;
         }
         if (debug <= 0) fprintf(stderr,"rotgetb %f %f %f\n",
            r[i][0],r[i][1],r[i][2]);
      }
}  /* rotget */
/**************************************/

rotput(r,n)
      int n ;
      double r[3][3] ;
/*
   Interpret rotation matrix 'r' as direction cosines of a
   rotation axis, and the sine and cosine of a rotation about
   that axis, and store in array 'quat'.

   Uses the fact that any rotation matrix can be written as -

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

   see 'Control of round-off propagation in articulating the
        human figure', D.Herbison-Evans and D.S.Richardson
        Computer Graphics and Image Processing,
        vol 17 pp 386-393 (1981)

   called by  matrot, spinto.
*/
{
      int j,k ;
      double a[3][3],b[3],d[3],e,f,g,c,s,trace ;
      double csq;
      double acc = {0.000002} ;

      if (debug < 0)
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
      f = 1.0;
      if (debug < 0)
           fprintf(stderr,"rotputb %f %f %f %f\n",trace,g,e,acc);

      if (g <= acc) goto lab1 ;

      f = 1.0/g ;
      quat[n][0] = f*b[0] ;
      quat[n][1] = f*b[1] ;
      quat[n][2] = f*b[2] ;

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
      if (debug < 0) fprintf(stderr,"rotputd %f %f\n",s,c);
      quat[n][3] = s ;
      quat[n][4] = c ;
      goto lab10 ;
/*
   symmetric matrix (180 or 360 degree rotation) -
*/
lab1: if (debug < 0)
      {
         fprintf(stderr,
            "rotpute symmetric matrix, frame %d, ellipsioid %d\n",frame,n);
         fprintf(stderr,"   trace %f, g %f, e %f, acc %f\n",trace,g,e,acc);
         for (k = 0; k < 3; ++k)
            fprintf(stderr,"         %f %f %f\n",r[k][0],r[k][1],r[k][2]);
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
         if (debug < 0) fprintf(stderr,"rotputf %d %f %f %f %f\n",
                               j,a[j][0],a[j][1],a[j][2],d[j]);
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
      quat[n][0] = f*a[j][0] ;
      quat[n][1] = f*a[j][1] ;
      quat[n][2] = f*a[j][2] ;
      quat[n][3] = 0.5*g ;
      quat[n][4] = c ;
      if (debug < 0)
         fprintf(stderr,"rotputg %d %f %f %f %f %f %f\n",
            j,a[j][0],a[j][1],a[j][2],d[j],f,g);

  lab10: if (debug < 0)
         fprintf(stderr,"rotputh    %d %f %f %f %f %f\n",
         n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      for (k = 0; k < 5; ++k)
      {
         if (quat[n][k] >  1.0) quat[n][k] =  1.0;
         if (quat[n][k] < -1.0) quat[n][k] = -1.0;
      }
}  /* rotput */
/**********************************************************/

twirl(x,y,z,r)
      double x,y,z ;
      double r[3][3] ;
/*
   Rotates all the rotation matrices 'quat', centres 'cen',
   of ellipsoids, and joints 'jnt',  about a point 'x,y,z' 
   using rotation matrix 'r'.

   called by  store3.
   calls  shift, matrot, vecmul.
*/
{
      double ra[3][3],rb[3][3];
      int i,k ;

      if (debug <= 0) fprintf(stderr,"twirla\n");
      shift(-x,-y,-z) ;
      if (debug < 0)
      {
         fprintf(stderr,"twirlb\n");
         for (i = 0; i < 3; ++i)
            fprintf(stderr,"   %f %f %f\n",r[0][i],r[1][i],r[2][i]);
         k = 1;
         fprintf(stderr,"twirlc %d %f %f %f %f %f\n",
            k,quat[k][0],quat[k][1],quat[k][2],
            quat[k][3],quat[k][4]);
      }

/*   rotate the ellipsoids and their centres- */

      for (  k = 0 ; k < nels ; ++ k )
      {
            matrot(r,k) ;
            vecmul(cen,r,k) ;
            if (debug <= 0)
               fprintf(stderr,"twirld %d %f %f %f\n",
                  k,cen[k][0],cen[k][1],cen[k][2]);
      }

/*   rotate the joints - */

      for (  k = 0 ; k < njts ; ++ k )
      {
            if (debug <= 0)
               fprintf(stderr,"twirle %d %f %f %f\n",
                  k,jnt[k][0],jnt[k][1],jnt[k][2]);
            vecmul(jnt,r,k) ;
            if (debug <= 0)
               fprintf(stderr,"twirlf %d %f %f %f\n",
                  k,jnt[k][0],jnt[k][1],jnt[k][2]);
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

     called by  matrot, spinby, getmat.
*/
{
      int i,j,k ;
      double x,c[3][3] ;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         for (  j = 0 ; j < 3 ; ++ j )
         {
            x=0.0 ;
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

/*   this rotates the 'n'th ellipsoid by rotation matrix 'r'. */

/*   called by twirl */
/*   calls  rotget, matmul, rotput */

{
      double ro[3][3],unro[3][3] ;

      if (debug <= 0) fprintf(stderr,"matrota    %d %f %f %f %f %f\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      rotget(ro,unro,n) ;
      if (debug < 0) fprintf(stderr,"matrotb    %d %f %f %f %f %f\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      matmul(r,ro,ro) ;
      rotput(ro,n) ;
      if (debug < 0) fprintf(stderr,"matrotc    %d %f %f %f %f %f\n",
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

   called by  touch, moveby, twirl.
*/
{
      int i,j ;
      double vv[3],x ;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         x = 0.0 ;
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

   called by  ratio, balanc.
*/
{
      int i,j ;
      double vv[3],x ;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         x = 0.0 ;
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
   get angles from nth entry in quat 

   called by angles, store3. 
*/
{
      double x,y,z,s1,c1,m1 ;
      
      x = quat[n][0] ;
      y = quat[n][1] ;
      z = quat[n][2] ;
      s1 = z ;
      m1 = 1.0-z*z ;
      if (debug <  0)
         fprintf(stderr,"mkanga %d %f %f %f %f %f\n",
                    n,quat[n][0],quat[n][1],quat[n][2],s1,m1);
      if (m1 > 0.0) c1 = sqrt(m1) ;
         else c1 = 0.0 ;
      if (debug < 0)
         fprintf(stderr,"mkangb %f %f %f\n",
            c1,quat[n][3],quat[n][4]);
      if ((x == 0.0 ) && ( y == 0.0))
          ang[0] = 0.0;
             else ang[0] = atan2(y,x) ;
      if ((s1 == 0.0 ) && ( c1 == 0.0))
          ang[1] = 0.0;
             else ang[1] = atan2(s1,c1) ;
      if ((quat[n][3] == 0.0 ) && ( quat[n][4] == 0.0))
          ang[2] = 0.0;
             else ang[2] = atan2(quat[n][3],quat[n][4]) ;
      if (debug < 0)
         fprintf(stderr,"mkangc %d %f %f %f\n",
                    n,ang[0],ang[1],ang[2]);
}  /* mkang */
/*****************************************/

shift(x,y,z)
      double x,y,z ;
/*
   this adds 'x,y,z' to all centres and joints

   called by store3, twirl.
*/
{
      int j,k;
      double dx[3];
      
      if (debug <= 0)
         fprintf(stderr,"shifta %f %f %f\n",x,y,z);
      if (debug <= 0)
         fprintf(stderr,"shiftb %f %f %f\n",
            cen[0][0],cen[0][1],cen[0][2]);
      dx[0] = x;
      dx[1] = y;
      dx[2] = z;
      for ( k = 0; k < 3; ++k)
      {
         for (  j = 0 ; j < njts ; ++ j )
            jnt[j][k] += dx[k] ;
         for (  j = 0 ; j < nels ; ++ j )
            cen[j][k] += dx[k] ;
      }
      if (debug <= 0)
         fprintf(stderr,"shiftc %f %f %f\n",
            cen[0][0],cen[0][1],cen[0][2]);
}  /* shift */
/*****************************/

rset(r,angl,axis)
      int axis ;
      double angl,r[3][3] ;
/*
   set up the rotation matrix 'r' for a rotation of
   'angl' radians about 'axis'.

   called by  input, setobs, spinby.
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
/*************************************************/

store3()
/*
    print out axes, centres, orientations and colours
    of  nels ellipsoids starting at 1 (avoiding  0 = world),
    and the joints.

    called by main, perfrm.
    calls   twirl, shift, mkang, ipr. 
*/
{
   int   j,k;
   
   if (debug <= 0)
      fprintf(stderr,"store3a %d %d\n",frame,nels);
   printf("%d %d 5000 5000 5000 0 0 0\n",nels,frame);
   if (nels > 0)
   {
/*
   turn scene for oblique view-
*/
      twirl(place[0],place[1],place[2],obs);
      shift(-place[0],-place[1],-place[2]);
      shift(500.0,500.0,500.0);
/*
   print out the ellipsoid details -
*/ 
      for (j = 0; j < nels; j++)
      {
         mkang(j);
         if (debug <= 0)
            fprintf(stderr,"store3b %d %f\n",j,ang[0]);
         for (k = 0; k < 3; k++) ipr(ten*ax[j][k]);
         for (k = 0; k < 3; k++) ipr(ten*cen[j][k]);
         for (k = 0; k < 3; k++) ipr(ang[k]/rad10);
         for (k = 0; k < 3; k++) printf("%d ",elcol[j][k]);
         printf("%s ",ename[j]);
         if (elcol[j][0] < 0) printf("%s\n",fname[j]);
            else printf("%d\n",j);
      }
/*
   print out the joint details -
*/ 
      if (flag1 < 0)
      {
         printf("%d %d\n",-1,njts);
         for (j = 0; j < njts; j++)
         {
            printf("%d %d ",coel[j][0],coel[j][1]);
            for (k = 0; k < 3; k++) ipr(ten*jnt[j][k]);
            printf(" %s\n",jname[j]);
         }
      }
   }
   if (debug <= 0) fprintf(stderr,
      "store3d %d\n",flag1);
}  /* store3 */
/***********************************************/

ipr(x)
double x;
/*
    print out integral part x

    called by store3.
*/
{
      int k;

      if (x >= doub0) k = (int)(x+inv2);
              else  k = (int)(x-inv2);
      printf("%d ",k);
}  /* ipr */
