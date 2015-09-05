import os
import time

# make necessary files
if not os.path.isdir("results_out"):
    os.system("mkdir results_out")
if not os.path.isdir("diff"):
    os.system("mkdir diff")
'''
# deleting MIR and recreating it
if not os.path.exists("Makefile") or os.path.exists("makefile"):
    print("No make file found!\nexiting...")
    exit()
elif os.path.exists("MIR"):
    os.system("rm -f MIR")

os.system("make")
'''
if not os.path.exists("MIR"):
    print("couldn't make MIR file!\nexiting...")
    exit()

failed = 0
succeeded = 0
# deleting all previous data created
os.system("rm -f results_out/*")
os.system("rm -f diff/*")

#copying new data
for i in range(1, 4):
    for j in range(1, 4):
        for k in range(1, 9):
            os.system("./MIR tests_files/songs_{}.in tests_files/parameters_{}.in tests_files/queries_{}.in > results_out/result_{}_{}_{}".format(i, j, k, i, j, k, i, j, k))
            os.system("diff results_out/result_{}_{}_{}  school_out/school_{}_{}_{} > diff/diff_{}_{}_{""}".format(i,j, k,i,j,k,i,j,k))
            if os.stat("diff/diff_{}_{}_{}".format(i, j, k)).st_size != 0:
                print("+++++++++++++++++++\nFailed test {}_{}_{}".format(i, j, k))
                print("in files: songs_{}.in, parameters_{}.in, queries_{}.in\n".format(i, j, k))
                os.system("cat diff/diff_{}_{}_{}".format(i, j, k))
                print("\n\n")
                failed += 1
            else:
                succeeded += 1
                continue

if (failed != 0):
    print("------ RESULTS -------\nFailed: {}\n Passed: {}\n".format(failed, succeeded))
else:
    print("Passed all tests\n")
'''
else:
    print(
        "-------------------\nPassed all tests!\n -----------------------------\nrunning coding style check...\n\n")
    time.sleep(3)
    os.system("~slabcpp/www/codingStyleCheck .")
    print("\n\n ----------------------\nmaking tar...")
    time.sleep(3)
    os.system("make tar")
    print("\n\n---------------------\nRunning presubmit...")
    time.sleep(3)
    os.system("~slabcpp/www/ex2/presubmit_ex2 ex2.tar")
'''