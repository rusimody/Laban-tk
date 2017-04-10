
def initialise(GV):
    
    GV.keylen = [0 for i in range(0,GV.EMAX)]
    GV.ellen = GV.jntlen = GV.fillen = GV.figlen = GV.sublen = GV.varlen =  [-1 for i in range(0,GV.EMAX)]
    GV.knee = GV.figell =  GV.ellfig =  GV.usevar = [0 for i in range(0,GV.EMAX)]
    GV.frstart = GV.frstop = GV.distrn = GV.cline = [0 for i in range(0,GV.EMAX)]
   
    GV.ellen[0] = GV.figlen[0] = GV.figlen[1] = GV.sublen[0] = GV.fillen[0] = GV.varlen[0] =5
    GV.axlen = [1,1,1] + [-1 for i in range(3,GV.EMAX)]

    GV.figell[1] = 1
   
    GV.coel = [[-1,-1] for i in range(0, GV.EMAX)]
    GV.subact = [[0,0] for i in range(0, GV.EMAX)]   #defined with upperlimit PMAX
   
    GV.called = GV.defined =  [1 for i in range(0,GV.PMAX)]
    GV.val = [GV.doub0 for i in range(0,GV.PMAX)] 

    #its a 3by3 matrix : rotation matrix applied to all ellipsoids to obtain observers view
    GV.obs = [[GV.doub1 ,GV.doub0 ,GV.doub0] , [GV.doub0 ,GV.doub1 ,GV.doub0]  ,[GV.doub0 ,GV.doub0 ,GV.doub1]]

    #its a 3by3 matrix :cen[i][j] - jth coordinate of centre of ith ellipsoid
    GV.cen = [[GV.doub3 ,GV.doub3 ,GV.doub3] for i in range(0,GV.EMAX)]

    #its a 3by3 matrix :ax3[i][j] - length of jth semiaxis of ith ellipsoid
    GV.ax =  [[GV.doub1 ,GV.doub1 ,GV.doub1]]  + [[GV.doub2 ,GV.doub2 ,GV.doub2] for i in range(0,(GV.EMAX)-1)]

    GV.color = [[GV.doub255 , GV.doub150 , GV.doub90] for i in range(0,GV.EMAX)  ]
    GV.quat = [[GV.doub1 , GV.doub0  , GV.doub0   , GV.doub0 , GV.doub1]  for i in range(0,GV.EMAX)] + [[GV.doub0 for i in range(0,5)] for j in range(0,2)]
    GV.axisname = ['x' ,'y','z']
    GV.textMapFileName = ['dummy']
    GV.figureName = ['every' , 'world']
    GV.ename = ['world']
    GV.vname = ['variab']
    GV.sname = ['nudes']

    GV.typeAction = [GV.keywordCode[15] for i in range(0,GV.PMAX)]  
    GV.pf = [[0,0,0,0,0,0] for i in range(0,GV.PMAX)]
   
    GV.frameInc = 1 
    GV.anglex = GV.angley = GV.anglez = GV.tx = GV.ty = GV.tz = GV.doub0
    GV.scaleFactor = GV.doub1
    GV.angleInc = GV.doub3
    GV.typeCurAction = 0
    GV.more = 1
    GV.ok = 0
    GV.frameCount = 0
    GV.num_chord_sphere = GV.init_num_chord_sphere
    GV.num_subroutine = 1
    GV.num_figure = 2
    GV.num_ellip_curFrame = 1 

    b = GV.doub1
    m = 0
    a = GV.inv2

    while(GV.doub1 + b > GV.doub1+a):
        b = a
        m += 1
        a *= GV.inv2

    tolr = b+b
    #print(tolr)
    '''
    print("   tolr " + (repr(n))) # + " " + (repr(m)) + " bits , maxint " + (repr(maxint)) + " ( " + (repr(n)) ")" )
    '''






