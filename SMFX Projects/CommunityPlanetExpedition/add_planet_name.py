from os import walk

mypath = "planetTerrainScripts~/"

filenames = next(walk(mypath), (None, None, []))[2]  # [] if no file

for i in range(0,len(filenames)):
    pname = filenames[i][0:len(filenames[i])-12]

    file =open('planetTerrainScripts~/'+filenames[i], 'r')
    
    filelist = "#Description added through Python script\n"
    filelist += '\nstring16 planet_name "'+pname+'"\n'
    
    filelist += file.read()+"\n"
    file.close()
    
    print(pname)
    
    file_test = open('planetTerrainScripts~/'+filenames[i], 'w')

    file_test.write(filelist)
    file_test.close()
