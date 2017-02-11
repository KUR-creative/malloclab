'''

# pass cmd arguments

import argparse
parser = argparse.ArgumentParser(description='ADD YOUR DESCRIPTION HERE')
parser.add_argument('-i','--input', help='Input file name',required=True)
parser.add_argument('-o','--output',help='Output file name', required=True)
args = parser.parse_args()

print("I: %s" % args.input)
print("O: %s" % args.output)


# run sh script in py

import subprocess 
subprocess.call(["ps", "-l"])

print("---------------------");


# get stdout output

proc = subprocess.Popen('ps', stdout=subprocess.PIPE)
tmp = proc.stdout.read()

print(tmp);


# file to string

f = open("out.txt");
string = f.read();

print(string);


# string to array
arr = string.split('\n');
print(arr);

'''

import subprocess 

RED = '\033[0;31m'
LGREEN = '\033[1;32m'
NOCOL = '\033[0m'

resultArr = [] # (trace-name, is-correct?, score)
traceArr = [
    #'amptjp-bal.rep',
    #'binary-bal.rep',
    #'binary2-bal.rep',
    #'cccp-bal.rep',
    #'coalescing-bal.rep',
    #'cp-decl-bal.rep',
    #'expr-bal.rep',
    #'random-bal.rep',
    #'random2-bal.rep',
    #'realloc-bal.rep',
    #'realloc2-bal.rep',
    'short1.rep',
    'short2.rep',
]


i = 0
for trace in traceArr:
    proc = subprocess.Popen(["./mdriver", "-vga", "-f", "traces/" + trace], stdout=subprocess.PIPE)
    tmpstr = proc.stdout.read()
    arr = tmpstr.split('\n')

    #print(arr[-4])
    is_correct = int(arr[-3].split(':')[1])
    
    score = int(arr[-2].split(':')[1])
    resultArr.append( (trace, bool(is_correct), score, arr[-4]) )

    i += 1


print("\nfile\t\t\tvaiid?\tscore")
print("-------------------------------------")

scoreSum = 0 
isSuccess = True
for result in resultArr:
    if result[1] == False:
        print("{0}\t\t{1}\t - ".format(result[0][:15], result[1]))
    else:
        print("{0}\t\t{1}\t{2}".format(result[0][:15], result[1], result[2]) + "\t" + result[3][10:])
    scoreSum += result[2]
    isSuccess = (isSuccess and result[1])

effectiveness = float(scoreSum) / float(100*len(traceArr)) * 100
print("-------------------------------------")
print("score_sum:  " + str(scoreSum)) 
print("percentage: " + str(effectiveness) + " %")

if isSuccess:
    subprocess.call([ 'printf', LGREEN + "\t    SUCCESS!\n" + NOCOL ])
else:
    subprocess.call([ 'printf', RED + "\t    FAIL\n" + NOCOL ])
