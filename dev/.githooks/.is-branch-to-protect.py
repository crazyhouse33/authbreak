#!/usr/bin/python3
import subprocess

with open("dev/protected-branchs",'rb') as f:
        branchList=f.read().splitlines()

currentBranch= subprocess.check_output(['git', 'rev-parse', '--abbrev-ref', 'HEAD']).strip()

if currentBranch in branchList:
    print (1)
else:
    print (0)

