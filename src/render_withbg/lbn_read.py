
class lbn_element():
    def __init__(self,name,item,x_position,y_position,stepSize,width,height ,level ):#,text ,lineNUmber):
        self.Name = name
        self.Item = item
        self.Xpos = x_position
        self.Ypos = y_position
        self.StepSize = stepSize
        self.Width = width
        self.Height = height
        self.Level = level
        self.a = 0                   #till now no idea about this entry   
        self.x2 = (x_position + width)
        self.y2 = (y_position + height)


def lbn_read(GV):
    try:
        filepointer = open(GV.finname , "r")
    except IOError:
        print("lbn file not found:")
        return
    with open(GV.finname) as f:
        content = f.readlines()
    content = map(lambda x: x.split() ,content)
    GV.listLbnObject =  map( lambda x:  lbn_element(x[0] , int(x[1]) ,int(x[2]) , int(x[3]), int(x[4]) , int(x[5]) , int(x[6]) , x[7]), content)

    GV.xmin = min(map(lambda y: y.Xpos , GV.listLbnObject))

    GV.Num_Lab_Entries = len( GV.listLbnObject )
    print( "lbnread:  " + str(GV.Num_Lab_Entries) + "  lbn symbols \n" )
    lbn_sorty(GV)

def lbn_sorty(GV):
  myList = map(lambda x: x.Ypos , GV.listLbnObject)
  listIndex = ([i[0] for i in sorted(enumerate(myList), key=lambda x:x[1])] )
  
  GV.listLbnObject = [x for (y,x) in sorted(zip(listIndex, GV.listLbnObject) )]





