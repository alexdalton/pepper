import subprocess
import os
import string
import re
from optparse import OptionParser

executable_name = ["ourfact", "ourgcf"]
c_file = ["factorial.c", "gcf.c"]
test_name = ["fact", "gcf"]
offset = [9, 29]

def testTheirs(results, studentDir, examDay):
    subprocess.call(["rm", "-f", executable_name[examDay]])
    results.write("***** Compilation Results *****\n")
    compile_results = subprocess.Popen(["gcc", "-g", "-Wall", "-ansi", "-o", executable_name[examDay],
                                        c_file[examDay]], stdout=subprocess.PIPE,
                                        stderr=subprocess.PIPE).communicate()
    results.write(compile_results[0])
    if compile_results[1]:
        results.write(compile_results[1])
        return

    for i in range(4):
        solution = open("testFiles/{0}{1}sol".format(test_name[examDay], i), "r")
        results.write("***** Test{0} *****\n".format(i))
        sol = solution.read()
        results.write("Ours:\n{0}".format(sol))
        subprocess.call("timeout 5s ./{0} <testFiles/{1}{2} >testFiles/myout{2}".format(executable_name[examDay], test_name[examDay], i), shell=True)
        if os.path.getsize("testFiles/myout{0}".format(i)) > 600:
            results.write("    Theirs: Unusually large output file (see testFiles/myout{0})\n".format(i))
            continue
        theirs = open("testFiles/myout{0}".format(i), "r")
        their_solution = theirs.read()
        results.write(" Theirs:\n{0}\n".format(their_solution[offset[examDay]:]))
        solution.close()

parser = OptionParser()
parser.add_option("-b", "--examdir", dest="examdir",
                  help="directory of pulled student MPs")
parser.add_option("-r", "--roster", dest="roster",
                  help="student roster file", metavar="FILE")
parser.add_option("-d", "--day", dest="examDay",
                  help="exam day (1 or 2)")

(options, args) = parser.parse_args()

if options.examdir is None or options.roster is None:
    parser.print_help()
    exit(1)

examDirectory = os.path.abspath(options.examdir)

if not os.path.exists(examDirectory):
    print("{0} does not exist".format(examDirectory))
    exit(1)

try:
    rosterPath = os.path.abspath(options.roster)
    roster = open(rosterPath, "r")
except IOError as e:
    print("I/O error({0}): {1} {2}".format(e.errno, rosterPath, e.strerror))
    exit(1)

cwd = os.getcwd()
for student in roster:
    studentDir = os.path.join(examDirectory, string.rstrip(student, '\n'))
    os.chdir(studentDir)
    print("testing in " + os.getcwd())
    subprocess.call(["cp", "-r", "/home/adalton2/pepper/exam1/testFiles/", studentDir])
    results = open("results.txt", "w")

    testTheirs(results, studentDir, int(options.examDay) - 1)

    results.close()

os.chdir(cwd)
