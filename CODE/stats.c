#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function prototypes
void analyze_file(const char* filepath, double* mean, double* std_dev);
void analyze_scenario(int scenario);

int main() {
    // Analyze all scenarios
    for(int scenario = 1; scenario <= 3; scenario++) {
        analyze_scenario(scenario);
    }
    return 0;
}

void analyze_file(const char* filepath, double* mean, double* std_dev) {
    FILE* fp = fopen(filepath, "r");
    if(!fp) {
        printf("Error opening file: %s\n", filepath);
        return;
    }
    
    // First pass: calculate mean
    double sum = 0;
    double value;
    int count = 0;
    
    while(fscanf(fp, "%lf", &value) == 1) {
        sum += value;
        count++;
    }
    
    *mean = sum / count;
    
    // Second pass: calculate standard deviation
    rewind(fp);
    sum = 0;
    
    while(fscanf(fp, "%lf", &value) == 1) {
        double diff = value - *mean;
        sum += diff * diff;
    }
    
    *std_dev = sqrt(sum / (count - 1));
    fclose(fp);
}

void analyze_scenario(int scenario) {
    char base_path[100];
    char filepath[200];
    double mean, std_dev;
    const char* file_types[] = {
        "uniform_integers.txt",
        "uniform_reals.txt",
        "normal_integers.txt",
        "normal_reals.txt",
        "truncated_normal_integers.txt",
        "truncated_normal_reals.txt"
    };
    
    sprintf(base_path, "DATA/Scenario%d", scenario);
    printf("\nScenario %d Statistical Analysis:\n", scenario);
    printf("----------------------------------------\n");
    
    for(int i = 0; i < 6; i++) {
        sprintf(filepath, "%s/%s", base_path, file_types[i]);
        analyze_file(filepath, &mean, &std_dev);
        printf("\n%s:\n", file_types[i]);
        printf("Mean: %.6f\n", mean);
        printf("Standard Deviation: %.6f\n", std_dev);
    }
}