
> {-# LANGUAGE DeriveDataTypeable #-}

> import Text.JSON.Generic

> import GHC.Generics
> import Data.Char

Labanotation is a two dimensional data structure which represents both time and space. Each Staff is a list of staff modules (where each staff module has its own time and key signatures so they can be independently notated and then combined to form a piece). In case everything remains constant throughout the piece, we can have just one staff module in the entire staff.

> data Notation = Notation {
>   staffs :: [Staff]
> } deriving (Show, Eq, Data, Typeable)
>
> data Staff = Staff {
>   timeSignature :: TimeSignature,
>   columnNames :: [(ColumnType, Position, Dimension)],--what column types will be there in the module
>   bars :: [Bar] --here comes the two dimensionality
> } deriving (Show, Eq, Data, Typeable)

Each bar will contain certain columns which will be filled with symbols representing the movement of the dancer. The interface and parser will ensure that each bar has the same columns in a particular StaffModule.

> data Bar = Bar {
>   barno :: Int,
>   position :: Position,
>   dimension :: Dimension,
>   columns :: [Column] 
> } deriving (Show, Eq, Data, Typeable)

> data Column = Column {
>   columnType :: ColumnType,
>   symbols :: [(Symbol, StepLength, StepLevel, StepPosition, Dimension)]
> } deriving (Show, Eq, Data, Typeable)
>
>
> data ColumnType = ColSupportLeft | ColSupportRight | ColLegGestureLeft | ColLegGestureRight | ColArmGestureLeft | ColArmGestureRight | ColBodyLeft | ColBodyRight | ColHandLeft | ColHandRight | ColHead deriving (Show, Eq, Data, Typeable)
>
> data Symbol = DirectionSymbol Dirm | PinSymbol Pin | LimbSymbol Limb | AreaSymbol Area | TurnSymbol Turn | DegreeSymbol Degree deriving (Show, Eq, Data, Typeable)
>

| KeySymbol Key deriving (Show, Eq)

>
> data Dirm = DirPlace | DirForward | DirBackward | DirRight | DirLeft | DirForwardRight | DirForwardLeft | DirBackwardLeft | DirBackwardRight deriving (Show, Eq, Data, Typeable)
>
> data Pin = PinForward | PinBackward | PinRight | PinLeft | PinForwardRight | PinForwardLeft | PinBackwardLeft | PinBackwardRight deriving (Show, Eq, Data, Typeable)
>
> data Limb = ShoulderLeft | ShoulderRight | ElbowLeft | ElbowRight | WristLeft | WristRight | HandLeft | HandRight | FingersLeft | FingersRight | HipLeft | HipRight | KneeLeft | KneeRight | AnkleLeft | AnkleRight | FootLeft | FootRight | ToesLeft | ToesRight | FootHandArea | FootHandBaseArea deriving (Show, Eq, Data, Typeable)
>
> data Area = AreaForward | AreaBackward | AreaRight | AreaLeft | AreaForwardRight | AreaForwardLeft | AreaBackwardLeft | AreaBackwardRight deriving (Show, Eq, Data, Typeable)
>
> data Turn = TurnClockwise | TurnAntiClockwise | TurnSomerForward | TurnSomerBackward | TurnCartwheelLeft | TurnCartwheelRight | TurnAny deriving (Show, Eq, Data, Typeable)
>
> data Degree = DegNarrow | DegVeryNarrow | DegWide | DegVeryWide deriving (Show, Eq, Data, Typeable)
>
>
> data StepLength = StepLength Int deriving (Show, Eq, Data, Typeable)
>
> data StepLevel = Low | Medium | High  | Blank deriving (Show, Eq, Data, Typeable)
>

x and y coordinates of the starting position of the symbol

> data StepPosition = StepPosition (Int, Int) deriving (Show, Eq, Data, Typeable)
>
> data TimeSignature = TimeSignature Int Int deriving (Show, Eq, Data, Typeable)
>
> data Dimension = Dimension (Int, Int) deriving (Show, Eq, Data, Typeable)
> data Position = Position (Int, Int) deriving (Show, Eq, Data, Typeable)
>

A function to parse from an input JSON string to the structure defined above

> trim = filter (not . isSpace)
> parseFromJSON :: String -> Notation
> parseFromJSON string = ((decodeJSON (trim string)) :: Notation)



toLbn is a function that take file-name and Notation as a input and create file_name.lbn file


> pin = [(PinForward,1) , (PinBackward,2) ,( PinRight,3) , (PinLeft,4) , (PinForwardRight,5) , (PinForwardLeft,6) , (PinBackwardLeft,7) , (PinBackwardRight,8)]
>
> dirm = [(DirPlace,1) , (DirForward,2) , (DirBackward,3) , (DirRight,4) ,( DirLeft,5) , (DirForwardRight,6) , (DirForwardLeft,7) ,( DirBackwardLeft ,8), (DirBackwardRight,9)]
>
> area = [(AreaForward,1) , (AreaBackward,2) , (AreaRight,3) , (AreaLeft,4) , (AreaForwardRight,5) , (AreaForwardLeft,6) , (AreaBackwardLeft,7) , (AreaBackwardRight,8)]
>
> limb = [(ShoulderLeft,1) , (ShoulderRight,2) , (ElbowLeft,3) , (ElbowRight,4) , (WristLeft,5) , (WristRight,6) , (HandLeft,7) , (HandRight,8) , (FingersLeft,9) , (FingersRight,10) , (HipLeft,11) , (HipRight,12) ,( KneeLeft,13) , (KneeRight,14) , (AnkleLeft,15) , (AnkleRight,16) , (FootLeft,17) , (FootRight,18) , (ToesLeft,19) , (ToesRight,20) , (FootHandArea,21) ,( FootHandBaseArea,22) ]
>
> turn = [(TurnClockwise,1) , (TurnAntiClockwise,2) , (TurnSomerForward,3) , (TurnSomerBackward,4) , (TurnCartwheelLeft,5) , (TurnCartwheelRight,6) , (TurnAny,7)]
>
> degree =[ (DegNarrow,1) , (DegVeryNarrow,2) , (DegWide,3) , (DegVeryWide,4) ]
>
> coltype = [(ColSupportLeft,0) , (ColSupportRight,1) , (ColLegGestureLeft,0) , (ColLegGestureRight,1) ,( ColArmGestureLeft,0) ,( ColArmGestureRight,1) ,( ColBodyLeft,0) , (ColBodyRight,1) , (ColHandLeft,0) , (ColHandRight,1) , (ColHead,2) ]
>
>
> level = [(High,"H"),(Low,"L"),(Medium,"M"),(Blank,"B")]
>
>
> combineLbn :: Notation -> String
> combineLbn (Notation ls) = cmbStav ++ (concat . map barLbn $ (zip lst1 linLst))
>  where
>   lst  = map (\(Staff a b bars) -> map (\(Bar bn pos dim colms) -> ((bn,pos,dim),(concat . map (\(Column t ls) -> ls) $ colms))) bars) ls
>   bnos = map fst (head lst)
>   lst1 = map (\bn->(bn,(concat . map ((\(Just x)->x).lookup bn) $ lst))) bnos
>   lst2 = concat . map (\(Staff a b ls1)-> b) $ ls
>   cmbStav = concat . map (\(( ct ,Position (x, y) ,Dimension (w, h)),ln) -> "Stav " ++ ((\(Just a)-> show a) $ (lookup ct coltype)) ++ " " ++ (show x) ++ " " ++ (show y) ++ " 1 " ++ ( show w) ++ " " ++ (show h) ++ " B # " ++ show ln ) $ (zip lst2 ([1..length lst2]))
>   linLst = getLn (1+length lst2) (map snd lst1)

>
> getLn :: Int -> [[(Symbol, StepLength, StepLevel, StepPosition, Dimension)]] -> [Int]
> getLn cnt []  = [cnt]
> getLn cnt (a:ls) = cnt : (getLn (cnt+length a) ls)



> barLbn :: (((Int, Position, Dimension), [(Symbol, StepLength, StepLevel, StepPosition, Dimension)]),Int) -> [Char]
> barLbn (((num , (Position (x,y)) , (Dimension (w,h)) ) , ls),ln) = "Bars " ++ (show num) ++ (show x)++" "++(show y) ++ " 1 " ++ (show w)++" "++(show h) ++ " B # " ++ (show ln) ++ " # bar " ++ (show num) ++ "\n"++ (concat . map symbLbn $ (zip ls [ln+1..ln+length ls])) 


> symbLbn :: ((Symbol, StepLength, StepLevel, StepPosition, Dimension),Int) -> String
> symbLbn ((DirectionSymbol d , StepLength l , lev , StepPosition (x, y) ,Dimension (w, h)),ln) = "Drin " ++ (show ((\(Just x)->x) $(lookup d dirm))) ++ " " ++ (show x) ++ " " ++ (show y) ++ " " ++ (show l) ++ " " ++ (show w) ++ " " ++ (show h) ++ " " ++ ((\(Just x)->x)$(lookup lev level)) ++ " # " ++ (show ln) ++ "\n"
> symbLbn ((PinSymbol p , StepLength l , lev , StepPosition (x, y) ,Dimension (w, h)),ln) = "Pins " ++ (show ((\(Just x)->x) $(lookup p pin))) ++ " " ++ (show x) ++ " " ++ (show y) ++ " " ++ (show l) ++ " " ++ (show w) ++ " " ++ (show h) ++ " " ++ ((\(Just x)->x)$(lookup lev level)) ++ " # " ++ (show ln) ++ "\n"
> symbLbn ((LimbSymbol li , StepLength l , lev , StepPosition (x, y) ,Dimension (w, h)),ln) = "Limb " ++ (show ((\(Just x)->x) $(lookup li limb))) ++ " " ++ (show x) ++ " " ++ (show y) ++ " " ++ (show l) ++ " " ++ (show w) ++ " " ++ (show h) ++ " " ++ ((\(Just x)->x)$(lookup lev level)) ++ " # " ++ (show ln) ++ "\n"
> symbLbn ((AreaSymbol ar , StepLength l , lev , StepPosition (x, y) ,Dimension (w, h)),ln) = "Area " ++ (show ((\(Just x)->x) $(lookup ar area))) ++ " " ++ (show x) ++ " " ++ (show y) ++ " " ++ (show l) ++ " " ++ (show w) ++ " " ++ (show h) ++ " " ++ ((\(Just x)->x)$(lookup lev level)) ++ " # " ++ (show ln) ++ "\n"
> symbLbn ((TurnSymbol tr, StepLength l , lev , StepPosition (x, y) ,Dimension (w, h)),ln) = "Rotn " ++ (show ((\(Just x)->x) $(lookup tr turn))) ++ " " ++ (show x) ++ " " ++ (show y) ++ " " ++ (show l) ++ " " ++ (show w) ++ " " ++ (show h) ++ " " ++ ((\(Just x)->x)$(lookup lev level)) ++ " # " ++ (show ln) ++ "\n"
> symbLbn ((DegreeSymbol dr, StepLength l , lev , StepPosition (x, y) ,Dimension (w, h)),ln) = " " ++ (show ((\(Just x)->x) $(lookup dr degree))) ++ " " ++ (show x) ++ " " ++ (show y) ++ " " ++ (show l) ++ " " ++ (show w) ++ " " ++ (show h) ++ " " ++ ((\(Just x)->x)$(lookup lev level)) ++ " # " ++ (show ln) ++ "\n"

> toLbn :: String -> Notation -> IO ()
> toLbn fname notation =  writeFile (fname++".lbn") (combineLbn notation)
