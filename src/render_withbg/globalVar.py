import sys
from initialise import initialise
from get_ini import get_ini
from led_param import led_param
from get_files import get_files
from lbn_read import lbn_read
from lfindstaff import lfindstaff

class GlobalVar():
    def __init__(self):
        self.EMAX = 1024   #Maximum No.of ellipsoid  (const)
        self.NKEYS = 64    #Number of kkeywords (const)
        self.PMAX = 6000   #maximum number of actions to perform
        self.BMAX = 256    #size of character buffer
        self.init_num_chord_sphere = 20  # initial number of chords around sphere
        self.VMAX = 2048   # max number of constants + variables
        self.FMAX = 2048   # maximum number of frames
        self.TMAX = 30 # max number of staff line
        self.MAN = 0
        self.WOMAN = 1

        self.NO = 0
        self.CL = 1
        self.PR = 2
        self.CP = 3
        self.DB = 4
        self.OP = 5
        self.CR = 6
        self.OE = 7
        self.CO = 8
        self.SH = 9

        self.DONE = 0
        self.TODO = 1
        self.TRUE = 0
        self.FALSE = 1
        


        self.doub0 = float(0)
        self.doub1 = float(1)
        self.doub2 = float(2)
        self.doub3 = float(3)
        self.doub4 = float(4)
        self.doub10 = float(10)
        self.doub60 = float(60)
        self.doub90 = float(90)
        self.doub150 = float(150)
        self.doub179 = float(179)
        self.doub180 = float(180)
        self.doub181 = float(181)
        self.doub255 = float(255)
        self.doub360 = float(360)
        self.doub500 = float(500)


        self.inv2 = float(1) / float(2)   
        self.inv3 = float(1) / float(3)   
        self.inv4 = float(1) / float(4)   
        self.inv5 = float(1) / float(5)   
        self.inv6 = float(1) / float(6)   
        self.inv10 = float(1) / float(10)   
        self.inv256 = float(1) / float(256)   
        self.inv1000 = float(1) / float(1000)   


 
        self.keywordCode = range(1,64)
        self.frameInc = 0 
        self.scaleFactor = 0
        self.angleInc = 0
        self.typeCurAction = 0
        self.more = 0
        self.ok =  0		  #ok = 0 if ok, else problem reference number
        self.frameCount = 0
        self.num_chord_sphere = 0    # number of chords around sphere
        self.num_subroutine = 0
        self.num_figure = 0
        self.num_ellip_curFrame = 0
        self.num_var = 0
        self.num_file = 0
        self.num_val = 0
        self.printDone = 1        # (FALSE = 1)TRUE if diagnostic printing already done
        self.num_curBar = -1      # number of current bar
        self.height_prev = 1      # height of previous step;
        self.col_prev = 0         # column of previous support symbol
        self.item_prev = 11       # item of previous support symbol
        self.trackOnMainFig = 0   # TRUE when tracking viewpoint on main figure

        self.start = -1
        self.lenNextInpLine = 0;
        self.frameNumMultiplier = 1;
        self.num_pauseCalls = 1;
        self.fslow = 1;
        self.num_joint = 0;

        self.hold = 0                # one of the defined holds NO,CL,PR,CP,DB,OP,CR,OE,CO,SH,SS
        self.prevhold = -99          # previous hold 
        self.prevFrame_time = -1     # clock reading of previous frame
        self.firstFrameNumAct = 0    # first frame number of action
        self.lastFrameNumAct = 0     # last frame number of actions
        self.firstFramePrevAct = 0   # first frame of previous action
        self.lastFramePrevAct = 0    # last frame of previous action
        self.max_Numframe = 0        # maximum frame number
        self.view_firstframe = 0     # first frame from view command
        self.view_lastframe = self.FMAX   # last frame from view command
        self.nudes_inMain = 0        # TRUE if still in main NUDES program

        self.forPause = self.FALSE
        self.shadowDisplay = self.TRUE
        self.frameNumDisplay = self.TRUE
        self.barNumDisplay = self.TRUE

        self.freezeAnimation =   1 #self.FALSE
        self.forward = self.TRUE
        self.single = self.DONE

        self.anglex = self.angley = self.anglez = self.tx = self.ty = self.tz = 0
 
        # 1D arrays in c
        self.axlen = self.frstart = self.frstop = self.distrn = self.cline =  self.keylen = self.ellen = self.jntlen = self.fillen = self.figlen = self.sublen = self.varlen = self.knee = self.figell = self.ellfig = self.usevar = []
 
        # 0,1 list for true,false
        self.called = [] #true if subroutine is called
        self.defined = [] #true if subroutine is defined 
 
        # 2D arrays in c
        self.coel = self.subact = []

        #rotation matrix applied to all ellipsoids to obtain observers view
        self.obs = []

        #cen[i][j] - jth coordinate of centre of ith ellipsoid
        self.cen = [] 

        #ax[i][j] - length of jth semiaxis of ith ellipsoid
        self.ax = []

        # color[i][j] - colour of ell i; j = 0 red, 1 green, 2 blue
        self.color = []

 
        # quat[i][j] - angle of ith ellipsoid
        #j = 0,1,2 - components of direction of rotation axis
        #j = 3,4   - sine and cosine of rotation about axis
        self.quat = [] 

        self.axisname = [] #first entry is the set of axis names 'x','y','z'.
        self.textMapFileName = [] # name of texture map file

        self.figureName = [] # figure name
        self.ename = []  # ellipsoid name
        self.jname = []  # joint names
        self.vname = []  # variable names
        self.sname = []  # subroutine names
                    
        self.typeAction = []
        self.pf = []
        
        self.val=[] # val[i] - if i <= num_val then value of ith constant
                    #         otherwise (s - i+1)th variable
        self.mspace = False
        self.wspace = self.FALSE

        self.ini_title =  [] #[['0']*32]*256
        self.ini_value =  []  #[['0']*128]*256
        self.numberOfParameterInIni = -1  #-1 if lintel.ini file not found else equals to number of parameters in lintel.ini file
        self.bufferList = []
        self.lbn_fps = -1 
        self.lbn_bpm = -1
        self.lbn_ppb = 23
        self.lbn_figures =1
        self.lbn_fpp = None

        self.input_file_type = -1 #tells us type of file .n or .lbn by its value 0 and 1
        self.name = ""
        self.haslbn = self.FALSE
        self.nudesname = ""
        self.finname = ""
        self.nudesfile = None #pointing to nude file
        self.infile = None #


        self.Num_Lab_Entries = 0
        self.listLbnObject = []
        self.xmin = 0

        ##########################
        self.symbolCounter = None
        self.stmiddle = None
        self.npins = None
        self.pins = [None,None]*self.TMAX
        self.staff =[[None]*6]*self.TMAX #[TMAX][6]
       


GV = GlobalVar()

#command line arguments are taken through tempFilename file
with open("tempFilename.txt", 'r') as f:
    data = f.read()
array = [x for x in data.split()]
argFilename = array[0]
arg1 = array[1]
arg2 = array[2]

initialise(GV)
get_ini(GV,0)
led_param(GV)
get_files(GV,argFilename)
lbn_read(GV)                        # lsorty, lbnread
lfindstaff(GV,arg2)
print("oooo")



