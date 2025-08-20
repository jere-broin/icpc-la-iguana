# "pre" file are generator parameters
# counterexample is stored in "in"
from os import system as sys
it=10000
for _ in range(it):
	sys("./c<pre>in")	#./c = generator
	sys("./a<in>o")		#./a = solution
	sys("./b<in>o2")	#./b = brute force
	x=open("o","r").read().strip().split()
	y=open("o2","r").read().strip().split()
	if x!=y:
		print("FAILED!!!!!")
		exit(0)
	print("ok",_+1)