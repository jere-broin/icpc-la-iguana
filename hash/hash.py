import sys, hashlib
code = open(sys.argv[1]).read()
print(hashlib.md5("".join(code.split()).encode()).hexdigest()[:6])