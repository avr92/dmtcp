import os
cid = []
with open("file","r") as fd:
	line = fd.readline()
	for num in fd.readlines():
		i = 0
		while i < 12:
			cid += num[i]
			i+=1
fd.close()
os.system("rm -rf file")
c_id = ""
for i in cid:
	c_id += i
fd = open("filep","w")
fd.write(c_id)
fd.close()
