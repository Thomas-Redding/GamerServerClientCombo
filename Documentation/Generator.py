# f = open('../GamerServerClientCombo/workfile', 'w')

from os import listdir
from os.path import isfile, join

class HeaderFile:
    def __init__(self, fileName, txt):
        self.fileName = fileName
        lastPound = txt.rfind("#")
        txt = txt[0:lastPound]
        lastPound = txt.rfind("#")
        txt = txt[lastPound:]
        firstNewLine = txt.find('\n')
        txt = txt[firstNewLine:]
        txt = txt.replace('\t', "&nbsp;&nbsp;&nbsp;&nbsp;")
        txt = txt.replace('\n', "<br/>")
        self.str = txt

pathToCode = "../GamerServerClientCombo"

files = [ f for f in listdir(pathToCode) if isfile(join(pathToCode,f)) ]

headers = []
for x in files:
    if x[-4:] == ".hpp":
        f = open("../GamerServerClientCombo/" + x, 'r')
        headers.append(HeaderFile(x[0:-4], f.read()))

for x in headers:
    f = open(x.fileName+".html", "w")
    f.write(x.str)
