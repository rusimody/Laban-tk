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
// #include "stdafx.h"
#include <math.h>
#include <ctype.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "glut.h"
#endif

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

int headcol4 = 0;
int headcol6 = 0;

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
    lbn_fpp = double(lbn_fps)*doub60 / (double(lbn_bpm)*double(lbn_ppb)); calculated in function led_param
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
     fstart = int(inv2+lbn_fpp*double(jy-ystart));//inv2 is 0.5
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
	-4 = L arm
	-3 = L gesture
    -1 = L support
	 1 = R support
	 3 = R gesture
	 4 = R arm

    called by linter,
*/
{
   int k;
   int kc;//column number
   int kwx;

   for (k = 0; k < nlabs; ++k)
   {
      kwx = lbn[k].x + (lbn[k].w/2);
      kc = (kwx - lcentre)/STEP;//here STEP is 12
      if (kwx < lcentre)//lcentre is x coordinate of middle stav
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

A structure Symbol is created as follows:
      struct Symbol {
        int i;       // item in menu
	int x;       // horizontal position of left side
	int y;       // vertical position of bottom
	int s;       // drawing step size
	int w;       // width
	int h;       // height
	int d;       // height indicator //0,1,2,3 : low,mid,high,blank
	char m;      // menu
	//below data not present in .lbn file , so hardcoded or derived from available data
	int x2;      // horizontal position of right side  = x+w
	int y2;      // vertical position of top = y+h
	int a;       // TRUE = 0 if already done
	int b;       // bent indicator // not implemented as given -1 value
	int c;       // column position relative to right support column
	int l;       // lbn file line number
	};
	Extra variables set :
	xmin = min(x)
	xmax = max(x+w)
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

staff[TMAX][6].
   staff[k][0] = stff[j][0]; // current staff index
   staff[k][1] = stff[j-1][1];// left staff x coordinate
   staff[k][2] = stff[j][1]; // current staff x cooridnate
   staff[k][3] = stff[j+1][1]; // right staff x coordinate
   staff[k][4] = -1;   // decides if staff represents a 'MAN' or'Woman'
   staff[k][5] = TODO;
*/
{
   int j,jp,jq;
   int k,kp,kq;
   int staffstart;//y coordinate of middle Stav
   int nstaffstart;//index of the staves
   int nstff;//number of staves
   int stff[TMAX][2];//temporary array to store staff info
   int gen;//stores the gender

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
      if(nstaff == 1)
	{
	  printf("\nSelect 1 for MAN and 2 for WOMAN\n");
	  scanf("%d",&gen);
	  if(gen == 1)
	    staff[j][4] = MAN;
	  else
	    staff[j][4] = WOMAN;
	}

      else if(j==0)
	  staff[j][4] = MAN;
      else if(j==1)
	staff[j][4] = WOMAN;

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
   int piv;//angle of turn

   if ( (jm == Rotn)&&(nbar > 0)&&
	 ((jc == -2)||(jc == -1)||(jc == 1)||(jc == 2)) )
   {
     piv = lgetpin();//finds the pin in the symbol and returns the angle
      if (fstart < 1) fstart = 1;
      g = lhasgesture(j);//checks the gesture column for (-3 +3)for ovelapping gestures
      t = lhastap(j);//checks if the j'th symbol has overlapping ground contact
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
   int mx,my;//coordinates of male pins if exist
   int wx,wy;//coordinates of female pins if exist

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
	 //if both male and female pins exist then do this
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
  int bend;//useless
  int k,kmax;//kmax is index of symbol with ymax
  int ymax;//highest y2 of a symbol

   ystart = 0;
   yend = lbn[0].y;
   ymax = yend;
   sstart = 0;
   ssend = nlabs;
   //finds the starting symbol and stores its y in ystart
   for (k = 0; k < nlabs; ++k)
   {
      if (lbn[k].m == Bars)
      {
         if (lbn[k].i == bstart)
         {
            sstart = k;
            ystart = lbn[k].y;//break should be used to avoid redundancy
         }
      }
   }
   bend = bstart + blength;
   //useless
   for (k = (sstart+1); k < nlabs; ++k)
   {
      if (lbn[k].m == Bars)
      {
         if (lbn[k].i == bend)
            ssend = k;
      }
   }
   //finds the last symbol and stores its y in ymax
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
   //f_max is total number of frames required for the dance
   f_max = 2 + int(lbn_fpp*double(ymax));
	printf("\n   lsetrange: pixels %d, frames %d\n",ymax,f_max);
} /* lsetrange */
/****************************************************/

void lcopyfigs(char* renOrfile)
/*
   finish off

   called by linter,
   calls     lgetout,
*/
{
	if (renOrfile[0] == 'r') {
		sprintf(figsname,"lintel.n");
	}
	else if (renOrfile[0] == 'n') {
		sprintf(figsname,"lintelnudes.n");
	}
	else{
		printf("Enter a valid option r for render n for nudes\n");
		exit(0);
		}
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
   nf = 0;//number of figures
   nm = 0;//no. of male figs
   nw = 0;//no. of female figs
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
     track = TRUE;//follows the figure while dance
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
  int g;//stores the index of Dirn symbol being modified
   int k;
   int ki,kx,kx2,ky,ky2;//temporary variables for i, x, x2, y, y2 of symbol
   int jy2h;
   char km;//temporary variable for menu name

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
   calls respective subroutines
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
		&&(colm[nc] == Area)&&(jd == LOW))
	{
		colm[nc] = CHEST;
		fprintf(nudesfile,"quadratic 10 60 bendto chest ribs stomach 0 0 45\n");    /*2015 Samir Patil/Manish Adkar Added missing pelvis bend option*/
		fprintf(nudesfile,"quadratic 10 60 bendto stomach waist pelvis 0 0 -45\n");
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
	  piv = lgetpin ( );//finds the pin belonging to Area symbol and returns the angle
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
void ldohead()
{
  if(ji == 1)
          {
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck -33 x\n",fstart,fend);
          }
        else if(ji == 5)
          {
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck 50 x\n",fstart,fend);
          }
        else if(ji == 3)
          {
                  fprintf(nudesfile,"quadratic %d %d bendby head throat neck 33 z\n",fstart,fend);
          }
        else if(ji == 8)
          {
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck -33 z\n",fstart,fend);
          }
        else if(ji == 2)
          {
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck -33 x\n",fstart,fend);
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck 33 z\n",fstart,fend);
          }
        else if(ji == 4)
          {
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck 50 x\n",fstart,fend);
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck 33 z\n",fstart,fend);
          }
        else if(ji == 7)
          {
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck 50 x\n",fstart,fend);
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck -33 z\n",fstart,fend);
          }
        else if(ji == 9)
          {
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck -33 x\n",fstart,fend);
            fprintf(nudesfile,"quadratic %d %d bendby head throat neck -33 z\n",fstart,fend);
          }
        else if(ji == 11)
          {
            fprintf(nudesfile,"quadratic %d %d bendto head throat neck 0 0 0\n",fstart,fend);
          }
}

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
	  lassign ();//assigns the parameter of current symbol to temporary varibles
	  lsetframes ();//sets the frame numbers for a particular symbol(fstart , fend, frange)
		fprintf(nudesfile,"* %d %3d %s",lbn[j].a,jc,lbnline[j]);
		if ( lbn[j].a == TODO )
		{
			if ( jm == Bars )
			  ldobar ();//increments nbar
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
				 else if(jc == 4 && (jm==Keys)&&(ji == 8))
				 {
				   headcol4 = 1;
				 }
				 else if(jc == 6 && (jm==Keys)&&(ji == 8))
				 {
				   headcol6 = 1;
				 }
				 else if(headcol4 == 1 && (jm == Dirn || jm == Rotn)&&jc == 4)
				 {
				   ldohead();
				   headcol4 = 0;
				 }
				 else if(headcol6 == 1 && (jm == Dirn || jm == Rotn)&&jc == 6)
				 {
				   ldohead();
				   headcol6 = 0;
				 }
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

void linter(char* renOrfile)
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

*/
{
   lbnread();
   lsorty();//sorts the lbn structure array by y parameter
   lfindstaff();
   lsetrange();
   lselectfig();
   lcopyfigs(renOrfile);
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
	nbar = -1;//number of bars processed
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

void shift(double x, double y, double z)
/*
   this adds 'x,y,z' to all centres and joints in lists
   'elist' and 'jlist'.

   called by  action, dogrofig, dogrojt, domovjnt,
              twirl, dodrag,
*/
{
   int e,j,n ;


   for (  n = 0 ; n < ecount ; ++ n )
   {
      e = elist[n] ;
      cen[e][0] += x ;
      cen[e][1] += y ;
      cen[e][2] += z ;
   }
   for (  n = 0 ; n < jcount ; ++ n )
   {
      j = jlist[n] ;
      jnt[j][0] += x ;
      jnt[j][1] += y ;
      jnt[j][2] += z ;
   }
}  /* shift */
/*****************************/

void rset(double r[3][3], double angl, int axis)
/*
   set up the rotation matrix 'r' for a rotation of
   'angl' radians about 'axis'.

   called by  input, setobs, dobalanc, dospinby,
*/
{
      double v[5] ;
      int i,j,k;

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

void matmul(double a[3][3], double b[3][3], double c[3][3])
/*
     this multiplies matrix 'b' by 'a' and puts the product
     in 'ans'.

     called by  dobalanc, matrot, dospinto, dospinby, getwist.
                getaxes, sepn,  getmat,

	  21 Sep 2006  unrolled loops
*/
{
	double ans00,ans01,ans02,ans10,ans11,ans12,ans20,ans21,ans22;
//
	ans00 = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0];
	ans01 = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1];
	ans02 = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2];
	ans10 = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0];
	ans11 = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1];
	ans12 = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2];
	ans20 = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0];
	ans21 = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1];
	ans22 = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2];
//
	c[0][0] = ans00;
	c[0][1] = ans01;
	c[0][2] = ans02;
	c[1][0] = ans10;
	c[1][1] = ans11;
	c[1][2] = ans12;
	c[2][0] = ans20;
	c[2][1] = ans21;
	c[2][2] = ans22;
}  /* matmul */
/**********************************************************/

void vecmul(double v[EMAX][3], double m[3][3], int n)
/*
   multiply the 'n'th vector from array 'v'
   by matrix 'm'.

   called by touch, dogrojnt, domovjnt, domoveby, doabut,
             twirl,
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

void rotget(double r[3][3], double unr[3][3], int n)
/*
   form a rotation matrix r and its inverse unr
   from the nth entries in quat

   called by  dobalanc, matrot, dospinto, dospinby,
              dogrojnt, domovjnt, doabut, doground,
*/
{
      int i,j ;
      double cp,sp,x,y,z,m,xsp,ysp,zsp,xm,ym,zm,xym,xzm,yzm ;

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
}  /* rotget */
/**************************************/

void rotput(double r[3][3], int n)
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

   see 'Control of round-off propagation in articulating the
        human figure', D.Herbison-Evans and D.S.Richardson,
        Computer Graphics and Image Processing,
        vol 17, pp. 386-393 (1981)

   called by matrot, dospinto, doangles, dolimb,
             getwist, store3,
*/
{
      int j,k ;
      double a[3][3],b[3],d[3],e,f,g,c,s,trace ;
      double csq;

      b[0] = r[1][2]-r[2][1] ;
      b[1] = r[2][0]-r[0][2] ;
      b[2] = r[0][1]-r[1][0] ;
      e = b[0]*b[0]+b[1]*b[1]+b[2]*b[2] ;
      trace = r[0][0]+r[1][1]+r[2][2] ;
      if (e > doub0) g = sqrt(e); else g = doub0;
      if (e > tolr)
      {
         f = doub1/g ;
         quat[n][0] = f*b[0] ;
         quat[n][1] = f*b[1] ;
         quat[n][2] = f*b[2] ;
/*
     use g=2s, and trace=1+2c to find s and c -
*/
         s = inv2*g;
         csq = doub1-s*s;
         if (csq > doub0) c = sqrt(csq); else c = doub0;
         if (trace < doub1) c = -c;
         quat[n][3] = s ;
         quat[n][4] = c ;
      }
      else
/*
   symmetric matrix (180 or 360 degree rotation) -
*/
      {
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
      }
      for (k = 0; k < 5; ++k)
      {
         if ((quat[n][k] > -tolr) && (quat[n][k] < tolr))
            quat[n][k] = 0;
         if (quat[n][k] >  doub1) quat[n][k] =  doub1;
         if (quat[n][k] < -doub1) quat[n][k] = -doub1;
      }
}  /* rotput */
/********************************************/

void mkquat(int n, double a1, double a2, double a3)
/*
   convert angles a1,a2,a3 (in radians) into quat entries

   called by dospinto, inframe,
*/
{
      int j;
      double s1,c1,s2,c2,s3,c3 ;

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
}  /* mkquat */
/**********************************************************/


void matrot(double r[3][3], int n)
/*
      this rotates the 'n'th ellipsoid by rotation matrix 'r'.

      called by twirl.
      calls     rotget, matmul, rotput,
*/
{
      double ro[3][3],unro[3][3] ;

      rotget(ro,unro,n) ;
      matmul(r,ro,ro) ;
      rotput(ro,n) ;
}  /* matrot */
/**********************************************/

void twirl(double x, double y, double z, double r[3][3])
/*
   rotates all the rotation matrices 'quat', centres 'cen',
   and joint vectors 'jnt', of ellipsoids and joints in lists
   'elist' and 'jlist' about a point 'x,y,z' using rotation
   matrix 'r'.

   called by  dospinto, dospinby, store3,
   calls      shift, matrot, vecmul, setels,
*/
{
      int e,j,k ;

      shift(-x,-y,-z) ;
      if (ecount >= 0)
      {

/*   rotate the ellipsoids and their centres- */

         for (  e = 0 ; e < ecount ; ++e )
         {
            k = elist[e];
/*  don't rotate world ! :- */
            if (k != 0)
            {
               matrot(r,k) ;
               vecmul(cen,r,k) ;
            }
         }
      }

/*   now for the joints- */

      if (jcount >= 0)
      {
         for (  j = 0 ; j < jcount ; ++j )
         {
            k = jlist[j];
            vecmul(jnt,r,k) ;
         }
      }

/*   put body part back where it came from- */
      shift(x,y,z) ;
}  /* twirl */
/*****************************/

void dospinto(double xx[3], int refell, double ang[3], double pro)
/*
     spins all ellipsoids in 'elist' and joints in 'jlist'
     so that 'ellpsd' is proportion 'pro' of the way to the
     orientation specified as a rotation 'ang' radians
     about axes of the reference ellipsoid 'refell'
     about point 'xx'.

   called by  action, dodrag,
   calls      rotget, rotput, mkquat, matmul, twirl,
*/
{
      double alfa,nualfa;
      double mv[3][3],unmv[3][3];
      double rf[3][3],unrf[3][3];
      double tg[3][3],untg[3][3];
      double mt[3][3],nu[3][3];
/*
   set rotation matrices of moving and reference ellipsoids -
*/
      rotget(mv,unmv,ellpsd);
      rotget(rf,unrf,refell);

/*   find target rotation matrix, and refer to refell- */

      mkquat(EMAX+1,ang[0],ang[1],ang[2]);
      rotget(tg,untg,EMAX+1);
      matmul(rf,tg,tg);

/*   find increment rotation matrix to reach target- */

      matmul(tg,unmv,mt);
      rotput(mt,EMAX+1);
      if (( quat[EMAX+1][3] == doub0 )
		  && ( quat[EMAX+1][4] == doub0 ))
      {
         ok = 53;
		 printf("dospinto no sine and cosine");
         alfa = doub0;
      }
      else alfa = atan2(quat[EMAX+1][3],quat[EMAX+1][4]) ;
      nualfa = pro*alfa ;
      if (alfa > pi ) nualfa = pro*(alfa - twopi);
      if (alfa < -pi) nualfa = pro*(alfa + twopi);
      quat[EMAX+1][3] = sin(nualfa);
      quat[EMAX+1][4] = cos(nualfa);
      rotget(nu,mt,EMAX+1);
      twirl(xx[0],xx[1],xx[2],nu);
}  /* dospinto */
/*************************************/

void dospinby(double xx[3], int refell, double angl, int axis)
/*
   spins all ellipsoids and joints in 'elist' and 'jlist'
   about a point 'x', by an angle 'angl' radians relative to
   an 'axis' of reference ellipsoid 'refell'.

   called by dobalanc, action, dobend, dotouch, fun, dodrag,
   calls     rset, rotget, matmul, twirl,
*/
{
      int j,k;
      double r[3][3],ro[3][3],unro[3][3];
/*
        do transformation on required coordinates
        aligned with axes of the reference ellipsoid-
*/
      rset(r,angl,axis);
      rotget(ro,unro,refell);
      matmul(r,unro,r);
      matmul(ro,r,r);
      for (j = 0; j < 3; ++j)
         for (k = 0; k < 3; ++k)
            if ((r[j][k] > -tolr) && (r[j][k] < tolr)) r[j][k] = 0;
      twirl(xx[0],xx[1],xx[2],r);
}  /* dospinby */
/**********************************************************/

void mkang(int n)
/*
   get angles in radians from 'n'th entry in 'quat' into
   array 'ang'.

   called by  doangles, store3, storeang,
*/
{
      double x,y,z,s1,c1,m1 ;
      int j;

      x = quat[n][0] ;
      y = quat[n][1] ;
      z = quat[n][2] ;
      s1 = z ;
      m1 = doub1-z*z ;
      if (m1 > doub0) c1 = sqrt(m1) ;
         else c1 = doub0 ;
      if ((x == doub0 ) && ( y == doub0))
          ang[0] = doub0;
      else
          ang[0] = atan2(y,x) ;
      if ((s1 == doub0 ) && ( c1 == doub0))
      {
          ok = 54;
          printf("mkang: n %d, s1 %f, c1 %f",
              n,s1,c1);
          ang[1] = doub0;
      }
      else ang[1] = atan2(s1,c1) ;
      if ((quat[n][3] == doub0 ) && ( quat[n][4] == doub0))
      {
          ok = 52;
          printf("mkang: n %d, quat[n][3] %f, quat[n][4] %f",
              n,quat[n][3],quat[n][4]);
          ang[2] = doub0;
      }
      else
	  ang[2] = atan2(quat[n][3],quat[n][4]) ;
      for (j = 0; j < 3; ++j)
      {
         if (ang[j] < doub0) ang[j] += twopi;
         if (ang[j] > twopi) ang[j] -= twopi;
      }
}  /* mkang */
/*****************************************/

void storeang(int f, int e, double a1, double a2, double a3)
/*
   convert angles a1,a2,a3 in degrees into quaternions
   and find direction vector of y axis
   for frame f and ellipsoid e

   called by store3,
*/
{
      double s1,c1,s2,c2,s3,c3;

      s1 = sin(a1) ;
      c1 = cos(a1) ;
      s2 = sin(a2) ;
      c2 = cos(a2) ;
      s3 = sin(a3) ;
      c3 = cos(a3) ;

      qu3[f][e][0] = a3*degree ;
      qu3[f][e][1] = c2*c1 ;
      qu3[f][e][2] = c2*s1 ;
      qu3[f][e][3] = -s2 ;

}  /* storeang */
/**********************************************************/

void doangles(int el, int re, double val[EMAX], int var0, int var1, int var2)
/*
  store the angles of 'el' relative to 're' in 'val' array.
  in degrees.

  called by action, dodrag,
  calls  matmul, rotget, rotput, mkang,
*/
{
   double mvro[3][3],mvunro[3][3];
   double stro[3][3],stunro[3][3];
   double r[3][3];

   rotget(stro,stunro,re) ;
   rotget(mvro,mvunro,el) ;
   matmul(stunro,mvro,r) ;
   rotput(r,EMAX) ;
   mkang(EMAX) ;
   val[var0] = ang[0]*degree ;
   val[var1] = ang[1]*degree ;
   val[var2] = ang[2]*degree ;
   if ((val[var0] > doub179)&&(val[var0] < doub181))
   {
	   val[var0] -= doub180;
	   val[var2] = -val[var2];
   }
   if (val[var1] > doub180) val[var1] -= doub360;
}  /* doangles */
/*********************************/

void dobend(double angle, int axis)
/*
  implements flex(38), rotate(39), abduct(40).

  called by action,
  calls     dospinby,
*/
{
   int refell ;
   int left ;

   refell = ellpsd ;
   if (t == rotate_keyword_code) goto lab1 ;
   if (ellpsd == coel[join][0]) refell = coel[join][1] ;
   if (ellpsd == coel[join][1]) refell = coel[join][0] ;
/*
  assume odd-numbered ellipsoids are on left side of figure-
*/
lab1: if (((ellpsd-figell[fig])%2) == 0)
          left = TRUE; else left = FALSE;
/*
  flex-
*/
   if ((t == flex_keyword_code)&&(knee[join])) angle = -angle ;
/*
  rotate-
*/
   if ((t == rotate_keyword_code)&&( left == FALSE)) angle = -angle ;
/*
  abduct-
*/
   if ((t == abduct_keyword_code)&&(left == TRUE)) angle = -angle ;
   dospinby(xx,refell,angle,axis) ;
}  /* dobend */
/****************************************************/

/*   compl42.h - based on complu

     This translates a NUDES script into a compact
     form for use by 'perfrm'.

   subroutines-
      getout
      llength
      nexts
      match
      value
      addname
      getint
      inells
      injts
      inlims
      inname
      dojoin
      checkin
      valadd
      parset
      inperf
      compl
*/

/***************************************/

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

int llength(void)
/*
   find length of line

   called by nexts,
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

int nexts_a ( char c )
{
		char astk = '*';
		char tab = '	';
		int code;

		code = 0;
		if ( c == astk ) code = 1;
		if ( c == '\n' ) code = 2;
		if ( c == blank
				|| c == tab
				|| c == null ) code = 3;
		if ( c == '.'
				|| ( c == '+' )
				|| ( c == '-' )
				|| ( c == '_' )
				|| ( c >= '0' ) && ( c <= '9' )
				|| ( c >= 'a' ) && ( c <= 'z' )
				|| ( c >= 'A' ) && ( c <= 'Z' ) ) code = 4;
		return code;
} /* nexts_a */
/*****************************************/

void nexts(void)
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

     called by inperf, inname, inells, injts, inlims, parset,
     calls     llength, getout,
*/
{
   int j;
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
lab10:
   start = 0 ;
   if (fgets(line,BMAX,infile) == NULL)
   {
      printf("\nOOPS in nexts: unexpected end of file\n");
      printf("missing STOP command?\n");
	   ok = 3;
      getout(ok);
      goto rtrn;
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
	  if (line[j] == '_') goto lab3;
      goto lab10;
lab1: ;
   }
/*
     rest of line empty, so look at next -
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
      if (line[start] == '\n') goto rtrn ;
      if (line[start] == blank) goto rtrn ;
      if (line[start] == tab) goto rtrn ;
      if (line[start] == null) goto rtrn ;
      if (line[start] == '.') goto lab5;
      if ((line[start] == '+') || (line[start] == '-')) goto lab5;
      if ((line[start] >= '0') && (line[start] <= '9')) goto lab5;
      if ((line[start] >= 'a') && (line[start] <= 'z')) goto lab5;
      if ((line[start] >= 'A') && (line[start] <= 'Z')) goto lab5;
      if (line[start] == '_') goto lab5;
      goto rtrn;
lab5:
      string[length] = line[start] ;
      ++length ;
   }
   start = -1 ;

rtrn:;
} /* nexts */
/***************************************/

int match(int nnames, int lengths[EMAX], char names[EMAX][BMAX])
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
               parset, addnam,
*/
{
   int j,k ;
   int found;
   int no;
   char sp = null;

   no = -1 ;
   for (k = 0; k <= nnames; ++k)
   {
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
   return(no);
} /* match */
/***************************************/

double value(void)
/*
     find the value of the number which is encoded as
     'length' characters in array 'string' and put it into 'v'.
     set ok false if string is not a number.

     called by inperf, inells, injts, parset,
*/
{
	double v;
	double nsign;
	double expon;
	int k;
	int frac;
	int d;
	char point = '.';
	char minus = '-';
	char plus = '+';

	pok = TRUE;
	v = doub0;
	nsign = doub1;
	expon = doub1;
	frac = FALSE;
	if ( ( length < 0 ) || ( length > BMAX ) )
	{
		pok = FALSE;
		return( v );
	}
	for ( k = 0; k < length; ++ k )
	{
		//	if a decimal point encountered, start decimal place counter
		if (string[k] == point )
		{
			frac = TRUE;
			goto lab3;
		}
		if ( string[k] == plus ) goto lab3;
		if ( string[k] == minus )
		{
			nsign = -nsign;
			goto lab3;
		}
		for ( d = 0; d < 10; ++ d )
		{
			if ( string[k] == dig[d] ) goto lab5;
		}
		pok = FALSE;
		return ( v );
lab5:
		v = v * doub10 + double(d);
		if ( frac == TRUE ) expon = expon / double(10);
lab3:;
	}
	v = v * expon * nsign;
	return( v );
} /* value */
/***************************************/

int addnam(int n, char names[EMAX][BMAX], int isvar, int lengths[EMAX])
/*
     add a name to a list of names.
	 return the number of names in the list.

     called by inperf, inname, inells, injts, parset,
     calls     match,
*/
{
   int k;
   int no ;
   int nnames;

   nnames = n;
/*
     see if name already exists-
*/
   no = match(nnames,lengths,names);
   if (no >= 0)
   {
      printf("addnam: string  %s confusable with ",string);
      for (k = 0; names[no][k] != null; ++k)
         printf("%c",names[no][k]);
      printf("\n");
   }
   if (isvar == FALSE)
/*
     non-variables must first check variable list-
*/
   {
      no = match(nvars,varlen,vname) ;
      if (no > 0)
      {
         printf(
            "name  %s  confusable with variable ",string);
         for ( k = 0; vname[no][k] != null ; ++ k)
            printf("%c",vname[no][k]);
         printf("\n");
      }
   }
   else
/*
     variables must check all name lists-
*/
   {
      no = match(nfigs,figlen,fname) ;
      if (no > 0)
      {
         printf("variable  %s  confusable with figure ",
            string);
         for ( k = 0; fname[no][k] != null; ++ k)
            printf("%c",fname[no][k]);
         printf("\n");
      }
      no = match(ne,ellen,ename) ;
      if (no > 0)
      {
         printf("variable  %s  confusable with ellipsoid ",
            string);
         for ( k = 0; ename[no][k] != null; ++ k)
            printf("%c",ename[no][k]);
         printf("\n");
      }
      no = match(njts,jntlen,jname) ;
      if (no > 0)
      {
         printf("variable  %s  confusable with joint ",
            string);
         for ( k = 0; jname[no][k] != null; ++ k)
            printf("%c",jname[no][k]);
         printf("\n");
      }
      no = match(nsubs,sublen,sname) ;
      if (no > 0)
      {
         printf("variable  %s  confusable with subroutine ",
            string);
         for ( k = 0; sname[no][k] != null; ++ k)
            printf("%c",sname[no][k]);
         printf("\n");
      }
      no = match(nfiles,fillen,tname) ;
      if (no > 0)
      {
         printf("variable  %s  confusable with file name ",
            string);
         for ( k = 0; tname[no][k] != null; ++ k)
            printf("%c",tname[no][k]);
         printf("\n");
      }
   }
/*
     add name to list-
*/
   if (nnames > EMAX)
   {
      printf("\nOOPS addnam: %s makes more than max of %d names\n",
         string,EMAX);
      ok = 84 ;
   }
   else
   {
      for (  k = 0 ; k < length ; ++ k )
         names[nnames][k] = string[k] ;
      for ( k = length ; k < BMAX; ++ k )
         names[nnames][k] = null;
      lengths[nnames] = length;
   }
   ++nnames ;
   return(nnames);
} /* addnam */
/***************************************/

int getint(void)
/*
     find value of positive integer which is encoded as 'length'
     characters in array 'string', and put its value into 'k'.
     set 'pok' false if string not a positive integer.

     called by parset, inname,
*/
{
	int j, k, m, ths;
	char plus = '+';

	if ( length <= 0 )
	{
		k = 0;
		pok = FALSE;
	}
	else
	{
		pok = TRUE;
		k = 0;
		for( j = 0; j < length; ++j )
		{
			if ( string[j] != plus )
			{
				ths = -1;
				for( m = 0; m < 10; ++m )
					if ( string[j] == dig[m] ) ths = m;

				if ( ths < 0 )
				{
					pok = FALSE;
					return( k );
				}
				k = 10 * k + ths;
			}
		}
	}
	return( k );
} /* getint */
/***************************************/

int inells(void)
/*
     read in next ellipsoid and its axis lengths.

     called by inperf, injts,
     calls     nexts, match, addnam, value,
*/
{
	int el, k;

	nexts();
	el = match ( ne, ellen, ename );
	if ( el < 0 )
	{
		ne = addnam ( ne, ename, 0, ellen );
		el = ne - 1;
	}
	for ( k = 0; k < 3; ++ k )
	{
		nexts ();
		semiax[k] = value ();
		if ( pok == FALSE )
		{
			printf("\nOOPS inells: ellipsoid snag with  %s\n",
				string );
			ok = 83;
			return ( el );
		}
	}
	return ( el );
} /* inells */
/***************************************/

void injts(void)
/*
     read in the next joint, the ellipsoids it connects, and the
     position of the joint relative to each ellipsoid centre.

     called by inperf,
     calls     nexts, addnam, inells,
*/
{
   int el,jt,k,e ;
   char klet = 'k';
   char nlet = 'n';
   char elet = 'e';

   nexts();
   njts = addnam(njts,jname,0,jntlen);
   jt = njts-1;
   if ( ok > 0 ) goto lab4 ;
/*
     is it a knee -
*/
   knee[jt] = FALSE;
   for (  k = 0 ; k < (length-1) ; ++ k )
   {
      if ((string[k] == klet)
       && (string[k+1] == nlet)
       && (string[k+2] == elet)) knee[jt] = TRUE;
   }
/*
  do the two ellipsoids
*/
   for (  e = 0 ; e <= 1 ; ++ e )
   {
      el = inells();
      if ( ok > 0 ) goto lab5 ;

      dcon[jt][e][0] = semiax[0] ;
      dcon[jt][e][1] = semiax[1] ;
      dcon[jt][e][2] = semiax[2] ;
      coel[jt][e] = el ;
   }
   goto rtrn ;
/*
     snags-
*/
lab5: printf("\nOOPS injts with %s \n",string);
   njts = njts-1 ;
   goto rtrn ;

lab4: printf("\nOOPS : injts more joints than max %d\n",EMAX );
   ok = 82 ;
rtrn:;
} /* injnts */
/***************************************/

void inlims(void)
/*
     read in limits for a joint.

     called by main,
     calls     nexts, match, value,

*/
{
   int k,m,n;

   nexts();
   n = match(njts,jntlen,jname);
   if (n < 0)
   {
      printf("limits given for nonexistent joint: %s\n",
         string);
      getout(1);
      if (ok == 1) goto rtrn;
   }
   for (k = 0; k < 3; ++k)
   {
      for (m = 0; m < 2; ++m)
      {
         nexts();
         lim[n][k][m] = value();
      }
   }
rtrn: ;
} /* inlims */
/***************************************/

int inname(int n, int isvar, int lengths[EMAX], char names[EMAX][BMAX])
/*
     read in a number and then that many names.

     called by inperf,
     calls     nexts, getint, match, addnam,
*/
{
   int e;
   int nitems;
   int nnames;
   int no;

   nnames = n;
/*
     get number of names in list
*/
   nexts();
   nitems = getint();
   if ( ok > 0 )
   {
	   printf("inname problem- number of names not stated on\n");
	   printf("%s\n",line);
	   goto rtrn;
   }
/*
     get names in list
*/
   if (nitems <= 0) goto rtrn ;
   for (  e = 0 ; e < nitems ; ++ e )
   {
      nexts();
      if (length < 1) goto rtrn ;
      no = match(nnames,lengths,names);
      if (no <= 0)
         nnames = addnam(nnames,names,isvar,lengths);
   }
rtrn:
   return(nnames);
} /* inname */
/***************************************/

void dojoin(void)
/*
   this works out the positions of the centres of each ellipsoid
   'cen' and the joints 'jnt', using the data 'dcon'

   called by  compl,
*/
{
      int e,ecount,newc,old,newel,oldel,j,k;
      int jfound[EMAX];
      int efound[EMAX];
      int elist[EMAX];
/*
     clear found and put all ellipsoids at origin -
*/
      for (  e = 0 ; e < ne ; ++ e )
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
                  if (coel[j][1] == oldel) newc = 0 ;
                  if (coel[j][0] == oldel) newc = 1 ;
                  jfound[j] = TRUE ;
                  old = 1-newc ;
                  newel = coel[j][newc] ;

/*   check for legality- */

                  for (  k = 0 ; k < ecount ; ++ k )
                  {
                     if (newel == elist[k])
                     {
                        printf(
   "cyclic joint structure - perhaps delete doub1 of the joints \n");
                        printf(
                           " %d %d %d %d %d %d %d %d %d %d\n",
                        ecount,ne,njts,e,j,newc,old,k,oldel,newel);
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
                      cen[newel][k] = jnt[j][k]-dcon[j][newc][k] ;
                  }
                }
            }
        }

/* locate an ellipsoid in some other figure - */

        for (newel = 0; newel < ne; ++ newel)
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
} /* dojoin */
/*******************************************/

void checkin(void)
/*
     check the specifications of the actions
     to be performed.

     called by  compl,
*/
{
   int newa;
   int j;
   int subfirst;

   newa = TRUE;
   subfirst = TRUE;
/*
     check for snags-
*/
   for (  j = 0 ; j <= ne ; ++ j )
   {
      if (ellfig[j] < 0)
      {
         printf("\nOOPS checkin: ellipsoid %d %s defined but not in a figure\n",
      		  j,ename[j]);
	     ok = 79 ;
      }
      if (ax[j][0]*ax[j][1]*ax[j][2] <= doub0)
      {
         printf("\nOOPS checkin: ellipsoid %d %s not dimensioned\n",
		     j,ename[j]);
	     ok = 80 ;
      }
   }
   if (fstop < fstart)
   {
      printf("\nOOPS  checkin: view %d %d - produces no frames\n",
          fstart,fstop );
      ok = 81;
   }
   for (  j = 1 ; j <= nsubs ; ++ j )
   {
      if ((ok == 0) && (called[j] == FALSE))
      {
	     if (subfirst == TRUE)
	     {
	        subfirst = FALSE;
	        newa = FALSE;
	     }
      }
   }
   if ((nvals+nvars) > EMAX)
   {
      printf("\nOOPS  checkin %d  non-integer values + %d variables\n",
             nvals,nvars);
      printf(" give more than max of %d \n",EMAX);
		ok = 82;
   }
} /* checkin */
/***************************************/

int valadd(double v)
/*
     if 'v' is not in array 'val', then put it at the end.
     wherever it is, put its index into 'j'.

     called by parset,
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
lab10: printf("\nOOPS in valadd: no. of constants %d > max %d\n",
          nvals,EMAX );
   ok = 90 ;

rtrn: return(j);
} /* valadd */
/***************************************/


int parset(int contrl)
/*
     decode the parameters of the jth action using:
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

     called by inperf,
     calls  nexts, getint, value, valadd, match, addnam,
*/
{
	int k;
	int nax = 2;
	int attach = 8;
	int detach = 9;
	double v;

	k = 0;
	if ( contrl == 0 ) return( k );
	nexts();

	//pick an integer constant-
	if ( ( contrl != 1 ) && ( contrl != 8 ) ) goto lab1;
	k = getint();
	if ( pok == TRUE ) return( k );

	//pick a double constant-
	pok =  TRUE;
	v = value();
	if ( pok == FALSE ) goto lab1;

	k = valadd(v);
	if ( pok == FALSE ) goto lab1;

	k = -k;
	return( k );

lab1://pick an axis-
	if ( ( contrl != 5 ) && ( contrl != 8 ) ) goto lab2;

	k = match ( nax, axlen, axnam );
	if ( k >= 0 ) return( k );

lab2://try for a variable-
	k = match ( nvars, varlen, vname );
	if ( k < 0 ) goto lab3;
	usevar[k] = 1;
	if ( contrl != 7 ) k = k - EMAX + 1;
	return( k );

lab3://pick an ellipsoid-
	if ( ( contrl != 2 ) && ( contrl != 8 ) ) goto lab4;
	k = match ( ne, ellen, ename );
	if ( k < 0 ) goto lab4;
	return( k );

lab4://pick a joint-
	if ( ( contrl != 3 ) && ( contrl != 8 ) ) goto lab5;
	k = match ( njts, jntlen, jname );
	if ( k >= 0 ) return( k );
	if ( ptype != attach ) goto lab5;

	njts = addnam ( njts, jname, 0, jntlen );
	k = njts - 1;
	return( k );

lab5://pick a figure-
	if ( ( contrl != 4 ) && ( contrl != 8 ) ) goto lab7;
	k = match ( nfigs, figlen, fname );
	if ( ptype == detach ) goto lab6;
	if ( k < 0 ) goto lab7;
	return( k );

lab6://action detach- accept any figure but "all"-
	if ( k == 0 ) goto lab7;
	if ( k > 0 ) return( k );
	nfigs = addnam ( nfigs, fname, 0, figlen );
	k = nfigs - 1;
	return( k );

lab7://pick a subroutine call-
	if ( ( contrl != 6 ) && ( contrl != 8 ) ) goto lab8;
	k = match ( nsubs, sublen, sname );
	if ( k <= 0 )
	{
		nsubs = addnam ( nsubs, sname, 0, sublen );
		k = nsubs - 1;
	}
	called[k] = TRUE;
	return( k );

lab8://pick a file name-
	if ( ( contrl != 9 ) && ( contrl != 8 ) ) goto lab9;
	k = match ( nfiles, fillen, tname );
	if ( k > 0 ) return( k );
	nfiles = addnam ( nfiles, tname, 0, fillen );
	k = nfiles - 1;
	return( k );

lab9://snag-
	printf ( "\nOOPS parset : contrl %d\n", contrl );
	bell ( 1, 1 );
	ok = 89;

	//lab11:
	return( k );
} /* parset */
/***************************************/

void inperf(void)
/*
     this decodes the input text defining the required actions.

  global  variables
     main     -true if in main program.
     nmax     -max number of commands possible.
     ptype    -type of action being read.

     called by compl,
     calls     nexts, match, addnam, inname, inells, injts,
               value, parset, nlims,

	30 Jul 2006 d072 put infinite loop if error
*/
{
	int nells;
	int how;     // type number of current action keyname.
	int j;
	int k;
	int linel;   // length of string 'line'
	int nmax;	  // max number of commands possible
	int s;	     // counter thru subs and along a string
	int thisub; // number of current subroutine
	double v;

	p = 0;
	thisub = 0;
	subact[0][0] = 0;
	nmax = 4 * EMAX + PMAX;

	// run through statements

	for ( comand = 1; ( ( ok == 0 ) && ( comand <= nmax ) ); ++comand )
	{
		start = -1;
		nexts ();
		linel = (int)strlen ( line );
		for ( s = 0; s < linel; ++s )
			aline[comand][s] = line[s];
		how = match ( NKEYS, keylen, keynam );
		ptype = how;
		if ( ( how <= 0 ) || ( how >= NKEYS ) )
		{
			printf ( "\nOOPS inperf: how %d outside range 0 to %d\n", how, NKEYS );
			bell ( 1, 1 );
			ok = 88;
		}
		else if ( how == stop_keyword_code )
		{
			subact[thisub][1] = p - 1;
			break;
		}
		else if ( how == figure_keyword_code  )
		{
			nexts ();
			nfigs = addnam ( nfigs, fname, FALSE, figlen );
			nells = ne;
			figell[nfigs-1] = ne;
			ne = inname ( nells, 0, ellen, ename );
		}
		else if ( how == ellips_keyword_code  )
		{
			j = inells ();
			ax[j][0] = semiax[0];
			ax[j][1] = semiax[1];
			ax[j][2] = semiax[2];
		}
		else if ( how == joint_keyword_code )
		{
			injts ();
		}
		else if ( how  == limits_keyword_code )
		{
			inlims ();
		}
		else if ( how == variable_keyword_code )
		{
			nvars = inname ( nvars, 1, varlen, vname );
			if ( ( nvars + nvals ) > EMAX )
			{
				printf ( "\nOOPS inperf nvars %d + nvals %d > EMAX %d\n", nvars, nvals, EMAX );
				bell ( 1, 1 );
				ok = 87;
			}
		}
		else if ( how == speed_keyword_code )
		{
			nexts ();
			v = value ();
			if ( v < doub0 ) slow = int ( -v + inv2 );
			if ( v > doub0 ) fast = int ( v + inv2 );
		}
		else if ( how == view_keyword_code )
		{
			nexts ();
			v = value ();
			if ( pok == TRUE )
			{
				vstart = int ( v ) - 1;
				if ( vstart < 0 ) vstart = 0;
				nexts ();
				v = value ();
				if ( pok == TRUE ) vstop = int ( v );
			}
			if ( pok == FALSE )
			{
				printf ( "\nOOPS inperf: view %f\n", v );
				bell ( 1, 1 );
				ok = 70;
			}
		}
		else if ( how == subrou_keyword_code  ) // start a subroutine
		{
			inmain = FALSE;
			if ( thisub == 0 ) subact[0][1] = p - 1;
			nexts ();
			thisub = match ( nsubs, sublen, sname );
			if ( thisub <= 0 )
			{
				nsubs = addnam ( nsubs, sname, 0, sublen );
				if ( ok == 0 ) thisub = nsubs - 1;
			}
			defined[thisub] = TRUE;
			subact[thisub][0] = p;
		}
		else if ( how == endsub_keyword_code )  //  end of a subroutine
		{
			nexts ();
			k = match ( nsubs, sublen, sname );
			if ( k == thisub )
			{
				subact[k][1] = p - 1;
			}
			else
			{
				printf ( "\nOOPS inperf: k %d != thisub %d\n", k, thisub );
				bell ( 1, 1 );
				ok = 86;
			}
		}
		else if ( p >= PMAX )//  read an action -
		{
			p = PMAX - 1;
			printf ( "beware- more than %d action specs\n", PMAX );
			printf ( "actions deleted after line  %d\n%s\n", nline, line );
		}
		else
		{
			distrn[p] = how;
			cline[p] = comand;

			// read frames to which this action refers -

			frstart[p] = parset(1);
			if ( ok == TRUE ) frstop[p] = parset ( 1 );
			if ( inmain == TRUE )
			{
				if ( frstart[p] < fstart )
					fstart = frstart[p];
				if ( frstop[p] > fstop )
					fstop = frstop[p];
			}
			if ( ok == TRUE ) //call of a subroutine
			{
				if ( how == call_keyword_code )
				{
					distrn[p] = call_keyword_code;
					ptype = call_keyword_code;
					type[p] = call_keyword_code;
					nexts ();
					k = match ( nvars, varlen, vname );
					if ( k < 0 )
					{
						k = match ( nsubs, sublen, sname );
						if ( k < 0 )
						{
							nsubs = addnam ( nsubs, sname, 0, sublen );
							k = nsubs - 1;
						}
						called[k] = TRUE;
						pf[p][0] = k;
					}
					else
					{
						pf[p][0] = k - EMAX + 1;
					}
				}
				else // read action done in these frames
				{
					nexts ();
					ptype = match ( NKEYS, keylen, keynam );
					type[p] = ptype;
					if ( ( ptype < 1 ) || ( ptype >= NKEYS ) )
					{
						printf ( "\nOOPS inperf: ptype %d\n", ptype );
						bell ( 1, 1 );
						ok = 85;
					}
					else // run through parameters of pth action
					{
						for ( j = 0; ( ( ok <= 0 ) && ( j < 6 ) ); ++j )
						{
							pf[p][j] = parset ( par[ptype][j] );
							if ( ok > 0 )
							{
								printf( "\nOOPS in inperf: problem parameter %d %d %d %d %d\n", j, p, pf[p][j], ptype, par[ptype][j] );
								bell ( 1, 1 );
							}
						}
					}
				}
			}
		}
		if ( ok > 0 )
		{
			printf ( 	"\nOOPS in inperf: problem near line %d\n %s\n\n",	nline, line );
			bell ( 1, 1 );
dead: goto dead;
		}
		if ( distrn[p] > 0 ) ++p;
		npfs = p;
	}
} /* inperf */
/***************************************/

void compl1(void)
/*
   calls    inperf, getout, dojoin, checkin,
   called by main,
*/
{
   nline = 0;
   inperf();
   if (ok > 0) getout(1);
   if (ok == 1) goto rtrn;
   dojoin();
   if (ok > 0) getout(1);
   if (ok == 1) goto rtrn;
   checkin();
   if (ok > 1) getout(1);
rtrn: ;
} /* compl */
/***************************************/
/*
          actions39.h

      setels      - finds ellipsoids and joints connected to given ellipsoid
      save        - store positions and orientations
      restore     - restore positions and orientations
      store3      - writes data about given frame to arrays
      getvalu     - gets a value from constants or variables
      vecmat      - multiplies a vector by a matrix
      doground    - moves a set of ellipsoids to rest on y = 0
      setjnt      - finds ellipsoids and joints connected to a given joint
      setfrc      - sets proportion of action for current frame
      doscale     - scale a value by some proportion
      findfg      - finds which figure includes a given ellipsoid
      checkpr     - checks parameters for legality
      setper      - decodes the parameters of the current action
      sqr         - square a value
      docolour    - sets colours of an ellipsoid
      doplace     - sets viewing point (array 'pplace')
      setobs      - sets 3*3 matrix for viewing rotation and place
      enquir      - stores values of centres, joints or axis lengths
      doattach    - joins 2 figures into 1
      dodetach    - breaks 1 figure into 2
      domoveby    - moves a set of ellipsoids relative to refell
      dogroell    - scales axes of an ellipsoid
      dogrofig    - scales a set of ellipsoids in size
      dogrojnt    - scales set of ellipsoids keeping a joint fixed
      domovjnt    - moves a joint
      balanc      - balances part of a figure
      dodrag      - keeps an ellipsoid touching ground
      dcen        - find separation of ellipsoid centres
      newton      - solve a polynomial
      getmat      - generate matrix of an ellipsoid
      getaxes     - find axis lengths of an ellipsoid
      surf        - find separation of ellipsoid surfaces
      sepn        - find distance between 2 ellipsoid surfaces
      fun         - used by 'solve' for abut
      solve       - find zero of 'fun'
      angsepn     - find approx angular separation of ell1 and ell2 from x
      dotouch     - bends a figure to make 2 ellipsoids touch
      trying      - 'domoveby' then 'sepn'
      fndmin      - find minimum of function 'trying'.
      doabut      - slide figure to touch another


***************************************/

void setels(int ellpsd, int jthis)
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
                store3, fun,
*/
{
      int change;
      int ell;
      int e,ee,j,jj ;


      if (ellpsd >= ne)
      {
          ok = 79;
          printf("\nOOPS setels: ellpsd %d %s >= ne %d\n",
			  ellpsd,ename[ellpsd],ne);
          goto rtrn;
      }
      if (ellpsd <= 0) goto lab6;
      ecount = 1;
      elist[0] = ellpsd;
      if (njts <= 0) goto rtrn;
      jcount = 0;
      if (jthis < 0) goto again;
      if (jthis >= njts)
      {
          ok = 78;
          printf("\nOOPS setels: jthis %d  %s > njts %d\n",
			  jthis,jname[jthis],njts);
          goto rtrn;
      }
      if ((coel[jthis][0] != ellpsd) && (coel[jthis][1] != ellpsd))
      {
          ok = 50;
          printf("\nOOPS setels: joint %d %s connected to %d %s and %d %s, not %d %s\n",
              jthis,jname[jthis],
			  coel[jthis][0],ename[coel[jthis][0]],
			  coel[jthis][1],ename[coel[jthis][1]],ellpsd,ename[ellpsd]);
          goto rtrn;
      }
      jcount = 1;
      jlist[0] = jthis;

again: change = FALSE;
      for ( e=0; e < ecount; ++e )
      {
/*   seek joint not in jlist connected to ellipsoid elist[e]- */

         for ( j=0; j < njts; ++j )
         {
            if ((j == jthis) && (jthis > 0)) goto lab3;
            for (  jj=0; jj < jcount; ++jj )
               if (j == jlist[jj]) goto lab3;
/*
    j not in list yet-
*/
            ell = -1;
            if (coel[j][0] == elist[e]) ell = coel[j][1];
            if (coel[j][1] == elist[e]) ell = coel[j][0];
            if (ell < 0) goto lab3;

/*   store new joint and ellipsoid- */

            jlist[jcount] = j;
            ++jcount;
            change = TRUE;
            for (  ee=0; ee < ecount; ++ee )
               if (ell == elist[ee]) goto lab3;
            elist[ecount] = ell;
            ++ecount;
            change = TRUE;

lab3: ;
         } /* j */
     } /* e */
     if (change == TRUE) goto again;
	 goto rtrn;

/*   set all ellipsoids and joints- */

lab6: jcount = 0 ;

/*   all joints with non-null connections- */

      jcount = 0;
      for (  j = 0 ; j <= njts ; ++ j )
      {
         if (coel[j][0] >= 0)
         {
            ++jcount;
            jlist[jcount-1] = j ;
         }
      }

/*   all ellipsoids except world- */

      ecount = ne ;
      for (  e = 1 ; e <= ne ; ++ e )
         elist[e-1] = e ;
rtrn: ;
}  /* setels */
/*************************************************/

/*****************************************************/
/*
         shado41.h

     based on shadoq.c

     to add shadows to figures

     26 Apr  2005  adapt to include in drawel
     16 Jan  2003  remove the shadows below ground
     15 Aug  2001  move the shadows below ground
     18 Aug  1993  to accommodate joints
     23 Oct  1992  D.Herbison-Evans  written

***************************************************

   subroutines-
        setcof
        setaxe
        setpro
        setmat
        setnup
        ground
        doshadow

***********************************************/

void setcof(double coef[7], double el[3][3] )
/*
     set up coeffs of outline ellipse of an ellipsoid about
     its own centre in the form -

     coef(1)*x**2 + coef[2]*z**2 + coef[3]*x*z
         + coef(4)*x + coef[5]*z + coef[6] = 0

     called by setnup,
*/
{
   double den ;

   if (el[1][1] == doub0) goto lab1 ;
   den = doub1/el[1][1] ;
   coef[1] = el[0][0] - el[0][1]*el[0][1]*den ;
   coef[2] = el[2][2] - el[1][2]*el[1][2]*den ;
   coef[3] = doub2*(el[0][2] - el[0][1]*el[1][2]*den) ;
   coef[4] = doub0 ;
   coef[5] = doub0 ;
   coef[6] =  -doub1 ;
   goto rtrn ;
/*
     snags -
*/
lab1:
   printf("setcof %f %f %f\n",
              el[1][0],el[1][1],el[1][2]);
   ok = 99 ;
rtrn:;
} /* setcof */
/************************************************/

void setaxe(int n, double axe[3], double coef[7])
/*
     find semiminor axis, axe[0], and semimajor
     axis, axe[2], of ellipse described by coef.

     called by setnup,
*/
{
   double discrt,lamx,lamz,c12,rtdis ;

   lamx = doub1 ;
   lamz = doub1 ;
   discrt = (coef[1] - coef[2])*(coef[1] - coef[2])+ coef[3]*coef[3];
   if (discrt < doub0) goto lab1 ;
   c12 = inv2*(coef[1]+coef[2]) ;
   rtdis = inv2*sqrt(discrt) ;
   lamx = c12 + rtdis ;
   lamz = c12 - rtdis ;
   if (lamx <= doub0) goto lab1 ;
   if (lamz <= doub0) goto lab1 ;
   axe[0] = doub1/sqrt(lamx) ;
   axe[2] = doub1/sqrt(lamz) ;
   goto rtrn ;
/*
     snags -
*/
lab1: printf("setaxe snag %f %f %f\n",
         lamx,lamz,discrt);
   ok = 98 ;
rtrn:;
} /* setaxe */
/******************************************/

double setpro(double coef[7])
/*
     for the outline of nth ellipsoid, find 'phi'
     angle between axx axis and scene x axis.

     called by setnup,
*/
{
   double phi ;

   phi = pi-inv2*atan2(coef[3], coef[1]-coef[2]) ;
   if (phi < doub0) phi = phi+twopi ;
   return(phi);
} /* setpro */
/******************************************/

void setmat ( int n, double el[3][3], double el1[3][3], double unel1[3][3] )
/*

	finds the matrix "el" of the quadratic form of the "n"th
	ellipsoid by taking the diagonal matrix of inverse square
	semiaxes, and doing on it a similarity transform
	for its own rotation.

	called by setnup, cutting,
	calls matmul, rotget,

	12 Aug 2006  returning el1 and unel1
*/
{
	int ii, j;
	double el0[3][3],el2[3][3],el3[3][3];
	double r[3][3], unr[3][3];

	// initialise diagonal matrix -

	for ( ii = 0; ii < 3; ++ ii )
	{
		for ( j = 0; j < 3; ++ j )
		{
			el0[ii][j] = doub0;
			el3[ii][j] = doub0;
		}
		if ( ax[n][ii] ==  doub0 )
		{
			printf ( "setmat  ax[%d][%d] = 0\n", n, ii );
			ok = 97;
			return;
		}
		el0[ii][ii] = doub1 / ax[n][ii];
		el3[ii][ii] = ax[n][ii];
	}
	rotget ( r, unr, n );

	// do similarity transform -

	matmul ( el0, unr, el1 );
	matmul ( r, el0, el2 );
	matmul ( el2, el1, el);
	matmul ( r, el3, unel1);
} /* setmat */
/**********************************************/

double setnup(int n, double axe[3])
/*
     set up parameters of nth ellipsoid relative
     to own centre.

     called by shadow,
     calls     setmat, setcof, setaxe, setpro,
*/
{
   double el[3][3],el0[3][3],el1[3][3];
	double con[7];
   double phi;

   phi = doub0;
   setmat(n,el,el0,el1) ;
   if ( ok > 0 ) goto lab1 ;
   setcof(con,el) ;
   if ( ok > 0 ) goto lab1 ;
   setaxe(n,axe,con) ;
   if ( ok > 0 ) goto lab1 ;
   phi = setpro(con) ;
   if ( ok > 0 ) goto lab1 ;
   goto rtrn ;
/*
     snag -
*/
lab1: ok = 96;
   printf(
      "setnup snag in ellipsoid %d\n",n );

rtrn:
   return(phi);
} /* setnup */
/******************************************/

double elground(int i)
/*
   find distance of lowest point above the ground
   of the ellipsoid 'i'.

   called by  shadow,
   calls      rotget,
*/
{
   double x,y,z,r[3][3],unr[3][3] ;
   double val;
   double sumsq;
   double sqt;

   val = cen[i][1];

/*   find lowest point- */

   rotget(r,unr,i) ;
   x = unr[0][1]*ax[i][0] ;
   y = unr[1][1]*ax[i][1] ;
   z = unr[2][1]*ax[i][2] ;
   sumsq = x*x+y*y+z*z;
   if (sumsq > doub0)
      sqt = sqrt(sumsq); else sqt = doub0;
   val = cen[i][1] - sqt ;
   return(val);
}  /* elground */
/**********************************************************/

void doshadow()
/*
  find the shadow ellipsoids of each ellsoid in the scene

     called by store3,
     calls     setnup, rset, rotput, ground,
*/
{
   int k,n;
   double y, phi;
   double r[3][3];
   double axe[3];
/*
     run thru ellipsoids to shadow each in turn -
*/
    k = ne;
    for (  n = 1 ; n < ne ; ++n )
    {
         phi = setnup(n,axe);
         y = elground(n);
         if (y > doub0)
         {
            cen[k][0] = cen[n][0];
            cen[k][1] = -inv5;
            cen[k][2] = cen[n][2];
            ax[k][0] = axe[0];
            ax[k][1] = inv5;
            ax[k][2] = axe[2];
            rset(r,phi,1);
            rotput(r,k);
            col[k][0] = doub1;
            col[k][1] = doub1;
            col[k][2] = doub1;
			++k;
         } /* y > 0 */
    } /* end n loop */
    ne = k;
} /* doshadow */
/******************************************/

void save(void)
/*
   save positions and orientations

   called by  store3, doabut, dodrag, dotouch,
*/
{
   int j,n;

   nesave = ne;
   for (n = 0; n <= ne; ++n)
   {
      for ( j = 0; j < 3; ++j)
      {
         censav[n][j] = cen[n][j];
         jntsav[n][j] = jnt[n][j];
      }
      for ( j = 0; j < 5; ++j)
         quasav[n][j] = quat[n][j];
   }
} /* save */
/***********************************************/

void restore(void)
/*
   restore positions and orientations

   called by  store3, doabut, try, dodrag, fun, dotouch,
*/
{
   int j,n;

   ne = nesave;
   for (n = 0; n <= ne; ++n)
   {
      for (j = 0; j < 3; ++j)
      {
         cen[n][j] = censav[n][j];
         jnt[n][j] = jntsav[n][j];
      }
      for ( j = 0; j < 5; ++j)
         quat[n][j] = quasav[n][j];
   }
} /* restore */
/***********************************************/

void store3(int f)
/*
    store axes, centres, orientations and colours
    of  nels ellipsoids starting at 1 (avoiding  0 = world),

    called by doframes,
    calls     save, doshadow, setels, shift, twirl, rotput,
	          mkang, storeang, mkquat, rotgrt, restore,
*/
{
   int   e,j;
   double invobs[3][3];

   save();
   if (shadow == TRUE) doshadow();
   setels(0,-1);
   twirl(pplace[0],pplace[1],pplace[2],obs);
   shift(-pplace[0],-pplace[1],-pplace[2]);
   nels[f] = ne;
   for (e = 0; e < ne; ++e)
   {
      for (j = 0; j < 3; ++j)
      {
         qu3[f][e][j+1] = quat[e][j];
         ax3[f][e][j] = ax[e][j]*inv1000;
         ce3[f][e][j] = cen[e][j]*inv1000;
         co3[f][e][j] = col[e][j]*inv256;
      } /* j*/
      qu3[f][e][3] = -qu3[f][e][3];
      qu3[f][e][0] = degree*atan2(quat[e][3], quat[e][4]);
      ce3[f][e][2] = doub1 - ce3[f][e][2];
      if (col[e][0] < 0)
            sprintf(tn3[f][e],"%s",tname[int(inv2-col[e][0])]);
   } /* e */
   rotput(obs,ne);
   mkang(ne);
   storeang(f,ne,ang[0],ang[1],ang[2]);
   mkquat(ne,ang[0],ang[1],ang[2]);
   rotget(obs,invobs,ne);
   restore();
}  /* store3 */
/***********************************************/

int getvalu(int p)
/*
  get value possibly from array val and put it into v and k.
  if p is negative, get value of variable val(abs(p)),
  if p is positive get p directly.

  called by  doperfrm, setper,
*/
{
   int k;
   int ref ;

   ref = 0 ;
/*
  is the parameter a variable or direct reference
*/
   if (p < 0)
   {
/*
  parameter is index into array val-
*/
      ref = -p ;
      if ((ref < 0) || (ref >= EMAX))
      {
         ok = 15 ;
         printf("val index %d outside range 0 - %d\n",
		     ref,EMAX);
      }
      else
      {
         v = val[ref] ;
         k = int(v + inv2) ;
         if (v < doub0) k = int(v -inv2) ;
      }
   }
   else
/*
  parameter is direct reference, use it-
*/
   {
      k = p ;
      v = k ;
   }
   return(k);
}  /* getvalu */
/**************************************/

void vecmat(double v[3], double m[3][3], double w[3])
/*
   multiply vector 'v' by matrix 'm',
   putting result in 'w'.

   called by  sepn, dobalanc,
*/
{
      int i,j;
      double vv[3],x;

      for (  i = 0 ; i < 3 ; ++ i )
      {
         x = doub0 ;
         for (  j = 0 ; j < 3 ; ++ j )
         {
            x = x+m[i][j]*v[j];
         }
         vv[i] = x ;
      }
      for (  i = 0 ; i < 3 ; ++ i )
      {
         w[i] = vv[i];
      }
}  /* vecmat */
/**********************************************************/

double elow(int i)
/*
   find height of lowest point of ellipsoid i

   called by doground,
   call rotget,
  */
{
   double r[3][3],unr[3][3];
   double x,y,z;
   double sq,sqt;
   double toty;

   rotget(r,unr,i);
   x = unr[0][1]*ax[i][0];
   y = unr[1][1]*ax[i][1];
   z = unr[2][1]*ax[i][2];
   sq = x*x+y*y+z*z;
   if (sq > doub0)
      sqt = sqrt(sq);
   else
      sqt = doub0;
   toty = cen[i][1] - sqt;
   return(toty);
} /* elow */
/******************************************************/

double doground(void)
/*
   find distance of lowest point above the ground
   of the ellipsoids contained in 'elist'.

   called by  action, dodrag, fun, doshadow,
   calls      rotget,
*/
{
   int n ;
   double toty;
   double val;

   if ((ecount < 1) || (ecount > ne))
   {
      ok = 38 ;
      printf("\nOOPS doground: ecount %d out of range\n",
            ecount);
   }
   else
   {
      val = cen[elist[0]][1];
/*  run through affected ellipsoids finding lowest point- */
      for (  n = 0 ; n < ecount ; ++ n )
      {
         toty = elow(elist[n]);
         if (toty < val) val = toty;
      } /* n */
   } /* if ecount */
   return(val);
}  /* doground */
/**********************************************************/

void setjnt(int ellpsd, int jthis)
/*
     puts into 'elist' and 'jlist' those ellipsoids and joints
     (if any) connected to 'ellpsd'
     (including 'ellpsd' and excluding 'jthis')
     except those connected through joint 'jthis'

     'ecount' is the number of ellipsoids in the list elist.
     'jcount' is the number of joints in the list jlist.

     called by  domovjnt,
*/
{
      int done;
      int e,j,i,jt ;

      ecount = 1 ;
      elist[0] = ellpsd ;
      jcount = 0 ;
      if ((coel[jthis][0] != ellpsd) && (coel[jthis][1] != ellpsd))
      {
          ok = 64;
          printf("\nOOPS setjnts: coel %d  %d out of range %d %d\n",
              coel[jthis][0],coel[jthis][1],ellpsd,jthis);
          goto rtrn;
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
}  /* setjnt */
/*************************************************/

void setfrc(int frame, int start, int stp)
/*
  set up prop and frac -  proportion of current action time
  to be done for current frame.

  variables -
     a - number of frames done of current action
     aa - number of increments of current action done
     b - number of frames to be done
     bb - number of increments of current action to be done
     even  - 0 if n is even, 1 if n is odd
     nn - total number of increments in current action

  called by  prfrm,
*/
{
   double a,aa,b,bb,h,n,nn,even;
   int distrp ;

   distrp = distrn[pp];
   n = stp-start ;
   nn = n*(n+doub1)*inv2 ;
   a = frame-start ;
   aa = a*(a+doub1)*inv2 ;
   b = stp-frame+1 ;
   bb = b*(b+doub1)*inv2 ;
   even = ((int)n)%2 ;
   h = ((int)n)/2 ;
/*
  repeat command-
*/
   if (distrp == repeat_keyword_code)
   {
      prop = doub1 ;
      frac = doub1 ;
   }
   else
/*
  linear command-
*/
   if (distrp == linear_keyword_code)
   {
      if ((b  == doub0) || (n == doub0))
      {
         ok = 10 ;
         printf("\nOOPS setfrc: linear b %d,  n %d, start %d\n",
              b,n,start);
      }
      else
      {
         frac = doub1/n;
         prop = doub1/b;
      }
   }
   else
/*
  acceleration command-
*/
   if (distrp == accele_keyword_code)
   {
      if ((nn == doub0) || ((nn-aa+a) == doub0))
      {
         ok = 11 ;
         printf("\nOOPS setfrc: accel bb %d,  nn %d, start %d\n",
              bb,nn,start);
      }
      else
      {
         frac = a/nn ;
         prop = a/(nn-aa+a) ;
      }
   }
   else
/*
  deceleration command-
*/
   if (distrp == decele_keyword_code)
   {
      if ((nn == doub0) || (bb == doub0))
      {
         ok = 12 ;
         printf("\nOOPS setfrc: decele bb %d,  nn %d, start %d\n",
              bb,nn,start);
      }
      else
      {
         frac = b/nn ;
         prop = b/bb ;
      }
   }
   else
/*
  quadratic command-
*/
   if (distrp == quadra_keyword_code)
   {
      nn = (n*(n+doub2)+even)/doub4 ;
      if (nn == doub0)
      {
         ok = 13 ;
         printf("\nOOPS setfrc: quadra nn %d, start %d\n",
              nn,start);
      }
      else
      {
         frac = a/nn;
         if (a >= b) frac = b/nn ;
      }
      if (bb == doub0)
      {
         ok = 13 ;
         printf("\nOOPS setfrc: quadra bb %d, start %d\n",
              bb,start);
      }
      prop = b/bb ;
      if (a < b)
      {
         if ((nn-aa+a) == doub0)
         {
            ok = 13 ;
         printf("\nOOPS setfrc: quadra nn-aa+a %d, start %d\n",
              nn-aa+a,start);
         }
         prop = a/(nn-aa+a) ;
      }
   }
   else
/*
   cubic command-
*/
   if (distrp == cubic_keyword_code)
   {
      nn = h*(h+doub1)*(doub2*h+doub1)*inv3 + even*(h+doub1)*(h+doub1);
      aa = a*(a+doub1)*(doub2*a+doub1)*inv6;
      bb = b*(b+doub1)*(doub2*b+doub1)*inv6;
      if ( a < b )
      {
         if (nn > doub0) frac = a*a/nn; else frac = doub1;
         if ((nn-aa+a*a) > doub0) prop = a*a/(nn-aa+a*a); else prop = doub1;
      }
      else
      {
         if (nn > doub0) frac = b*b/nn; else frac = doub1;
         if (bb > doub0) prop = b*b/bb; else prop = doub1;
      }
   }
} /* setfrc */
/************************************************************/

double doscale(double x)
/*
   scale x by proportion frac

   called by setper,
*/
{
   double v1,v2,v3,v4,v5;

   if (x == doub0)
   {
      ok = 51;
      printf("\nOOPS scale: scale factor 0\n");
      v5 = doub0;
   }
   else
   {
      if (x > doub0) v1= x; else v1 = -x;
      if ( v1 > doub0) v2 = log(v1); else v2 = doub0;
      v3 = frac*v2;
      v4 = exp(v3);
      if (x > doub0) v5 = v4; else v5 = -v4;
   }
   return(v5);
}  /* doscale */
/***************************************/

int findfg(int ell)
/*
  find the figure (excluding 'every')
  that includes the ellipsoid 'ell'.

  called by setper, doattach, dodetach,
  calls     setels,
*/
{
   int e,f;

   setels(ell,-1) ;
   for (  f = 1 ; f <= nfigs ; ++ f )
   {
      for (  e = 0 ; e < ecount ; ++ e )
         if (figell[f] == elist[e]) return(f);
   }
/*
  snag-
*/
   ok = 35 ;
   printf("\nOOPS findfg: ecount %d, ell %d %s\n",
	   ecount,ell,ename[ell]);
   return(-1);
}  /* findfg */
/************************************************/

void checkpr(void)
/*
  check parameters for legality

  called by  setper,
*/
{
   if ((njts > 0)&&((join < 0) || (join > njts))) goto lab12 ;
   if ((axis < 0) || (axis > 2)) goto lab13 ;
   if ((ellpsd < 0) || (ellpsd > ne)) goto lab14 ;
   if ((refell < 0) || (refell > ne)) goto lab15 ;
   if ((ell1 < 0) || (ell1 > ne)) goto lab20 ;
   if ((ell2 < 0) || (ell2 > ne)) goto lab21 ;
   if ((fig < 0) || (fig > nfigs)) goto lab16 ;
   if (nvars <= 0) goto lab10 ;
   if ((var0 < 0) || (var0 >= EMAX)) goto lab17 ;
   if ((var1 < 0) || (var1 >= EMAX)) goto lab18 ;
   if ((var2 < 0) || (var2 >= EMAX)) goto lab19 ;
   if (newcol[0] < -nfiles) goto lab45 ;
   if (newcol[0] <= 0)
   {
      if (newcol[1] < 0) goto lab48 ;
      if (newcol[2] < 0) goto lab49 ;
   }
   goto lab10 ;
/*
  data snag-
*/
lab12: ok = 16 ;
   printf("\nOOPS checkpr: joint %d out of range 0 to  %d\n",
      join,njts);
   goto lab10 ;

lab13: ok = 17 ;
   printf("\nOOPS checkpr: axis %d out of range 0 to 2\n",
      axis);
   goto lab10 ;

lab14: ok = 18 ;
   printf("\nOOPS checkpr: ellpsd %d out of range 0 to %d\n",
      ellpsd,ne);
   goto lab10 ;

lab15: ok = 19 ;
   printf("\nOOPS checkpr: refell %d out of range 0 to %d\n",
      refell,ne);
   goto lab10 ;

lab16: ok = 20 ;
   printf("\nOOPS checkpr: fig %d out of range 0 to %d\n",
      fig,nfigs);
   goto lab10 ;

lab17: ok = 21 ;
   printf("\nOOPS checkpr: var0 %d out of range 0 to %d\n",
      var0,nvars);
   goto lab10 ;

lab18: ok = 22 ;
   printf("\nOOPS checkpr: var1 %d out of range 0 to %d\n",
      var1,nvars);
   goto lab10 ;

lab19: ok = 23 ;
   printf("\nOOPS checkpr: var2 %d out of range 0 to %d\n",
      var2,nvars);
   goto lab10 ;

lab20: ok = 36 ;
   printf("\nOOPS checkpr: ell1 %d out of range 0 to %d\n",
      ell1,ne);
   goto lab10 ;

lab21: ok = 37 ;
   printf("\nOOPS checkpr: ell2 %d out of range 0 to %d\n",
      ell2,ne);
   goto lab10 ;

lab45: ok = 45 ;
   printf("\nOOPS checkpr: newcol[0] %d out of range\n",
      newcol[0]);
   goto lab10 ;

lab48: ok = 48 ;
   printf("\nOOPS checkpr: newcol[1] %d out of range\n",
      newcol[1]);
   goto lab10 ;

lab49: ok = 49 ;
   printf("\nOOPS checkpr: newcol[2] %d out of range\n",
      newcol[2]);

lab10:
   ;

}  /* checkpr */
/***************************************/

void setper ( int keyword_code )
/*
  decodes the parameters of the 'pp'th action using -

     0 - none
     1 - x
     2 - y
     3 - z
     4 - ang1
     5 - ang2
     6 - ang3
     7 - x scaling factor
     8 - y scaling factor
     9 - z scaling factor
    10 - value for a variable
    11,12,13 - red, green and blue colour coords
    14 - the debug parameter
    15 - reference to a file name in list 'fname'
    21 - axis
    22 - joint
    23 - reference ellipsoid
    24 - ellpsd (moving or central ellipsoid)
    25 - fig  (figure)
    27,28,29 - var0,var1,var2 (references to variables)
    30 - ell1 (ellipsoid to touch)
    31 - ell2 (ellipsoid to be touched)

  called by doperfrm,
  calls     getvalu, checkpr, findfg, setels,
*/
{
	int c;
	int j;

	if ( ( keyword_code < 1 ) || ( keyword_code > NKEYS ) )
	{
		ok = 14;
		printf ( "\nOOPS setper: keyword_code %d\n", keyword_code );
		bell ( 1, 1 );
		return;
	}

	for (  j = 0; j < 6; ++ j )//run thru parameters of 'p'th action
	{
		c = code[keyword_code][j];
		if ( c != 0 )
		{
			k = getvalu ( pf[pp][j] );
			if ( ok != 0 ) return;

			//			set real parameters -

			if ( c ==  1 ) xx[0] = v;
			if ( c ==  2 ) xx[1] = v;
			if ( c ==  3 ) xx[2] = v;
			if ( c ==  4 ) ang[0] = v * radian;
			if ( c ==  5 ) ang[1] = v * radian;
			if ( c ==  6 ) ang[2] = v * radian;
			if ( keyword_code != growto_keyword_code )
			{
				if ( c ==  7 ) factor[0] = doscale ( v );
				if ( c ==  8 ) factor[1] = doscale ( v );
				if ( c ==  9 ) factor[2] = doscale ( v );
			}
			if ( keyword_code == growto_keyword_code )
			{
				if ( c ==  7 ) factor[0] = v;
				if ( c ==  8 ) factor[1] = v;
				if ( c ==  9 ) factor[2] = v;
			}
			if ( c == 10 ) varval = v;

			//			set int parameters-

			if ( c == 11 ) newcol[0] = k;
			if ( c == 12 ) newcol[1] = k;
			if ( c == 13 ) newcol[2] = k;
			if ( c == 21 ) axis = k;
			if ( c == 22 ) join = k;
			if ( c == 23 ) refell = k;
			if ( c == 24 ) ellpsd = k;
			if ( c == 25 ) fig = k;
			if ( c == 27 ) var0 = EMAX - k - 1;
			if ( c == 28 ) var1 = EMAX - k - 1;
			if ( c == 29 ) var2 = EMAX - k - 1;
			if ( c == 30 )
			{
				ell1 = k;
				ellpsd = k;
			}
			if ( c == 31 ) ell2 = k;
		} /* c != 0 */
	}	/* j */

	//	check for errors-

	checkpr ( );
	if ( ok != 0 ) return;

	/*
	if appropriate, set up lists of ellipsoids and joints
	in affected figures ( NB figell[every] is -1)  -
	*/
	if ( keyword_code == drag_keyword_code )
	{
		if ( ellpsd == coel[join][0] )
			refell = coel[join][1];
		else
			refell = coel[join][0];
	}

	if ( code[keyword_code][0] == linear_keyword_code )
	{
		setels ( figell[fig], -1 );
		if ( ok != 0 ) return;
	}

	if ( ( keyword_code == rotate_keyword_code )
		|| ( keyword_code == abduct_keyword_code )
		|| ( keyword_code == drag_keyword_code )
		|| ( keyword_code == abut_keyword_code ) )
	{
		fig = findfg ( ellpsd );
		if ( ok != 0 ) return;
	}

	if ( keyword_code == abut_keyword_code )
	{
		setels ( ellpsd, -1 );
		if ( ok != 0 ) return;
	}
	else if ( ( keyword_code == balanc_keyword_code )
		|| ( keyword_code == touch_keyword_code )
		|| ( keyword_code == bendby_keyword_code )
		|| ( keyword_code == bendto_keyword_code )
		|| ( keyword_code == flex_keyword_code )
		|| ( keyword_code == rotate_keyword_code )
		|| ( keyword_code == abduct_keyword_code )
		|| ( keyword_code == drag_keyword_code )
		|| ( keyword_code == linkx_keyword_code ) )
	{
		if ( keyword_code != linkx_keyword_code ) setels ( ellpsd, join );
		if ( ok != 0 ) return;
		xx[0] = jnt[join][0];
		xx[1] = jnt[join][1];
		xx[2] = jnt[join][2];
	}

	if ( ( keyword_code == grofig_keyword_code )
		|| ( keyword_code == spinto_keyword_code )
		|| ( keyword_code == spinby_keyword_code )
		|| ( keyword_code == center_keyword_code )
		|| ( keyword_code == centre_keyword_code ) )
	{
		xx[0] = cen[ellpsd][0];
		xx[1] = cen[ellpsd][1];
		xx[2] = cen[ellpsd][2];
	}
	else if ( keyword_code == moveto_keyword_code )
	{
		xx[0] = xx[0] - cen[ellpsd][0];
		xx[1] = xx[1] - cen[ellpsd][1];
		xx[2] = xx[2] - cen[ellpsd][2];
	}

	if ( ( keyword_code == growto_keyword_code ) )
	{
		xx[0] = cen[ellpsd][0];
		xx[1] = cen[ellpsd][1];
		xx[2] = cen[ellpsd][2];
		return;
	}

	if ( ( keyword_code == opacty_keyword_code ) )
	{
		xx[0] = cen[ellpsd][0];
		xx[1] = cen[ellpsd][1];
		xx[2] = cen[ellpsd][2];
		return;
	}
	if ( ( keyword_code == lghtng_keyword_code ) )
	{
		xx[0] = cen[ellpsd][0];
		xx[1] = cen[ellpsd][1];
		xx[2] = cen[ellpsd][2];
		return;
	}
   for (j = 0; j < ne; ++j)
	{
		minax[j] = ax[j][0];
		if (ax[j][1] < minax[j]) minax[j] = ax[j][1];
		if (ax[j][2] < minax[j]) minax[j] = ax[j][2];
		maxax[j] = ax[j][0];
		if (ax[j][1] > maxax[j]) maxax[j] = ax[j][1];
		if (ax[j][2] > maxax[j]) maxax[j] = ax[j][2];
	}
}  /* setper */
/****************************************************/

double sqr(double x)
/*

  called by   surf, angsepn, dotouch,

  16 Sep 2006 called by totouch
*/
{
   return(x*x);
}  /* sqr */
/*******************************************************/

void docolour(double prop)
/*
  sets ellipsoid colour proportionately to the appropriate rgb.

  called by  action,
*/
{
   col[ellpsd][0] += prop*(newcol[0]-col[ellpsd][0]) ;
   col[ellpsd][1] += prop*(newcol[1]-col[ellpsd][1]) ;
   col[ellpsd][2] += prop*(newcol[2]-col[ellpsd][2]) ;
   if (t == 52) col[ellpsd][0] = -newcol[0] ;
}  /* docolour */
/***************************************/

void doplace(void)
/*
  set observers viewing point to new values.

  called by  action,
*/
{
   pplace[0] += prop*(xx[0]-pplace[0]);
   pplace[1] += prop*(xx[1]-pplace[1]);
   pplace[2] += prop*(xx[2]-pplace[2]);
}  /* doplace */
/***************************************/

void setobs(void)
/*
  set up matrix 'obs' for eulerian angles in 'ang'.

  called by action,
  calls     rset, matmul,
*/
{
   double newang[3];
   double r1[3][3],r2[3][3],r3[3][3] ;

   newang[0] = oldang[0] + prop*(ang[0]-oldang[0]);
   newang[1] = oldang[1] + prop*(ang[1]-oldang[1]);
   newang[2] = oldang[2] + prop*(ang[2]-oldang[2]);
   rset(r1,newang[0],0) ;
   rset(r2,newang[1],1) ;
   rset(r3,newang[2],2) ;
   matmul(r1,r2,obs) ;
   matmul(obs,r3,obs) ;
   oldang[0] = newang[0];
   oldang[1] = newang[1];
   oldang[2] = newang[2];
}  /* setobs */
/************************************************************/

void enquir(int thisp, double array[EMAX][3])
/*
  store values from 'array' into variables.

  called by  action,
*/
{
   val[var0] = array[thisp][0] ;
   val[var1] = array[thisp][1] ;
   val[var2] = array[thisp][2] ;
}  /* enquir */
/************************************************************/


void doattach(void)
/*
  create a joint 'join' at point 'x,y,z'
  relative to centre of refell.

  called by action,
  calls     findfg,
*/
{
   int fig1,fig2,low,high ;

   if ((coel[join][1] != -1) || (coel[join][0] != -1))
   {
      ok = 42 ;
      printf("doattach: join %d, coel[join][0] %d,  coel[join][1] %d\n",
              join,coel[join][0],coel[join][1]);
   }
   else
   {
/*
  find lowest ellipsoid of the figures being connected-
*/
      fig1 = findfg(ellpsd);
      fig2 = findfg(refell);
      if (ok == 0)
      {
         high = fig2 ;
         low = fig1 ;
         if (figell[low] > figell[high])
         {
            low = fig2 ;
            high = fig1 ;
         }
         figell[high] = figell[low] ;
         coel[join][0] = ellpsd ;
         coel[join][1] = refell ;
         jnt[join][0] = xx[0]+cen[ellpsd][0] ;
         jnt[join][1] = xx[1]+cen[ellpsd][1] ;
         jnt[join][2] = xx[2]+cen[ellpsd][2] ;
      }
   }
}  /* doattach */
/*************************************/

void dodetach(void)
/*
  split 1 figure into 2.

  called by action,
  calls     findfg, setels,
*/
{
   int othere,otherf;
   int j,k;
   int fgk ;
   int fg[2],el[2] ;
/*
  check if the new figure 'fig' is already being used -
*/
   j = figell[fig] ;
   if (j != 0)
   {
      ok = 43 ;
      printf("\nOOPS dodetach:  fig %d %s,  figell[fig] %d %s\n",
              fig,fname[fig],figell[fig],ename[figell[fig]]);
      goto rtrn ;
   }
/*
   fig ok, so start detaching-
*/
   othere = 0 ;
   if (coel[join][0] == ellpsd) othere = coel[join][1] ;
   if (coel[join][1] == ellpsd) othere = coel[join][0] ;
   if (othere == 0)
   {
      ok = 44 ;
      printf("\nOOPS dodetach:  join %d %s,  ellpsd %d %s, othere %d %s\n",
              join,jname[join],ellpsd,ename[ellpsd],othere,ename[othere]);
      goto rtrn;
   }
   otherf = findfg(othere);
   if (ok != 0) goto rtrn ;
/*
   move all the joints down one -
*/
   for (j = join; j < njts; ++j)
   {
      coel[j][0] = coel[j+1][0] ;
      coel[j][1] = coel[j+1][1] ;
      jnt[j][0] = jnt[j+1][0];
      jnt[j][1] = jnt[j+1][1];
      jnt[j][2] = jnt[j+1][2];
   }
   --njts;
/*
   find representative ellipsoid of each figure -
*/
   el[0] = ellpsd ;
   el[1] = othere ;
   fg[0] = fig ;
   fg[1] = otherf ;
   for (  k = 0 ; k < 2 ; ++ k )
   {
      setels(el[k],-1);
      fgk = fg[k] ;
      figell[fgk] = EMAX ;
      for (  j = 0 ; j < ecount ; ++ j )
         if (elist[j] < figell[fgk]) figell[fgk] = elist[j] ;
   }
rtrn: ;
}  /* dodetach */
/*******************************/

void domoveby( double x, double y, double z, int refell)
/*
  moves ellipsoids and joints in lists 'elist' and 'jlist'
  by vector 'x,y,z' relative to the axes of 'refell'.

  called by  try, action, abut, fun,
  calls      rotget, vecmul, shift,
*/
{
   double v[EMAX][3];
   double r[3][3];
   double unr[3][3] ;

   v[0][0] = x ;
   v[0][1] = y ;
   v[0][2] = z ;
   rotget(r,unr,refell) ;
   vecmul(v,r,0) ;
   shift(v[0][0],v[0][1],v[0][2]);
}  /* domoveby */
/************************************************************/

void dogroell( double f[3], int j, double a[EMAX][3])
/*
  scales jth member of array by factor 'f'.

  called by  action, dogrofig,
*/
{
   a[j][0] *= f[0] ;
   a[j][1] *= f[1] ;
   a[j][2] *= f[2] ;
}  /* dogroell */
/***************************************/

void dogrofig( double x0, double x1, double x2)
/*
  scale parts in 'elist' and 'jlist' about the point 'x0,x1,x2',
  multiplying all semi-axes and coords of centres and joints
  by factor[0],factor[1],factor[2] in x,y, and z directions
  respectively

  called by  action, dogrojnt,
  calls      shift, dogroell,
*/
{
   int e,j,n ;

   shift(-x0,-x1,-x2);
   for (  n = 0 ; n < ecount ; ++ n )
   {
      e = elist[n];
      dogroell(factor,e,cen) ;
      dogroell(factor,e,ax) ;
      maxax[e] = ax[e][0];
      minax[e] = ax[e][0];
      for (j = 1; j < 3; ++j)
      {
         if (ax[e][j] > maxax[e]) maxax[e] = ax[e][j];
         if (ax[e][j] < minax[e]) minax[e] = ax[e][j];
      }
   }
   for (  n = 0 ; n < jcount ; ++ n )
      dogroell(factor,jlist[n],jnt) ;
   shift(x0,x1,x2);
}  /* dogrofig */
/********************************************/

void dogrojnt(void)
/*
  scales ellipsoid 'ellpsd' by factors 'f', keeping position
  of joint 'join' fixed and moving all other joints and
  ellipsoids connected to 'ellpsd' appropriately.

  called by  action,
  calls      rotget, twirl, dogrofig, setels, vecmul, shift,
*/
{
   double d[EMAX][3],r[3][3],unr[3][3] ;
   double x0,x1,x2;
   int jscan,othere,dim ;

   if ((njts <= 0) || (njts > EMAX)) goto lab11 ;
   if ((coel[join][0] != ellpsd)&&(coel[join][1] != ellpsd))
      goto lab12 ;

   rotget(r,unr,ellpsd) ;
/*
  scale and shift the growing ellipsoid-
*/
   x0 = jnt[join][0] ;
   x1 = jnt[join][1] ;
   x2 = jnt[join][2] ;
   elist[0] = ellpsd ;
   ecount = 1;
   jcount = 0;
   twirl(x0,x1,x2,unr) ;
   dogrofig(x0,x1,x2) ;
   twirl(x0,x1,x2,r) ;
/*
  now shift everything connected to ellpsd-
*/
   for ( jscan = 0 ; jscan < njts ; ++ jscan )
   {
      if (jscan != join)
      {
         othere = 0 ;
         if (coel[jscan][0] == ellpsd) othere = coel[jscan][1] ;
         if (coel[jscan][1] == ellpsd) othere = coel[jscan][0] ;
         if (othere != 0)
         {
/*
  find parts connected to jscan through othere-
*/
            setels(othere,jscan);
            if (ok != 0) goto lab10 ;
/*
  find out how much to shift things hanging here-
*/
            for ( dim = 0 ; dim < 3 ; ++ dim )
               d[0][dim] = jnt[jscan][dim]-jnt[join][dim] ;
            vecmul(d,unr,0) ;
            for ( dim = 0 ; dim < 3 ; ++ dim )
               d[0][dim] = d[0][dim]*(factor[dim]-doub1) ;
            vecmul(d,r,0) ;
            shift(d[0][0],d[0][1],d[0][2]);
         } /* othere != 0 */
      } /* jscan != join */
   } /* jscan */
   goto lab10 ;
/*
  snags-
*/
lab11: ok = 40 ;
   printf("\nOOPS dogrojnt:  njts %d\n",njts);
   goto lab10 ;

lab12: ok = 41 ;
   printf("\nOOPS dogrojnt:  ellpsd %d\n",ellpsd);

lab10: ;
}  /* dogrojnt */
/************************************************************/

void domovjnt(void)
/*
  moves joint 'join' by amounts 'x', keeping the position
  of ellipsoid 'ellpsd' fixed and moving all other joints
  and ellipsoids connected to 'join' appropriately.

  called by  action,
  calls      rotget, setjnt, vecmul, shift,
*/
{
   double d[EMAX][3],r[3][3],unr[3][3] ;
   int othere,dim ;

   if ((njts <= 0) || (njts > EMAX)) goto lab11 ;
   othere = 0 ;
   if (coel[join][0] == ellpsd) othere = coel[join][1] ;
   if (coel[join][1] == ellpsd) othere = coel[join][0] ;
   if (othere == 0) goto lab11 ;

   rotget(r,unr,ellpsd) ;
/*
  shift the joint -
*/
   for (dim = 0; dim <3; ++dim)
       d[0][dim] = frac*xx[dim];
   setjnt(ellpsd,join);
   vecmul(d,unr,0);
   shift(d[0][0],d[0][1],d[0][2]);
   goto lab10 ;
/*
  snags-
*/
lab11: ok = 63 ;
   printf("\nOOPS domovjnt:  join %d,  ellpsd %d\n",
              join,ellpsd);

lab10: ;
}  /* domovjnt */
/************************************************************/

void dobalanc(void)
/*
  balance part of a figure by bending ellipsoid 'ellpsd' at
  the joint at point 'x' about 'axis' of ellipsoid 'refell'.

  called by  action,
  calls      rotget, rset, matmul, vecmat, dospinby,
*/
{
   double wsum,wmod,uw,vw,alpha,beta,phi,mass;
   double dx[3],u[3],u1[3],u2[3],v[3],w[3],w1[3],ww[3];
   double ro[3][3],unro[3][3],rph[3][3],ralph[3][3],rb[3][3];
   double usq;
   int j,k,thise ;

   rotget(ro,unro,refell) ;
/*
  form unit vector along rotation axis
*/
   for (  k = 0 ; k < 3 ; ++ k )
   {
      ww[k] = doub0;
      u[k] = ro[k][axis] ;
   }
/*
  run through moving ellipsoids-
*/
   for (  j = 0 ; j < ecount ; ++ j )
   {
      thise = elist[j] ;
      mass = ax[thise][0]*ax[thise][1]*ax[thise][2] ;
/*
  find vector to jth moving ellipsoid centre-
*/
      for (  k = 0 ; k < 3 ; ++ k )
      {
         dx[k] = cen[thise][k]-xx[k];
         ww[k] += mass*dx[k];
      }
   }
/*
  find vector 'w' to centre of mass of moving parts -
*/
   wsum = doub0;
   for (k = 0; k < 3; ++k)
      wsum += ww[k]*ww[k];
   if (wsum > doub0) wmod = sqrt(wsum); else wmod = doub0;
   for (k = 0; k < 3; ++k)
      if (wmod > doub0) w[k] = ww[k]/wmod; else w[k] = doub0;
/*
   find vector 'v' at point on meridien through u
   equal in distance from u as w is from u -
*/
   uw = doub0;
   for (k = 0; k < 3; ++k)
      uw += u[k]*w[k];
   usq = u[0]*u[0] + u[2]*u[2];
   if (usq > doub0) u1[0] = sqrt(usq); else u1[0] = doub0;
   u1[1] = u[1];
   u1[2] = doub0;
   if ((uw < -doub1) || (uw > doub1))
	   alpha = doub0;
   else
	   alpha = acos(uw);
   rset(ralph,alpha,2);
   vecmat(u1,ralph,u2);
   phi = -atan2(u[2],u[0]);
   rset(rph,phi,1);
   vecmat(u2,rph,v);
   vw = v[0]*w[0] + v[1]*w[1] + v[2]*w[2];
   if ((vw > -doub1) && (vw < doub1))
	   beta = acos(vw);
   else
	   beta = doub0;
   rset(rb,beta,axis);
   matmul(rb,unro,rb);
   matmul(ro,rb,rb);
   vecmat(w,rb,w1);
   if (w[1] > w1[1]) beta = -beta;
   dospinby(xx,refell,beta,axis) ;
}  /* dobalanc */
/************************************************************/

void dodrag(void)
/*
   bend 'ellpsd' at joint 'join' with coordinates 'x'
   about 'axis' of 'refell' to make 'ell1' touch the ground

   called by  action,
   calls      dospinby, save, restore, shift, doground,
              setels, doangles,
*/
{
	int jb,jc,jd;
	int fixde;
	int quadrant,qa,qb,qd;
	double gap;
	double yj;
	double proptemp;
	double xa,xb,xd;
	double dx;
	double y,ya,yb,yd;

	proptemp = prop;
	prop = doub1;
/*
	set rest of figure section, excluding ellpsd-ell1,
	to touch the ground -
*/
	fixde = 0;
	if ( coel[join][0] == ellpsd ) fixde = coel[join][1];
	if ( coel[join][1] == ellpsd ) fixde = coel[join][0];
	if ( fixde == 0)
	{
		ok = 65;
		printf(
			"\nOOPS dodrag: %s not connected to joint %s\n",
			ename[ellpsd],jname[join]);
		printf("which joins  %s and %s\n",
			ename[coel[join][0]], ename[coel[join][1]]);
		bell ( 1, 1 );
		prop = proptemp;
	} /* joint does not connect specified ellipsoid */
	else
	{
		setels(fixde,join);
		gap = doground();
		setels(fixde,-1);
		shift ( doub0, -gap, doub0 );
		yj = jnt[join][1] + minax[ell1];
		if (yj <= minax[ellpsd])
			printf("dodrag snag : joint too low\n");
		else
		if ( yj > minax[ellpsd] )
		{
/*
	which quadrant is centre of ell1 in wrt join -
*/
			quadrant = 0;
			if ( jnt[join][0] > cen[ell1][0] ) quadrant += 1;
			if ( jnt[join][2] > cen[ell1][2] ) quadrant += 2;
			save ( );
			xx[0] = jnt[join][0];
			xx[1] = jnt[join][1];
			xx[2] = jnt[join][2];
			setels(ellpsd,join);
			y = doground ( );
//printf("dodrag  %d %f %s   %f %f %f\n",
//f,y,ename[ell1],cen[ell1][0],cen[ell1][1],cen[ell1][2]);
//printf("            %s   %f %f %f\n",
//ename[fixde],cen[fixde][0],cen[fixde][1],cen[fixde][2]);
//
			setels(ellpsd,join);
			xa = doub0;
			qa = quadrant;
			ya = y;
//
			xb = doub2;
			qb = -1;
			for (jb = 0; ((jb < 8)&&(qb != quadrant)); ++jb)
			{
				xb *= inv2;
				restore();
				dospinby ( xx, refell, xb, axis );
				yb = doground ( );
				qb = 0;
				if ( jnt[join][0] > cen[ell1][0] ) qb += 1;
				if ( jnt[join][2] > cen[ell1][2] ) qb += 2;
//printf("dodragb %d %f %f %d\n",jb,xb,yb,qb);
			}
			xd = doub0;
			if (ya*yb < doub0)
			{
				for (jc = 1; jc < 9; ++jc)
				{
					dx = (xb - xa)*inv2;
					if ((ya*yb < doub0)||(ya*ya < yb*yb))
						xb = xb - dx;
					else
					{
						xa = xb;
						ya = yb;
						xb = xb + dx;
					}
					restore();
					dospinby ( xx, refell, xb, axis );
					yb = doground ( );
					qb = 0;
					if ( jnt[join][0] > cen[ell1][0] ) qb += 1;
					if ( jnt[join][2] > cen[ell1][2] ) qb += 2;
//printf("dodragc %d %f %f %d\n",jc,xb,yb,qb);
				} /* jc loop */
//printf("dodragd %d %f %s   %f %f %f\n",
//f,xb,ename[ell1],cen[ell1][0],cen[ell1][1],cen[ell1][2]);
				qd = -1;
				xd = xb*doub2;
				for (jd = 0; ((jd < 8)&&(qd != quadrant)); ++jd)
				{
					xd *= inv2;
					restore();
					dospinby ( xx, refell, xd, axis );
					yd = doground ( );
					qd = 0;
					if ( jnt[join][0] > cen[ell1][0] ) qd += 1;
					if ( jnt[join][2] > cen[ell1][2] ) qd += 2;
//printf("dodrage %d %f %f %d\n",jd,xd,yd,qd);
				} /* jd */
			} /* ya*yb < 0 */
			restore();
			prop = proptemp;
//printf("dodragf %d %f %s   %f %f %f\n",
//f,xd,ename[ell1],cen[ell1][0],cen[ell1][1],cen[ell1][2]);
			dospinby ( xx, refell, prop*xd, axis );
//printf("dodragg %d %f %s  %f %f %f\n\n",
//f,prop*xd,ename[ell1],cen[ell1][0],cen[ell1][1],cen[ell1][2]);
//printf("            %s   %f %f %f\n\n",
//ename[fixde],cen[fixde][0],cen[fixde][1],cen[fixde][2]);
			prdone = TRUE;
		} /* joint OK */
	}  /* connections  OK */
} /* dodrag */
/************************************************************/

double dcen(double d[3])
/*
  find separation between ellipsoid centres

  called by  doabut, sepn,
*/
{
   int j;
   double ans,dsq;

   dsq = doub0 ;
   for (j = 0; j < 3; ++ j)
   {
      d[j] = cen[ell1][j]-cen[ell2][j];
      dsq += d[j]*d[j];
   }
   if (dsq > doub0) ans = sqrt(dsq); else ans = doub0;
   return(ans);
}  /* dcen */
/************************************************************/

double newton(int n, double start, double a[])
/*
   solve the polynomial of degree (n-1):

           n-1           n-2
   a[n-1]*x    + a[n-2]*x    + ... a[1]*x + a[0] = 0

   using 48 Newton-Raphson iterations starting at 'start'.

   called by  surf,
*/
{
   double x,xold,num,den;
   int j,k;

   x = start;
   xold = doub2*start+doub1;
   num = doub1;
   for (j = 0;
      ((j < 48) && (num != doub0) && (x != xold)); ++j)
   {
      num = doub0;
      den = doub0;
      for (k = n-1; k >= 0; --k)
      {
         num = x*num + a[k];
         if (k > 0) den = x*den + a[k]*double(k);
      }
      if (den == doub0)
      {
         ok = 57;
         printf("\nOOPS newton: ell2 %d, den %f\n",
              join,ell1,coel[join][0],coel[join][1]);
         x = -doub1;
         xold = -doub1;
      }
      else
      {
         xold = x;
         if (den != doub0) x -= num/den;
      }
   }
   return(x);
}  /* newton */
/*******************************************************/

void getmat(double mat[3][3], double tr[3][3], double untr[3][3],
			double trtr[3][3], double untrtr[3][3], int ell)
/*
   for ellipsoid 'ell', find its matrix 'mat',
   also: its transformation matrix 'tr' and
   its transpose 'trtr', and its inverse 'untr'
   and its inverse transpose 'untrtr'.

   called by  surf,
   calls      rotget, matmul,
*/
{
   double r[3][3],unr[3][3];
   double diag[3][3];
   double undiag[3][3];
   int j,k;
/*
   make the matrix -
*/
   rotget(r,unr,ell);
   for (j = 0; j < 3; ++j)
   {
      for (k = 0; k < 3; ++k)
      {
         undiag[j][k] = doub0;
         diag[j][k] = doub0;
      }
      if (ax[ell][j] == doub0)
      {
         ok = 60;
         printf("\nOOPS getmat: ell %d, j %d,  ax[ell][j] %f\n",
              ell,j,ax[ell][j]);
         goto done;
      }
      if (ax[ell][j] > doub0)
         undiag[j][j] = doub1/ax[ell][j];
      else
         undiag[j][j] = doub0;
      diag[j][j] = ax[ell][j];
   }
   matmul(undiag,unr,trtr);
   matmul(r,undiag,untrtr);
   matmul(untrtr,trtr,mat);
/*
  make the transformation matrices-
*/
   matmul(diag,unr,untr);
   matmul(r,diag,tr);
done: ;
} /* getmat */
/***********************************************/

void getaxes(double m[3][3], double axes[3], double r[3][3])
/*
   from its matrix 'm', find the 3 semiaxes of an ellipsoid
   and corresponding rotation matrix 'r'.

   called by  surf,
   calls      matmul,
*/
{
   double lambda,mu,nu,nusq,numu;
   double s[3][3],t[3][3];
   double st[3][3],tmp[3][3];
   double sn,cs,sig;
   double a,b,c,abc;
   int p,q;
   int j,k,n;

   for (j = 0; j < 3; ++j)
   {
      for (k = 0; k < 3; ++k)
      {
         r[j][k] = doub0;
         t[j][k] = m[j][k];
      }
      r[j][j] = doub1;
   }
/*
   iterate 3 times -
*/
   for (n = 0; n < 3; ++n)
   {
/*
   find largest off-diagonal element -
*/
      a =  t[0][1]; if (a < doub0) a = -a;
      b =  t[0][2]; if (b < doub0) b = -b;
      c =  t[1][2]; if (c < doub0) c = -c;
      abc = a; p = 0; q = 1;
      if (b > abc)
      {
         abc = b;
         q = 2;
      }
      if (c > abc)
      {
         abc = c;
         p = 1;
         q = 2;
      }
      if (abc != doub0)
      {
         lambda = -t[p][q];
         mu = inv2*(t[p][p] - t[q][q]);
         nusq = lambda*lambda + mu*mu;
         if (nusq > doub0)
            nu = sqrt(nusq);
         else
            nu = doub0;
         if (mu > doub0)
            sig = doub1;
         else
            sig = -doub1;
         numu = nu + mu*sig;
         if ((nu > doub0) && (numu > doub0))
            cs = sqrt((numu)/(doub2*nu));
         else
            cs = doub0;
         if ((cs > doub0) && (nu > doub0))
            sn = sig*lambda/(cs*doub2*nu);
         else
            sn = doub0;
         for (j = 0; j < 3; ++j)
         {
            for (k = 0; k < 3; ++k)
            {
               s[j][k] = doub0;
            }
            s[j][j] = doub1;
         }
         s[p][p] = cs;
         s[q][q] = cs;
         s[p][q] = sn;
         s[q][p] = -sn;
         for (j = 0; j < 3; ++j)
         {
            for (k = 0; k < 3; ++k)
            {
               st[j][k] = s[k][j];
            }
         }
         matmul(st,t,tmp);
         matmul(tmp,s,t);
         matmul(st,r,r);
      }
   }
   for (j = 0; j < 3; ++j)
   {
      if (t[j][j] == doub0)
      {
         ok = 60;
         printf("\nOOPS getaxes: ell1 %d,  ell2 %d,  j %d,  t[j][j] %f\n",
              ell1,ell2,j,t[j][j]);
      }
      else
      if (t[j][j] > doub0)
         axes[j] = doub1/sqrt(t[j][j]);
      else
         axes[j] = doub0;
   }
}  /* getaxes */
/******************************************************/

static void initsphere(void)
/*
    set up a unit sphere centred on the origin

    called by  main, checkeys,
*/
{
   int i,j,k,m,n;
   int nlat,nlong;
   double longi,lat;
   double dlat,dlong;
   double xval,yval,zval;
   double ssmall;

   if (nsph >= SMAX)
   {
      printf("initsphere oops %d > max, reset to %d\n",nsph,SMAX);
	  nsph = SMAX-2;
   }
   if (nsph < SMIN)
   {
      printf("initsphere oops %d < min, reset to %d\n",nsph,SMIN);
		nsph = SMIN;
   }
   dlat = pi/(double)nsph;
   dlong = dlat;
   nlong = nsph+nsph;
   nlat = nsph;
   lat = -piby2;
/*
   set up vertices -
*/
   for (i = 0; i <= nlat; i++)
   {
      ssmall = cosf(lat);
      yval = sinf(lat);
      longi = 0;
      for ( j = 0; j <= nlong; ++ j)
      {
         xval = ssmall*cosf(longi);
         point[i][j][0] = xval;
         zval = ssmall*sinf(longi);
         point[i][j][1] = yval;
         point[i][j][2] = zval;
         longi += dlong;
      }
      lat += dlat;
   }
/*
   set up faces and their normals -
*/
   m = 0;
   for (i = 0; i < nlat; ++i)
   {
      for (j = 0; j < nlong; ++j)
      {
         for (k = 0; k < 3; ++k)
         {
            sph[m][0][k] = point[i][j+1][k];
            sph[m][1][k] = point[i+1][j+1][k];
            sph[m][2][k] = point[i+1][j][k];
            sph[m][3][k] = point[i][j][k];
            norm[m][k] = doub0;
            for (n = 0; n < 4; ++n)
                norm[m][k] += inv4*sph[m][n][k];
         }
         ++m;
         if (m >= 4*SMAX*SMAX)
         {
            printf("initsphere faces (%d)  %d > %d\n",
				nsph,m,4*SMAX*SMAX);
            getout(1);
            if (ok == 1) goto rtrn;
         }
      }
   }
   nfaces = m;
rtrn: ;
}   /* initsphere */
/*************************************************/

double surf(int ell1, int ell2)
/*
  return 0 if ell1 touches ell2
  return -ve if they intersect
  return +ve if they do not intersect

    5 May 2007 skip if touch found
   15 Sep 2006 return 0 if they touch
   10 Sep 2006 use polyhedral vertices of ell1
               instead of ellipsoid
   10 Sep 2006 surf() uses 2 parameters
   17 Feb 1993 find distance between surfaces of ell1 and ell2
               using Buckdales algorithm (giving answer in
               transformed coordinates).
    1 Oct 1981 using polyhedral vertices of ell1 and ell2
               written: Don Herbison-Evans

   called by  dotouch, cutting,
   calls      sqr, setmat, vecmul, getout, initsphere
*/
{
	int j;
	double d12, dax, dmin;
	double c1[3],c2[3];

	dax = minax[ell1] + minax[ell2];
	dmin = doub0;
//
//   check separation of centres -
//
	for (j = 0; j < 3; ++j)
	{
		c1[j] = cen[ell1][j];
		c2[j] = cen[ell2][j];
		d12 = c1[j]-c2[j];
		dmin += d12*d12;
	}
	dmin = sqrt(dmin);
	return( dmin - dax);
} /* surf */
/***********************************/

void cutting ( void )
/*
  find if any ellipsoids intersect that shouldnt.

  called by  doframes,
  calls setmat, vecmul, getout, initsphere, surf

   15 Sep 2006 use surf() = 0 if ellipsoids touch
   10 Sep 2006 moved innards to surf()
   12 Aug 2006 fixed initsphere and setmat
    8 Aug 2006 Don Herbison-Evans
*/
{
	int j,k;
	int s,smin,smax;
	int ncut,ntemp;
	int el1,el2;
	double dmin;
	double m[3][3],m1[3][3],unm1[3][3];
	double e1c[EMAX][3];
	double c1[3];
	char key;

	ncut = 5;
	ntemp = nsph;
	nsph = ncut;
	if (2*nsph*nsph > EMAX)
		nsph = int(sqrt(double(EMAX-1)*inv2));
	printf("cuttinga %d %d\n",ntemp,ncut);
	initsphere ( );
	for (el1 = 1; el1 < (ne-1); ++el1)
	{
		setmat ( el1, m, m1, unm1 );
		for (j = 0; j < 3; ++j)
			c1[j] = cen[el1][j];
		s = 0;
		for (j = 0; j <= nsph; ++j)
		{
			for ( k = 0;  k <= (nsph+nsph); ++k)
			{
				e1c[s][0] = point[j][k][0];
				e1c[s][1] = point[j][k][1];
				e1c[s][2] = point[j][k][2];
				vecmul ( e1c, unm1, s);
				e1c[s][0] += c1[0];
				e1c[s][1] += c1[1];
				e1c[s][2] += c1[2];
				++s;
				if (s >= EMAX)
				{
					printf("snag in 'cutting'\n");
					printf(" no. vertices %d, max %d\n",
						2*nsph*nsph,EMAX);
					ok = 66;
					getout(ok);
				}
			} /* k loop */
		} /* j loop */
		smax = s;
		smin = -1;
		for (el2 = el1+1; el2 < ne; ++el2)
		{
			if (forbid[el1][el2] == true)
			{
				dmin = surf(el1, el2);
				if (dmin < doub0)
				{
					printf("frame %d: ellipsoid %s cuts ellpsoid %s\n",
						f,ename[el1],ename[el2]);
					printf ( "\n carry on regardless? Hit 'enter' for Yes, 'no' then 'enter' for No: " );
					key = getchar();
					if ( key == '\n' )
					{
						for (j = 0; j < ne; ++j)
							for (k = 0; k < ne; ++k)
								forbid[j][k] = false;
					}
					else
					{
						pause = true;
						fstop = f-1;
					}
				} // dmin
			} /* ell2 forbidden */
		} /* el2 */
	} /* el1 */
	nsph = ntemp;
	printf("cuttingb %d %d\n",el1,el2);
	initsphere ( );
} /* cutting */
/******************************************************/

double sepn(void)
/*
   find distance between surfaces of ell1 and ell2.

   called by  dotouch, fun, fndmin, doabut, try,
   calls      dcen, surf,
*/
{
   double dmid;
   double ans,minsep;
   double d[3];
/*
   find bounds on separation -
*/
   dmid = dcen(d);
   minsep = dmid-minax[ell1]-minax[ell2];
   if (minsep <= doub0)
   {
      ans = -doub1;
   }
   else
   {
      ans = surf(ell1,ell2);
      if (ans < doub0) ans = -doub1;
   }
   return(ans);
} /* sepn */
/**********************************************/

double fun(double xarg)
/*
   called by  solve,
   calls      setels, dospinby, doground, restore, sepn,
              domoveby,
*/
{
   double ans;
   double dx[3];

   ans = doub0;
   if (t == drag_keyword_code)
   {
      setels(ellpsd,join);
      restore();
      dospinby(xx,refell,xarg,axis);
      ecount = 1; elist[0] = ell1;
      ans = doground();
      return(ans);
   }
   else
   if (t == abut_keyword_code)
   {
      dx[0]=doub0;
      dx[1]=doub0;
      dx[2]=doub0;
      dx[axis] = xarg;
      domoveby(dx[0],dx[1],dx[2],refell);
      ans = sepn();
      if (ok != 0)
	     return(doub0);
      restore();
      return(ans);
   }
   else
   {
      ok = 59;
      return(doub0);
   }
} /* fun */
/*******************************************/

double solve(double a, double b, int n)
/*
   find a zero of 'fun()' in the range 'a' to 'b'
   to an accuracy of 1.0 on fun, using at most 'n' iterations.

   called by  doabut,
   calls      fun,
*/
{
   double valab,vala,valb;
   double angab,anga,angb;
   double dval;
   int k;

   angab = a;
   anga = a;
   vala = fun(a);
   if ((vala > -doub1) && (vala < doub1)) goto done;
   if (ok != 0) goto done;
   angab = b;
   angb = b;
   valb = fun(b);
   if (ok != 0) goto done;
   if ((valb > -doub1) && (valb < doub1)) goto done;
   if (vala*valb > doub0)
   {
      if (vala > doub0)
      {
         if (vala < valb) angab = a;
            else angab = b;
      }
      else
      {
         if (vala < valb) angab = b;
            else angab = a;
      }
      anga = doub0; angb = doub0;
      valab = doub0; vala = doub0; valb = doub0;
      goto done;
   }
   if (vala > valb)
   {
      valab = vala;
      vala = valb;
      valb = valab;
      angab = anga;
      anga = angb;
      angb = angab;
   }
   for (k = 0; k < n; ++k)
   {
      dval = vala-valb;
      if (dval < doub0) dval = -dval;
      if (dval < doub1) goto done;
      angab = inv2*(anga+angb);
      valab = fun(angab);
      if (ok != 0) goto done;
      if (valab < doub0)
      {
         anga = angab;
         vala = valab;
      }
      else
      {
         angb = angab;
         valb = valab;
      }
   }

done:
   return(angab);
} /* solve */
/*******************************************/

double angsepn ( double xx[3], int ell1, int ell2 )
/*
   find approx angular separation in radians at xx
   of ell1 and ell2 using minax

   called by  dotouch
   calls sqr

	 5 May 2007  zero if overlapping well
   16 Sep 2006  xx,ell1,ell2 parameters instead of global
*/
{
	  double dmin,dsep;
	  double asep;
	  double dist1, dist2;

	  dmin = minax[ell1] + minax[ell2];
	  dsep = sqrt (sqr ( cen[ell1][0] - cen[ell2][0] )
		  + sqr ( cen[ell1][1] - cen[ell2][1] )
		  + sqr ( cen[ell1][2] - cen[ell2][2] ) );
	  if (dsep <= dmin)
		  asep = doub0;
	  else
	  {
	     dist1 = sqrt( sqr ( xx[0] - cen[ell1][0] )
		     + sqr ( xx[1] - cen[ell1][1] )
		     + sqr ( xx[2] - cen[ell1][2] ) );

	     dist2 = sqrt( sqr ( xx[0] - cen[ell2][0] )
		     + sqr ( xx[1] - cen[ell2][1] )
		     + sqr ( xx[2] - cen[ell2][2] ) );

	     asep = (dsep + dsep) / (dist1 + dist2);
	  }
	  return( asep );
} /* angsepn */
/************************************************/

void dotouch(void)
/*
  make ellipsoid 'ell1' come as close as possible to 'ell2'
  by bending ellipsoid 'ellpsd' at the joint at point 'x'
  about 'axis' of ellipsoid 'refell'.

  called by  action,
  calls      angsepn, surf, save, restore, dospinby, sqr,

  	5 May 2007  skip if overlapping well already
  16 Sep 2006  find min of square of surf() penetration
  10 Sep 2006  surf() uses 2 parameters
   1 Oct 1981  written Don Herbison-Evans
*/
{
	double angj, angk;
	double arange;
	double dang;
	double gap, g1, gmin;
	double pro;
	int samples = 10;
	int iterations = 5;
	int j;
	int jend;
	int jmin;
	int jstart;
	int k;

	save ();
	pro = prop;
	prop = doub1;
	arange = angsepn ( xx, ell1, ell2 );
	jstart = -samples / 2;
	jend = jstart + samples;
	angk = doub0;
	for ( k = 0; k < iterations; ++k )
	{
		restore ();
		dang = arange / double( samples );
		angj = angk + dang * double( jstart );
		dospinby ( xx, refell, angj, axis );
		gap = sqr ( surf ( ell1, ell2 ) );
		g1 = gap;
		gmin = gap;
		jmin = jstart;
		/*
		seek minimum of gap,
		*/
		for ( j = jstart + 1; ( j < jend + 1 ); ++j )
		{
			restore ();
			angj = angk + dang * double( j );
			dospinby ( xx, refell, angj, axis );
			gap = sqr ( surf ( ell1, ell2 ) );
			if ( gap < gmin )
			{
				jmin = j;
				gmin = gap;
			}
		} /* j */
		if ( ( jmin != jstart ) && ( jmin != jend ) )
			arange = dang + dang;
		angk += dang*double( jmin );
	} /* k */
	prop = pro;
	restore ();
	angj = angk + dang * double( jmin );
	dospinby ( xx, refell, prop*angj, axis );
} /* dotouch */
/************************************************************/

double trying(double a)
/*
     function to be found a minimum of,
     called from doabut.

     called by  fndmin,
     calls      domoveby, sepn, restore,
*/
{
   double dx[3],s;

   if (t == abut_keyword_code)
   {
      dx[0] = doub0; dx[1] = doub0; dx[2] = doub0;
      dx[axis] = a;
      domoveby(dx[0],dx[1],dx[2],refell);
      s = sepn();
      restore();
   }
   else
   {
      ok = 62;
      s = doub0;
      printf("\nOOPS trying: doabut not calling it!\n");
   }
   return(s);
} /* trying */
/***************************************************/

double fndmin(double a, double b, int n)
/*
   finds the minimum value of 'try'
   in the range 'a' to 'b' using at most 'n' iterations.

   called by  dotouch,
   calls      try,
*/
{
   double trya,tryb,tryab;
   double olda,oldb;
   double mina,minb;
   int k;

   tryab = doub0;
   olda = a; oldb = b;
   for (k = 0; k < n; ++k)
   {
      trya = olda + (oldb-olda)*inv3;
      mina = trying(trya);
      if (ok != 0) goto out;
      tryb = oldb - (oldb-olda)*inv3;
      minb = trying(tryb);
      if (ok != 0) goto out;
      if (mina < minb) oldb = tryb;
         else olda = trya;
   }
   if (mina < minb) tryab = trya;
      else tryab = tryb;
out:
   return(tryab);
} /* fndmin */
/*******************************************/

void doabut(void)
/*
   move figure containg ell1 to touch ell1 to ell2
   along direction parallel to given axis of
   reference ellipsoid.

   called by  prfrm,
   calls      save, restore, sepn, dcen,
              rotget, vecmul, domoveby, solve, fndmin,
*/
{
   int j;
   int steps;
   double min,max;
   double mov;
   double dold,dnew;
   double xold,xnew;
   double forward,back;
   double shft;
   double dist;
   double cdist;
   double d[3];
   double dx[3];
   double v[EMAX][3];
   double r[3][3],unr[3][3];

   save();
   min = minax[ell1];
   if (min < minax[ell2]) min = minax[ell2];
   max = maxax[ell1];
   if (max < maxax[ell2]) max = maxax[ell2];
   if ((max > doub0) && (lg2 != doub0)) steps = int(doub2 + log(max)/lg2);
      else steps = 2;
   dist = sepn();
   if (ok != 0) goto out;
   for (j = 0; j < 3; ++j)
          dx[j] = doub0;
/*
   do they already just touch -
*/
   if (dist == doub0)
	   goto out;
   else
   if (dist < doub0)
/*
   they overlap already, so seek shortest way to separate them -
*/
   {
       mov = doub2*max;
       dx[axis] = mov;
       domoveby(dx[0],dx[1],dx[2],refell);
       forward = sepn();
       if (ok != 0) goto out;
       restore();
       dx[axis] = -mov;
       domoveby(dx[0],dx[1],dx[2],refell);
       back = sepn();
       if (ok != 0) goto out;
       restore();
       if ((back < doub0) && (forward < doub0))
       {
          ok = 58;
          printf("doabut: ell1 %d,  ell2 %d,  back %f,  forward %f",
              ell1,ell2,back,forward);
          goto out;
       }
       else
       if (back > forward) mov = -mov;
       shft = solve(doub0,mov,steps);
   }
   else
/*
  try to overlap them -
*/
   {
      cdist = dcen(d);
      for (j = 0; j < 3; ++ j)
         v[0][j] = d[j] ;
      rotget(r,unr,refell) ;
      vecmul(v,unr,0) ;
      mov = -v[0][axis];
      dnew = doubmax;
      xold = mov - max - min;
      for (xnew = mov-max; xnew < (mov+max+min);
              xnew += min*inv2)
      {
         dx[axis] = xnew;
         domoveby(dx[0],dx[1],dx[2],refell);
         dold = dnew;
         dnew = sepn();
         if (ok != 0) goto out;
         restore();
         if ((mov > doub0) && (dnew < doub0)) goto gotit;
         if ((mov < doub0) && (dnew > dold)) goto gotit;
         xold = xnew;
      }
      shft = xnew;
      goto out;

gotit:
      if ((dold > doub0) && (dnew > doub0)) goto domin;
/*
   they will overlap -
*/
      shft = solve(xold,xnew,steps);
      goto done;
/*
   they wont overlap so just bring them closest together -
*/
domin:
      shft = fndmin(xold-min,xnew,steps);
   }
/*
   move proportion to abut -
*/
done:
   restore();
   dx[axis] = prop*shft;
   domoveby(dx[0],dx[1],dx[2],refell);

out: ;
} /* doabut */
/***************************************************/
/*
   drawel.cpp version 42

   subroutines -
      getout      - exit keeping window open
      initialise  - initialise variables and constants
      openfile    - read file root and open input file
      action      - selects an action to perform
      doperfrm    - performs each action in turn for a given frame
      doframes    - simulates and stores each frame in turn
      help        - list interactive commands
      initsphere  - set up polyhedral approximation to a sphere
      dopause     - do nothing for a while
      donum       - write numbers on the animation window
      image       - draw the ellipsoids
      animate     - update interactive variables
      checkeys    - respond to keyboard commands
      initgraphics- initialise graphics window
      main       - run the show

/***********************************************/

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

void dolighting ( double x, double y, double z )
/*
change of lighting
*/
{
	lighting_rgb[0] = x / 255.0;
	lighting_rgb[1] = y / 255.0;
	lighting_rgb[2] = z / 255.0;
} /* dolighting */
/******************************************/

void doopacity ( void )
/*
	change of opacity

	calls elground, rotput, rset, setnup
*/
{
	int k,n;
	double y, phi;
	double r[3][3];
	double axe[3];

	// run thru ellipsoids to shadow each in turn -

	k = ne;
	for ( n = 1; n < ne; ++n )
	{
		phi = setnup ( n, axe );
		y = elground ( n );
		if ( y > doub0 )
		{
			cen[k][0] = cen[n][0];
			cen[k][1] = -inv5;
			cen[k][2] = cen[n][2];
			ax[k][0] = axe[0];
			ax[k][1] = inv5;
			ax[k][2] = axe[2];
			rset ( r, phi, 1 );
			rotput ( r, k );
			col[k][0] = doub1;
			col[k][1] = doub1;
			col[k][2] = doub1;
			col[k][3] = 100;  // transparency 0-100 flags 101-255

			++k;
		} /* y > 0 */
	}	  /* end n loop */
	ne = k;
} /* doopacity */
/*****************************************/

void doangles(int el, int re, double v[3])
/*
	store the angles of 'el' relative to 're' in 'val' array.
	in degrees.

	called by action, dodrag
	calls  matmul, rotget, rotput, mkang,

	14 Aug 2006  answers put in 3 element array
*/
{
	  double mvro[3][3],mvunro[3][3];
	  double stro[3][3],stunro[3][3];
	  double r[3][3];

	  rotget(stro,stunro,re);
	  rotget(mvro,mvunro,el);
	  matmul(stunro,mvro,r);
	  rotput(r,EMAX);
	  mkang(EMAX);
	  v[0] = ang[0] * degree;
	  v[1] = ang[1] * degree;
	  v[2] = ang[2] * degree;
	  if ((v[0] > doub179) && (v[0] < doub181))
	  {
			v[0] -= doub180;
			v[2] = -v[2];
	  }
	  if (v[1] > doub180) v[1] -= doub360;
}  /* doangles */
/***********************************************/

void dogrowto ( double x, double y, double z )
/*
	find distance between extremal points in each direction
	and scale to desired output

	growto  (fname)  (referenceellipsoid) (axis) (size)
		where size =
		(variablename)
		(value)
	makes the total extent of the nominated figure in its current articulated
	state equal to the value of size, in the direction parallel to the nominated
	axis of the reference ellipsoid (tangent plane to tangent plane, normal to
	this axis direction).

	called by  action
	calls dogroell, shift, bell,
*/
{
	double cen_min[3];
	double cen_max[3];
	double cen_dif[3];
	double cen_scale[3];

	int e;
	int j;
	int n;

	for ( j = 0; j < 3; ++j )
	{
		cen_min[j] = doubmax;
		cen_max[j] = -doubmax;
	}

	shift( -x, -y, -z );
	for ( n = 0; n < ecount; ++ n )
	{
		e = elist[n];
		maxax[e] = ax[e][0];
		minax[e] = ax[e][0];
		for ( j = 1; j < 3; ++j )
		{
			if ( ax[e][j] > maxax[e] ) maxax[e] = ax[e][j];
			if ( ax[e][j] < minax[e] ) minax[e] = ax[e][j];
		}
		for ( j = 0; j < 3; ++j )
		{
			if ( cen[e][j] > cen_min[j] ) cen_min[j] = cen[e][j];
			if ( cen[e][j] < cen_max[j] ) cen_max[j] = cen[e][j];
		}
	}

	for ( j = 0; j < 3; ++j )
	{
		cen_dif[j] = -( cen_max[j] - cen_min[j] );
		cen_scale[j] = 1.0;
		if ( cen_dif[j] > 0.0 ) cen_scale[j] = factor[j] / cen_dif[j];
		factor[j] = cen_scale[j];
	}

	for ( n = 0; n < ecount; ++ n )
	{
		e = elist[n];
		dogroell ( factor, e, cen );
		dogroell ( factor, e, ax );
		maxax[e] = ax[e][0];
		minax[e] = ax[e][0];
		for ( j = 1; j < 3; ++j )
		{
			if ( ax[e][j] > maxax[e] ) maxax[e] = ax[e][j];
			if ( ax[e][j] < minax[e] ) minax[e] = ax[e][j];
		}
	}

	for ( n = 0; n < jcount; ++ n )
		dogroell ( factor, jlist[n], jnt );

	shift ( x, y, z );
	return;
} /* dogrowto */
/******************************************/

void action ( int keyword_code )
/*
  decode and do an action keyword_code.

  called by  doperfrm,
  calls      doabut, doangles, doattach, dobalanc, dobend,
		docolour, dodetach, dodrag, dogroell, dogrofig, dogrojnt,
		dogrowto, doground, domoveby, domovjnt, dolighting,
		doopacity, doplace, dospinby, dospinto, dotouch,
		enquir, setobs, shift,

	 1 Sep 2006  allow world world means allow any intersection
	14 Aug 2006  altered parameters of doangles()
	13 Aug 2006  added allow and forbid

*/
{
	double min;
	double v[3];
	int j,k;

	if ( ( keyword_code < 7 ) || ( keyword_code > NKEYS ) )
	{
		/*
		int figure_keyword_code  =  1;
		int ellips_keyword_code  =  2;
		int joint_keyword_code   =  3;

		int accele_keyword_code  =  5;
		int subrou_keyword_code  =  6;
		*/

		ok = 24;
		printf ( "action type %d out of range %d %d\n", keyword_code, 7, NKEYS );
	}

	if ( keyword_code == balanc_keyword_code ) dobalanc();

	if ( keyword_code == attach_keyword_code ) doattach();

	if ( keyword_code == detach_keyword_code ) dodetach();

	if ( keyword_code == grofig_keyword_code ) dogrofig ( xx[0], xx[1], xx[2] );

	if ( keyword_code == spinto_keyword_code ) dospinto ( xx, refell, ang, prop );

	if ( keyword_code == moveby_keyword_code ) domoveby ( frac * xx[0], frac * xx[1], frac * xx[2], refell );

	if ( keyword_code == add_keyword_code ) val[var0] = xx[0] + xx[1];

	if ( keyword_code == touch_keyword_code ) dotouch ();

	if ( keyword_code == spinby_keyword_code ) dospinby ( xx, refell, ang[0] * frac, axis );

	if ( keyword_code == ground_keyword_code )
	{
		min = doground ();
		shift ( doub0, -prop * min, doub0 );
	}
	if ( keyword_code == bendby_keyword_code ) dospinby ( xx, refell, ang[0] * frac, axis );

	if ( keyword_code == set_keyword_code ) val[var0] = varval;

	if ( keyword_code == bendto_keyword_code ) dospinto ( xx, refell, ang, prop );

	if ( keyword_code == repeat_keyword_code )
	{
		ok = 25;
		printf ( "non-existent action %d\n", keyword_code );
	}
	if ( keyword_code == quadra_keyword_code )
	{
		ok = 26;
		printf ( "non-existent action %d\n", keyword_code );
	}
	if ( keyword_code == linear_keyword_code )
	{
		ok = 27;
		printf ( "non-existent action %d\n", keyword_code );
	}
	if ( keyword_code == observ_keyword_code ) setobs();

	if ( keyword_code == moveto_keyword_code ) shift ( prop * xx[0], prop * xx[1], prop * xx[2] );

	if ( keyword_code == invert_keyword_code )
	{
		if ( val[var0] != doub0 )
		{
			val[var0] = doub1 / val[var0];
		}
		else
		{
			val[var0] = doub0;
		}
	}
	if ( keyword_code == groell_keyword_code ) dogroell ( factor, ellpsd, ax );

	if ( keyword_code == grojnt_keyword_code ) dogrojnt();

	if ( keyword_code == growto_keyword_code ) dogrowto( xx[0], xx[1], xx[2] );

	if ( keyword_code == angles_keyword_code )
	{
		doangles ( ellpsd, refell, v );
		val[var0] = v[0]; val[var1] = v[1]; val[var2] = v[2];
	}

	if ( keyword_code == centre_keyword_code || keyword_code == center_keyword_code) enquir ( ellpsd, cen );

	if ( keyword_code == flex_keyword_code ) dobend ( ang[0] * frac, 0 );

	if ( keyword_code == rotate_keyword_code ) dobend ( ang[0] * frac, 1 );

	if ( keyword_code == abduct_keyword_code ) dobend ( ang[0] * frac, 2 );

	if ( keyword_code == negate_keyword_code ) val[var0] = -val[var0];

	if ( keyword_code == subtra_keyword_code ) val[var0] = xx[0] - xx[1];

	if ( keyword_code == divide_keyword_code )
	{
		if ( xx[1] == doub0 )
		{
			ok = 30;
			printf ( "action: divide, keyword_code %d,  EMAX-var0-1 %d,  xx[1] %f", keyword_code, EMAX-var0-1, xx[1] );
		}
		else
		{
			val[var0] = xx[0] / xx[1];
		}
	}
	if ( keyword_code == multip_keyword_code ) val[var0] = xx[0] * xx[1];

	if ( keyword_code == 45 )
	{
		ok = 28;
		printf ( "action: non-existent action %d\n", keyword_code );
	}
	if ( keyword_code == cubic_keyword_code )
	{
		ok = 29;
		printf ( "action: non-existent action %d\n", keyword_code );
	}
	if ( keyword_code == place_keyword_code ) doplace();

	if ( keyword_code == axes_keyword_code ) enquir ( ellpsd, ax );

	if ( keyword_code == linkx_keyword_code ) enquir ( join, jnt );

	if ( keyword_code == colour_keyword_code ||
		keyword_code == color_keyword_code ) docolour ( prop );

	if ( keyword_code == print_keyword_code ) printf ( "frame %d, %s %9g\n", f, vname[EMAX-var0-1], val[var0] );

	if ( keyword_code == textur_keyword_code ) docolour ( doub1 );

	if ( keyword_code == drag_keyword_code ) dodrag ();

	if ( keyword_code == abut_keyword_code ) doabut ();

	if ( keyword_code == movjnt_keyword_code ) domovjnt ();

	if ( keyword_code == opacty_keyword_code ) doopacity ();

	if ( keyword_code == lghtng_keyword_code ) dolighting ( xx[0], xx[1], xx[2] );

	if ( keyword_code == allow_keyword_code )
	{
		//printf("actionb allow %s %s\n",ename[ell1],ename[ell2]);
		forbid[ell1][ell2] = false;
		forbid[ell2][ell1] = false;
		if ((ell1+ell2) == 0)
		{
			for (j = 0; j < EMAX; ++j)
				for (k = 0; k < EMAX; ++k)
					forbid[j][k] = false;
		}
	}
	if ( keyword_code == forbid_keyword_code )
	{
		forbid[ell1][ell2] = true;
		forbid[ell2][ell1] = true;
		//printf("actionc forbid %s %s\n",ename[ell1],ename[ell2]);
	}
}  /* action */
/*********************************************************/

void doperfrm(int sub, int fr, int fstart, int fend)
/*
   perform actions of subroutine 'sub' for frame 'fr'
   between frames 'fstart' and 'fend'

   called by  doframes,
   calls      getvalu, setfrc, setper, action,
*/
{
   int frame;
   int newsub;
   int p;
   int pstart,pend;
   int fsstart;
   int fstrt,fstp;
   int fsubstart ;

   pstart = subact[sub][0] ;
   pend = subact[sub][1] ;
/*
  find 'subfrm', the earliest formal frame number in
  current subroutine ignoring unset variable
  frame numbers ( == -1) -
*/
   fsubstart = MAXINT ;
   for (p = pstart ; p <= pend ; ++p )
   {
      fsstart = getvalu(frstart[p]) ;
      if (ok != 0) goto snag ;
      if (fsstart >= 0)
      {
         fsstart *= fast ;
         if (fsstart < fsubstart) fsubstart = fsstart ;
      }
   }
   frame = fr + fsubstart - fstart;
   if (fr >= fstop) fstop = fr+1;
/*
  run through actions in the subroutine -
*/
  for (p = pstart; p <= pend; ++p)
  {
      pp = p;
      t = type[p] ;
      if ((t != stop_keyword_code)
			&&(t != subrou_keyword_code)
			&&(t != endsub_keyword_code))
      {
         fstrt = getvalu(frstart[p]) ;
         if (fstrt < 0)
         {
            ok = 46;
            printf("doperfrm: start %d\n",
                start);
         }
         if (ok != 0) goto snag ;
         fstp = getvalu(frstop[p]) ;
         if (fstp < fstrt)
         {
            ok = 47 ;
            printf("doperfrm: fstrt %d,  fstp %d\n",
                fstrt,fstp);
         }
         if (ok != 0) goto snag ;
         if (fstrt == fstp) ++fstp;
         fstrt *= fast ;
         fstp *= fast ;
         if ((fstp > frame) && (fr < fend)) ++more;
         if ((frame > fstrt) && (frame <= fstp))
         {
            if (t == call_keyword_code)
            {
               newsub = getvalu(pf[p][0]);
               if ((newsub <= 0) || (newsub > PMAX))
               {
                  ok = 8 ;
                  printf("doperfrm: newsub %d,  PMAX %d\n",
                         newsub,PMAX);
                  goto snag ;
               }
               if (distrn[p] == call_keyword_code)
                  doperfrm(newsub,frame,fstrt,fstp);
               else
                  doperfrm(newsub,frame,frame-1,frame);
               if (ok != 0) goto rtrn ;
            }
/*
  if not a subroutine call, then do normal action -
*/
            else
            {
               setfrc(frame,fstrt,fstp) ;
               if (ok != 0) goto snag ;
               setper(t);
               if (ok != 0) goto snag ;
               action(t);
               if (ok != 0) goto snag ;
            } /* t not call */
         } /* frame f in range of action p */
      } /* t not start or end of subroutine */
   } /* p */
   goto rtrn ;
/*
  snag-
*/
snag:
      printf("error in doperfrm, frame %d, action %d\n",
	      f,p+1);
	  getout(ok);
rtrn: ;
}  /* doperfrm */
/*********************************************/

void doframes(void)
/*
  calls and performs the actions for each frame in turn.

  called by  main,
  calls      doperfrm, store3,
*/
{
   int j;

   t = 1;
   axis = 1;
   join = 1;
   var0 = 1;
   var1 = 1;
   var2 = 1;
   fig = 1;
   ellpsd = 1;
   refell = 1;
   ell1 = 1;
   ell2 = 1;
   for (j = 0; j < 3; ++j)
   {
      newcol[j] = 0;
      oldang[j] = doub0;
      ang[j] = doub0;
      xx[j] = doub0;
      factor[j] = doub1;
   }
   varval = doub0;
/*
  simulate and store each frame of movie-
*/
   for (f = 1; more > 0; ++f)
   {
      more = 0;
      doperfrm(0,f,0,fstop);
      if ((fslow == 1) || (f%fslow == 1))
         store3(f);
   }
   if (vstart > fstart) fstart = vstart;
   if ((vstop > 0) && (vstop < fstop)) fstop = vstop;
} /* doframes */
/*********************************************/

void help(void)
/*
   list the interactive commands

   called by  main, checkeys,
*/
{
  printf("\n\n******* TO ACTIVATE THESE: CLICK IN THE ANIMATION WINDOW FIRST *******\n");
  printf("\n  Interactive commands :-\n\n");

  printf("\n\n   animation parameters\n");
  printf("    i - freeze (opp. of 'a')\n");
  printf("    a - continue animating (opp. of 'i')\n");
  printf("    c - continue through restart at full rate (opp. of 'p')\n");
  printf("    p - pause on first and last frames (opp. of 'c')\n");
  printf("    b - if frozen, go back 1 frame else run backwards (opp. of 'f')\n");
  printf("    f - if frozen, go forward 1 frame else run forwards (opp.of 'b')\n");
  printf("    0 - reset parameters to defaults, and freeze at start\n");
  printf("    - - slow down the animation \n");
  printf("    = - speed up the animation \n");

  printf("\n\n   scene movement parameters\n");
  printf("    d - shift down 10 per cent (opp. of 'u')\n");
  printf("    u - shift up 10 per cent (opp. of 'd')\n");
  printf("    l - shift scene left 10 per cent (opp. of 'r')\n");
  printf("    r - shift scene right 10 per cent (opp. of 'l')\n");
  printf("    t - shift scene away by 10 per cent(opp. of 't')\n");
  printf("    v - shift away (opp. of 'w')\n");
  printf("    w - shift nearer (opp. of 'v')\n");

  printf("\n\n   scene rotation parameters\n");
  printf("    x - rotate 3 degrees about x (left - right) axis (opp. of '1')\n");
  printf("    y - rotate 3 degrees about y (vertical) axis (opp. of '2')\n");
  printf("    z - rotate 3 degrees about z (front - back) axis  (opp. of '3')\n");
  printf("    1 - rotate 10 degrees about x (right - left) axis (opp. of 'x')\n");
  printf("    2 - rotate 10 degrees about y (vertical) axis (opp. of 'y')\n");
  printf("    3 - rotate 10 degrees about z (back - front) axis  (opp. of 'z')\n");

  printf("\n\n   scene size parameters\n");
  printf("    g - grow scene by 10 per cent (opp. of 's')\n");
  printf("    s - shrink scene by 10 per cent (opp. of 'g')\n");

  printf("\n\n   polygon parameters\n");
  printf("    j - increase the number of polygons per sphere by 1 {opp. of 'k')\n");
  printf("    k - decrease the number of polygons per sphere by 1 {opp. of 'j')\n");

  printf("\n\n   shading parameters\n");
  printf("    4 - normal shading/modified shading (toggle)\n");
  printf("    6 - display shadows (toggle) - inoperative at present\n");
  printf("    8 - display footprints (toggle) - inoperative at present\n");

  printf("\n\n   annotation parameters\n");
  printf("    n - display of frame numbers (toggle)\n");
  printf("    o - display of bar numbers (toggle)\n");
  printf("    5 - display of time (toggle) - inoperative at present\n");

  printf("\n\n   avi output parameters\n");
  printf("    7 - save display as AVI file - inoperative at present\n");

  printf("\n\n   program usage parameters\n");
  printf("    h - show these instructions\n");
  printf("    q - quit\n");

  printf(" \n\n******* TO ACTIVATE THESE: CLICK IN THE ANIMATION WINDOW FIRST *******\n");
} /* help */
/********************************************/


void dopause(int t)
/*
   pause for a while

   called by  image, animate,
*/
{
   double a;
   int j,k;

   a = 1.0;
   for (j = 1; j < t*1000; ++j)
   {
      for (k = 1; k < 1000; ++k)
      {
         a += double(j)/double(k);
      }
   }
   if (a < 0.0) printf("%d\n",t);
} /* dopause */
/*****************************************/

void donum(int f)
/*
   draw bar and/or frame numbers

   called by image,
*/
{
   char nstr[BMAX];
   int b,c,nlngth;

   if (bnums == TRUE)
   {
      b = int(doub1 + inv2 + double(f)/double(frperbar));
      sprintf(nstr,"bar %d",b);
      nlngth = strlen(nstr);
      glColor3f(0.9, 0.0, 0.9);
      glRasterPos3f(0.05,0.95,0.999999);
      for (c = 0; c < nlngth; c++)
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nstr[c]);
   }
   if (fnums == TRUE)
   {
      sprintf(nstr,"frame %d",f);
      nlngth = strlen(nstr);
      glColor3f(0.9, 0.0, 0.9);
      glRasterPos3f(0.05,0.05,0.999999);
      for (c = 0; c < nlngth; c++)
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nstr[c]);

	  //pres_time = clock();
	  //rate = CLOCKS_PER_SEC/(pres_time - prev_time);
	  //prev_time = pres_time;
	  //glRasterPos3f(0.9,0.05,0.999999);
	  //printf("%d fr/sec  %d %d %d\n",
		  //rate,pres_time,prev_time,CLOCKS_PER_SEC);
	  //sprintf(nstr, "%d fr/sec",rate);
	  //nlngth = strlen(nstr);
	  //for (c = 0; c < nlngth; c++)
         //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nstr[c]);
   }
} /* donum */
/**********************************************************/

void ellmat(double r[3][3], int e, int f)
/*
   for ellipsoid 'e' in frame 'f' find its
   rotation matrix 'r',

   called by  image,
*/
{
      double p,cp,sp;
      double x,y,z,m,xsp,ysp,zsp,xm,ym,zm,xym,xzm,yzm ;

      p = qu3[f][e][0]*radian ;
      x = qu3[f][e][1] ;
      y = qu3[f][e][2] ;
      z = qu3[f][e][3] ;
      sp = sin(p);
      cp = cos(p);
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
} /* ellmat */
/***********************************************/

void image(void)
/*
   called by  main,
   calls      donum, dopause, ellmat,
*/
{
    int e,j,k;
    double amb,shade,illum;
    double r[3][3];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (e = 1; e < nels[f]; ++e)
    {
         glPushMatrix();

         // interactive parameters -

         glScalef(doub1,doub1,inv10);
         glScalef(scale,scale,scale);
         glTranslatef(tx,ty,tz);
         glTranslatef(inv2,inv2,inv2);
         glRotatef(anglez,0,0,1);
         glRotatef(angley,0,1,0);
         glRotatef(anglex,1,0,0);

         // ellipsoid parameters -

         glTranslatef(ce3[f][e][0], ce3[f][e][1], ce3[f][e][2]);
         glRotatef(qu3[f][e][0], qu3[f][e][1], qu3[f][e][2], qu3[f][e][3]);
         glScalef(ax3[f][e][0], ax3[f][e][1], ax3[f][e][2]);
         ellmat(r,e,f);
         glPolygonMode(GL_FRONT, GL_FILL);
         glBegin(GL_QUADS);
         amb = 0.7;
         for (j = 0; j < nfaces; ++j)
         {
            illum = doub0;
            for (k = 0; k < 3; ++k)
                illum += r[k][1]*norm[j][k];
            shade = amb + (doub1 - amb)*illum;
            glColor3f(shade*co3[f][e][0], shade*co3[f][e][1], shade*co3[f][e][2]);
            for (k = 0; k < 4; ++k)
            {
               glVertex3f(sph[j][k][0],sph[j][k][1],sph[j][k][2]);
            } /* k  vertices */
         } /* j faces */
         glEnd();
         glPopMatrix();
    } /* e ellipsoids */
    if ((fnums == TRUE)||(bnums == TRUE)) donum(f);
    glutSwapBuffers();
    glFlush();
    if (slow < 0) slow = 0;
    if (slow > 0) dopause(slow);
} /* image */
/***************************************/

void animate(void)
/*
   called by  main,
   calls      dopause,
*/
{
    if (freeze == TRUE)
    {
         if (single == TODO)
         {
            if (forward == TRUE)
               df = 1;
            else
               df = -1;
         }
         else
            df = 0;
    }
    else
    if (forward == TRUE)
         df = 1;
    else
         df = -1;
    f += df;
    if (f < 1) f = fstop-1;
    if (f >= fstop) f = fstart+1;
    if (((f == (fstart+2)) || (f == (fstart+1))) && (pause == TRUE))
         dopause(100);
    anglex += dangx;
    angley += dangy;
    anglez += dangz;
    if (anglex < -doub180) anglex += doub360;
    if (anglex > doub180) anglex -= doub360;
    if (angley < -doub180) angley += doub360;
    if (angley > doub180) angley -= doub360;
    if (anglez < -doub180) anglez += doub360;
    if (anglez > doub180) anglez -= doub360;
    dangx = doub0;
    dangy = doub0;
    dangz = doub0;
    glutPostRedisplay();
    single = DONE;
} /* animate */
/***************************************/

void checkeys(unsigned char key, int x, int y)
/*
   called by  main,
   calls      initsphere,
*/
{
   if ((key == GLUT_KEY_ESCAPE) || (key == 'q'))
   {
         getout(0);
         if (ok == 1) main(0,junk);
   }
   if (key == 'h') help();
   if (key == 'j')
   {
         nsph +=1;
         printf("'j' more facets %d (opp. 'k')\n", nsph);
			printf("checkeysa %c\n",key);
         initsphere();
         if (ok == 1) main(0,junk);
   }
   if (key == 'k')
   {
         nsph -=1;
         printf("'k' fewer facets %d (opp. 'j')\n", nsph);
			printf("checkeysb %c\n",key);
         initsphere();
         if (ok == 1)  main(0,junk);
   }
   if (key == 'a')
   {
         df = 1;
         printf("'a' animate (opp. 'i')\n");
         if (forward == FALSE) df = -1;
         freeze = FALSE;
   }
   if (key == 'i')
   {
         freeze = TRUE;
         printf("'i' freeze (opp. 'a')\n");
   }
   if (key == 'f')
   {
         if (freeze == TRUE) single = TODO;
         printf("'f' forwards (opp. 'b')\n");
         forward = TRUE;
   }
   if (key == 'b')
   {
         if (freeze == TRUE) single = TODO;
         printf("'b' backwards (opp. 'f')\n");
         forward = FALSE;
   }
   if (key == 'p') { pause = TRUE; printf("'p' pause on first and last frames (opp. 'c')\n"); }
   if (key == 'c') { pause = FALSE; printf("'c' continuous looping (opp. 'p')\n"); }
   if (key == 'g') { scale *= 1.1; printf("'g' grow %f (opp.'s')\n", scale); }
   if (key == 's') { scale /= 1.1; printf("'s' shrink %f (opp. 'g')\n", scale); }
   if (key == 'l') { tx -= 0.1; printf("'l' shift left %f (opp. 'r')\n", tx); }
   if (key == 'r') { tx += 0.1; printf("'r' shift right %f (opp. 'l')\n", tx); }
   if (key == 'd') { ty -= 0.1; printf("'d' shift down %f (opp. 'u')\n", ty); }
   if (key == 'u') { ty += 0.1; printf("'u' shift up %f (opp. 'd')\n", ty); }
   if (key == 'v') { tz -= 0.1; printf("'v' shift in %f (opp. 'w')\n", tz); }
   if (key == 'w') { tz += 0.1; printf("'w' shift away %f (opp. 'v')\n", tz); }
   if (key == 'x') { dangx = alpha; printf("'x' rotate x %f (opp. '1')\n", anglex); }
   if (key == '1') { dangx = -alpha; printf("'1' rotate x %f (opp. 'x')\n", anglex); }
   if (key == 'y') { dangy = alpha; printf("'y' rotate y %f (opp. '2')\n", angley); }
   if (key == '2') { dangy = -alpha; printf("'2' rotate y %f (opp. 'y')\n", angley); }
   if (key == 'z') { dangz = alpha; printf("'z' rotate z %f (opp. '3')\n", anglez); }
   if (key == '3') { dangz = -alpha; printf("'3' rotate z %f (opp. 'z')\n", anglez); }
   if (key == '-') { slow += 2; printf("'-' slower %d (opp. '=')\n", slow); }
   if (key == '=') { slow -= 2; printf("'=' faster %d (opp. '-')\n", slow); }
   if (key == 'n')
   {
	   if (fnums == TRUE)
	   {
		   fnums = FALSE;
		   printf("'n' hide frame numbers (toggle)\n");
	   }
	   else
	   {
		   fnums = TRUE;
		   printf("'n' show frame numbers (toggle)\n");
	   }
   }
   if (key == 'o')
   {
	   if (bnums == TRUE)
	   {
		   bnums = FALSE;
		   printf("'n' hide bar numbers (toggle)\n");
	   }
	   else
	   {
		   bnums = TRUE;
		   printf("'n' show bar numbers (toggle)\n");
	   }
   }
   if (key == '0')
   {
      printf("'0' reset parameters and freeze at frame 1\n");
      f = fstart+1;
      freeze = TRUE;
      forward = TRUE;
      df = 1;
      scale = SCALE;
      tx = doub0;
      ty = doub0;
      tz = doub0;
      anglex = doub0;
      angley = doub0;
      anglez = doub0;
      slow = 1;
      nsph = SSTART;
   } /* key = '0' */
} /* checkeys */
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
}/* strcmpend */
/************************************************/

void get_files ( char file[] )
/*
   called by main
	calls strcmpend, bell, add_id_num,
*/
{
	int c;
	int i;
	int len;
	int last;
	//int err_count;
	int error;
	int loc_dot;
	//int from_ini;
	char key;
	bool get_out;
	//bool ini_ok;
	//bool file_ok;
	//bool dir_ok;
	bool lbn_type;
	char dir[BMAX];

	//from_ini = 0;
	//err_count = 0;
	error = 0;
	get_out = false;
	//ini_ok = false;
	//file_ok = false;
	//dir_ok = false;
	lbn_type = true;

	/*err_count = err_count + 1;
	if ( err_count >= 25 )
	{
		printf( " Limit: tried %d times for input file %s\n",
			err_count,name );
		ok = -1;
		return;
		}*/
	input_file_type = -1;
	for ( c = 0; c < BMAX; ++c )
	{
		name[c] = NULL;
		finname[c] = NULL;
		nudesname[c] = NULL;
	}

	if(file==NULL){
	  printf("\nPlease provide a filename\n");
	  exit(0);
	}
	else
	  strcpy ( name, file );

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
		error = 1;
		name[0] = NULL;
		exit(0);
	}

	printf( "\n    " );
	if ( input_file_type == 0 )
	{
		sprintf ( nudesname, "%s", name );
		if ( ( infile = fopen( nudesname, "r" ) ) == NULL )
		{
			if ( infile ) fclose ( infile );
			printf ( "\n\n %s OOPS?\n", nudesname );
			printf ( "file NOT found\nPlease give correct file name as argument\n ");
			bell ( 1, 1 );
			exit(0);
		}
		printf ( "  Opened %s\n", nudesname );
	}
	else if ( input_file_type > 0 )
	{
		strcpy( finname, name );

		if ( ( infile = fopen ( finname, "r" ) ) == NULL )
		{
			if ( infile ) fclose ( infile );
			printf ( "\n   %s ?  OOPS\n", finname );
			printf ( "file NOT found\nPlease give correct file name as argument\n ");
			bell ( 1, 1 );
			exit(0);
		}

		printf ( "\n   opened input file %s\n", finname );

		add_id_num ( name, nudesname, ".n" );
		if ( ( nudesfile = fopen ( nudesname, "w" ) ) == NULL )
		{
			if ( nudesfile ) fclose ( nudesfile );
			printf ( "\n\n %s OOPS?\n", nudesname );
			bell ( 1, 1 );
			exit(0);
		}
		printf ( "\n   created nudes file %s\n", nudesname );
	}
	if ( ( infile = fopen(nudesname, "r" ) ) == NULL )
	{
		if ( infile ) fclose ( infile );
		printf ( "\n\n %s OOPS?\n", nudesname );
		bell ( 1, 1 );
		exit(0);
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

void initgraphics(void)
/*
   called by  main,
*/
{
   char title[BMAX];

   sprintf(title,"%s  -  %s",ptitle,finname);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(width, height);
   glutInitWindowPosition(xw,yw);
   glutCreateWindow(title);
/* run in full screen if WINDOW_MODE macro undefined */
#ifndef WINDOW_MODE
   glutFullScreen();
#endif
/* background color */
   glClearColor(1.0, 1.0, 1.0, 0.5);

/* init viewing matrix */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
   glEnable(GL_DEPTH_TEST);
} /* initgraphics */
/***************************************/

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
	get_files ( argv[1] );
	if ( ok != 0 ) goto more;
	if (haslbn == TRUE)
	{
         fprintf(nudesfile,
            "*\n* created %s from %s using %s\n*\n",
            nudesname,name,ptitle);
         linter(argv[2]);
	}
	if(argv[2][0] == 'r')
	{
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
		goto more;
	}

}
