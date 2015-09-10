__author__ = 'davebarda'

from random import randint
from random import uniform
import os
from sys import argv

def main(argv):
    if not(os.path.exists(os.path.abspath(os.curdir) + "/Tests/")):
        os.mkdir(os.path.abspath(os.curdir) + "/Tests/")
    for i in range(0, int(argv[0])):
        operation = randint(1, 4)
        f = open(os.path.abspath(os.curdir) + "/Tests/different_size_int_" + str(operation)
                 + "_" + str(i), "w+")
        num_of_rows_first = randint(1, 5)
        num_of_cols_first = num_of_rows_first + 1
        f.write(str(1) + "\n")
        f.write(str(operation) + "\n")
        f.write(str(num_of_rows_first) + "\n")
        f.write(str(num_of_cols_first) + "\n")
        for j in range(0, num_of_rows_first):
            for k in range(0, num_of_cols_first):
                f.write(str(randint(0, 9999)))
                f.write(',')
            f.write("\n")
        if operation <= 2:
            num_of_rows_second = num_of_rows_first + 2
            num_of_cols_second = num_of_cols_first + 3
            f.write(str(num_of_rows_second) + "\n")
            f.write(str(num_of_cols_second) + "\n")
            for j in range(0, num_of_rows_second):
                for k in range(0, num_of_cols_second):
                    f.write(str(randint(0, 9999)))
                    f.write(',')
                f.write("\n")

    for i in range(0, int(argv[1])):
        operation = randint(1, 4)
        f = open(os.path.abspath(os.curdir) + "/Tests/different_size_double_" + str(operation)
                 + "_" + str(i), "w+")
        num_of_rows_first = randint(1, 5)
        num_of_cols_first = num_of_rows_first + 1
        f.write(str(2) + "\n")
        f.write(str(operation) + "\n")
        f.write(str(num_of_rows_first) + "\n")
        f.write(str(num_of_cols_first) + "\n")
        for j in range(0, num_of_rows_first):
            for k in range(0, num_of_cols_first):
                f.write(str(uniform(0, 9999)))
                f.write(',')
            f.write("\n")
        if operation <= 2:
            num_of_rows_second = num_of_rows_first + 2
            num_of_cols_second = num_of_cols_first + 3
            f.write(str(num_of_rows_second) + "\n")
            f.write(str(num_of_cols_second) + "\n")
            for j in range(0, num_of_rows_second):
                for k in range(0, num_of_cols_second):
                    f.write(str(uniform(0, 9999)))
                    f.write(',')
                f.write("\n")

    for i in range(0, int(argv[2])):
        operation = randint(1, 4)
        f = open(os.path.abspath(os.curdir) + "/Tests/different_size_complex_" + str(operation)
                 + "_" + str(i), "w+")
        num_of_rows_first = randint(1, 5)
        num_of_cols_first = num_of_rows_first + 1
        f.write(str(3) + "\n")
        f.write(str(operation) + "\n")
        f.write(str(num_of_rows_first) + "\n")
        f.write(str(num_of_cols_first) + "\n")
        for j in range(0, num_of_rows_first):
            for k in range(0, num_of_cols_first):
                f.write(str(uniform(0, 9999)) + "+" + str(uniform(0, 9999)) + "i")
                f.write(',')
            f.write("\n")
        if operation <= 2:
            num_of_rows_second = num_of_rows_first + 2
            num_of_cols_second = num_of_cols_first + 3
            f.write(str(num_of_rows_second) + "\n")
            f.write(str(num_of_cols_second) + "\n")
            for j in range(0, num_of_rows_second):
                for k in range(0, num_of_cols_second):
                    f.write(str(uniform(0, 9999)) + "+" + str(uniform(0, 9999)) + "i")
                    f.write(',')
                f.write("\n")


    operation = randint(1, 4)
    f = open(os.path.abspath(os.curdir) + "/Tests/zero_by_1_int_" + str(operation)
             + "_" + str(i), "w+")
    num_of_rows_first = 0
    num_of_cols_first = 1
    f.write(str(1) + "\n")
    f.write(str(operation) + "\n")
    f.write(str(num_of_rows_first) + "\n")
    f.write(str(num_of_cols_first) + "\n")
    for j in range(0, num_of_rows_first):
        for k in range(0, num_of_cols_first):
            f.write(str(randint(0, 9999)))
            f.write(',')
        f.write("\n")
    if operation <= 2:
        num_of_rows_second = num_of_rows_first
        num_of_cols_second = num_of_cols_first
        f.write(str(num_of_rows_second) + "\n")
        f.write(str(num_of_cols_second) + "\n")
        for j in range(0, num_of_rows_second):
            for k in range(0, num_of_cols_second):
                f.write(str(randint(0, 9999)))
                f.write(',')
            f.write("\n")

    operation = randint(1, 4)
    f = open(os.path.abspath(os.curdir) + "/Tests/zero_by_1_double_" + str(operation)
             + "_" + str(i), "w+")
    num_of_rows_first = 0
    num_of_cols_first = 1
    f.write(str(2) + "\n")
    f.write(str(operation) + "\n")
    f.write(str(num_of_rows_first) + "\n")
    f.write(str(num_of_cols_first) + "\n")
    for j in range(0, num_of_rows_first):
        for k in range(0, num_of_cols_first):
            f.write(str(randint(0, 9999)))
            f.write(',')
        f.write("\n")
    if operation <= 2:
        num_of_rows_second = num_of_rows_first
        num_of_cols_second = num_of_cols_first
        f.write(str(num_of_rows_second) + "\n")
        f.write(str(num_of_cols_second) + "\n")
        for j in range(0, num_of_rows_second):
            for k in range(0, num_of_cols_second):
                f.write(str(randint(0, 9999)))
                f.write(',')
            f.write("\n")

    operation = randint(1, 4)
    f = open(os.path.abspath(os.curdir) + "/Tests/zero_by_1_complex_" + str(operation)
             + "_" + str(i), "w+")
    num_of_rows_first = 0
    num_of_cols_first = 1
    f.write(str(3) + "\n")
    f.write(str(operation) + "\n")
    f.write(str(num_of_rows_first) + "\n")
    f.write(str(num_of_cols_first) + "\n")
    for j in range(0, num_of_rows_first):
        for k in range(0, num_of_cols_first):
            f.write(str(randint(0, 9999)))
            f.write(',')
        f.write("\n")
    if operation <= 2:
        num_of_rows_second = num_of_rows_first
        num_of_cols_second = num_of_cols_first
        f.write(str(num_of_rows_second) + "\n")
        f.write(str(num_of_cols_second) + "\n")
        for j in range(0, num_of_rows_second):
            for k in range(0, num_of_cols_second):
                f.write(str(randint(0, 9999)))
                f.write(',')
            f.write("\n")

    operation = randint(1, 4)
    f = open(os.path.abspath(os.curdir) + "/Tests/1_by_zero_int_" + str(operation)
             + "_" + str(i), "w+")
    num_of_rows_first = 1
    num_of_cols_first = 0
    f.write(str(1) + "\n")
    f.write(str(operation) + "\n")
    f.write(str(num_of_rows_first) + "\n")
    f.write(str(num_of_cols_first) + "\n")
    for j in range(0, num_of_rows_first):
        for k in range(0, num_of_cols_first):
            f.write(str(randint(0, 9999)))
            f.write(',')
        f.write("\n")
    if operation <= 2:
        num_of_rows_second = num_of_rows_first
        num_of_cols_second = num_of_cols_first
        f.write(str(num_of_rows_second) + "\n")
        f.write(str(num_of_cols_second) + "\n")
        for j in range(0, num_of_rows_second):
            for k in range(0, num_of_cols_second):
                f.write(str(randint(0, 9999)))
                f.write(',')
            f.write("\n")

    operation = randint(1, 4)
    f = open(os.path.abspath(os.curdir) + "/Tests/1_by_zero_double_" + str(operation)
             + "_" + str(i), "w+")
    num_of_rows_first = 1
    num_of_cols_first = 0
    f.write(str(2) + "\n")
    f.write(str(operation) + "\n")
    f.write(str(num_of_rows_first) + "\n")
    f.write(str(num_of_cols_first) + "\n")
    for j in range(0, num_of_rows_first):
        for k in range(0, num_of_cols_first):
            f.write(str(randint(0, 9999)))
            f.write(',')
        f.write("\n")
    if operation <= 2:
        num_of_rows_second = num_of_rows_first
        num_of_cols_second = num_of_cols_first
        f.write(str(num_of_rows_second) + "\n")
        f.write(str(num_of_cols_second) + "\n")
        for j in range(0, num_of_rows_second):
            for k in range(0, num_of_cols_second):
                f.write(str(randint(0, 9999)))
                f.write(',')
            f.write("\n")

    operation = randint(1, 4)
    f = open(os.path.abspath(os.curdir) + "/Tests/1_by_zero_complex_" + str(operation)
             + "_" + str(i), "w+")
    num_of_rows_first = 1
    num_of_cols_first = 0
    f.write(str(3) + "\n")
    f.write(str(operation) + "\n")
    f.write(str(num_of_rows_first) + "\n")
    f.write(str(num_of_cols_first) + "\n")
    for j in range(0, num_of_rows_first):
        for k in range(0, num_of_cols_first):
            f.write(str(randint(0, 9999)))
            f.write(',')
        f.write("\n")
    if operation <= 2:
        num_of_rows_second = num_of_rows_first
        num_of_cols_second = num_of_cols_first
        f.write(str(num_of_rows_second) + "\n")
        f.write(str(num_of_cols_second) + "\n")
        for j in range(0, num_of_rows_second):
            for k in range(0, num_of_cols_second):
                f.write(str(randint(0, 9999)))
                f.write(',')
            f.write("\n")
    # # Specials
    # f = open(os.path.abspath(os.curdir) + "/Tests/no_type_choice", "w+")
    # f.write("\n");
    # f.close()

    # f = open(os.path.abspath(os.curdir) + "/Tests/no_op_choice", "w+")
    # f.write("1\n\n");
    # f.close()

    # f = open(os.path.abspath(os.curdir) + "/Tests/no_size_choice_int_add", "w+")
    # f.write("1\n1\n\n\n");
    # f.close()

    # f = open(os.path.abspath(os.curdir) + "/Tests/no_size_choice_int_mul", "w+")
    # f.write("1\n2\n\n\n");
    # f.close()
    
    # f = open(os.path.abspath(os.curdir) + "/Tests/no_size_choice_int_trans", "w+")
    # f.write("1\n3\n\n\n");
    # f.close()
    
    # f = open(os.path.abspath(os.curdir) + "/Tests/no_size_choice_int_trace", "w+")
    # f.write("1\n4\n\n\n");
    # f.close()

if __name__ == '__main__':
    main(argv[1:])
