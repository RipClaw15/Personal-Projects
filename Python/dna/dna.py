import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("Error")

    # TODO: Read database file into a variable
    with open(argv[1],"r") as file:
        read1 = csv.reader(file)
        subsequence = next(read1)

    with open(argv[1],"r") as file1:

        reader = csv.DictReader(file1)

        # for row in reader:


            # TODO: Read DNA sequence file into a variable
        sequence = open(argv[2]).read()


        r = 0
                # TODO: Find longest match of each STR in DNA sequence
        for row in reader:
            r = 0

            for i in subsequence[1:]:

                if int(row[i]) == longest_match(sequence,i):
                    r = 1

                else:
                    r = 0
                    break
            if r == 1 :
                print(row["name"])
                break
    # TODO: Check database for matching profiles
        if r == 0:
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
