import math
#from __future__ import division

def find_ini_title(titleList,title):
    if title in titleList:
        return titleList.index(title)
    else:
        return -1

def get_ini_value(valueList,titleList,title):
    value = valueList[find_ini_title(titleList,title)]
    if value.isdigit():
        return int(value)
    else:
        if value[0].upper() == 'T':
            return True
        else:
            return False

def led_opena(GV,min_fps,max_fps,min_beats,max_beats):
    get_out = True
    if (GV.lbn_fps<min_fps or GV.lbn_fps>max_fps):
        print "Oops : fps value is %d but mush be between %d and %d"%(GV.lbn_fps,min_fps,max_fps)
        get_out = False
    if (GV.lbn_bpm < min_beats or GV.lbn_bpm > max_beats):
        if GV.lbn_bpm < 0:
            print "   Oops: bpm value missing"
        else:
            print "   Oops: bpm value is %d but must be between %d and %d"%(GV.lbn_bpm,min_beats,max_beats)
            get_out = False
    return get_out

def led_param(GV):
    
    min_fps = 1
    max_fps = 250
    min_beats = 25
    max_beats = 250

    if GV.numberOfParameterInIni >= 0 :
        lbn_figure_in = get_ini_value(GV.ini_value,GV.ini_title,"lbn_figures")
        lbn_default = get_ini_value(GV.ini_value,GV.ini_title,"lbn_default")
        lbn_fps_in = get_ini_value(GV.ini_value,GV.ini_title,"lbn_fps")
        lbn_bpm_in = get_ini_value(GV.ini_value,GV.ini_title,"lbn_bpm")
    
        if (lbn_fps_in < min_fps) or (lbn_fps_in>max_fps) or (lbn_bpm_in < min_beats) or (lbn_bpm_in>max_beats):
            lbn_default = False
        if lbn_default == True:
            GV.lbn_fps = lbn_fps_in
            GV.lbn_bpm = lbn_bpm_in
            GV.lbn_figures = lbn_figure_in
    if lbn_default == False:
        get_out = False
        print "Please enter frames/second (%d-%d)"%(min_fps,max_beats)
        print "       and beats/minute(%d-%d)"%(min_beats,max_beats)
        print "        seperated by a space"
        while True:
            GV.lbn_fps,GV.lbn_bpm = map(int,raw_input().split())    
            get_out = led_opena(GV,min_fps,max_fps,min_beats,max_beats)
            if get_out == True:
                break
    GV.lbn_fpp = (GV.lbn_fps*GV.doub60)/(GV.lbn_bpm*GV.lbn_ppb) 
    print "    frames/pixel %g, fps %d, bpm %d, ppb %d"%(GV.lbn_fpp,GV.lbn_fps,GV.lbn_bpm,GV.lbn_ppb)
    print " number of figures %d"%GV.lbn_figures
