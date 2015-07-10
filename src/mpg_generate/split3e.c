/*
   split3e

   usage -
      split3e  nudesname [start] < inputfilename

      to split a inputfilename ellipsoid file into a series
         of files : one per frame, starting with frame 1.
      if start != null,
         then number the output files from start onwards.

   modified
       to correct code                 12/4/01 (Don Herbison-Evans)
       to speed it up                  5/11/92 (Don Herbison-Evans)
       to include ellipsoid names      17/8/91 (Don Herbison-Evans)
       to take standard input          31/3/89 (Don Herbison-Evans)
       to allow texture map filenames  23/6/88 (Myles Thomas) 

   originated
       Don Herbison-Evans  and  Myles Thomas   10/5/88

   subroutines -
      main     - iterate through frames
      getfram3 - get a frame of information from standard input
      putfram3 - write a frame of information to frame file
      openout  - set up a file for current frame
*/

#include <stdio.h>

#define BMAX  256
#define EMAX 1024

int debug = 1;
int flag1,flag2;
int iplx,iply,iplz,iobs1,iobs2,iobs3;
int len;
int nels,nfr;
int nf;
int njts;
int start;

char buf1[BMAX];
char buf2[BMAX];
char cmnd[BMAX];
char eline[EMAX][BMAX];
char jline[EMAX][BMAX];
char f3[BMAX];
char f[BMAX];
char middle[2];

FILE *outfile;

/*******************************************************/

main (argc,argv)
int argc;
char *argv[];
/*
   calls openout, getfram3, putfram3.
*/
{
   if ((argc < 2) || (argc > 4))
   {
      fprintf(stderr,
         "usage: split3e nudesname [start] < nudes.3\n");
      exit(1);
   }
   start = 1;
   if (argc == 3)
      sscanf(argv[2],"%d",&start);
   sprintf(f,"%s",argv[1]);
   len = strlen(f);
   if ((f[len] == '3') && (f[len-1] == '.'))
   {
      f[len] = 0;
      f[len-1] = 0;
   }
   sprintf(f3,"%s.3",f);
   sprintf(middle,".3");
   nels = 1;
   flag1 = -1;
   flag2 = 0;
   nf = start;
   while (nels > 0)
   {
      getfram3();
      if (nels > 0)
      {
         openout(nf);
         putfram3();
      }
      ++nf;
   }
   exit(0);
} /* main */
/**************************************/

getfram3()
/*
   get a frame from a nudes.3 file

   called by main
*/
{
   int e,j;

   if (flag1 < 0)
   {
      if ( NULL == gets(buf1))
      {
         fprintf(stderr,"\nERROR in split3e: %s empty\n",f3);
         exit(1);
      }
      sscanf(buf1,"%d %d %d %d %d %d %d %d\n",
          &nels,&nfr,&iplx,&iply,&iplz,&iobs1,&iobs2,&iobs3);
   }
   else
      sscanf(buf2,"%d %d %d %d %d %d %d %d\n",
          &nels,&nfr,&iplx,&iply,&iplz,&iobs1,&iobs2,&iobs3);
   if (nf == 0)
   {
      debug = nfr;
      if ( nels <= 0)
      {
         fprintf(stderr,
            "\nERROR in split3e: no ellipsoids in file %s\n",f3);
         exit(1);
      }
   }
   if (debug <= 0) fprintf(stderr,
     "getfram3a %d %d %d %d %d %d %d %d\n",
          nels,nfr,iplx,iply,iplz,iobs1,iobs2,iobs3);
   flag1 = 1;
   if (nels == 0) goto end;
   for (e = 0; e < nels; ++e)
   {
      if ( NULL == gets(eline[e]))
      {
         fprintf(stderr,
            "\nERROR in split3e: unexpected end of input file \n");
         fprintf(stderr,"reading ellipsoid %d, frame %d\n",e,nfr);
         nels = e;
         goto end;
      }
      else
      {
         if (debug < 0) fprintf(stderr,"getfram3b %s\n",eline[e]);
      }
   }
   if ( NULL == gets(buf2))
   {
      fprintf(stderr,
         "\nERROR in split3e: unexpected end of input file\n");
      fprintf(stderr,"reading number of joints in frame %d\n",nfr);
      goto end;
   }
   sscanf(buf2,"%d %d\n",&flag1,&flag2);
   if (flag1 < 0)
   {
      njts = flag2;
      for (j = 0; j < njts; ++j)
      {
         if ( NULL == gets(jline[j]))
         {
            fprintf(stderr,
               "\nERROR in split3e: unexpected end of input file\n");
            fprintf(stderr,"reading joint %d in frame %d\n",j,nfr);
            goto end;
         }
         if (debug < 0) fprintf(stderr,"dofram3b %s\n",jline[j]);
      }
   }
end:;
} /* getfram3 */
/*************************************************/

putfram3()
/*
   write a frame file

   called by main
*/
{
   int e,j;

   fprintf(outfile,"%d %d %d %d %d %d %d %d\n",
              nels,nfr,iplx,iply,iplz,iobs1,iobs2,iobs3);
   for (e = 0; e < nels; ++e)
   {
         fprintf(outfile,"%s\n",eline[e]);
   }
   if (flag1 < 0)
   {
      fprintf(outfile,"%d %d\n",flag1,njts);
      for ( j = 0; j < njts; ++j )
      {
            fprintf(outfile,"%s\n",jline[j]);
      }
   }
end:;
   fprintf(outfile,"0 %d 0 0 0 0 0 0\n",nfr+1);
   fclose(outfile);
} /* putfram3 */
/*************************************************/

openout(n)
int n;
/*
    create new file
 
    called by main
*/
{
   char foname[BMAX];

   if ((n >= 0 ) && (n <= 9 ))
              sprintf(foname,"%s.000%d%s",f,n,middle);
   if ((n >= 10) && (n <= 99))
              sprintf(foname,"%s.00%d%s",f,n,middle);
   if ((n >= 100) && (n <= 999))
              sprintf(foname,"%s.0%d%s",f,n,middle);
   if (n >= 1000)
              sprintf(foname,"%s.%d%s",f,n,middle);
   if( NULL == (outfile=fopen(foname,"w+")) )
   {
       fprintf(stderr,
          "\nERROR in split3e: can't open/create %s for writing\n",
          foname);
       exit(1);
   }
} /* openout */
