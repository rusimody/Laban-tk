import os.path
# contains function get_files and add_id_num:

def get_files(GV,filename):
    if (filename == None):
        print("\n please provide a filename \n")
        return
    GV.name = filename
    indexDot = (GV.name).find(".")
    if (indexDot == -1):
        Extension = ""
    else:
        Extension = (GV.name[indexDot:])

    isError = 1
    if ((Extension == ".nud") or (Extension == ".n")):
       GV.input_file_type = 0
       GV.haslbn = GV.FALSE
       isError = 0

    if (Extension == ".lbn"):
       GV.input_file_type = 1
       GV.haslbn = GV.TRUE
       isError = 0

    if (Extension == "."):
       GV.input_file_type = 2
       GV.name = GV.name + "lbn"
       GV.haslbn = GV.TRUE
       isError = 0

    if (Extension == ""):
       GV.input_file_type = 2
       GV.name = GV.name + ".lbn"
       GV.haslbn = GV.TRUE
       isError = 0
    if (isError == 1):
       GV.name = ""
       return
 
    #either it is .nud/.n or .lbn
    if (GV.input_file_type == 0):
        GV.nudesname = GV.name
    if (GV.input_file_type > 0):
        GV.finname = GV.name
    try:
            filepointer = open(GV.name, "r")
    except IOError:
            print( "\n\n  " + GV.name + "  OOPS? \n")
            print("file NOT found \n Please give correct file name as arguments\n")
            return
    print ("Opened  " + GV.name + "\n")
    
    if (GV.input_file_type > 0):
        add_id_num(GV)
        print("nude file name %s"%GV.nudesname)
        try:
           GV.nudesfile = open(GV.nudesname , "a")
           print("\n created nudes file" + GV.nudesname +"\n")
        except IOError:
                 print("\n\n  "+GV.nudesname+" OOPS? \n")
                 return

        try:
            GV.infile = open(GV.nudesname , "r")
        except IOError:
                print("\n\n " + GV.nudesname + " OOPS \n")


            
def add_id_num(GV):
    ext = ".n"
    for j in range(0,100):   #10000 is the upperlimit on number of nude files one can create we can change this value:
        GV.nudesname =  GV.name+"_"+str(j)+ext 
        
        if (  os.path.isfile(GV.nudesname ) == False):
            return
        else:
             a= 1
            



