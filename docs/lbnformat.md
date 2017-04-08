# .lbn Format
This document is a brief description of what .lbn File Format.

## Comment
  In .lbn file if user can added any comment , then this comment is add in starting in file one by one.

## .lbn File divide into 11 colums/parts. 
 1)  Notation Groups
 2)  Item Number
 3)  X Posion 
 4)  Y Posion 
 5)  Step Size 
 6)  Width 
 7)  Hight
 8)  Level
 9)  Text 
 10) Line Number 
 11) Bar Number

### 1)Notation Groups:
     There is a total 12 Notation Groups.
     a) Bars
     b) Stav
     c) Dirn
     d) Limb
     e) Area
     f) Volm
     g) Ways
     h) Face
     i) Misc
     j) Pins
     k) Rotn
     l) Keys
 
##### a) Bars:
All Vertical Lines in LED is called as Bars.<br />
All Bars have a key which is also it's Item number, Wich is increment order star form lower side is 0,1,.....<br />
![Bars](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Bar.png)

##### b) Stav:
All Horizontal Lines in LED is calld Stav.<br />
Stav have a Item number wich is 0,1,2.<br />
![Stav](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Stav.png)

##### c) Dirn:
Dirn have  Following Symbol:<br />
![Dirn](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Dirn.png)

##### d) Limb:
Limb have  Following Symbol:<br />
![Limb](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Limb.png)

##### e) Area:
Area have  Following Symbol:<br />
![Area](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Area.png)

##### f) Volm:
Volm have  Following Symbol:<br />
![Volm](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Volm.png)

##### g) Ways:
Ways have  Following Symbol:<br />
![Ways](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Ways.png)

##### h) Face:
Face have  Following Symbol:<br />
![Face](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Face.png)

##### i) Misc:
Misc have  Following Symbol:<br />
![Misc](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Misc.png)

##### j) Pins:
Pins have  Following Symbol:<br />
![Pins](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Pins.png)

##### k) Rotn:
Rotn have  Following Symbol:<br />
![Rotn](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Rotn.png)

##### l) Keys:
Keys have  Following Symbol:<br />
![Keys](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/Keys.png)

<br /><br />

It is also have a Text. If user can inserted Text into LED then it goes into Keys group.
## 2)Item Number:
Every Group have number of Symbol and evrey Symbol have a Unick Number , for a pertiular grup.That number is called Item number.
Every Symbol have a Item Number . It is a Integer Value.
<br /><br />

## 3 , 4)X and Y Possion:
It is Possion of a Symbol/Text where it is place in LED.
<br /><br />

## 5)Step Size:
Step Size is a integer value , It is a step size of Symbol or Text. <br />
If Symbol Size is incrise then step size also increment by 1. <br />
If Symbol size is dicrese then step size will be decrse by 1.

<br /><br />

## 6)Width:
It is width of Symbol or text.
<br /><br />

## 7)Hight:
It is Hight of Symbol or text.
<br /><br />

## 9)Level:
Every Symbol Having 4 type of level. Wich is Low , High , Midioum and  Blank in .lbn file.<br />
Low lavel have L key , High level have H key , Midioum level have M key and Blank is not a level but if symbil is not given any level then it is Blank wich is B key in .lbn file.<br />
Keys Symbol Having By Default Step Size is Blank wich is B and other Symbol having By Default Midium Level wich is M.

<br /><br />

## 10)Text:
Text is a string or Number or chracter in .lbn file.<br />
Wich is only filled by Keys Notation Group Symbol , otherwise it is empty.
<br /><br />

## 11)Line Number:
It is line number in .lbn file. and It is seprated by '#'.

## 12)Bar Number:
It is Bar number in .lbn file.<br />
It is only filled if symbol is bar otherwise it is empty. and It is Seprayed by '#'.
<br /><br />

## Table:

|Symbol | Notation Group | Item Number | Default Step Size | Defalt Width | Defult Hight |
|-------|----------------|-------------|-------------------|--------------|--------------|
|![Right_Forword](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/right_forword.svg)| Dirn           |      1      |        4          |      10      |     23       |
|![Right_Forword_Diagonal](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/right_forword_diagonal.svg)| Dirn           |      2      |        4          |      10      |     23       |
|![Right_Side](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/right_side.svg)| Dirn           |      3      |        4          |      10      |     23       |
|![Right_backword_diagonal](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/right_backword_diagonal.svg)| Dirn           |      4      |        4          |      10      |     23       |
|![Right_backword](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/right_backword.svg)| Dirn           |      5      |        4          |      10      |     23       |
|![Left_backword_Direction](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/left_backword_Direction.svg)| Dirn           |      6      |        4          |      10      |     23       |
|![Left_backword_Diagonal](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/left_backword_diagonal.svg)| Dirn           |      7      |        4          |      10      |     23       |
|![Left_Side](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/left_side.svg)| Dirn           |      8      |        4          |      10      |     23       |
|![Left_Forword_Diagonal](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/left_forword_diagonal.svg)       | Dirn           |      9      |        4          |      10      |     23       |
|![Left_Forword](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/left_forword.svg)| Dirn           |      10     |        4          |      10      |     23       |
|![Center](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/direction/centre.svg)| Dirn           |      11     |        4          |      10      |     23       |
|![Left_Solder](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_shoulder.svg)| Limb           |      1      |        4          |      12      |     24       |
|![Left_elbow](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_elbow.svg)| Limb           |      2      |        4          |      12      |     24       |
|![Left_wirst](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_wrist.svg)| Limb           |      3      |        4          |      12      |     24       |
|![Left_finger](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_finger.svg)| Limb           |      4      |        4          |      12      |     24       |
|![Left_fingers](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_fingers.svg)| Limb           |      5      |        4          |      12      |     24       |
|![right_shoulder](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_shoulder.svg)| Limb           |      6      |        4          |      12      |     24       |
|![right_elbow](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_elbow.svg)| Limb           |      7      |        4          |      12      |     24       |
|![right_wirst](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_wrist.svg)| Limb           |      8      |        4          |      12      |     24       |
|![right_finger](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_finger.svg)| Limb           |      9      |        4          |      12      |     24       |
|![Right_Fingers](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_fingers.svg)| Limb           |      10     |        4          |      12      |     24       |
|![Left_hip](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_hip.svg)| Limb           |      11     |        4          |      12      |     24       |
|![Left_knee](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_knee.svg)| Limb           |      12     |        4          |      12      |     24       |
|![Left_ankle](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_ankle.svg)| Limb           |      13     |        4          |      12      |     24       |
|![Left_foot](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_foot.svg)| Limb           |      14     |        4          |      12      |     24       |
|![Left_toe](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_toe.svg)| Limb           |      15     |        4          |      12      |     24       |
|![Right_hip](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_hip.svg)| Limb           |      16     |        4          |      12      |     24       |
|![Right_knee](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_knee.svg)| Limb           |      17     |        4          |      12      |     24       |
|![Left_ankle](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_ankle.svg)| Limb           |      18     |        4          |      12      |     24       |
|![Right_foot](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_foot.svg)| Limb           |      19     |        4          |      12      |     24       |
|![Right_toe](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_toe.svg)| Limb           |      20     |        4          |      12      |     24       |
|![Palm](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/palm.svg)| Limb           |      21     |        4          |      12      |     24       |
|![Palm_Upper_Side](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/palm_upper_side.svg)| Limb           |      22     |        4          |      12      |     24       |
|![up_middle_arm](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/up__middle_arm_gesture.svg)  | Area           |      1      |        3          |      15      |     15       |
|![right_high_arm](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_high_arm_gesture.svg)       | Area           |      2      |        3          |      15      |     15       |
|![right_middle_arm](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_middle_arm_gesture.svg)       | Area           |      3      |        3          |      15      |     15       |
|![right_low_leg](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_low_leg_gesture.svg)       | Area           |      4      |        3          |      15      |     15       |
|![down_middle_arm](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/down__middle_arm_gesture.svg)       | Area           |      5      |        3          |      15      |     15       |
|![left_low_leg](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_low_leg_gesture.svg)       | Area           |      6      |        3          |      15      |     15       |
|![left_middle_arm](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_middle_arm_gesture.svg)       | Area           |      7      |        3          |      15      |     15       |
|![left_high_arm](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_high_arm_gesture.svg)       | Area           |      8      |        3          |      15      |     15       |
|![chest](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/chest.svg)       | Area           |      9      |        3          |      15      |     15       |
|![Short_1](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/intensity/short_1.svg)| Volm           |      1      |        1          |      12      |     12       |
|![Long_1](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/intensity/long_1.svg)       | Volm           |      2      |        1          |      12      |     12       |
|![Short_4](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/intensity/short_4.svg)       | Volm           |      3      |        1          |      12      |     12       |
| ![Long_4](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/intensity/long_4.svg)      | Volm           |      4      |        1          |      12      |     12       |
| ![5](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-72%20copy.svg)      | Volm           |      5      |        1          |      12      |     12       |
| ![6](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-70.svg)       | Volm           |      6      |        1          |      12      |     12       |
| ![7](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/tambaurine.svg)       | Volm           |      7      |        1          |      12      |     12       |
| ![Ways1](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/path_back.svg)      | Ways           |      1      |        6          |      12      |     24       |
| ![Ways2](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/path_front.svg)      | Ways           |      2      |        6          |      12      |     24       |
|![Ways3](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/trill.svg)       | Ways           |      3      |        6          |      12      |     24       |
|![Ways4](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/inward_undulation.svg)       | Ways           |      4      |        6          |      12      |     24       |
| ![Ways5](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/outword_undulation.svg)      | Ways           |      5      |        6          |      12      |     24       |
| ![Ways6](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-5%20copy.svg)      | Ways           |      6      |        3          |      12      |     48       |
| ![Ways7](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-6%20copy.svg)      | Ways           |      7      |        3          |      12      |     48       |
| ![Face1](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/front_of_audiance.svg)      | Face           |      1      |        1          |      18      |     18       |
|![Face2](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/front_right_of_audiance.svg)       | Face           |      2      |        1          |      18      |     18       |
|![face3](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/right_of_audiance.svg)       | Face           |      3      |        1          |      18      |     18       |
|![face4](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/back_right_of_audiance.svg)       | Face           |      4      |        1          |      18      |     18       |
|![face5](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/back_of_audiance.svg)       | Face           |      5      |        1          |      18      |     18       |
|![face6](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/back_left_of_audiance.svg)       | Face           |      6      |        1          |      18      |     18       |
|![face7](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/left_of_audiance.svg)       | Face           |      7      |        1          |      18      |     18       |
|![face8](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/front_left_of_audiance.svg)       | Face           |      8      |        1          |      18      |     18       |
| ![Misc1](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-3%20copy.svg)      | Misc           |      1      |        4          |      48      |     8        |
|![Misc2](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-23%20copy.svg)       | Misc           |      2      |        4          |      12      |     12       |
| ![Misc3](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-24%20copy.svg)      | Misc           |      3      |        4          |      12      |     12       |
|![Misc4](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-20%20copy.svg)       | Misc           |      4      |        4          |      12      |     12       |
|![Misc5](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-18%20copy.svg)       | Misc           |      5      |        4          |      12      |     12       |
|![Misc6](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-19.svg)       | Misc           |      6      |        4          |      12      |     12       |
|![Misc7](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-21%20copy.svg)       | Misc           |      7      |        4          |      12      |     12       |
|![Misc8](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/right_whole_foot.svg)       | Misc           |      8      |        4          |      12      |     12       |
| ![Misc9](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/body/left_whole_foot.svg)      | Misc           |      9      |        4          |      12      |     12       |
| ![Pins1](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/degrees_of_rotation_clockwise_360.svg)      | Pins           |      1      |        1          |      18      |     18       |
| ![Pins2](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/degrees_of_rotation_clockwise_45.svg)      | Pins           |      2      |        1          |      18      |     18       |
| ![Pins3](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/degrees_of_rotation_clockwise_90.svg)      | Pins           |      3      |        1          |      18      |     18       |
| ![Pins4](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/degrees_of_rotation_clockwise_135.svg)      | Pins           |      4      |        1          |      18      |     18       |
| ![Pins5](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/degrees_of_rotation_clockwise_180.svg)      | Pins           |      5      |        1          |      18      |     18       |
| ![Pins6](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/degrees_of_rotation_clockwise_225.svg)      | Pins           |      6      |        1          |      18      |     18       |
| ![Pins7](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/degrees_of_rotation_clockwise_270.svg)      | Pins           |      7      |        1          |      18      |     18       |
| ![Pins8](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/degrees_of_rotation_clockwise_315.svg)      | Pins           |      8      |        1          |      18      |     18       |
| ![Rotn1](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/anticlockwise_turning.svg)      | Rotn           |      1      |        4          |      10      |     22       |
| ![Rotn2](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/clockwise_turning.svg)      | Rotn           |      2      |        4          |      10      |     22       |
| ![Rotn3](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/somersaulting_forward.svg)      | Rotn           |      3      |        4          |      10      |     22       |
| ![Rotn4](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/somersaulting_backward.svg)      | Rotn           |      4      |        4          |      10      |     22       |
| ![Rotn5](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/cartwheeling_left.svg)  | Rotn           |      5      |        4          |      10      |     22       |
| ![Rotn6](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/rotation/cartwheeling_right.svg)      | Rotn           |      6      |        4          |      10      |     22       |
| ![Rotn7](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/turning/no_turn.svg)      | Rotn           |      7      |        4          |      10      |     22       |
| ![Rotn8](https://rawgit.com/rusimody/Laban-tk/pucsd_laban_project/src/web_led/laban_notations/others/Untitled-47%20copy.svg)      | Rotn           |      7      |        4          |      10      |     22       |
|   1   | Keys           |      1      |        2          |      12      |     12       |
|   2   | Keys           |      2      |        2          |      12      |     12       |
|   3   | Keys           |      3      |        2          |      12      |     12       |
|   4   | Keys           |      4      |        2          |      12      |     12       |
|   5   | Keys           |      5      |        2          |      12      |     12       |
|   [   | Keys           |      6      |        2          |      12      |     12       |
|   ]   | Keys           |      7      |        2          |      12      |     12       |
|   C   | Keys           |      8      |        2          |      12      |     12       |
|   6   | Keys           |      9      |        2          |      12      |     12       |
|   7   | Keys           |      10     |        2          |      12      |     12       |
|   8   | Keys           |      11     |        2          |      12      |     12       |
|   9   | Keys           |      12     |        2          |      12      |     12       |
|   0   | Keys           |      13     |        2          |      12      |     12       |
|   (   | Keys           |      14     |        2          |      12      |     12       |
|   )   | Keys           |      15     |        2          |      12      |     12       |
|   .   | Keys           |      16     |        2          |      12      |     12       |
|   _   | Keys           |      17     |        2          |      12      |     12       |
|   +   | Keys           |      18     |        2          |      12      |     12       |
|   ~   | Keys           |      19     |        2          |      12      |     12       |
|   <   | Keys           |      10     |        2          |      12      |     12       |
|   >   | Keys           |      21     |        2          |      12      |     12       |
|   /   | Keys           |      22     |        2          |      12      |     12       |
|   \|  | Keys           |      23     |        2          |      12      |     12       |
|   \   | Keys           |      24     |        2          |      12      |     12       |
 

## Example of .lbn File:
![Eg](https://raw.githubusercontent.com/rusimody/Laban-tk/pucsd_laban_project/docs/img/eg.png)


\# This is a example of .lbn File <br />
Stav   0  9   12   1   1  638 B   # 1<br />
Stav   1 170   12   1   1  638 B   # 2<br />
Stav   2 133   48   1   1  602 L   # 3<br />
Bars   0  30   48   1 464    3 B   # 4 # bar 0<br />
Bars   1  30   96   1 464    3 L   # 5 # bar 1<br />
Dirn  11 134   97   4  10   23 M   # 6<br />
Keys   1  18   98   2   5   12 L 1 # 7<br />
Dirn   1 134  121   4  10   23 M   # 8<br />
Bars   2  30  145   1 464    3 B   # 9 # bar 2<br />
Dirn  10 122  146   4  10   23 M   # 10<br />
Keys   1  18  146   2   2   12 B 2 # 11<br />
Dirn   3 134  171   4  10   23 M   # 12<br />
Bars   3  30  194   1 464    3 B   # 13 # bar 3<br />
Dirn   8 122  195   4  10   23 M   # 14<br />
Keys   1  18  195   2   2   12 B 3 # 15<br />
Dirn  11 134  219   4  10   23 M   # 16<br />
Bars   4  30  243   1 464    3 B   # 17 # bar 4<br />
Keys   1  18  244   2   2   12 B 4 # 18<br />
Keys   0  95  267   2  20   15 L demo # 19<br />
Bars   5  30  292   1 464    3 B   # 20 # bar 5<br />
Keys   1  18  293   2   2   12 B 5 # 21<br />
Bars   6  30  341   1 464    3 B   # 22 # bar 6<br />
Keys   1  18  342   2   2   12 B 6 # 23<br />
Bars   7  30  390   1 464    3 B   # 24 # bar 7<br />
Keys   1  18  391   2   2   12 B 7 # 25<br />
Bars   8  30  439   1 464    3 B   # 26 # bar 8<br />
Keys   1  18  440   2   2   12 B 8 # 27<br />
Bars   9  30  488   1 464    3 B   # 28 # bar 9<br />
Keys   1  18  489   2   5   12 L 1 # 29<br />
Keys   1  18  489   2   2   12 B 9 # 30<br />
Bars  10  30  537   1 464    3 B   # 31 # bar 10<br />
Keys   1  18  538   2  10   12 B 10 # 32<br />
Bars  11  30  586   1 464    3 B   # 33 # bar 11<br />
Keys   1  18  587   2  10   12 B 11 # 34<br />
Bars  12  30  635   1 464    3 B   # 35 # bar 12<br />
Keys   1  18  636   2  10   12 B 12 # 36<br />
