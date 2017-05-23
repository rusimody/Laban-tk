def lsetrange(GV):
    GV.ystart = 0
    GV.yend = GV.listLbnObject[0].Ypos
    yMax = GV.yend
    GV.startScoreSymbol = 0
    GV.endScoreSymbol = GV.Num_Lab_Entries


    for i in range(GV.Num_Lab_Entries):
        if GV.listLbnObject[i].Name == 'Bars':
            if GV.listLbnObject[i].Item == 0:
                GV.startScoreSymbol = i
                GV.ystart = GV.listLbnObject[i].Ypos

    for i in range(GV.Num_Lab_Entries):
        if GV.listLbnObject[i].Name == 'Dirn':
            if GV.listLbnObject[i].Ypos > GV.yend:
                GV.yend = GV.listLbnObject[i].Ypos
            if GV.listLbnObject[i].Ypos + GV.listLbnObject[i].Height > yMax:
                yMax = GV.listLbnObject[i].Ypos + GV.listLbnObject[i].Height
                kMax = i
    GV.max_Numframe = 2 + (int ( 2 + GV.lbn_fpp*yMax))
    print(GV.ystart,GV.yend,GV.startScoreSymbol,GV.endScoreSymbol)
    print("\n lsetrange: pixels %d, frames %d\n"%(yMax,GV.max_Numframe))
