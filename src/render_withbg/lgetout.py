def lgetout(GV,allok):
    if allok == 0:
        print("%s created OK"%GV.nudesname)
        if GV.infile:
            GV.infile.close()
        if GV.nudesfile:
            GV.nudesfile.close()
        if GV.figsfile:
            GV.figsfile.close()
    else:
        print("lintel snag, line %d"%GV.symbolCounter)
        #print(GV.lbnline[symbolCounter])
        GV.ok=1
    return

