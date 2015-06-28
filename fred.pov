#include "colors.inc"    
global_settings {  assumed_gamma 1.0 }



camera{
            location <1000,1000,1000>
            look_at <0,0,0 >
    }
    
light_source{
            <000,2000,2000>
            color White
    }
    
 #declare lfoot =
 sphere{
      0,1 scale<40,20,80>
    //  texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
   
    #declare rfoot =
 sphere{
      0,1 scale<40,20,80>
    //  texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
   
   
    #declare lleg =
 sphere{
      0,1 scale<40,200,40>
   //   texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
   
   
    #declare rleg =
 sphere{
      0,1 scale<40,200,40>
      //texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   }   
   
   
    #declare lthigh =
 sphere{
      0,1 scale<50,200,60>
    //  texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
   
   
    #declare rthigh =
 sphere{
      0,1 scale<50,200,60>
  //    texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
    #declare luarmt =
 sphere{
      0,1 scale<40,135,40>
//      texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
   
    #declare luarm =
 sphere{
      0,1 scale<40,135,40>
//      texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
   
    #declare ruarm =
 sphere{
      0,1 scale<40,135,40>
//      texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
    #declare llarm =
 sphere{
      0,1 scale<35,120,35>
      //texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
    #declare rlarm =
 sphere{
      0,1 scale<35,120,35>
    //  texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   }
   
   
    #declare lhand =
 sphere{
      0,1 scale<40,70,20>
  //    texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
   
    #declare rhand =
 sphere{
      0,1 scale<40,70,20>
//      texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   }
   
   
    #declare lthumb =
 sphere{
      0,1 scale<10,50,10>
      //texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
    #declare rthumb =
 sphere{
      0,1 scale<10,50,10>
    //  texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   }  
   
   
   
    #declare head =
 sphere{
      0,1 scale<73,100,80>
  //    texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
   
    #declare nose =
 sphere{
      0,1 scale<20,20,60>
//      texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
    #declare neck =
 sphere{
      0,1 scale<30,60,30>
   //   texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   }  
   
   
    #declare shldrs =
 sphere{
      0,1 scale<155,50,40>
      //texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   

   
    #declare chest =
 sphere{
      0,1 scale<130,230,75>
     // texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   } 
   
    #declare pelvis =
 sphere{
      0,1 scale<120,75,75>
     // texture{pigment{color rgbf <1,0.95,0.9,0.8> }}
   }
    
#declare plane1 =   
     plane{
            y,-200+20
            texture{pigment{color White}}
        } 
    
  background{ color White}
  
  union{//whole body 
  union{//neck +,
  union{//spine +,
  union{//thumb+
  union{//hands,larmsboth,uarms,shoulders,chest,pelvis both legs
  union{//larmsboth,uarms,shoulders,chest,pelvis both legs
 union{//uarms,shoulders,chest,pelvis both legs 
 union{   //shoulders,chest,pelvis both legs
 union{   //chest,pelvis,legs
  union{  //pelvis,legs
   
   union{ //left leg
   
   object{lfoot translate<0,-200+20,55>}
   object{lleg }
   object{lthigh translate<0,185+200,0>}
    
    }
              
    
     union{//right leg
   
   object{rfoot translate<0,-200+20,55>}
   object{rleg }
   object{rthigh translate<0,185+200,0>}
           translate<120,0,0>
      }
      
      
     object{pelvis translate <60,200+400-15+75-50,0>}
     
     
     }
     
     object{chest translate<60,200+400-15+150+150+15+15-200+155,0>}
    } 
    
    
    
    object{shldrs translate <60-155+155,200+400-15+150+150+15+15+230-100-10,0>}
    
    }
    
    object{luarm translate<60-155-40+40+10,200+400-15+150+150+15+15+230-100-120-10,0>}
     object{ruarm translate<60-155-40+40+10+155*2-20,200+400-15+150+150+15+15+230-100-120-10,0>}
     }
     
    object{llarm translate <60-155-40+40+10,200+400-15+150+150+15+15+230-100-120-115-120-10,0 >}
    object{llarm translate <60-155-40+40+10+155*2-20,200+400-15+150+150+15+15+230-100-120-115-120-10,0 >} 
    }
    
    object{lhand translate <60-155-40+40+10,200+400-15+150+150+15+15+230-100-120-115-120-10-115-70-5+20,0>}
    object{rhand translate <60-155-40+40+10+155*2-20,200+400-15+150+150+15+15+230-100-120-115-120-10-115-70-5+20,0>}
    }
    object{lthumb translate <60-155-40+40+10-20,200+400-15+150+150+15+15+230-100-120-115-120-10-115-70-5+20-70-50+70+40,10>}
    object{rthumb translate <60-155-40+40+10+155*2-20+20,200+400-15+150+150+15+15+230-100-120-115-120-10-115-70-5+20-70-50+70+40,10>} 
    }
    object{neck translate < 60-155+155,200+400-15+150+150+15+15+230-100-10+50+10,0 >}
    }
    object{head translate < 60-155+155,200+400-15+150+150+15+15+230-100-10+50+10+20+100,0 >}
    }
    object{nose  translate < 60-155+155,200+400-15+150+150+15+15+230-100-10+50+10+20+100+30+10,55 >}
    
    object{plane1} 
    translate<0,-700,0>
    texture {pigment{color Gray85}}
    
   
    }
    
   