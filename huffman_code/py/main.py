import sys

def usage():
    howto = """USAGE: ./[exec] flags [input filename] [output filename]
flags:
-e  encodes the input file
-d  decodes the input file
Flags are required
The resulting file is saved as [output filename]
NOTE: both files must be in a .txt format"""
    print(howto)

if len(sys.argv) != 4:
    usage()
    sys.exit()

inf = open(sys.argv[2])
outf = open(sys.argv[3], "w")

if sys.argv[1] == "-e":
    pass
elif sys.argv[1] == "-d":
    pass

inf.close()
outf.close()
