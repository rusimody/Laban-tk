/*            twista.c

   to rotate the scene in a NUDES file a bit left and right
   by inserting a "spinby" command at the end of the main program.

   Don Herbison-Evans   7 April 1996
*/
#include <stdio.h>
#include <values.h>
#include "X11/Xlib.h"
#include "X11/Xutil.h"

#define BMAX    256     /* size of string buffers */
#define FALSE 0
#define TRUE 1

int debug;

char  buf[BMAX];	/* input string buffer */
char  infile[BMAX];     /* input file name */
char  outfilel[BMAX];   /* left output file name */
char  outfiler[BMAX];   /* right output file name */

FILE  *INFILE;
FILE  *OUTFILEL;
FILE  *OUTFILER;

/************************************************/

main(argc,argv)
int argc;
char *argv[];
{
   int j,k,m,p,q;
   int done,gotsub;
   char sub[BMAX];
   char stop[BMAX];
   char space;

   debug = 1;
   sprintf(sub,"subroutine");
   sprintf(stop,"stop");
   space = ' ';
   sprintf(infile,"%s.n",argv[1]);
   if (NULL == (INFILE = fopen(infile,"r")))
   {
      printf("twista: cannot open input file %s\n",infile);
      exit(1);
   }
   if (debug <= 0) printf("maina %s\n",infile);
   sprintf(outfilel,"%s.left.n",argv[1]);
   if (NULL == (OUTFILEL = fopen(outfilel,"w+")))
   {
      printf("twista: cannot open output file %s\n",outfilel);
      exit(1);
   }
   sprintf(outfiler,"%s.right.n",argv[1]);
   if (NULL == (OUTFILER = fopen(outfiler,"w+")))
   {
      printf("twista: cannot open output file %s\n",outfiler);
      exit(1);
   }
   fprintf(OUTFILEL,"*   %s, based on\n",outfilel);
   fprintf(OUTFILER,"*   %s, based on\n",outfiler);
   done = FALSE;
   for (j = 0; (NULL != fgets(buf,BMAX,INFILE)); ++j)
   {
      if (done == FALSE)
      {
         gotsub = TRUE;
         for (p = 0; buf[p] == space; ++p);
	 m = 0;
         for (k = p; ((k < BMAX)
	    && (buf[k] != NULL) && (buf[k] != space) && (buf[k] != '\n'));
	       ++k)
         {
	    if ((buf[k] != sub[m]) && (buf[k] != stop[m]))
	       gotsub = FALSE;
	    if (debug <= 0)
	       printf("mainb %d %d %d %d %c %c %c %d %d\n",
	          j,p,k,m,buf[k],sub[m],stop[m],gotsub,TRUE);
	    ++m;
         } /* k */
	 if (gotsub == TRUE)
	 {
	    fprintf(OUTFILEL,"linear 0 1 moveby every world -500 0 -500\n");
	    fprintf(OUTFILEL,"linear 0 1 spinby every world world -2 y\n");
	    fprintf(OUTFILEL,"linear 0 1 moveby every world +500 0 +500\n");
	    fprintf(OUTFILER,"linear 0 1 moveby every world -500 0 -500\n");
	    fprintf(OUTFILER,"linear 0 1 spinby every world world +2 y\n");
	    fprintf(OUTFILER,"linear 0 1 moveby every world +500 0 +500\n");
	    done = TRUE;
	 } /* gotsub = TRUE */
      } /* done false */
      fprintf(OUTFILEL,"%s",buf);
      fprintf(OUTFILER,"%s",buf);
   } /* j */
   fclose(INFILE);
   fclose(OUTFILEL);
   fclose(OUTFILER);
   exit(0);
} /* main */
/************************************************/
