class GlobalVariable:
    """ This Class is use to hold all global variables """
    programTitle="lintel084"
    #def __init__(self):

        

def initialise():
    barNumber = -1 #number of current bar
    rise = 1 # used in  3 functions
    prevc = 0 # used in 3 functions
    previ = 11 # used in 2 functions
    track = TRUE # used in 2 functions
    mspace = false # used in  3 functions
    wspace = FALSE # used in  3 functions
    doub0 = 0
    doub1 = 1
    doub2 = 2
    doub3 = 3 
    doub4 = 4
    doub10 = 10
    doub60 = 60
    doub90 = 90
    doub150 =150
    doub179 = 179
    doub180 = 180
    doub181 = 181
    doub255 = 255
    doub360 = 360
    doub500 = 500
    inv2 = doub1/doub2 #used in aprox all functions
    inv3 = doub1/doub3 #used in 2 functions only
    inv4 = doub1/doub4 #used in 1 function
    inv5 = doub1/5 #used in 2 functions
    inv6 = doub1/6 #used in 2 functions
    inv10 = doub1/doub10 #used in 3 functions
    inv256 = doub1/256 #used in 2 functions 
    inv1000 = doub1/1000 #used in 3 functions
    rt3 = sqrt(doub3) #used in one functions
    piby2 = doub2*atan(doub1) #used in 2 functions
    pi = piby2+piby2 #used in 2 functions 
    twopi = pi+pi #used in 3 functions
    radten = twopi/3600 #used in one functions
    radian = twopi/doub360 #used in 3 functions
    degree = doub1/radian #used in 3 functions
    lg2 = log(doub2) #used in 2 functions
    freeze = FALSE  #used in 2 functions
    forward = TRUE #in 2 functions
    single = DONE #in 2
    pause = FALSE # in 2
    shadow = TRUE # in 2
    fnums = TRUE # in 3
    bnums = TRUE # in 3
    hold = NO
    prevhold = -99 #in 5
    prev_time = -1 # in 1
    fstart = 0 # in 8
    fstop = 0 # in 4
    pstart = 0 # in 5
    pend = 0 # in 6
    f_max = 0 # in 5
    vstart = 0 # in 3
    vstop = FMAX # in 3
    inmain = TRUE # in 3
    start = -1 # in 4
    lline = 0 # in 2
    fast = 1 # in 3
    slow = 1 # in 3
    fslow = 1 # in 2
    njts = 0 # more then 6
    nvars = 0 # in 4
    nfiles = 0 # in 3
    nvals = 0 # in 3
    axlen[0] = 1 # in 2
    axlen[1] = 1 # in 2
    axlen[2] = 1 # in 2

def main():
    print("    running",GlobalVariable.programTitle)
   # initialise()

if __name__=="__main__":
    main()
