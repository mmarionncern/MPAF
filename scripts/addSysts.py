import os, sys, math


def retrieveCategs(inputFile):

    ifile=open(inputFile,'r')
    lines=ifile.read().splitlines()

    categs=[]
    tmpS=""
    categ=""
    for line in lines:
        if 'categ\t' in line and not 'endcateg' in line:
            categ=line[6:]
            #print line[6:]
        if not 'categ\t' in line and not 'endcateg' in line:
            tmpS=line

        if 'endcateg' in line and tmpS!="":
            #print categ
            categs.append(categ)
        if 'endcateg' in line:
            tmpS=""
            categ=""

    return categs


def copyFile(inputFile, categs, ofile):
    
    ifile=open(inputFile,'r')
    lines=ifile.read().splitlines()
    write=False
    for line in lines:
        #print write,line[6:] in categs, "====> ", line
        if 'categ\t' in line and not 'endcateg' in line and line[6:] in categs:
            ofile.write(line+"\n")
            write=True
            
        if 'endcateg' in line and write:
            ofile.write(line+"\n\n")
            write=False

        
        if write and 'categ' not in line:
            ofile.write(line+"\n")

def copyFiles(mainFile, addFile, outName=""):

    mainCategs=retrieveCategs(mainFile)
    addCategs=retrieveCategs(addFile)
    

  #  print mainCategs

   # print addCategs

    ofile = open(outName,'w')


    copyFile(mainFile, mainCategs, ofile)
    copyFile(addFile, addCategs, ofile)
    ofile.close()


copyFiles(sys.argv[1], sys.argv[2], sys.argv[3])

#copyFiles("/mnt/t3nfs01/data01/shome/mmarionn/MPAF/workdir/stats/SSDL2015/syst_TTZ_LO.dat","/mnt/t3nfs01/data01/shome/mmarionn/MPAF/workdir/stats/SSDL2015/syst_test.dat","test.txt")
