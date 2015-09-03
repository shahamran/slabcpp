import os
import time

EX="MIR"

if not os.path.isdir("results_out"):
	os.system("mkdir results_out")
if not os.path.isdir("diff"):
	os.system("mkdir diff")

failed = 0
succeeded = 0

os.system("rm -f results_out/*")
os.system("rm -f diff/*")

os.system(EX + " >> results_out/result_nofiles 2>&1")
os.system(EX + " songs/songs_1.in nofile nofile >> results_out/result_noparams_noqueries 2>&1")
os.system(EX + " nofile params/parameters_1.in nofile >> results_out/result_nosongs_noqueries 2>&1")
os.system(EX + " nofile nofile queries/queries_1.in >> results_out/result_nosongs_noparams 2>&1")
os.system(EX + " songs/songs_1.in params/parameters_1.in nofile >> results_out/result_noqueries 2>&1")
os.system(EX + " nofile params/paramseters_1.in queries/queries_1.in >> results_out/result_nosongs 2>&1")
os.system(EX + " songs/songs_1.in nofile queries/queries_1.in >> results_out/result_noparams 2>&1")

for result in os.listdir("results_out"):
	os.system("diff results_out/" + result + " school_out/" + result + " > diff/diff_" + result)
	if os.stat("diff/diff_" + result).st_size != 0:
		print("Failed test: " + result)
		failed+=1
	else:
		succeeded+=1


for songs in os.listdir("songs"):
	for params in os.listdir("params"):
		for queries in os.listdir("queries"):
			os.system(EX + " songs/{} params/{} queries/{} > results_out/result_{}_{}_{}".format(songs, params, queries, songs, params, queries))
			os.system("diff results_out/result_{}_{}_{}  school_out/school_{}_{}_{} > diff/diff_{}_{}_{}".format(songs, params, queries, songs, params, queries, songs, params, queries))
			if os.stat("diff/diff_{}_{}_{}".format(songs, params, queries)).st_size != 0:
				print("Failed test: {} {} {}".format(songs, params, queries))
				failed+=1
			else:
				succeeded += 1
				continue
			
if (failed != 0):
	print("\nFAILED {}\nPASSED {}\n".format(failed, succeeded))
else:
	print("\nPASSED ALL ({})\n".format(succeeded))
#	print("PASSED ALL\n -----------------------------\nrunning coding style check...\n\n")
#	time.sleep(3)
#	os.system("~slabcpp/www/codingStyleCheck .")
#	print("\n\n ----------------------\nmaking tar...")
#	time.sleep(3)
#	os.system("make tar")
#	print("\n\n---------------------\nRunning presubmit...")
#	time.sleep(3)
#	os.system("~slabcpp/www/ex2/presubmit_ex2 ex2.tar")
