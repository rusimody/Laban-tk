from lgetout import lgetout

def lfindystart(GV):
    #for i in range(GV.Num_Lab_Entries):
    #    print(GV.listLbnObject[i].Name,GV.listLbnObject[i].Item,GV.listLbnObject[i].Xpos,GV.listLbnObject[i].Ypos,GV.listLbnObject[i].StepSize,GV.listLbnObject[i].Width,GV.listLbnObject[i].Height,GV.listLbnObject[i].Level,GV.listLbnObject[i].a,GV.listLbnObject[i].x2,GV.listLbnObject[i].y2)

    GV.ystart = -1
    j = 0
    while(GV.Num_Lab_Entries > j and GV.ystart<0):
        j +=1
        print(GV.listLbnObject[j].Name,GV.listLbnObject[j].Level)
        if GV.listLbnObject[j].Name == 'Bars' and GV.listLbnObject[j].Level == 'L':
            GV.ystart = GV.listLbnObject[j].Ypos +1
            print(GV.listLbnObject[j].Ypos)

    if GV.ystart<0:
        j = 0
        while (GV.Num_Lab_Entries > j and GV.ystart<0):
            j +=1
            if GV.listLbnObject[j].Name == 'Bars':
                GV.ystart = GV.listLbnObject[j].Ypos+1
    
   # if GV.ystart<0:
   #     j = 0
   #     while(GV.Num_Lab_Entries > j and GV.ystart<0):
   #         if GV.listLbnObject[j].Name=='Dirn' and (GV.listLbnObject[j].c == 1 or GV.listLbnObject[j].c==-1):
   #             GV.ystart = GV.listLbnObject[j].Ypos

    GV.ystart -=3
    if GV.ystart < 0:
        print("linter : findystart finds no direction support symbols")
        lgetout(GV,1)
        GV.ystart = 0
