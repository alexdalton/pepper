import subprocess
import os
import string
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-b", "--mpdir", dest="mpdir",
                  help="directory of pulled student MPs")
parser.add_option("-r", "--roster", dest="roster",
                  help="student roster file", metavar="FILE")

(options, args) = parser.parse_args()

if options.mpdir is None or options.roster is None:
    parser.print_help()
    exit(1)

mpDirectory = os.path.abspath(options.mpdir)

if not os.path.exists(mpDirectory):
    print("{0} does not exist".format(mpDirectory))
    exit(1)

try:
    rosterPath = os.path.abspath(options.roster)
    roster = open(rosterPath, "r")
except IOError as e:
    print("I/O error({0}): {1} {2}".format(e.errno, rosterPath, e.strerror))
    exit(1)

cwd = os.getcwd()
for student in roster:
    studentDir = os.path.join(mpDirectory, string.rstrip(student, '\n'))
    os.chdir(studentDir)
    subprocess.call(["cp", "/home/adalton2/pepper/MP4/gold/printBinary.o", os.path.join(studentDir, "printBinary.o")])
    subprocess.call(["cp", "/home/adalton2/pepper/MP4/distribution/Makefile", studentDir])
    results = open("results.txt", "w")
    results.write("***** Compilation Results *****\n")
    compile_results = subprocess.Popen(["make"], stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
    results.write(compile_results[0])
    if compile_results[1]:
        results.write(compile_results[1])
    results.close()

os.chdir(cwd)
