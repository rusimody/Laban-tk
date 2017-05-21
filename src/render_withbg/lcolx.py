def lcolx(GV,lcentre):
    for k in range(GV.Num_Lab_Entries):
        kwx = GV.listLbnObject[k].Xpos + GV.listLbnObject[k].Width/2
        kc = (kwx - lcentre)/GV.STEP
        if kwx < lcentre :
            kc -=1
        else:
            kc +=1
      #  GV.listLbnObject[k].c = kc
