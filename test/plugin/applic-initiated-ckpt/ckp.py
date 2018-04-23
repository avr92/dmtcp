import os
cid = []


os.system("docker ps > file")
a = ""
with open("file","r") as fd:
	line = fd.readline()
	j = 0
	while j < 10:
		for num in fd.readlines():
			i = 0
			while i < 12:
				a += num[i]
				i+=1
			cid.insert(j,a)
			a = ""
		j+=1
fd.close()

os.system("rm -rf file")
fd = open("file","a")
j = 0
while j < 10:
	try:
		cmd_create = []
		cmd_create.append("docker checkpoint create ")
		cmd_rm = []
		cmd_rm.append("docker checkpoint rm ")
		cmd_rm.append(str(cid[j]))
		cmd_create.append(str(cid[j]))
		cmd_rm.append(" ckp")
		cmd_create.append(" ckp")
		cmd_rm.append(str(j).rstrip())
		cmd_create.append(str(j).rstrip())
		rm = ''.join(cmd_rm)
		cre = ''.join(cmd_create)
		os.system(rm)
		ret = os.system(cre)
		if ret == 0:
			fd.write(str(cid[j])+" ckp"+str(j)+"\n")
		j += 1
	except IndexError:
		exit()
