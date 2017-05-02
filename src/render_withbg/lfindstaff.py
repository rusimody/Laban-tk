from lgetout import lgetout

def lsortx(localStaff,nstaff):
    for j in range(nstaff-1):
        for k in range(j,nstaff):
            if localStaff[k][1]<localStaff[j][1]:
                s0 = localStaff[j][0]
                s1 = localStaff[j][1]
                localStaff[j][0] = localStaff[k][0]
                localStaff[j][1] = localStaff[k][1]
                localStaff[k][0] = s0
                localStaff[k][1] = s1
    return localStaff

def loverlap(p1j,p2j,p1k,p2k):
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

def lfindstaff(GV,gender):
    localStaff = [[0,0] for i in range(GV.TMAX)] # temporary list to store staff information
    counter = 0
    staffStart = 0 # y coordinate of midle stav
    nstaffstart = 0 # index of staves
    nstaff = 0 # number of staves

    for i in range(GV.Num_Lab_Entries):       
        if GV.listLbnObject[i].Name == 'Stav':
            localStaff[counter][0]=i
            localStaff[counter][1]=GV.listLbnObject[i].Xpos
            if GV.listLbnObject[i].Ypos > staffStart:
                staffStart = GV.listLbnObject[i].Ypos
            nstaffstart = i
            counter +=1
            GV.listLbnObject[i].a = GV.DONE
    
    if counter > 3:
        print("lfindstaff: only %d staff lines\n"%counter)
        lgetout(1)
        if GV.ok==1:
            return

    if counter > GV.TMAX:
        print("lfindstaff: %d staff lines, max %d"%(counter,GV.TMAX))
        lgetout(GV,1)
        if GV.ok == 1:
            return
    
    nstaff = counter
    lsortx(localStaff,nstaff)
    counter = 0
    for i in range(1,nstaff,3): # need for look
        GV.staff[counter][0]=localStaff[i][0] 
        GV.staff[counter][1]=localStaff[i-1][1]
        GV.staff[counter][2]=localStaff[i][1]
        GV.staff[counter][3]=localStaff[i+1][1]
        GV.staff[counter][4]=-1
        GV.staff[counter][5]=GV.TODO
        counter +=1
    
    GV.numberOfStaff = counter
    GV.stmiddle = (GV.staff[0][2]+GV.staff[GV.numberOfStaff-1][2])/2
    GV.npins = 0

    for j in range (nstaffstart):
        print(nstaffstart)
        print(GV.listLbnObject[j].Name)
        if GV.listLbnObject[j].Name=='Pins':#need for look
            jp = GV.listLbnObject[j].Xpos
            jq = GV.listLbnObject[j].x2
            GV.pins[GV.npins][0] = j
            GV.pins[GV.npins][1] = -1
            for k in range(GV.numberOfStaff):
                kp = GV.staff[k][2]-1
                kq = kp+2
                if loverlap(jp,jq,kp,kq)>0:
                    if GV.listLbnObject[j].Level == "B": # d is not defines
                        print(GV.listLbnObject[j].Level)
                    if GV.listLbnObject[j].Level == 0: # d is not defines
                        localStaff[counter][4] = GV.MAN
                        GV.pins[GV.npins][1] = counter
                        GV.listLbnObject[j].a = GV.DONE
                    else:
                        localStaff[counter][4] = GV.WOMAN
                        GV.pins[GV.npins][1] = counter
                        GV.listLbnObject[j].a = GV.DONE
            GV.npins +=1

    if GV.numberOfStaff < 1:
        print("No staves found")
    else:
        for j in range(GV.numberOfStaff):
            if gender!=None:
                if GV.numberOfStaff ==1:
                    if gender == 'm':
                        GV.staff[j][4] = GV.MAN
                        print(GV.staff[j][4])
                    elif gender == 'f':
                        GV.staff[j][4] = GV.WOMAN
                elif j == 0:
                    GV.staff[j][4] = GV.MAN
                elif j ==1:
                    GV.staff[j][4] = GV.WOMAN
