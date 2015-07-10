/*
               nudes.c
             version nude51

      runs the suite of NUDES programs under unix

   usage- nudes file [output] [options]

 last modified-
      3 Jul  2004   use -v for vector o/p, -p for pause

 For input, it searches for an input file name in the
       following order:
          file.n, file.4, file.3, file.2, or file.ps
          (NUDES files) in this directory.

   allows choice of output format :-
      -2     NUDES ellipse specification file
      -3     NUDES ellipsoid specification file
      -4     NUDES numeric command file
      -a     hanumeric output images
      -A     anaglyph output (red: left; green: right)
      -c [n] full shaded colour with 'n' colours allowed
             (default, default n:  10000)
      -D     dither the background of stereograms as well
             (default: figures only)
      -g     make monochrome grey scale images (default: colour)
      -G     make gif output images (default: mpg)
      -h     ellipsoid outlines with hidden lines removed
      -i [n] autostereogram with 'n' percent randomness (default n: 0)
      -J [n] juxtaposed stereo pairs, overlapping by 'n' pixels (default n: 0)
      -L     lenticular output (default: monocular)
      -m n1 n2    density images
      -M     mpg movie output (default)
      -p     pause 25 frames at start and end of mpg (default: no pause)
      -P     make ppm output image files
      -r n   b/w dithered with 'n' per cent correlated randomness in all frames
      -s [n] autostereogram, with eye separation 'n' pixels (default n: 160)
      -T     major axes only
      -u n   b/w dithered with 'n' per cent uncorrelated randomness
      -v     vector postscript file 
      -w     ellipsoid outlines with hidden lines visible
      -X     crossed stereo pairs
      -y     postscript for Laserwriter
      -Z     z shading (default: y shading)

   allows various other options :-
      -b n  start showing the figure from frame 'n' of NUDES
            script, and number the final frames from 'n' onward.
            (default: 0, i.e. the beginning)
      -B n  blur ellipsoids after the first 'n'(default: no blurring)
      -d n  debugging mode:
			   'n'>3: no diagnostics
			   'n'=3: main system calls;
			   'n'=2: warnings + main system calls; (default)
			   'n'=1: warnings + all system calls
			   "n"<1: stand well back
      -e n  interpolate extra frames if 'n' positive,
            else delete all but every 'n'th frame if 'n' negative,
            overridden by 'speed' commands in NUDES script.
            Only applies if input file is a NUDES script.
            (default: 1, i.e. no added or omitted frames)
      -E    echo all system commands (default: echo some)
      -g    make monochrome grey scale images (default: colour)
      -j    no shadows (default: show shadows)
      -k    keep intermediate files and temporary directories
            (default: delete intermediate files and directories)
      -l n  show sequence of length 'n' frames
            (default: the full length)
      -n    omit frame numbers
            (default: frame numbers inserted)
      -o n  draw n chords around each ellipse outline
            (default: n =  20)
      -q    quiet: omit all command echoes (default: echo some)
      -t s  use %s as temporary directory (default: /usr/tmp )
      -x n  set size of image to 'n' square (default:  256 square)
      -z    compress output file (default: no compression)

   previously modified -

     25 Feb  2004   set mpg FALSE when intermediate results requested
     28 Sep  2003   use bigger frame numbers (frad3c)
     22 Sep  2003   use echo 
     20 Sep  2003   default mpg, frame numbers, shadows 
     19 Sep  2003   make mpg output movies
     15 Sep  2003   make gif output image
     12 Sep  2003   using prfrmerr in home/bin
      7 Sep  2003   using prfrm
     24 Aug  2003   correcting comments re programs used
     24 Jul  2003   using prfrmz
     18 Jul  2003   using prfrmy
      6 Jun  2003   using prfrmx
     16 Jan  2003   using shadoq and viewc
     16 Jan  2003   using shadoq to remove low shadows
      9 Dec  2002   using shadep
     16 Nov  2002   allowing lenticular output
     10 Nov  2002   allowing lenticular output
      8 Nov  2002   fixing prfrmerr error
     12 Sep  2002   simplifying control flow
     29 Aug  2002   fixing -h bug
     10 Jan  2002   to use prfrmerr in same directory
     15 Aug  2001   to use shadeo
     12 Apr  2001   to use split3e
     21 Jun  1999   to use raselr
     20 Jun  1999   to use raselq
      2 Jun  1999   to use home= ~/don
     24 Jul  1998   correct miscount of prfrmerr file
      8 May  1998   accommodate stereo7
     21 Apr  1998   accommodate rasts, raselp, juxte, stereo6.
     20 Apr  1998   accommodate anaglyphe
     14 Apr  1997   accommodate anaglyphd
     13 Apr  1997   accommodate juxtd
     23 Mar  1997   fix debug bug (accommodate complm)
     21 Mar  1997   accommodate stereo5 
     18 Mar  1997   allow warnings to be suppressed (uses compll)
      7 Dec  1996   accommodate rastr 
     18 Oct  1996   fix bugs in rastp and raselo
      4 Oct  1996   allow optional spacing of freeview images
     14 Sep  1996   fix another bug in rasto
     27 Jul  1996   fix bug in rasto
     16 Jul  1996   use postscript for intermediate vector files
     16 Jul  1996   clean up frame numbering
     29 Jun  1996   accommodate texture files
     17 Jun  1996   clean up output file names
      7 Jun  1996   ppm output formats
      8 May  1996   allow anaglyphs
     14 Apr  1996   allow percentage of random dithering
     10 Apr  1996   allow blurring
      9 Apr  1966   allow z shading
      8 Apr  1996   generate juxtaposed stereo pairs too
     14 Mar  1996   allow stereo dithered file types
      7 Mar  1996   generate postscript output
      7 Feb  1996   use updated hide and prfrm programs
      2 Feb  1996   scan y upward
      5 Jan  1996   fix colour bugs
     20 Oct  1995   generate autostereograms
     26 May  1994   interpret prfrm messages
     17 Jul  1993   include density images
     28 Oct  1992   include joint limits
     22 Oct  1992   include shadows
      9 Jan  1992   limit number of colours
     21 Dec  1991   allow choice of frame numberr
     28 Nov  1991   use prfrm error messages
      1 Jul  1991   allow arbitrary colours
     31 Mar  1989   /usr/tmp to reduce ethernet
      6 Jun  1988   remove intermediate files (Myles Thomas)
     27 May  1988   compress image files
     17 Jan  1988   modified for AED512 colour
     14 Sep  1987   modified for Sun 3/50
      1 Apr  1987   for DEC VAX/780 at basser
      3 Jun  1986   in C for UNIX on DEC VAX/8600

 Compile using -
         For DEC or MIPS -
      cc nudes.c -o nude34 -lm -lX11 -I/usr/include/bsd -lbsd
         For a Sun -
      cc nudes.c -o nude34 -lm -lX11 -I/usr/include/bsd
         For an Iris -
      cc nudes.c -o nude34 -lgl_s -I/usr/include/gl -lm

   The program creates a directory /usr/tmp and copies data file there.
   It creates lots of intermediate files there.
   The final display file is copied back to original directory,
     and the intermediate subdirectory is cleared and removed,
     unless the -k flag is used.

   Single images may be displayed using 'xv'.
   Animated sequences can be constructed using 'movieconvert',
   and displayed using 'movieplayer'.
   On Silicon Graphics machines, an ellipsoid file may be viewed,
   animated and manipulated in real time using 'drawel'.

   **********************************

   NUDES Syntax:-

     (NUDES program) = (declarations) (movements) (stop)

   where (declarations) =
     (declaration)
     (declarations)

   where (declaration) =
     debug   (integer)
     speed   (multiplier)
     view    (framestart) (framestop)
     figure  (figurename) (ellipsoidcount) (ellipsoidnamelist)
     ellips  (ellipsoidname) (x) (y) (z)
     joint   (jointname) (ellipsoidname) (x) (y) (z)
                      (ellipsoidname) (x) (y) (z)
     limit   (jointname) (xmin) (xmax) (ymin) (ymax) (zmin) (zmax)
     variab  (variablecount) (variablenamelist)
     subrou  (subroutinename)
     endsub  (subroutinename)

   where (movements) =
     (movement)
     (movements)

   where (movement) =
     call    (framestart) (framestop) (sname)
     repeat  (framestart) (framestop) (action)
     linear  (framestart) (framestop) (action)
     quadra  (framestart) (framestop) (action)
     accele  (framestart) (framestop) (action)
     decele  (framestart) (framestop) (action)

   where (action) =
     debug   (level)
     call    (sname)
     colour  (ename) (redvalue) (greenvalue) (bluevalue)
     textur  (ename) (iname) (xoffset) (yoffset)
     grofig  (fname) (ename) (xfactor) (yfactor) (zfactor)
     groell  (ename) (xfactor) (yfactor) (zfactor)
     grojnt  (ename) (jname) (xfactor) (yfactor) (zfactor)
     movjnt  (jname) (ename) (x) (y) (z)
     moveto  (fname) (ename) (x) (y) (z)
     moveby  (fname) (refell) (x) (y) (z)
     ground  (fname)
     spinto  (fname) (ename) (refell)
                 (colatitude) (longditude) (twist)
     spinby  (fname) (ename) (refell) (angle) (axis)
     bendto  (mvgell) (jname) (refell)
                 (colatitude) (longditude) (twist)
     bendby  (mvgell) (jname) (refell)
                 (angle) (axis)
     flex    (mvgell) (jname) (angle)
     rotate  (mvgell) (jname) (angle)
     abduct  (mvgell) (jname) (angle)
     drag    (ename) (mvgell) (jname) (refell) (axis)
     touch   (tchgell) (tchdell) (mvgell) (refell) (jname) (axis)
     abut    (tchgell) (tchdell) (refell) (axis)
     balanc  (mvgell) (jname) (refell) (axis)
     detach  (mvgell) (jname) (newfigurename)
     attach  (ename) (jname) (ename) (x) (y) (z)
     set     (variablename) (anything)
     invert  (variablename)
     negate  (variablename)
     add     (variablename) (x) (x)
     subtra  (variablename) (x) (x)
     multip  (variablename) (x) (x)
     divide  (variablename) (x) (x)
     angles  (ename) (refell)
                     (variablename) (variablename) (variablename)
     centre  (ename) (variablename) (variablename) (variablename)
     axes    (ename) (variablename) (variablename) (variablename)
     link    (jname) (variablename) (variablename) (variablename)
     observe (angle) (angle) (angle)
     place   (x) (y) (z)  {default: 500 500 500}
     write   (fname)
     print   (variablename)

   where (ellipsoidnamelist) =
     (ellipsoidname) (ellipsoidnamelist)
     (ellipsoidname)

   where (subroutinenamelist) =
     (subroutinename) (subroutinenamelist)
     (subroutinename)

   where (variablenamelist) =
     (variablename) (variablenamelist)
     (variablename)

   where (x),(y),(z),(angle),
         (colatitude),(longditude),(twist),
         (xfactor),(yfactor),(zfactor),
         (redvalue),(greenvalue),(bluevalue),
         (xoffset),(yoffset) =
     (variablename)
     (value)

   where  (framestart),(framestop) =
     (positiveinteger)

   where  (positiveinteger) =
     (digit)(positiveinteger)
     (digit)

   where  (level),(multiplier) =
     (integer)

   where  (integer) =
     (positiveinteger)
     -(positiveinteger)

   where  (value),(xmin),(xmax),(ymin),(ymax),(zmin),(zmax) =
     (integer).(positiveinteger)
     (integer)

   where  (fname) =
     all
     world
     (figurename)
     (variablename)

   where  (tchgell),(tchdell),(ename),(mvgell),(refell) =
     world
     (ellipsoidname)
     (variablename)

   where   (iname) =
     (imagename)
     (variablename)

   where   (jname) =
     (jointname)
     (variablename)

   where  (sname) =
     (subroutinename)
     (variablename)

   where  (prefix) =
     (non-space character)

   where  (newfigurename),
       (figurename),(ellipsoidname),
       (jointname),(subroutinename),
       (variablename),(imagename) =
     (up to 6 non-space characters)

   where (axis) =
     (variablename)
     x
     y
     z

   where (anything) =
     (value)
     (axis)
     (ellipsoidname)
     (jointname)
     (figurename)
     (subroutinename)
     (variablename)

   where (stop) =
     stop


  *************************************

    NUDES Semantics

      key  no        description

    debug  22 - set debug parameter to given value
    speed  30 - delete or interpolate extra frames
    view   33 - set range of frames actually to be drawn
    figure  1 - declare ellipsoids that compose given figure
    ellips  2 - declare semi-axis lengths of given ellipsoid
    joint   3 - declare position of given joint
    variab 32 - declare names of variables

    repeat 23 - do the given action at each frame in given range
    linear 25 - generate action over given frames at constant rate
    quadra 24 - generate given action accltng then decrtng to rest
    accele  5 - generate action linearly accelerating from rest
    decele 10 - generate action linearly decelerating to rest

    link   49 - store coordinates of a joint
    axes   48 - store semiaxis lengths of an ellipsoid
    angles 36 - store the current orientation angles of an ellipsoid
    centre 38 - store current coordinates of centre of an ellipsoid
    subrou  6 - start a subroutine definition
    end    29 - end of subroutine or main program
    call   28 - call a subroutine
    stop   16 - no more commands after this

    colour 50 - colour the named ellipsoid with the red, green,
                blue components given (each in the range 0 - 255)
    textur 52 - map given image file onto named ellipsoid
    print  51 - print value of given variable
    ground 18 - make lowest point of figure touch ground plane
    grofig 11 - scale given figure about centre of given
                ellipsoid, multiplying all parts of figure
                by given factor
    groell 34 - scale a single ellipsoid in size keeping all
                joints fixed
    grojnt 35 - scale a single ellipsoid in size keeping a
                nominated joint of it fixed, and allowing its
                centre, other joints and connected ellipsoids
                to move appropriately
    movjnt 56 - move an ellipsoid (and every other ellipsoid joined to it)
                by moving the joint between ellipsoids
    moveby 13 - move given figure by given amounts parallel to
                the axes of given reference ellipsoid
    moveto 27 - move given figure so that centre of given
                ellipsoid is at given position
    spinby 17 - spin given figure about centre of given ellipsoid,
                rotating by given angle about given axis in given
                reference ellipsoid
    spinto 12 - spin given figure about centre of given ellipsoid,
                rotating given ellipsoid to given angles relative
                to axes in given reference ellipsoid
    bendby 19 - bend figure by given angle about given axis in
                given reference ellipsoid at given joint,
                rotating the given moving ellipsoid and all
                those joined to it
    bendto 21 - bend figure at given joint, rotating given
                ellipsoid to given angles relative to axes in
                given reference ellipsoid
    flex   38 - bend given joint about x axis
    rotate 39 - bend given joint about y axis inwards
    abduct 40 - bend given joint about z axis away from body
    drag   53 - bend second ellipsoid at given joint about its
                given axis so that the first ellipsoid
                touches the ground as well as ensuring that the
                rest of the figure is grounded
    touch  15 - make first ellipsoid touch the second ellipsoid
                by bending the third ellipsoid at the given joint
                about the given axis of the reference ellipsoid.
    abut   55 - slide figure containing first ellipsoid so that
                that ellipsoid touches the second ellipsoid,
                moving the figure parallel to the axis of th
                third (reference) ellipsoid)
    balanc  7 - bend at given joint about axis of reference
                ellipsoid to balance the moving set of ellipsoids
                with respect to y axis gravity
    set    20 - set a value to a named variable
    invert 31 - divide 1 by value
    negate 41 - negate the value of a named variable
    add    14 - add two variables or values to give a variable
    subtra 42 - subtract second value from first to give a variable
    multip 44 - multiply two values to give a variable
    divide 43 - divide second value into first to give a variable
    attach  8 - join 2 figures at the point on the second
                ellipsoid which is shifted from its centre
                by the given coordinates. The joined figure 
                is thereafter known by either name of the figures
                joined.
    detach  9 - break a figure into 2 at given joint, naming
                the new figure containing the given ellipsoid by
                the given name, and keeping the old figure name
                for the other part of the old figure
    observ 26 - set Eulerian angles of direction of observer
    place  47 - set centre of view of observer

  ************************************

   NUDES Introduction

     NUDES allows a user to manipulate a set of linked ellipsoids
     for which, various actions can be performed, each distributed
     over specified sets of frames;

     the whole scene or individual figures can be translated and
     rotated;

     the figures can be bent at any joint, thus allowing
     articulation;

     the whole scene, single figures, or individual ellipsoids can
     be scaled in size along each of the axes separately;

     additionally an ellipsoid can be scaled in size thus moving
     all the other ellipsoids connected to it except for those
     connected through a nominated joint;

     the scene or a figure can be positioned so that the lowest
     point just touches the ground;

     sequences of actions can be called as subroutines;

     various levels of echoing and diagnostics can be produced;

     the spacing of items is free, providing there is at
     least one space between items;

     data may be documented by inserting text between
     an *  and the end of a line;

     where more than one action occurs between a given pair of
     frames, they are performed in the order in which the
     respective commands are presented;

     the frame numbers must be integers in the range 0 to 32767;

     the earliest frame number is assumed to be notional only,
     and that frame is not drawn;

     frame numbers in subroutines are only internal and purely
     relative, with actual numbers supplied in the call;

     units :- the frame is 1000 units wide.
              the height depends on the output device.

     angles are in degrees measured anticlockwise about rotation
     axis looking from the origin toward plus infinity along
     that axis.

     keywords may be abbreviated arbitrarily provided
     no ambiguity results.

     keywords may not be used for names.

     all variables are global.

     x axis: left to right.
     y axis: up.
     z axis: away from observer.

  *************************************

   subroutines - 

   main      - organise the other subroutines
   setup     - setup constants
   dodname   - set name of working directory
   getinput  - set up input names
   images    - count input files
   donud     - make a NUDES.3 file from a NUDES.n file
   prmess    - print out diagnostics from prfrm
   getpar    - sort out input and output requirements
   findip    - work out which input file to use
   view      - do viewing transform, shadows and frame numbers
   frames3   - count frames in a NUDES.3 file
   dovector  - make a postscript file of line drawings
   colour    - make a shaded full colour image
   dodir     - make a temporary subdirectory
   doscan    - make image file from postscript file
   doprint   - produce alphanumeric picture
   doshade   - make shaded black and white images
   countin   - count the input files
   openin    - seek a file name containing the frame number
   openout   - create a file with a name containing a frame number
   exec      - execute a shell command
   getout    - remove temporary files and subdirectories
   doauto    - make autostereograms
   dopairs   - create stereo pair sequence
   makeseq   - make an animated sequence
   docompress- make a gif, compress an output file
   dolentic  - make a lenticular image
   dompg     - make mpg movie

 programs used from ~don/bin/ -

   anaglyphe- create an anaglyph (red/green) sequence
   complm   - produce NUDES.4 file from analysis of NUDES.n script
   densf    - produce density images from NUDES.3 file
   frad3c   - add frame numbers to NUDES.3 file
   hideo    - project ellipsoids to ellipses, removing hidden lines
   juxte    - juxtapose left and right sequences
   lentic   - make lenticular images
   nudes    - this program
   plotelg  - produce readable plot file from ellipse outlines
   prfrmerr - error messages for prfrm
   prfrm    - make ellipsoid and joint file from NUDES command file
   prplb    - draw lines on alphanumeric output device
   raselr   - produce ppm file shaded image(s) of ellipsoids
   rasts    - produce image file(s) from a readable plot file
   shadoq   - add shadow ellipsoids to ellipsoid file
   split3e  - break an ellipsoid file into many: one per frame
   stereo7  - create autostereogram image(s)
   twista   - make left and right NUDES scripts
   viewc    - apply viewing parameters
   visig    - project ellipsoids to give ellipse outlines

 associated programs -

   drawel   - animate an ellipsoid file using OpenGL
   draweln  - animate an ellipsoid file on an Iris
   eltonu   - convert an ellipsoid file into a nudes.n file
   edell    - edit a bunch of ellipsoids
   led      - edit a led.lbn Labanotation file
   linter   - interpret a led.lbn file into a nudes.n file
   showx    - animate a set of image files in X-Windows

 system programs used-

   chmod    - change file permissions
   cp       - copy a file
   ls       - list the files in a directory
   mv       - change the name/location of a file
   ppmquant - reduce number of colours in a ppm image
   ppmtogif - convert a ppm image to a gif image
   ppmtompeg- convert a set of ppm images to an mpg movie
   rm       - remove files and directories
*/

#include <stdio.h>
#include <values.h>
#include <sys/param.h>

#define BMAX 256  /* size of input string buffer */
#define CMAX 256  /* max number of shades per colour */
#define EMAX 1024 /* max number of ellipsoids */
#define TRUE 1
#define FALSE 0
#define NIL '\0'

char home[] = "/home/laban-experiments";
char bin[] = "bin";
char place  = 'u';

char bmess[BMAX];   /* message to juxte about starting frame number */
char bgmess[BMAX];  /* message about background */
char blmess[BMAX];  /* message about blurring */
char buf[BMAX];     /* input buffer used when counting NUDES.3 frames */
char command[BMAX]; /* string accumulating next system command */
char comess[BMAX];  /* message about colouring */
char device; /* code for output to be produced -
			  2 - an ellipse file
			  3 - an ellipsoid file
			  4 - a .4 file of coded actions for 'prfrm'
			  a - alphanumeric images
		        i - ppm (default)
		        p - postscript */
char dimess[BMAX]; /* message about b/w shading -
                    r - random (frame correlated)
			  u - random (frame uncorrelated)
			  g - smooth */
char endin[BMAX];   /* end of input file name */
char err[BMAX];     /* error messages */
char extn;          /* output file extension */
char fbase[BMAX];   /* base of data file name */
char file3[BMAX];   /* ellipsoid file name */
char file4[BMAX];   /* performance file name */
char figname[BMAX]; /* name of figure file if -D option not used */
char fin[BMAX];     /* name of input file */
char fout[BMAX];    /* name of output file */
char imess[BMAX];   /* stereo separation message */
char infile[BMAX];  /* name of input file containing frame number */
char input;         /* n, 2, 3, 4, p, or q for NUDES input file */
char kmess[BMAX];   /* message to anaglyphe re keeping intermediate files */
char opts[BMAX];    /* temporary store for each optional parameter */
char outfile[BMAX]; /* name of output file containing frame number */
char output; /* code for type of output required -
			  c - colour (default)
			  g - grey scale 
			  h - hidden lines
			  r - b/w random correlated
			  t - major axes only
			  u - b/w uncorrelated
			  w - wireframe */
char solid; /* type of solid to be used -
		        e - ellipsoids (default)
			  m - melded density functions */
char stem[BMAX];    /* name of stem of temporary directory */
char td[BMAX];      /* name of temporary subdirectory */
char type; /* code for type of output file 
                    L - lenticular
		        m - monoscopic
		        p - parallel stereo
		        x - cross stereo
		        a - anaglyph
		        w - wallpaper autostereogram
		        r - random stereogram */
char usez[BMAX];    /* for use if z shading */
char wd[BMAX];      /* name of original directory */

int backgrnd;       /* true if background to be dithered
		           (autostereograms only) (default: true) */
int compldebug;     /* debug parameter for complm */
int colmax;         /* number of allowed colours */
int comprs;         /* true if output files are to be compressed */
int debug;          /* prints diagnostics if value < 2 */
int docol;          /* true if colour requested */
int dofr;           /* insert frame numbers */
int dogif;          /* true if gif images wanted (default: false) */
int echoall;        /* true if all system commands to be echoed */
int echosome;       /* true if some system commands to be echoed */
int frend;          /* last frame number */
int getfig;         /* true if figure to be read from a file */
int grey = 127;     /* colour of frame numbers */
int keep;           /* true if intermediate files to be kept */
int length;         /* number of frames of a script to interpret */
int m;              /* index into buf array */
int m1,m2;          /* parameters to density program densf */
int move;           /* true if files to be moved from temp directory */
int mpg;            /* true if mpg movie wanted */
int n;              /* current frame count */
int nblur;          /* number of ellipsoids to be blurred */
int nfr;            /* current frame number */
int nframes;        /* number of frames in NUDES.3 file */
int nsteps;         /* number of chords around ellipse outline */
int pair;           /* true if stereo pairs wanted */
int pause;          /* true if 25 frame pause wanted at start and end */
int sepn;           /* overlap of freeview pairs */
int shadow;         /* true if shadows wanted */
int size;           /* picture width (assumed square) */
int speed;          /* add or omit frames */
int start;          /* the frame of input file at which to start (default: 1)*/


FILE *FILE3;
FILE *FILE4;
FILE *FIN;
FILE *INFILE;
FILE *OUTFILE;
FILE *PRFRMMESS;
FILE *PWDFILE;
/********************************************/

main(argc,argv)
int   argc;
char  *argv[];
/*
   calls setup, getpar, dodname, findip, dodir, dopairs,
	 makeseq, getout.
*/
{
   int k;

   printf("nude51/n");
   setup();
   dodname();
   getpar(argc,argv);
   findip(fbase);
   if (debug <= 0)
   {
      printf("nudes %s\n",fbase);
      printf("output %c\n",output);
      printf("device %c\n",device);
      printf("type %c\n",type);
      printf("input %c\n",input);
      printf("start %d\n",start);
      printf("length %d\n",length);
      printf("nframes %d\n",nframes);
      printf("size %d\n",size);
   } /* debug <= 0 */
   dodir();
   if (pair == TRUE) dopairs(fbase);
      else makeseq(fbase);
   if (mpg == TRUE) dompg(fbase);
   sprintf(command,"chmod 775 %s/*\n",wd);
   exec(FALSE);
   getout(0);
} /* main */
/*********************************************/

setup()
/*
   set up constants

   called by main.
*/
{
   type = 'm';
   input = 'n';
   output = 'c';
   device = 'i';
   solid = 'e';
   move = TRUE;
   pair = FALSE;
   backgrnd = TRUE;
   colmax = 10000;
   pause = 1;
   sprintf(usez," ");
   nsteps = 20;
   docol = TRUE;
   echoall = FALSE;
   echosome = TRUE;
   dofr = TRUE;
   dogif = FALSE;
   mpg = TRUE;
   keep = FALSE;
   debug = 2;
   start = 1;
   getfig = FALSE;
   length = MAXINT/2;
   comprs = FALSE;
   speed = 1;
   size = 256;
   shadow = TRUE;
   nframes = -1;
   sprintf(bgmess," ");
   sprintf(blmess," ");
   sprintf(comess," ");
   sprintf(dimess," ");
   sprintf(imess," ");
   sprintf(kmess," ");
   sprintf(stem,".");
   sprintf(fbase,"f");
} /* setup */
/************************************************/

dodname()
/*
   set up working directory name

   called by main
*/
{
   int k;

   char *answer;
   char *getwd();
   answer = getwd(wd);
   sprintf(wd,"%s",getwd(wd));
   
/*
   sprintf(command,"pwd > pwdfile\n");
   exec(FALSE);
   PWDFILE = fopen("pwdfile","r");
   fgets(wd,BMAX,PWDFILE);
   for (k = 0; k < BMAX; ++k)
      if (wd[k] == '\n') wd[k] = '\0';
   sprintf(command,"rm pwdfile\n");
   exec(FALSE);*/
} /* dodname */
/***********************************************/

getinput(f)
/*
   get input files

   called by makeseq.
   calls     donud, view, frames3, images.
*/
{
   if ((input == 'n') || (input == '4')) donud(f);

   if (device == '4') goto enuf;
   else
      if ((input == 'c') || (input == 'n')
       || (input == '3') || (input == '4'))
      view(f);

   if (device == '3') goto enuf;
   frames3(f);

enuf:
   if (debug <= 1)
      printf("getinputa %c %c %c\n",input,device,output);
} /* getinput */
/*********************************************/

donud(f)
char f[BMAX];
/*
   translate a NUDES script into a NUDES.3 ellipsoid file

   calls prmess, getout, exec.
         strcpy, strcat, sprintf, fprintf, printf, fopen, fclose, system.
   called by getinput.
*/
{
   int maxframe;
   FILE *SPEED;

   if (debug <= 0) printf("donuda %d\n",nframes);
   if (input == 'n')
   {
      strcpy(fin,f);
      strcat(fin,".n");
      if (NULL == (FIN = fopen(fin,"r")))
      {
         sprintf(err,
            "donud cannot find either %s or %s in directory %s\n",
            f,fin,wd);
         getout(1);
      }
      if (NULL == (SPEED = fopen("speed","w+")))
      {
         sprintf(err,"donud cannot open file 'speed'\n");
         getout(1);
      }
      maxframe = start-1+length;
      if (maxframe < 0) maxframe = MAXINT/2;
      fprintf(SPEED,"speed %d\n",speed);
      fprintf(SPEED,"view %d %d\n",start-1,maxframe);
      fclose(SPEED);
      sprintf(command,"cat speed %s > aug%s\n",fin,fin);
      exec(FALSE);
      sprintf(command,"%s/compln -d %d < aug%s > %s.4\n",
	      wd,compldebug,fin,f); /* fixed path, complm to compln */
      exec(FALSE);
      sprintf(outfile,"%s.4",f);
   }

   if (((input =='n') || (input == '4')) && (device != '4'))
   {
     sprintf(command,"%s/prfrm < %s.4 > %sa.3\n",wd,f,f); /* fixed path */
      if (debug <= 2) printf("%s",command);
      system(command);
      if (NULL != (PRFRMMESS = fopen("prfrm.mess","r")))
         prmess();
      else
      sprintf(outfile,"%s.3",f);
      sprintf(command,"cp %sa.3 %s 2>%s/cp1.mess\n",f,outfile,td);
      exec(FALSE);
   }
   if (debug <= 0) printf("donudb %s\n",f);
} /* donud */
/***************************************************/

prmess()
/*
 interpret error messages from prfrm

   Don Herbison-Evans  18 Dec 1986

   called by donud.
*/
{
   int j[7];
   int k;
   int njts,nels,fast,slow,npfs,nvals,nvars,nfigs;
   int nkeys,nsubs,vstrt,vstop,nfiles;
   int k0,frame,type,line;
   int skip;

   char buf[BMAX];
   char buf0[BMAX],buf1[BMAX],buf2[BMAX],buf3[BMAX];
   char c1;
   char ellnam[EMAX][BMAX];
   char fignam[EMAX][BMAX];
   char jntnam[EMAX][BMAX];
   char keynam[EMAX][BMAX];
   char subnam[EMAX][BMAX];
   char varnam[EMAX][BMAX];
   char m;
   char mess1[BMAX];
   char perr[BMAX];
   char thing[BMAX];

   FILE *PERR;

   printf("\nOOPS nudes in prfrm: \n");
/*
   get names of ellipsoids, joints, subroutines, etc. -
*/
   sprintf(file4,"%s.4",fbase);
   if ((FILE4 = fopen(file4,"r")) == NULL)
   {
      sprintf(err,"prmess cannot open %s\n",file4);
      getout(1);
   }
   fscanf(FILE4,"%d %d %d %d %d %d %d %d %d\n",
      &debug,&njts,&nels,&fast,&slow,&npfs,&nvals,&nvars,&nfigs);
   fscanf(FILE4,"%d %d %d %d %d\n",
      &nkeys,&nsubs,&vstrt,&vstop,&nfiles);
   --nkeys;
   skip = nsubs + npfs + njts + nfigs + nkeys
                    + (nvals-1)/5 + nfiles + nels + nkeys;
   for (k = 0; k < skip; ++k)
      fgets(buf,BMAX,FILE4);
   for (k = 0; k < nkeys ; ++k)
      fscanf(FILE4,"%d %s\n",&k0,keynam[k]);
   for (k = 0; k < nels ; ++k)
      fscanf(FILE4,"%d %s\n",&k0,ellnam[k]);
   for (k = 0; k < njts ; ++k)
      fscanf(FILE4,"%d %s\n",&k0,jntnam[k]);
   for (k = 0; k < nsubs ; ++k)
      fscanf(FILE4,"%d %s\n",&k0,subnam[k]);
   for (k = 0; k < nvars ; ++k)
      fscanf(FILE4,"%d %s\n",&k0,varnam[k]);
   for (k = 0; k < nfigs ; ++k)
      fscanf(FILE4,"%d %s\n",&k0,fignam[k]);
   sprintf(command,"cat prfrm.mess\n");
   exec(FALSE);
   sprintf(perr,"%s/%s/prfrmerr",home,bin);
   if ((PERR = fopen(perr,"r")) == NULL)
   {
      sprintf(err,"prmess cannot open %s\n",perr);
      getout(1);
   }
   fscanf(PRFRMMESS,"%s %d %s %d %s %d\n %d %d %d %d %d %d %d\n",
      buf0,buf1,&frame,buf2,&type,buf3,&line,
      &j[0],&j[1],&j[2],&j[3],&j[4],&j[5],&j[6]);
   while (fgets(buf,BMAX,PERR) != NULL)
   {
     if (debug <= 0) printf("prmess %s\n",buf);
     sscanf(buf,"%c %d",&m,&k0);
     if (k0 == j[0])
     {
         printf("\nerror number %d\n",k0);
         printf("in action type %d %s\n",
            type,keynam[type]);
         printf("on line %d of %s.n file\n",line,fbase);
         k = 0;
         while ((fgets(mess1,BMAX,PERR) != NULL)
            && (k < 6) && (j[k] != 12345))
         {
            mess1[strlen(mess1)-1]= NIL;
            if (k == 0)
               printf("%s\n",mess1);
            else
            {
               sprintf(thing," ");
               if ((mess1[0] == 'e') && (mess1[1] == 'l'))
                  sprintf(thing,"%s",ellnam[j[k]]);
               if ((mess1[0] == 'f') && (mess1[1] == 'i'))
                  sprintf(thing,"%s",fignam[j[k]]);
               if ((mess1[0] == 'j') && (mess1[1] == 'o'))
                  sprintf(thing,"%s",jntnam[j[k]]);
               if ((mess1[0] == 's') && (mess1[1] == 'u'))
                  sprintf(thing,"%s",subnam[j[k]]);
               if ((mess1[0] == 'v') && (mess1[2] == 'a'))
                  sprintf(thing,"%s",varnam[j[k]]);
               printf("%s %d %s\n",mess1,j[k],thing);
            }
            ++ k;
         }
         getout(0);
      }
   }
   sprintf(err,
      " error from `prfrm which prmess could not interpret.\n");
   getout(1);
} /* prmess */
/***********************************************/

getpar(argc,argv)
int argc;
char *argv[];
/*
  get output options from flags.

   called by main.
*/
{
   int len;
   int k;
   int levels;
   char caps;
   char f[BMAX];
   char next[BMAX];

   caps = 'A' - 'a';
   if ( argc < 2)
   {
      debug = 2;
      sprintf(command,"more %s/src/nudes.c",home);
      exec(FALSE);
      exit(1);
   }
   if (debug < 2)
   {
      printf("\n");
      for (k = 0; k < argc; ++ k)
         printf("%s ",argv[k]);
      printf("\n");
   }

   for (k = 1; k < argc; ++ k)
   {
      strcpy(opts,argv[k]);
      if (debug <= 0) printf("getpara %d %d %s\n",k,debug,opts);
      if (opts[0] == '-')
      {
         switch (opts[1])
         {
            case '4': device = '4';
                      comprs = FALSE;
                      mpg = FALSE;
                      break;
            case '3': device = '3';
                      comprs = FALSE;
                      mpg = FALSE;
                      break;
            case '2': device = '2';
	              if ((output == 'c') || (output == 'r')
		           || (output == 'g') || (output == 'u'))
		          output = 'h';
                      mpg = FALSE;
                      comprs = FALSE;
                      break;
            case 'a': output = 's';
                      break;
            case 'A': pair = TRUE;
                      move = FALSE;
                      type = 't';
                      break;
            case 'b': if (k == (argc-1))
                      {
                          printf(
                             "\nOOPS nudes:: not enuf parameters for '-b'\n");
                          exit(1);
                      }
                      sscanf(argv[k+1],"%d",&start);
		          sprintf(bmess,"-b %d ",start);
                      ++ k;
                      break;
            case 'B': if (k == (argc-1))
                      {
			       printf(
                           "\nOOPS nudes:: not enuf parameters for '-B'\n");
                         exit(1);
                      }
                      sscanf(argv[k+1],"%d",&nblur);
                      ++ k;
                      if (nblur < 0)
                      {
			       printf(
                           "\nOOPS nudes:: funny parameter for '-B': %d\n",nblur);
                         exit(1);
                      }
		          sprintf(blmess," -b %d ",nblur);
                      break;
            case 'c': output = 'c';
                      docol = TRUE;
                      if (k != (argc-1))
                      {
                         strcpy(next,argv[k+1]);
                         if ((next[0] <= '9') && (next[0] >= '0'))
                         {
                            sscanf(argv[k+1],"%d",&colmax);
                            ++ k;
                         }
                      }
                      sprintf(comess," -c %d ",colmax);
                      break;
            case 'd': if (k == (argc-1))
                      {
                          printf(
            "\nOOPS nudes:: not enuf parameters for '-d'\n");
                          exit(1);
                      }
                      sscanf(argv[k+1],"%d",&debug);
                      if (debug < 2)
                        printf("nudes debug = %d\n",debug);
                      ++ k;
                      break;
            case 'D': sprintf(bgmess," -b ");
		          pair = TRUE;
                      move = FALSE;
		          type = 's';
                      break;
            case 'e': if (k == (argc-1))
                      {
                          printf(
            "\nOOPS nudes:: not enuf parameters for '-e'\n");
                          exit(1);
                      }
                      sscanf(argv[k+1],"%d",&speed);
                      ++ k;
                      break;
            case 'E': echoall = TRUE;
	              echosome = FALSE;
                      break;
            case 'g': output = 'g';
	              docol = FALSE;
                      break;
            case 'G': comprs = FALSE;
                      dogif = TRUE;
                      mpg = FALSE;
                      break;
            case 'h': output = 'h';
	              docol = FALSE;
                      break;
	      case 'i': printf("\nOOPS nudes:: unknown parameter: i\n");
		          exit(1);
                      break;
            case 'j': shadow = FALSE;
                      break;
            case 'J': pair = TRUE;
                      move = FALSE;
                      type = 'j';
                      if (k != (argc-1))
                      {
                         strcpy(next,argv[k+1]);
                         if (((next[0] >= '0') && (next[0] <= '9'))
			    || (next[0] == '-'))
                         {
                            sscanf(argv[k+1],"%d",&sepn);
                            ++ k;
                         }
                      }
                      break;
            case 'L': pair = TRUE;
                      move = FALSE;
		          type = 'L';
                      break;
            case 'k': keep = TRUE;
                      sprintf(kmess," -k ");
                      break;
            case 'l': if (k == (argc-1))
                      {
                          printf(
            "\nOOPS nudes:: not enuf parameters for '-l'\n");
                          exit(1);
                      }
                      sscanf(argv[k+1],"%d",&length);
                      ++ k;
		         if (length < 1)
		         {
			    printf("length %d reset to %d\n",length,1-length);
			    length = 1-length;
		         }
                      break;
            case 'm': solid = 'm';
                      if (k == (argc-1))
                      {
                          printf(
            "\nOOPS nudes:: not enuf parameters for '-m'\n");
                          exit(1);
                      }
                      sscanf(argv[k+1],"%d",&m1);
                      ++ k;
                      if (k == (argc-1))
                      {
                          printf(
            "\nOOPS nudes:: not enuf parameters for '-m'\n");
                          exit(1);
                      }
                      sscanf(argv[k+1],"%d",&m2);
                      ++ k;
                      break;
            case 'M': mpg = TRUE;
                      move = FALSE;
                      comprs = FALSE;
                      dogif = FALSE;
                      break;
            case 'n': dofr = FALSE;
                      break;
            case 'o': if (k == (argc-1))
                      {
                          printf(
            "\nOOPS nudes:: not enuf parameters for '-o'\n");
                          exit(1);
                      }
                      sscanf(argv[k+1],"%d",&nsteps);
                      ++ k;
                      if (nsteps < 2)
                      {
                         printf(
            "\nOOPS nudes:: -o parameter funny: %d\n",nsteps);
                         nsteps = 2;
                         printf("reset to %d\n",nsteps);
                      }
                      if (nsteps < 3)
                         output = 't';
                      break;
            case 'p': pause = 25;
                      break;
            case 'P': dogif = FALSE;
                      mpg = FALSE;
                      break;
            case 'q': echoall = FALSE;
                      echosome = FALSE;
                      break;
            case 'r': device = 'r';
	                docol = FALSE;
                      levels = 99;
                      if (k != (argc-1))
                      {
                         strcpy(next,argv[k+1]);
                         if ((next[0] <= '9') && (next[0] >= '0'))
                         {
                            sscanf(next,"%d",&levels);
                            ++ k;
                         }
                      }
                      sprintf(dimess," -r %d ",levels);
                      break;
            case 's': type = 's';
                      pair = TRUE;
                      move = FALSE;
		          if (k != (argc-1))
                      {
                         strcpy(next,argv[k+1]);
                         if ((next[0] <= '9') && (next[0] >= '0'))
                         {
                            sprintf(imess," -i %s ",argv[k+1]);
                            ++ k;
                         }
                      }
                      break;
            case 't': if (k == (argc-1))
                      {
                          printf(
                          "\nOOPS nudes:: not enuf parameters for '-t'\n");
                          exit(1);
                      }
                      sscanf(argv[k+1],"%s",stem);
                      ++ k;
                      break;
            case 'T': output = 't';
		          nsteps = 2;
		          break;
            case 'u': device = 'u';
		          docol = FALSE;
                      levels = 99;
                      if (k != (argc-1))
                      {
                         strcpy(next,argv[k+1]);
                         if ((next[0] <= '9') && (next[0] >= '0'))
                         {
                            sscanf(next,"%d",&levels);
                            ++ k;
                         }
                      }
                      sprintf(dimess," -u %d ",levels);
                      break;
            case 'v': output = 'p';
                      break;
            case 'w': output = 'w';
		          docol = FALSE;
                      break;
            case 'x': if (k == (argc-1))
                      {
                          printf(
            "\nOOPS nudes:: not enuf parameters for '-x'\n");
                          exit(1);
                      }
                      if (debug <= 1)
                        printf("size %d overridden",size);
                      sscanf(argv[k+1],"%d",&size);
                      if (debug <= 1)
                        printf(" by %d\n",size);
                      ++ k;
                      break;
            case 'X': pair = TRUE;
                      move = FALSE;
                      type = 'x';
		          break;
            case 'y': device = 'y';
		          break;
            case 'z': comprs = FALSE;
		          break;
            case 'Z': sprintf(usez," -z ");
                      device = 'z';
		          break;
            default : sprintf(err,"getpar unknown flag: %s\n",opts);
                      getout(1);
         }
      }
      else
         strcpy(f,opts);
   }
   strcpy(fbase,f);
   extn = device;
   if ((docol == FALSE) && (extn >= 'a') && (extn <= 'z'))
	   extn += caps;
   if (output == 'c')      sprintf(comess,"-c %d",colmax);
   if (size <= 1) size = 256;
   compldebug = debug+1;
   if (debug > 2) --debug;
   if (debug <= 0)
      printf("getparb %d %c %c %c %c %c %c %d %d %d %d\n",
         debug,input,output,device,type,solid,extn,docol,TRUE,size,sepn);
} /* getpar */
/*************************************************/

findip(f)
char f[BMAX];
/*
   work out 'f', the root name of the NUDES script,
   and 'fin', the  input file to use.

   called by main
*/
{
   int len;

   fin[0] = '.';
   len = strlen(f);
   if (f[len-2] == '.')
   {
      strcpy(fin,f);
      if (f[len-1] == 'n') input = 'n';
      if (f[len-1] == '4') input = '4';
      if (f[len-1] == '3') input = '3';
      if (f[len-1] == '2')
      {
         input = '2';
         nframes = 1;
      }
      if ((f[len-1] == 'n')
       || (f[len-1] == '4')
       || (f[len-1] == '3')
       || (f[len-1] == '2'))
      {
         f[len-2] = f[len];
         f[len-1] = f[len];
      }
   }
   else
   if (f[len-3] == '.')
   {
      if ( (f[len-2] == 'p') && (f[len-1] == 's'))
      {
         input = 'p';
         strcpy(fin,f);
         f[len-3] = f[len];
         f[len-2] = f[len];
         f[len-1] = f[len];
         nframes = 1;
      }
      else
      {
         sprintf(err,"findip: funny input file: %s",f);
         getout(1);
      }
   }
   if (fin[0] == '.')
   {
      sprintf(fin,"%s.n",f);
      if (NULL != (FIN = fopen(fin,"r")))
      {
         input = 'n';
         fclose(FIN);
      }
      else
      {
         sprintf(fin,"%s.4",f);
         if (NULL != (FIN = fopen(fin,"r")))
         {
            input = '4';
            fclose(FIN);
         }
         else
         {
            sprintf(fin,"%s.3",f);
            if (NULL != (FIN = fopen(fin,"r")))
            {
               input = '3';
               fclose(FIN);
            }
            else
            {
               sprintf(fin,"%s.2",f);
               if (NULL != (FIN = fopen(fin,"r")))
               {
                  input = '2';
                  fclose(FIN);
                  nframes = 1;
               }
               else
               {
                  sprintf(fin,"%s.ps",f);
                  if (NULL != (FIN = fopen(fin,"r")))
                  {
                      input = 'p';
                      fclose(FIN);
                      nframes = 1;
                  }
                  else
                  {
                      sprintf(err,
                      "findip cannot open input file like %s\n",
                             f);
                      getout(1);
                  }
               }
            }
         }
      }
   }
   if (debug <= 0) printf("findipa f %s ; fin %s ; input %c ; nframes %d\n",
      f,fin,input,nframes);
} /* findip */
/************************************************/

view(f)
char f[BMAX];
/*
   produce shadows, apply viewing transform, and add frame numbers

   called by getinput.
*/
{
   if (debug <= 0) printf("viewa\n");
   if (input == '3') sprintf(outfile,fin);
   if (shadow == TRUE)
   {
      sprintf(command,"%s/shadoq < %s.3 > %sb.3\n",wd,f,f);
      exec(TRUE);
      if ((input != '3') && (keep == FALSE))
      {
         sprintf(command,"rm -f %s.3\n",f);
         exec(TRUE);
      }
      sprintf(outfile,"%sb.3",f);
   }
   sprintf(command,"%s/viewc  < %s > %sc.3\n",wd,outfile,f);
   exec(TRUE);
   if (keep == FALSE)
   {
      sprintf(command,"rm -f %s\n",outfile);
      exec(TRUE);
   }
   sprintf(outfile,"%sc.3",f);
   if (dofr == TRUE)
   {
      sprintf(command,"%s/frad3c -g %d < %s > %sd.3 \n",
	      wd,grey,outfile,f);
      exec(TRUE);
      sprintf(outfile,"%sd.3",f);
   }
   if (input != '3')
   {
      sprintf(command,"cp %s %s.3 2>%s/cp2.mess\n",outfile,f,td);
      exec(TRUE);
      sprintf(outfile,"%s.3",f);
   }
   if (debug <= 1) printf("viewc %s\n",outfile);
} /* view */
/************************************************/

frames3(f)
char f[BMAX];
/*
   find number of frames in NUDES.3 file, and if the file is not
   split into one file per frame, split it.

   called by getinput.
   calls countin.
*/
{
   if (debug <= 1) printf("frames3a\n");
   sprintf(file3,"%s",outfile);
   if ( NULL == (FILE3 = fopen(file3,"r")))
   {
      sprintf(endin,".3");
      countin(f);
      if (nframes < 1)
      {
         sprintf(err,"'frames3' cant open %s for reading\n",file3);
         getout(1);
      }
   }
   else
   {
     sprintf(command,"%s/split3e %s %d < %s\n",wd,f,start,file3);
      exec(TRUE);
      sprintf(endin,".3");
      countin(f);
   }
   if (debug <= 1) printf("frames3b\n");
} /* frames3 */
/**************************************/

dovector(f)
char f[BMAX];
/*
   make postscript file from a 3D ellipsoid file.

   calls  openin.
   called by makeseq.
*/
{
   if (debug <= 0) printf("dovectora %d %s\n",nfr,f);
   if ((input == 'n') || (input == '4') || (input == '3'))
   {
      sprintf(file3,"%s.3",f);
      sprintf(endin,".3");
      openin(f);
      if (keep == TRUE)
         sprintf(command,"cp %s %s 2>%s/cp3.mess\n",infile,file3,td);
      else
         sprintf(command,"cp %s %s 2>%s/cp4.mess\n",infile,file3,td);
      exec(nfr == start);

      if ((output == 's') || (output == 'w'))
         sprintf(command,"%s/%s/visig < %s > %s.2 \n",home,bin,file3,f);
      else if ((output == '2') || (output == 'h'))
            sprintf(command,"%s/hideo < %s > %s.2 \n",
		    wd,file3,f);
      else
      {
         sprintf(err,"dovector output = %c\n",output);
         getout(1);
      }
      exec(nfr == start);
   }

   if (device == '2')
      sprintf(outfile,"%s.2",f);
   else
   {
      sprintf(command,"%s/plotelg %d %s\n",wd,nsteps,f);
      exec(nfr == start);
      sprintf(outfile,"%s.ps",f);
   }
   if (debug <= 0) printf("dovectorb %d\n",nfr);
} /* dovector */
/**************************************/

dodensity(f)
char f[BMAX];
/*
   create shaded coloured image files.

   called by makeseq.
   calls openin.
*/
{
   if (debug <= 0) printf("dodensitya %d\n",nfr);
   sprintf(endin,".3");
   openin(f);
   sprintf(command,"cp %s %s 2>%s/cp5.mess\n",infile,file3,td);
   exec(nfr == start);
   sprintf(command,
     "%s/%s/densg %s -x %d %s -d %d -a %d -b %d < %s\n",
      home,bin,f,size,comess,1,m1,m2,file3);
   exec(nfr == start);
   sprintf(infile,"%s.0000.ppm",f);
   sprintf(outfile,"%s.0000.ppm",f);
   if (debug <= 0) printf("dodensityb %s\n",outfile);
}/* dodensity */
/********************************************************/

dodir()
/*
   create a new directory and go into it for working -

   called by main
*/
{
   if (debug <= 0) printf("dodira %s\n",td);
/*
   remove old versions of output file and temporary directory -
*/
   sprintf(td,"%s/%s.tmp",wd,fbase);
   sprintf(command,"rm -rf %s \n",td);
   if (debug < 2) printf("%s",command);
   system(command);

   sprintf(command,"mkdir %s\n",td);
   exec(TRUE);
   sprintf(command,"chmod 775 %s\n",td);
   exec(TRUE);
/*
   go into new directory -
*/
   if (debug < 2) printf("cd %s\n",td);
   if (chdir(td) < 0)
   {
      sprintf(err,"dodir cannot get into new directory %s\n",td);
      getout(1);
   }
/*
   copy or link input file(s) to new directory -
*/
   sprintf(command,"cp %s/prfrmerr %s 2>%s/cp0.mess\n",wd,td,td);
   if (debug <= 2) printf("%s",command);
   system(command);
   sprintf(command,"mv %s/rm1.mess %s/ 2>%s/mv1.mess\n",wd,td,td);
   if (debug < 2) printf("%s",command);
   system(command);

   if ((device == 'u') || (device == 'r') || (device == 'z')
      || (output == 's') || (device == 'g'))
   {
      sprintf(command,"cp %s/*.ppm  %s/. 2>%s/cp6.mess\n",wd,td,td);
      if (debug <= 2) printf("%s",command);
      system(command);
      sprintf(command,"cp %s/*.ppm.Z  %s/. 2>%s/cp7.mess\n",wd,td,td);
      if (debug <= 2) printf("%s",command);
      system(command);
   }
   sprintf(command,"cp %s/%s %s 2>cp8.mess\n",wd,fin,td);
   if (debug <= 2) printf("%s",command);
   system(command);
   if (debug <= 0) printf("dodirb %s\n",wd);
} /* dodir */
/*********************************************/

doscan(f)
char f[BMAX];
/*
   create image from line drawing

   called by makeseq.
*/
{
     if (debug <= 0) printf("doscana %d\n",nfr);
     sprintf(command,"%s/%s/rasts %s %d < %s.ps\n",
        home,bin,f,size,f);
     exec(nfr == start);
     sprintf(infile,"%s.0000.ppm",f);
     sprintf(outfile,"%s.0000.ppm",f);
} /* doscan */
/*******************************************/

doprint(f)
char f[BMAX];
/*
   draws vectors on alphanumeric displays or printers.

   called by makeseq.
*/
{
   if (debug <= 0) printf("doprint %d\n",nfr);
   if (device == 's')
   {
      sprintf(command,"%s/%s/prplb <%s >%s.pr\n",home,bin,outfile,f);
      exec(nfr == start);
      sprintf(infile,"%s.0000.txt",f);
      sprintf(outfile,"%s.0000.txt",f);
   }
   else
   {
      sprintf(err,
         " doprint device %c\n",device);
      getout(1);
   }
} /* doprint */
/*********************************************/

doshade(f,nfr)
char f[BMAX];
int nfr;
/*
   make shaded image of frame nfr.

   called by makeseq
   calls  openin
*/
{
   char colmess[BMAX];  /* message about colouring */

   sprintf(colmess," ");
   if (docol == TRUE) sprintf(colmess," -c ");
   if (debug <= 0)
     printf("doshadea %s %s %d %d %d\n",f,endin,nframes,docol,TRUE);
   openin(f);
   if ( keep == TRUE )
         sprintf(command,"cp %s %s 2>%s/cp9.mess\n",infile,file3,td);
      else
         sprintf(command,"mv %s %s 2>%s/mv9.mess\n",infile,file3,td);
      exec(nfr == start);
   sprintf(command,"%s/raselr %s %s %s %s -x %d < %s\n",
         wd,f,usez,blmess,colmess,size,file3);
   sprintf(infile,"%s.0000.ppm",f);
   sprintf(outfile,"%s.0000.ppm",f);
   exec(nfr == start);
   if (debug <= 0) printf("doshadec %s\n",outfile);
} /* doshade */
/***********************************/

countin(f)
char f[BMAX];
/*
    find number of input files

    called by  frames3, images
*/
{
   for (n = start; n < MAXINT; ++n)
   {
      if ((n >= 0 ) && (n <= 9 ))
             sprintf(infile,"%s.000%d%s",f,n,endin);
      if ((n >= 10) && (n <= 99))
             sprintf(infile,"%s.00%d%s",f,n,endin);
      if ((n >= 100) && (n <= 999))
             sprintf(infile,"%s.0%d%s",f,n,endin);
      if (n >= 1000)
             sprintf(infile,"%s.%d%s",f,n,endin);
      if( NULL == (INFILE=fopen(infile,"r")) )
              break;
      fclose(INFILE);
   }
   nframes = n-1;
   if (debug <= 0) printf("countina %d %s\n",nframes,infile);
} /* countin */
/***********************************/

openin(f)
char f[BMAX];
/*
    find name of input file

    called by  makeseq, colour, doshade.
*/
{
   if (debug <= 0) printf("openin %s %d %s\n",f,nfr,endin);
   if ((nfr >= 0 ) && (nfr <= 9 ))
             sprintf(infile,"%s.000%d%s",f,nfr,endin);
   if ((nfr >= 10) && (nfr <= 99))
             sprintf(infile,"%s.00%d%s",f,nfr,endin);
   if ((nfr >= 100) && (nfr <= 999))
             sprintf(infile,"%s.0%d%s",f,nfr,endin);
   if (nfr >= 1000)
             sprintf(infile,"%s.%d%s",f,nfr,endin);
   if( NULL == (INFILE=fopen(infile,"r")) )
   {
      if (debug <= 0)
        printf("openin cannot find %s for reading\n",infile);
   }
   else
   {
      if (debug <= 0)
             printf( "openin found %s\n",infile);
      fclose(INFILE);
   }
} /* openin */
/***********************************/

openout(f,outf,endf)
char f[BMAX];
char outf[BMAX];
char endf[3];
/*
    create new file

    called by  dolentic, docompress.
*/
{
   if ((nfr >= 0 ) && (nfr <= 9 ))
              sprintf(outf,"%s.%c.000%d.%s",f,extn,nfr,endf);
   if ((nfr >= 10) && (nfr <= 99))
              sprintf(outf, "%s.%c.00%d.%s",f,extn,nfr,endf);
   if ((nfr >= 100) && (nfr <= 999))
              sprintf(outf,  "%s.%c.0%d.%s",f,extn,nfr,endf);
   if (nfr >= 1000)
              sprintf(outf,   "%s.%c.%d.%s",f,extn,nfr,endf);
   if( NULL == (OUTFILE=fopen(outf,"w+")) )
   {
       sprintf(err,
          "openout: can't open/create %s for writing\n",outf);
       getout(1);
   }
   fclose(OUTFILE);
   if (debug <= 0) printf("openouta %s %d %s %s\n",f,nfr,endf,outf);
} /* openout */
/**********************************/

exec(echo)
int echo;
/*
   test and execute the command string 'command'

   called throughout
*/
{
   int e;

   if ((echoall == TRUE) || ((echo == TRUE) && (echosome == TRUE)))
      printf("%s",command);
   e = system(command);
   if (e != 0)
   {
      sprintf(err,"OOPS: exec %s\n   %s\n",e,command);
      getout(1);
   }
} /* exec */
/***************************************/

getout(n)
int n;
/*
   clear up as exiting

   called throughout
*/
{
   int top;
   int j;

   if (debug <= 0)
     printf("getout %c %c %c %d %d %d\n",
            input,output,device,nframes,comprs,TRUE);
   if (n != 0)
      printf("\nOOPS nudes in %s",err);

   sprintf(command,"chmod 775 %s\n",wd,td);
   if ((n > 0) && (debug < 2))
      printf("\n%s",command);
   else if (debug < 2)
      printf("%s",command);
   system(command);

   sprintf(command,"chmod 777 %s/*\n",td,td);
   if (debug < 2) printf("%s",command);
   system(command);

   if ((device == '3') || (device == '4'))
   {
      sprintf(command,"mv  %s %s/. 2>%s/mv5.mess\n",outfile,wd,td);
      if (debug < 2) printf("%s",command);
      system(command);
   }

   if (debug < 2) printf("cd %s\n",wd);
   chdir(wd);

   if (keep == FALSE)
   {
      sprintf(command,"rm -rf %s\n",td);
      if (debug < 2) printf("%s",command);
      system(command);
   }
   else
   {
      sprintf(command,"chmod 775 %s/* 2>%s/chmod6.mess\n",td,td);
      if (debug < 2) printf("%s",command);
      system(command);
   }
   exit(n);
} /* getout */
/******************************************/

doauto(f)
char f[BMAX];
/*
     make autostereograms

     called by makeseq.
*/
{
   if (debug <= 0) printf("doautoa %c %c\n",
	       output,device);
   if ((device == 'i') && (type == 's') &&
	   ((output == 'g')  || (output == 'c')))
   {
      sprintf(endin,".3");
      openin(f);
      if (keep == TRUE)
         sprintf(command,"cp %s %s 2>%s/cp8,mess\n",infile,file3,td);
      else
         sprintf(command,"mv %s %s 2>%s/mva.mess\n",infile,file3,td);
      exec(TRUE);
     
      if (output == 'c')
         sprintf(command,"%s/%s/stereo7 %s %s %s %s -c -x %d -y %d -n %d < %s\n",
                        home,bin,f,dimess,imess,bgmess,size,size,nfr,file3);
      else
      sprintf(command,"%s/%s/stereo7 %s %s %s %s -x %d -y %d -n %d < %s\n",
                        home,bin,f,dimess,imess,bgmess,size,size,nfr,file3);
      exec(TRUE);
   }
   else
   {
      sprintf(err," doauto:\n %c %c %c\n",
		      device,type,output);
      getout(1);
   }

   sprintf(outfile,"%s.0000.ppm",f);
   if (debug <= 0) printf("doautob %s %s\n",
	       infile,outfile);
} /* doauto */
/******************************************/

dopairs(f)
char f[BMAX];
/*
    make a set of paired stereo images

    called by main.
    calls     getout, makeseq, dolentic, docompress.
*/
{
   char fleft[BMAX];
   char fright[BMAX];
   char fold[BMAX];
   char finold[BMAX];
   char fnew[BMAX];

   if (debug <= 0) printf("dopairsa %c\n",device);
   if (input != 'n')
   {
      sprintf(err," dopairs\n input %c  type %c\n",
	   input,type);
      getout(1);
   } /* input != 'n' */
   sprintf(finold,"%s",fin);
   sprintf(fold,"%s",f);
   sprintf(command,"%s/%s/twista %s\n",home,bin,f);
   exec(TRUE);
   sprintf(fin,"%s.left.n",fold);
   sprintf(fleft,"%s.left",fold);
   if (debug <= 0) printf("dopairsb %s\n",fin);
   makeseq(fleft);
   sprintf(fin,"%s.right.n",fold);
   sprintf(fright,"%s.right",fold);
   if (debug <= 0) printf("dopairsc %s\n",fin);
   makeseq(fright);
   nfr = start;
   if (type == 't')
   {
      sprintf(command,"%s/%s/anaglyphe %s.left.%c %s.right.%c %s.%c %s -z %s\n",
         home,bin,fold,extn,fold,extn,fold,extn,kmess,bmess);
      exec(TRUE);
   }
   else
   if (type == 'j')
   {
      sprintf(command,"%s/%s/juxte %s.left.%c %s.right.%c %s.%c -s -%d %s\n",
	 home,bin,fold,extn,fold,extn,fold,extn,sepn,bmess);
      -- debug;
      exec(TRUE);
      ++debug;
   }
   else
   if (type == 'x')
   {
      sprintf(command,"%s/%s/juxte %s.right.%c %s.left.%c %s.%c -s %d %s\n",
	 home,bin,fold,extn,fold,extn,fold,extn,sepn,bmess);
      -- debug;
      exec(TRUE);
      ++ debug;
   }
   else if (type ='L')
      dolentic(fleft,fright);

   sprintf(outfile,"%s.%c*",fold,extn);
   docompress(f,0,FALSE);
   if (debug <= 0) printf("dopairsd %s\n",fold);
} /* dopairs */
/******************************************/

makeseq(f)
char f[BMAX];
/*
   make animated sequence

   called by main, dopairs.
   calls getinput, openin, dodensity, doauto, dovector, doshade,
         getout, doscan, doprint, docmprs.
*/
{
      if (debug <= 0) printf("makeseqa %c %c %d %d\n",
	    input,device,start,nframes);
      if (input != '2') getinput(f);
      if ((device == '3') || (device == '4')) goto enuf;

      for (nfr = start;  nfr <= nframes;  ++nfr)
      {
         if (debug <= 0) printf("makeseqb %d\n",nfr);
         if ((input == 'n') || (input == '4') || (input == '3'))
         {
            if (solid == 'm')
                dodensity(f);
	    else
	    if (type == 's')
	          doauto(f);
          else
          {
             if ((output == 's') || (output == 'h')
	        || (output == 'w') || (output == '2')
		  || (output == 't'))
                     dovector(f);
             else
             if ((output == 'g') || (output == 'c')
		  || (output == 'u') || (output == 'r'))
                     doshade(f,nfr);
             else
	       {
	          sprintf(err,
 "OOPS nudes makeseq: input %c,  solid %c,  type %c,   output %c\n",
		     input,solid,type,output);
             } /* combination no good */
          } /* output != 's' */
       } /* input = n,4,3  */
       else
	 if (input == '2')
            dovector(f);
       else
	 {
            sprintf(err," makeseq: unknown input: %c\n",input);
            getout(1);
       }

       if ((device == '2') && (comprs == TRUE))
       {
          docompress(f,nfr,FALSE);
          goto enuf;
       } /* device = '2' */
       if (debug <= 0) printf("makeseqc %d %d\n",nfr,nframes);

       if ((output == 's') || (output == 'h') || (output == 'w'))
       {
          if ((type == 't') || (type == 'j') || (type == 'x'))
		 doscan(f);
          else
          if (device == 's')
             doprint(f);
          else
          {
             sprintf(err,
                  " makeseq: output %c   device %c   type %c\n",
                  output,device,type);
             getout(1);
          } /* device != 's' */
       } /* output = 's','h','w' */

       if (debug <= 0) printf("makeseqd %d %s\n",nfr,outfile);
       docompress(f,nfr,TRUE);
    } /* nfr */

enuf:;
} /* makeseq */
/********************************************/

docompress(f,nfr,change)
char f[BMAX];
int nfr;
int change;
/*
   optionally make a gif output file
   compress output file
   change it to public readability,
   move it to initial directory

   calls openout.
   called by makeseq, dopairs.
*/
{

   char outgif[BMAX];
   char outtmp[BMAX];

   if (debug <= 0) printf("docompressa %d %s\n",nfr,outfile);
   if (change == TRUE)
   {
      strcpy(fout,outfile);
      openout(f,outfile,"ppm");
      sprintf(command,"cp %s %s\n",fout,outfile);
      exec(TRUE);
   }
   sprintf(command,"chmod 775 %s 2>chmod1.mess\n",outfile);
   exec(FALSE);
   if (dogif == TRUE)
   {
      openout("nudes",outtmp,"ppm");
      sprintf(command,"ppmquant 256 < %s > %s\n",outfile,outtmp);
      exec(nfr == start);
      openout(f,outgif,"gif");
      sprintf(command,"ppmtogif < %s > %s\n",outtmp,outgif);
      exec(nfr == start);
      strcpy(outfile,outgif);
   }
   if (comprs == TRUE)
   {
      sprintf(command,"rm -f %s.Z\n",outfile);
      exec(FALSE);
      sprintf(command,"compress %s\n",outfile);
      exec(FALSE);
      strcpy(fout,outfile);
      sprintf(outfile,"%s.Z",fout);
   }
   if ((pair == FALSE) && (mpg == FALSE))
   {
      sprintf(command,"mv %s %s/. 2>mv7.mess\n",outfile,wd);
      exec(TRUE);
   }
} /* docompress */
/*************************************************/

dolentic(fleft,fright)
char fleft[BMAX];
char fright[BMAX];
/*
   make a lenticular image sequence

   called by dopairs.
   calls openin, openout.
*/
{
   char f[BMAX];
   char finleft[BMAX];
   char finright[BMAX];
   char outf[BMAX];
   char inleft[BMAX];
   char inright[BMAX];

   if (debug <= 0)
   {
      printf("dolentica %s %s %s %c\n",
          fbase,fleft,fright,extn);
      sprintf(command,"ls -l *.ppm");
      exec(TRUE);
   }
   strcpy(endin,".ppm");
   for (nfr = start;  nfr <= nframes;  ++nfr)
   {
      openout(fbase,outfile,"ppm");
      strcpy(outf,outfile);
      sprintf(finleft,"%s.%c",fleft,extn);
      openin(finleft);
      strcpy(inleft,infile);
      sprintf(finright,"%s.%c",fright,extn);
      openin(finright);
      strcpy(inright,infile);
      sprintf(command,
            "%s/%s/lentic  %s   %s  > %s\n",
	    home,bin,inleft,inright,outf);
      exec(TRUE);
   } /* nfr */
} /* dolentic */
/************************************************/

dompg(fbase)
char fbase[BMAX];
/*
   make an mpg movie

   called by main
*/
{
      int p;

      sprintf(command,"rm -rf *.0000.*\n");
      exec(TRUE);
      sprintf(command,"ls *.ppm > n.mid\n");
      exec(TRUE);
 
       sprintf(command,"cp  %s/nudes.head n.head\n",wd);
      exec(TRUE);
      sprintf(command,"cp  %s/nudes.tail n.tail\n",wd);
      exec(TRUE);
    
      if (pause < 2)
      {
         sprintf(command,
            "cat n.head n.mid n.tail > nudes.par\n");
         exec(TRUE);
      }
      else
      {
         sprintf(command,"head -1 n.mid > n.first\n");
         exec(TRUE);
         sprintf(command,"tail -1 n.mid > n.last\n");
         exec(TRUE);
         for (p = 1; p < pause; ++p)
         {
	    sprintf(command,"cat n.first >> n.p1\n");
            exec(TRUE);
	    sprintf(command,"cat n.last >> n.p2\n");
            exec(TRUE);
         }
         sprintf(command,
            "cat n.head n.p1 n.mid n.p2 n.tail > nudes.par\n",
            home,home);
         exec(TRUE);
      }
      if ((echoall == TRUE) || (echosome == TRUE))
         sprintf(command,"ppmtompeg nudes.par\n");
      else
         sprintf(command,"ppmtompeg -q nudes.par\n");
      exec(TRUE);
      sprintf(command,"mv output.mpg %s/%s.mpg 2>mv6.mess\n",wd,fbase);
      exec(TRUE);
      if (keep == FALSE)
      {
         sprintf(command,"rm %s*.ppm n.* nudes.par 2>rm.mess\n",fbase);
         exec(TRUE);
      }
} /* dompg */
