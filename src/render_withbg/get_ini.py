import os

def get_ini(GV,dump):
    max_ini = 256
    GV.ini_title = map(lambda x: [None]+x[1:],GV.ini_title)
    GV.ini_value = map(lambda x: [None]+x[1:],GV.ini_value)
    GV.numberOfParameterInIni = -1 # -1 if lintel.ini is not found else > 0
    try:
        iniFilePointer = open("lintel.ini","r")
    except IOError:
        print "lintel.ini not available - will continue"
        sys.exit()
    with iniFilePointer:
        ini_no = 0
        ini_diag = 0

        GV.ini_title = []
        GV.ini_value = []
        GV.buffer = iniFilePointer.readlines()
        prefix = ('*',' ')
        for i in GV.buffer:
            if i[0]=='*' or i[0]==' ':
                continue
            else:
                temp = i.strip('\n').split(',')
                if len(temp)>1:
                    GV.ini_title.append(temp[0])
                    GV.ini_value.append(temp[1].split(';')[0].strip())

