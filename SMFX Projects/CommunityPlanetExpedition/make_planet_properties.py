from os import walk

mypath = "planetTerrainScripts~/"

filenames = next(walk(mypath), (None, None, []))[2]  # [] if no file

for i in range(0,len(filenames)):
    pname = filenames[i][0:len(filenames[i])-12]
    filelist = "#Generated through Python script"
    filelist += "\nuint32 CivScenario hash("+pname+")"
    filelist += "\nuint32 CreatureScenario hash("+pname+")"
    filelist += "\nbool FirstGroup true"
    filelist += "\nuint32 PlanetIcon hash("+pname+")"
    filelist += "\nuint32 SpaceScenario hash("+pname+")"
    filelist += "\nuint32 TribeScenario hash("+pname+")"
    filelist += '\nstring16 planetscriptDescription "'+pname+'"'
    filelist += "\nuint32 terrainscript hash("+pname+")"
    filelist += "\nbool 0xEA288A88 false"
    print(filelist)
    file_test = open('StarterWorlds/'+filenames[i], 'w')
    file_test.write(filelist)
    file_test.close()
