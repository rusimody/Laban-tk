import os;
x=input("enter the value to speed down animation by multiple of 1/100th of second ")
def fun(x):
	
	#os.system("povray fred.ini");
	os.system("animate -delay "+str(x)+" fredexp*.png");

fun(x)
