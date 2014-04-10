/*     eltonub

   convert a nudes.3 ellipsoid file to a nudes.n nudes script

   modified -
            26 June   1996 added rotation routines
            25 June   1996 copy angles to bendto commands
   written   5 August 1994 Don Herbison-Evans

   subroutines -
      input
      output
      setdcon
      prnt
      rotget
      rotput
      dospinto
      dospinby
      twirl
      matmul
      matrot
      vecmul
      vecmat
      mkang
      shift
      rset
      mkquat
      setels
      setjnt
*/
#include <stdio.h>

#define EMAX 1024
#define BMAX 256
#define TRUE 0
#define FALSE 1

int coel[EMAX][2];
int col[EMAX][3];
int debug = 2;
int ecount;
int elist[EMAX];
int jcount;
int jlist[EMAX];
int nels,njts,flag,frame;
int perm[3][3][3] = {
      { {2,1,1},{1,3,4},{1,5,3} },
      { {3,1,5},{1,2,1},{4,1,3} },
      { {3,4,1},{5,3,1},{1,1,2} }};

double ang[3];
double ax3[EMAX][3];
double cen[EMAX][3];
double dcon[EMAX][2][3];
double doub0;
double doub1;
double doub2;
double inv2;
double inv10;
double jnt[EMAX][3];
double quat[EMAX][5];
double rad;
double rad10;
double tolr;
double twopi;
double vx,vy,vz,ax,ay,az;

double atan(),sin(),cos(),sqrt(),atan2();

char enames[EMAX][BMAX];
char fnames[EMAX][BMAX];
char jnames[EMAX][BMAX];
char tnames[EMAX][BMAX];
char buf[BMAX];
/****************************************************/

main()
/*
   calls input, setdcon, output.
*/
{
   double atan();

   if (debug <= 1) fprintf(stderr,"maina\n");
   doub0 = (double)0;
   doub1 = (double)1;
   doub2 = (double)2;
   inv2 = doub1/doub2;
   inv10 = (double)1/(double)10;
   twopi = (double)4*atan(doub1);
   rad = twopi/(double)360;
   rad10 = rad*inv10;
   tolr = 0.0000001;
   input();
   setdcon();
   output();
   exit(0);
}
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
*/
{
   int ang0,ang1,ang2;
   int axx,axy,axz;
   int cenx,ceny,cenz;
   int col0,col1,col2;
   int ivx,ivy,ivz,iax,iay,iaz;
   int j0,j1,j2;
   int jntx,jnty,jntz;
   int k ;
   double a0,a1,a2;
   char name[BMAX];
   char name1[BMAX];
   char name2[BMAX];

   if (debug <= 1) fprintf(stderr,"inputa\n");
   scanf("%d %d %d %d %d %d %d %d\n",
         &nels,&frame,&ivx,&ivy,&ivz,&iax,&iay,&iaz);
   vx = (double)ivx*inv10;
   vy = (double)ivy*inv10;
   vz = (double)ivz*inv10;
   ax = (double)iax*inv10;
   ay = (double)iay*inv10;
   az = (double)iaz*inv10;
   if (debug <= 1)
      fprintf(stderr,"inputb %d %d\n",nels,frame );
   if ((nels <= 0) || (nels > EMAX))
   {
      fprintf(stderr,"\nERROR in eltonb : frame %d\n",frame);
      fprintf(stderr,"number of ellipsoids %d\n max number %d\n",
         nels,EMAX);
      exit(1);
   }
   else
   {
/* 
     read ellipsoids in current frame -  
*/
      for ( k = 0 ; k < nels ; ++ k )
      {
         if (0 ==
         scanf("%d %d %d %d %d %d %d %d %d %d %d %d %s %s",
            &axx,&axy,&axz,&cenx,&ceny,&cenz,&ang0,&ang1,&ang2,
            &col0,&col1,&col2,name1,name2) )
         {
            fprintf(stderr,"\nERROR in hidel: end of file\n");
            fprintf(stderr,"reading ellipsoid %d in frame %d\n",
                k,frame);
            exit(1);
         }
         if (debug <= 1)
            fprintf(stderr,
            "inputc %d %d %d %d %d %d %d %d %d %d %s\n",
            k,axx,axy,axz, cenx,ceny,cenz, ang0,ang1,ang2,name1);
/* 
     scale everything back to size -  
*/
         ax3[k][0] = inv10*(double)axx ;
         ax3[k][1] = inv10*(double)axy ;
         ax3[k][2] = inv10*(double)axz ;
         cen[k][0] = inv10*(double)cenx ;
         cen[k][1] = inv10*(double)ceny ;
         cen[k][2] = inv10*(double)cenz ;
         a0 = rad10*(double)ang0 ;
         a1 = rad10*(double)ang1 ;
         a2 = rad10*(double)ang2 ;
         mkquat(k,a0,a1,a2);
         col[k][0] = col0;
         col[k][1] = col1;
         col[k][2] = col2;
         sprintf(enames[k],"%s",name1);
         sprintf(tnames[k],"%s",name2);
      }
/*
     read joints -
*/
      scanf("%d %d\n",&flag,&njts);
      if (debug <= 1)
         fprintf(stderr,"inputd %d %d\n",flag,njts);
      if (flag < 0)
      {
         flag = 1;
         for ( k = 0 ; k < njts ; ++ k )
         {
            if (0 == scanf("%d %d %d %d %d %s",
                  &coel[k][0],&coel[k][1],&j0,&j1,&j2,name) )
            {
               fprintf(stderr,"unexpected end of file\n");
               fprintf(stderr,"reading joint %d in frame %d\n",
                   k,frame);
               exit(1);
            }
            else
            {
               sprintf(jnames[k],"%s",name);
               jnt[k][0] = inv10*(double)j0;
               jnt[k][1] = inv10*(double)j1;
               jnt[k][2] = inv10*(double)j2;
            }
         }
      }
   }
} /* input */
/**********************************************/

output()
/*
    print out a NUDES script

   called by main.
*/
{
   int done[EMAX];
   int e;
   int e1,e2;
   int f;
   int i0,i1,i2;
   int j;
   int k;
   int left;
   int m;
   int n;
   int this;
   double a0,a1,a2;

   f = 0;
   for (e = 0; e < nels; ++e)
      done[e] = FALSE;

   for (e = 0; e < nels; ++e)
   {
      if (done[e] == FALSE)
      {
         setels(e,-1);
/*
   figure declaration -
*/
         if (debug <= 0) fprintf(stderr,"outputa %d\n",nels);
         printf("*\n*\nfigure fig%d %d",f,ecount);
         for (n = 0; n < ecount; ++n)
         {
            k = elist[n];
            if (n%6 == 5) printf("\n   ");
            printf(" %s",enames[k]);
         }
         printf("\n*\n");
/*
   ellipsoid declarations -
*/
         for (n = 0; n < ecount; ++n)
         {
            k = elist[n];
            a0 = ax3[k][0];
            a1 = ax3[k][1];
            a2 = ax3[k][2];
            printf("ellipsoid %s",enames[k]);
            prnt(a0);
            prnt(a1);
            prnt(a2);
            printf("\n");
         }
         printf("*\n");
/*
   joint declarations -
*/
         if (debug <= 0) fprintf(stderr,"outputb %d\n",njts);
         for (n = 0; n < jcount; ++n)
         {
            k = jlist[n];
            e1 = coel[k][0];
            e2 = coel[k][1];
            printf("joint %s  %s", jnames[k], enames[e1]);
            prnt(dcon[k][0][0]);
            prnt(dcon[k][0][1]);
            prnt(dcon[k][0][2]);
            printf("  %s",enames[e2]);
            prnt(dcon[k][1][0]);
            prnt(dcon[k][1][1]);
            prnt(dcon[k][1][2]);
            printf("\n");
         }
         if (jcount > 0) printf("*\n");
/*
   the angle commands -
*/
         k = elist[0];
         mkang(k);
         i0 = ang[0]/rad;
         i1 = ang[1]/rad;
         i2 = ang[2]/rad;
         if ((i0 != 0) || (i1 != 0) || (i2 != 0))
         {
            printf("repeat 0 1 spinto fig%d %s world ",f,enames[k]);
            prnt(ang[0]/rad);
            prnt(ang[1]/rad);
            prnt(ang[2]/rad);
            printf("\n");
         }
         i0 = cen[k][0];
         i1 = cen[k][1];
         i2 = cen[k][2];
         if ((i0 != 0) || (i1 != 0) || (i2 != 0))
         {
            printf("repeat 0 1 moveto fig%d %s ",f,enames[k]);
            prnt(cen[k][0]);
            prnt(cen[k][1]);
            prnt(cen[k][2]);
            printf("\n");
         }
         done[k] = TRUE;
again:
         left = 0;
         for (n = 1; n < ecount; ++n)
         {
            k = elist[n];
            if (done[k] == FALSE)
            {
               for (m = 0; (m < jcount) && (done[k] == FALSE); ++m)
               {
                  this = -1;
                  j = jlist[m];
                  if (coel[j][0] == k) this = 1;
                     else
                        if (coel[j][1] == k) this = 0;
                  if (this != -1)
                  {
                     if (done[coel[j][this]] == TRUE)
                     {
                        mkang(k);
                        i0 = ang[0]/rad;
                        i1 = ang[1]/rad;
                        i2 = ang[2]/rad;
                        if ((i0 != 0) || (i1 != 0) || (i2 != 0))
                        {
                           printf("repeat 0 1 bendto %s %s world ",enames[k],jnames[j]);
                           prnt(ang[0]/rad);
                           prnt(ang[1]/rad);
                           prnt(ang[2]/rad);
                           printf("\n");
                        }
                     }
                     done[k] = TRUE;
                  } /* this */
               }  /* m */
            } /* done */
            else
               ++left;
         } /* n */
         if (left > 0) goto again;
         ++f;
      }
   }
   printf("*\n");
/*
   colours -
*/
   for (k = 0; k < nels; ++k)
   {
      printf("repeat 0 1 colour %s %d %d %d\n",
         enames[k],col[k][0],col[k][1],col[k][2]);
   }
   printf("*\n");
/*
   the place and observe commands -
*/
   printf("*\n");
   printf("repeat 0 1 place");
   prnt(vx);
   prnt(vy);
   prnt(vz);
   printf("\n");
   i0 = ax; i1 = ay; i2 = az;
   if ((i0 != 0) || (i1 != 0) || (i2 != 0))
   {
      printf("repeat 0 1 observe");
      prnt(ax);
      prnt(ay);
      prnt(az);
   }
   printf("\n");
   printf("*\n");
/*
   and the stop command -
*/
   printf("stop\n");
} /* output */
/********************************************/

setdcon()
/*
   work out 'dcon' array from 'jnt' and 'coel'

   called by main.
*/
{
   int a,e,k,m;

   for (k = 0; k < njts; ++k)
   {
      for (m = 0; m < 2; ++m)
      {
         e = coel[k][m];
         if (debug <= 0) fprintf(stderr,
           "setdcon %d %d %g %g %g %g %g %g\n",
            k,e,jnt[k][0],jnt[k][1],jnt[k][2],
            cen[e][0],cen[k][1],cen[k][2]);
         for (a = 0; a < 3; ++a)
         {
            dcon[k][m][a] = jnt[k][a] - cen[e][a];
         }
      }
   }
} /* setdcon */
/****************************************/

prnt(x)
double x;
/*
   print x as an integer if reasonable
*/
{
   int ix,jx;

   jx = x*(double)1000000;
   if (jx%1000000 == 0)
   {
      ix = x;
      printf(" %d",ix);
   }
   else
      printf(" %g",x);
} /*   prnt */
/****************************************/

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
         printf("rotgeta    %3d %g %g %g %g %g\n",
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
         printf("rotgetb    %3d %g %g %g\n",
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
            printf("      %g %g %g\n",
               r[k][0],r[k][1],r[k][2]);
      }
      b[0] = r[1][2]-r[2][1] ;
      b[1] = r[2][0]-r[0][2] ;
      b[2] = r[0][1]-r[1][0] ;
      e = b[0]*b[0]+b[1]*b[1]+b[2]*b[2] ;
      trace = r[0][0]+r[1][1]+r[2][2] ;
      if (e > doub0) g = sqrt(e); else g = doub0;
      if (debug <= -1)
           printf("rotputb %g %g %g %g\n",
               trace,g,e,acc);
      if (e > acc)
      {
         f = doub1/g ;
         quat[n][0] = f*b[0] ;
         quat[n][1] = f*b[1] ;
         quat[n][2] = f*b[2] ;

         if (debug <= -1)
            printf("rotputc %3d %g %g %g %g\n",
                            debug,f,b[0],b[1],b[2]);
/*
     use g=2s, and trace=1+2c to find s and c -
*/
         s = inv2*g;
         csq = doub1-s*s;
         if (csq > doub0) c = sqrt(csq); else c = doub0;
         if (trace < doub1) c = -c;
         if (debug <= -1) printf("rotputd %g %g\n",s,c);
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
               "rotpute symmetric matrix, ellipsoid %d\n", n);
            printf("   trace %g, g %g, e %g, acc %g\n",
                   trace,g,e,acc);
            for (k = 0; k < 3; ++k)
               printf("         %g %g %g\n",
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
               printf("rotputf %3d %g %g %g %g\n",
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
            printf("rotputg %3d %g %g %g %g %g %g\n",
                               j,a[j][0],a[j][1],a[j][2],d[j],f,g);
      }
      if (debug <= -1)
          printf("rotputh    %3d %g %g %g %g %g\n",
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

dospinby(x,refell,angl,axis)
      int refell,axis ;
      double angl ;
      double x[3];
/*
   spins all ellipsoids and joints in 'elist' and 'jlist'
   about a point 'x', by an angle 'angl' radians relative to
   an 'axis' of reference ellipsoid 'refell'.

   called by   dobalanc, action, dobend, swing, fun, dodrag.
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
           "dospinbya %3d %g %3d %3d %g %g %g %g %g\n",
           refell,angl,axis,k,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      rset(r,angl,axis) ;
      if (debug <= 0)
      {
         k = elist[0];
         printf(
           "dospinbyb %3d %g %3d %3d %g %g %g %g %g\n",
           refell,angl,axis,k,
           quat[k][0],quat[k][1],quat[k][2],quat[k][3],quat[k][4]);
      }
      rotget(ro,unro,refell) ;
      if (debug <= 0)
      {
         k = elist[0];
         printf(
           "dospinbyc %3d %g %3d %3d %g %g %g %g %g\n",
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
           "dospinbyd %3d %g %3d %3d %g %g %g %g %g\n",
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
            printf("   %g %g %g\n",
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
                  printf("twirld %3d %3d %g %g %g\n",
                  i,k,cen[k][0],cen[k][1],cen[k][2]);
               matrot(r,k) ;
               vecmul(cen,r,k) ;
               if (debug <= -1)
                  printf("twirle %3d %3d %g %g %g\n",
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
               printf("twirlf %3d %3d %g %g %g\n",
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

      if (debug <= 0) printf("matrota    %3d %g %g %g %g %g\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      rotget(ro,unro,n) ;
      if (debug < 0) printf("matrotb    %3d %g %g %g %g %g\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
      matmul(r,ro,ro) ;
      rotput(ro,n) ;
      if (debug < 0) printf("matrotc    %3d %g %g %g %g %g\n",
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

   called by  angles, store3.
*/
{
      double x,y,z,s1,c1,m1 ;
      int j;

      if (debug <= 0)
         printf("mkanga %d %g %g %g %g %g\n",
            n,quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
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
          fprintf(stderr,"eltonub, sub mkang, snag1, %d\n",n);
          exit(1);
      }
      else ang[1] = atan2(s1,c1) ;
      if ((quat[n][3] == doub0 ) && ( quat[n][4] == doub0))
      {
          fprintf(stderr,"eltonub, sub mkang, snag2, %d\n",n);
          exit(1);
      }
      else ang[2] = atan2(quat[n][3],quat[n][4]) ;
      for (j = 0; j < 3; ++j)
         if (ang[j] < doub0) ang[j] += twopi;
      if (debug <= 0)
         printf("mkanb %3d %g %g %g\n",
                    n,ang[0],ang[1],ang[2]);
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
         printf("shifta %3d %3d %g %g %g\n",
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

      if (debug <= 0) printf("rset %3d %g\n",axis,angl);
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
   convert angles a1,a2,a3 into quat entries

   called by input, dospinto.
*/
{
      int j;
      double s1,c1,s2,c2,s3,c3 ;

      if (debug <= 0) printf("mkquata %9d %g %g %g\n",n,a1,a2,a3);
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
         printf("mkquatc %g %g %g %g %g\n",
             quat[n][0],quat[n][1],quat[n][2],quat[n][3],quat[n][4]);
}  /* mkquat */
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
          fprintf(stderr,"eltonub, sub mkang, snag3, %d %d %d %d\n",
          ellpsd,jthis,coel[jthis][0],coel[jthis][1]);
          exit(1);
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
          fprintf(stderr,"eltonub, sub setjnt, snag4, %d %d %d %d\n",
          ellpsd, jthis, coel[jthis][0], coel[jthis][1]);
          exit(1);
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
