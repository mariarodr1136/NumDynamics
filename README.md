# NumDynamics: Advanced Random Number Generator 🎲

NumDynamics is a sophisticated random number generation system that produces high-quality random numbers following various statistical distributions. Built with **C** for core functionality and analysis and **Python** for visualization, the system generates, analyzes, and visualizes random number distributions with precision and efficiency. The project combines the speed and powerful data analysis capabilities of C with Python's visualization capabilities to create a comprehensive random number generation and analysis toolkit.

![C](https://img.shields.io/badge/C-Programming%20Language-blue)
![Python](https://img.shields.io/badge/Python-Data%20Analysis-yellow)
![NumPy](https://img.shields.io/badge/NumPy-Numerical%20Computing-orange)
![Matplotlib](https://img.shields.io/badge/Matplotlib-Data%20Visualization-green)
![SciPy](https://img.shields.io/badge/SciPy-Scientific%20Computing-blue)

---

<img width="777" alt="Screenshot 2025-01-17 at 10 17 39 PM" src="https://github.com/user-attachments/assets/f16a6206-f00d-40c3-89ec-7d60b1614baa" />

---

## Table of Contents
- [Key Features](#key-features)
- [Distribution Types](#distribution-types)
- [Project Structure](#project-structure)
- [Technical Implementation](#technical-implementation)
- [Installation](#installation)
- [Usage Examples](#usage-examples)
- [Pre-configured Scenarios](#pre-configured-scenarios)
- [Requirements](#requirements)
- [Contributing](#contributing)
- [Contact](#contact)

---

## Key Features
- **Multiple Distribution Types**: Generate numbers following various statistical distributions
- **High-Performance C Core**: Optimized random number generation using C
- **Statistical Analysis**: Comprehensive statistical calculations using C
- **Data Visualization**: Automated histogram generation for distribution analysis
- **Organized Data Management**: Structured directory system for data storage
- **Configurable Parameters**: Customizable distribution parameters for different scenarios
- **Automated Workflow**: Single-command execution for generation, analysis, and visualization

---

<img width="293" alt="Screenshot 2025-01-18 at 6 43 09 PM" src="https://github.com/user-attachments/assets/d7cd5783-fb16-477d-86f4-a42c9e1d80e2" />
<img width="293" alt="Screenshot 2025-01-18 at 6 43 24 PM" src="https://github.com/user-attachments/assets/33e4ad8e-aba3-4a2a-b4eb-971bbc4dd8f0" />
<img width="303" alt="Screenshot 2025-01-18 at 6 43 38 PM" src="https://github.com/user-attachments/assets/d6c39bae-aaa9-488f-a291-b22cc274185f" />

---

## Distribution Types
NumDynamics supports multiple distribution types to meet various random number generation needs:

- **Uniform Distribution**
  - Integer ranges with customizable bounds
  - Real number ranges with precise control
  
- **Normal Distribution**
  - Integer-based normal distribution
  - Real number normal distribution
  - Configurable mean and standard deviation
  
- **Truncated Normal**
  - Bounded normal distribution for integers
  - Bounded normal distribution for real numbers
  - Control over truncation limits

---

## Project Structure
```
NumDynamics/
├── CODE/
│   ├── random_gen.c                 # Core C program
│   ├── stats.c                      # Statistical analysis
│   └── histogram_generator.py       # Visualization script
│   └── Makefile                     # Build automation
├── DATA/                            # Generated datasets
│   ├── Scenario1/
│   ├── Scenario2/
│   └── Scenario3/
├── HISTOGRAM/                      # Visualization outputs
└── README.md                       # Documentation
```

---

## Technical Implementation

### Core Generation (C)
- Implements multiple random number generation algorithms
- Optimized for performance and statistical quality
- Handles different distribution types efficiently

### Analysis (Python)
- Calculates comprehensive statistical metrics
  - Mean, standard deviation
  - Distribution parameters
  - Quality assessments
- Generates detailed analytical reports

### Visualization (Python)
- Creates publication-quality histograms
- Supports multiple plot types
- Automated visualization pipeline

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/numdynamics.git
   cd CODE
   ```

2. Install Python dependencies:
   ```bash
    brew install gcc
    brew install python
    pip3 install numpy matplotlib scipy
   ```

3. Compile and run:
   ```bash
   make
   ./ass1
   ```

4. Clean generated files (optional):
   ```bash
   make clean
   ```

---

## Usage Examples

### Basic Usage
```bash
# Generate numbers with default parameters
./random_gen

# Analyze generated data
./stats

# Generate visualizations
python histogram_generator.py
```

### Custom Parameters
```bash
# Generate numbers with custom range
./random_gen -min 1 -max 100 -n 1000

# Generate normal distribution
./random_gen -dist normal -mean 50 -std 10
```

---

## Pre-configured Scenarios

### Scenario 1: Precise Control
- Range: 1 to 8
- Mean: 5
- Standard Deviation: 1
- Ideal for testing small-scale distributions

### Scenario 2: Medium Range
- Range: 1 to 2000
- Suitable for statistical sampling

### Scenario 3: Wide Distribution
- Range: 1 to 8100
- Custom mean and standard deviation
- Perfect for large-scale simulations

---

## Requirements
- **C Compiler**: GCC 5.0+ or equivalent
- **Python**: 3.7+
- **Python Libraries**:
  - NumPy >= 1.19.0
  - Matplotlib >= 3.3.0
  - SciPy >= 1.5.0

---

## Contributing
Feel free to submit issues or pull requests for improvements or bug fixes. You can also open issues to discuss potential changes or enhancements. All contributions are welcome to enhance the app’s features or functionality!

To contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix:
   ```bash
   git checkout -b feat/your-feature-name
- Alternatively, for bug fixes:
   ```bash
   git checkout -b fix/your-bug-fix-name
3. Make your changes and run all tests before committing the changes and make sure all tests are passed.
4. After all tests are passed, commit your changes with descriptive messages:
   ```bash
   git commit -m 'add your commit message'
5. Push your changes to your forked repository:
   ```bash
   git push origin feat/your-feature-name.
6. Submit a pull request to the main repository, explaining your changes and providing any necessary details.

## Contact
If you have any questions or feedback, feel free to reach out at [mrodr.contact@gmail.com](mailto:mrodr.contact@gmail.com).
