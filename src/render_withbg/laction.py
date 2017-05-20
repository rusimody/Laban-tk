def laction(GV):
    (GV.nudesfile).seek(2)
    (GV.nudesfile).write("*\n***************barakadabra*********************\n")
    GV.oriented = False
    if GV.dofig == GV.MAN:
        (GV.nudesfile).write("*\nrepeat      0 %3d call   doman\n"% GV.max_Numframe)
    else:
        (GV.nudesfile).write("*\nrepeat      0 %3d call   dowoman\n"%max_Numframe)
    for GV.symbolCounter in range(GV.NCOLM):
        
