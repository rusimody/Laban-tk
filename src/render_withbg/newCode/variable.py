
class Define:
    DONE = 0
    NO = 0                 # no hold
    FMAX = 2048            # maximum number of frame
    EMAX = 1024            # maximum number of ellipsoids
    NKEYS = 1024 #64             # number of keywords
    PMAX = 6000            # maximum number of actions to perform
    VMAX = 2048            # max number of constants + variables
    BMAX = 256             # size of character buffer
    SSTART =  20           # initial number of chords around sphere
   
   
   #define TRUE      0
    #define FALSE     1
    #define DONE      0
    #define TODO      1
    #define MAN       0
    #define WOMAN     1
    #define MAXINT 1073741824
    #define WINDOW_MODE  1
    #define GLUT_KEY_ESCAPE 27
    #define EMAX   1024         // maximum number of ellipsoids
    #define SMAX    100         // maximum number of chords around sphere
    #define SMIN      2         // minimum number of chords around sphere
    
    #define LMAX   5000         // max number of laban score entries
    #define TMAX     30         // max number of staff lines
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
#                     // but both prepared to travel to man's L.
#                            #define CP         3        // counter promenade position: facing partner, bodies touching,
#                                                        // but both prepared to travel to man's R.
#                                                        #define DB         4        // double hold: facing partner, bodies apart,
#                                                                                    // L hand to R, R hand to L.
#                                                                                    #define OP         5        // open hold: facing partner, bodies apart,
#                                                                                                                // man's L to lady's R, other hands free.
#                                                                                                                #define CR         6        // crossed open hold: facing partner, bodies apart,
#                                                                                                                                            // man's R to lady's R, other hands free.
#                                                                                                                                            #define OE         7        // open extended hold: both facing same way, bodies apart,
#                                                                                                                                                                        // man's L hand to lady's R, other hands free.
#                                                                                                                                                                        #define CO         8        // counter open extended hold: both facing same way, bodies apart,
#                                                                                                                                                                                                    // man's R hand to lady's L, other hands free.
#                                                                                                                                                                                                    #define SH         9        // shadow hold: both facing same way, bodies touching,
#                                                                                                                                                                                                                                // L hand to L, R hand to R.
#                                                                                                                                                                                                                                #define SS        10        // semi-shadow hold: both facing same way, bodies touching,
#                                                                                                                                                                                                                                                            // man's L hand to lady's L,
#                                                                                                                                                                                                                                                                                        // man's R hand on lady's R hip, lady's R hand free.
#

class GlobalVariable:
    """ This Class is use to hold all global variables """
    programTitle="lintel084"
    barNumber =None 
    rise = None 
    prevc = None 
    previ = None 
    track =None 
    mspace = None 
    wspace =None 
    doub0 =None 
    doub1 = None 
    doub2 =None 
    doub3 =None 
    doub4 =None 
    doub10 =None 
    doub60 =None 
    doub90 =None 
    doub150 =None 
    doub179 = None 
    doub180 =None 
    doub181 = None 
    doub255 =None 
    doub360 =None 
    doub500 =None 
    inv2 = None 
    inv3 =None 
    inv4 =None 
    inv5 =None 
    inv6 =None 
    inv10 =None 
    inv256 =None 
    inv1000 =None 
    rt3 = None 
    piby2 = None 
    pi = None 
    twopi = None 
    radten = None 
    radian =None 
    degree =None 
    lg2 = None 
    freeze = None 
    forward = None 
    single = None 
    pause = None 
    shadow = None 
    fnums = None 
    bnums =None 
    hold =None 
    prevhold = None 
    prev_time =None 
    fstart = None 
    fstop = None 
    pstart =None 
    pend = None 
    f_max = None 
    vstart =None 
    vstop =None 
    inmain = None 
    start = None 
    lline =None 
    fast =None 
    slow = None 
    fslow =None 
    njts = None 
    nvars =None 
    nfiles =None 
    nvals = None
    df = None
    f = None
    val = [0]*Define.VMAX
    axlen = [0]*Define.EMAX 
    keylen = [0]*Define.NKEYS
    ellen =jntlen=figlen=fillen=knee=figell=ellfig= [0]*Define.EMAX
    sublen=varlen=usevar=called=defined = [0]*Define.PMAX
    coel = [[0]*2]*Define.EMAX
    subact = [[0]*2]*Define.PMAX
    cen = [[0]*3]*Define.EMAX
    ax = [[0]*3]*Define.EMAX
    lim = [[[0]*2]*3]*Define.EMAX
    obs = [[0]*3]*3

    col = [[0]*3]*Define.EMAX
    quat = [[0]*5]*(Define.EMAX+2)
    tname = jname = sname = vname = axnam = ename = fname = [[0]*Define.BMAX]*Define.EMAX 
    typo = frstart = frstop = cline = distrn = [0]*Define.PMAX
    pf = [[0]*6]*Define.PMAX

    nsubs = ne = nfigs = None
    figell = [0]*Define.EMAX
    stop_keyword_code = 16
    dummy = "dummy"
    every = "every"
    nudes = "nudes"
    world = "world"
    variab = "variab"
