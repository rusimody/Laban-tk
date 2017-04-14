import sys


#readFile :: String -> [String]
def readFile(FileName):
    try:
       data =filter(lambda fLines : len(fLines.strip(' ')) > 1 , open(FileName).readlines()) 
   #    logUpdate({"function" : "readFile() successfully"}) 
       return data
    except :
   #    logUpdate({"function" : "readFile()  unsuccessfully"}) 
       return None



def createDict(dictOb,lListKeyValue):    
    if(lListKeyValue[0][0] == 'B'):
          dictOb[lListKeyValue[1]]= int(lListKeyValue[2])
          return dictOb
    elif lListKeyValue[0][0] == 'i':

         if lListKeyValue[0] == "int_array":
            if(int(lListKeyValue[2]) == 1):
              dictOb[lListKeyValue[1]] = [-1 for x in range(int(lListKeyValue[3]))]
              return dictOb
            else :
              dictOb[lListKeyValue[1]] = [[-1 for y in range(int(lListKeyValue[4])) ] for x in range(int(lListKeyValue[3]))]  
              return dictOb
         else :
              dictOb[lListKeyValue[1]] = int(lListKeyValue[2])
              return dictOb
    
    elif lListKeyValue[0][0] == 'c':
          dictOb[lListKeyValue[1]] = lListKeyValue[2]
          return dictOb
    elif lListKeyValue[0][0] == 'd':
          dictOb[lListKeyValue[1]] = float(lListKeyValue[2])
          return dictOb
    elif lListKeyValue[0] == 'char_array':

         if(int(lListKeyValue[2]) == 1):
           dictOb[lListKeyValue[1]] = ['' for x in range(int(lListKeyValue[3]))]
           return dictOb
         else :
           dictOb[lListKeyValue[1]] = [["" for y in range(int(lListKeyValue[4])) ] for x in range(int(lListKeyValue[3]))]  
           return dictOb


         
#readFile :: [Lines] -> [dict]
def createLinterVariable(lLines):
    initialComment = int((lLines[0].split())[1])
    lLines  = lLines[initialComment+1:]
    lLines  = filter(lambda l : len(l) > 1 ,map(lambda x: x.strip() ,lLines))  # filter out the blank lines

    dictOfVariable = dict()
    
    while (len(lLines) > 1 ) and (lLines[0][0] == '#') :
      print lLines
      dictSpec = map(lambda Token : Token.strip()  ,lLines[1].split(' ')) 
      dictOfVariable[dictSpec[2]] = reduce( lambda dic,line :createDict(dic,map(lambda dictKV : dictKV.strip() ,line.split())) , lLines[2:int(dictSpec[1])],{}) 
      lLines = lLines[int(dictSpec[1])+2:]

    #adding lbn[LMAX]
    dictOfVariable['fileStorage']['lbn'] = [dictOfVariable['symbolStruct'] for x in range(dictOfVariable['hashGlobal']['LMAX'])]                               
    dictOfVariable.pop('')
    return dictOfVariable




ldata = readFile(sys.argv[1])
globalVariableForLinter = createLinterVariable(ldata)
