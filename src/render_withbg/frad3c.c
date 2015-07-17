/*
   frad3c

   usage :-  frad3c [-g u] < filein > fileout

   Add sets of ellipsoids composing the frame numbers
   to a nudesname.3 file, in grey colour 'u' (default: 127);

   modified:
      20/ 9/03 make numbers bigger (Don Herbison-Evans)
       3/ 9/93 allow joint information (Don Herbison-Evans)
      21/12/91 allow optional number grey colour (Don Herbison-Evans)
      17/08/91 keep names on ends of lines (Don Herbison-Evans)

   originated:
      21/5/88 Don Herbison-Evans  and  Myles Thomas

   subroutines:
      main     - runs through frames
      getpar   - reads invocation parameters
      getfram3 - reads a frame from input
      putells  - puts out ellipsoids of frame
      putjnts  - puts out joint information
      digs     - puts digits of frame number into array "val"
*/

#include <stdio.h>

#define EMAX 1024
#define BMAX  128
#define TRUE    1
#define FALSE   0

char cmnd[BMAX];
char buf[BMAX];
char enames[EMAX][BMAX];
char fnames[EMAX][BMAX];
char jnames[EMAX][BMAX];

int a1,a2,a3;
int debug ;
int empty;
int first;
int flag;
int grey ;
int jnt[EMAX][5];
int nels;
int nfr;
int njts;
int val[EMAX][12];
int start[11] = {0, 6, 7, 11, 17, 20, 25, 29, 31, 39, 43};
int vx,vy,vz;

int dig[43][9] = {
/* 0 */ {20,  60,  20, 1000, 306, 1000,    0,    0,    0},
        {20,  40,  20, 1028, 227, 1000,    0, -890,  450},
        {20,  40,  20, 1085, 227, 1000,    0, -890, 1350},
        {20,  60,  20, 1113, 306, 1000,    0,  890, 1800},
        {20,  40,  20, 1085, 394, 1000,    0,  890, 1350},
        {20,  40,  20, 1028, 394, 1000,    0,  890,  450},
/* 1 */ {20, 120,  20, 1000, 306, 1000,    0,    0,    0},
/* 2 */ {20,  50,  20,  960, 404, 1000,    0, -890, 1650},
        {20,  50,  20, 1022, 440, 1000,    0, -890,  750},
        {20, 140,  20, 1000, 306, 1000,    0,  890,  300},
        {20,  80,  20, 1010, 184, 1000,    0, -890,  890},
/* 3 */ {20,  50,  20,  929, 396, 1000,    0, -890, 1350},
        {20,  50,  20, 1000, 396, 1000,  225, -890,  450},
        {20,  50,  20, 1000, 326, 1000, -225,  890,  450},
        {20,  60,  20, 1007, 248, 1000,    0, -890,  450},
        {20,  60,  20, 1007, 163, 1000,    0,  890,  450},
        {20,  60,  20,  922, 163, 1000,    0,  890, 1350},
/* 4 */ {20, 130,  20,  990, 262, 1000,    0,  890,  890},
        {20, 160,  20,  950, 339, 1000,    0,  890,  600},
        {20, 120,  20, 1000, 306, 1000,    0,    0,    0},
/* 5 */ {20,  70,  20, 1000, 446, 1000, -450,  890,  890},
        {20,  70,  20,  930, 376, 1000,    0,    0,    0},
        {20,  70,  20, 1000, 306, 1000,    0, -890,  890},
        {20,  70,  20, 1070, 236, 1000,    0,    0,    0},
        {20,  70,  20, 1000, 166, 1000,    0,  890,  890},
/* 6 */ {20, 120,  20,  913, 362, 1000,    0,  890,  350},
        {20,  70,  20,  894, 214, 1000,    0, -890,  450},
        {20,  70,  20,  993, 214, 1000,    0, -890, 1350},
        {20,  60,  20, 1000, 306, 1000,    0,  890, 1350},
/* 7 */ {20, 100,  20,  980, 444, 1000,    0, -890,  890},
        {20, 160,  20, 1000, 306, 1000,    0,  890,  300},
/* 8 */ {20,  60,  20, 1092, 228, 1000, -225,  890,  450},
        {20,  60,  20, 1007, 228, 1000, -675,  890, 1350},
        {20,  50,  20, 1000, 306, 1000,  675, -890, 1350},
        {20,  50,  20, 1000, 376, 1000,    0,  890, 1350},
        {20,  50,  20, 1000, 447, 1000,    0, -890, 1350},
        {20,  50,  20, 1071, 447, 1000,  225, -890,  450},
        {20,  60,  20, 1064, 369, 1000,    0,  890,  450},
        {20,  60,  20, 1064, 284, 1000,    0, -890,  450},
/* 9 */ {20, 120,  20, 1087, 250, 1000,    0, -890, 1450},
        {20,  70,  20, 1106, 398, 1000,    0,  890, 1350},
        {20,  70,  20, 1007, 398, 1000,    0,  890,  450},
        {20,  60,  20, 1000, 306, 1000,    0, -890,  450}};

/*************************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls  getpar, getfram3, putells, digits, putjnts.
*/
{
   first = TRUE;
   empty = FALSE;
   grey = 1;
   debug = 1;
   getpar(argc,argv);
   nels = 1;
   flag = -1;
   while (empty == FALSE)
   {
      getfram3();
      if (debug <= 0)
         fprintf(stderr,"maina %d %d %d\n",nfr,nels,njts);
      if (nels > 0)
      {
         digits();
         putells();
         if (njts > 0)
            putjnts();
      }
      if (debug <= 0)
         fprintf(stderr,"mainb %d %d %d\n",nfr,nels,njts);
   }
   printf("%d %d %d %d %d %d %d %d\n",0,nfr,vx,vy,vz,a1,a2,a3);
   exit(0);
} /* main */
/**************************************/

getpar(argc,argv)
int argc;
char *argv[];
/*
   check if a parameter is present to set grey level

   called by main.
*/
{
   char buf1[100];
   char buf2[100];

   if (debug <= 0) fprintf(stderr,"getpara %d\n",argc);
   if (argc > 1)
   {
      sprintf(buf1,"%s",argv[1]);
      sprintf(buf2,"%s",argv[2]);
      if ( (buf1[0] != '-') || (buf1[1] != 'g') )
      {
         fprintf(stderr,"frad3c: unrecognized parameter : %s\n",buf1);
         exit(1);
      }
      if (debug < 0) fprintf(stderr,"getparb %s\n",buf2);
      sscanf(buf2,"%d",&grey);
      if ( (grey < 0) || (grey > 255) )
      {
         fprintf(stderr,"frad3c: funny grey value: %d\n",grey);
         exit(1);
      }
   }
   if (debug < 0) fprintf(stderr,"getparc %d\n",grey);
}   /* getpar */
/**************************************/

getfram3()
/*
   get a frame from a nudes.3 file,
      i.e. nels lines of 12 values per line
           and then the joints if any.

   called by main.
*/
{
   int e,j,k;

   if (flag < 0)
   {
      if (NULL == gets(buf))
      {
         fprintf(stderr,
            "\nERROR: frad3c: input empty after frame %d\n",nfr);
         exit(1);
      }
   }
   sscanf(buf,"%d %d %d %d %d %d %d %d\n",
              &nels,&nfr,&vx,&vy,&vz,&a1,&a2,&a3);
   if (first == TRUE) debug = nfr;
   first = FALSE;
   if ((nels < 0) || (nels > EMAX))
   {
      fprintf(stderr,"\nERROR: frad3c: frame %d\n",nfr);
      fprintf(stderr," number of ellipsoids is %d, max is %d\n",
          nels,EMAX);
      nels = 0;
   }
   if (nels <= 0) empty = TRUE;
   if (debug <= 0) fprintf(stderr,"getfram3a %d %d\n",nels,nfr);
   for (e = 0; e < nels; ++e)
   {
       if ( NULL == gets(buf))
      {
         fprintf(stderr,
            "\nERROR: frad3c: unexpected EOF at ellipsoid %d\n",e);
         fprintf(stderr," frame %d\n",nfr);
         nels = e;
      }
      else
      {
         sscanf(buf,"%d %d %d %d %d %d %d %d %d %d %d %d %s %s\n",
            &val[e][0],&val[e][1],&val[e][2],
            &val[e][3],&val[e][4],&val[e][5],
            &val[e][6],&val[e][7],&val[e][8],
            &val[e][9],&val[e][10],&val[e][11],
            enames[e],fnames[e]);
         for (k = 0; k < 12; ++k)
         {
            if (debug < 0) fprintf(stderr,
               "getfram3b %d %d %d\n",e,k,val[e][k]);
         }
      }
   }
   if (NULL == gets(buf))
      njts = 0;
   else
   {
      sscanf(buf,"%d %d\n",&flag,&njts);
      if (debug <= 0)
         fprintf(stderr,"getfram3c %d %d\n",flag,njts);
      if (flag >= 0)
         njts = 0;
      else
      {
         for (j = 0; j < njts; ++j)
         {
            if ( NULL == gets(buf))
            {
               fprintf(stderr,
                  "\nERROR in frad3c: unexpected EOF at joint %d\n",
                  j);
               fprintf(stderr," frame %d\n",nfr);
               njts = j;
            }
            else
            {
               sscanf(buf,"%d %d %d %d %d %s\n",
                  &jnt[j][0],&jnt[j][1],&jnt[j][2],&jnt[j][3],
                  &jnt[j][4], jnames[j]);
               if (debug < 0) fprintf(stderr,"getfram3d %d %s\n",
                  j,jnames[j]);
            }
         }
      }
   }
} /* getfram3 */
/*************************************************/

putells()
/*
   put out ellipsoids of a  nudes.3 file

   called by main
*/
{
   int e,k;

   printf("%d %d %d %d %d %d %d %d\n",nels,nfr,vx,vy,vz,a1,a2,a3);
   for (e = 0; e < nels; ++e)
   {
      for (k = 0; k < 12; ++k)
         printf(" %d",val[e][k]);
      printf(" %s",enames[e]);
      printf(" %s\n",fnames[e]);
   }
} /* putells */
/*************************************************/

putjnts()
/*
   put out joints of a nudes.3 file

   called by main
*/
{
   int j,k;

   printf("%d %d\n",flag,njts);
   for (j = 0; j < njts; ++j)
   {
      for (k = 0; k < 5; ++k)
         printf(" %d",jnt[j][k]);
      printf(" %s\n",jnames[j]);
   }
} /* putjnts */
/*************************************************/

digits()
/*
   put the ellipsoids composing the frame number in array val too.

   called by main
*/

{
   int  k,m,n,p,t;

   if (nfr >= 0) t = nfr;
      else t = -nfr;
   for (k = 0;  t > 0; k++)
   {
      m = t % 10;  t = t / 10;
      if (debug < 0)
          fprintf(stderr,"digitsa %d %d %d\n",t,k,m);
      for (n = start[m];  n < start[m+1]; ++n)
      {
         for (p = 0;  p < 12; ++p)
         {
            if (p == 0) val[nels][p] = 2*dig[n][p];
            else if (p == 1) val[nels][p] = 2*dig[n][p];
            else if (p == 2) val[nels][p] = 2*dig[n][p];
            else if (p == 3) val[nels][p] = 2*dig[n][p]-600*k;
            else if (p == 4) val[nels][p] = 2*dig[n][p];
            else if (p == 5) val[nels][p] = 2*dig[n][p];
            else if (p < 9) val[nels][p] = dig[n][p];
            else val[nels][p] = grey;
            if (debug < 0)
               fprintf(stderr,"%d ",val[nels][p]);
         }
         sprintf(enames[nels],"dig%d.%d",k,m);
         sprintf(fnames[nels],"0");
         if (debug < 0)
            fprintf(stderr,"%s\n",enames[nels]);
         nels ++;
         if (nels >= EMAX)
           fprintf(stderr,
              "ERROR frad3c: more than %d ellipsoids in frame %d\n",
                  EMAX,nfr);
      }
   }
} /* digits */
/*********************************************/
