/*
                     anaglyphe.c

   superimpose 2 sets of images, left in red and right in green,
                   to make anaglyphs.

  For viewing, can use Lee filters 106 (primary red)
                               and 139 (primary green)

   Usage:
    anaglyphe infileleft infileright outfile [-b n] [-d n] [-l n] [-k] [-z]

   Flags-
	 -b : begin at frame "n" (default: 1).
	 -d : set debug parameter to "n" (default: 1).
	 -l : do "n" images (default: all).
         -k : keep intermediate directory and files.
         -z : do not compress final files

        20 Apr 1998   put red on the left!
        14 Apr 1997   begin at optional frame number
        17 Jun 1996   use ppm format input and output image files
        21 Apr 1996   written (Don Herbison-Evans)

   File format (ppm) -
      4 lines of format data -
	 P3
         width
         height
         maxcols
      then three integers per pixel of width*height values.

   subroutines -
      main           - organises things
      getpar         - get invoked parameters
      getfile        - get the image files
      tryfile        - try various file types
      isfile         - find full name of image file
      checkhead      - check header of image file
      doframe        - load line buffer and print it
      exec           - execute a system command
      getout         - exit gracefully
      combine        - print combined image line out
      openout        - open output file
*/
#include <stdio.h>
#include <values.h>

#define BMAX    256        /* size of string buffers */
#define CMAX    256        /* number of values of each colour */
#define PMAX    1000       /* max number of frames */
#define XMAX    1024       /* max width of image */
#define TRUE    1
#define FALSE   0

int   cmax;
int   cmaxl;
int   cmaxr;

char  blank;            /* blanks to separate images */
char  bgr,bgl;          /* backgrounds of images */
char  buf[BMAX];	/* input string buffer */
char  cmnd[BMAX];	/* shell command string buffer */
char  err[BMAX];	/* error message string buffer */
char  filelname[BMAX];  /* original left image file name */
char  filername[BMAX];  /* original right image file name */
char  finame[BMAX];     /* current input file name */
char  fliname[BMAX];	/* root+image type left file name stem */
char  friname[BMAX];	/* root+image type right file name stem */
char  flname[BMAX];	/* root name of left image file names */
char  frname[BMAX];	/* root name of right image file names */
char  foname[BMAX];     /* root name of output files */
char  home[BMAX] = "/rose/don";
char  infile[BMAX];     /* current input image file name */
char  outfile[BMAX];    /* output image file name */

int   black;
int   count;            /* output file line counter */
int   debug;            /* <= 0 for debugging info to be printed */
int   f;		/* current frame number */
int   frno;             /* frame number read from image file */
int   flheight;         /* height of the left image */
int   frheight;         /* height of the right image */
int   first = TRUE;     /* true when doing first frame */
int   fwidth,fheight;   /* size of current image */
int   flwidth;          /* width of the left image */
int   frwidth;          /* width of the right image */
int   height;           /* height of output image */
int   keep;             /* true if intermediate files to be kept */
int   length;		/* number of frames to be processed */
int   line[XMAX];       /* output line buffer */
int   nfr;		/* number of current frame */
int   ok;               /* true if image file obtained  */
int   pack;             /* true if final files to be compressed */
int   start;		/* number of first frame file */
int   step;		/* increment between frame numbers */
int   stop;             /* number of last frame file */
int   white;
int   width;            /* width of output image */

FILE  *INFILE;
FILE  *INFILEL;
FILE  *INFILER;
FILE  *OUTFILE;

/************************************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls  getpar, getfiles, getout.
*/
{
   black = 0; white = 255;
   keep = FALSE;
   pack = TRUE;
   getpar(argc,argv);
   getfiles();
   getout(0);
} /* main */

/************************************************/

getpar(argc,argv)
int argc;
char *argv[];
/*
   get the parameters

   called by main.
   calls     getout.
*/
{
   int p;
   int x;
   int value;

   debug = 1;
   start = 0;
   step = 1;
   length = PMAX;
   stop = length;
   blank = 255;
   if (argc < 4)
   {
       sprintf(cmnd,"more %s/src.nudes/anaglyphe.c\n",home);
       exec(cmnd);
       exit(0);
   }
   else
   {
       for ( p = 1; p < argc; ++ p)
       {
          sprintf(buf,"%s",argv[p]);
	  if (debug <= 0)
	     printf("getpara %d %s %c\n",
		p,argv[p],buf[0]);
          if (buf[0] != '-')
	  {
	     if (p == 1)
                sprintf(flname,"%s",argv[p]);
	     else
	     if (p == 2)
                sprintf(frname,"%s",argv[p]);
	     else
	     if (p == 3)
                sprintf(foname,"%s",argv[p]);
             else
	     {
		sprintf(err,"anaglyphe: funny %dth parameter:%s",p,argv[p]);
		getout(1);
	     }
	  } /* buf0 != - */
	  else
          if (buf[1] == 'b')
	  {
	     ++p;
	     sscanf(argv[p],"%d",&start);
	  }
          else
          if (buf[1] == 'd')
	  {
	     ++p;
	     sscanf(argv[p],"%d",&debug);
	  }
          else
          if (buf[1] == 'k')
	     keep = TRUE;
	  else
          if (buf[1] == 'l')
	  {
	     ++p;
	     sscanf(argv[p],"%d",&length);
	  }
          else
          if (buf[1] == 'z')
	     pack = FALSE;
	  else
          {
             sprintf(err,"unrecognized flag: %s",argv[p]);
             getout(1);
          }
       }
   }
   if (length == PMAX)
   {
      length = (length-1)*step+1;
      if (step != 1) printf(
        "max length changed to %d\n",length);
   }
   stop = start + step*length ;
   if (debug <= 0)
   {
      printf("left file %s\n",flname);
      printf("right file %s\n",frname);
   }
} /* getpar */

/************************************************/

getfiles()
/*
   run through files

   called by main.
   calls     isfile, tryfile, doframe, getout.
*/
{
   int nextl,nextr;
   int tryfile();
   int isfile();

   if (debug <= 0)
      printf("getfilesa %s %s %d\n",flname,frname,start);
   f = 0;
   first = TRUE;
   sprintf(fliname,"%s",flname);
   sprintf(friname,"%s",frname);
   if (start < 0) start = 0;
   if (start == 0)
   {
      if ((tryfile(start,flname,fliname) == FALSE)
       || (tryfile(start,frname,friname) == FALSE))
	  start = 1;
   }
   stop = start+step*length;
   if (debug <= 0)
      printf("getfilesb %d %d\n",start,stop);
   for ( nfr = start; nfr < stop; nfr += step)
   {
      if (debug <= 0) printf("getfilesc %d\n",nfr);
      nextl = tryfile(nfr,flname,fliname);
      nextr = tryfile(nfr,frname,friname);
      if (debug <= 0) printf("getfilesd %d\n",nfr);
      nextl = isfile(fliname,nfr);
      if (nextl == FALSE) break;
      checkhead();
      if (debug < 0)
         printf("getfilese %d %d %d\n",fwidth,fheight,cmax);
      INFILEL = INFILE;
      bgl = 255;
      flwidth = fwidth; flheight = fheight; cmaxl = cmax;
      nextr = isfile(friname,nfr);
      if (nextr == FALSE) break;
      checkhead();
      if (debug < 0)
         printf("getfilesf %d %d %d\n",fwidth,fheight,cmax);
      INFILER = INFILE;
      bgr = 255;
      frwidth = fwidth; frheight = fheight; cmaxr = cmax;
      if (debug <= 0)
         printf("getfilesg %d %d\n",flwidth,frwidth);
      if ((nextl == TRUE) && (nextr == TRUE))
      {
	  openout(nfr);
	  if (flwidth > frwidth) width = flwidth;
             else width = frwidth;
	  if (flheight > frheight) height = flheight;
	     else height = frheight;
          if (cmaxl > cmaxr) cmax = cmaxl;
             else cmax = cmaxr;
          fprintf(OUTFILE,"P3\n");
	  fprintf(OUTFILE," %d\n",width);
	  fprintf(OUTFILE," %d\n",height);
	  fprintf(OUTFILE," %d\n",cmax);
          doframe();
	  if (count > 0) fprintf(OUTFILE,"\n");
          fclose(OUTFILE);
	  sprintf(cmnd,"chmod 775 %s\n",outfile);
	  exec(cmnd);
	  sprintf(cmnd,"rm %s.Z 2>/usr/tmp/mess\n",outfile);
	  exec(cmnd);
	  sprintf(cmnd,"compress %s\n",outfile);
	  --debug; if (pack == TRUE) exec(cmnd); ++debug;
      } /* next true */
      else
      {
         if (nfr == start)
         {
            sprintf(err,
                  "can't open file like %s or %s for reading",
                  fliname,friname);
            sprintf(cmnd,"rm -rf /tmp/%s.*\n",fliname);
	    if (keep == FALSE) exec(cmnd);
            sprintf(cmnd,"rm -rf /tmp/%s.*\n",friname);
	    if (keep == FALSE) exec(cmnd);
            getout(1);
         } /* nfr = start */ 
         else
	 {
            sprintf(cmnd,"rm -rf /tmp/%s.*\n",fliname);
	    if (keep == FALSE) exec(cmnd);
            sprintf(cmnd,"rm -rf /tmp/%s.*\n",friname);
	    if (keep == FALSE) exec(cmnd);
	    goto dis;
	 } /* nfr = start */
      } /* next false */
      sprintf(cmnd,"rm -rf /tmp/%s*\n",fliname);
      if (keep == FALSE) exec(cmnd);
      sprintf(cmnd,"rm -rf /tmp/%s*\n",friname);
      if (keep == FALSE) exec(cmnd);
      if (f > length)
      {
          printf("more than %d frames\n",length);
          ok = FALSE;
          goto dis;
      } /* f > length */
      ++ f;
   } /* nfr */
   
dis:
   if (f != 1) printf("%d frames written\n",f);
      else printf("%d frame written\n",f);
   sprintf(cmnd,"rm -rf /tmp/%s*\n",fliname);
   if (keep == FALSE) exec(cmnd);
   sprintf(cmnd,"rm -rf /tmp/%s*\n",friname);
   if (keep == FALSE) exec(cmnd);
   if (debug <= 0) printf("getfilesh %d %d\n",start,stop);
}  /* getfiles */
/***********************************************/

int tryfile(nfr,fname,finame)
int nfr;
char fname[CMAX];
char finame[CMAX];
/*
   try various types of files for same root name
   'fname' and frame number 'nfr', leaving name
   in 'finame' if ok.

   called by getfiles.
   calls     isfile.
*/
{
   int k;

   if (debug < 0)
         printf("tryfilea %d %s\n",nfr,fname);
   sprintf(finame,"%s",fname);
   if (isfile(finame,nfr) == TRUE) goto gotit;
   sprintf(finame,"%s.ppm",fname);
   if (isfile(finame,nfr) == TRUE) goto gotit;
   return(FALSE);

gotit:
   fclose(INFILE);
   if (debug <= 0)
         printf("tryfileb %s %d %d %d %d\n",
           fname,nfr,flwidth,flheight,frwidth,frheight);
   return(TRUE);
} /* tryfile */
/*************************************************/

int isfile(ftmp1,nfr)
char ftmp1[BMAX];
int nfr;
/*
   check whether there is a file for nfr'th frame.

   called by getfiles, tryfile.
   calls     getout.
*/
{
   int  comprd;	/* true if current frame is compressed */
   int  ok;
   char filename[BMAX];
   char ftmp2[BMAX];
   char ftmp3[BMAX];
   char ftmpz[BMAX];

   ok = FALSE;
   sprintf(ftmp2,"ftmp2");
   sprintf(ftmp3,"ftmp3");
   sprintf(ftmpz,"ftmpz");
   sprintf(filename,"filename");
   comprd = FALSE;
   if (first == TRUE)
   {
      sprintf(filename,"%s",ftmp1);
      if (debug < 0) printf("isfilea trying %s\n",ftmp1);
      if( NULL != (INFILE=fopen(ftmp1,"r")) )
      {
         sprintf(infile,"%s",ftmp1);
         length = 1;
         ok = TRUE;
      }
      else
      {
         sprintf(ftmpz,"%s.Z",ftmp1);
         sprintf(filename,"%s",ftmpz);
         if (debug < 0) printf("isfileb trying %s\n",ftmpz);
         if (NULL != (INFILE=fopen(ftmpz,"r")) )
         {
            sprintf(cmnd,"zcat %s >/tmp/%s\n",ftmpz,ftmp1);
            exec(cmnd);
            sprintf(ftmp2,"/tmp/%s",ftmp1);
            if (debug < 0) printf("isfilec trying %s\n",ftmp2);
            if( NULL == (INFILE=fopen(ftmp2,"r")) )
            {
               sprintf(err,
                   "can't open %s (uncompressed %s)",ftmp2,ftmpz);
               getout(1);
            }
            comprd = TRUE;
            length = 1;
            ok = TRUE;
            sprintf(infile,"%s",ftmpz);
         }
      }
   }
   if (ok == FALSE)
   {
      if ((nfr >= 0 ) && (nfr <= 9 ))
              sprintf(ftmp2,"%s.000%d.ppm",ftmp1,nfr);
      if ((nfr >= 10) && (nfr <= 99))
              sprintf(ftmp2,"%s.00%d.ppm",ftmp1,nfr);
      if ((nfr >= 100) && (nfr <= 999))
              sprintf(ftmp2,"%s.0%d.ppm",ftmp1,nfr);
      if (nfr >= 1000)
              sprintf(ftmp2,"%s.%d.ppm",ftmp1,nfr);
      sprintf(filename,"%s",ftmp2);
      if (debug < 0) printf("isfiled trying %s\n",ftmp2);
      if( NULL == (INFILE=fopen(ftmp2,"r")) )
      {
         sprintf(ftmpz,"%s.Z",ftmp2);
         sprintf(filename,"%s",ftmpz);
         if (debug < 0) printf("isfilee trying %s\n",ftmpz);
         if( NULL != (INFILE=fopen(ftmpz,"r")) )
         {
            fclose(INFILE);
            comprd = TRUE;
            sprintf(cmnd,"zcat %s >/tmp/%s\n",ftmpz,ftmp2);
            exec(cmnd);
            sprintf(ftmp3,"/tmp/%s",ftmp2);
            if (debug < 0) printf("isfilef trying %s\n",ftmp3);
            if( NULL == (INFILE=fopen(ftmp3,"r")) )
            {
               sprintf(err,
                   "cannot open %s (uncompressed %s)",ftmp3,ftmpz);
               getout(1);
            }
            sprintf(infile,"%s",ftmpz);
            ok = TRUE;
         }
      }
      else
      {
         sprintf(infile,"%s",ftmp2);
         ok = TRUE;
      }
   }
   if (debug <= 0)
      printf("isfileg %d %d %d %s %s %s %s %s %s %s\n",
	ok,TRUE,nfr,fliname,friname,ftmp1,ftmp2,ftmp3,ftmpz,filename);
   return(ok);
} /* isfile */

/****************************************************/

checkhead()
/*
   check the heading of an image file

   called by isfile.
   calls getout.
*/
{
   char buf1[BMAX];
   int k;
   int temp;

   if (debug <= 0) printf("checkheada\n");
   for (k = 0; k < 4; ++k)
   {
      fscanf(INFILE,"%s\n",buf1);
      if (debug <= 0) printf("checkheadb %s\n",buf1);
      if (k != 0)
      {
	   sscanf(buf1,"%d",&temp);
           if (k == 1) fwidth = temp;
           else
	   if (k == 2) fheight = temp;
	   else
           if (k == 3) cmax = temp;
           else
	   {
	      sprintf(err,
                 "input header funny, frame %d\n%s\n",
		    nfr,buf1);
              getout(1);
	   }
      }
   }
   if (debug <= 0)
	 printf("checkheadc %d %d %d\n",
	    nfr,fheight,fwidth);
} /* checkhead */
/******************************************/

doframe()
/*
   load line buffer from image files
   and print it out.

   called by getfiles.
   calls     getout.
             
*/
{
   int x;
   int y;
   int rl,gl,bl;
   int rr,gr,br;
   int greyl[XMAX],greyr[XMAX];

   if (debug <= 0)
      printf("doframea %d %d %d %d %d\n",
         flwidth,CMAX,TRUE,frwidth,width);
   for (y = 0; y < height; ++y)
   {
      for ( x = 0; x < width; ++ x)
      {
         if ((x < flwidth) && (y < flheight))
            fscanf(INFILEL,"%d %d %d",&rl,&gl,&bl);
         else
         {
            rl = black;
            gl = black;
            bl = black;
         }
         greyl[x] = (rl + gl + bl)/3;

         if ((x < frwidth) && (y < frheight))
            fscanf(INFILER,"%d %d %d",&rr,&gr,&br);
         else
         {
            rr = black;
            gr = black;
            br = black;
         }
         greyr[x] = (rr + gr + br)/3;
      } /* x */
      combine(y,width,greyl,greyr);
   } /* y */
   fclose(INFILEL);
   fclose(INFILER);
   if (debug <= 0) printf("doframed %d %d\n",width,height);
} /* doframe */
/**********************************/

exec(cmnd)
char cmnd[BMAX];
/*
   execute a system command with optional echo

   called by isfile, getout, getpar, getfiles.
*/
{
   if (debug <= 0) printf("%s",cmnd);
   system(cmnd);
} /* exec */
/******************************************/

getout(v)
int v;
/*
   exit gracefully

   called by main, getpar, doframe, checkhead, isfile,
	     getframes, openout.
*/
{
   int j;

   if (v != 0) printf("anaglyphe: %s\n",err);
   sprintf(cmnd,"rm -rf /tmp/%s*\n",fliname); 
   if (keep == FALSE) exec(cmnd);
   sprintf(cmnd,"rm -rf /tmp/%s*\n",friname);
   if (keep == FALSE) exec(cmnd);
   exit(v);
} /* getout */
/*******************************************/

combine(y,width,greyl,greyr)
int y,width;
int greyl[XMAX],greyr[XMAX];
/*
   write line out

   called by  doframe.
*/
{
   int x;
   int r,g,b;

   if (debug < 0)
      printf("combinea  %d\n",width);
   for (x = 0; x < width; ++x)
   {
      r = greyl[x];
      g = greyr[x];
      b = black;
      fprintf(OUTFILE,"%3d %3d %3d ",r,g,b);
      count += 12;
      if (count > 57)
      {
         count = 0;
         fprintf(OUTFILE,"\n");
      }
   }
   if (debug < 0)
         printf("combineb  %d\n",y);
} /* combine */
/************************************************/

openout(nfr)
int nfr;
/*
   open output file

   called by getfiles.
   calls     getout.
*/
{
   if (debug <= 0) printf("openouta %d %s\n",nfr,foname);
   if ((nfr >= 0 ) && (nfr <= 9 ))
           sprintf(outfile,"%s.000%d.ppm",foname,nfr);
   if ((nfr >= 10) && (nfr <= 99))
           sprintf(outfile,"%s.00%d.ppm",foname,nfr);
   if ((nfr >= 100) && (nfr <= 999))
           sprintf(outfile,"%s.0%d.ppm",foname,nfr);
   if (nfr >= 1000)
           sprintf(outfile,"%s.%d.ppm",foname,nfr);
   if( NULL == (OUTFILE=fopen(outfile,"w+")) )
   {
      sprintf(err,"cannot open output file %s\n",outfile);
      getout(1);
   }
   count = 0;
} /* openout */
/************************************************/
 
int random()
/*
    return a random integer in the range 0 to 255.
 note : that a=123465,b=54321,c0=34567 gives a regular grid

 called by combine.
*/
{
   int ans;
   static unsigned int a=1234589,b=3432,c=4567;

   c = (b*c)%a;
   ans = 256*c/a;
   if (debug < -1)
         fprintf(stderr,"random %d %d %d %d\n",a,b,c,ans);
   return(ans);
} /* random */
/***************************************************/
