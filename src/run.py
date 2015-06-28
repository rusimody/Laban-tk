import subprocess
import os
# runs led to create lbn file
p = subprocess.Popen("./led")
p.wait()
# runs lintel to create .n file
p = subprocess.Popen("./lintel")
p.wait()

# gets the name of .n file to be processed
# removes allow commands from the file which cause trobule
userinput = raw_input("Enter the name of .n file created Eg(test.lbn_000.n)" )
f = open(userinput,"r")
lines = f.readlines()
f.close()
f = open(userinput,"w")
for line in lines:
	if 'allow' not in line:
		f.write(line)

f.close()	

# runs nudes with our .n file as input		
p = subprocess.Popen(['./nudes',userinput])
p.wait()

# go into the newly created folder and create a gif using imagemagick
folder = userinput[:-1] + "tmp"
currentpath = os.getcwd()
path = currentpath+"/"+folder
os.chdir(path)
initials = userinput[:5]
animate = "convert -delay 10 -loop 0 "+initials+"*.ppm animation.gif"
print (animate)
p = subprocess.Popen(animate,shell=True)
p.wait()
print("All done!!!! find animation.gif in "+folder+" folder")


