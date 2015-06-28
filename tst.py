import os;
x=input("enter the value to speed down animation by multiple of 1/100th of second(enter 12 for normal speed)(enter 0 for max speed) ")
def fun(x):
	
	os.system("povray fred.ini");
	os.system("animate -delay "+str(x)+" fredexp*.png");

fun(x)
