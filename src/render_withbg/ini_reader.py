import re

def ini_reader(ini_file):

    filename = open(ini_file,"r")
    file_data = filename.read()
    lines = file_data.split("\n")

    var_line_patt = re.compile("(.*),(.*);(.*)$")
    
    var_lines = []
    var_names = []
    var_values = []
    
    for i in lines:
        if var_line_patt.match(i):
            strip_comments = i.split(";")
            var_lines.append(strip_comments[0])
            
    for i in var_lines:
        separate_name_value = i.split(",")        
        var_names.append(separate_name_value[0])
        var_values.append(separate_name_value[1].lstrip())

    return var_names,var_values



filename = "/home/vikrant/laban_proj/Laban-tk/src/render_withbg/lintel.ini"
list = ini_reader(filename)
n = len(list[0])
for i in range(n):
    print list[0][i],list[1][i]
    
