from lbn_read import lbn_read
from lfindstaff import lfindstaff
from lsetrange import lsetrange
from lselectfig import lselectfig
from lcopyfig import lcopyfig
from lfindystart import lfindystart
from lbent import lbent

def linter(GV,renderFile,gender):
    lbn_read(GV)
    lfindstaff(GV,gender)
    lsetrange(GV)
    lselectfig(GV)
    #lcopyfig(GV,renderFile)
    lfindystart(GV)
    #lbows(GV)
    lbent(GV)
