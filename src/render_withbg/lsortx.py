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

