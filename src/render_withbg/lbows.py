from lfindstaff import loverlap

def lbows(GV):
    centre = (GV.staff[0][2] + GV.staff[1][2])/2
    Step = 12
    for GV.symbolCounter in range(0,GV.Num_Lab_Entries):
       if (((GV.listLbnObject[GV.symbolCounter]).Name == "Misc") and ((GV.listLbnObject[GV.symbolCounter]).Item) == 1 ):
        lbnElement = GV.listLbnObject[GV.symbolCounter]
        held = lseeksym("Volm",1,lbnElement.Xpos , lbnElement.x2 ,lbnElement.Ypos - Step, lbnElement.y2,Step,GV)
        if (held > 0):
          mlhand = lseeksym("Limb",4,lbnElement.Xpos-Step/2,lbnElement.Xpos+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
          mrhand = lseeksym("Limb",9,lbnElement.Xpos-Step/2,lbnElement.Xpos+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
          wlhand = lseeksym("Limb",4,lbnElement.x2-Step/2,lbnElement.x2+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
          wrhand = lseeksym("Limb",9,lbnElement.x2-Step/2,lbnElement.x2+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
          front  = lseeksym("Area",1,lbnElement.Xpos-Step/2,lbnElement.Xpos+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
          if (front < 0):
              front  = lseeksym("Area",1,lbnElement.x2-Step/2,lbnElement.x2+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
          if (front < 0):
              front  = lseeksym("Area",2,lbnElement.Xpos-Step/2,lbnElement.Xpos+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
          if (front < 0):
              front  = lseeksym("Area",2,lbnElement.x2-Step/2,lbnElement.x2+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
              back   = lseeksym("Area",5,lbnElement.Xpos-Step/2,lbnElement.Xpos+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
          if (back < 0):
              back  = lseeksym("Area",5,lbnElement.x2-Step/2,lbnElement.x2+Step/2,lbnElement.Ypos,lbnElement.y2+Step,Step,GV)
          
          GV.curSymbolBend = 0
          
          if (front > 0 ):
             GV.curSymbolBend = GV.FRONT 
             GV.listLbnObject[front].a = GV.Done
          if (back > 0):
             GV.curSymbolBend = GV.BACK
             GV.listLbnObject[back].a = GV.DONE
          if (mlhand > 0):
              GV.curSymbolBend = GV.curSymbolBend + GV.MLHAND
          if (mrhand > 0):
              GV.curSymbolBend = GV.curSymbolBend + GV.MRHAND
          if (wlhand > 0):
              GV.curSymbolBend = GV.curSymbolBend + GV.WLHAND
          if (wrhand > 0):
              GV.curSymbolBend = GV.curSymbolBend + GV.WRHAND
          if (GV.curSymbolBend < 0):
              (GV.nudesfile).write("* OOPS: lbows: bow " + str(GV.symbolCounter) + " with no contacts\n")
        (GV.nudesfile).write("*  lbowsb " + str(GV.symbolCounter+1) + str( held ) + str(front) + str(back) + str(mlhand) + str(mrhand) + str(wlhand) + str(wrhand) + str(curSymbolBend))

#upadting -> GV.curSymbolBend





def lseeksym(Name,i,x1,x2,y3,y4,Step,GV):      
     lap = -1
     if (y3 < 0):
         y3 = 0
     if (y4 < 0):
         y4 = 0
     kstart = y3 - 2*Step    
     if (kstart < 1):
         kstart = 1
     k  = (GV.symbolStartAtYpos[kstart])
     length = len(GV.listLbnObject)
     while ((k < length) and (lap < 0 ) and (GV.listLbnObject[k].Ypos < y4)):
 
         if ((GV.listLbnObject[k].Name == Name) and (GV.listLbnObject[k].Item == i)):
              if ((loverlap(x1,x2,GV.listLbnObject[k].Xpos,GV.listLbnObject[k].x2)  > 0)
                      and (loverlap(y3,y4,GV.listLbnObject[k].Ypos , GV.listLbnObject[k].y2) > 0)):
                lap = k

         k = k + 1
     return lap




