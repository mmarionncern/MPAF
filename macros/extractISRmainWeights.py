import os, sys, math

def retrieveYields(inputFile, targetCateg):

    ifile=open(inputFile,'r')
    lines=ifile.read().splitlines()

    nEvt=0
    nGen=0
    nEvtErr=0
    sample=""

    init=False
    initSel=False
    curCateg=""
    
    output=[]

    for line in lines:
        
        if 'categ\t' in line and not 'endcateg' in line:
            curCateg=line[6:]
            if targetCateg != curCateg: #just for initialization
                continue
            
        if 'selected' in line:
            sample=line.split()[1]
            
            if targetCateg == curCateg:
                nEvt = float(line.split()[2])
                nGen = float(line.split()[3])
                nEvtErr = float(line.split()[4])*float(line.split()[4])
                output=[ nEvt, nGen, nEvtErr]

    if len(output)==0:
        output=[0,0,0]

    return sample, output


def getYields(mainFile):

    sample=""
    vals={}
    sample, vals["global_OffZBaseline"] = retrieveYields(mainFile,"global_OffZBaseline")
    sample, vals["global_OffZBaseline\tUncISRDo"] = retrieveYields(mainFile,"global_OffZBaseline\tUncISRDo")
    sample, vals["global_OffZBaseline\tUncisrUp"] = retrieveYields(mainFile,"global_OffZBaseline\tUncisrUp")
    sample, vals["global_OffZBaseline\tUncisrDo"] = retrieveYields(mainFile,"global_OffZBaseline\tUncisrDo")

    sample, vals["global_OnZBaseline"] = retrieveYields(mainFile,"global_OnZBaseline")
    sample, vals["global_OnZBaseline\tUncISRDo"] = retrieveYields(mainFile,"global_OnZBaseline\tUncISRDo")
    sample, vals["global_OnZBaseline\tUncisrUp"] = retrieveYields(mainFile,"global_OnZBaseline\tUncisrUp")
    sample, vals["global_OnZBaseline\tUncisrDo"] = retrieveYields(mainFile,"global_OnZBaseline\tUncisrDo")
  
    central=vals["global_OffZBaseline"][0]+vals["global_OnZBaseline"][0]
    reweight=vals["global_OffZBaseline\tUncISRDo"][0]+vals["global_OnZBaseline\tUncISRDo"][0]
    upVar=vals["global_OffZBaseline\tUncisrUp"][0]+vals["global_OnZBaseline\tUncisrUp"][0]
    doVar=vals["global_OffZBaseline\tUncisrDo"][0]+vals["global_OnZBaseline\tUncisrDo"][0]
    #print central, reweight, upVar, doVar, sample
    if reweight==0 or upVar==0 or doVar==0:
        line=sample+"\t1\t1\t1\n"
    else:
        line=sample+"\t"+str(central/reweight)+"\t"+str(central/upVar)+"\t"+str(central/doVar)+"\n"
    print line
    return line



def makeDB(signal):

    path="/mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan/workdir/stats/SUSY3L/"

    ofile = open( "/mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan/workdir/database/"+signal+"ISR.db",'w')

    #header
    ofile.write("//vs\tc\te\te\n")
    ofile.write("//keep this header format!!\n")

    from os import listdir
    from os.path import isfile, join
    onlyfiles = [f for f in listdir(path) if isfile(join(path, f)) and f[-3:]=="dat" and f[:10]=="3l_scanSig" and signal in f ]

    for f in onlyfiles:
        line = getYields(path+f)
        ofile.write(line)


    ofile.close()
    

#makeDB("T5qqqqVV_noDM")

getYields("/mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan/workdir/stats/SUSY3L/3l_scanSig_T5qqqqVV_noDM_mG_1000_mN_1.dat")
