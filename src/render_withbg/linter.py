from lbn_read import lbn_read
from lfindstaff import lfindstaff
from lsetrange import lsetrange
from lselectfig import lselectfig
from lcopyfig import lcopyfig
from lbows import lbows

def linter(GV,renderFile,gender):
    lbn_read(GV)
    lfindstaff(GV,gender)
    lsetrange(GV)
    lselectfig(GV)
    lcopyfig(GV,renderFile)
    lbows(GV)
