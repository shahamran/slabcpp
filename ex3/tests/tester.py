import os, sys
import time

print("Checking files...")

if not os.path.isfile("Matrix.hpp"):
	print("No Matrix.hpp found.")
	sys.exit(1)

print("Extracting school solution...")

SSF="~slabcpp/www/ex3"

os.system("tar xvf {}/ex3_schoolSol.tar".format(SSF))

print("Extracting driver files...")

os.system("tar xvf {}/ex3_files.tar".format(SSF))

EX="GMD"

os.system("rm -rf Tests/*")

if not os.path.isdir("Tests") or os.listdir("Tests") == []:
	print("Generating test cases...")
	os.system("python genGood.py 100 100 100")
	os.system("python genBad.py 30 30 30")

print("Compiling...")

os.system("make clean && make GMD")
if not os.path.isfile("GMD"):
	print("Compilation failed.")
	sys.exit(1)

if not os.path.isdir("results_out"):
	os.system("mkdir results_out")
if not os.path.isdir("diff"):
	os.system("mkdir diff")
if not os.path.isdir("school_out"):
	os.system("mkdir school_out")

failed = 0
succeeded = 0

os.system("rm -f results_out/*")
os.system("rm -f diff/*")

print("Running tests...")

if os.path.isfile("faliedTests.txt"):
	os.system("rm -rf failedTests.txt")
failedFile = open("failedTests.txt", "w+")

for test in os.listdir("Tests"):
	os.system("GenericMatrixDriver < Tests/{} > school_out/{}".format(test, test))
	os.system("{} < Tests/{} > results_out/{}".format(EX, test, test))
	os.system("diff results_out/{} school_out/{} > diff/diff_{}".format(test, test, test))
	if os.stat("diff/diff_{}".format(test)).st_size != 0:
		print("Failed test: {}".format(test))
		failedFile.write("Failed test: {}".format(test))
		failed += 1
	else:
		succeeded += 1
		continue

failedFile.close()
			
if (failed != 0):
	print("\nFAILED {}\nPASSED {}\n".format(failed, succeeded))
else:
	print("\nPASSED ALL ({})\n".format(succeeded))

print("Running parallel check...")
print("Compiling...")

os.system("make PAR")
if not os.path.isfile("PAR"):
	print("Compilation failed.")
	sys.exit(1)

print("\nSmall:\n")
os.system("PAR ~slabcpp/www/sets/small.txt")

print("\nBig:\n")
os.system("PAR ~slabcpp/www/sets/big.txt")

#print("\nRunning coding style check...")
#os.system("~slabcpp/www/codingStyleCheck Matrix.hpp")

