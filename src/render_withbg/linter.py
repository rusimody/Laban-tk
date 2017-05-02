from lbn_read import lbn_read
from lfindstaff import lfindstaff
from lsetrange import lsetrange
from lselectfig import lselectfig
def linter(GV,renderFile,gender):
    lbn_read(GV)
    lfindstaff(GV,gender)
    lsetrange(GV)
    lselectfig(GV)
