from loverlap import loverlap

def lbent(GV):
    for GV.symbolCounter in range(GV.endScoreSymbol):
        if GV.listLbnObject[GV.symbolCounter].Name == 'Volm' and GV.listLbnObject[GV.symbolCounter].Item <=GV.STRETCH:
            lassign()
            currentY2Height = GV.currentY2+GV.currentHeight
            directionSymbolIndex = -1
            k = GV.symbolCounter+1
            while (k<GV.Num_Lab_Entries and directionSymbolIndex < 0):
                k +=1
                tempMenuName = GV.listLbnObject[k].Name
                if tempMenuName == 'Dirn' and GV.listLbnObject[k].a == GV.TODO:
                    tempYpos = GV.listLbnObject[k].Ypos
                    if tempYpos > currentY2Height:
                        directionSymbolIndex = 0
                    else:
                        tempY2 = GV.listLbnObject[k].Y2
                        tempXpos = GV.listLbnObject[k].Xpos
                        tempX2 = GV.listLbnObject[k].X2
                        if loverlap(GV,currentXpos,currentX2,tempXpos,tempX2) and loverlap(currentY2,currentY2Height,tempYpos,tempY2) > 0:
                            directionSymbolIndex = k
                            tempItem = GV.listLbnObject[k].Item
                            GV.listLbnObject[symbolCounter].Item = tempItem
                            GV.listLbnObject[symbolCounter].Y2 = tempY2
                            GV.listLbnObject[symbolCounter].Height = GV.listLbnObject[k] - currentYpos
                            GV.listLbnObject[symbolCounter].Level = GV.listLbnObject[k].Level
                            GV.listLbnObject[symbolCounter].a = GV.DONE
