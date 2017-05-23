Labanotation is a two dimensional data structure which represents both time and space. Each Staff is a list of staff modules (where each staff module has its own time and key signatures so they can be independently notated and then combined to form a piece). In case everything remains constant throughout the piece, we can have just one staff module in the entire staff.

> data Notation = Notation {
>   staffs :: [Staff]
> }
>
> data Staff = Staff {
>   timeSignature :: TimeSignature,
>   columnNames :: [ColumnType],   --what column types will be there in the module
>   bars :: [Bar] --here comes the two dimensionality
> } deriving (Show, Eq)

Each bar will contain certain columns which will be filled with symbols representing the movement of the dancer. The interface and parser will ensure that each bar has the same columns in a particular StaffModule.

> data Bar = Bar {
>   barno :: Int,
>   columns :: [Column] 
> } deriving (Show, Eq)

> data Column = Column {
>   columnType :: ColumnType,
>   symbols :: [(Symbol, StepLength, StepLevel, StepPosition, Dimension)]
> } deriving (Show, Eq)
>
>
> data ColumnType = ColSupportLeft | ColSupportRight | ColLegGestureLeft | ColLegGestureRight | ColArmGestureLeft | ColArmGestureRight | ColBodyLeft | ColBodyRight | ColHandLeft | ColHandRight | ColHead deriving (Show, Eq)
>
> data Symbol = DirectionSymbol Dirm | PinSymbol Pin | LimbSymbol Limb | AreaSymbol Area | TurnSymbol Turn | DegreeSymbol Degree deriving (Show, Eq)
>

| KeySymbol Key deriving (Show, Eq)

>
> data Dirm = DirPlace | DirForward | DirBackward | DirRight | DirLeft | DirForwardRight | DirForwardLeft | DirBackwardLeft | DirBackwardRight deriving (Show, Eq)
>
> data Pin = PinForward | PinBackward | PinRight | PinLeft | PinForwardRight | PinForwardLeft | PinBackwardLeft | PinBackwardRight deriving (Show, Eq)
>
> data Limb = ShoulderLeft | ShoulderRight | ElbowLeft | ElbowRight | WristLeft | WristRight | HandLeft | HandRight | FingersLeft | FingersRight | HipLeft | HipRight | KneeLeft | KneeRight | AnkleLeft | AnkleRight | FootLeft | FootRight | ToesLeft | ToesRight | FootHandArea | FootHandBaseArea deriving (Show, Eq)
>
> data Area = AreaForward | AreaBackward | AreaRight | AreaLeft | AreaForwardRight | AreaForwardLeft | AreaBackwardLeft | AreaBackwardRight deriving (Show, Eq)
>
> data Turn = TurnClockwise | TurnAntiClockwise | TurnSomerForward | TurnSomerBackward | TurnCartwheelLeft | TurnCartwheelRight | TurnAny deriving (Show, Eq)
>
> data Degree = DegNarrow | DegVeryNarrow | DegWide | DegVeryWide deriving (Show, Eq)
>
>
> data StepLength = StepLength Int deriving (Show, Eq)
>
> data StepLevel = Low | Medium | High deriving (Show, Eq)
>

x and y coordinates of the starting position of the symbol

> data StepPosition = StepPosition (Int, Int) deriving (Show, Eq)
>
> data TimeSignature = TimeSignature Int Int deriving (Show, Eq)
>
> data Dimension = Dimension (Int, Int) deriving (Show, Eq)
