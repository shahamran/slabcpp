import os
import time

SCHOOL="SCHOOL"

if not os.path.isdir("school_out"):
	os.system("mkdir school_out")	

os.system("rm -f school_out/*")

os.system(SCHOOL + " >> school_out/result_nofiles 2>&1")
os.system(SCHOOL + " songs/songs_1.in nofile nofile >> school_out/result_noparams_noqueries 2>&1")
os.system(SCHOOL + " nofile params/parameters_1.in nofile >> school_out/result_nosongs_noqueries 2>&1")
os.system(SCHOOL + " nofile nofile queries/queries_1.in >> school_out/result_nosongs_noparams 2>&1")
os.system(SCHOOL + " songs/songs_1.in params/parameters_1.in nofile >> school_out/result_noqueries 2>&1")
os.system(SCHOOL + " nofile params/paramseters_1.in queries/queries_1.in >> school_out/result_nosongs 2>&1")
os.system(SCHOOL + " songs/songs_1.in nofile queries/queries_1.in >> school_out/result_noparams 2>&1")

for songs in os.listdir("songs"):
	for params in os.listdir("params"):
		for queries in os.listdir("queries"):
			os.system(SCHOOL + " songs/{} params/{} queries/{} > school_out/school_{}_{}_{}".format(songs, params, queries, songs, params, queries))

print("SCHOOL GENERATION OK")
