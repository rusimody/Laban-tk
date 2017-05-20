from lgetout import lgetout

def loverlap(GV,p1j,p2j,p1k,p2k):
    if p1j > p2j or pik > p2k:
        print("OOPS: loverlap %d %d %d %d"%(p1j,p2j,p1k,p2k))
        lgetout(GV.symbolCounter)
    lap = False
    if p1k<p1j:
        p1max = p1j
    else:
        p1max = p1k
    if p2k < p2j:
        p2min = p2k
    else:
        p2min = p2j
    lap = p2min - p1max
    return lap
