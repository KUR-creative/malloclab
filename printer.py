import subprocess 
import fileinput

RED = '\033[0;31m'
GREEN = '\033[0;32m'
LGREEN = '\033[1;32m'
YELLOW = '\033[0;33m'
LYELLOW = '\033[1;33m'
CYAN = '\033[0;36m'
LCYAN = '\033[1;36m'
NOCOL = '\033[0m'

def headColorPrinter(line, color):
    subprocess.call([ 'printf', color + line[:12] + NOCOL + line[12:] ])

def isStrInLine(line, string):
    return (line.find(string) != -1) # line has string!

flen = len('FAILED')
for line in fileinput.input():
    if isStrInLine(line, '[  FAILED  ]') or isStrInLine(line, '[  ERROR   ]'): 
        headColorPrinter(line, RED)
    #elif isStrInLine(line, '[ RUN      ]'):
        #pass
        #subprocess.call(['printf', NOCOL + line])
    elif isStrInLine(line, '[       OK ]'):
        headColorPrinter(line, LGREEN)
        pass
    elif isStrInLine(line, '[==========]'):
        headColorPrinter(line, CYAN)
    elif isStrInLine(line, '[  SKIPPED ]'):
        headColorPrinter(line, LYELLOW)
    else:
        subprocess.call(['printf', NOCOL + line])
    pass

subprocess.call(['printf', NOCOL])
#subprocess.call(['printf', 'I ' + RED + 'love' + NOCOL +' Stack Overflow\n'])
#subprocess.call(['printf', RED + line + NOCOL + line])
