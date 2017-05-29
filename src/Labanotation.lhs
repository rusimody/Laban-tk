
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
> data StepLevel = Low | Medium | High deriving (Show, Eq, Data, Typeable)
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
