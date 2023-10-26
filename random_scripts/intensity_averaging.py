import pandas as pd
import argparse


parser = argparse.ArgumentParser(description="BEATS ZMQ Writer")
parser.add_argument('--file', type=str, help='Input file name')
args = parser.parse_args()
file_path = args.file

# Read the input data
input_file = file_path
output_file = 'OUTPUT_'+input_file

# Dictionary to store and calculate averages
averages = {}

# Read the input file and calculate averages
with open(input_file, 'r') as f:
    next(f)  # Skip the header line
    for line in f:
        columns = line.strip().split('\t')
        if len(columns) == 2:
            x_val = float(columns[0])
            y_val = float(columns[1])
            if x_val in averages:
                averages[x_val].append(y_val)
            else:
                averages[x_val] = [y_val]

# Calculate the averages
with open(output_file, 'w') as f:
    f.write('#2th\t#Int\n')
    for key, value in sorted(averages.items()):
        avg = sum(value) / len(value)
        f.write(f'{key:.3f}\t{avg:.5f}\n')

print(f'Output saved to {output_file}')
