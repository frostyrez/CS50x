# Notes: to read from specific cell:
# with open(filename, 'rb') as f:
#      rows = list(csv.reader(f))
#      print rows[row_number][column_number]

# Above loads whole file into memory
# To avoid use itertools:

# import itertools
# with open(filename, 'rb') as f:
#      row = next(itertools.islice(csv.reader(f), row_number, row_number+1))
#      print row[column_number]

import csv
import sys

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    # with open(sys.argv[1],"r") as file:
    database = csv.reader(open(sys.argv[1]))
        # for row in database:
        #     for col in row:
        #         print(row[col],end=" ")
        # print("")

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2],"r") as file:
        seq = file.read()

    # Find number of STRs to test:

    # TODO: Find longest match of each STR in DNA sequence
    for row in database:
        str_count = len(row) - 1
        longest = [0 for i in range(len(row)-1)]
        for col in range(1,str_count+1):
            longest[col-1] = longest_match(seq,row[col])
        # print(longest)
        break


    # TODO: Check database for matching profiles
    database = csv.reader(open(sys.argv[1]))
    for row in database:
        i = 0
        if row[0] != "name":
            # print(f"Longest: {longest[i]}, row[{i+1}]: {row[i+1]}")
            while longest[i] == int(row[i+1]):
                if i == str_count-1:
                    print(row[0])
                    return
                else:
                    i += 1
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
