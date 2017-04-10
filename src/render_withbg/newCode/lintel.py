import argparse
import variable
import math

def initialise(GlobalVariable,Define):
    GlobalVariable.barNumber = -1 #number of current bar
    GlobalVariable.rise = 1 # used in  3 functions
    GlobalVariable.prevc = 0 # used in 3 functions
    GlobalVariable.previ = 11 # used in 2 functions
    GlobalVariable.track = True # used in 2 functions
    GlobalVariable.mspace = False # used in  3 functions
    GlobalVariable.wspace = False # used in  3 functions
    GlobalVariable.doub0 = 0
    GlobalVariable.doub1 = 1
    GlobalVariable.doub2 = 2
    GlobalVariable.doub3 = 3 
    GlobalVariable.doub4 = 4
    GlobalVariable.doub10 = 10
    GlobalVariable.doub60 = 60
    GlobalVariable.doub90 = 90
    GlobalVariable.doub150 =150
    GlobalVariable.doub179 = 179
    GlobalVariable.doub180 = 180
    GlobalVariable.doub181 = 181
    GlobalVariable.doub255 = 255
    GlobalVariable.doub360 = 360
    GlobalVariable.doub500 = 500
    GlobalVariable.inv2 = GlobalVariable.doub1/GlobalVariable.doub2 #used in aprox all functions
    GlobalVariable.inv3 = GlobalVariable.doub1/GlobalVariable.doub3 #used in 2 functions only
    GlobalVariable.inv4 = GlobalVariable.doub1/GlobalVariable.doub4 #used in 1 function
    GlobalVariable.inv5 = GlobalVariable.doub1/5 #used in 2 functions
    GlobalVariable.inv6 = GlobalVariable.doub1/6 #used in 2 functions
    GlobalVariable.inv10 = GlobalVariable.doub1/GlobalVariable.doub10 #used in 3 functions
    GlobalVariable.inv256 = GlobalVariable.doub1/256 #used in 2 functions 
    GlobalVariable.inv1000 = GlobalVariable.doub1/1000 #used in 3 functions
    GlobalVariable.rt3 = math.sqrt(GlobalVariable.doub3) #used in one functions
    GlobalVariable.piby2 = GlobalVariable.doub2*math.atan(GlobalVariable.doub1) #used in 2 functions
    GlobalVariable.pi = GlobalVariable.piby2*2 #used in 2 functions 
    GlobalVariable.twopi = GlobalVariable.pi*2 #used in 3 functions
    GlobalVariable.radten = GlobalVariable.twopi/3600 #used in one functions
    GlobalVariable.radian = GlobalVariable.twopi/GlobalVariable.doub360 #used in 3 functions
    GlobalVariable.degree = GlobalVariable.doub1/GlobalVariable.radian #used in 3 functions
    GlobalVariable.lg2 = math.log(GlobalVariable.doub2) #used in 2 functions
    GlobalVariable.freeze = False  #used in 2 functions
    GlobalVariable.forward = True #in 2 functions
    GlobalVariable.single = Define.DONE #in 2
    GlobalVariable.pause = False # in 2
    GlobalVariable.shadow = True # in 2
    GlobalVariable.fnums = True # in 3
    GlobalVariable.bnums = True # in 3
    GlobalVariable.hold = Define.NO
    GlobalVariable.prevhold = -99 #in 5
    GlobalVariable.prev_time = -1 # in 1
    GlobalVariable.fstart = 0 # in 8
    GlobalVariable.fstop = 0 # in 4
    GlobalVariable.pstart = 0 # in 5
    GlobalVariable.pend = 0 # in 6
    GlobalVariable.f_max = 0 # in 5
    GlobalVariable.vstart = 0 # in 3
    GlobalVariable.vstop = Define.FMAX # in 3
    GlobalVariable.inmain = True # in 3
    GlobalVariable.start = -1 # in 4
    GlobalVariable.lline = 0 # in 2
    GlobalVariable.fast = 1 # in 3
    GlobalVariable.slow = 1 # in 3
    GlobalVariable.fslow = 1 # in 2
    GlobalVariable.njts = 0 # more then 6
    GlobalVariable.nvars = 0 # in 4
    GlobalVariable.nfiles = 0 # in 3
    GlobalVariable.nvals = 0 # in 3
    GlobalVariable.axlen[0]=1 # in 2
    GlobalVariable.axlen[1]=1 # in 2
    GlobalVariable.axlen[2]=1 # in 2

    for j in range(0,Define.EMAX):
        if ( j > 2 ):
            GlobalVariable.axlen[j] = -1
        GlobalVariable.keylen[j] = 0
        GlobalVariable.ellen[j] = -1
        GlobalVariable.jntlen[j] = -1
        GlobalVariable.fillen[j] = -1
        GlobalVariable.figlen[j] = -1
        GlobalVariable.sublen[j] = -1
        GlobalVariable.varlen[j] = -1
        GlobalVariable.knee[j] = 0 
        GlobalVariable.figell[j] = 0
        GlobalVariable.ellfig[j] = 0
        GlobalVariable.usevar[j] = 0
        GlobalVariable.coel[j][0] = -1
        GlobalVariable.coel[j][1] = -1
        GlobalVariable.subact[j][0] = 0
        GlobalVariable.subact[j][1] = 0
        GlobalVariable.called[j] = False
        GlobalVariable.defined[j] = False
        GlobalVariable.val[j] = GlobalVariable.doub0 
        
        for k in range(3):
            GlobalVariable.cen[j][k] = GlobalVariable.doub3
            GlobalVariable.ax[j][k] = GlobalVariable.doub2
            GlobalVariable.lim[j][k][0]= -GlobalVariable.doub360
            GlobalVariable.lim[j][k][1]=GlobalVariable.doub360
            GlobalVariable.obs[k][0] = GlobalVariable.doub0
            GlobalVariable.obs[k][1] = GlobalVariable.doub0
            GlobalVariable.obs[k][2] = GlobalVariable.doub0
            GlobalVariable.obs[k][k] = GlobalVariable.doub1
        
        GlobalVariable.col[j][0]=GlobalVariable.doub255
        GlobalVariable.col[j][1]=GlobalVariable.doub150
        GlobalVariable.col[j][2]=GlobalVariable.doub90
        GlobalVariable.quat[j][0]=GlobalVariable.doub1
        GlobalVariable.quat[j][1]=GlobalVariable.doub0
        GlobalVariable.quat[j][2]=GlobalVariable.doub0
        GlobalVariable.quat[j][3]=GlobalVariable.doub0
        GlobalVariable.quat[j][4]=GlobalVariable.doub1

        for k in range(Define.BMAX):
            GlobalVariable.axnam[j][k] = None
            GlobalVariable.tname[j][k] = None
            GlobalVariable.fname[j][k] = None
            GlobalVariable.ename[j][k] = None
            GlobalVariable.jname[j][k] = None
            GlobalVariable.vname[j][k] = None
            GlobalVariable.sname[j][k] = None
    
    GlobalVariable.axnam[0][0] = 'x'
    GlobalVariable.axnam[1][0] = 'y'
    GlobalVariable.axnam[2][0] = 'z'

    for j in range(Define.PMAX):
        GlobalVariable.typo[j] = GlobalVariable.stop_keyword_code
        GlobalVariable.frstart[j] = 0
        GlobalVariable.frstop[j] = 0
        GlobalVariable.distrn[j] = 0
        GlobalVariable.cline[j] = 0
        for k in range(6):
            GlobalVariable.pf[j][k]=0

    GlobalVariable.nsubs = 1
    GlobalVariable.nfigs = 2
    GlobalVariable.ne = 1
    GlobalVariable.figell[0]=0
    GlobalVariable.figell[1]=1

    GlobalVariable.tname = GlobalVariable.dummy
    GlobalVariable.sname = GlobalVariable.nudes
    GlobalVariable.fname = GlobalVariable.every
    GlobalVariable.fname = GlobalVariable.world
    GlobalVariable.ename = GlobalVariable.world
    GlobalVariable.vname = GlobalVariable.variab

    GlobalVariable.fillen[0] = 5
    GlobalVariable.sublen[0] = 5
    GlobalVariable.figlen[0] = 5
    GlobalVariable.figlen[1] = 5
    GlobalVariable.ellen[0] = 5
    GlobalVariable.varlen[0] = 6
    GlobalVariable.ax[0][0] = GlobalVariable.doub1
    GlobalVariable.ax[0][1] = GlobalVariable.doub1
    GlobalVariable.ax[0][2] = GlobalVariable.doub1

    GlobalVariable.df = 1
    GlobalVariable.f = 0
    GlobalVariable.nsph = Define.SSTART
    GlobalVariable.anglex = GlobalVariable.angley = GlobalVariable.anglex = GlobalVariable.doub0
    GlobalVariable.tx = GlobalVariable.ty = GlobalVariable.tz = GlobalVariable.doub0
    GlobalVariable.scale = GlobalVariable.doub1
    GlobalVariable.alpha = GlobalVariable.doub3
    GlobalVariable.t = 0
    GlobalVariable.more = 1
    GlobalVariable.ok = 0

    
    b = GlobalVariable.doub1
    m = 0
    a = GlobalVariable.inv2
    
    while(GlobalVariable.doub1 + b > GlobalVariable.doub1+a):
        b = a
        m += 1
        a *= GlobalVariable.inv2
    
    GlobalVariable.tolr = b+b
    j = 2
    n = 0
    k = 1
   # while(k<j):
   #     print("###")
   #     k +=k
   #     n +=1
   #     j +=j
    GlobalVariable.maxint = k
    print("\n tolr " + str(GlobalVariable.tolr) + "(" + str(m)+" bits), maxint "+str(GlobalVariable.maxint)+" ("+str(n)+"bits)\n" )

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-l',dest='lbn',help=".lbn file required",required=True)
    parser.add_argument('-r',dest='render',help="render flag required <r>",required=True)
    parser.add_argument('-s',dest='figure',help="figure flag required <m or f>",required=True)
    args = parser.parse_args() 
    print("    running",variable.GlobalVariable.programTitle) 
    initialise(variable.GlobalVariable,variable.Define)

if __name__=="__main__":
    main()


