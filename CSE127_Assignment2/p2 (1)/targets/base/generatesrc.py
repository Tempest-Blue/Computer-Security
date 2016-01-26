#!/usr/bin/python

import random
import shutil

# Grab sid

fsid = open("SID",'r')
lines = fsid.readlines()
lines = [line for line in lines if line.strip()]
sid = sorted(lines)[0].strip()
fsid.close()
if len(sid) < 8 or sid[0:10] == "STUDENT_ID":
    print "Please put your student ID and name in the SID file."
    print "Example: A12345678 Joe McMillan."
    exit(1)

random.seed(sid)

# Generate basic target
def gen_target(num,reps):
    if int(num) != 3:
        ft = open("./base/target"+num+".c",'r')
        fto = open("target"+num+".c",'w')
    else:
        ft = open("./base/target"+num+".cc",'r')
        fto = open("target"+num+".cc",'w')


    t = ft.readlines()
    ft.close()
    for l in t:
        for (v,t) in reps:
            l = l.replace(v,t)
        fto.write(l)
    fto.close()



# Setup target1
t1_replace = "T1BUFFER"
t1_val = str(40 + random.randrange(1,200))

# Setup target2
t2_replace_1 = "T3_WIDGET_NUMDUBS"
t2_val_1 = str(2**(random.randrange(2,4)) - 1)
t2_replace_2 = "T3_MAXWIDGETS"
t2_val_2 = str(513 + random.randrange(1,401))

# Setup target3
t3_replace = "T3BUFFER"
t3_val = str(40 + random.randrange(2,100))
t3_replace_2 = "T3_LT_BUFFER"
t3_val_2 = str(int(t3_val) - 1)

# Generate targets
gen_target("0", [])
gen_target("1",[(t1_replace,t1_val)])
gen_target("2",[(t2_replace_1,t2_val_1),(t2_replace_2,t2_val_2)])
gen_target("3",[(t3_replace,t3_val), (t3_replace_2, t3_val_2)])

