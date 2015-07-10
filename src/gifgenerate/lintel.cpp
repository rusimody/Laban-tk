/* lintel version 84
 
   This set of routines reads a specifications of actions 
   to be performed in a LED .lbn file in Labanotation, 
   or a NUDES .n file, and performs them
   producing an interactive 3D animated display.

   If there are two or more staves in labanotation,
   it assumes   man on the left, woman on the right

   written in C++ for 
       Microsoft Visual Studio .NET 2003, Opengl, and Glut32.

  		and optionally	lintel.ini

    7 Nov 2008 lintel084- added 'limit' to declaration comments
   27 Nov 2007 lintel084- oriented, laction, lsethold, ldochest
   14 Nov 2007 lintel083- chest twist: laction, ldolimb
   14 Nov 2007 lintel082- lbn_figures: option of 1 stave
    5 May 2007 lintel081- angsep, dotouch, surf,
    3 Apr 2007 lintel080- fix middle relaxed arms, donum
    6 Dec 2006 lintel079- ptitle, reading lintel.ini
    4 Dec 2006 lintel078- lintel066 + lintel077, lsetcoords
   16 Sep 2006 lintel077- dotouch seeks min sqr(surf())
   19 Aug 2006 lintel076- toe taps use dodrag
   14 Aug 2006 lintel075- binary search for dodrag
   13 Aug 2006 lintel074- forbid, allow
    8 Aug 2006 lintel073- cutting
   21 Jun 2006 lintel069- lleggesture
    1 Jun 2006 lintel068- input frame rate, beats per minute 
                          bpm,fps,ppb,initialise,lgetfiles,
                          doub60,fac,FACTOR
   15 May 2006 lintel066- default .lbn,
                          staves 1 2, track, spot turn
   12 May 2006 lintel065- allow non-alphanumerics in names
    9 May 2006 lintel064- fix arm angles arlx arlx
    8 May 2006 lintel063- fix lbows
    7 May 2006 lintel062- fix lselectfig
    2 May 2006 lintel061- fix semishadow hold,
   21 Apr 2006 lintel060- accommodating chest directions
   19 Apr 2006 lintel059- fixing feet angles
   18 Apr 2006 lintel058- adding ldoposn, ldokeep
   15 Apr 2006 lintel057- using only lintel.n
   14 Mar 2006 lintel056- fix lleggesture,
   12 Mar 2006 lintel055- fix action (ground: t18 frac -> prop)
   19 Jan 2006 lintel054- fix globals, dodrag, doground, elow,
	                  inperf, help, checkeys, image,
   14 Jan 2006 lintel054- fix lleggesture, ldostep,
   11 Jan 2006 lintel053- fix lselectfig, lgetfiles, lleggesture
    7 Jan 2006 lintel052- fix lspotturn, laction, lsethold, hold constants, face indicators
    5 Jan 2006 lintel051- cut forward, back, settle, lside, rename lleggesture
   26 Dec 2005 lintel050- fix lforward, ssend, ssmall, radten
   23 Dec 2005 lintel049- fix loverlap, ldopivot, lbent, ldoarms, remove lhaspivot, diagnostics
   21 Dec 2005 lintel048- fix laction, lback, ldohold, fclh
   20 Dec 2005 lintel047- fix back step, diagonal aerials
    5 Dec 2005 lintel046- fix back step
    4 Dec 2005 lintel045- fix overlapping facing symbols
    4 Dec 2005 lintel044- fix kept,keptf
   16 Nov 2005 lintel043- fix closed position
   11 Nov 2005 lintel042- fix promenade position, bent arms
    8 Nov 2005 lintel041- fix rotary chasses
    8 Nov 2005 lintel040- clean up
    5 Nov 2005 lintel039- fix spot turns in Charmaine
    1 Nov 2005 lintel038- fix closed and shadow holds
    1 Nov 2005 lintel037- fix associating pins with rotation signs
   31 Oct 2005 lintel036- include shadow hold, fix back step
    3 Oct 2005 lintel035- fix closed and semishadow holds
    3 Oct 2005 lintel034- fix starting positions man and woman
    3 Oct 2005 lintel033- syncronise man and woman
   30 Sep 2005 lintel032- request new file in event of an error
   28 Sep 2005 lintel031- fix subroutine counting bug
   27 Sep 2005 lintel030- fix counting bugs (off by 1)
   26 Sep 2005 lintel029- rewrote setels
   21 Sep 2005 lintel027- able to run .n files also
   17 Sep 2005 lintel026- drag limited to high ankle position
    9 Sep 2005 lintel025- use Lintel.figs.n and Lintel.subs.n
   13 Aug 2005 lintel024- import ballroom hold from rev18.n   
    8 Aug 2005 lintel023- set holds
    7 Aug 2005 lintel022- set starting spacing
    1 Aug 2005 lintel021- set starting positions
   31 Jul 2005 lintel020- animate both man and woman NBG
   29 Jul 2005 lintel019- move calls to setman/setwoman
    6 Jul 2005 lintel018- fix undefined variables t,k,fname
    5 Jul 2005 lintel017- fix leg-gesture/turn combination
    4 Jul 2005 lintel016- tidy up 
    2 Jul 2005 lintel015- fix Charmaine spot turn
    1 Jul 2005 lintel014- NBG
   30 Jun 2005 lintel013- fix Boston 2 Step women end facing snag
   29 Jun 2005 lintel012- fix La Bomba arms snag
   26 Jun 2005 lintel011- accommodating XX (bent) sign
   15 Jun 2005 lintel010- fix 'touch' problem in 'angsep'
   14 Jun 2005 lintel009- add data file name to window title
   13 Jun 2005 lintel008- use Linter.decs.n and Linter.subs.n
    8 Jun 2005 lintel007- still fixing drag, luci.lbn, bar 25, fr 899
    7 Jun 2005 lintel006- use 'drag' for toe/foot/heel taps, slowed pivots
    6 Jun 2005 lintel005- fix Fred's 'drag' problem in luci.lbn
    5 Jun 2005 lintel004- allow comment lines in .lbn file
    4 Jun 2005 lintel003- display bar numbers
    1 Jun 2005 lintel002- use only linter.subs.n and linter.decs.n
    5 May 2005 lintel001- check number of staves
    4 May 2005 drawel45- add linter50 for left/right staves
    3 May 2005 linter  - convert to C++
    2 May 2005 drawel43- delete input summary printout
   26 Apr 2005 drawel42- add compl
   26 Apr 2005 drawel41- add shadows
   25 Apr 2005 complu  - fix view command
   25 Apr 2005 complt  - fix final summary
   24 Apr 2005 drawel40- correct shading
   24 Apr 2005 drawel39- compress z axis
   23 Apr 2005 drawel38- fix place/observe error
   20 Apr 2005 compls  - change nels to ne
   20 Apr 2005 drawel35- write errors to standard output
    8 Apr 2005 drawel35- debug view transform
    7 Apr 2005 drawel34- incorporate movement simulation (prfrm)
    5 Apr 2005 drawel33- incorporate view transform (view)
    4 Apr 2005 drawel32- scale about screen centre
    3 Apr 2005 drawel31- input root of datafile name
   28 Mar 2005 drawel30- improve vertical illumination
   28 Mar 2005 drawel29- improve file name input 
   27 Mar 2005 drawel28- file name input
   27 Mar 2005 drawel27- echo commands
   27 Mar 2005 drawel26- slow pause, added 'v','w'
   26 Mar 2005 drawel25- fix shading
   26 Mar 2005 drawel24- fix visibility of frame numbers
   22 Mar 2005 drawel23- fix x and y rotations
   22 Mar 2005 drawel  - fix z rotation and help
   22 Mar 2005 drawel  - show frame numbers
   22 Mar 2005 drawel  - fix inter-frame delay
   22 Mar 2005 drawel  - fix pausing on first and last frames
   22 Mar 2005 drawel  - add single frame forward and back
   21 Mar 2005 drawel  - add pause routine
   19 Mar 2005 drawel  - separate setels routine.
   13 Mar 2005 drawel  - translate to C++ for .NET
    3 Apr 2005 complr  - list statistics at end
    1 Apr 2005 complq  - read nudes filename root
   29 Mar 2005 complp  - rewritten in C++ for .NET 2003
    3 Jul 2004 linter  - restore upper case figure name initials
   11 Oct 2003 linter  - ensure fend > fstart
   10 Oct 2003 linter  - align output spacing
    7 Oct 2003 linter  - use 'woman', 'man' variables
   12 Sep 2003 prfrm   - error message contains frame number
   10 Sep 2003 prfrm   - touch using nested search
    7 Sep 2003 compl   - avoid expanding the 0-1 frame period with -e option
   24 Jul 2003 prfrm   - extend drag search angle from 10 to 20 degrees
   24 Jul 2003 linter  - use more drag on closing ankle
   10 Jul 2003 linter  - use drag on closing ankle
   16 Jun 2003 prfrm   - improve drag
    6 Jun 2003 prfrm   - debug drag
    6 Jun 2003 linter  - accommodate close sign for standing foot
   29 May 2003 linter  - fixing leg compression
    1 Feb 2003 linter  - optional 1 second pause at start and end
   29 Jan 2003 linter  - use 'started' to fix initial orientation
   18 Jan 2003 linter  - fix initial orientation
   16 Jan 2003 linter  - still fixing arms
   10 Jan 2003 linter  - accommodating menu abbreviations
   10 Jan 2003 drawel12- fix batch flag descriptions
   30 Nov 2002 linter  - fix  arms
    8 Nov 2002 linter  - fix rise and fall again
    2 Nov 2002 linter  - note bars
   30 Oct 2002 linter  - fix misinterpretation of zero bar line
   19 Oct 2002 linter  - fix misinterpretation of arms once more
   27 Sep 2002 linter  - fix misinterpretation of arms again
    5 Sep 2002 drawel  - make x rotation inwards
    5 Sep 2002 drawel  - fix single frame bug
    5 Sep 2002 linter  - fix rise and fall
    5 Sep 2002 linter  - fix misinterpretation of arm columns
   29 Aug 2002 linter  - fix misinterpretation of columns
   16 Jan 2002 viewc   - double precision throughout
   10 Jan 2002 linter  - fix close without weight
   22 Nov 2001 drawel  - report when arrays limit animation length
   28 Sep 2001 drawel  - fix shading to after rotation
   23 Sep 2001 drawel  - fix delay routine
   23 Sep 2001 drawel  - delay double buffer swap
   21 Sep 2001 drawel  - fix CreateWindow bug
   15 Aug 2001 drawel  - start with trigonal bipyramids
    1 Aug 2001 drawel  - add variable display slow
   14 Jun 2001 drawel  - fix shading
    7 Jun 2001 drawel  - show frame numbers
   24 May 2001 drawel  - slow down
   24 May 2001 drawel  - try for animation
   15 May 2001 drawel  - trying to get shading right
    3 May 2001 drawel  - get rotations in right order
    2 May 2001 drawel  - enable hidden surface testing
   24 Mar 2001 drawel  - initsphere revised
    7 Mar 2001 drawel  - opengl routine names inserted
   22 Nov 2001 linter  - still trying to point foot in gestures
   22 Nov 2001 linter  - report gestures in output file
    8 Nov 2001 linter  - don't close at end of step
    1 Nov 2001 linter  - fix pointed foot in gestures
    1 Nov 2001 linter  - fix overturning
   12 Oct 2001 linter  - fix stepping on toes
   15 Aug 2001 linter  - fix floor
   14 Feb 2001 linter  - fix closing without weight some more
    7 Feb 2001 linter  - standard output
    7 Feb 2001 linter  - stop calls to routines overlapping
   31 Jan 2001 linter  - get left and right legs sorted out
   31 Jan 2001 linter  - avoid straightening leg closing without weight
   24 Jan 2001 drawel  - interactive and flag options removed for simplicity.
   17 Aug 2000 drawel  - for gl on Viewsonic/Zondata machines.
   12 Nov 1999 linter  - stop pointing toes when stepping diagonally forward
    4 Sep 1998 linter  - comments about step directions added
   28 Aug 1998 linter  - 'leg[]' used for legs
   23 Aug 1998 linter  - 'stt[]' used for legs
   31 Jul 1998 linter  - check next symbol in column
   15 Jul 1998 linter  - add back routine
   23 Apr 1998 drawel  - display slow
   17 Apr 1998 drawel  - t for translate in z, +/- for slow
   13 Apr 1998 linter  - add date, forward and compress routines
   12 Apr 1998 linter  - simplified NUDES variables
   23 Mar 1997 linter  - fix core dump on dor1234 file
   23 Mar 1997 linter  - optional pixels per frame
   23 Mar 1997 compl   - debug information hidden more
   18 Mar 1997 compl   - optional warnings
   13 Mar 1997 linter  - bent arms
   17 Jul 1996 prfrm   - print command to standard error output
    7 Feb 1996 prfrm   - clean up 'dotouch'
    3 Feb 1996 prfrm   - clear floating exceptions
    6 Oct 1996 linter  - relaxed arms
    6 Oct 1996 linter  - optionally use rightmost staff
    2 Oct 1996 linter  - start at specified bar
   25 Sep 1996 linter  - use relaxed knees
   13 Sep 1996 linter  - written (Don Herbison-Evans)
   19 Aug 1994 prfrm   - remove some goto's
   13 Aug 1994 prfrm   - clean up 'perfrm'
   21 Jul 1994 compl   - fixed 'match' bug
   29 Apr 1994 prfrm   - cleaning up 'drag'
   28 Apr 1994 compl   - variable subroutines permitted
   22 Sep 1993 prfrm   - cleaning up after 'detach' fixed up
   10 Sep 1993 drawel  - accommodate joint information
   10 Sep 1993 compl   - documentation improved
   16 Aug 1993 compl   - 'movjnt' added
    2 Aug 1993 viewb   - allow joint information
   12 Mar 1993 compl   - 'abut' added
   11 Mar 1993 compl   - repeat subroutine calls allowed
    4 Mar 1993 compl   - keyword 'all' turned into 'every'
   17 Feb 1993 prfrm   - 'touch' using Buckdale's algorithm
    4 Feb 1993 prfrm   - 'touch' using scanning
   28 Oct 1992 prfrm   - joint limits added
   15 Oct 1992 prfrm   - viewing transformation separated (view)
   12 Jun 1992 compl   - 'drag' added
   17 Apr 1992 prfrm   - 'touch' fixed
   26 Feb 1992 drawel  - written : for Silicon Graphics Iris
   12 Feb 1992 compl   - allow cubic movements
   29 Jul 1991 prfrm   - print variable values nicely
   24 Nov 1988 prfrm   - more ellipsoids accommodated
    7 Apr 1987 compl   - translate to C, 'copy' command deleted
   10 Dec 1986 prfrm   - translate into C for Digital VAX 780
   29 Nov 1986 prfrm   - write figure for Benesh interpreter
   25 Nov 1986 compl   - write a complete figure
   17 Oct 1986 prfrm   - texture for ellipsoids
    7 Oct 1986 compl   - 'texture' statement added
    8 Mar 1986 compl   - 'print' statement added
   21 Jul 1985 compl   - ellipsoids declared on the fly
   22 Jun 1985 prfrm   - 'grofig' scales about an ellipsoid (Peter Gummer)
   14 Jun 1985 prfrm   - 'spinto' added (Peter Gummer)
   15 Apr 1985 prfrm   - 'setels' simplified (Peter Gummer)
   12 Apr 1985 compl   - simplify subroutine 'join' (Peter Gummer)
    3 Apr 1985 compl   - 'world' added, 'refell' for 'spinby','moveby' (Peter Gummer)
    3 Jan 1985 prfrm   - 'attach', 'detach' work properly (Peter Gummer)
   23 May 1984 compl   - change parsing order
    7 May 1984 prfrm   - 'multiply', 'subtract', 'divide', 'balance' added
   22 Dec 1983 compl   - reduce number of constants in val
   14 Dec 1983 compl   - variable frame numbers
   12 Dec 1983 prfrm   - variable frame numbers
   25 Nov 1983 prfrm   - rotations stored as twist about axis
   22 Nov 1983 prfrm   - separate error message file
    2 Nov 1983 compl   - move integer codes 11-19 to 21-29 (Danuta Kucharska)
   15 Oct 1983 compl   - add 'colour' action (Danuta Kucharska)
   15 Oct 1983 compl   - ellipsoid default colour to flesh (Danuta Kucharska)
   16 Aug 1983 compl   - work out range of frames
   19 Apr 1983 prfrm   - insert 'axes', 'link', fix 'detach', 'ground'
   16 Sep 1982 prfrm   - ellipsoid names put in 1st frame
   19 Jul 1982 prfrm   - tolerance put in subroutine rotput
   31 Mar 1982 compl   - 'observe', 'all', 'par' array stored
   26 Mar 1982 prfrm   - single precision version for speed
   26 Mar 1982 nudes   - move to Digital PDP11/34 
    8 Oct 1981 prfrm   - make data structure of figure a list
    2 Oct 1981 prfrm   - 'add','attach','detach','flex','extend', etc. added
    1 Oct 1981 compl   - 'add','touch','attach','detach','flex',etc
   28 Sep 1981 compl   - declare variables to PMAX
   16 Jul 1981 compl   - to negate variables (Nora Neilands)
   16 Jun 1981 compl   - to store orientations and positions (Nora Neilands)
   29 May 1980 compl   - separate compile and perform
   29 May 1980 nudes   - moved to CDC 1800
   27 Jul 1979 nudes   - 'groell','grojnt' added
   20 Feb 1979 nudes   - subroutines added
    1 Apr 1977 nudes   - named constants introduced
   17 Jan 1977 nudes   - bends use arbitrary reference ellipsoid (Bruce McNair)
    4 Jun 1976 nudes   - made interpretive
   10 May 1976 nudes   - input translation separated from drawing
    1 Apr 1975 nudes   - frame numbers used in input language
    1 Apr 1975 nudes   - translated in to Fortran for IBM 7040
   28 Oct 1974 nudes   - use optionally the plotter
   24 Sep 1974 nudes   - verbalize the input language
   11 Aug 1973 nudes   - translated into Fortran for IBM 7040
   11 Apr 1973 nudes   - allow more than one figure
    1 Dec 1972 nudes   - remove hidden lines
   11 Aug 1972 nudes   - originated in Algol on English Electric KDF9 (Don Herbison-Evans) 

     *******************************************************

      Interactive commands :-
          a - continue animating (opp. of 'i')
          b - if frozen, go back one frame else run backwards (opp. of 'f')
          c - continue through restart at full rate (opp. of 'p')
          d - shift down 1% (opp. of 'u')
          f - if frozen, show next forward frame else run forwards (opp.of 'b')
          g - grow scene by 10% (opp. of 's')
          h - show these instructions
          i - freeze (opp. of 'a')
          j - double the number of polygons per sphere {opp. of 'k')
          k - halve the number of polygons per sphere {opp. of 'j')
          l - shift scene left 1% (opp. of 'r')
          n - display of frame numbers (opp. of 'o')
          o - do not display frame numbers (opp. of 'n')
          p - pause on first and last frames (opp. of 'c')
          q - quit
          r - shift scene right 1% (opp. of 'l')
          s - shrink scene by 10% (opp. of 'g')
          t - shift scene away by 10 (opp. of 'T')
          u - shift up 1% (opp. of 'd')
          v - shift away (opp. of 'w')
          w - shift nearer (opp. of 'v')
          x - rotate 10 degrees about x (left - right) axis (opp. of '1')
          y - rotate 10 degrees about y (vertical) axis (opp. of '2')
          z - rotate 10 degrees about z (front - back) axis  (opp. of '3')
          0 - reset parameters to default values and freeze at start
          - - delay more between frames 
          = - delay less between frames

    *************************************

  NUDES action commands:
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

  ****************************************************

  NUDES syntax:

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
     touch   (mvell) (stillell) (movingellipsoid) (referenceellipsoid) (jname) (axis)
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
     every
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

*************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <math.h>
#include <math.h>
#include <ctype.h> 

typedef char TCHAR;

#define TRUE      0
#define FALSE     1
#define DONE      0
#define TODO      1
#define MAN       0
#define WOMAN     1
#define MAXINT 1073741824
#define WINDOW_MODE  1
#define GLUT_KEY_ESCAPE 27 
#define BMAX    256         // size of character buffer
#define EMAX   1024         // maximum number of ellipsoids
//#define FACTOR    2         // number of y pixels per frame
#define FMAX   2048         // maximum number of frames
#define NKEYS    64         // number of keywords
#define PMAX   6000         // maximum number of actions to perform
#define SMAX    100         // maximum number of chords around sphere
#define SMIN      2         // minimum number of chords around sphere
#define SSTART   20         // initial number of chords around sphere

#define LMAX   5000         // max number of laban score entries 
#define TMAX     30         // max number of staff lines
#define VMAX   2048         // max number of constants + variables
#define NCOLM    18         // number of columns around staff
#define STEP     12         // spacing of symbols 
#define WIDTH  1024         // width of the score 
#define NSYMS    25         // max number of items in each menu

#define RELAX     1         // item number of 'relaxed' symbol
#define BENT      3         // item number of 'bent' symbol
#define STRAIGHT  2         // item number of 'straight' symbol
#define STRETCH   4         // item number of 'stretched' symbol      
#define FRONT   100         // front symbol found
#define BACK    200         // back symbol found
#define MLHAND    1         // man's left hand symbol found
#define MRHAND    2         // man's right hand symbol found
#define WLHAND   10         // woman's left hand symbol found
#define WRHAND   20         // woman's right hand symbol found
#define ARM      'a'        // arm found in colm[]
#define CHEST    'c'        // chest found in colm[]

#define LOW       0
#define MED       1
#define HIGH      2
#define BLANK     3

#define NO         0        // no hold
#define CL         1        // closed hold: normal ballroom dancing position.
#define PR         2        // promenade position: facing partner, bodies touching,
                            // but both prepared to travel to man's L.
#define CP         3        // counter promenade position: facing partner, bodies touching,
                            // but both prepared to travel to man's R.
#define DB         4        // double hold: facing partner, bodies apart,
                            // L hand to R, R hand to L.
#define OP         5        // open hold: facing partner, bodies apart,
                            // man's L to lady's R, other hands free.
#define CR         6        // crossed open hold: facing partner, bodies apart,
                            // man's R to lady's R, other hands free.
#define OE         7        // open extended hold: both facing same way, bodies apart,
                            // man's L hand to lady's R, other hands free.
#define CO         8        // counter open extended hold: both facing same way, bodies apart,
                            // man's R hand to lady's L, other hands free.
#define SH         9        // shadow hold: both facing same way, bodies touching,
                            // L hand to L, R hand to R.
#define SS        10        // semi-shadow hold: both facing same way, bodies touching, 
                            // man's L hand to lady's L,
                            // man's R hand on lady's R hip, lady's R hand free.

// ini file variables-

int x;
char ini_title[256][32];
char ini_value[256][128];
int max_ini = 256;
int max_ini_len = 32;
int number_ini;
int ini_diag = 0;
int input_file_type;
int lbn_fps = -1;
int lbn_bpm = -1;
int lbn_ppb = 23;
int lbn_figures = 1;     // number of staves to be interpreted
int time;
int nextcount = 0;
bool output_file_id;

// symbol menus-
char Area ='A';
char Bars ='B';
char Dirn ='D';
char Face ='F';
char Path ='H';
char Keys ='K';
char Limb ='L';
char Misc ='M';
char Pins ='P';
char Rotn ='R';
char Stav ='S';
char Volm ='V';

bool forbid[EMAX][EMAX];

double  doub0;
double  doub1;
double  doub2;
double  doub3;
double  doub4;
double  doub10;
double  doub60;
double  doub90;
double  doub150;
double  doub179;
double  doub180;
double  doub181;
double  doub255;
double  doub360;
double  doub500;
double  doubmax;
double  inv2;
double  inv3;
double  inv4;
double  inv5;
double  inv6;
double  inv10;
double  inv256;
double  inv1000;
double  lg2;                   //logarithm of 2 
double  rt3;
double  tolr;
double  twopi;
double  pi;                    // 3.142...etc /
double  piby2;
double  degree;                // number of degrees in a radian 
double  radian;                // number of radians in a degree
double  rad;                   // conversion factor from degrees to radians 
double  radten;                // conversion factor from tenths of a degree to radians 
double  alpha;                 // basic interactive angle increment
double  anglex,angley,anglez;  // interactive rotation angles 
double  dangx,dangy,dangz;     // interactive rotation angle increments 
//double  fac;                   // lbn conversion factor from y to frames 
double  scale;                 // interactive scaling factor 
double  SCALE = 1.0;           // default scaling to fit window
double  tx,ty,tz;              // interactive translations
//double  x1a,x1b,x2a,x2b;
//double  y1a,y1b,y2a,y2b;
//double  x1s,x2s,y1s,y2s;
double  frac;                  // fraction of action to be done in this frame
double  prop;                  // proportion of action yet to be done 
double  step1,step2;
double  v;
double  varval;                // varval - value of variable
double  ang[3];                // the 3 eulerian angles 
double  oldang[3];
double  obsang[3];
double  factor[3];             // factors in x,y, and z directions 
double  lighting_rgb[3];
double  pplace[3];             // position of centre of observers attention
double  semiax[3];             // coordinate triple read from input 
double  xx[3];                 // x,y and z values (x&y used for commands add, subtract,multiply,divide)
double  val[VMAX];             // val[i] - if i <= nvals then value of ith constant
                               //           otherwise (s - i+1)th variable 
double  maxax[EMAX];           // maxax[j] - largest semiaxis of jth ellipsoid 
double  minax[EMAX];
double  pres[EMAX];
double  obs[3][3];             // rotation matrix applied to all ellipsoids to obtain observers view  
double  col[EMAX][3];          // col[i][j] - colour of ell i; j = 0 red, 1 green, 2 blue 
double  quasav[EMAX+2][5];
double  ax[EMAX][3];           // ax3[i][j] - length of jth semiaxis of ith ellipsoid
double  cen[EMAX][3];          // cen[i][j] - jth coordinate of centre of ith ellipsoid
double  censav[EMAX][3];
double  dcon[EMAX][2][3];      // distances of joint from ellipsoid centres
double  jnt[EMAX][3];          // coordinates of joints between ellipsoids 
double  jntsav[EMAX][3];
double  ob3[FMAX][3];          // observation angles of each frame
double  pl3[FMAX][3];          // centre of view of each frame
double  norm[4*SMAX*SMAX][3];  // normals at sphere faces 
double  sph[4*SMAX*SMAX][4][3];// vertices of facets of  sphere 
double  lim[EMAX][3][2];
double  co3[FMAX][EMAX][3];    // colours of ellipsoids
double  ce3[FMAX][EMAX][3];    // coordinates of ellipsoid centres 
double  ax3[FMAX][EMAX][3];    // ellipsoid semiaxis lengths 
double  qu3[FMAX][EMAX][4];    // quaternions of ellipsoids  
double  quat[EMAX+2][5];       // quat[i][j] - angle of ith ellipsoid 
                               // j = 0,1,2 - components of direction of rotation axis  
                               // j = 3,4   - sine and cosine of rotation about axis 
double point[SMAX][2*SMAX+1][3];



struct Symbol {
	int a;       // TRUE = 0 if already done
	int b;       // bent indicator
	int c;       // column position relative to right support column
	int h;       // height
	int i;       // item in menu
	int l;       // lbn file line number
	char m;      // menu
	int s;       // drawing step size
	int w;       // width
	int x;       // horizontal position of left side
	int y;       // vertical position of bottom
	int x2;      // horizontal position of right side
	int y2;      // vertical position of top
	int d;       // height indicator
   };

struct Symbol lbn[LMAX]; // laban score entries
int ja;                  // TRUE = 0 if already done
int jb;                  // bendedness of current symbol
int jc;                  // current symbol column
int jh;                  // current symbol height
int ji;                  // current symbol item in menu
int jl;                  // line of current symbol
char jm;                 // current symbol menu
int js;                  // current symbol step size
int jw;                  // current symbol width
int jx;                  // current symbol x bottom
int jy;                  // current symbol y bottom 
int jx2;                 // current symbol x top
int jy2;                 // current symbol y top
int jd;                  // current symbol shading
/*************************************************************/

// linter variables -
bool mspace,wspace;

double lbn_fpp;      // frames per pixel

int blength;         // number of bars to interpret
int bpm;             // beats per minute
int bstart;          // bar to start at
int lcentre;         // x position of centre staff line
int complete;        // true if Gloria and Frank to be used
int dofig;           // required gender of current staff
int dostaff;         // index in staff[] of current staff
int facedif;         // difference between facing directions of man and lwoman
int facecl;          // facing score of closed position
int facepr;          // facing score of promenade position
int facesh;          // facing score of shadow position
int facess;          // facing score of semishadow position
int fbegin,ffin,flen;// start,end, and length of a position
int fend;            // frame number of end of current movement
int fhalf;           // frame halfway through a movement
int f_max;            // maximum frame number
int fps;             // frames/second
int frange;          // number of frames in an action
int frperbar;        // frames per bar;
int fstart;          // first frame number of action
int gy,gh;           // arm gesture range disabled by contact bow
int haslbn;          // TRUE if input is lbn file, FALSE for .n file
int hold;            // one of the defined holds NO,CL,PR,CP,DB,OP,CR,OE,CO,SH,SS
int holdcl;          // closed hold counter 
int holdco;          // counter open extended hold counter
int holdoe;          // open extended hold counter
int holdpr;          // promenade hold counter
int holdsh;          // shadow hold counter
int holdss;          // semishadow hold counter
int j;               // counter through symbols
int keptf;           // last frame when last position kept
int mface,wface;     // facing directions of man and woman
int nbar;            // number of current bar
int nlabs;           // number of laban score entries
int npins;           // number of pins below first barline
int nm;              // number of men
int nw;              // number of women
int nmw;             // nm * nw
int nstaff;          // number of staves
int oriented;        // true after orientation
int pend;            // last frame of previous action
int pstart;          // first fame of previous action
int ppb;             // pixels per beat (= 23 );
int prev_time;       // clock reading of previous frame
int pres_time;       // clock reading of current frame
int previ;           // item of previous support symbol
int prevc;           // column of previous support symbol
int prevhold;        // previous hold
int rise;            // height of previous step;
int ssend;           // ending score symbol
int sstart;          // starting score symbol
int st;              // current staff number
int stmiddle;        // halfway across between L and R staves
int track;           // TRUE when tracking viewpoint on main figure
int xmin,xmax;       // width range of score symbols
int ymax;            // top of score
int yend;            // y position of last movement
int ystart;          // y position of start of movement
int yj[5*FMAX];      // symbols starting at given y positions
int pins[TMAX][2];   // index and use of initial pins
int staff[TMAX][6];  // index, x positions, gender, and use of staves
char colm[NCOLM];    // limb presigns in the columns

//nudes variables -
int axis;            // axis of next rotation
int bnums;           // TRUE if bar numbers to be displayed 
int comand;          // counter through all commands.
int df;              // interactive frame increment 
int ecount;          // number of entries in 'elist'
int ell1;            // ellipsoid to touch something  
int ell2;            // ellipsoid to be touched 
int ellpsd;          // active ellipsoid
int f;               // counter through frames 
int fast;            // multiplier of frame numbers
int fig;             // current figure 
int fnums;           // TRUE if frame numbers to be displayed 
int forward;         // TRUE for animation to go forwards 
int freeze;          // TRUE if animation frozen 
int fstop;           // last frame number of actions
int fslow;
int height = 512;    // height  of window in pixels
int hstart;          // frame at start of hold
int hend;            // frame at end of hold
int inmain;          // TRUE if still in main NUDES program 
int intersect;
int jcount ;
int join;            // joint for current bend command  
int k;
int length;          // length of next input string 
int lline;           // length of next input line 
int maxint;          // largest representable integer
int more;            // if > 0 means more actions for which stp>=fr 
int ne;              // number of ellipsoids in current frame
int nesave;
int nfaces;          // number of faces on sphere 
int nfigs;           // number of figures
int nfiles;          // number of texture map files
int njts;            // number of joints 
int nline;           // number of current nudes file line
int npfs;            // number of actions 
int nsph;            // number of chords around sphere 
int nsubs;           // number of subroutines 
int nvals;           // number of values in 'val' 
int nvars;           // number of variables in array val 
int ok;              // ok = 0 if ok, else problem reference number 
int p;               // counter through actions
int pause;           // TRUE if pausing on 1st and last frames 
int pok;             // true if positive integer read 
int prdone;          // TRUE if diagnostic printing already done
int ptype;           // code of current action 
int pp;
int donesurf;        // TRUE if 'surf' called from 'dotouch'
int refell;          // ellipsoid used as angular reference 
int shadow;          // TRUE if shadows wanted
int single;          // either TODO or DONE when frozen
int slow;            // number of pause calls between animating frames 
int start;           // pointer to next character on current input line 
int t;               // type of current action 
int var0;
int var1;
int var2;
int vstart;          // first frame from view command
int vstop;           // last frame from view command
int width = 512;     // height  of window 
int xw = 10;
int yw = 10;         // lower left corner of window 
int newcol[3];
int axlen[EMAX];     // lengths of names
int ellen[EMAX];
int figlen[EMAX];
int jntlen[EMAX];
int fillen[EMAX];
int keylen[NKEYS];
int sublen[PMAX];
int varlen[PMAX];
int called[PMAX];    // true if subroutine is called 
int cline[PMAX];     // line numbers in input file of each action 
int coel[EMAX][2];   // the 2 ellipsoids joined at a joint 
int defined[PMAX];   // TRUE if subroutine is defined 
int distrn[PMAX];    // how actions are distributed over frames 
int ellfig[EMAX];    // number of the figure containing each ellipsoid
int elist[EMAX];     // array for lists of ellipsoids in current action 
int figell[EMAX];    // figell[i] - first ellipsoid in ith figure 
int frames[FMAX];    // original NUDES frame numbers
int frstart[PMAX];   // frstart[i] - frame number of start of ith action 
int frstop[PMAX];    // frstop[i] - frame number of end of ith action  
int jlist[EMAX];     // array for lists of joints in current action 
int knee[EMAX];      // knee[j] - true if jth joint is a knee i.e. flexes backwards  
int nels[FMAX];      // number of ellipsoids in each frame 
int type[PMAX];      // type of  action 
int pf[PMAX][6];     // pf[i][j] - jth parameter of ith action-  +ve: itself, -ve: index into array val 
int subact[PMAX][2]; // subact[i][] - action numbers of start and end of ith subroutine
int usevar[PMAX];    // 0 if variable not used 
int order[3][3][3] = {
      { {2,1,1},{1,3,4},{1,5,3} },
      { {3,1,5},{1,2,1},{4,1,3} },
      { {3,4,1},{5,3,1},{1,1,2} }};
int perm[3][3][3] = {
      { {2,1,1},{1,3,4},{1,5,3} },
      { {3,1,5},{1,2,1},{4,1,3} },
      { {3,4,1},{5,3,1},{1,1,2} }};
/*
   keyword codes -
*/
   int figure_keyword_code=  1;
   int ellips_keyword_code=  2;
   int joint_keyword_code=  3;
   int accele_keyword_code=  5;
   int subrou_keyword_code=  6;
   int balanc_keyword_code=  7;
   int attach_keyword_code=  8;
   int detach_keyword_code=  9;
   int decele_keyword_code= 10;
   int grofig_keyword_code= 11;
   int spinto_keyword_code= 12;
   int moveby_keyword_code= 13;
   int add_keyword_code= 14;
   int touch_keyword_code= 15;
   int stop_keyword_code= 16;
   int spinby_keyword_code= 17;
   int ground_keyword_code= 18;
   int bendby_keyword_code= 19;
   int set_keyword_code= 20;
   int bendto_keyword_code= 21;
   int dodebug_keyword_code= 22;
   int repeat_keyword_code= 23;
   int quadra_keyword_code= 24;
   int linear_keyword_code= 25;
   int observ_keyword_code= 26;
   int moveto_keyword_code= 27;
   int call_keyword_code= 28;
   int endsub_keyword_code= 29;
   int speed_keyword_code= 30;
   int invert_keyword_code= 31;
   int variable_keyword_code = 32;
   int view_keyword_code= 33;
   int groell_keyword_code= 34;
   int grojnt_keyword_code= 35;
   int angles_keyword_code= 36;
   int centre_keyword_code= 37;
   int flex_keyword_code= 38;
   int rotate_keyword_code= 39;
   int abduct_keyword_code= 40;
   int negate_keyword_code= 41;
   int subtra_keyword_code= 42;
   int divide_keyword_code= 43;
   int multip_keyword_code= 44;
   int cubic_keyword_code= 46;
   int place_keyword_code= 47;
   int axes_keyword_code= 48;
   int linkx_keyword_code= 49;
   int colour_keyword_code= 50;
   int print_keyword_code= 51;
   int textur_keyword_code= 52;
   int drag_keyword_code= 53;
   int limits_keyword_code= 54;
   int abut_keyword_code= 55;
   int movjnt_keyword_code= 56;
   int growto_keyword_code= 57;
   int color_keyword_code= 58;
   int center_keyword_code= 59;
   int opacty_keyword_code= 60;
   int lghtng_keyword_code= 61;
   int allow_keyword_code= 62;
   int forbid_keyword_code= 63;


FILE *infile;
FILE *nudesfile;
FILE *figsfile;

char* junk[BMAX];

char buf[BMAX];            // input buffer
char line[BMAX];           // compl input buffer 
char lbnline[LMAX][BMAX];  // lbn file lines
char string[BMAX];         // next set of non-blank characters from data file */
char name[BMAX];           // name of input file
char finname[BMAX];        // name of input file
char figsname[BMAX];       // name of lintel nudes figures, declarations, and subroutines file */
char nudesname[BMAX];      // name of intermediate nudes file
char ptitle[BMAX];         // program title
char risesub[3][5] = {{'f','l','o','w'},
                      {'f','m','e','d'},
                      {'f','h','i','g','h'}};
char xyz[2][10] = {{'m','x',' ','m','y',' ','m','z'},
                  {'w','x',' ','w','y',' ','w','z'}};
char aline[PMAX][BMAX];    // nudes input lines
char tname[EMAX][BMAX];    // name of texture map file
char jname[EMAX][BMAX];    // joint names 
char sname[EMAX][BMAX];    // subroutine names
char vname[EMAX][BMAX];    // variable names
char axnam[EMAX][BMAX];    // first entry is the set of axis names 'x','y','z'. The rest are null
char ename[EMAX][BMAX];    // ellipsoid names 
char fname[EMAX][BMAX];    // figure names 
char tn3[FMAX][EMAX][BMAX];// names of reduced texture map files
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
int par[NKEYS][6] =  {
      {0,0,0,0,0,0},//   0
      {0,0,0,0,0,0},//   1  figure
      {0,0,0,0,0,0},//   2 ellips
      {0,0,0,0,0,0},//   3 joint
      {0,0,0,0,0,0},//   4 
      {1,0,0,0,0,0},//   5 accele
      {0,0,0,0,0,0},//   6 subrou 
      {2,3,2,5,0,0},//   7 balanc
      {2,3,2,1,1,1},//   8 attach
      {2,3,4,0,0,0},//   9 detach
      {1,0,0,0,0,0},//  10 decele
      {4,2,1,1,1,0},//  11 grofig
      {4,2,2,1,1,1},//  12 spinto
      {4,2,1,1,1,0},//  13 moveby
      {7,1,1,0,0,0},//  14 add
      {2,2,2,2,3,5},//  15 touch
      {0,0,0,0,0,0},//  16 stop
      {4,2,2,1,5,0},//  17 spinby
      {4,0,0,0,0,0},//  18 ground
      {2,3,2,1,5,0},//  19 bendby
      {7,8,0,0,0,0},//  20 set
      {2,3,2,1,1,1},//  21 bendto
      {1,0,0,0,0,0},//  22 dodebug
      {1,0,0,0,0,0},//  23 repeat
      {1,0,0,0,0,0},//  24 quadra
      {1,0,0,0,0,0},//  25 linear
      {1,1,1,0,0,0},//  26 observ
      {4,2,1,1,1,0},//  27 moveto
      {8,0,0,0,0,0},//  28 call
      {0,0,0,0,0,0},//  29 endsub
      {0,0,0,0,0,0},//  30 speed
      {7,0,0,0,0,0},//  31 invert
      {0,0,0,0,0,0},//  32 variable
      {0,0,0,0,0,0},//  33 view
      {2,1,1,1,0,0},//  34 groell
      {2,3,1,1,1,0},//  35 grojnt
      {2,2,7,7,7,0},//  36 angles
      {2,7,7,7,0,0},//  37 centre
      {2,3,1,0,0,0},//  38 flex
      {2,3,1,0,0,0},//  39 rotate
      {2,3,1,0,0,0},//  40 abduct
      {7,0,0,0,0,0},//  41 negate
      {7,1,1,0,0,0},//  42 subtra
      {7,1,1,0,0,0},//  43 divide
      {7,1,1,0,0,0},//  44 multiply
      {0,0,0,0,0,0},//  45
      {0,0,0,0,0,0},//  46 cubic
      {1,1,1,0,0,0},//  47 place
      {2,7,7,7,0,0},//  48 axes
      {3,7,7,7,0,0},//  49 linkx
      {2,1,1,1,0,0},//  50 colour
      {7,0,0,0,0,0},//  51 print
      {2,9,1,1,0,0},//  52 texture
      {2,2,3,2,5,0},//  53 drag
      {0,0,0,0,0,0},//  54 limits
      {2,2,2,5,0,0},//  55 abut
      {3,2,1,1,1,0},//  56 movjnt
		{4,2,1,1,1,0},//  57;
		{2,1,1,1,0,0},//  58;
		{2,7,7,7,0,0},//  59;	
		{2,1,0,0,0,0},//  60;
		{1,1,1,0,0,0},//  61;
		{2,2,0,0,0,0},//  62;
		{2,2,0,0,0,0}};// 63;

char keynam[NKEYS][BMAX] = {
      {'k','e','y','w','o','r','d'},             // 0
      {'f','i','g','u','r','e'},                 // 1
      {'e','l','l','i','p','s','o','i','d'},     // 2
      {'j','o','i','n','t'},                     // 3
      {'c','o','p','y'},                         // 4
      {'a','c','c','e','l','e','r','a','t','e'}, // 5
      {'s','u','b','r','o','u','t','i','n','e'}, // 6
      {'b','a','l','a','n','c','e'},             // 7
      {'a','t','t','a','c','h'},                 // 8
      {'d','e','t','a','c','h'},                 // 9
      {'d','e','c','e','l','e','r','a','t','e'}, // 10
      {'g','r','o','f','i','g'},                 // 11
      {'s','p','i','n','t','o'},                 // 12
      {'m','o','v','e','b','y'},                 // 13
      {'a','d','d'},                             // 14
      {'t','o','u','c','h'},                     // 15
      {'s','t','o','p'},                         // 16
      {'s','p','i','n','b','y'},                 // 17
      {'g','r','o','u','n','d'},                 // 18
      {'b','e','n','d','b','y'},                 // 19
      {'s','e','t'},                             // 20
      {'b','e','n','d','t','o'},                 // 21
      {'d','e','b','u','g'},                     // 22
      {'r','e','p','e','a','t'},                 // 23
      {'q','u','a','d','r','a','t','i','c'},     // 24
      {'l','i','n','e','a','r'},                 // 25
      {'o','b','s','e','r','v','e'},             // 26
      {'m','o','v','e','t','o'},                 // 27
      {'c','a','l','l'},                         // 28
      {'e','n','d','s','u','b'},                 // 39
      {'s','p','e','e','d'},                     // 30
      {'i','n','v','e','r','t'},                 // 31
      {'v','a','r','i','a','b','l','e','s'},     // 32
      {'v','i','e','w'},                         // 33
      {'g','r','o','e','l','l'},                 // 34
      {'g','r','o','j','n','t'},                 // 35
      {'a','n','g','l','e','s'},                 // 36
      {'c','e','n','t','r','e'},                 // 37
      {'f','l','e','x'},                         // 38
      {'r','o','t','a','t','e'},                 // 39
      {'a','b','d','u','c','t'},                 // 40
      {'n','e','g','a','t','e'},                 // 41
      {'s','u','b','t','r','a','c','t'},         // 42
      {'d','i','v','i','d','e'},                 // 43
      {'m','u','l','t','i','p','l','y'},         // 44
      {'r','e','a','d'},                         // 45
      {'c','u','b','i','c'},                     // 46
      {'p','l','a','c','e'},                     // 47
      {'a','x','e','s'},                         // 48
      {'l','i','n','k','x'},                     // 49
      {'c','o','l','o','u','r'},                 // 50
      {'p','r','i','n','t'},                     // 51
      {'t','e','x','t','u','r','e'},             // 52
      {'d','r','a','g'},                         // 53
      {'l','i','m','i','t'},                     // 54
      {'a','b','u','t'},                         // 55
      {'m','o','v','j','n','t'},				       // 56
		{'g','r','o','w','t','o'},                 // 57
		{'c','o','l','o','r'},                     // 58
		{'c','e','n','t','e','r'},                 // 59
		{'o','p','a','c','t','y'},                 // 60
		{'l','g','h','t','n','g'},                 // 61
		{'a','l','l','o','w'},                     // 62
		{'f','o','r','b','i','d'} };               // 63
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
      {0,0,0,0,0,0},      // 0
      {0,0,0,0,0,0},      // 1
      {0,0,0,0,0,0},      // 2
      {0,0,0,0,0,0},      // 3
      {0,0,0,0,0,0},      // 4
      {0,0,0,0,0,0},      // 5
      {0,0,0,0,0,0},      // 6
      {24,22,23,21,0,0},  // 7
      {24,22,23,1,2,3},   // 8
      {24,22,25,0,0,0},   // 9
      {0,0,0,0,0,0},      // 10
      {25,24,7,8,9,0},    // 11
      {25,24,23,4,5,6},   // 12
      {25,23,1,2,3,0},    // 13
      {27,1,2,0,0,0},     // 14
      {30,31,24,23,22,21},// 15
      {0,0,0,0,0,0},      // 16
      {25,24,23,4,21,0},  // 17
      {25,0,0,0,0,0},     // 18
      {24,22,23,4,21,0},  // 19
      {27,10,0,0,0,0},    // 20
      {24,22,23,4,5,6},   // 21
      {14,0,0,0,0,0},     // 22
      {0,0,0,0,0,0},      // 23
      {0,0,0,0,0,0},      // 24
      {0,0,0,0,0,0},      // 25
      {4,5,6,0,0,0},      // 26
      {25,24,1,2,3,0},    // 27
      {0,0,0,0,0,0},      // 28
      {0,0,0,0,0,0},      // 29
      {0,0,0,0,0,0},      // 30
      {27,0,0,0,0,0},     // 31
      {0,0,0,0,0,0},      // 32
      {0,0,0,0,0,0},      // 33
      {24,7,8,9,0,0},     // 34
      {24,22,7,8,9,0},    // 35
      {24,23,27,28,29,0}, // 36
      {24,27,28,29,0,0},  // 37
      {24,22,4,0,0,0},    // 38
      {24,22,4,0,0,0},    // 39
      {24,22,4,0,0,0},    // 40
      {27,0,0,0,0,0},     // 41
      {27,1,2,0,0,0},     // 42
      {27,1,2,0,0,0},     // 43
      {27,1,2,0,0,0},     // 44
      {0,0,0,0,0,0},      // 45
      {0,0,0,0,0,0},      // 46
      {1,2,3,0,0,0},      // 47
      {24,27,28,29,0,0},  // 48
      {22,27,28,29,0,0},  // 49
      {24,11,12,13,0,0},  // 50
      {27,0,0,0,0,0},     // 51
      {24,11,12,13,0,0},  // 52
      {30,24,22,23,21,0}, // 53
      {0,0,0,0,0,0},      // 54
      {30,31,23,21,0,0},  // 55
      {22,24,1,2,3,0},    // 56
		{0,0,0,0,0,0},      // growto 57;
		{24,11,12,13,0,0},  // color 58;
		{24,27,28,29,0,0},  // center 59;
		{30,31,0,0,0,0},    // opacity 60;
		{30,31,0,0,0,0},    // lighting 61;
		{30,31,0,0,0,0},    // allow 62;
		{30,31,0,0,0,0}};   // forbid 63;

/****************************************/

char menutext[NSYMS][4] = {
     {'B','a','r','s'},
     {'D','i','r','n'},
     {'P','i','n','s'},
     {'F','a','c','e'},
     {'L','i','m','b'},
     {'V','o','l','m'},
     {'A','r','e','a'},
     {'R','o','t','n'},
     {'K','e','y','s'},
     {'M','i','s','c'},
     {'W','a','y','s'},
     {'Z','Z','Z','Z'},
     {'S','t','a','v'} };

int   leg[12][3]   /* quaternion angles of 11 direction symbols */
                   /* for walking */
     =   {{  0,  0,  0},
          {  0,  0, 30},
          {  0,315, 30},
          {  0,270, 30},
          {  0,225, 30},
          {  0,180, 30},
          {  0,180, 30},
          {  0,135, 30},
          {  0, 90, 30},
          {  0, 45, 30},
          {  0,  0, 30},
          {  0,  0,  0}};

int   opp[12]       /* opposite direction to a movement */
                    /* for the leg that is left behind */
                    =    {  0,  5,  7,  8,  9,  1,  1,  2,  3,  4,  5,  0};

int   stt[3][12][3] /* quaternion angles of 11 direction symbols */
                    /* for straight limbs */
                    /* at hip or shoulder */
     =  {{{  0,  0,  0}, // null
			 {  0,  0, 35}, //   1 R forward low
			 {  0,315, 35}, //   2 R diagonally forward low
			 { 68, 90,-35}, //   3 R side low
			 {  0,225, 35}, //   4 R diagonally back low
			 {  0,180, 35}, //   5 R back low
			 {  0,180, 35}, //   6 L back low
			 {  0,135, 35}, //   7 L diagonally back low
			 { 68, 90, 35}, //   8 L side low
			 {  0, 45, 35}, //   9 L diagonally forward low
			 {  0,  0, 35}, //  10 L forward low
			 {  0,  0,  0}},//  11 in place low
			{{  0,  0,  0}, // null
			 {  0,  0, 90}, //   1 R forward middle
			 {337,339, 98}, //   2 R diag forward middle
			 {315,270, 90}, //   3 R side middle
			 {158,339, 98},
			 {180,  0, 90},
			 {180,  0, 90},
			 {202, 21, 98},
			 {114, 90, 90},
			 { 22, 21, 98},
			 {  0,  0, 90},
			 {  0,  0,  0}},
			{{  0,  0,  0}, // null
			 {  0,  0,135}, // R forward high
			 {  0,315,135},
			 {  0,270,135},
			 {  0,225,135},
			 {  0,180,135},
			 {  0,180,135},
			 {  0,135,135},
			 {  0, 90,135},
			 {  0, 45,135},
			 {  0,  0,135},
			 {  0,  0,180}}};
int   trlx[3][12][3]  /* quaternion angles of 11 direction symbols */
                      /* for relaxed thighs */
     =  {{{  0,  0,  0}, // null
			 {  0,  0, 55}, // R low forward
			 {321,342, 70},
			 {180,270, 44}, // R low side
			 {257,310, 60},
			 {180,  0, 30}, // R low back
			 {180,  0, 30}, // L low back
			 { 99, 46, 58},
			 { 87, 90, 44}, // L low side
			 { 42, 17, 66},
			 {  0,  0, 50},
			 {  0,  0,  0}},
			{{  0,  0,  0},
			 {  0,  0,110},
			 {341,339,107},
			 { 45,277, 90},
			 {225,294, 95},
			 {180,  0, 80},
			 {180,  0, 80},
			 {135, 66, 95},
			 {315, 83, 90},
			 { 19, 21,107},
			 {  0,  0,100},
			 {  0,  0,  0}},
			{{  0,  0,  0},
			 {  0,  0,145},
			 {352,338,148},
			 { 68,275,135},
			 {192,291,135},
			 {180,  0,125},
			 {180,  0,125},
			 {167, 69,134},
			 {292, 85,135},
			 {  7, 22,148},
			 {  0,  0,145},
			 {  0,  0,180}}};
int   arlx[3][12][3]  /* quaternion angles of 11 direction symbols */
     =  {{{  0,   0,   0}, // null
          {  0,   0,  35}, // R low forward
          {307, 346,  56},
          {287, 335, 102}, // R low side
          {141, 342,  70},
          {180,   0,  50},
          {180,   0,  50},
          {222,  17,  66},
          { 72,  25, 102}, // L low side
          { 57,  12,  54}, // L low diag forward
          {  0,   0,  35}, // L low forward
          {  0,   0,  0}}, // L low centre
         {{  0,   0,   0}, // null
          {  0,   0,  67},
          {328, 341,  79},
          {303, 331, 108}, // R middle side
          {285, 328, 143},
          {270, 327, 179}, // R middle back
          { 90,  33, 179}, // L middle back
          { 75,  33, 143},
          { 57,  29, 108}, // L middle side
          { 32,  19,  79},
          {  0,   0,  67}, // L middle front
          {315,  60,  98}},// L middle centre
         {{  0,  0,  0},
          {  0,  0,145},
          {348,338,129},
          {247,275,135},
          {209,298,142},
          { 90, 72,180},
          { 90, 72,180},
          {150, 62,143},
          {112, 85,135},
          { 12, 22,129},
          {  0,  0,125},
          {350,-45,166}}};

int   abnt[3][12][3]  /* quaternion angles of 11 direction symbols */
                      /* for 90 degree bent arms */
     =  {{{252 , 17,  95},
          {  0,   0,   0},
          {270,   0,  45},
          {270,   0,  90}, // R low side
          {270,   0, 135},
          {270,   0, 180}, // R low back 
          { 90,   0, 180}, // L low back
          { 90,   0, 135},
          { 90,   0,  90},
          { 90,   0,  45},
          {  0,   0,   0}, // L low forward
          {  0,   0,   0}},
         {{  0,   0,   0},
          { 45, 300,  98},
          { 67,  21,  98}, // R middle side
          {225, 300,  98},
          {  0, 225, 135},
          {  0, 180, 135},
          {  0, 180, 135},
          {  0, 135, 135},
          {135,  60,  98},
          {292, 339,  98}, // L middle side
          {315,  60,  98},
          {  0,   0,   0}},
         {{  0,   0,   0},
          {  0, 315, 135},
          {  0, 270, 135},
          { 45, 225, 135},
          { 90, 225, 135},
          {135, 225, 135},
          {135, 225, 135},
          { 90,  45, 135},
          { 45, 225, 225},
          {  0,  90, 135},
          {  0,  45, 135},
          { 90,  67, 180}}};

/************************************************/

int main(int argc, char* argv[]);

void lgetout(int allok)
/*
    close files and wait

	called by  linter, lcopyfigs, lcopysubs, ldopivot, lchange,
	           lfindstaff, lfindystart, lleggesture, lselectfig,
	           loverlap,
*/
{
   if (allok == 0) 
   {
      printf("%s created OK\n", nudesname);
      if (infile) fclose(infile);
      if (nudesfile) fclose(nudesfile);
      if (figsfile) fclose(figsfile);
   }
   else
   {
      printf("lintel snag, line %d\n",j);
      printf("%s\n",lbnline[j]);
notok: goto notok;
	   ok = 1;
   }
}/* lgetout */
/***********************************************************/

void initialise(void)
/*
   set up constants to default values

   called by main,
*/
{
   double a,b;
   int k,m,n;

   prdone = FALSE;
   nbar = -1;
   rise = 1;
   prevc = 0;
   previ = 11;
   track = TRUE;
	mspace = false;
	wspace = FALSE;

   doub0 = double(0);
   doub1 = double(1);
   doub2 = double(2);
   doub3 = double(3);
   doub4 = double(4);
   doub10 = double(10);
	doub60 = double(60);
   doub90 = double(90);
   doub150 = double(150);
   doub179 = double(179);
   doub180 = double(180);
   doub181 = double(181);
   doub255 = double(255);
   doub360 = double(360);
   doub500 = double(500);
   inv2 = doub1/doub2;
   inv3 = doub1/doub3;
   inv4 = doub1/doub4;
   inv5 = doub1/double(5);
   inv6 = doub1/double(6);
   inv10 = doub1/doub10;
   inv256 = doub1/double(256);
   inv1000 = doub1/double(1000);
   rt3 = sqrt(doub3);
   piby2 = doub2*atan(doub1);
   pi = piby2+piby2 ;
   twopi = pi+pi;
   radten = twopi/double(3600);
   radian = twopi/doub360;
   degree = doub1/radian;
   lg2 = log(doub2);
   freeze = FALSE;
   forward = TRUE;
   single = DONE;
   pause = FALSE;
   shadow = TRUE;
   fnums = TRUE;
   bnums = TRUE;
   hold = NO;
   prevhold = -99;
   prev_time = -1;
   fstart = 0;
   fstop = 0;
   pstart = 0;
   pend = 0;
   f_max = 0;
   vstart = 0;
   vstop = FMAX;
   inmain = TRUE;
   start = -1;
   lline = 0;
   fast = 1;
   slow = 1;
   fslow = 1;
   njts = 0;
   nvars = 0;
   nfiles = 0;
   nvals = 0;
   axlen[0] = 1; axlen[1] = 1; axlen[2] = 1;
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
      figell[j] = 0;
      ellfig[j] = 0;
      usevar[j] = 0;
      coel[j][0] = -1;
      coel[j][1] = -1;
      subact[j][0] = 0;
      subact[j][1] = 0;
      called[j] = FALSE;
      defined[j] = FALSE;
      val[j] = doub0 ;

      for (  k = 0 ; k < 3 ; ++ k )
      {
         cen[j][k] = doub3;
         ax[j][k] = doub2;
         lim[j][k][0] = -doub360;
         lim[j][k][1] =  doub360;
         obs[k][0] = doub0;
         obs[k][1] = doub0;
         obs[k][2] = doub0;
         obs[k][k] = doub1;
      }
      col[j][0] = doub255;
      col[j][1] = doub150;
      col[j][2] = doub90;
      quat[j][0] = doub1;
      quat[j][1] = doub0;
      quat[j][2] = doub0;
      quat[j][3] = doub0;
      quat[j][4] = doub1;
      for (  k = 0 ; k < BMAX ; ++ k )
      {
         axnam[j][k] = NULL;
         tname[j][k] = NULL;
         fname[j][k] = NULL;
         ename[j][k] = NULL;
         jname[j][k] = NULL;
         vname[j][k] = NULL;
         sname[j][k] = NULL;
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
      type[j] = stop_keyword_code;
      frstart[j] = 0;
      frstop[j] = 0;
      distrn[j] = 0;
      cline[j] = 0;

      for (  k = 0 ; k < 6 ; ++ k )
         pf[j][k] = 0;
   }
/*
     artificially set up subroutine "nudes",
     file "dummy", figures "every" and "world",
     variable "variable", and ellipsoid "world"-
*/
   nsubs = 1;
   nfigs = 2;
   ne = 1;
   figell[0] = 0;
   figell[1] = 1;

   for (  k = 0 ; k < 6 ; ++ k )
   {
      tname[0][k] = dummy[k];
      sname[0][k] = nudes[k];
      fname[0][k] = every[k];
      fname[1][k] = world[k];
      ename[0][k] = world[k];
      vname[0][k] = variab[k];
   }
   fillen[0] = 5;
   sublen[0] = 5;
   figlen[0] = 5;
   figlen[1] = 5;
   ellen[0] = 5;
   varlen[0] = 6;
   ax[0][0] = doub1;
   ax[0][1] = doub1;
   ax[0][2] = doub1;
   df = 1;
   f = 0;
   nsph = SSTART;
   anglex = doub0; angley = doub0; anglez = doub0;
   tx = doub0; ty = doub0; tz = doub0;
   scale = doub1;
   alpha = doub3;
   t = 0;
   more = 1;
   ok = 0;

// find bits in double mantissa -	
	b = doub1;
	m = 0;
	for (a = inv2; doub1 + b > doub1 + a; a *= inv2)
	{
		b = a;
		++ m;
	}
	tolr = b+b;
	j = 2;
	n = 0;

// find bits in integer -
	for (k = 1; k < j; j += j)
	{
		k += k;
		++ n;
	}
	maxint = k;
	printf("\n   tolr %g (%d bits), maxint %d (%d bits)\n",
		tolr,m,maxint,n);
} /* initialise */
/***************************************/

void bell ( int number, int delay)
{
	  int i, j;
	  for ( i = 0; i < number; i++ )
	  {
            printf ( "\a" );
			for ( j = 0; j < delay; j++ )
			{
			}
	  }
} /* bell */
/***************************************/

int lfindnext(int c, int y1, int y2)
/*
   find next symbol in column 'c' in range 'y1' to 'y2'.

   called by ldostep,
*/

{
   int k;
   int q;
   int yy;

   q = -1;
   yy = y2;
   for (k = sstart; k < ssend; ++k)
   {
      if ((lbn[k].c == jc) && (lbn[k].y >= y1) && (lbn[k].y <= y2))
      {
         if (lbn[k].y < yy)
         {
            q = k;
            yy = lbn[k].y;
         }
      }
   }
   return(q);
}   /* lfindnext */
/****************************************************/

void lsetframes(void)
/*
    set the frames over which an action occurs :-
    fstart, fhalf, frange, fend.

    called by laction,
*/
{
   if (nbar < 1)
   {
      fstart = 0;
      frange = 1;
      fend = 1;
   }
   else
   {
      fstart = int(inv2+lbn_fpp*double(jy-ystart));
      if (fstart < 1) fstart = 1;
      frange = int(inv2+lbn_fpp*double(jh));
      if (frange < 1) frange = 1;
      fend = fstart + frange;
   }
   fhalf = fstart + frange/2;
   if (fend <= fstart) fend = fhalf+1;
   if (fhalf > fend) fend = fhalf+1;
   if (fend > f_max) f_max = fend;
} /* lsetframes */
/************************************************/

void lcolx(int lcentre)
/*
    find column number of each symbol
	-5 = L arm
	-3 = L gesture
    -1 = L support
	 1 = R support
	 3 = R gesture
	 5 = R arm
	
    called by linter,
*/
{
   int k;
   int kc;
   int kwx;

   for (k = 0; k < nlabs; ++k)
   {
      kwx = lbn[k].x + (lbn[k].w/2);
      kc = (kwx - lcentre)/STEP;
      if (kwx < lcentre)
         --kc;
      else
         ++kc;
      lbn[k].c = kc;
   }
} /* lcolx */
/************************************************/

void lbnread(void)
/*
   read .lbn laban score file

   called by linter,
*/
{
   int j;
   int i,x,y,s,w,h;
   char d;
   char m0,m1,m2,m3;

   j = 0;
   xmax = 0;
   xmin = 10000;
	if ( ( infile = fopen( finname, "r" ) ) == NULL )
	{
		printf("lbnread oops\n");
a: goto a;
	}
   while ((j < LMAX) && (fgets(buf,BMAX,infile) != NULL))
   {
		strcpy(lbnline[j],buf);
		sscanf(buf,"%c%c%c%c %d %d %d %d %d %d %c",
             &m0,&m1,&m2,&m3,&i,&x,&y,&s,&w,&h,&d);
		if (m0 != '#')
		{
            lbn[j].m = m0;
            if ((m0 == 'P')&&(m1 == 'a'))
            lbn[j].m = Path;
            lbn[j].i = i;
            lbn[j].x = x;
            lbn[j].y = y;
            lbn[j].w = w;
            lbn[j].h = h;
            lbn[j].s = s;
            lbn[j].b = -1;
            lbn[j].l = j;
            lbn[j].a = TODO;
            lbn[j].x2 = x+w;
            lbn[j].y2 = y+h;
            lbn[j].d = BLANK;
            if (d =='M') lbn[j].d = MED;
            if (d =='L') lbn[j].d = LOW;
            if (d =='H') lbn[j].d = HIGH;
            if (x < xmin) xmin = x;
            if (x+w > xmax) xmax = x+w;
            if (j >= LMAX)
            {
               printf("\nBEWARE: score truncated at line %d\n",j);
               printf("more than %d laban score items\n",LMAX);
            }
            ++j;
		}
   } /* while reading next line */
   nlabs = j;
	printf("\n   lbnread: %d lbn symbols\n",nlabs);
}  /* lbnread */
/************************************************/

void lassign(void)
/*
   assign global variables

   called by laction, lsorty, lbent,
*/
{
      ja = lbn[j].a;
      jb = lbn[j].b;
      jc = lbn[j].c;
      jd = lbn[j].d;
      jh = lbn[j].h;
      ji = lbn[j].i;
      jl = lbn[j].l;
      jm = lbn[j].m;
      js = lbn[j].s;
      jw = lbn[j].w;
      jx = lbn[j].x;
      jy = lbn[j].y;
      jx2 = lbn[j].x2;
      jy2 = lbn[j].y2;
} /* lassign */
/**********************************************/

void lsorty(void)
/*
   sort score symbols into ascending order of 'y'
   (bubble sort)
   find maxy, and fill yj table

   called by linter,
   calls     lassign,
*/
{
   int k;
   int last;
   int y;

   for (j = 0; j < (nlabs-1); ++j)
   {
      for (k = j; k < nlabs; ++k)
      {
         if (lbn[k].y < lbn[j].y)
         {
            lassign();
            lbn[j].a = lbn[k].a;
            lbn[j].b = lbn[k].b;
            lbn[j].c = lbn[k].c;
            lbn[j].d = lbn[k].d;
            lbn[j].h = lbn[k].h;
            lbn[j].i = lbn[k].i;
            lbn[j].l = lbn[k].l;
            lbn[j].m = lbn[k].m;
            lbn[j].s = lbn[k].s;
            lbn[j].w = lbn[k].w;
            lbn[j].x = lbn[k].x;
            lbn[j].y = lbn[k].y;
            lbn[j].x2 = lbn[k].x2;
            lbn[j].y2 = lbn[k].y2;
            lbn[k].a = ja;
            lbn[k].b = jb;
            lbn[k].c = jc;
            lbn[k].d = jd;
            lbn[k].h = jh;
            lbn[k].i = ji;
            lbn[k].l = jl;
            lbn[k].m = jm;
            lbn[k].s = js;
            lbn[k].w = jw;
            lbn[k].x = jx;
            lbn[k].y = jy;
            lbn[k].x2 = jx2;
            lbn[k].y2 = jy2;
            strcpy(buf,lbnline[j]);
            strcpy(lbnline[j],lbnline[k]);
            strcpy(lbnline[k],buf);
         }
      }
   }
   ymax = 0;
   for (j = 0; j < nlabs; ++j)
       if (((lbn[j].y2) > ymax)&&(lbn[j].m != Stav))
            ymax = lbn[j].y2+1;
   for (y = 0; y < ymax; ++y)
       yj[y] = -1;
   for (j = 0; j < nlabs; ++j)
   {
       y = lbn[j].y;
	   if (y < 0) y = 0;
       if (yj[y] < 0) yj[y] = j;
   }
   last = 0;
   for (y = 0; y < ymax; ++y)
   {
       if (yj[y] < 0)
            yj[y] = last;
       else
            last = yj[y];
   }
}   /* lsorty */
/************************************************/

void lsortx(int stff[LMAX][2], int nstff)
/*
   sort staff symbols into ascending order of 'x'
   (bubble sort)

   called by lfindstaff,
*/
{
   int j;
   int k;
   int s0,s1;

   for (j = 0; j < (nstff-1); ++j)
   {
      for (k = j; k < nstff; ++k)
      {
         if (stff[k][1] < stff[j][1])
         {
            s0 = stff[j][0];
            s1 = stff[j][1];
            stff[j][0] = stff[k][0];
            stff[j][1] = stff[k][1];
            stff[k][0] = s0;
            stff[k][1] = s1;
         }
      }
   }
}   /* lsortx */
/************************************************/

int loverlap(int p1j, int p2j, int p1k, int p2k)
/*
   check how much symbols j and k overlap in dimension p

   called by lbent, lleggesture, lhastap, lhasgesture,
             lseeksym, ldopivot,
			 
   calls lgetout,
*/
{
   int p1max,p2min;
   int lap;

   if ((p1j > p2j)||(p1k > p2k))
   {
	   printf("OOPS: loverlap %d %d %d %d\n",
		   p1j,p2j,p1k,p2k);
	   lgetout(j);
   }
   lap = FALSE;
   if (p1k < p1j)
      p1max = p1j;
         else
            p1max = p1k; 
   if (p2k < p2j)
      p2min = p2k;
         else
            p2min = p2j;
   lap = p2min - p1max;
   return(lap);
} /* loverlap */
/********************************************/

void lfindstaff(void)
/*
    find the centres of the staves

    called by linter,
	calls     lsortx, lgetout,
*/
{
   int j,jp,jq;
   int k,kp,kq;
   int staffstart;
   int nstaffstart;
   int nstff;
   int stff[TMAX][2];

   k = 0;
   staffstart = 0;
   for (j = 0; j < nlabs; ++j)
   {
      if (lbn[j].m == Stav)
      {
         stff[k][0] = j;
         stff[k][1] = lbn[j].x;
         if (lbn[j].y > staffstart)
            staffstart = lbn[j].y;
         nstaffstart = j;
         ++k;
         lbn[j].a = DONE;
      }
   }
   if (k < 3)
   {
      printf("lfindstaff: only %d staff lines\n",k);
      lgetout(1);
      if (ok == 1) goto rtrn;
   }
   if (k > TMAX)
   {
      printf("lfindstaff: %d staff lines, max %d\n",k,TMAX);
      lgetout(1);
      if (ok == 1) goto rtrn;
   } 
   nstff = k;
   lsortx(stff,nstff);
   k = 0;
   for (j = 1; j < nstff; j += 3)
   {
      staff[k][0] = stff[j][0];
      staff[k][1] = stff[j-1][1];
      staff[k][2] = stff[j][1];
      staff[k][3] = stff[j+1][1];
      staff[k][4] = -1;
      staff[k][5] = TODO;
      ++k;
   }
   nstaff = k;
   stmiddle = (staff[0][2] + staff[nstaff-1][2])/2;
   npins = 0;
   // seek pins under center stafflines
   for (j = 0; j < nstaffstart; ++j)
   {
      if (lbn[j].m == Pins)
      {
         jp = lbn[j].x;
         jq = lbn[j].x2;
         pins[npins][0] = j;
         pins[npins][1] = -1;
         for (k = 0; k < nstaff; ++k)
         {
            kp = staff[k][2] - 1;
            kq = kp+2;
            if (loverlap(jp,jq,kp,kq) > 0)
            {
               if (lbn[j].d == 0)
               {
                  staff[k][4] = MAN;
                  pins[npins][1] = k;
				  lbn[j].a = DONE;
               }
               else
               {
                  staff[k][4] = WOMAN;
                  pins[npins][1] = k;
				  lbn[j].a = DONE;
               } /* empty pin */
            } /* pin under central staff */
         } /* k : staff lines */
         ++npins;
      } /* a pin found */
   } /* j */
   if (nstaff < 1)
	   printf("No staves found\n");
   else
   for (j = 0; j < nstaff; ++j)
   {
		if (j == 0)
			printf("\n");
      printf("staff %d: ",j+1);
      if (staff[j][4] == MAN)
         printf(" man\n");
      else
      if (staff[j][4] == WOMAN)
         printf(" woman\n");
      else
         printf(" no gender\n");
   }
rtrn: ;
}   /* lfindstaff */
/***************************************************/

void lfindystart(void)
/*
   find y position of first double bar line

   called by linter,
*/
{
   int j;

   ystart = -1;
/*
   seek initial double bar line -
*/
   for (j = 0; ((j < nlabs)&&(ystart < 0)); ++j)
   {
      if ((lbn[j].m == Bars) && (lbn[j].d == LOW))
	     ystart = lbn[j].y + 1;
   }
/*
   if none, seek any bar line -
*/
   if (ystart < 0)
   {
      for (j = 0; ((j < nlabs)&&(ystart < 0)); ++j)
         if (lbn[j].m == Bars) ystart = lbn[j].y + 1;
   }
/*
   if none, seek any supporting direction symbol -
*/
   if (ystart < 0)
   {
      for (j = 0; ((j < nlabs)&&(ystart < 0)); ++j)
         if ((lbn[j].m == Dirn) &&
	        ((lbn[j].c == 1) || (lbn[j].c == -1)) )
	           ystart = lbn[j].y;
   }
   ystart -= 3;
   if (ystart < 0)
   {
      printf(
         "linter : findystart finds no direction support symbols\n");
      lgetout(1);
      ystart = 0;
   }
} /* lfindystart */
/**************************************************/

void lchange(char d)
/*
    change bend in ankles,legs, and hips while stepping

    called by ldostep,
*/
{
   if (d == 'L')
   {
      fprintf(nudesfile,
         "repeat    %3d %3d set tcls1 tlow1\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set tcls2 tlow2\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set tcls3 tlow3\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set lcls1 llow1\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set lcls2 llow2\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set lcls3 llow3\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set fcls1 flow1\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set fcls2 flow2\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set fcls3 flow3\n",fstart,fend);
   }
   else if (d == 'M')
   {
      fprintf(nudesfile,
         "repeat    %3d %3d set tcls1 trlx1\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set tcls2 trlx2\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set tcls3 trlx3\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set lcls1 lrlx1\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set lcls2 lrlx2\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set lcls3 lrlx3\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set fcls1 frlx1\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set fcls2 frlx2\n",fstart,fend);
      fprintf(nudesfile,
         "repeat    %3d %3d set fcls3 frlx3\n",fstart,fend);
   }
   else if (d == 'H')
   {
      if ((ji != 1)&&(ji != 10))
      {
         fprintf(nudesfile,
            "repeat    %3d %3d set tcls1 thig1\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set tcls2 thig2\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set tcls3 thig3\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set lcls1 lhig1\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set lcls2 lhig2\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set lcls3 lhig3\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set fcls1 fmed1\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set fcls2 fmed2\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set fcls3 fmed3\n",fstart,fend);
      }
      else
      if ((ji != 5)&&(ji != 6))
      {
         fprintf(nudesfile,
            "repeat    %3d %3d set tcls1 trlx1\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set tcls2 trlx2\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set tcls3 trlx3\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set lcls1 lrlx1\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set lcls2 lrlx2\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set lcls3 lrlx3\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set fcls1 fhig1\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set fcls2 fhig2\n",fstart,fend);
         fprintf(nudesfile,
            "repeat    %3d %3d set fcls3 fhig3\n",fstart,fend);
      }
   }
   else
   {
      printf("linter: funny depth parameter, frame %d\n",
		  fstart);
      lgetout(1);
   }
} /* lchange */
/*********************************************/

void lsetcoords(void)
/*
   set the coordinate system for a step
	
	called by ldostep, lleggesture
	*/
{
	if ( dofig == MAN )
	{
		if (mspace == false)
			fprintf( nudesfile, "repeat    %3d %3d set    coords mpelvis\n",
				fstart, fend);
		else
			fprintf( nudesfile, "repeat    %3d %3d set    coords mspace\n",
				fstart, fend);
	}
	else
	{
		if (wspace == FALSE)
			fprintf( nudesfile, "repeat    %3d %3d set    coords wpelvis\n",
				fstart, fend);
		else
			fprintf( nudesfile, "repeat    %3d %3d set    coords wspace\n",
				fstart, fend);
	}	/* dofig == WOMAN */
} /* lsetcoords */
/************************************************/

void ldostep(void)
/*
   create NUDES calls for steps on score

   called by laction,
   calls     lsetframes, lfindnext, lsetcoords
*/
{
	int b;
	int havestep;
	int k;
	int n;

	b = 0;
	if ( ( jm == Dirn ) && ( ( jc == -1 ) || ( jc == 1 ) ) )
	{
		havestep = TRUE;
		k = lfindnext ( jc, jy + jh, jy + 2 * jh );
		if ( ji > 5 )
			n = ji - 5;
		else
			n = ji + 5;
		fprintf( nudesfile, "*\n" );
		if ( ( jc == -1 ) &&
			( ( ji == 1 ) || ( ji == 5 ) || ( ji == 3 ) ) )
		{
			printf( "dostep: funny symbol in left support column, line %d, bar %d\n",
				j, nbar );
			printf( "%3d %3d %3d %3d %3d %3d %d\n",
				jm, ji, jy, js, jw, jh, jd );
		}
		else if ( ( jc == 1 ) &&
			( ( ji == 10 ) || ( ji == 6 ) || ( ji == 8 ) ) )
		{
			printf( "dostep: funny  symbol in right support column, line %d, bar %d\n",
				j, nbar );
			printf( "%3d %3d %3d %3d %3d %3d %d\n",
				jm, ji, jy, js, jw, jh, jd );
		}
		else
		{
			fprintf( nudesfile, "repeat    %3d %3d set    fend  %d\n",
				fstart, fend, frange );
			fprintf( nudesfile, "repeat    %3d %3d call   %s\n",
				fstart, fend, risesub[jd] );
			lsetcoords();
			if ( jc > 0 )
				fprintf( nudesfile, "repeat    %3d %3d call   forright\n",
					fstart, fend );
			else
				fprintf( nudesfile, "repeat    %3d %3d call   forleft\n",
					fstart, fend );
			if ( ( ji == 1 ) || ( ji == 10 ) )
				fprintf( nudesfile, "call      %3d %3d forward\n",
					fstart, fend );
			if ( ji == 3 )
				fprintf( nudesfile, "call      %3d %3d rside\n",
					fstart, fend );
			if ( ji == 8 )
				fprintf( nudesfile, "call      %3d %3d lside\n",
					fstart, fend );
			if ( ( ji == 5 ) || ( ji == 6 ) )
				fprintf( nudesfile, "call      %3d %3d back\n",
					fstart, fend );
			if ( ji == 2 )
				fprintf( nudesfile, "call      %3d %3d rfordiag\n",
					fstart, fend );
			if ( ji == 9 )
				fprintf( nudesfile, "call      %3d %3d lfordiag\n",
					fstart, fend );
			if ( ji == 4 )
				fprintf( nudesfile, "call      %3d %3d rbacdiag\n",
					fstart, fend );
			if ( ji == 7 )
				fprintf( nudesfile, "call      %3d %3d lbacdiag\n",
					fstart, fend );
			if ( ji == 11 )
				fprintf( nudesfile, "call      %3d %3d close\n",
					fstart, fend );
			lbn[j].a = DONE;
			pstart = fstart;
			pend = fend;
		}
		rise = jd;
		prevc = jc;
		previ = ji;
	} /* column OK */
}     /* ldostep */
/****************************************************/

int lhastap(int j)
/*
   check if symbol j has overlapping ground contact
   
   called by ldopivot,
*/
{
   int t;
   int yk;
   int k;
   int kc,ki,ky,ky2;
   char km;

   t = -1;
   yk = jy - jh;
   if (yk < 1) yk = 1;
   for (k = yj[yk];
	   ((t < 0)&&(k < nlabs)&&(lbn[k].y < jy2)); ++k)
   {
      km = lbn[k].m;
      if (km == Misc)
      {
         ki = lbn[k].i;
         if ((ki >= 4) && (ki <= 9))
         {
            kc = lbn[k].c;
            if ((kc == -3)||(kc == -2)||(kc == 2)||(kc == 3))
            {
               ky = lbn[k].y;
               ky2 = ky + lbn[k].h;
               if (loverlap(jy,jy2,ky,ky2) > 0)
               {
                  t = k;
               } /* overlap = TRUE*/
            } /* in leg gesture column */
         } /* tap symbol */
      } /* tap menu */
   } /* k */
   return(t);
} /* lhastap */
/*******************************************************/

int lhasgesture(int j)
/*
   check if symbol j has overlapping gesture
   
   called by ldopivot,
   calls     loverlap,
*/
{
   int kc,ky,ky2;
   int k;
   int g;
   char km;

   g = -1;
   for (k = 0; ((g < 0)&&(k < nlabs)); ++k)
   {
      km = lbn[k].m;
      if (km == Dirn)
      {
         kc = lbn[k].c;
         if ((kc == -3)||(kc == 3))
         {
            ky = lbn[k].y;
            ky2 = lbn[k].y2;
            if (loverlap(jy,jy2,ky,ky2) > 0)
               g = k;
         }
      }
   }
   return(g);
} /* lhasgesture */
/*******************************************************/

void lleggesture(void)
/*
   do gestures of the legs

   called by laction,
   calls     lsetframes, lgetout, lsetcoords,

   Volm   1  RELAX
   Volm   3  BENT
   Volm   2  STRAIGHT
   Volm   4  STRETCH
   Volm   7  hold
*/
{
   if ((jc == -3)||(jc == 3))
   {
      {
         if ((jd < 0) || (jd > 2))
         {
            printf("OOPS: dogesture height problem line %d\n",j);
            printf("%3d %3d %3d %3d %3d %3d %3d %d\n",
	             jm,ji,jx,jy,js,jw,jh,jd);
            lgetout(j);
            if (ok == 1) goto rtrn;
         } /* level funny */
         fprintf(nudesfile,"*\n");
         if  (ji==11)
            fprintf(nudesfile,"* close without weight");
         else
         if ((ji==1)||(ji==10))
            fprintf(nudesfile,"* forward gesture");
         else
         if ((ji==2)||(ji==9))
            fprintf(nudesfile,"* forward diagonal gesture");
         else
         if ((ji==3)||(ji==8))
            fprintf(nudesfile,"* sideways gesture");
         else
         if ((ji==4)||(ji==7))
            fprintf(nudesfile,"* back diagonal gesture");
         else
         if ((ji==5)||(ji==6))
            fprintf(nudesfile,"* backward gesture");
//
         if (jd == LOW)
            fprintf(nudesfile," low\n");
         if (jd == MED)
            fprintf(nudesfile," middle\n");
         if (jd == HIGH)
            fprintf(nudesfile," high\n");
//
         if (jc < 0)
         {
            if ((ji <= 1)||(ji == 3)||(ji == 5)||(ji > 11))
            {
               printf("OOPS: dogesture direction problem line %d\n",j);
               printf("%3d %3d %3d %3d %3d %3d %3d %3d %d\n",
                  jm,ji,jx,jy,js,jw,jh,jb,jd);
               lgetout(1);
               if (ok == 1) goto rtrn;
            } /* i wrong */
            fprintf(nudesfile,
               "repeat    %3d %3d call   forleft * left = b\n",
                  fstart,fend);
         } /* left side */
         else if (jc > 0)
         {
            if ((ji < 1)||(ji == 6)||(j == 8)||(ji == 10)||(ji > 11))
            {
               printf("OOPS: dogesture direction problem line %d\n",j);
               printf("%3d %3d %3d %3d %3d %3d %3d %3d %d\n",
                  jm,ji,jx,jy,js,jw,jh,jb,jd);
               lgetout(1);
               if (ok == 1) goto rtrn;
            } /* i wrong */
            fprintf(nudesfile,
               "repeat    %3d %3d call   forright * right = b\n",
                  fstart,fend);
         } /* right side */
//
         fprintf(nudesfile,"repeat    %3d %3d centre afoot  %s\n",
                  fstart,fend,xyz[dofig]);
//
         if (ji == 11)
         {
            fprintf(nudesfile,"repeat    %3d %3d call   %s\n",
                  fstart,fend,risesub[rise]);
            fprintf(nudesfile,"repeat    %3d %3d set    fend  %d\n",
                  fstart,fend,frange);
				lsetcoords();
            fprintf(nudesfile,"call      %3d %3d close\n",
                  fstart,fend);
         } /* close without weight */
         else
         {
            fprintf(nudesfile,
               "quadratic %3d %3d bendto bthigh bhip   pelvis %d %d %d\n",
                  fstart,fend,stt[jd][ji][0],stt[jd][ji][1],stt[jd][ji][2]);
            if ((jd == LOW)&&((ji == 1)||(ji == 3)||(ji == 8)||(ji == 10))||(jb == 2)||(jb == 4))
               fprintf(nudesfile,
                  "linear    %3d %3d bendto bleg   bknee  bthigh lhig1 lhig2 lhig3\n",
                      fhalf,fend);
            else
               fprintf(nudesfile,
                  "linear    %3d %3d bendto bleg   bknee  bthigh lrlx1 lrlx2 lrlx3\n",
                      fhalf,fend);
            fprintf(nudesfile,
               "linear    %3d %3d bendto bfoot  bankle bleg   fhig1 fhig2 fhig3\n",
                  fhalf,fend);
         } /* doing a leg gesture */
         if ((ji != 11)&&(hold == NO)||(st < 1))
            fprintf(nudesfile,
               "repeat    %3d %3d moveto fig    afoot  %s\n",
	            fstart,fend,xyz[dofig]);
         lbn[j].a = DONE;
      } /* no tap and pivot */
   } /* c OK */
rtrn: ;
} /* lleggesture */
/***************************************************/

void ldoarms(void)
/*
   do movements of the arms

   called by ldolimb,
   calls     lsetframes,
*/
{
   int absjc;

   if (jc < 0) absjc = -jc; else absjc = jc;
   if ((absjc > 3)&&(absjc < 7))
   {
      if (jm == Dirn)
      {
         fprintf(nudesfile,"*\n* arms\n");
         if ((jd < 0) || (jd > 2))
         {
            printf("ldoarms problem line %d, bar %d\n",j,nbar);
            printf("%c %3d %3d %3d %3d %3d %3d %d\n",
	           jm,ji,jx,jy,js,jw,jh,jd);
            lgetout(1);
            if (ok == 1) goto rtrn;
         }
         if (jc < 0) // left arm
         {
            if (jb == RELAX)
            {
					fprintf(nudesfile,
                  "quadratic %3d %3d bendto luarm  lshldr shldrs %3d %3d %3d\n",
                     fstart,fend,arlx[jd][ji][0],arlx[jd][ji][1],arlx[jd][ji][2]);
					fprintf(nudesfile,
                  "quadratic %3d %3d bendto llarm  lelbow luarm  %3d %3d %3d\n",
                     fstart,fend,0,0,45);
               if (dofig == MAN)
					{  
						fprintf(nudesfile,
                     "quadratic %3d %3d bendto lhand  lwrist llarm  %3d %3d %3d\n",
                        fstart,fend,0,0,0);
					} /* man */
               else
               {
						fprintf(nudesfile,
                     "quadratic %3d %3d bendto lhand  lwrist llarm  %3d %3d %3d\n",
                        fstart,fend,270,0,150);
					} /* woman */
            }
            else
            if (jb == BENT)
            {
               if (ji == 11)
               {
                   fprintf(nudesfile,
                      "quadratic %3d %3d bendto luarm  lshldr shldrs %3d %3d %3d\n",
                         fstart,fend,abnt[jd][0][0],abnt[jd][0][1],abnt[jd][0][2]);
                   fprintf(nudesfile,
                      "quadratic %3d %3d bendto llarm  lelbow luarm  %3d %3d %3d\n",
                         fstart,fend,0,0,70);
               }
               else
               {
                   fprintf(nudesfile,
                      "quadratic %3d %3d bendto luarm  lshldr shldrs %3d %3d %3d\n",
                         fstart,fend,abnt[jd][ji][0],abnt[jd][ji][1],abnt[jd][ji][2]);
                   fprintf(nudesfile,
                      "quadratic %3d %3d bendto llarm  lelbow luarm  %3d %3d %3d\n",
                         fstart,fend,0,0,90);
               } /* ji != 11 */
            }
            else
            {
               fprintf(nudesfile,
                  "quadratic %3d %3d bendto llarm  lelbow luarm  %3d %3d %3d\n",
                     fstart,fend,0,0,0);
               fprintf(nudesfile,
                  "quadratic %3d %3d bendto luarm  lshldr shldrs %3d %3d %3d\n",
                     fstart,fend,stt[jd][ji][0],stt[jd][ji][1],stt[jd][ji][2]);
            }
         }
         else // if (jc > 0) =  right arm
         {
            if (jb == RELAX)
            {
					fprintf(nudesfile,
                  "quadratic %3d %3d bendto ruarm  rshldr shldrs %3d %3d %3d\n",
                     fstart,fend,arlx[jd][ji][0],arlx[jd][ji][1],arlx[jd][ji][2]);
					fprintf(nudesfile,
                  "quadratic %3d %3d bendto rlarm  relbow ruarm  %3d %3d %3d\n",
                     fstart,fend,0,0,45);
               if (dofig == MAN)
					{  
						fprintf(nudesfile,
                     "quadratic %3d %3d bendto rhand  rwrist rlarm  %3d %3d %3d\n",
                        fstart,fend,0,0,0);
					} /* man */
               else
               {
						fprintf(nudesfile,
                     "quadratic %3d %3d bendto rhand  rwrist rlarm  %3d %3d %3d\n",
                        fstart,fend,270,0,150);
			      } /* woman */

            } /* relaxed */
            else
            if (jb == BENT)
            {		   
               fprintf(nudesfile,
                  "quadratic %3d %3d bendto ruarm  rshldr shldrs %3d %3d %3d\n",
                     fstart,fend,abnt[jd][ji][0],abnt[jd][ji][1],abnt[jd][ji][2]);
               if (ji == 11)
                   fprintf(nudesfile,
                      "quadratic %3d %3d bendto rlarm  relbow ruarm  %3d %3d %3d\n",
                         fstart,fend,0,0,70);
               else
                   fprintf(nudesfile,
                      "quadratic %3d %3d bendto rlarm  relbow ruarm  %3d %3d %3d\n",
                         fstart,fend,0,0,90);
            } /* bent */
            else
            {
               fprintf(nudesfile,
                  "quadratic %3d %3d bendto rlarm  relbow ruarm  %3d %3d %3d\n",
                     fstart,fend,0,0,0);
               fprintf(nudesfile,
                  "quadratic %3d %3d bendto ruarm  rshldr shldrs %3d %3d %3d\n",
                     fstart,fend,stt[jd][ji][0],stt[jd][ji][1],stt[jd][ji][2]);
               fprintf(nudesfile,
                  "quadratic %3d %3d bendto rhand  rwrist rlarm  %3d %3d %3d\n",
                     fstart,fend,0,0,0);
            } /* not bent or relaxed */
         } /* right arm */
      } /* Dirn symbol */
   } /* in arm column */
   lbn[j].a = DONE;
rtrn: ;
} /* ldoarms */
/***************************************************/

void lspotturn(int j, int piv, int fstart, int fend, int g)
/*
  maintain straight non-standing foot with ground 
  contact during turn.

  called by ldopivot,
*/
{
   int gc,gi;

   gi = lbn[g].i;
   gc = lbn[g].c;
   fprintf(nudesfile,"*\n* spot turn-\n");
   if (gc < 0)
      fprintf(nudesfile,
         "repeat    %3d %3d call   forleft * left = b\n",fstart,fend);
   else
      fprintf(nudesfile,
         "repeat    %3d %3d call   forright * right = b\n",fstart,fend);
   fprintf(nudesfile,
      "repeat    %3d %3d centre afoot  %s\n",
         fstart,fend,xyz[dofig]);
   fprintf(nudesfile,
      "linear    %3d %3d spinby fig    afoot  pelvis %d y\n",
         fstart,fend,piv);
   fprintf(nudesfile,
      "linear    %3d %3d bendto bthigh bhip   pelvis %d %d %d\n",
	      fstart,fend,stt[0][ji][0],stt[0][ji][1],stt[0][ji][2]);
   fprintf(nudesfile,
      "repeat    %3d %3d ground fig\n",fstart,fend);
   if ((hold == NO)||(st < 1))
      fprintf(nudesfile,
       "repeat    %3d %3d moveto fig    afoot  %s\n",
         fstart,fend,xyz[dofig]);
   fprintf(nudesfile,
      "linear    %3d %3d bendto bfoot  bankle bleg   fhig1 fhig2 fhig3\n",
	     fstart,fhalf);
   fprintf(nudesfile,
      "repeat    %3d %3d drag   bfoot  bfoot  bankle bleg  x\n",
         fhalf,fend);
   lbn[j].a = DONE;
   lbn[t].a = DONE;
} /* lspotturn */
/******************************************************/

int lgetpin(void)
/*
    seek a pin in a rotation sign
	
	called by ldolimb, ldopivot,
	calls     loverlap,
*/
{
    int k,ki;
    int piv;
    int ymost;
    int xlap,ylap;

    ki = -123;
    ymost = -1;
    for (k = yj[jy-jh]; lbn[k].y < jy2; ++k)
    {
         if (lbn[k].m == Pins)
         {
             xlap = loverlap(jx,jx2,lbn[k].x,lbn[k].x2);
             ylap = loverlap(jy,jy2,lbn[k].y,lbn[k].y2);
             if ((xlap > 0) && (ylap > ymost))
             {
                ki = lbn[k].i;
                ymost = ylap;
             } /* pin overlaps more than previous pins */
         } /* got a pin */
    } /* k loop looking for overlapping pin */
	 piv = 0;
    if ((ki > 0)&&(ki <= 9))
    {
       if (ji == 1) piv = -45*(9-ki);
       if (ji == 2) piv = 45*(ki-1);
       if (ki == 1) piv = 360;
    }
    return(piv);
} /* lgetpin */
/***************************************************/

void ldopivot(void)
/*
   do turns in the support columns

   called by laction,
   calls     lsetframes, lspotturn, lhasgesture, 
             lhastap,    lgetpin,
*/
{
   int g,t;
   int piv;

   if ( (jm == Rotn)&&(nbar > 0)&&
	 ((jc == -2)||(jc == -1)||(jc == 1)||(jc == 2)) )
   {
      piv = lgetpin();
      if (fstart < 1) fstart = 1;
      g = lhasgesture(j);
      t = lhastap(j);
      if ((g > 0)&&(t > 0))
      {
         lspotturn(j,piv,fstart,fend,g);
         pstart = fstart;
         pend = fend;
      }
      else
      {
         fprintf(nudesfile,"*\n* pivot\n");
         if (jc < 0)
            fprintf(nudesfile,
               "repeat    %3d %3d call   forleft * b = left\n",fstart,fend);
         else
            fprintf(nudesfile,
               "repeat    %3d %3d call   forright * b = right\n",fstart,fend); 	
         fprintf(nudesfile,
            "repeat    %3d %3d centre bfoot  %s\n",
                fstart,fstart+1,xyz[dofig]);
         fprintf(nudesfile,
            "linear    %3d %3d spinby fig    bfoot  pelvis %d y\n",
               fstart,fend,piv);
         if ((hold == NO)||(st < 1))
			 fprintf(nudesfile,
                "repeat    %3d %3d moveto fig    bfoot  %s\n",
                  fstart,fend,xyz[dofig]);
         if (hold == PR)
             hold = NO;
         pstart = fend;
         pend = fend+1;
      } /* spotturn == false */
   }
} /* ldopivot */
/**************************************************/

int lseeksym(char m, int i, int x1, int x2, int y3, int y4)
/*
     seek a symbol of menu m, item i,
	 overlapping box x1,x2,y1,y2.

	 called by lbows, lsethold,
	 call      loverlap,
*/
{
   int lap;
   int kstart;
   int k,kx,kx2,ky,ky2;
   int y1,y2;

   lap = -1;
   if (y3 < 0) y1 = 0; else y1 = y3;
   if (y4 < 0) y2 = 0; else y2 = y4;
   kstart = y1 - 2*STEP;
   if (kstart < 1) kstart = 1;
   for (k = yj[kstart]; ((lap < 0)&&(lbn[k].y < y2)); ++k)
   {
      kx = lbn[k].x;
      kx2 = lbn[k].x2;
      ky = lbn[k].y;
      ky2 = lbn[k].y2;
      if ((lbn[k].m == m )&&(lbn[k].i == i))
      {
         if ((loverlap(x1,x2,kx,kx2) > 0)
            && (loverlap(y1,y2,ky,ky2) > 0))
         {
            lap = k;
         }
      } /* m and i true */
   } /* k loop */
   return(lap);
}  /* lseeksym */
/***************************************************/

void lbows(void)
/*
      detect and flag the various contact bows.

	  called by linter,
	  calls     lseeksym,

Relevant symbols:-
     m     i
    Misc   1  bow
    Limb   4  lhand
    Limb   9  rhand
    Area   1  top/front 
    Area   5  back/bottom
    Volm   1  relax
    Volm   2  bent
    Volm   3  straight
    Volm   4  stretch
    Volm   7  hold
*/
{
   int centre;
   int held,front,back;
   int mlhand,mrhand,wlhand,wrhand;

   centre = (staff[0][2] + staff[1][2])/2;
   for (j = 0; j < nlabs; ++j)
   {
      if ((lbn[j].m == Misc)&&(lbn[j].i == 1))
      {
          lassign();
          held = lseeksym(Volm,1,jx,jx2,jy-STEP,jy2);
	  if (held > 0)
          {
              mlhand = lseeksym(Limb,4,jx-STEP/2,jx+STEP/2,jy,jy2+STEP);
              mrhand = lseeksym(Limb,9,jx-STEP/2,jx+STEP/2,jy,jy2+STEP);
              wlhand = lseeksym(Limb,4,jx2-STEP/2,jx2+STEP/2,jy,jy2+STEP);
              wrhand = lseeksym(Limb,9,jx2-STEP/2,jx2+STEP/2,jy,jy2+STEP);
              front  = lseeksym(Area,1,jx-STEP/2,jx+STEP/2,jy,jy2+STEP);
              if (front < 0)
                 front  = lseeksym(Area,1,jx2-STEP/2,jx2+STEP/2,jy,jy2+STEP);
              if (front < 0)
                 front  = lseeksym(Area,2,jx-STEP/2,jx+STEP/2,jy,jy2+STEP);
              if (front < 0)
                 front  = lseeksym(Area,2,jx2-STEP/2,jx2+STEP/2,jy,jy2+STEP);
              back   = lseeksym(Area,5,jx-STEP/2,jx+STEP/2,jy,jy2+STEP);
              if (back < 0)
                 back  = lseeksym(Area,5,jx2-STEP/2,jx2+STEP/2,jy,jy2+STEP);
              jb = 0;
              if (front > 0)
              {
                 jb = FRONT;
                 lbn[front].a = DONE;
              }
              else 
              if (back > 0)
              {
                 jb = BACK;
                 lbn[back].a = DONE;
              }
              if (mlhand > 0) jb += MLHAND;
              if (mrhand > 0) jb += MRHAND;
              if (wlhand > 0) jb += WLHAND;
              if (wrhand > 0) jb += WRHAND;
              if (jb <= 0)
                 fprintf(nudesfile,"* OOPS: lbows: bow %d with no contacts\n",j);
              else
              {
                 if (mlhand > 0) lbn[mlhand].b = jb;
                 if (mrhand > 0) lbn[mrhand].b = jb;
                 if (wlhand > 0) lbn[wlhand].b = jb;
                 if (wrhand > 0) lbn[wrhand].b = jb;
              }
           } /* held */
           fprintf(nudesfile,"*  lbowsb %d %d %d %d %d %d %d %d %d\n",
              j+1,held,front,back,mlhand,mrhand,wlhand,wrhand,jb);
      } /* contact bow */
   } /* j */
} /* lbows */
/****************************************/

void lstart(void)
/*
   seek pins denoting starting positions.

   called by linter,
*/
{
   int k;
   int p;
   int dx,dz;
   int mx,my;
   int wx,wy;

   mx = -123;
   my = -123;
   wx = -123;
   wy = -123;
   if (nm > 0)
      fprintf(nudesfile,"\n*\ncall        0   1 doman\n");
   else
      fprintf(nudesfile,"\n*\ncall        0   1 dowoman\n");
   fprintf(nudesfile,"call        0   1 forleft\n");
   for (k = 0; k < npins; ++k)
   {
      if (pins[k][1] < 0)
      {
         p = pins[k][0];
         ji = lbn[p].i;
         if (lbn[p].d == LOW)
         {
            mx = lbn[p].x;
            my = lbn[p].y;
            if (nm > 0)
               fprintf(nudesfile,
                  "*\nquadratic   0   1 spinby man    mlfoot  mpelvis %d y\n",
                  (ji-1)*45);
         }
         else
         {
            wx = lbn[p].x;
            wy = lbn[p].y;
            if (nw > 0)
               fprintf(nudesfile,
                  "*\nquadratic   0   1 spinby woman  wrfoot  wpelvis %d y\n",
                  (ji-1)*45);
         }
         if ((wx > 0)&&(mx > 0)&&(wy > 0)&&(my > 0))
         {
            dx = ((wx - mx)*2)/3;
            dz = (wy - my)/2;
            if (nmw > 0)
            {
               fprintf(nudesfile,"*\n");
               fprintf(nudesfile,"repeat      0   1 centre mpelvis  kx ky kz\n");
               fprintf(nudesfile,"repeat      0   1 moveto woman    wpelvis kx ky kz\n");
               fprintf(nudesfile,"repeat      0   1 axes   wpelvis  cx cy cz\n");
               fprintf(nudesfile,"linear      0   1 set    dx %d\n",dx);
               fprintf(nudesfile,"linear      0   1 set    dz %d\n",dz);
               fprintf(nudesfile,"linear      0   1 mult   wx   dx  cx\n");
               fprintf(nudesfile,"linear      0   1 mult   wz   dz  cx\n");
               fprintf(nudesfile,"repeat      0   1 centre wpelvis  cx cy cz\n");
               fprintf(nudesfile,"linear      0   1 moveby woman    mpelvis  wx  0 wz\n");
               fprintf(nudesfile,"repeat      0   1 centre wpelvis  cx cy cz\n");
			   fprintf(nudesfile,"repeat      0   1 set    fpos     1\n");
               fprintf(nudesfile,"repeat      0   1 call   noposn\n");
            }
         }
      }
   }
} /* lstart */
/***********************************************/
   
   void lsetrange(void)
/*
   set range of symbols to be interpreted

   called by linter,
*/
{
   int bend;
   int k,kmax;
   int ymax;

   ystart = 0;
   yend = lbn[0].y;
   ymax = yend;
   sstart = 0;
   ssend = nlabs;
   for (k = 0; k < nlabs; ++k)
   {
      if (lbn[k].m == Bars)
      {
         if (lbn[k].i == bstart)
         {
            sstart = k;
            ystart = lbn[k].y;
         }
      }
   }
   bend = bstart + blength;
   for (k = (sstart+1); k < nlabs; ++k)
   {
      if (lbn[k].m == Bars)
      {
         if (lbn[k].i == bend)
            ssend = k;
      }
   }
   for (k = 0; k < nlabs; ++k)
   {
      if (lbn[k].m == Dirn)
      {
         if (lbn[k].y > yend)
            yend = lbn[k].y;
         if ((lbn[k].y+lbn[k].h) > ymax)
		 {
            ymax = lbn[k].y+lbn[k].h;
			kmax = k;
		 }
      }
   }
   f_max = 2 + int(lbn_fpp*double(ymax));
	printf("\n   lsetrange: pixels %d, frames %d\n",ymax,f_max);
} /* lsetrange */
/****************************************************/

void lcopyfigs(void)
/*
   finish off

   called by linter,
   calls     lgetout,
*/
{
   sprintf(figsname,"lintel.n");
   if ((figsfile = fopen(figsname,"r")) == NULL)
   {
      if (figsfile) fclose(figsfile);
      printf("\n\noops %s not in folder\n",figsname);
      lgetout(1);
      if (ok == 1) goto rtrn;
   }
   while (fgets(buf,BMAX,figsfile) != NULL)
      fprintf(nudesfile,"%s",buf);
rtrn: ;
} /* lcopyfigs */
/********************************************/

void lfinish(void)
/*
   finish off

   called by linter,
   calls lgetout,
*/
{
   f_max += 2;
   fprintf(nudesfile,"*\n");
   fprintf(nudesfile,"**************************\n");
   fprintf(nudesfile,"*\n");
   if (nm > 0)
      fprintf(nudesfile,
         "repeat      0 %3d ground man\n",f_max);
   else
      fprintf(nudesfile,
         "repeat      0   1 moveto man    mlfoot  10000 10000 10000\n");
   if (nw > 0)
      fprintf(nudesfile,
         "repeat      0 %3d ground woman\n",f_max);
   else
      fprintf(nudesfile,
         "repeat      0   1 moveto woman  wlfoot  10000 10000 10000\n");
   if (nm > 0)
      fprintf(nudesfile,
         "repeat      0 %3d centre mpelvis fx fy fz\n",f_max);
   else
      fprintf(nudesfile,
         "repeat      0 %3d centre wpelvis fx fy fz\n",f_max);
   if (track == TRUE)
   {
	   fprintf(nudesfile,
         "repeat      0 %3d add     fy -900 fz\n",f_max);
       fprintf(nudesfile,
         "repeat      0 %3d place   fx  500 fy\n",f_max);
   }
   fprintf(nudesfile,
       "repeat      0 %3d observe -9    0  0\n*\n",f_max);
   fprintf(nudesfile,
      "end dance\n****************************\n");
   fprintf(nudesfile,
      "*\nsubroutine setfmax\n");
   fprintf(nudesfile,
      "*\nrepeat 0 1 set fmax %d\n",f_max);
   fprintf(nudesfile,
      "*\nend setfmax\n");
   fprintf(nudesfile,
      "****************************\n*\nstop\n");
   fclose(nudesfile);
   if (nbar > 0)
         frperbar = f_max/nbar;
   else
         frperbar = 0;
} /* lfinish */
/********************************************/

void lselectfig(void)
/*
   select figure

   called by linter,
*/
{   
   int k;
   int nf;
   int nogo;
   int st;
   int stv0,stv1,st4;
   int stv[2];
   char key;

again:
   for (k = 0; k < nstaff; ++k)
      staff[k][5] = DONE;
   nf = 0;
   nm = 0;
   nw = 0;
   nogo = FALSE;
   if (nstaff < 1)
      printf("no staves\n");
   else
   if (nstaff == 1)
   {
      staff[0][5] = TODO;
      if (staff[0][4] == MAN) 
         ++nm;
      else
         ++nw;
   }
   else
   if (nstaff > 1)
   {
      nmw = 0;
      if (nstaff > TMAX)
         printf("This can only interpret staves from 1 to %d\n",
		    TMAX);
      if (lbn_figures == 2)
      {
         stv[0] = 1; stv[1] = 2;
         track = TRUE;
      }
      else // (lbn_figures != 2)
      {
         printf("\nPlease type the number of staves to be interpreted\n");
         if (gets(buf) == NULL)
         {
            printf("OOPS: cannot open standard input\n");
            lgetout(1);
            nogo = TRUE;
            if (ok == 1) goto rtrn;
         }
         sscanf(buf,"%d",&lbn_figures);
         if (lbn_figures > 2)
         {
            printf("sorry; this program can only interpret 2 staves at a time\n");
            nogo = TRUE;
            goto again;
         }
         if (lbn_figures == 1)
            printf("Please enter the staff number to be interpreted\n");
         else
         {
            printf("Please enter staff numbers to be interpreted\n");
            printf("separated by a space, and followed by the 'enter' key.\n\n");
         }
         if (gets(buf) == NULL)
         {
            printf("OOPS: cannot read staff numbers\n");
            lgetout(1);
            nogo = TRUE;
            if (ok == 1) goto rtrn;
         }
         if (lbn_figures == 1)
         {
            sscanf(buf,"%d",&stv0); 
            stv[0] = stv0; stv[1] = -1;
         }
         else
         {
            sscanf(buf,"%d %d",&stv0,&stv1); 
            stv[0] = stv0; stv[1] = stv1;
         }
      } /* lbn_figures != 2 */
      for (nf = 0; nf < lbn_figures; ++nf)
      {
            st = stv[nf]-1;
            if ((st < 0)||(st > nstaff))
            {
                printf("OOPS: staff number %d out of range\n",st+1);
                goto again;
            }
            st4 = staff[st][4];
            if ( ((nm > 0)&&(st4 == MAN))
               ||((nw > 0)&&(st4 == WOMAN)) )
            {
                printf("Sorry: can only do one man and/or one woman.");
                printf("Please select again.\n");
                nogo = TRUE;
             } /* more than 1 man or woman */
             else
             {
                if (st4 == WOMAN) ++nw;
                if (st4 == MAN) ++nm;
                staff[st][5] = TODO;
             } /* a man or woman */  
             nmw = nm*nw;
       } /* nf */
   } /* nstaff > 1 */
   if (nogo == TRUE)
      goto again;

rtrn: 
   if (lbn_figures != 2)
   {
       track = TRUE;
       printf("Track main figure? Hit 'enter' for Yes, any other key for No\n");
       key = getchar(); 
       if (key != '\n')
          track = FALSE;
   }
   else
       track = TRUE;
   if (track == FALSE)
       printf("\n   tracking OFF\n");
   else
       printf("\n   tracking ON\n");
} /* lselectfig */
/***********************************************/

void ldobar(void)
/*
   write bar number out

   called by laction,
*/
{
   if ((jm == Bars) && (jy < yend))
   {
      ++nbar;
      fprintf(nudesfile,"*\n");
      fprintf(nudesfile,"***************************\n");
      fprintf(nudesfile,"*\n");
      fprintf(nudesfile,"*   bar %d\n",nbar);
      fprintf(nudesfile,"*\n");
   }
} /* ldobar */
/********************************************/

void lbent(void)
/*
   for Volm symbol : flag next 'Dirn' symbol above
   
   called by laction,
   calls lassign,

   Volm   1  RELAX
   Volm   3  BENT
   Volm   2  STRAIGHT
   Volm   4  STRETCH
   Volm   7  hold
*/
{
   int g;
   int k;
   int ki,kx,kx2,ky,ky2;
   int jy2h;
   char km;

   for (j = 0; j < ssend; ++j)
   {
      if ((lbn[j].m == Volm)&&(lbn[j].i <= STRETCH)) 
      {
         lassign();
         jy2h = jy2+jh;
         g = -1;
         for (k = j+1;	((k < nlabs)&&(g < 0)); ++k)
         {
            km = lbn[k].m;
            if ((km == Dirn)&&(lbn[k].a == TODO))
            {
               ky = lbn[k].y;
               if (ky > jy2h)
                  g = 0;
               else
               {
                  ky2 = lbn[k].y2;
                  kx = lbn[k].x;
                  kx2 = lbn[k].x2;
                  if ((loverlap(jx,jx2,kx,kx2) > 0)
                     &&(loverlap(jy2,jy2h,ky,ky2) > 0))
                  {
                      g = k;
                      lbn[j].b = ji;
                      ki = lbn[k].i;
                      lbn[j].m = km;
                      lbn[j].i = ki;
                      lbn[j].y2 = ky2;
                      lbn[j].h = lbn[k].y2 - jy;
                      lbn[j].d = lbn[k].d;
                      lbn[k].a = DONE;
                      if (ji == BENT)
                      {
                         if ((ki == 11)&&(jc < 0))
                            lbn[j].i = 8;
                         else
                         if ((ki == 11)&&(jc > 0))
                            lbn[j].i = 3;
                      } /* ji == BENT */
                  } /* overlapping */
               } /* ky < jy2h */
            } /* km = Dirn */
         } /* k */
      } /* jm = Volm */
   } /* j */
} /* lbent */
/********************************************/

void lrelease(void)
/*
   release the hold when jm = Misc

   called by laction,
   	  Assumes one of the following holds:

	  So far:
   NO  - no hold: arm gestures apply.
   CL  - closed hold: normal ballroom dancing position.
   SS  - semi-shadow hold: both facing same way, bodies touching, 
         man's L hand to lady's L hand,
         man's R hand to front of lady's R hip,
		 lady's R hand free.
   OE  - open extended hold: both facing same way, bodies apart,
         man's R hand to lady's L hand, other hands free.
   CO  - counter open extended hold: both facing same way, bodies apart,
         man's L hand to lady's R hand, other hands free.
   SH  - shadow hold: both facing same way, bodies touching,
         L hand to L hand, R hand to R hand.

      later to do:
   PR  - promenade position: facing partner, bodies touching,
         but both prepared to travel to man's L.
   CP  - counter promenade position: facing partner, bodies touching,
         but both prepared to travel to man's R.
   DB  - double hold: facing partner, bodies apart,
         L hand to R hand, R hand to L hand.
   OP  - open hold: facing partner, bodies apart,
         man's L hand to lady's R hand, other hands free.
   CR  - crossed open hold: facing partner, bodies apart,
         man's R hand to lady's R hand, other hands free.

	Relevant symbols:-
     m     i
    Misc   1  bow
    Misc   2  release1
    Misc   3  release2
    Limb   4  lhand
    Limb   9  rhand
    Area   1  top/front 
    Area   5  back/bottom
    Volm   1  RELAX
    Volm   3  BENT
    Volm   2  STRAIGHT
    Volm   4  STRETCH
    Volm   7  hold

    FRONT   100         // front symbol found
    BACK    200         // back symbol found
    MLHAND    1         // man's left hand symbol found
    MRHAND    2         // man's right hand symbol found
    WLHAND   10         // woman's left hand symbol found
    WRHAND   20         // woman's right hand symbol found
*/
{
   int fdif;
   int fbegin,ffin;

   if ((nmw > 0)&&(ji == 2)) // release
   {
      holdcl = 0;
      holdoe = 0;
      holdco = 0;
      holdpr = 0;
      holdsh = 0;
      holdss = 0;
      fbegin = pend;
      ffin = fend;
      if (ffin <= fbegin) ffin = fbegin + 1;
      fdif = ffin - fbegin;
      if ((st > 0) && (hold != NO))
      {
         fprintf(nudesfile,
            "repeat    %3d %3d set fpos %d\n",fbegin,ffin,fdif);
         fprintf(nudesfile,
            "call      %3d %3d noposn\n*\n",fbegin,ffin);
      }
      hold = NO;
      fprintf(nudesfile,
         "* lreleasea %d %d %d %d %d %d\n",
            fstart,fend,j,jb,hold,prevhold);
      keptf = ffin;
   }
} /* lrelease */
/******************************************/

void ldoposn(void)
/*
   set up a couple dance position

   called by lsethold, ldohold
*/
{
	  fbegin = fstart;
	  ffin = fend;
	  	  fprintf(nudesfile,
		"** ldoposn %3d %3d, %3d %3d\n",fbegin,ffin, st,hold);
      if (st > 0)
      {
			flen = ffin - fbegin;
			if (flen < 1) flen = 1;
			if (hold != NO) 
            fprintf(nudesfile,
               "repeat    %3d %3d set    fpos %3d\n",
                  fbegin,ffin,flen);
			if (hold == PR)
            fprintf(nudesfile,
               "call      %3d %3d prposn\n*\n",fbegin,ffin);
			else
			if (hold == CO)
            fprintf(nudesfile,
               "call      %3d %3d coposn\n*\n",fbegin,ffin);
			else
			if (hold == CL)
            fprintf(nudesfile,
               "call      %3d %3d clposn\n*\n",fbegin,ffin);
			else
			if (hold == SS)
            fprintf(nudesfile,
               "call      %3d %3d ssposn\n*\n",fbegin,ffin);
			else
			if (hold == OE)
            fprintf(nudesfile,
               "call      %3d %3d oeposn\n*\n",fbegin,ffin);
			else
			if (hold == SH)
            fprintf(nudesfile,
               "call      %3d %3d shposn\n*\n",fbegin,ffin);
			keptf = ffin;
			prevhold = hold;
      } /* st > 0 */
} /* ldoposn */
/*******************************************/

void ldokeep(void)
/*
   maintain a couple dancing position

   called by dohold,
*/
{
	fprintf(nudesfile,
		"** ldokeep %3d %3d, %3d\n",fbegin,ffin,hold);
         if (hold == PR)
            fprintf(nudesfile,
               "repeat    %3d %3d call   prkeep\n*\n",fbegin,ffin);
         else
         if (hold == CL)
		     fprintf(nudesfile,
               "repeat    %3d %3d call   clkeep\n*\n",fbegin,ffin);
         else
         if (hold == OE)
            fprintf(nudesfile,
               "repeat    %3d %3d call   oekeep\n*\n",fbegin,ffin);
         else
         if (hold == SS)
            fprintf(nudesfile,
               "repeat    %3d %3d call   sskeep\n*\n",fbegin,ffin);
		 else
         if (hold == CO)
            fprintf(nudesfile,
               "repeat    %3d %3d call   cokeep\n*\n",fbegin,ffin);
         else
         if (hold == SH)
            fprintf(nudesfile,
               "repeat    %3d %3d call   shkeep\n*\n",fbegin,ffin);
         keptf = ffin;
}   /* ldokeep */
/******************************************/

void ldohold(void)
/*
    set up and maintain holds
	
	called by laction,
	calls ldokeep, ldoposn,
*/
{
   fbegin = keptf;
   ffin = pend;
		fprintf(nudesfile,
		"** ldohold %3d %3d, %3d %3d\n",fbegin,ffin, hold,prevhold);
   if (prevhold == hold) 
   {
	   fbegin = keptf;
      if (fbegin < ffin) ldokeep();
   } /* prevhold == hold */
   else
   {
      ldoposn();
   } /* prevhold != hold */
} /* ldohold */
/*************************************************/

void lsethold(void)
/*
   set the hold if jm = Limb or jm = Face

   called by laction,
   calls ldoposn,

      Uses the hand signs to determine the holds if any.
   	  Assumes one of the following holds:

	  So far:
   NO - no hold: arm gestures apply.
   CL - closed hold: normal ballroom dancing position.
   SS - semi-shadow hold: both facing same way, bodies touching, 
        man's L hand to lady's L hand,
        man's R hand to front of lady's R hip,
         ady's R hand free.
   OE - open extended hold: both facing same way, bodies apart,
        man's R hand to lady's L hand, other hands free.
   CO - counter open extended hold: both facing same way, bodies apart,
        man's L hand to lady's R hand, other hands free.
   SH - shadow hold: both facing same way, bodies touching,
        L hand to L hand, R hand to R hand.
   PR - promenade position: diagonally facing partner,
        bodies touching, both travelling to man's L.
   CP - counter promenade position: facing partner, bodies touching,
        but both prepared to travel to man's R.
   DB - double hold: facing partner, bodies apart,
        L hand to R hand, R hand to L hand.
   OP - open hold: facing partner, bodies apart,
        man's L hand to lady's R hand, other hands free.
   CR - crossed open hold: facing partner, bodies apart,
        man's R hand to lady's R hand, other hands free.

#define NO        0        // no hold
#define CL        1        // closed hold
#define PR        2        // promenade position
#define CP        3        // counter promenade position
#define DB        4        // double hold
#define OP        5        // open hold
#define CR        6        // crossed open hold
#define OE        7        // open extended hold
#define CO        8        // counter open extended hold
#define SH        9        // shadow hold
#define SS       10        // semi-shadow hold 

	Relevant symbols:-
     m     i
    Misc   1  bow
    Misc   2  release1
    Misc   3  release2
    Limb   4  lhand
    Limb   9  rhand
    Area   1  top/front 
    Area   5  back/bottom
    Volm   1  RELAX
    Volm   3  BENT
    Volm   2  STRAIGHT
    Volm   4  STRETCH
    Volm   7  hold

#define FRONT   100         // front/top symbol found
#define BACK    200         // back symbol found
#define MLHAND    1         // man's left hand symbol found
#define MRHAND    2         // man's right hand symbol found
#define WLHAND   10         // woman's left hand symbol found
#define WRHAND   20         // woman's right hand symbol found
*/
{
   int i,n;
   int dy,ylap;

   prevhold = hold;
   mface = -1;
   wface = -1;
   facedif = -1;
	if ((jm == Face)&&(oriented == FALSE)&&
		(((dofig == MAN)&&(jc < 0))||(dofig == WOMAN)&&(jc > 0)))
	{
		fprintf(nudesfile,
			"linear    %3d %3d spinby fig    afoot  pelvis %d y\n",
         0,1,(ji-1)*45);
		oriented = TRUE;
	}
   if ((jm == Limb)&&((ji == 4)||(ji == 9)))
   {
      if (jb ==  11) { ++holdss; ++holdsh; }
      if (jb ==  12) ++holdoe;
      if (jb ==  21) { ++holdco; ++holdcl; ++holdpr; }
      if (jb ==  22) ++holdsh;
      if (jb == 110) { ++holdcl; ++holdpr; }
      if (jb == 102) ++holdss;
      if (jb == 120) ++holdss;
      if (jb == 202) { ++holdcl; ++holdpr; }
   } /* jm = a hand */
   else
   if ((jm == Face)&&(jx > stmiddle))
   {
      n = -1;
      ylap = -1;
      wface = ji;
      for (i = 1; i < 9; ++i)
      {
         n = lseeksym(Face,i,xmin,stmiddle,jy,jy2);
         if (n >= 0)
         {
            dy = loverlap(jy,jy2,lbn[n].y,lbn[n].y2);
            if (dy > ylap)
            {
               ylap = dy;
               mface = i;
            }
         } /* found man facing sign */
      }
      if (mface >= 0)
      {
         facedif = mface - wface;
         if (facedif < 0) facedif += 8;
         if (facedif > 7) facedif -= 8;
      }
      else
         facedif = -1;
      if (facedif == 0)
      {
         facecl = 0;
         facepr = 0;
         facesh = 1;
         facess = 1;
      } /* facing same way */
      else
      if (facedif == 2)
      {
         facecl = 0;
         facepr = 1;
         facesh = 0;
         facess = 0;
      } /* facing at right angles */
      else
      if (facedif == 4)
      {
         facecl = 1;
         facepr = 0;
         facesh = 0;
         facess = 0;
      } /* facing opposite ways */
   } /* jm == Face */
   if (holdoe > 1) if (hold != CO) hold = OE;
   if (holdco > 1) if (hold != OE) hold = CO;
   if ((facesh+holdsh) > 4) hold = SH;
   if ((facess+holdss) > 4) hold = SS;
   if ((facepr+holdpr) > 4) hold = PR;
   if ((facecl+holdcl) > 4) hold = CL;
	fprintf(nudesfile,
		"** lsethold %d %d,  %d %d,  %d %d,  %d %d,  %d %d, %3d %3d %3d\n",
		hold, prevhold,
		facesh,holdsh,facess,holdss,facepr,holdpr,facecl,holdcl,
		mface,wface,facedif);
   if (prevhold != hold) ldoposn();
} /* lsethold */
/********************************************/

void ldochest(int piv)
/*
   rotate the chest and stomach
   
   called by ldolimb,
*/
{
   if (piv == 0)
   {
	   fprintf(nudesfile,
         "quadratic %3d %3d bendto chest   ribs  stomach 0 0 0\n",
             fstart,fend);
	   fprintf(nudesfile,
         "quadratic %3d %3d bendto stomach waist pelvis 0 0 0\n",
             fstart,fend);
   } /* piv == 0 */
   else
   {
      if (dofig == MAN)
         fprintf(nudesfile,
            "quadratic %3d %3d rotate chest   ribs %3d\n",
             fstart,fend,-piv/2);
      else
	      fprintf(nudesfile,
            "quadratic %3d %3d rotate chest   ribs %3d\n",
             fstart,fend,piv/2);
      fprintf(nudesfile,
         "quadratic %3d %3d rotate stomach waist %3d\n",
          fstart,fend,piv/2);
   } /* piv != 0 */
} /* ldochest */
/******************************************/

void ldolimb(void)
/*
   do something to some body part
   
   called by laction,
   calls ldoarms, ldochest,

	Volm 7 + Area 9 = chest
*/
{
	int nc;
	int piv;

	nc = jc+8;
	piv = -1;
	if ( (colm[nc] == ARM)&&(jm == Dirn)&&
		((hold == NO)||(hold == OE)||(hold == CO)) )
        ldoarms();
	else
	if (jm == Limb)
		colm[nc] = Limb;
	else
	if ((jm == Volm)&&(ji == 7)
		&&(colm[nc] == Area)&&(jd == BLANK))
	{
		colm[nc] = CHEST;
	   fprintf(nudesfile,"* ldolimba CHEST at column %d\n",nc);
	}
	else
	if ((jm == Area)&&(ji == 9)
		&&(colm[nc] == Volm)&&(jd == BLANK))
		colm[nc] = CHEST;
	else
	if ((jm == Area)&&(ji == 9))
		colm[nc] = Area;
	else
	if ((jm == Volm)&&(ji == 7))
		colm[nc] = Volm;
	else
	if ((jm == Rotn)&&(colm[nc] == CHEST))
	{
		piv = lgetpin();
		ldochest(piv);
	}
} /* ldolimb */
/*********************************************/

void lcoords(char jm, int ji)
/*
	check for change of coordinates

	called by laction,
	calls lseeksym, lgetpin

	Relevant symbols:-
	m      i
	Volm   5  space hold
	Volm   6  coordinates
	Volm   7  body hold
	Area   9  square
	Pins   1  forward
	Pins   5  backward
	
	 1 Aug 2006 checking piv against maxint
	30 Jul 2006 writing bendtos for mspace and wspace
*/
{
	int k;
	int piv;

	if ((jm == Area)&&(ji == 9))
	{
		piv = lgetpin ( );
		//fprintf(nudesfile,"* lcoordsa %c %d\n",m,piv);
		if (piv != maxint)
		{
			if (piv == 360) piv = 0;
			//coordinates = SPACE;
			if ( dofig == MAN )
			{
				fprintf(nudesfile,
					"repeat %d %d bendto mspace jman joist 270 0 %d\n",
					fstart, fend, piv);
			   mspace = true;
			}
			else
			{
				fprintf(nudesfile,
					"repeat %d %d bendto wspace jwoman joist 270 0 %d\n",
					fstart, fend, piv);
				wspace = TRUE;
			}
		} /* space stance found */
	} /* possible space stance found */
	else
	{
		k = lseeksym(Volm,7,jx,jx2,jy,jy2);
		if (k > 0)
		{
			//coordinates = BODY;
			if ( dofig == MAN )
			   mspace = false;
			else
				wspace = FALSE;
		} /* body stance found */
		//fprintf(nudesfile,"* lcoordsb mspace wspace TRUE\n",
			//mspace,wspace,TRUE);
	} /* possible body stance found */
}  /* lcoords */
/*****************************************/

void ldotoetaps ( void )/*
/*

	do toe taps with gestures of the legs
	doing diagonals sideways at present

	Volm   1  RELAX
	Volm   3  BENT
	Volm   2  STRAIGHT
	Volm   4  STRETCH
	Volm   7  hold

	called by laction,
	calls lgetout, lsetframes, bell,

	19 Aug 2006 d076- Don Herbison-Evans
*/
{
	if ( (( jc == -3 )||( jc == 3 )) && ( jd == -1 ) )
	{
			fprintf ( nudesfile, "*\n" );
			if  ( ji==11 )
				fprintf ( nudesfile, "* in place tap\n" );
			else if ( ( ji == 1 ) || ( ji == 10 ) )
				fprintf ( nudesfile, "* forward tap\n" );
			else if ( ( ji == 2 ) || ( ji == 9 ) )
				fprintf ( nudesfile, "* forward diagonal tap\n" );
			else if ( ( ji == 3 ) || ( ji == 8 ) )
				fprintf ( nudesfile, "* sideways tap\n" );
			else if ( ( ji == 4 ) || ( ji == 7 ) )
				fprintf ( nudesfile, "* back diagonal tap\n" );
			else if ( ( ji == 5 ) || ( ji == 6 ) )
				fprintf( nudesfile, "* backward tap\n" );
			//
			if ( dofig == MAN )
			{
				if (mspace == false)
					fprintf( nudesfile, "repeat    %3d %3d set    coords mpelvis\n",
					fstart, fend );
				else
					fprintf( nudesfile, "repeat    %3d %3d set    coords mspace\n",
					fstart, fend );
			}
			else
			{
				if (wspace == FALSE)
					fprintf( nudesfile, "repeat    %3d %3d set    coords wpelvis\n",
					fstart, fend );
				else
					fprintf( nudesfile, "repeat    %3d %3d set    coords wspace\n",
					fstart, fend );
			}
			//
			if ( jc < 0 )
			{
				if ( ( ji <= 1 ) || ( ji == 3 ) || ( ji == 5 ) || ( ji > 11 ) )
				{
					printf ( "OOPS: ldotoetap left direction problem line %d\n", j );
					printf ( "%3d %3d %3d %3d %3d %3d %3d %3d %d\n", jm, ji, jx, jy, js, jw, jh, jb, jd );
					lgetout ( 1 );
					if ( ok == 1 ) return;
				} /* i wrong */
				fprintf ( nudesfile,
					"repeat    %3d %3d call   forleft * left = b\n", fstart, fend );
			} /* left side */
			else if ( jc > 0 )
			{
				if ( ( ji < 1 ) || ( ji == 6 ) || 
					( ji == 8 ) || ( ji == 10 ) || ( ji > 11 ) )
				{
					printf ( "OOPS: ldotoetap right direction problem line %d\n", j );
					printf ( "%3d %3d %3d %3d %3d %3d %3d %3d %d\n", jm, ji, jx, jy, js, jw, jh, jb, jd );
					lgetout ( 1 );
					if ( ok == 1 ) return;
				} /* i wrong */
				fprintf ( nudesfile,
					"repeat    %3d %3d call   forright * right = b\n",fstart, fend );
			} /* right side */
//
			if ( ji == 11 )
			{
				fprintf ( nudesfile, "repeat    %3d %3d call   %s\n",
					fstart, fend, risesub[rise] );
				fprintf ( nudesfile,
					"repeat    %3d %3d set    fend  %d\n",
					fstart, fend, frange );
				fprintf ( nudesfile,
					"linear    %3d %3d bendto bleg   bknee  bthigh lrlx1 lrlx2 lrlx3\n",
					fstart, fend );
			} /* close without weight */
			else
				fprintf ( nudesfile,
					"linear    %3d %3d bendto bleg   bknee  bthigh lhig1 lhig2 lhig3\n",
					fstart, fend );
			fprintf ( nudesfile,
				"linear    %3d %3d drag   bfoot  bfoot  bankle bleg  x\n",
				fstart, fend );
			lbn[j].a = DONE;
	} /* c OK */
} /* ldotoetaps */
/**************************************/

void laction(void)
/*
   run through and interpret the actions

   called by linter,
   calls     ldobar,   ldosteps, lleggesture, ldolimb,
             ldopivot, lbent,    lassign,  lsetframes,
             lsethold, ldohold,  lrelease, lface,

#define FRONT   100         // front symbol found
#define BACK    200         // back symbol found
#define MLHAND    1         // man's left hand symbol found
#define MRHAND    2         // man's right hand symbol found
#define WLHAND   10         // woman's left hand symbol found
#define WRHAND   20         // woman's right hand symbol found 
	
#define NO        0        // no hold
#define CL        1        // closed hold
#define PR        2        // promenade position
#define CP        3        // counter promenade position
#define DB        4        // double hold
#define OP        5        // open hold
#define CR        6        // crossed open hold
#define OE        7        // open extended hold
#define CO        8        // counter open extended hold
#define SH        9        // shadow hold
#define SS       10        // semi-shadow hold 

Relevant symbols:-
     m     i
    Misc   1  bow
    Misc   2  release1
    Misc   3  release2
    Limb   4  lhand
    Limb   9  rhand
    Area   1  top/front 
    Area   5  back/bottom
	 Area   9  square
    Volm   1  RELAX
    Volm   3  BENT
    Volm   2  STRAIGHT
    Volm   4  STRETCH
	 Volm   6  coordinates
    Volm   7  hold
    Face   n  facing direction

*/
{
	fprintf ( nudesfile, "*\n************************************\n" );
	oriented = FALSE;
	if ( dofig == MAN )
		fprintf ( nudesfile, "*\nrepeat      0 %3d call   doman\n", f_max );
	else
		fprintf ( nudesfile, "*\nrepeat      0 %3d call   dowoman\n", f_max );
	for ( j = 0; j < NCOLM; ++j )
		colm[j] = ARM;
	for ( j = 0; j < ssend; ++j )
	{
		lassign ();
		lsetframes ();
		fprintf(nudesfile,"* %d %3d %s",lbn[j].a,jc,lbnline[j]);
		if ( lbn[j].a == TODO )
		{
			if ( jm == Bars )
				ldobar ();
			else if ( ( jm == Face ) || ( jm == Limb ) )
				lsethold ();
			else if ( jm == Misc )
			{
				lrelease ();
			}
			else if ( ( jc > -8 ) && ( jc < 8 ) )
			{
				if ( (( jm == Volm )&&( ji == 6 )) 
					||(( jm == Area )&&( ji == 9 )) )
						lcoords(jm, ji);
				if ( ( jm == Rotn ) && ( jc > -4 ) && ( jc < 4 ) )
					ldopivot ();
				else if (( jm == Dirn ) && ( jc > -4 ) && ( jc < 4 ))
				{
					ldostep ();
					lleggesture ();
					ldotoetaps ();
				}
				else
					ldolimb ();
			} /* jc OK */
		} /* ja == TODO */
		if (( (jm == Dirn)||(jm == Rotn) )&&(jc >= -6)&&(jc <= 6)
			&&( nmw > 0 )&&( dofig == WOMAN ) )
			ldohold ();
		pstart = fstart;
		pend = fend;
	} /* j */
} /* laction */
/*************************************************/

void linter(void)
/*
                     linter

      interpret labanotation score into a NUDES file
                version linter50.c

      input : LED Labanotation file:   standard input (led.lbn)
      output: NUDES animation script:  standard output (led.n)

   called by main,
   calls     lbnread, lsorty, lfindstaff, lstart, lhold,
             lfindystart, lcolx, lsetrange, lselectfig,
             lgetout, lcopyfigs, lfinish, lcopysubs,
             lbows,
*/
{
   lbnread();;
   lsorty();
   lfindstaff();
   lsetrange();
   lselectfig();
   lcopyfigs();
   lstart();
   lfindystart();
   lbows(); // flag hand signs
   lbent(); // flag dirn signs
   for (st = 0; st < nstaff; ++st)
   {
      hold = NO;
      holdcl = 0;
      holdco = 0;
      holdoe = 0;
      holdpr = 0;
      holdsh = 0;

      holdss = 0;
      facecl = 0;
      facepr = 0;
      facesh = 0;
      facess = 0;
      prevhold = -9;
      prevc = 0;
      pstart = -1;
      pend = -1;
      keptf = 0;
      gy = -1;
      gh = 0;
      if (staff[st][5] == TODO)
      {
         nbar = -1;
         if (staff[st][4] == MAN)
            dofig = MAN;
         else
            dofig = WOMAN;
         lcolx(staff[st][2]);
         laction();
         staff[st][5] = DONE;
      }
   }
   lfinish();
} /* linter */
/****************************************/


void getout(int v)
/*
   exit gracefully

   called by main, inlims, openfile, compl, nexts, doperfrm,
             initsphere, getkeys,
*/
{
   if (v != 0) 
   {
	   printf("lintel problem\nok error number %d\n",ok);
	   printf("line %d, action %d\n%s\n",
		   pp,p,aline[pp]);
   }
   if (infile) fclose(infile);
   ok = 1;
} /* getout */
/********************************************/

void openfile(void)
/*
   open the nudes file written by linter routine

   called by main,
*/
{
      if ((infile = fopen(nudesname,"r")) == NULL)
      {
         if (infile) fclose(infile);
         printf("\n\n %s oops?\n",nudesname);
		 ok = 2;
         getout(1);
         if (ok == 1) goto rtrn;
      }
      printf("\n   opened %s\n",nudesname);
rtrn: ;
} /* openfile */
/***************************************/



void add_id_num ( char name[], char outname[], char ext[] )
{
	FILE *test_File;
	int j;

	for ( j = 0; j <= 999; j++ )
	{
		sprintf ( outname, "%s_%03d%s", name, j, ext );

		if ( ( test_File = fopen ( outname, "r" ) ) != NULL )
		{
			fclose ( test_File );
		}
		else
		{
			return;
		}
	}
	sprintf ( outname, "%s_000%s", name, ext );
} /* add_id_num */
/*******************************************/

int find_ini_title ( char title[] )
/*
   called by get_ini_str, get_ini_bool, 
	          get_ini_char,
*/
{
	int value = -1;
	int ini_no;
	int j;
	int plen;
	int iplen;
	if ( number_ini <= 0 ) return( NULL );
	for ( ini_no = 0; ini_no < number_ini; ini_no++ )
	{
		plen = (int)strlen ( title );
		iplen = 0;
		for ( j = 0; j < plen; j++ )
		{
			if ( title[j] == ini_title[ini_no][j] )
			{
				iplen = iplen + 1;
			}
		}
		if ( iplen == plen )
		{
			return( ini_no );
		}
	}
	return( value );
} /* find_ini_title */
/************************************************/

void get_ini_dump ( void )
{
	int ini_no;
	printf ( "  number ini %d\n", number_ini );
	if ( number_ini <= 0 ) return;
	for ( ini_no = 0; ini_no < number_ini; ini_no++ )
	{
		printf ( " ini_no %2d title %s value %s\n",
			ini_no, &ini_title[ini_no][0], &ini_value[ini_no][0] );
	}
} /* get_ini_dump */
/************************************************/

bool get_if_ini ( void )
{
	if ( number_ini > 0 ) return( true );
	return( false );
} /* get_if_ini */
/************************************************/

bool get_ini_bool ( char title[] )
{
	bool value;
	int ini_no;
	value = -1;NULL;
	if ( number_ini <= 0 ) return( NULL );
	ini_no = find_ini_title ( title );
	if ( ini_no < 0 ) return( NULL );
	if ( toupper( ini_value[ini_no][0] ) == 'T' )
		return( true );
	if ( toupper( ini_value[ini_no][0] ) == 'F' )
		return( false );
	return( NULL );

} /* get_ini_bool */
/************************************************/

char* get_ini_char ( char title[] )
/*
   calls find_ini_title, ini_value
*/
{
	char* value;
	int ini_no;
	value = NULL;
	if ( number_ini <= 0 ) return( NULL );
	ini_no = find_ini_title ( title );
	if ( ini_no < 0 ) return( NULL );
	return( &ini_value[ini_no][0] );

} /* get_ini_char */
/************************************************/

int get_ini_int ( char title[] )
/*
   calls find_ini_title, ini_value
*/
{
	int value = 0;
	int ini_no;
	if ( number_ini <= 0 ) return( NULL );
	ini_no = find_ini_title ( title );
	if ( ini_no < 0 ) return( NULL );
	value = atoi ( &ini_value[ini_no][0] );
	//printf ( " ini_no %d value %d\n", ini_no, value );
	return( value );

} /* get_ini_int */
/************************************************/

float get_ini_float ( char title[] )
/*
   calls find_ini_title, ini_value
*/
{
	float value = 0.0f;
	int ini_no;
	if ( number_ini <= 0 ) return( NULL );
	ini_no = find_ini_title ( title );
	if ( ini_no < 0 ) return( NULL );
	value = atof ( &ini_value[ini_no][0] );
	return( value );
} /* get_ini_float */
/************************************************/

double get_ini_double ( char title[] )
/*
   calls find_ini_title, ini_value
*/
{
	double value = 0.0;
	int ini_no;
	if ( number_ini <= 0 ) return( NULL );
	ini_no = find_ini_title ( title );
	if ( ini_no < 0 ) return( NULL );
	value = strtod ( &ini_value[ini_no][0], NULL );
	return( value );
} /* get_ini_double */
/************************************************/

bool get_ini_str ( char title[], char value[] )
/*
   calls find_ini_title, ini_value
*/
{
	//char* value;
	int ini_no;
	int i;
	int len;

	value[0] = NULL;
	if ( number_ini <= 0 ) return( false );
	ini_no = find_ini_title ( title );
	if ( ini_no < 0 ) return( false );
	len = (int)strlen( &ini_value[ini_no][0] );
	if ( len <= 0 )  return( false );
	i = -1;
	do
	{
		i = i + 1;
		value[i] = ini_value[ini_no][i];		
	} while ( ini_value[ini_no][i] != NULL );

	return( true );

} /* get_ini_str */
/************************************************/

void get_ini ( int dump )
/*
   open  and decode .ini file

   called by main,
*/
{
	FILE *ini_file_unit;
	int ini_no;
	int j;
	int k;
	int len;
	int loc_comma;
	int loc_semi;
	char asterisk = '*';
	char blank = ' ';
	char comma = ',';
	char semi = ';';
	bool getout;

	for ( ini_no = 0; ini_no < max_ini; ini_no++ )
	{
		ini_title[ini_no][0] = NULL;
		ini_value[ini_no][0] = NULL;
	}

	number_ini = -1;
	ini_diag = 0;
	ini_file_unit = NULL;

	// open ini file - check if it exists

	if ( ( ini_file_unit = fopen ( "lintel.ini", "r" ) ) == NULL )
	{
		if ( ini_file_unit ) fclose ( ini_file_unit );
		printf ( "\n\n    %s\n\n",
			"lintel.ini not available - will continue" );
	}
	else
	{
		ini_no = 0;
		number_ini = ini_no;
		len = -1;
		do
		{
			ini_title[ini_no][0] = NULL;
			ini_value[ini_no][0] = NULL;

			if ( fgets ( buf, BMAX, ini_file_unit ) != NULL )
			{
				if ( ini_diag >= 1 )
					printf ( " ini_no %2d buf %s", ini_no, buf );
				if ( buf[0] != asterisk )
				{
					if ( ini_diag >= 1 )
						printf ( " ini_no %2d buf %s", ini_no, buf );
					loc_comma = -1;
					loc_semi = -1;
					getout = false;
					len = (int)strlen( buf );
					if ( ini_diag >= 1 ) printf ( " len %d\n", len );
					for ( j = 0; j < len; j++ )
					{
						if ( buf[j] == comma && loc_semi == -1 ) loc_comma = j;
						if ( buf[j] == semi  )
						{
							loc_semi = j;
							getout = true;
						}
						if ( getout == true ) break;
					}
					if ( ini_diag >= 1 )
						printf ( " loc_comma %d loc_semi %d\n",
							loc_comma, loc_semi );

					// get parameter title

					k = 0;
					for ( j = 0; j < loc_comma; j++ )
					{
						if ( buf[j] != blank )
						{
							ini_title[ini_no][k] = buf[j];
							k = k + 1;
						}

					}
					ini_title[ini_no][k] = NULL;

					// get parameter value

					k = 0;
					for ( j = loc_comma + 1; j < loc_semi; j++ )
					{
						if ( buf[j] != blank )
						{
							ini_value[ini_no][k] = buf[j];
							if ( ini_diag > 1 )
							{
								printf( " j %d k %d buf[j] %c ini %c\n",
									j, k, buf[j],ini_value[ini_no][k] );
							}
							k = k + 1;
						}
					}
					ini_value[ini_no][k] = NULL;
					ini_no = ini_no + 1;
				}
				else
				{
					if ( buf[1] == 'd' && buf[2] == 'u' 
						&& buf[3] == 'm' && buf[4] == 'p' )
						dump = 1;
				}
			}
		}
		while ( !feof( ini_file_unit ) && len != 0 );
		number_ini = ini_no;
	}
	if ( dump == 1 ) get_ini_dump ();
} /* get_ini */
/************************************************/

bool strcmpend ( char str1[], char str2[] )
/*
	compare strings to see if str2 is included at end of str1
*/
{
	int len1, len2;
	int i1, i2;
	int cnt;

	len1 = (int)strlen( str1 );
	len2 = (int)strlen( str2 );

	cnt = 0;
	i2 = len2 - 1;
	for ( i1 = len1 - 1; i1 >= len1 - len2; i1-- )
	{
		if ( str1[i1] == str2[i2] ) cnt = cnt + 1;
		i2 = i2 - 1;
	}
	if ( cnt == len2 )		return( true );

	return( false );
}/* strcmpend */void get_filesa ( bool lbn_type, int error )
{
	printf( "\n" );
	if ( error == 0 )
	{
		printf( "    Please type input filename followed by pressing the 'enter' key\n\n" );
	}
	else
	{
		printf( "\n" );
		printf( "    Please type a correct input filename\n\n" );
	}

	if ( lbn_type == true )
	{
		printf( "      NUDES file (xxx.nud or xxx.n)\n" );
		printf( "        - full filename (xxx.nud or xxx.n)\n" );
		printf( "      LBN file (yyy.lbn)\n" );
		printf( "        - root portion (yyy) of filename\n" );
		printf( "           (interprets staves 1 and 2 with figure tracking)\n" );
		printf( "        - full filename (yyy.lbn)\n" );
		printf( "           (choice of staves, choice of tracking)\n\n" );
		printf( "    Filename:  " );
	}


	if ( lbn_type == false )
	{
		printf( "    Filename:  " );
	}
} /* get_filesa */
/************************************************/

void get_files ( char file[] )
/*
   called by main
	calls get_filesa, strcmpend, bell, add_id_num,
*/
{
	int c;
	int i;
	int len;
	int last;
	int err_count;
	int error;
	int loc_dot;
	int from_ini;
	char key;
	bool get_out;
	bool ini_ok;
	bool file_ok;
	bool dir_ok;
	bool lbn_type;
	char dir[BMAX];

	from_ini = 0;
	err_count = 0;
	error = 0;
	get_out = false;
	ini_ok = false;
	file_ok = false;
	dir_ok = false;
	lbn_type = true;
start:
	err_count = err_count + 1;
	if ( err_count >= 25 ) 
	{
		printf( " Limit: tried %d times for input file %s\n",
			err_count,name );
		ok = -1;
		return;
	}
	input_file_type = -1;
	for ( c = 0; c < BMAX; ++c )
	{
		name[c] = NULL;
		finname[c] = NULL;
		nudesname[c] = NULL;
	}

	if ( file == NULL )
	{
		file_ok = false;
		if ( from_ini == 0 )
		{
			if ( get_if_ini () == true )
			{
				ini_ok = get_ini_bool ( "input_file_default" );
				if ( ini_ok == true ) 
				{
					file_ok = get_ini_str ( "input_file_name", name );
					dir_ok = get_ini_str ( "input_file_dir", dir );
					if ( dir[0] == NULL ) dir_ok = false;
					len = (int)strlen( dir );
					if ( dir_ok == true && dir[len - 1] != '\\' )
						dir[len - 1] = '\\';
					lbn_type = get_ini_bool ( "lbn_file_encoded" );
					from_ini = 1;
				}
			}
		}

		if ( file_ok == false )
		{
			name[0] = NULL;
			get_filesa ( lbn_type, error );
			if ( gets ( name ) != NULL )
			{
				len = (int)strlen( name );
				if ( len == 0 )
				{
					get_out = true;
					error = 1;
					goto start; 
				}
			}
			else
			{
				get_out = true;
				error = 1;
				goto start; 
			}
		}
	}
	else
	{
		strcpy ( name, file );
	}

	len = (int)strlen( name );
	last = len - 1;

	loc_dot = -1;
	i = -1;
	do
	{
		i = i + 1;
		key = name[i];
		if ( key == '.' ) loc_dot = i;
	} while ( key != NULL );

	if ( loc_dot >= 0 ) loc_dot = last - loc_dot;

	input_file_type = -1;
	haslbn = FALSE;
	get_out = false;

	if ( lbn_type == true ) // use filename to decide lbn type
	{
		switch ( loc_dot )
		{
		case 3:
			// .nud extention
			if ( strcmpend ( name, ".nud" ) ) 
			{
				input_file_type = 0;
				haslbn = FALSE;
			}
			// .lbn extention
			if ( strcmpend ( name, ".lbn" ) )
			{
				input_file_type = 1;
				haslbn = TRUE;
			}
			if ( input_file_type < 0 ) get_out = true;
			break;
		case 2:
			// problem
			get_out = true;
			break;
		case 1:
			// .n extention
			if ( strcmpend ( name, ".n" ) )
			{
				input_file_type = 0;
				haslbn = FALSE;
			}
			else
			{
				get_out = true;
			}
			break;
		case 0:
			// . extention
			if ( strcmpend ( name, "." ) )
			{
				input_file_type = 2;
				strcat( name, "lbn" );
				haslbn = TRUE;
			}
			else
			{
				get_out = true;
			}
			break;
		case -1:
			// no extention
			if ( len > 0 && !strcmpend ( name, "." ) )
			{
				input_file_type = 2;
				strcat( name, ".lbn" );
				haslbn = TRUE;
			}
			else
			{
				get_out = true;
			}
			break;
		default:
			get_out = true;
			break;
		}
	}
	if ( get_out == true )
	{
		if ( from_ini == 1 ) 
		{
			printf("\n\nFile: %s from lintel.ini is not available.\n",
				name );
			from_ini = -1;
		}
		error = 1;
		name[0] = NULL;
		goto start;
	}

	// add directory to filename
	if ( dir_ok == true )
	{
		strcat ( dir, name );
		strcpy ( name, dir );
	}
	printf( "\n    " );
	if ( input_file_type == 0 )
	{
		sprintf ( nudesname, "%s", name );
		if ( ( infile = fopen( nudesname, "r" ) ) == NULL )
		{
			if ( infile ) fclose ( infile );
			printf ( "\n\n %s OOPS?\n", nudesname );
			bell ( 1, 1 );
			if ( from_ini == 1 ) 
			{
				from_ini = -1;
			}
			goto start;
		}
		printf ( "  Opened %s\n", nudesname );
	}
	else if ( input_file_type > 0 )
	{
		strcpy( finname, name );

		if ( ( infile = fopen ( finname, "r" ) ) == NULL )
		{
			if ( infile ) fclose ( infile );
			printf ( "\n   %s ?  OOPS - file not found.\n", finname );
			bell ( 1, 1 );
			if ( from_ini == 1 ) 
			{
				printf( "\n\n    File: %s from lintel.ini is not available.\n", name );
				from_ini = -1;
			}
			goto start;
		}

		printf ( "\n   opened input file %s\n", finname );

		add_id_num ( name, nudesname, ".n" );
		if ( ( nudesfile = fopen ( nudesname, "w" ) ) == NULL )
		{
			if ( nudesfile ) fclose ( nudesfile );
			printf ( "\n\n %s OOPS?\n", nudesname );
			bell ( 1, 1 );
			goto start;
		}
		printf ( "\n   created nudes file %s\n", nudesname );
	}
	if ( ( infile = fopen(nudesname, "r" ) ) == NULL )
	{
		if ( infile ) fclose ( infile );
		printf ( "\n\n %s OOPS?\n", nudesname );
		bell ( 1, 1 );
		goto start;
	}
} /* get_files */
/************************************************/

bool led_opena ( int min_fps, int max_fps, int min_beats, int max_beats )
{
	bool get_out;
	get_out = true;
	if ( lbn_fps < min_fps || lbn_fps > max_fps )
	{
		printf ( "\n   Oops: fps value is %d but must be between %d and %d\n", lbn_fps, min_fps, max_fps );
		get_out = false;
	}
	if ( lbn_bpm < min_beats || lbn_bpm > max_beats )
	{
		if ( lbn_bpm < 0 )
		{
			printf ( "\n   Oops: bpm value missing\n" );
		}
		else
		{
			printf ( "\n   Oops: bpm value is %d but must be between %d and %d\n", lbn_bpm, min_beats, max_beats  );
		}
		get_out = false;
	}
	return( get_out );
} /* led_opena */
/********************************************/

void led_param ( void )
/*
   set up parameters of .lbn interpretation from .ini file

   called by main
*/
{
	bool get_out;
	int min_fps;
	int max_fps;
	int min_beats;
	int max_beats;
	int lbn_figures_in;
	bool lbn_default;
	int lbn_fps_in;
	int lbn_bpm_in;

	lbn_fps = -1;
	lbn_bpm = -1;
	lbn_ppb = 23;
	min_fps = 1;
	max_fps = 250;
	min_beats = 25;
	max_beats = 250;	
	lbn_default = false;
	lbn_figures = 1;
	if ( get_if_ini () == true )
	{
		lbn_figures_in = get_ini_int ( "lbn_figures" );
		lbn_default = get_ini_bool ( "lbn_default" );
		lbn_fps_in = get_ini_int ( "lbn_fps" );
		lbn_bpm_in = get_ini_int ( "lbn_bpm" );

		if ( lbn_fps_in < min_fps || lbn_fps_in > max_fps 
			|| lbn_bpm_in < min_beats || lbn_bpm_in > max_beats )
				lbn_default = false;
		if ( lbn_default == true )
		{
			lbn_fps = lbn_fps_in;
			lbn_bpm = lbn_bpm_in;
			lbn_figures = lbn_figures_in;
		}
	}

	if ( lbn_default == false )
	{
		get_out = false;
		do
		{
			printf ( "\n   Please enter frames/second (%d-%d)", min_fps, max_fps );
			printf ( "\n            and beats/minute (%d-%d)", min_beats, max_beats );
			printf ( "\n            separated by a space\n   :" );
			if ( gets ( buf ) != NULL && buf[0] != 0 )
			{
				sscanf ( buf, "%d %d", &lbn_fps, &lbn_bpm );
				get_out = led_opena ( min_fps, max_fps, min_beats, max_beats);
			}
			else
			{
				lbn_fps = 25;
				lbn_bpm = 120;
				printf ( "\n   Oops: cannot read fps and bpm" );
				printf ( "\n   values set to %d and %d respectively\n",
					lbn_fps, lbn_bpm );
				get_out = true;
			}
		} while ( get_out == false );
	}
	lbn_fpp = double(lbn_fps)*doub60
					/ (double(lbn_bpm)*double(lbn_ppb));
	printf("\n   frames/pixel %g, fps %d, bpm %d, ppb %d\n",
				lbn_fpp, lbn_fps, lbn_bpm, lbn_ppb );
	printf("   number of figures %d\n",lbn_figures);
}/* led_param */
/************************************************/



int main(int argc, char* argv[])
/*
   calls initialise, lgetfiles, linter, openfile, compl,
         doframes, initsphere, initgraphics,
         checkeys, image, animate, getout,
         help, gluInit, glutKeyboardFunc, glutDisplayFunc,
         glutIdleFunc, glutMainLoop,
			get_ini, get_files, led_param
*/
{
	sprintf(ptitle,"lintel084");
	printf("\n   %s running\n",ptitle);

more:
	initialise();
	get_ini ( 0 );
	led_param();
	get_files ( NULL );
	if ( ok != 0 ) goto more;
	if (haslbn == TRUE)
	{
         fprintf(nudesfile,
            "*\n* created %s from %s using %s\n*\n",
            nudesname,name,ptitle);
         linter();
	}
	/*
	fstart = 0;
	if (ok == 0) openfile(); 
	   else 
	      if (ok != 1) getout(1);
	         else goto more;
	compl1();
	if (ok == 0) doframes();
       else 
          if (ok != 1) getout(1);
             else goto more;
	if (ok == 0)
	  initsphere();
       else 
          if (ok != 1) getout(1);
             else goto more;
	glutInit(&argc, argv); 
	initgraphics(); 
	printf("For interactive command list:\n");
	printf("    click in animation window, then press 'h' key\n");
	glutKeyboardFunc(checkeys); // register Keyboard handler 
	glutDisplayFunc(image);     // register Display handler  
	glutIdleFunc(animate);
	glutMainLoop();
	goto more;*/
}



