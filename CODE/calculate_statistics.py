import numpy as np
import os

# List of all scenarios
scenarios = ["DATA/Scenario1", "DATA/Scenario2", "DATA/Scenario3"]

# List of all file types
files = [
    "uniform_integers.txt",
    "uniform_real.txt", 
    "normal_integers.txt",
    "normal_real.txt",
    "truncated_normal_integers.txt",
    "truncated_normal_real.txt"
]

# Loop through each scenario
for scenario in scenarios:
    print(f"\n--- Statistics for {scenario} ---")
    
    # Ensure only one generation per scenario
    if not os.path.exists(scenario):
        print(f"Scenario {scenario} not found, skipping...")
        continue  # Skip if scenario folder does not exist
    
    # Calculate statistics for each file in the scenario
    for file in files:
        path = os.path.join(scenario, file)
        
        # Check if the file exists before processing it
        if os.path.exists(path):
            data = np.loadtxt(path)
            mean = np.mean(data)
            std = np.std(data, ddof=1)  
            print(f"\n{file}")
            print(f"Mean: {mean:.2f}")
            print(f"Standard Deviation: {std:.2f}")
