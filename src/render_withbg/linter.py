from lbn_read import lbn_read
from lfindstaff import lfindstaff
from lsetrange import lsetrange
from lselectfig import lselectfig
from lcopyfig import lcopyfig
from lbows import lbows
from lfindystart import lfindystart
from lbent import lbent
from lcolx import lcolx
#from laction import laction
#from lfinish import lfinish


def linter(GV,renderFile,gender):
    lbn_read(GV)
    lfindstaff(GV,gender)
    lsetrange(GV)
    lselectfig(GV)
    lcopyfig(GV,renderFile)
    lfindystart(GV)
    lbows(GV)
    lbent(GV)
    for GV.currentStaffNumber in range(GV.numberOfStaff): 
        GV.hold = GV.NO
        GV.closeHoldCounter = 0
        GV.openHoldCounter = 0
        GV.openExtendedHoldCounter = 0
        GV.promenadeHoldCounter = 0
        GV.shadowHoldCounter = 0
        GV.semiShadowHoldCounter = 0
        GV.closeFaceScore = 0
        GV.promenadeFaceScore = 0
        GV.shadowFaceScore = 0
        GV.semiShadowFaceScore = 0
        GV.prevhold = -9
        GV.col_prev = 0
        GV.firstFramePrevAct = -1
        GV.lastFramePrevAct = -1
        GV.keptLastFrame = 0

        if GV.staff[GV.currentStaffNumber][5] == GV.TODO:
            GV.num_curBar = -1
            if GV.staff[GV.currentStaffNumber][4] == GV.MAN:
                GV.dofig = GV.MAN
            else:
                GV.dofig = GV.WOMAN
            lcolx(GV,GV.staff[GV.currentStaffNumber][2])
  #          laction(GV)
  #          GV.staff[GV.currentStaffNumber][5] = GV.DONE
  #  #lfinish(GV)
