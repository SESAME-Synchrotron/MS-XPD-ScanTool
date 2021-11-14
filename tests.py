import sys
import os


def check(exp,msg):
    if not exp:
        print(msg)
        while True:
            reply = input("Do you want to continue?(Y/N)\n")
            if reply in ["y","n","Y","N"]:
                reply = str(reply).lower()                
                if reply =='y':
                    return
                elif reply == "n":
                    sys.exit()

#check(1==1,"invalid")

def isfloat(fval):
	try:
		return True,float(fval)
	except:
		return False,None

def kint():
    while True:
        try:
            print("hello")
        except KeyboardInterrupt as e:
            print("keeb intrupt")
            break

print(isfloat('x'))