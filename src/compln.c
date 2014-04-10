/*      program compln

     This progrm translates a NUDES script into a compact form
        for use by the next NUDES program

     The NUDES system allows a user to manipulate a set of
     linked ellipsoids

     compile for use under Xwindows for a MIPS using:
        cc complm.c -o complm -lm -lX11 -I/usr/include/bsd -lbsd

     modified -

    5 Nov 2008  adding limit to declaration syntax comment
    7 Sep 2003  avoiding expanding the 0-1 frame period with -e option
   23 Mar 1997  debug information hidden more
   18 Mar 1997  optional warnings
   21 Jul 1994  fixed 'match' bug
   28 Apr 1994  variable subroutines permitted
   10 Sep 1993  documentation improved
   16 Aug 1993  movjnt added
   12 Mar 1993  abut added
   11 Mar 1993  repeated subroutine calls allowed
    4 Mar 1993  keyword 'all' turned into 'every'
   28 Oct 1992  limits added
   12 Jun 1992  drag added
   12 Feb 1992  allow cubic movements
    7 Apr 1987  translated to c, copy deleted
   25 Nov 1986  write a complete figure
    7 Oct 1986  texture statement added
    8 Mar 1986  print statement added
   21 Jul 1985  ellipsoids declared on the fly
   22 Jun 1985  grofig scales about an ellipsoid (Peter Gummer)
   14 Jun 1985  spinto added (Peter Gummer)
   12 Apr 1985  simplified subroutine join (Peter Gummer)
    3 Apr 1985  world added, refell for spinby,moveby (Peter Gummer)
   23 May 1984  change parsing order
    7 May 1984  mul,sub,div,balance inserted
   22 Dec 1983  reduced number of constants in val
   14 Dec 1983  variable frame numbers
    2 nov 1983  moved integer codes 11-19 to 21-29 (Danuta Kucharska)
   15 Oct 1983  added 'colour' action (Danuta Kucharska)
   15 Oct 1983  ellipsoid default colour to flesh (Danuta Kucharska)
   16 Aug 1983  work out range of frames
   19 Apr 1983  axes, link put in, detach work
   31 Mar 1982  observe, all, par array stored
    1 Oct 1981  add,touch,attach,detach,flex,etc
   28 Sep 1981  declare variables to PMAX
   16 Jul 1981  to negate variables (Nora Neilands)
   16 Jun 1981  to store orientations and positions (Nora Neilands)
   29 May 1980  separate compile and perform
   27 Jul 1979  groell, grojnt added
   20 Feb 1979  subroutines added
    1 Apr 1977  named constants introduced
   17 Jan 1977  bends use arbitrary reference ellipsoid (Bruce McNair)
    4 Jun 1976  made interpretive
   10 May 1976  input trnsltn separated from drawing
    1 Apr 1975  frame numbers used in input language
   28 Oct 1974  to use optionally the plotter
   24 Sep 1974  to verbalize the input language
   11 Apr 1973  to allow more than one figure
    1 Dec 1972  to remove hidden lines

     originated : Don Herbison-Evans  1972

     Various actions can be performed on the ellipsoids,
     distributed over specified sets of frames.

     The whole scene or individual figures can be translated and
     rotated.

     The figures can be bent at any joint,
     thus allowing articulation.

     The whole scene, single figures, or individual ellipsoids can
     be scaled in size along each of the axes separately.

     Additionally an ellipsoid can be scaled in size,
     thus moving all the other ellipsoids connected to it,
     except for those connected through a nominated joint.

     The scene or a figure can be positioned so that the
     lowest point just touches the ground.

     Sequences of actions can be called as subroutines.

     Various levels of echoing and diagnostics can be produced.

     The spacing of items is free, providing there is at
     least one space between items.

     Data may be documented by inserting text between
     an *  and the end of a line.

     Where more than one action occurs between
     a given pair of frames, they are performed in the order
     in which the respective commands are presented.

     The frame numbers must be integers in the range 0 to 9999.

     The earliest frame number is assumed to be notional only,
     and that frame is not drawn.

     Frame numbers in subroutines are only internal and purely
     relative. the actual numbers are supplied in the call.

     Units - the frame is 1000 units wide (the height depends
          on the output device).

     Angles are in degrees measured anticlockwise
     about rotation axis looking from the origin toward
     plus infinity along that axis.

     Keywords may be abbreviated arbitrarily provided
     no ambiguity results.

     Keywords may not be used for names.

     All variables are global.

     x axis-left to right.
     y axis-up.
     z axis-away from observer.

  *************************************

   input syntax -

     (nudesscript) = (declarations) (movements) (stop)

   where (declarations) =
     (declaration)
     (declarations)

   where (declaration) =
     debug   (integer)
     speed   (multiplier)
     view    (framestart) (framestop)
     figure  (figurename) (ellipsoidcount) (ellipsoidnamelist)
     ellips  (ellipsoidname) (xvalue) (yvalue) (zvalue)
     joint   (jointname) (ellipsoidname) (xvalue) (yvalue) (zvalue)
                      (ellipsoidname) (xvalue) (yvalue) (zvalue)
     limit   (jointname)   (xvalue) (yvalue) (zvalue)
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
     cubic   (framestart) (framestop) (action)

   where (action) =
     debug   (level)
     call    (sname)
     colour  (ename) (redvalue) (greenvalue) (bluevalue)
     textur  (ename) (iname)   (xoffset) (yoffset)
     grofig  (fname) (ename)   (xfactor) (yfactor) (zfactor)
     groell  (ename) (xfactor) (yfactor) (zfactor)
     grojnt  (ename) (jname)   (xfactor) (yfactor) (zfactor)
     movjnt  (jname) (ename)   (x) (y) (z)
     moveto  (fname) (ename)   (x) (y) (z)
     moveby  (fname) (referenceellipsoid) (x) (y) (z)
     ground  (fname)
     spinto  (fname) (ename) (referenceellipsoid)
                     (colatitude) (longditude) (twist)
     spinby  (fname) (ename) (referenceellipsoid) (angle) (axis)
     bendto  (movingellipsoid) (jname) (referenceellipsoid)
                               (colatitude) (longditude) (twist)
     bendby  (movingellipsoid) (jname) (referenceellipsoid)
                               (angle) (axis)
     flex    (movingellipsoid) (jname) (angle)
     rotate  (movingellipsoid) (jname) (angle)
     abduct  (movingellipsoid) (jname) (angle)
     drag    (ename) (movingellipsoid) (jname)
                               (referenceellipsoid) (axis)
     touch   (mvell) (stillell) (movingellipsoid) (jname) (axis)
     balanc  (movingellipsoid) (jname) (referenceellipsoid) (axis)
     detach  (movingellipsoid) (jname) (fname)
     attach  (ename)           (jname) (ename) (x) (y) (z)
     set     (variablename) (anything)
     invert  (variablename)
     negate  (variablename)
     add     (variablename) (x) (x)
     subtra  (variablename) (x) (x)
     multip  (variablename) (x) (x)
     divide  (variablename) (x) (x)
     angles  (ename) (referenceellipsoid)
                  (variablename) (variablename) (variablename)
     centre  (ename) (variablename) (variablename) (variablename)
     axes    (ename) (variablename) (variablename) (variablename)
     linkx   (jname) (variablename) (variablename) (variablename)
     observe (angle) (angle) (angle)
     place   (x) (y) (z)
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

   where  (value),(xvalue),(yvalue),(zvalue) =
     (integer).(positiveinteger)
     (integer)

   where  (fname) =
     all
     world
     (figurename)
     (variablename)

   where  (ename),(stillell),(mvell),
       (movingellipsoid),(referenceellipsoid) =
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

   where  (oldfigurename),(newfigurename),
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

    input semantics -

      key  no        description

    debug  22 - set debug parameter to given value
    speed  30 - delete or interpolate extra frames
    view   33 - set range of frames actually to be drawn
    figure  1 - declare ellipsoids that compose given figure
    ellips  2 - declare semi-axis lengths of given ellipsoid
    joint   3 - declare position of given joint
    limit  54 - declare angle limits on joint movements
    variab 32 - declare names of variables

    repeat 23 - do the given action at each frame in given range
    linear 25 - generate action over given frames at constant rate
    quadra 24 - generate given action accelerating then decelerating
                to rest quadratically
    cubic  46 - generate given action accelerating then decelerating
                to rest cubically
    accele  5 - generate action linearly accelerating from rest
    decele 10 - generate action linearly decelerating to rest

    linkx  49 - store coordinates of a joint
    axes   48 - store semiaxis lengths of an ellipsoid
    angles 36 - store the current orientation angles of an ellipsoid
    centre 37 - store current coordinates of centre of an ellipsoid
    subrou  6 - start a subroutine definition
    end    29 - end of subroutine or main program
    call   28 - call a subroutine
    stop   16 - no more commands after this

    colour 50 - colour the named ellipsoid the red, green,
                blue coordinates given
    textur 52 - map given image file onto ellipsoid named
    print  51 - print value of given variable
    ground 18 - make lowest point of given figure touch ground plane
    grofig 11 - scale given figure about centre of given
                ellipsoid, multiplying all parts of figure
                by given factor
    groell 34 - scale a single ellipsoid in size keeping all
                joints fixed
    grojnt 35 - scale a single ellipsoid in size keeping a
                nominated joint of it fixed, and allowing its
                centre, other joints and connected ellipsoids
                to move appropriately
    moveby 13 - move given figure by given amounts parallel to
                the axes of given reference ellipsoid
    moveto 27 - move given figure so that centre of given
                ellipsoid is at given position
    movjnt 56 - move a joint relative to the centre of an
                ellipsoid
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
    drag   53 - bend second (moving) ellipsoid at given joint about
                its given axis so that first ellipsoid
                touches the ground, while ensuring that the rest
                of the figure is grounded also
    touch  15 - make first ellipsoid touch the second ellipsoid
                by bending the third ellipsoid at the given joint
                about the given axis of the third ellipsoid.
    abut   55 - make ellipsoid1 touch ellipsoid2 by moving its
                figure parallel to given axis of ellipsoid3
    balanc  7 - bend at given joint about given axis of reference
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
                by the given coordinates
    detach  9 - break a figure into 2 at given joint, naming
                the figure containing the given ellipsoid by
                the given name, and keeping the old figure name
                for the other part of the old figure
    observ 26 - set eulerian angles of direction of observer
    place  47 - set centre of view of observer

  *************************************

        subroutines -

     main    - drives it all
     setdebug- set debug level
     setup   - initialise all arrays
     inperf  - decode input text defining actions
     next    - get next string from input
     llength - find length of a line
     match   - compare string with set of identifiers
     addnam  - add a name to a list of names
     getint  - decode a string as an integer
     inells  - read parameters of an ellipsoid
     injts   - read the parameters of a joint
     inlims  - read angular joint limits
     inname  - read in a list of names
     join    - locate all ellipsoids by implementing joint commands
     parset  - decode parameters of an action
     prinvl  - prints summary of values, variables, and action
               subroutines
     prname  - print out a name
     store4  - write out digested action commands
     valadd  - add a value to a list of values
     value   - decode string as floating point number

  *************************************

*/

#include <stdio.h>
#include <values.h>

#define BMAX  256    /* max number of characters in a name */
#define EMAX 1024    /* max number of ellipsoids */
#define NKEYS  57    /* number of preset keynames */
#define PMAX 2345    /* max number of actions */
#define FALSE   0
#define TRUE    1
/*
  initialisations for complm.c
*/
int debug = 3;
int nline = -2;   /* number of current line of input file */
int figure = 1;   /* code of a 'figure' declaration */
int ellips = 2;   /* code of 'ellipsoid' declaration */
int joined = 3;   /* code of 'joint' declaration */
int viewfr = 33;  /* code of a 'view' declaration */
int decvar = 32;  /* code of declaration of variables */
int subrou = 6;   /* code of start of subroutine */
int calsub = 28;  /* code of subroutine call */
int endsub = 29;  /* code of end of subroutine */
int speedf = 30;  /* code for action to alter 'fast' and 'slow' */
int endnud = 16;  /* code for 'stop' at end of input actions */
int debugf = 22;  /* code for debug command */
int repeat = 23;  /* code for 'repeat' command */
int limits = 54;  /* code for 'limits' declaration */

char null  = '\0';
char blank = ' ';
char dig[11] = {'0','1','2','3','4','5','6','7','8','9','*'};
char dummy[6] = {'d','u','m','m','y'};
char every[6] = {'e','v','e','r','y'};
char nudes[6] = {'n','u','d','e','s'};
char world[6] = {'w','o','r','l','d'};
char variab[6]= {'v','a','r','i','a','b'};
char expect[9][10] = { {' '},
                       {'v','a','l','u','e'},
                       {'e','l','l','i','p','s','o','i','d'},
                       {'j','o','i','n','t'},
                       {'f','i','g','u','r','e'},
                       {'a','x','i','s'},
                       {'s','u','b','r','o','u','t','i','n','e'},
                       {'v','a','r','i','a','b','l','e','s'},
                       {'s','t','r','i','n','g'} };
/*
   par[p,k] - the type of the kth parameter of the pth action -
             0  none expected
             1  numeric value or variable name
             2  ellipsoid name
             3  joint name
             4  figure name
             5  axis name
             6  subroutine name
             7  variable name
             8  anything
             9  image file name
*/
int par[EMAX][6] =  {
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {1,0,0,0,0,0},
      {0,0,0,0,0,0},
      {2,3,2,5,0,0},
      {2,3,2,1,1,1},
      {2,3,4,0,0,0},
      {1,0,0,0,0,0},
      {4,2,1,1,1,0},
      {4,2,2,1,1,1},
      {4,2,1,1,1,0},
      {7,1,1,0,0,0},
      {2,2,2,2,3,5},
      {0,0,0,0,0,0},
      {4,2,2,1,5,0},
      {4,0,0,0,0,0},
      {2,3,2,1,5,0},
      {7,8,0,0,0,0},
      {2,3,2,1,1,1},
      {1,0,0,0,0,0},
      {1,0,0,0,0,0},
      {1,0,0,0,0,0},
      {1,0,0,0,0,0},
      {1,1,1,0,0,0},
      {4,2,1,1,1,0},
      {8,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {7,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {2,1,1,1,0,0},
      {2,3,1,1,1,0},
      {2,2,7,7,7,0},
      {2,7,7,7,0,0},
      {2,3,1,0,0,0},
      {2,3,1,0,0,0},
      {2,3,1,0,0,0},
      {7,0,0,0,0,0},
      {7,1,1,0,0,0},
      {7,1,1,0,0,0},
      {7,1,1,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {1,1,1,0,0,0},
      {2,7,7,7,0,0},
      {3,7,7,7,0,0},
      {2,1,1,1,0,0},
      {7,0,0,0,0,0},
      {2,9,1,1,0,0},
      {2,2,3,2,5,0},
      {0,0,0,0,0,0},
      {2,2,2,5,0,0},
      {3,2,1,1,1,0} };

char keynam[EMAX][BMAX] = {
      {'k','e','y','w','o','r','d'},
      {'f','i','g','u','r','e'},
      {'e','l','l','i','p','s','o','i','d'},
      {'j','o','i','n','t'},
      {'c','o','p','y'},
      {'a','c','c','e','l','e','r','a','t','e'},
      {'s','u','b','r','o','u','t','i','n','e'},
      {'b','a','l','a','n','c','e'},
      {'a','t','t','a','c','h'},
      {'d','e','t','a','c','h'},
      {'d','e','c','e','l','e','r','a','t','e'},
      {'g','r','o','f','i','g'},
      {'s','p','i','n','t','o'},
      {'m','o','v','e','b','y'},
      {'a','d','d'},
      {'t','o','u','c','h'},
      {'s','t','o','p'},
      {'s','p','i','n','b','y'},
      {'g','r','o','u','n','d'},
      {'b','e','n','d','b','y'},
      {'s','e','t'},
      {'b','e','n','d','t','o'},
      {'d','e','b','u','g'},
      {'r','e','p','e','a','t'},
      {'q','u','a','d','r','a','t','i','c'},
      {'l','i','n','e','a','r'},
      {'o','b','s','e','r','v','e'},
      {'m','o','v','e','t','o'},
      {'c','a','l','l'},
      {'e','n','d','s','u','b'},
      {'s','p','e','e','d'},
      {'i','n','v','e','r','t'},
      {'v','a','r','i','a','b','l','e','s'},
      {'v','i','e','w'},
      {'g','r','o','e','l','l'},
      {'g','r','o','j','n','t'},
      {'a','n','g','l','e','s'},
      {'c','e','n','t','r','e'},
      {'f','l','e','x'},
      {'r','o','t','a','t','e'},
      {'a','b','d','u','c','t'},
      {'n','e','g','a','t','e'},
      {'s','u','b','t','r','a','c','t'},
      {'d','i','v','i','d','e'},
      {'m','u','l','t','i','p','l','y'},
      {'r','e','a','d'},
      {'c','u','b','i','c'},
      {'p','l','a','c','e'},
      {'a','x','e','s'},
      {'l','i','n','k','x'},
      {'c','o','l','o','u','r'},
      {'p','r','i','n','t'},
      {'t','e','x','t','u','r','e'},
      {'d','r','a','g'},
      {'l','i','m','i','t'},
      {'a','b','u','t'},
      {'m','o','v','j','n','t'} };
/*
     code[p,k] - type of kth parameter of pth action using -

     0-illegal
     1-x coordinate
     2-y coordinate
     3-z coordinate
     4-angle 1
     5-angle 2
     6-angle 3
     7-x scaling factor
     8-y scaling factor
     9-z scaling factor
    10-value for a variable
    11,12,13-red green and blue colour coords, respectively,
               or image texture file reference ,xoffset and yoffset
    14-debug parameter

    21-axis
    22-joint
    23-reference ellipsoid
    24-moving or central ellipsoid
    25-figure
    27,28,29-names of variables
    30-touching or dragged ellipsoid (ell1)
    31-touched ellipsoid (ell2)
*/
int code[NKEYS][6] = {
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {24,22,23,21,0,0},
      {24,22,23,1,2,3},
      {24,22,25,0,0,0},
      {0,0,0,0,0,0},
      {25,24,7,8,9,0},
      {25,24,23,4,5,6},
      {25,23,1,2,3,0},
      {27,1,2,0,0,0},
      {30,31,24,23,22,21},
      {0,0,0,0,0,0},
      {25,24,23,4,21,0},
      {25,0,0,0,0,0},
      {24,22,23,4,21,0},
      {27,10,0,0,0,0},
      {24,22,23,4,5,6},
      {14,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {4,5,6,0,0,0},
      {25,24,1,2,3,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {27,0,0,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {24,7,8,9,0,0},
      {24,22,7,8,9,0},
      {24,23,27,28,29,0},
      {24,27,28,29,0,0},
      {24,22,4,0,0,0},
      {24,22,4,0,0,0},
      {24,22,4,0,0,0},
      {27,0,0,0,0,0},
      {27,1,2,0,0,0},
      {27,1,2,0,0,0},
      {27,1,2,0,0,0},
      {0,0,0,0,0,0},
      {0,0,0,0,0,0},
      {1,2,3,0,0,0},
      {24,27,28,29,0,0},
      {22,27,28,29,0,0},
      {24,11,12,13,0,0},
      {27,0,0,0,0,0},
      {24,11,12,13,0,0},
      {30,24,22,23,21,0},
      {0,0,0,0,0,0},
      {30,31,23,21,0,0},
      {22,24,1,2,3,0} };

float ax[EMAX][3];       /* ellipsoid semi-axis lengths */
float cen[EMAX][3];      /* centres of the ellipsoids */
float dcon[EMAX][2][3];  /* distances of joint from ellipsoid centres */
float jnt[EMAX][3];      /* coordinates of the joints */
float lim[EMAX][3][2];   /* angular limits on the joints */
float semiax[3];         /* coordinate triple read from input */
float val[EMAX];         /* constants used by data file */

int allok;               /* set to true only if all data decoded ok */
int called[PMAX];        /* true if subroutine is called */
int cline[PMAX];         /* line numbers in input file of each action */
int coel[EMAX][2];       /* the 2 ellipsoids joined at a joint */
int defined[EMAX];       /* true if subroutine is defined */
int distrn[PMAX];        /* how actions are distributed over frames */
int ellfig[EMAX];        /* number of the figure containing each ellipsoid
                            (zero if not dimensioned) */
int fast;                /* factor multiplying frame counts */
int frstop[PMAX];        /* number of last frame affected by action */
int frstrt[PMAX];        /* frame number after which action is to begin */
int figell[EMAX];        /* numbers of first ellipsoid in each figure */
int knee[EMAX];          /* true if joint is a knee and flexes backwards */
int length;              /* length of next input string */
int lline;               /* length of next input line */
int nels;                /* number of ellipsoids */
int nfigs;               /* number of figures */
int nfiles;              /* number of texture map files */
int njts;                /* number of joints */
int npfs;                /* number of actions */
int nsubs;               /* number of action subroutines */
int nvals;               /* number of values in 'val' */
int nvars;               /* number of variables in 'varname' */
int ok;                  /* true if last set of characters
                            decoded ok */
int pf[PMAX][6];         /* action parameters, coded as-
                            positive -  itself
                            negative -  index into array 'val' */
int pok;                 /* true if positive integer read */
int ptype;               /* code of current action */
int slow;                /* factor by which frames are to be cut */
int start;               /* pointer to next character on current
                            input line */
int subact[EMAX][2];     /* numbers of the first and last
                            actions of the subroutines */
                         /* actions of subroutines */
int type[PMAX];          /* the type codes of the actions */
int usevar[EMAX];        /* zero if variable not used */
int vstrt,vstop;         /* range of frame numbers to be drawn */

int axlen[EMAX];         /* lengths of names */
int ellen[EMAX];
int figlen[EMAX];
int jntlen[EMAX];
int fillen[EMAX];
int keylen[EMAX];
int sublen[EMAX];
int varlen[EMAX];

char axnam[EMAX][BMAX];  /* first entry is the set of axis names -
                            'x','y','z'. The rest are null */
char ellnam[EMAX][BMAX]; /* ellipsoid names */
char fignam[EMAX][BMAX]; /* figure names */
char filnam[EMAX][BMAX]; /* texture map file names */
char jntnam[EMAX][BMAX]; /* joint names */
char line[BMAX];         /* input buffer */
char string[BMAX];       /* next set of non-blank characters
                            from data file */
char subnam[EMAX][BMAX]; /* subroutine names */
char varnam[EMAX][BMAX]; /* variable names */

/******************************************/

main(argc,argv)
int argc;
char *argv[];
/*
   calls  setdebug, setup, inperf, prinvl, join, store4.
*/
{
   setdebug(argc,argv);
   setup();
   allok = TRUE ;
   inperf();
   if (debug <= 0) prinvl();
   if (allok == FALSE) exit(1);
   join();
   if (allok == TRUE) store4(); else exit(1);
   exit(0);
} /* main */
/***********************************************************/

setdebug(argc,argv)
int argc;
char *argv[];
{
   if (argc > 2)
   {
      if  ((argv[1][0] == '-')
	&& (argv[1][1] == 'd'))
      {
         sscanf(argv[2],"%d",&debug);
      }
   }
} /* setdebug */
/********************************************************/

setup()
/*
     clears nfigs,nels,njts,nvars,nvals,nsubs.
     clears fignam,ellnam,jntnam,varnam,subnam to nulls.
     initialises keyword and axis names.
     sets other name lengths to -1.
     clears val,figell,coel,subact,cen,ax.
     initialises subroutine "nudes", figure "every",
       and ellipsoid "world".

     called by main
*/
{
   int stop = 16;
   int j,k ;

   if (debug <= 0) fprintf(stderr,"setupa\n");
/*
     clear everything
*/
   vstrt = 0 ;
   vstop = MAXINT-1;
   start = -1 ;
   lline = 0;
   fast = 1 ;
   slow = 1 ;
   njts = -1 ;
   nvars = -1 ;
   nfiles = 0 ;
   nvals = 0 ;
   axlen[0] = 1; axlen[1] = 1;; axlen[2] = 1;
   for (  j = 0 ; j < EMAX ; ++ j )
   {
      if ( j > 2) axlen[j] = -1;
      keylen[j] = 0;
      ellen[j] = -1;
      jntlen[j] = -1;
      fillen[j] = -1;
      figlen[j] = -1;
      sublen[j] = -1;
      varlen[j] = -1;
      knee[j] = 0 ;
      figell[j] = 0 ;
      ellfig[j] = 0 ;
      usevar[j] = 0 ;
      coel[j][0] = -1 ;
      coel[j][1] = -1 ;
      subact[j][0] = 0 ;
      subact[j][1] = 0 ;
      called[j] = FALSE;
      defined[j] = FALSE;
      val[j] = 0.0 ;

      for (  k = 0 ; k < 3 ; ++ k )
      {
         cen[j][k] = 0.0 ;
         ax[j][k] = 0.0 ;
         lim[j][k][0] = -90.0;
         lim[j][k][1] =  90.0;
      }

      for (  k = 0 ; k < BMAX ; ++ k )
      {
         axnam[j][k] = null;
         filnam[j][k] = null ;
         fignam[j][k] = null ;
         ellnam[j][k] = null ;
         jntnam[j][k] = null ;
         varnam[j][k] = null ;
         subnam[j][k] = null ;
      }
   }
   axnam[0][0] = 'x';
   axnam[1][0] = 'y';
   axnam[2][0] = 'z';
/*
     set all actions by default to stop
*/
   for (  j = 0 ; j < PMAX ; ++ j )
   {
      type[j] = stop ;
      frstrt[j] = 0 ;
      frstop[j] = 0 ;
      distrn[j] = 0;
      cline[j] = 0 ;

      for (  k = 0 ; k < 6 ; ++ k )
         pf[j][k] = 0 ;
   }
/*
     artificially set up subroutine "nudes",
     file "dummy", figures "every" and "world",
     variable "variable", and ellipsoid "world"-
*/
   nsubs = 0 ;
   nfigs = 1 ;
   nels = 0 ;
   figell[0] = 0 ;
   figell[1] = 1 ;

   for (  k = 0 ; k < 6 ; ++ k )
   {
      filnam[0][k] = dummy[k];
      subnam[0][k] = nudes[k] ;
      fignam[0][k] = every[k] ;
      fignam[1][k] = world[k] ;
      ellnam[0][k] = world[k] ;
      varnam[0][k] = variab[k];
   }
   fillen[0] = 5;
   sublen[0] = 5;
   figlen[0] = 5;
   figlen[1] = 5;
   ellen[0] = 5;
   varlen[0] = 6;
   ax[0][0] = 1.0 ;
   ax[0][1] = 1.0 ;
   ax[0][2] = 1.0 ;
} /* setup */
/***************************************/

inperf()
/*
     this decodes the input text defining the required actions.

   variables
     comand   -counter through all commands.
     how      -type number of current action keyname.
     main     -true if in main program.
     nmax     -max number of commands possible.
     p        -counter through actions.
     ptype    -type of action being read.
     thisub   -number of current subroutine.

     called by main
     calls  next, match, addnam, inname, inells, injts,
         value, parset.
*/
{
   int comand,how,j,k,nmax,p,thisub ;
   int inells(),match(),parset();
   float v;
   float value();
   
   if (debug <= 0) fprintf(stderr,"inperfa\n");
   ok = TRUE ;
   p = 0 ;
   thisub = 0 ;
   subact[0][0] = 0 ;
   nmax = 4*EMAX+PMAX ;
/*
     run through statements
*/
   for (comand = 1; ((allok == TRUE) && (comand <= nmax)); ++comand)
   {
      start = -1 ;
      next();
      how = match(keynam,NKEYS,keylen) ;
      ptype = how;
      if (( how <= 0 ) || ( how >= NKEYS))
         ok = FALSE;
      else
      if (how == endnud)
      {
         subact[thisub][1] = p-1;
         break;
      }
      else
      if (how == figure)
      {
         next();
         addnam(&nfigs,fignam,0,figlen);
         figell[nfigs] = nels+1 ;
         inname(&nels,ellnam,0,ellen);
      }
      else
      if (how == ellips)
      {
         j = inells();
         ax[j][0] = semiax[0] ;
         ax[j][1] = semiax[1] ;
         ax[j][2] = semiax[2] ;
      }
      else
      if (how == joined)
         injts();
      else
      if (how  == limits)
         inlims();
      else
      if (how == debugf)
      {
         next();
         v = value() ;
         if (v >= 0.0) debug = v+0.5 ;
         if (v < 0.0) debug = v-0.5 ;
      }
      else
      if (how == decvar)
      {
         inname(&nvars,varnam,1,varlen);
         if ( (nvars+nvals) > EMAX) ok = FALSE ;
      }
      else
      if (how == speedf)
      {
         next();
         v = value() ;
         if (v < 0.0) slow = -v+0.5 ;
         if (v > 0.0) fast = v+0.5 ;
      }
      else
      if (how == viewfr)
      {
         next();
         v = value();
         if ( ok == TRUE )
         {
            vstrt = v ;
            next();
            v = value();
            if ( ok == TRUE ) vstop = v ;
         }
      }
      else
      if (how == subrou)
/*
     start a subroutine -
*/
      {
         if (thisub == 0) subact[0][1] = p-1;
         next();
         thisub = match(subnam,nsubs,sublen) ;
         if (thisub <= 0)
         {
            addnam(&nsubs,subnam,0,sublen);
            if ( ok == TRUE ) thisub = nsubs ;
         }
         defined[thisub] = TRUE;
         subact[thisub][0] = p ;
         if (debug <= 0)
            fprintf(stderr,"inperfb %d %s %d %d %d %d\n",
               nsubs,string,thisub,p,subact[thisub][0],subact[thisub][1]);
      }
      else
      if (how == endsub)
/*
     end of a subroutine -
*/
      {
         next();
         k = match(subnam,nsubs,sublen) ;
         if (k == thisub) subact[k][1] = p-1 ;
            else ok == FALSE;
         if (debug <= 0)
            fprintf(stderr,"inperfc %s %d %d %d %d\n",
               string,thisub,k,subact[k][0],subact[k][1]);
      }
      else
/*
     read an action -
*/
      {
         if (p >= PMAX)
         {
            p = PMAX-1 ;
            fprintf(stderr,"beware- more than %d action specs\n",
               PMAX);
            fprintf(stderr,"actions deleted after line  %d\n%s\n",
               nline,line);
         }
         else
         {
            distrn[p] = how ;
            cline[p] = nline ;
/*
     read frames to which this action refers -
*/
            frstrt[p] = parset(1);
            if ( ok == TRUE ) frstop[p] = parset(1);
            if (ok == TRUE)
            {
/*
     call of a subroutine -
*/
               if (how == calsub)
               {
                  distrn[p] = calsub ;
                  ptype = calsub ;
                  type[p] = calsub ;
                  next();
                  k = match(varnam,nvars,varlen);
                  if (k < 0)
                  {
                     k = match(subnam,nsubs,sublen);
                     if (k < 0)
                     {
                        addnam(&nsubs,subnam,0,sublen);
                        k = nsubs;
                     }
                     called[k] = TRUE;
                     pf[p][0] = k;
                  }
                  else
                     pf[p][0] = k - EMAX + 1 ;
               }
               else
/*
     read action done in these frames -
*/
               {
                  next();
                  ptype = match(keynam,NKEYS,keylen) ;
                  type[p] = ptype ;
                  if ((ptype < 1) || (ptype >= NKEYS))
                     ok = FALSE ;
                  else
/*
     run through parameters of pth action -
*/
                  {
                     for (  j = 0 ; j < 6 ; ++ j )
                        pf[p][j] = parset(par[ptype][j]);
                  }
               }
            }
         }
      }
      if ( ok == FALSE )
      {
         fprintf(stderr,
            "\nERROR in complm: problem near line %d\n %s\n\n",
            nline,line);
         allok = FALSE;
      }
      if (distrn[p] > 0) ++p ;
      npfs = p ;
   }
} /* inperf */
/***************************************/

next()
/*
     this picks the next continuous string of non-blank integers
     from 'line', starting at 'start'.

     if an asterisk is read, the data is assumed to continue onto
     the next line.

  input -
     line - an image of the current line being scanned.
     start - the start of the scan.

  output -
     line - an image of the current line being scanned.
     start - the start of the next non-blank string in line.
     string - a copy of the first 6 characters of the next
              non-blank string
     length - the length of the string.

     called by inperf, inname, inells, injts, inlims, parset
     calls llength.
*/
{
   int j,k;
   int llength() ;
   char astk = '*';
   char tab = '	';

   length = 0;

   for (  j = 0 ; j < BMAX ; ++ j )
      string[j] = null ;
/*
     get a new line if required-
*/
   if ((start < lline) && (start > 0)) goto lab17 ;

lab10: start = 0 ;
   if (gets(line) == NULL)
   {
      fprintf(stderr,"\nERROR in complm: unexpected end of file\n");
      fprintf(stderr,"missing STOP command?\n");
      exit(1);
   }
   ++nline ;
   lline = llength();
/*
     find start of next string-
*/
lab17:
   for ( j = start ; j < lline ; ++ j )
   {
      if (line[j] == astk) goto lab10 ;
      if (line[j] == blank) goto lab1 ;
      if (line[j] == tab) goto lab1 ;
      if (line[j] == null) goto lab1 ;
      if (line[j] == '.') goto lab3;
      if ((line[j] == '+') || (line[j] == '-')) goto lab3;
      if ((line[j] >= '0') && (line[j] <= '9')) goto lab3;
      if ((line[j] >= 'a') && (line[j] <= 'z')) goto lab3;
      if ((line[j] >= 'A') && (line[j] <= 'Z')) goto lab3;
      fprintf(stderr,
         "\nERROR in complm: funny character '%c', ascii %d\n",
         line[j],line[j]);
      fprintf(stderr,"near line %d at position %d\n",nline,j);
      fprintf(stderr,"%s\n",line);
      exit(1);
lab1: ;
   }
/*
     rest of line empty, so look at next one-
*/
   j = 0;
   goto lab10 ;
/*
     copy up to the characters of the string,
     then move start to next blank-
*/
lab3:
   for ( start = j ; start < lline ; ++start )
   {
      if (line[start] == '\n') goto lab8 ;
      if (line[start] == blank) goto lab8 ;
      if (line[start] == tab) goto lab8 ;
      if (line[start] == null) goto lab8 ;
      if (line[start] == '.') goto lab5;
      if ((line[start] == '+') || (line[start] == '-')) goto lab5;
      if ((line[start] >= '0') && (line[start] <= '9')) goto lab5;
      if ((line[start] >= 'a') && (line[start] <= 'z')) goto lab5;
      if ((line[start] >= 'A') && (line[start] <= 'Z')) goto lab5;
      fprintf(stderr,"\nERROR in complm: odd character '%c'\n",
         line[start]);
      fprintf(stderr,"near line %d at position %d\n",nline,start);
      fprintf(stderr,"%s\n",line);
      exit(1);
lab5:
      string[length] = line[start] ;
      ++length ;
   }
   start = -1 ;

lab8:;
} /* next */
/***************************************/

int llength()
/*
   find length of line

   called by next.
*/
{
   int j,sp;

   sp = 0;
   for ( j = 0; line[j] != null; ++j);
   {
      if (line[j] != blank) sp = j;
   }
   return(sp);
} /* llength */
/*******************************************/

int match(names,nnames,lengths)
   int nnames;
   char names[EMAX][BMAX] ;
   int lengths[EMAX];
/*
     find which of 'names' fits 'string'.

     input
   string - array of a1 characters to be matched.
   nnames - number of names actually stored in array names.
   names - list of possible strings for which to search.
   lengths - lengths of each of the existing names
   length - length of 'string'

     output
   which of the names that string matches, -1 if none.

     called by inperf, innames, inells, injts, inlims,
               parset, addnam
*/
{
   int j,k ;
   int found;
   int no;
   char sp = null;

   no = -1 ;
   for (k = 0; k <= nnames; ++k)
   {
      if (debug <= 0)
      {
         fprintf(stderr,"matcha %d %s ",k,string);
         for (j = 0; j < length; ++j)
         {
            fprintf(stderr,"%c",names[k][j]);
         }
         fprintf(stderr,"\n");
      }
      found = TRUE;
      if ((lengths[k] == 0) || (lengths[k] == length))
      {
         for (j = 0; j < length; ++j)
         {
            if (string[j] != names[k][j]) found = FALSE;
         }
         if (found == TRUE)
         {
            no = k ;
            break;
         }
      }
   }
   if (debug <= 0)
      fprintf(stderr,"matchb %d %s %d %s %d %d %d %d\n",
         nnames,string,length,names[0],lengths[0],no,ok,TRUE);
   return(no);
} /* match */
/***************************************/

addnam(nnames,names,isvar,lengths)
   int *nnames ;
   int isvar ;
   char names[EMAX][BMAX] ;
   int lengths[EMAX];
/*
     add a name to a list of names.

     called by inperf, innames, inells, injts, parset
     calls  match
*/
{
   int match();
   int k,no ;

   if (debug <= 0) fprintf(stderr,"addnama %d %s %d %d\n",
      *nnames,string,isvar,TRUE);
/*
     see if name already exists-
*/
   no = match(names,*nnames,lengths);
   if (no >= 0)
   {
      fprintf(stderr,"string  %s confusable with ",string);
      for (k = 0; names[no][k] != null; ++k)
         fprintf(stderr,"%c",names[no][k]);
      fprintf(stderr,"\n");
   }
   if (isvar == FALSE)
/*
     non-variables must first check variable list-
*/
   {
      no = match(varnam,nvars,varlen) ;
      if (no > 0)
      {
         fprintf(stderr,
            "name  %s  confusable with variable ",string);
         for ( k = 0; varnam[no][k] != null ; ++ k)
            fprintf(stderr,"%c",varnam[no][k]);
         fprintf(stderr,"\n");
      }
   }
   else
/*
     variables must check all name lists-
*/
   {
      no = match(fignam,nfigs,figlen) ;
      if (no > 0)
      {
         fprintf(stderr,"variable  %s  confusable with figure ",
            string);
         for ( k = 0; fignam[no][k] != null; ++ k)
            fprintf(stderr,"%c",fignam[no][k]);
         fprintf(stderr,"\n");
      }
      no = match(ellnam,nels,ellen) ;
      if (no > 0)
      {
         fprintf(stderr,"variable  %s  confusable with ellipsoid ",
            string);
         for ( k = 0; ellnam[no][k] != null; ++ k)
            fprintf(stderr,"%c",ellnam[no][k]);
         fprintf(stderr,"\n");
      }
      no = match(jntnam,njts,jntlen) ;
      if (no > 0)
      {
         fprintf(stderr,"variable  %s  confusable with joint ",
            string);
         for ( k = 0; jntnam[no][k] != null; ++ k)
            fprintf(stderr,"%c",jntnam[no][k]);
         fprintf(stderr,"\n");
      }
      no = match(subnam,nsubs,sublen) ;
      if (no > 0)
      {
         fprintf(stderr,"variable  %s  confusable with subroutine ",
            string);
         for ( k = 0; subnam[no][k] != null; ++ k)
            fprintf(stderr,"%c",subnam[no][k]);
         fprintf(stderr,"\n");
      }
      no = match(filnam,nfiles,fillen) ;
      if (no > 0)
      {
         fprintf(stderr,"variable  %s  confusable with file name ",
            string);
         for ( k = 0; filnam[no][k] != null; ++ k)
            fprintf(stderr,"%c",filnam[no][k]);
         fprintf(stderr,"\n");
      }
   }
/*
     add name to list-
*/
   ++*nnames ;
   if (debug <= 0)
      fprintf(stderr,"addnamb %d %s %d %s %d\n",
         *nnames,string,length,names[0],lengths[0]);
   if (*nnames > EMAX)
   {
      fprintf(stderr,"%s makes more than max of %d names\n",
         string,EMAX);
      ok = FALSE ;
   }
   else
   {
      for (  k = 0 ; k < length ; ++ k )
         names[*nnames][k] = string[k] ;
      for ( k = length ; k < BMAX; ++ k )
         names[*nnames][k] = null;
      lengths[*nnames] = length;
   }
} /* addnam */
/***************************************/

int getint()
/*
     find value of positive integer which is encoded as 'length'
     characters in array 'string', and put its value into 'k'.
     set 'pok' false if string not a positive integer.

     called by parset, inname.
*/
{
   int j,k,m,this ;
   char plus = '+';

   if (length <= 0)
   {
      k = 0 ;
      pok = FALSE;
   }
   else
   {
      pok = TRUE;
      k = 0;
      for (j = 0; j < length; ++j)
      {
         if (string[j] != plus)
         {
            this = -1 ;
            for (m = 0; m < 10; ++m)
               if (string[j] == dig[m]) this = m ;

            if (this < 0)
            {
                pok = FALSE;
                goto out;
            }
            k = 10*k+this ;
         }
      }
   }
out:;
   if (debug <= 0)
      fprintf(stderr,"getintb %s %d %d %d %d\n",
         string,length,k,pok,TRUE);
   return(k);
} /* getint */
/***************************************/

int inells()
/*
     read in next ellipsoid and its axis lengths.

     called by inperf, injts
     calls  next, match, addnam, value
*/
{
   int el,k ;
   int match();
   float value();

   if (debug <= 0) fprintf(stderr,"inellsa %d\n",nels);
   next();
   el = match(ellnam,nels,ellen) ;
   if (el >= 0) goto lab3 ;
   addnam(&nels,ellnam,0,ellen);
   el = nels ;

lab3:
   for (  k = 0 ; k < 3 ; ++ k )
   {
      next();
      semiax[k] = value();
      if ( ok == FALSE ) goto lab11 ;
   }

   goto rtrn ;
/*
     snag-
*/
lab11: fprintf(stderr,"ellipsoid snag with  %s\n",string);
   ok = FALSE ;
rtrn: return(el);
} /* inells */
/***************************************/

injts()
/*
     read in the next joint, the ellipsoids it connects, and the
     position of the joint relative to each ellipsoid centre.

     called by inperf
     calls  next, addnam, inells
*/
{
   int el,k,e ;
   char klet = 'k';
   char nlet = 'n';
   char elet = 'e';

   if (debug <= 0) fprintf(stderr,"injtsa %d\n",njts);
   next();
   addnam(&njts,jntnam,0,jntlen);
   if ( ok == FALSE ) goto lab4 ;
/*
     is it a knee -
*/
   knee[njts] = FALSE;
   for (  k = 0 ; k < (length-1) ; ++ k )
   {
      if ((string[k] == klet)
       && (string[k+1] == nlet)
       && (string[k+2] == elet)) knee[njts] = TRUE;
   }
/*
  do the two ellipsoids
*/
   for (  e = 0 ; e <= 1 ; ++ e )
   {
      el = inells();
      if ( ok == FALSE ) goto lab5 ;

      dcon[njts][e][0] = semiax[0] ;
      dcon[njts][e][1] = semiax[1] ;
      dcon[njts][e][2] = semiax[2] ;
      coel[njts][e] = el ;
   }
   goto rtrn ;
/*
     snags-
*/
lab5: fprintf(stderr,"joint snag with %s \n",string);
   njts = njts-1 ;
   goto rtrn ;

lab4: fprintf(stderr,"more joints than max %d\n",EMAX );
   ok = FALSE ;
rtrn:
   if (debug <= 0) fprintf(stderr,"injtsb %d\n",njts);
} /* injnts */
/***************************************/

inlims()
/*
     read in limits for a joint.

     called by main.
     calls     next, match, value.

*/
{
   int k,m,n;
   int match();
   float value();

   if (debug <= 0) fprintf(stderr,"inlimsa\n");
   next();
   n = match(jntnam,njts,jntlen);
   if (n < 0)
   {
      fprintf(stderr,"limits given for nonexistent joint: %s\n",
         string);
      exit(1);
   }
   for (k = 0; k < 3; ++k)
   {
      for (m = 0; m < 2; ++m)
      {
         next();
         lim[n][k][m] = value();
      }
   }
} /* inlims */
/***************************************/

inname(nnames,names,isvar,lengths)
   int *nnames;
   int lengths[EMAX];
   char names[EMAX][6] ;
   int isvar ;
/*
     read in a number of names and then the names themselves.

     called by inperf
     calls  next, getint, match, addnam
*/
{
   int e,ne,no ;
   int match();
   int getint();

   ok = TRUE ;
   pok = TRUE;
/*
     get number of names in list
*/
   next();
   ne = getint();
   if (debug <= 0)
      fprintf(stderr,"innamesa %s %d %d %s %d %d\n",
         string,ne,*nnames,names[0],isvar,lengths[0]);
   if ( pok == FALSE ) goto lab6 ;
/*
     get names in list
*/
   if (ne <= 0) goto rtrn ;
   for (  e = 0 ; e < ne ; ++ e )
   {
      next();
      if (length < 1) goto rtrn ;
      no = match(names,*nnames,lengths) ;
      if (no > 0) goto lab1 ;
      addnam(nnames,names,isvar,lengths);
lab1: ;
   }
   goto rtrn ;

lab6: fprintf(stderr,"problem- number of names not stated on\n");
   fprintf(stderr,"%s\n",line);
rtrn:;
} /* inname */
/***************************************/

join()
/*
   this works out the positions of the centres of each ellipsoid
   'cen' and the joints 'jnt', using the data 'dcon'

   called by main
*/
{
      int e,ecount,new,old,newel,oldel,j,k;
      int jfound[EMAX];
      int efound[EMAX];
      int elist[EMAX];

      if (debug <= 0) fprintf(stderr,"joina %d %d\n",nels,njts);
/*
     clear found and put all ellipsoids at origin -
*/

      for (  e = 0 ; e < nels ; ++ e )
      {
         cen[e][0] = 0; cen[e][1] = 0; cen[e][2] = 0;
         jfound[e] = FALSE ;
         efound[e] = FALSE ;
      }
      if (njts >= 0)
      {
         ecount=0 ;
         elist[ecount]=0 ;
         efound[ecount] = TRUE;
/*
     run through the ellipsoids of current figure -
*/
lab2:    for (  e = ecount ; e <= ecount ;  e ++ )
         {

/*   run through joints, adding to figure's ellipsoids - */

            for (  j = 0 ; j <= njts ; ++ j )
            {
               if ((jfound[j] == FALSE)
                   && ((coel[j][0] == elist[e])
                     ||(coel[j][1] == elist[e])))
               {

/*   found a joint- */

                  oldel = elist[e] ;
                  if (coel[j][1] == oldel) new = 0 ;
                  if (coel[j][0] == oldel) new = 1 ;
                  jfound[j] = TRUE ;
                  old = 1-new ;
                  newel = coel[j][new] ;

/*   check for legality- */

                  for (  k = 0 ; k < ecount ; ++ k )
                  {
                     if (newel == elist[k])
                     {
                        fprintf(stderr,
   "cyclic joint structure - perhaps delete one of the joints \n");
                        fprintf(stderr,
                           " %d %d %d %d %d %d %d %d %d %d\n",
                        ecount,nels,njts,e,j,new,old,k,oldel,newel);
                        goto lab10 ;
                     }
                  }
                  ecount = ecount+1 ;
                  elist[ecount] = newel ;
                  efound[newel] = TRUE;

/*   locate the new joint and ellipsoid- */
   
                  for (  k = 0 ; k < 3 ; ++ k )
                  {
                      jnt[j][k] = cen[oldel][k]+dcon[j][old][k] ;
                      cen[newel][k] = jnt[j][k]-dcon[j][new][k] ;
                  }
                  if (debug <= 0)
                  {
                     fprintf(stderr,"joinb %d %f %f %f\n",
                     oldel,cen[oldel][0],cen[oldel][1],cen[oldel][2]);
                     fprintf(stderr,"      %d %f %f %f\n",
                     j,jnt[j][0],jnt[j][1],jnt[j][2]);
                     fprintf(stderr,"      %d %f %f %f\n",
                     newel,cen[newel][0],cen[newel][1],cen[newel][2]);
                   }
                }
            }
        }

/* locate an ellipsoid in some other figure - */

        for (newel = 0; newel < nels; ++ newel)
        {
            if (efound[newel] == FALSE)
            {
               ++ ecount;
               elist[ecount] = newel;
               efound[newel] = TRUE;
               goto lab2;
            }
        }
     }
lab10: ;
} /* join */
/*******************************************/

int parset(contrl)
int contrl;
/*
     decode the parameters of the jth action

     called by inperf
     calls  next, getint, value, valadd, match, addnam
*/
{
   int k,m;
   int nax = 2;
   int attach = 8;
   int detach = 9;
   float v ;
   float value();
   int getint();
   int match();

   k = 0 ;
   if (contrl == 0) goto lab11 ;
   next();
/*
     pick an integer constant-
*/
   if ((contrl != 1)&&(contrl != 8)) goto lab1 ;
   k = getint();
   if (pok == TRUE) goto lab11 ;
/*
     pick a float constant-
*/
   pok =  TRUE ;
   v = value();
   if ( pok == FALSE ) goto lab1 ;
   k = valadd(v) ;
   if ( pok == FALSE ) goto lab1 ;
   k = -k ;
   goto lab11 ;
/*
     pick an axis-
*/
lab1: if ((contrl != 5)&&(contrl != 8)) goto lab2 ;
   k = match(axnam,nax,axlen) ;
   if (k >= 0) goto lab11 ;
/*
     try for a variable-
*/
lab2: k = match(varnam,nvars,varlen) ;
   if (k < 0) goto lab3 ;
   usevar[k] = 1 ;
   if (contrl != 7) k = k-EMAX+1 ;
   goto lab11 ;
/*
     pick an ellipsoid-
*/
lab3: if ((contrl != 2)&&(contrl != 8)) goto lab4 ;
   k = match(ellnam,nels,ellen) ;
   if (k < 0) goto lab4 ;
   goto lab11 ;
/*
     pick a joint-
*/
lab4: if ((contrl != 3)&&(contrl != 8)) goto lab5 ;
   k = match(jntnam,njts,jntlen) ;
   if (k >= 0) goto lab11 ;
   if ((k < 0)&&(ptype != attach)) goto lab5 ;
   addnam(&njts,jntnam,0,jntlen);
   k = njts ;
   goto lab11 ;
/*
     pick a figure-
*/
lab5: if ((contrl != 4)&&(contrl != 8)) goto lab7 ;
   k = match(fignam,nfigs,figlen) ;
   if (ptype == detach) goto lab6 ;
   if (k < 0) goto lab7 ;
   goto lab11 ;
/*
     action detach- accept any figure but "all"-
*/
lab6: if (k == 0) goto lab7 ;
   if (k > 0) goto lab11 ;
   addnam(&nfigs,fignam,0,figlen);
   k = nfigs ;
   goto lab11 ;
/*
     pick a subroutine call-
*/
lab7: if ((contrl != 6)&&(contrl != 8)) goto lab8 ;
   k = match(subnam,nsubs,sublen) ;
   if (k <= 0)
   {
      addnam(&nsubs,subnam,0,sublen);
      k = nsubs ;
   }
   called[k] = TRUE;
   goto lab11 ;
/*
     pick a file name-
*/
lab8: if ((contrl != 9)&&(contrl != 8)) goto lab10 ;
   k = match(filnam,nfiles,fillen) ;
   if (k > 0) goto lab11 ;
   addnam(&nfiles,filnam,0,fillen);
   k = nfiles ;
   goto lab11 ;
/*
     snag-
*/
lab10: {
          fprintf(stderr," snag with  ");
          for (m = 0; m < 10; ++m)
             fprintf(stderr,"%c",expect[contrl][m]);
          fprintf(stderr," %s\n",string);
       }
   ok = FALSE ;

lab11:
   return(k) ;
} /* parset */
/***************************************/

prinvl()
/*
     print out summary of values, variables, actions, subroutines

     called by main.
*/
{
   int j,p,ptype ;

   fprintf(stderr,"\nactions   \n");

   for (  p = 0 ; p <= npfs ; ++ p )
   {
      ptype = type[p] ;
      fprintf(stderr,"%d %d %d %d %d %d %d %d %d %d %d ",
         p,frstrt[p],frstop[p],ptype,distrn[p],
         pf[p][0],pf[p][1],pf[p][2],pf[p][3],pf[p][4],pf[p][5]);
      for (j = 0; j < 6; ++ j) fprintf(stderr,"%c",keynam[ptype][j]);
      fprintf(stderr,"\n");
   }

   fprintf(stderr,"\nvariables\n");
   for (  p = 0 ; p <= nvars ; ++ p )
   {
      j = EMAX-p-1 ;
      fprintf(stderr,"%d %d %f ", p,j,val[j] );
      for ( j = 0 ; j < 6; ++ j) fprintf(stderr,"%c",varnam[p][j]);
      fprintf(stderr,"\n");
   }

   fprintf(stderr,"\nvalues\n");
   for (  p = 0 ; p <= nvals ; ++ p )
      fprintf(stderr,"%d %f\n",p,val[p] );

   fprintf(stderr,"\nsubroutines\n");
   for (  p = 0 ; p <= nsubs ; ++ p )
   {
      fprintf(stderr,"%d %d %d ",p,subact[p][0],subact[p][1] );
      for (j = 0; j < 6; ++ j) fprintf(stderr,"%c",subnam[p][j]);
      fprintf(stderr,"\n");
   }
} /* prinvl */
/***************************************/

prname(names,no)
char names[][BMAX];
int no;
/*
   print the names in array names, each on a separate line.

   called by store4
*/
{
   int j,k;

   for ( k = 0; k <= no; ++k)
   {
      printf("%d ",k);
      for ( j = 0; names[k][j] != null; ++j)
         printf("%c",names[k][j]);
      printf("\n");
   }
} /* prname */
/******************************************/

store4()
/*
     write out the numerical specifications of the actions
     to be performed.

     called by main
*/
{
   int new;
   int j,k,m ;
   int line;
   int subfirst;

   new = TRUE;
   subfirst = TRUE;
/*
     check for snags-
*/
   for (  j = 0 ; j <= nels ; ++ j )
   {
      if (ellfig[j] >= 0) goto lab7 ;
      fprintf(stderr,"/nERROR in complm: ellipsoid  ");
      for (k = 0 ; k < ellen[j]; ++ k)
         fprintf(stderr,"%c",ellnam[j][k]);
      fprintf(stderr," defined but not in a figure \n");
      allok = FALSE ;
lab7: if (ax[j][0]*ax[j][1]*ax[j][2]  >  0.0) goto lab1 ;
      allok = FALSE ;
      fprintf(stderr,"\nERROR in complm: ellipsoid  ");
      for (k = 0 ; k < ellen[j]; ++ k) fprintf(stderr,"%c",ellnam[j][k]);
      fprintf(stderr," not dimensioned \n");
lab1: ;
   }

   for (  j = 1 ; j <= nsubs ; ++ j )
   {
      if ((debug < 3) && (allok == TRUE) && (called[j] == FALSE))
      {
	 if (subfirst == TRUE)
	 {
	    subfirst = FALSE;
	    new = FALSE;
	    fprintf(stderr,
	    "\nNote: undefined variables are assumed to be subroutines\n");
	 }
         fprintf(stderr,"subroutine ");
         for (k = 0 ; k < sublen[j]; ++ k)
            fprintf(stderr,"%c",subnam[j][k]);
         fprintf(stderr," apparently not called \n");
      }
      if ((debug < 3) && (defined[j] == FALSE))
      {
	 if (new == TRUE) fprintf(stderr,"\n");
	 new = FALSE;
         fprintf(stderr,"subroutine ");
         for (k = 0 ; k < sublen[j]; ++ k)
            fprintf(stderr,"%c",subnam[j][k]);
         fprintf(stderr," apparently not defined \n");
      }
   }

   if (vstrt >= vstop) goto lab12 ;
   for (  j = 0 ; j <= subact[0][1] ;  j  ++ )
   {
      if ((frstop[j] < 0) || (vstrt < frstop[j])) goto lab6 ;
   }
   goto lab12 ;

lab6: if ((nvals+nvars) > EMAX) goto lab13 ;
   if (nvars <= 0) goto lab9 ;
   for (  j = 0 ; j <= nvars ; ++ j )
      if ((debug < 3) && (usevar[j] == 0))
      {
	 if (new == TRUE) fprintf(stderr,"\n");
	 new = FALSE;
         fprintf(stderr,"variable ");
         for (k = 0 ; k < varlen[j]; ++ k)
            fprintf(stderr,"%c",varnam[j][k]);
         fprintf(stderr," not used\n");
      }

lab9: if ( allok == FALSE ) goto rtrn ;

   printf("%6d %6d %6d %6d %6d %6d %6d %6d %6d\n",
      debug+1,njts+1,nels+1,fast,slow,npfs+1,nvals+1,nvars+1,nfigs+1);
   printf("%6d %6d %6d %6d %6d\n",
      NKEYS+1,nsubs+1,vstrt,vstop,nfiles+1);

   for (j = 0; j <= nsubs; ++j )
      printf("%6d %6d\n",subact[j][0],subact[j][1]);

   for (j = 0; j <= npfs; ++ j)
      printf("%6d %6d %6d %6d %6d %6d %6d %6d %6d %6d %6d\n",
         type[j],frstrt[j],frstop[j],distrn[j],
         pf[j][0],pf[j][1],pf[j][2],pf[j][3],pf[j][4],pf[j][5],cline[j]);

   for ( j = 0; j <= njts ; ++j)
   {
      printf("%6d %6d %f %f %f ",
         coel[j][0],coel[j][1],jnt[j][0],jnt[j][1],jnt[j][2]);
      for (k = 0; k < 3; ++k)
         for (m = 0; m < 2; ++m)
            printf("%f ",lim[j][k][m]);
      if (knee[j] == TRUE)
         printf("t\n"); else printf("f\n");
   }

   for ( j = 0; j <= nfigs; ++j)
   {
      printf("%6d ",figell[j]) ;
      if (( j%11 == 0) && ( j > 0 )) printf("\n");
   }
   if ( nfigs%11 != 0) printf("\n");

   for (k = 0; k <= NKEYS; ++k)
       printf("%d %d %d %d %d %d\n",
           code[k][0],code[k][1],code[k][2],code[k][3],code[k][4],code[k][5]) ;

   for ( j = 0; j <= nvals ; ++j)
   {
      printf("%f ",val[j]);
      line = FALSE;
      if ( j%5 == 4 )
      {
         printf("\n");
         line = TRUE;
      }
   }
   if (line == FALSE) printf("\n");

   for ( j = 0; j <= nels ; ++j)
      printf("%f %f %f %f %f %f\n",
          ax[j][0],ax[j][1],ax[j][2],cen[j][0],cen[j][1],cen[j][2]);

   for ( j = 0; j <= nfiles ; ++j)
   {
      printf("%d ",j);
      for (k = 0; filnam[j][k] != null; ++k)
         printf("%c",filnam[j][k]) ;
      printf("\n");
   }
    for (k = 0; k <= NKEYS; ++k)
        printf("%d %d %d %d %d %d\n",
           par[k][0],par[k][1],par[k][2],par[k][3],par[k][4],par[k][5]) ;
/*
     put names on end of file-
*/
      prname (keynam,NKEYS-1) ;
      prname (ellnam,nels) ;
      prname (jntnam,njts) ;
      prname (subnam,nsubs) ;
      prname (varnam,nvars) ;
      prname (fignam,nfigs) ;
/* */
      goto rtrn ;
/* */
/*   snags-*/
/* */
lab12: fprintf(stderr,
       "\nERROR in complm: view %d %d - produces no frames\n",
       vstrt,vstop );
       goto rtrn ;
/* */
lab13: fprintf(stderr,
       "\nERROR in complm:  %d  non-integer values + %d variables\n",
          nvals,nvars);
       fprintf(stderr," give more than max of %d \n",EMAX);
/* */
rtrn:;
} /* store4 */
/***************************************/

int valadd(v)
   float v;
/*
     if 'v' is not in array 'val', then put it at the end.
     wherever it is, put its index into 'j'.

     called by parset
*/
{
   int j ;

   for (  j = 1 ; j <= nvals ; ++ j )
      if (val[j] == v) goto lab2 ;

   nvals = nvals+1 ;
   if (nvals > EMAX) goto lab10 ;
   j = nvals ;
   val[j] = v ;

lab2: ;
   goto rtrn ;
/*
     snag-
*/
lab10: fprintf(stderr,
          "\nERROR in complm: no. of constants %d > max %d\n",
          nvals,EMAX );
   ok = FALSE ;

rtrn: return(j);
} /* valadd */
/***************************************/

float value()
/*
     find the value of the number which is encoded as
     characters in array 'string' and put it into 'v'.
     set ok false if string is not a number.

     called by inperf, inells, injts, parset
*/
{
   float v,nsign,expon ;
   int k,frac,d ;
   char point = '.';
   char minus = '-';
   char plus = '+';

   v = 0.0 ;
   nsign = 1.0 ;
   expon = 1.0 ;
   frac = FALSE ;
   if ((length < 0) || (length > BMAX)) goto lab4;

   for (  k = 0 ; k < length ; ++ k )
   {
/*
     if a decimal point encountered, start decimal place counter
*/
      if (string[k] == point) frac = TRUE ;
      if (string[k] == point) goto lab3 ;

      if (string[k] == plus) goto lab3 ;
      if (string[k] == minus) nsign = -nsign ;
      if (string[k] == minus) goto lab3 ;

      for (  d = 0 ; d < 10 ; ++ d )
         if (string[k] == dig[d]) goto lab5 ;

      goto lab1 ;

lab5: v = v*10.0+(float)d ;
      if (frac == TRUE) expon = expon/10.0 ;
lab3: ;
   }

   v = v*expon*nsign ;
   goto rtrn ;
/*
     not a number-
*/
lab1: pok = FALSE ;
   goto rtrn ;

lab4: pok = FALSE ;

rtrn: return(v);
} /* value */
