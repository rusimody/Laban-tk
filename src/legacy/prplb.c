/*
             prplb.c

   program to draw a readable plot file on a text output device

    ppm input             Don Herbison-Evans   3 Mar 2000
    cleaned up            Don Herbison-Evans  14 Nov 1992
    written:              Don Herbison-Evans   5 Oct 1987
*/
#define BMAX  256
#define GMAX   10
#define PMAX 1000
#define XMAX  100
#define YMAX 1000

int debug = 1;
int k;
int r,g,b;
char p[GMAX] = {' ','.',',',':',';','^','>','L','F','W'};
char buf[256];

#include <stdio.h>

main()
{
   int ctop, xtop, ytop;
   int j;
   int x,y;
   int head;

   head=2;

   for (j = 0; j < 3; ++j)
   {
      if (gets(buf) == NULL)
      {
         fprintf(stderr,"prplbA : end of file\n");
         exit(1);
      }
      else
      {
         if (debug < 1) fprintf(stderr,"prplbB %d %s\n",head,buf);
         if (buf[0] == '#')
         {
            if (debug < 1) fprintf(stderr,"%s\n",buf); 
         }
         else if (head == 2)
         {
            if ((buf[0] != 'P') && (buf[1] !='3'))
            {
               fprintf(stderr,"prlpbC not ppm input:\n%s\n",buf);
               exit(1);
            }
            head = 1;
         }
         else if (head == 1)
         {
            sscanf(buf,"%d %d",&xtop,&ytop);
            gets(buf);
            sscanf(buf,"%d",&ctop);
            head = 0;
            if (debug < 1)
               fprintf(stderr,"prplbD %d %d %d\n",xtop,ytop,ctop);
         }
      }
   }

   newbuf();
   for (y = 0; y < ytop; ++y)
   {
      for (x = 0; x < xtop; ++x)
      {
         bufscan();
         j = GMAX*(r+g+b)/(3*ctop);
         if (j < 0) j = 0;
         if (j >= GMAX) j = GMAX-1;
         printf("%c",p[GMAX-j-1]);
         if (debug < 1)
            fprintf(stderr,"prplbF %d %d %d %d %d %d %d\n",head,x,y,r,g,b,j);
      }
      printf("\n");
   }
} /* main */
/********************************************/

bufscan()
/*
    get next three values from 'buf' array,
*/
{
   int j;
 
   r = 0;
   g = 0;
   b = 0;



   for (j = k; (j < BMAX) && (buf[j] >= '0') && (buf[j] <= '9'); ++j)
   {
      r = 10*r + buf[j]-'0';
   }
   k = j;
   for (j = k; (j < BMAX) && ((buf[j] < '0')||(buf[j] > '9')); ++j);
   k = j;
   if (j > (BMAX-1) ) newbuf();


   for (j = k; (j < BMAX) && (buf[j] >= '0') && (buf[j] <= '9'); ++j)
   {
      g = 10*g + buf[j]-'0';
   }
   k = j;
   for (j = k; (j < BMAX) && ((buf[j] < '0')||(buf[j] > '9')); ++j);
   k = j;
   if (j > (BMAX-1) ) newbuf();


   for (j = k; (j < BMAX) && (buf[j] >= '0') && (buf[j] <= '9'); ++j)
   {
      b = 10*b + buf[j]-'0';
   }
   k = j;
   for (j = k; (j < BMAX) && ((buf[j] < '0')||(buf[j] > '9')); ++j);
   k = j;
   if (j > (BMAX-1) ) newbuf();


   if (debug < 1)
      fprintf(stderr,"prplb: bufscanA %d %d %d %d %d\n",j,k,r,g,b);
}   /* bufscan */
/*******************************************/

newbuf()
/*
    read new 'buf' array and scan up to first
    non-blank character;
*/
{
   int j;

   k = 0;
   if (gets(buf) == NULL)
   {
      fprintf(stderr,"prplb: newbufA: end of file\n");
      exit(0);
   }
   if (debug < 1)
      fprintf(stderr,"prplb: newbufB %s\n",buf);
   for (j = k; (j < BMAX) && ((buf[j] < '0')||(buf[j] > '9')); ++j);
   k = j;
   if (debug < 1)
      fprintf(stderr,"prplb: newbufC %d %d\n",j,k);
} /* newbuf */
