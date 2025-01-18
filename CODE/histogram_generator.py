import numpy as np
import matplotlib.pyplot as plt
import os
from scipy.stats import truncnorm

# Parameters for Scenario 3
params = {
    'uniform_int': (1, 8100),
    'uniform_real': (1, 8100),
    'normal_int': (4096, 1331.2),
    'normal_real': (4096, 1331.2),
    'truncated_normal_int': (4096, 1331.2, 1, 8100),
    'truncated_normal_real': (4096, 1331.2, 1, 8100),
}

# Number of samples
N = 1000

# Create the directory for saving the histogram data
histogram_dir = "HISTOGRAM/Scenario3"
os.makedirs(histogram_dir, exist_ok=True)

# Function to generate uniform integers
def generate_uniform_int(m, M, n=N):
    return np.random.randint(m, M+1, size=n)

# Function to generate uniform real numbers
def generate_uniform_real(m, M, n=N):
    return np.random.uniform(m, M, size=n)

# Function to generate normal integers
def generate_normal_int(mu, sigma, n=N):
    return np.random.normal(mu, sigma, size=n).round().astype(int)

# Function to generate normal real numbers
def generate_normal_real(mu, sigma, n=N):
    return np.random.normal(mu, sigma, size=n)

# Function to generate truncated normal integers
def generate_truncated_normal_int(mu, sigma, m, M, n=N):
    lower, upper = (m - mu) / sigma, (M - mu) / sigma
    return truncnorm.rvs(lower, upper, loc=mu, scale=sigma, size=n).round().astype(int)

# Function to generate truncated normal real numbers
def generate_truncated_normal_real(mu, sigma, m, M, n=N):
    lower, upper = (m - mu) / sigma, (M - mu) / sigma
    return truncnorm.rvs(lower, upper, loc=mu, scale=sigma, size=n)

# Function to save histogram data to text file
def save_histogram_data(filename, data, bins=50):
    count, bin_edges = np.histogram(data, bins=bins)
    np.savetxt(filename, np.column_stack((bin_edges[:-1], count)), fmt='%.6f', header="Bin edges and counts")
    return count, bin_edges

# Function to plot and save histogram
def plot_histogram(data, title, filename):
    plt.figure(figsize=(8, 6))
    plt.hist(data, bins=50, edgecolor='black', alpha=0.7)
    plt.title(title, fontsize=14)
    plt.xlabel('Value', fontsize=12)
    plt.ylabel('Frequency', fontsize=12)
    plt.figtext(0.5, 0.01, f'File: {filename}', ha="center", fontsize=10)
    plt.figtext(0.5, 0.98, 'Team Member: Maria Rodriguez', ha="center", fontsize=10)
    plt.tight_layout()
    plt.savefig(filename)
    plt.close()

# Generate data for each distribution and save histograms
distribution_funcs = {
    'uniform_int': generate_uniform_int,
    'uniform_real': generate_uniform_real,
    'normal_int': generate_normal_int,
    'normal_real': generate_normal_real,
    'truncated_normal_int': generate_truncated_normal_int,
    'truncated_normal_real': generate_truncated_normal_real
}

for dist_name, func in distribution_funcs.items():
    print(f"Generating {dist_name} data...")
    # Generate the data based on the distribution
    if dist_name in ['truncated_normal_int', 'truncated_normal_real']:
        data = func(*params[dist_name])
    else:
        data = func(*params[dist_name][:2])
    
    # Save histogram data to .txt file
    txt_filename = f"{histogram_dir}/{dist_name}_data.txt"
    counts, bin_edges = save_histogram_data(txt_filename, data)
    
    # Plot and save the histogram as a .png file
    plot_filename = f"{histogram_dir}/{dist_name}_histogram.png"
    plot_histogram(data, f'{dist_name.capitalize()} Histogram', plot_filename)

# Combine all histograms into a PDF
from matplotlib.backends.backend_pdf import PdfPages

with PdfPages(f'{histogram_dir}/histogram.pdf') as pdf:
    for dist_name in distribution_funcs:
        plot_filename = f"{histogram_dir}/{dist_name}_histogram.png"
        img = plt.imread(plot_filename)
        fig, ax = plt.subplots(figsize=(8, 6))
        ax.imshow(img)
        ax.axis('off')
        pdf.savefig(fig)
        plt.close(fig)

print("Histograms and data have been saved successfully.")