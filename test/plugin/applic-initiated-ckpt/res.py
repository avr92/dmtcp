import os
import subprocess as subp

cmd_res = []
tmp = "docker start --checkpoint "
with open("file","r") as fd:
	for line in fd:
		cmd_res = []
		cid, ckp = line.split(" ")
		ckp = ckp.rstrip()
		cmd_res.append(str(ckp).rstrip())
		cmd_res.append(" ")
		cmd_res.append(str(cid))
		cmd = ''.join(cmd_res)
		cmd = tmp + cmd
		subp.check_call(str(cmd), shell=True)
