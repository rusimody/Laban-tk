import subprocess
import os
# runs led to create lbn file
p = subprocess.Popen("./led")
p.wait()
# runs lintel to create .n file
p = subprocess.Popen("./lintelm")
p.wait()


userinput = raw_input("Enter the name of .n file created Eg(test.lbn_000.n)" )
f = open(userinput,"r")
lines = f.readlines()
f.close()
f = open(userinput,"w")
for line in lines:
	if 'floor' not in line:
		f.write(line)
	
f.close()

f = open(userinput,"r")
lines = f.readlines()
f.close()
f = open(userinput,"w")
for line in lines:
	if 'bdx' not in line:
		f.write(line)
	
f.close()


f = open(userinput,"r")
lines = f.readlines()
f.close()
f = open(userinput,"w")
for line in lines:
	if 'brdz' not in line:
		f.write(line)
	
f.close()


print("Enter the name of .n file")
p = subprocess.Popen("./lintel")
p.wait()	

