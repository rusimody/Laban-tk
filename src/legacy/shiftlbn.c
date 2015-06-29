/*
                shiftlbn.c

              to shift a score up or down
 
    Usage: shiftlbn  h  f
       where
	  h = required height shift
	  f = name of input laban file

    Stores the output score in file shift.lbn.

    20 Nov 1998 Don Herbison-Evans

    subroutines -
      main              - organises everything
      getargs           - get invocation arguments
      lbnwrite          - write out a file of the score in 'lbn' format
      lbninput          - read in a score from a file in 'lbn' format
*/
#include <stdio.h>

#define    BMAX      128
#define    SMAX    10000

int     count;
int     yshift;

char    infile[BMAX];
char    outfile[BMAX];

FILE    *INFILE;
FILE    *OUTFILE;

struct Segment {
   int w;
   int h;
   int x;
   int y;
   int hit;
   int menu;
   int item;
   int step;
   int ok;
   int done;
   char level;
};
struct Segment segs[SMAX];

/*************************************/

main(argc,argv)
int     argc;
char    **argv;
/*
            getargs, 
*/
{
   int s;

   getargs(argc,argv);
   lbninput();
   lbnwrite();
   exit(0);
} /* main */
/*****************************************/

getargs(argc,argv)
int     argc;
char    **argv;
/*
   interpret command line arguments

   called by main.
*/
{

   sscanf(argv[1],"%d",&yshift);
   printf("shiftlbn: yshift = %d\n",yshift);
   strcpy(infile,argv[2]);
   printf("shiftlbn: input file = %s\n",infile);
   strcpy(outfile,"shift.lbn");
   printf("shiftlbn: output file = %s\n",outfile);
} /* getargs */
/*****************************************/

lbnwrite()
/*
   store the score in file "shift.lbn".

   called by main
*/
{
   int s;

   if (count <= 0)
      printf("shiftlbn: no symbols on score to store\n");
   else
   {
      if ( NULL == (OUTFILE = fopen(outfile,"w+")))
         printf("oops, cannot open %s for writing\n",outfile);
      else
      {
         for (s = 0; s < count; ++s)
         {
               fprintf(OUTFILE,"%3d %3d %3d %3d %3d %3d %3d %c\n",
                  segs[s].menu,segs[s].item,segs[s].x,segs[s].y,
                  segs[s].step,segs[s].w,segs[s].h,segs[s].level);
         }
      }
      fclose(OUTFILE);
      if (count == 1)
	 printf("shiftlbn: stored %d item to file %s\n",
            count,outfile);
      else
	 printf("shiftlbn: stored %d items to file %s\n",
            count,outfile);
   }
} /* lbnwrite */
/************************************************/

lbninput()
/*
   read in a score

   called by main.
*/
{
   int d;
   int h;
   int j;
   int m;
   int s;
   int w;
   int x;
   int y;
   char lev;

      s = 0;
      if ( NULL == (INFILE = fopen(infile,"r")))
            printf("oops, cannot open %s for input\n",infile);
      else
      {
         while (fscanf(INFILE,"%d %d %d %d %d %d %d %c\n",
               &m,&j,&x,&y,&d,&w,&h,&lev) != EOF)
         {
               segs[s].x = x;
               segs[s].y = y + yshift;
               segs[s].w = w;
               segs[s].h = h;
               segs[s].item = j;
               segs[s].menu = m;
               segs[s].level = lev;
               segs[s].step = d;
               ++s;
         } /* while */
      } /* fopen ok */
      count = s;
} /* lbninput */
/**************************************/

