#!/usr/bin/python
import sys
import os

if len(sys.argv) < 2:
    print sys.argv[0] + " [fileName] [compiler flags] [linker flags]\ncreates the file [filename] and makes it into a makefile for the subdirectories src and obj"
    sys.exit()

mfile = open(sys.argv[1], "w")

print("writing to file " + sys.argv[1])

mfile.write("CC = gcc\nLC=g++\nCFLAGS=" + sys.argv[2] + "\nLFLAGS=" + sys.argv[3] + "\n\nall : " + sys.argv[4] + "\n")
print("compiler flags are: " + sys.argv[2])
print("linker flags are: " + sys.argv[3])
doWrite = False
objs = str()
objPath = str()
if len(sys.argv) < 6:
    objPath = "./obj/release/"
    print("building release makefile")
else:
    objPath = "./obj/debug/"
    print("build debug makefile")

for root, dirs, files in os.walk("./src"):
    for a in files:
        a = "./src/"+a
        if a.find(".h") != -1:
            tot = objPath + a[6:-1] + "o : " + a[0:-1] + "cpp " + a + " "
            if not os.path.isfile(a):
                print("no such file as " + a)
                continue
            tfile = open(a, "r")
            for s in tfile:
                if s == "\n":
                    tot = tot + "\n"
                    break
                pos1 = s.find("\"")
                if pos1 == -1:
                    continue
                pos2 = s.find("\"", pos1+1)
                tot = tot + "./src/" + s[pos1+1:pos2] + " "
            tfile.close()
            finalOutput = tot + "\t$(CC) $(CFLAGS) " + a[0:-1] + "cpp -o " + objPath + a[6:-1] + "o\n"
            mfile.write(finalOutput)
            print(tot + "\tline written")
            objs = objs + objPath + a[6:-1] + "o "
        #elif a.find(".cpp") != -1:
            #mfile.write(objPath + a[6:-3] + "o : " + a + "\n\t$(CC) $(CFLAGS) " + a + " -o " + objPath + a[6:-3] + "o\n")
            #objs = objs + objPath + a[6:-3] + "o "

mfile.write(sys.argv[4] + " : " + objs + "\n\t$(LC) " + objs + " $(LFLAGS) -o" + sys.argv[4])
mfile.close()
print("makefile compiled")
