from os import walk

path1 = "LevelEditor_Saves~/"
mypath = "planetTerrainScripts~/"

filenames = next(walk(path1), (None, None, []))[2]  # [] if no file

for i in range(0,len(filenames)):
    pname = filenames[i][0:len(filenames[i])-10]
    file =open('mod_planets/'+pname+'.prop.prop_t', 'r')
    filelist = file.read()
    file.close()
    
    print(pname)
    
    file_test = open('planetTerrainScripts~/'+pname+'.prop.prop_t', 'w')

    file_test.write(filelist)
    file_test.close()
