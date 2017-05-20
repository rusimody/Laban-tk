import sys
from lgetout import lgetout

def lcopyfig(GV,renderFile):
    if renderFile == 'r':
        GV.figsname = "lintel.n"
    elif renderFile == 'n':
        GV.figsname = "lintelnudes.n"
    else:
        print("Enter the valid option, r for render, n for nudes")
        sys.exit(0)
    try:
        print ("figsname" , GV.figsname)
        GV.figsfile = open(GV.figsname,"r")
    except (OSError,IOError) as err:
        print("oops %s not in folder: %s"%(GV.figsname,err))
        lgetout(GV,1)
        if GV.ok==1:
            return
   
    
    for line in GV.figsfile:
        (GV.nudesfile).write(line)
