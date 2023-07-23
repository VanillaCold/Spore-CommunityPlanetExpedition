from os import walk

mypath = "LevelEditor_Saves~"

filenames = next(walk(mypath), (None, None, []))[2]  # [] if no file

for i in range(0,len(filenames)):
    pname = filenames[i][0:len(filenames[i])-10]

    if pname[len(pname)-5:len(pname)] != "__Civ":
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
        file_test = open('StarterWorlds/'+pname+".prop.prop_t", 'w')
        file_test.write(filelist)
        file_test.close()

    #file_test = open('StarterWorlds/AB_'+pname+"_2222.prop.prop_t", 'w')
    #file_test.write(filelist)
    #file_test.close()

    #file_test = open('StarterWorlds/YZ_'+pname+"_3333.prop.prop_t", 'w')
    #file_test.write(filelist)
   # file_test.close()

    #file_test = open('StarterWorlds/MN_'+pname+"_4444.prop.prop_t", 'w')
    #file_test.write(filelist)
    #file_test.close()
    
