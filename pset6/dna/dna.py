import csv
import sys

# Compare the STR counts againts each row in the CSV file
def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
    csv_file = sys.argv[1]
    txt_file = sys.argv[2]
    # Open csv file
    with open(csv_file) as DNA:
        # Read csv file
        reader = csv.reader(DNA)
        # Skip header
        all_sequences = next(reader)[1:]
        # Open txt file
        with open(txt_file) as sequences:
            # .read() reads entire string at once of txt file
            string = sequences.read()
            actual_sequence = [repeat(string, sequence) for sequence in all_sequences]
            for row in reader:
                name = row[0]
                values = [int(val) for val in row[1:]]
                if values == actual_sequence:
                    print(name)
            print("No match")

# For each position in the sequence: compute how many times the STR repeats starting at that position
def repeat(string, substring):
    # Inicialize 0 with string length
    num = [0] * len(string)
    for i in range(len(string) - len(substring), -1, -1):
        if string[i: i + len(substring)] == substring:
            # If out of bounds
            if i + len(substring) > len(string) - 1:
                num[i] = 1
            else:
                num[i] = 1 + num[i + len(substring)]
    # Return largest number
    return max(num)

# Standard way of calling the main function in Python when the entire code runs without importing libraries
if __name__ == "__main__":
    main()
