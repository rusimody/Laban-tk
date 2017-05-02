def lselectfig(GV):
    stv = [0,0]
    while(True):
        for k in range(GV.numberOfStaff):
            GV.staff[k][5] = GV.DONE
        numberOfFigure = 0
        GV.numberOfMen = 0 # male fig count
        GV.numberOfWomen = 0 # female fig count
        nogo = False
        if GV.numberOfStaff<1:
            print("No staves")
        else:
            if GV.numberOfStaff==1:
                GV.staff[0][5] = GV.TODO
                if GV.staff[0][4]==GV.MAN:
                    GV.numberOfMen +=1
                else:
                    GV.numberOfWomen +=1
            else:
                if GV.numberOfStaff>1:
                    GV.numberMenWomen = 0
                    if GV.numberOfStaff > GV.TMAX:
                        print("This can only interpret staves from 1 to %d"%GV.TMAX)
                    if GV.lbn_figures ==2:
                        stv[0] = 1
                        stv[1] = 2
                        GV.trackOnMainFig = True
                    else:
                        print("Please type the numbet of staves to be interpreted")
                        GV.lbn_figures = int(input())
                        if GV.lbn_figures >2:
                            print("Sorry: this program can only interpret 2 staves at a time")
                            nogo = True
                            continue
                        if GV.lbn_figures==1:
                            print("Please enter the staff number to be interprted")
                        else:
                             print("Please enter staff numbers to be interpreted")
                             print("separated by a space, and followed by the 'enter' key.")
                        if GV.lbn_figures == 1:
                            stv0 = int(input())
                            stv[0] = stv0
                            stv[1] = -1
                        else:
                            stv0,stv1 = map(int,input().split())
                            stv[0] = stv0
                            stv[1] = stv1
                    for GV.numberOfFigure in range(GV.lbn_figures):
                        st = stv[GV.numberOfFigure]-1
                        if st<0 or st > gv.numberOfStaff:
                            print("OOPS: staff number %s out of range"%st+1)
                            continue
                        st4 = GV.staff[st][4]
                        if (GV.numberOfMen>0 and st4 == GV.MEN) or (GV.numberOfWomen>0 and st4 == GV.WOMEN):
                            print("Sorry: can only do one men and/or one women.")
                            print("Please select again")
                            nogo = True
                        else:
                            if st4 == GV.WOMEN:
                                GV.numberOfWomen +=1
                            if st4 == GV.MEN:
                                GV.numberOfMen +=1
                            GV.staff[st][5] = GV.TODO
                        GV.numberMenWomen = GV.numberOfMen*GV.numberOfWomen
        if nogo==True:
            continue
        else:
            break

    if GV.lbn_figures !=2:
        GV.trackOnMainFig = True
        print("Track main figure? Hit 'Enter' for Yes,any ither key for no")
        key = raw_input()
        if key == '\n':
            GV.trackOnMainFig = False
        else:
            GV.trackOnMainFig = True #follows the figure while dance
        if GV.trackOnMainFig ==False:
            print("     Tacking OFF")
        else:
            print("     Tracknig ON")
