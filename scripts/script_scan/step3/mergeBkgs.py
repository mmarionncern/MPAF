import os, sys, math,subprocess

def retrieveSamples(inputFile):

    samples=[]

    ifile=open(inputFile,'r')
    lines=ifile.read().splitlines()

    for line in lines:
        
        if 'selected'in line or 'denominator' in line:
            sample=line.split()[1]
            if sample not in samples:
                samples.append(line.split()[1])

    #print "samples ", samples
    return samples


def retrieveCategs(inputFile):

    ifile=open(inputFile,'r')
    lines=ifile.read().splitlines()

    categs=[]
    for line in lines:
        if 'categ\t' in line and not 'endcateg' in line:
            categs.append(line[6:])
            #print line[6:]

    return categs


def retrieveYields(inputFile, samples):

    ifile=open(inputFile,'r')
    lines=ifile.read().splitlines()

    goodLines={}
    totYield={}
    totNGen={}
    totUnc={}
    
    #samples=[]

    init=False
    initSel=False
    curCateg=""
    
    for line in lines:
        
        if 'categ\t' in line and not 'endcateg' in line:
            init=False
            curCateg=line[6:]
            goodLines[ curCateg ]={}
            for sample in samples:
                goodLines[ curCateg ][sample]=""

            if 'global_' not in curCateg: #just for initialization
                totYield[curCateg]={}
                totNGen[curCateg]={}
                totUnc[curCateg]={}
                
                #if init:
                for sample in samples:
                    totYield[curCateg][sample]=0
                    totNGen[curCateg][sample]=0
                    totUnc[curCateg][sample]=0

        if 'selected'in line or 'denominator' in line: 
            sample=line.split()[1]
            
            #if not init:
            #    #samples.append(sample)
            #    totYield[curCateg][sample]=0
            #    totNGen[curCateg][sample]=0
            #    totUnc[curCateg][sample]=0

        if 'selected' in line or 'denominator' in line:
            sample=line.split()[1]
            
            if 'global_' in curCateg and 'BR' not in curCateg and 'Fake' not in curCateg and 'mId' not in curCateg and "WZCR" not in curCateg and "Baseline" not in curCateg:
                goodLines[ curCateg ][sample]=line
                if 'Unc' not in curCateg:
                    if sample in totYield['global'].keys():
                        totYield['global'][sample] += float(line.split()[2])
                        totNGen['global'][sample]  += float(line.split()[3])
                        totUnc['global'][sample]   += float(line.split()[4])*float(line.split()[4])
                else:
                    p=curCateg.find('Unc')
                    redCateg='global\t'+curCateg[p:]
                    if sample in totYield[redCateg].keys():
                        totYield[redCateg][sample] += float(line.split()[2])
                        totNGen[redCateg][sample]  += float(line.split()[3])
                        totUnc[redCateg][sample]   += float(line.split()[4])*float(line.split()[4])

            elif 'global_' in curCateg:
                #print line, goodLines[ curCateg ].keys(), curCateg
                if sample in goodLines[ curCateg ].keys(): 
                    #print "---> pass"
                    goodLines[ curCateg ][sample]=line


        if 'endcateg' in line and not init:
            init=True

    #addition of empyt categs
    for k in goodLines.keys():
        for s in samples:
            if s not in goodLines[k].keys():
                print "====>>> ", k, s
                goodLines[k][s]='\tselected\t'+s+'\t0\t0\t0'
            else:
                if goodLines[k][s]=="":
                    goodLines[k][s]='\tselected\t'+s+'\t0\t0\t0'

    for i in totYield.keys():
        for j in totYield[i].keys():
            totUnc[i][j] = math.sqrt(totUnc[i][j])
    
    return goodLines, totYield, totNGen, totUnc


def mergeYields(mainFile, addFile,outName):

    mainSamples=retrieveSamples(mainFile)
    addSamples=retrieveSamples(addFile)

    mainLines, mainYields, mainNGen, mainUnc=retrieveYields(mainFile, mainSamples)
    addLines,  addYields,  addNGen,  addUnc=retrieveYields(addFile, addSamples)

    mainCategs=retrieveCategs(mainFile)
    addCategs=retrieveCategs(addFile)

    ofile = open(outName,'w')

    # first, complete the category list
    allCategs=mainCategs
    for cat in addCategs: 
        if cat not in allCategs: allCategs.append(cat)
    
    for cat in allCategs:

        ofile.write('categ\t'+cat+'\n')
     
        if 'global_' not in cat : #overall yields and values
            if cat in mainYields.keys():
                for s in mainYields[cat].keys():
                    line='\tselected\t'+s+'\t'+str(mainYields[cat][s])+'\t'+str(mainNGen[cat][s])+'\t'+str(mainUnc[cat][s])+'\n'
                    ofile.write(line)
            else:
                for s in mainYields['global'].keys():
                    line='\tselected\t'+s+'\t'+str(mainYields['global'][s])+'\t'+str(mainNGen['global'][s])+'\t'+str(mainUnc['global'][s])+'\n'
                    ofile.write(line)
            
            if cat in addYields.keys():
                for s in addYields[cat].keys():
                    line='\tselected\t'+s+'\t'+str(addYields[cat][s])+'\t'+str(addNGen[cat][s])+'\t'+str(addUnc[cat][s])+'\n'
                    ofile.write(line)
            else:
                for s in addYields['global'].keys():
                    line='\tselected\t'+s+'\t'+str(addYields['global'][s])+'\t'+str(addNGen['global'][s])+'\t'+str(addUnc['global'][s])+'\n'
                    ofile.write(line)
        else:
            if cat in mainLines.keys():
                if len(mainLines[cat].keys())==0:
                    for s in mainYields['global'].keys():
                        ofile.write('\tselected\t'+s+'\t0\t0\t0\n')
                else:
                    for s in mainLines[cat].keys():
                        ofile.write(mainLines[cat][s]+'\n')
            else:
               p=cat.find('\t')
               redCat=cat[:p]
               if redCat in mainLines.keys():
                   if len(mainLines[redCat].keys())==0:
                       for s in mainYields['global'].keys():
                           ofile.write('\tselected\t'+s+'\t0\t0\t0\n')
                   else:
                       for s in mainLines[redCat].keys():
                           ofile.write(mainLines[redCat][s]+'\n')

            ### additionnal lines
            if cat in addLines.keys():
                if len(addLines[cat].keys())==0:
                    for s in addYields['global'].keys():
                        ofile.write('\tselected\t'+s+'\t0\t0\t0\n')
                else:
                    for s in addLines[cat].keys():
                        ofile.write(addLines[cat][s]+'\n')
            else:
                p=cat.find('\t')
                redCat=cat[:p]
                if redCat in addLines.keys():
                    if len(addLines[redCat].keys())==0:
                        for s in addYields['global'].keys():
                            ofile.write('\tselected\t'+s+'\t0\t0\t0\n')
                    else:
                        for s in addLines[redCat].keys():
                            ofile.write(addLines[redCat][s]+'\n')
          
        ofile.write('endcateg\t'+cat+'\n\n')


 
    ofile.close()






pipe = subprocess.Popen("ls " + sys.argv[2] + "*.dat", shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
ls = [l.strip("\n") for l in pipe.stdout.readlines()]
os.system("cp " + ls[0] + " " + sys.argv[1])
for i in range(1,len(ls)):
    if os.path.isdir(ls[i]): continue
    print "merging " + ls[i] + " into " + sys.argv[1]
    mergeYields(sys.argv[1], ls[i], sys.argv[1])


#/shome/mmarionn/MPAF/workdir/stats/SUSY3L/susy3lScanZZZ.dat
#/shome/mmarionn/MPAF/workdir/stats/SUSY3L/susy3lScanZZTo4L.dat
#mergeYields("/shome/mmarionn/MPAF/workdir/stats/SUSY3L/susy3lScanZZZ.dat",
#            "/shome/mmarionn/MPAF/workdir/stats/SUSY3L/susy3lScanDoubleMuon_Run2015D_PromptV4_runs_258159_260627.dat",
#            "test.txt")

#retrieveYields("/afs/cern.ch/user/m/mmarionn/workspace/private/MPAF/workdir/stats/SSDL2015/ssdlScan-1125-775-.dat")

#retrieveCategs("/afs/cern.ch/user/m/mmarionn/workspace/private/MPAF/workdir/stats/SSDL2015/ssdl2fb_Bkg.dat")
#retrieveYields("/afs/cern.ch/user/m/mmarionn/workspace/private/MPAF/workdir/stats/SSDL2015/ssdl2fb_Bkg.dat")
















#mainFile=sys.argv[1]
#addFile=sys.argv[2]
#outName=sys.argv[3]

