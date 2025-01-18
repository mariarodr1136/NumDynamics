#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

// Macro for generating random real numbers uniformly in [0, 1)
#define frand() ((double)rand() / RAND_MAX)

// Function Prototypes
double generate_uniform_real(double m, double M);
int generate_uniform_int(int m, int M);
double generate_normal(double mu, double sigma);
int generate_normal_int(double mu, double sigma);
double generate_truncated_normal(double mu, double sigma, double m, double M);
int generate_truncated_normal_int(double mu, double sigma, int m, int M);
void create_directory(const char* path);
void generate_and_save_sequence(const char* filename, int n, void* generator, void* params);

// Function implementations for creating a directory
void create_directory(const char* path) {
    // Try to create the directory with read, write, and execute permissions
    if (mkdir(path, 0777) == -1) {
        perror("Error creating directory");
    }
}

// Function to generate a uniform real number between m and M
double generate_uniform_real(double m, double M) {
    return m + frand() * (M - m);
}

// Function to generate a uniform integer between m and M
int generate_uniform_int(int m, int M) {
    return m + rand() % (M - m + 1);
}

// Function to generate a normal real number with mean mu and standard deviation sigma
double generate_normal(double mu, double sigma) {
    double u1 = frand();
    double u2 = frand();
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return mu + z0 * sigma;
}

// Function to generate a normal integer with mean mu and standard deviation sigma
int generate_normal_int(double mu, double sigma) {
    return (int)round(generate_normal(mu, sigma));
}

// Function to generate a truncated normal real number with mean mu, standard deviation sigma, truncated between m and M
double generate_truncated_normal(double mu, double sigma, double m, double M) {
    double value;
    do {
        value = generate_normal(mu, sigma);
    } while (value < m || value > M);
    return value;
}

// Function to generate a truncated normal integer with mean mu, standard deviation sigma, truncated between m and M
int generate_truncated_normal_int(double mu, double sigma, int m, int M) {
    return (int)round(generate_truncated_normal(mu, sigma, (double)m, (double)M));
}

// Structure to hold distribution parameters
typedef struct {
    double m, M, mu, sigma;
} Parameters;

// Generator function types
typedef double (*RealGenerator)(void*);
typedef int (*IntGenerator)(void*);

// Wrapper functions for generators
double uniform_real_wrapper(void* params) {
    Parameters* p = (Parameters*)params;
    return generate_uniform_real(p->m, p->M);
}

int uniform_int_wrapper(void* params) {
    Parameters* p = (Parameters*)params;
    return generate_uniform_int(p->m, p->M);
}

double normal_real_wrapper(void* params) {
    Parameters* p = (Parameters*)params;
    return generate_normal(p->mu, p->sigma);
}

int normal_int_wrapper(void* params) {
    Parameters* p = (Parameters*)params;
    return generate_normal_int(p->mu, p->sigma);
}

double truncated_normal_real_wrapper(void* params) {
    Parameters* p = (Parameters*)params;
    return generate_truncated_normal(p->mu, p->sigma, p->m, p->M);
}

int truncated_normal_int_wrapper(void* params) {
    Parameters* p = (Parameters*)params;
    return generate_truncated_normal_int(p->mu, p->sigma, p->m, p->M);
}

// Function to generate and save the sequence of random numbers to a file
void generate_and_save_sequence(const char* filename, int n, void* generator, void* params) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Call the generator function and write the generated values to the file
    for (int i = 0; i < n; i++) {
        double value = ((RealGenerator)generator)(params); // Cast to RealGenerator
        fprintf(file, "%f\n", value);
    }

    fclose(file);
}

int main() {
    srand(time(NULL));

    // Define scenarios
    Parameters scenarios[] = {
        {1, 8, 5, 1},                    // Scenario 1
        {1, 2000, 1024, 256},           // Scenario 2
        {1, 8100, 4096, 1331.2}         // Scenario 3
    };

    // Create main data directory
    create_directory("DATA");

    // Number of random numbers to generate per sequence
    const int N = 1000;

    // Process each scenario
    for (int s = 0; s < 3; s++) {
        // Create scenario directory
        char scenario_dir[100];
        sprintf(scenario_dir, "DATA/Scenario%d", s + 1);
        create_directory(scenario_dir);

        // Generate all sequences for current scenario
        char filename[200];
        
        // Uniform integers
        sprintf(filename, "%s/uniform_integers.txt", scenario_dir);
        generate_and_save_sequence(filename, N, uniform_int_wrapper, &scenarios[s]);

        // Uniform real numbers
        sprintf(filename, "%s/uniform_real.txt", scenario_dir);
        generate_and_save_sequence(filename, N, uniform_real_wrapper, &scenarios[s]);

        // Normal integers
        sprintf(filename, "%s/normal_integers.txt", scenario_dir);
        generate_and_save_sequence(filename, N, normal_int_wrapper, &scenarios[s]);

        // Normal real numbers
        sprintf(filename, "%s/normal_real.txt", scenario_dir);
        generate_and_save_sequence(filename, N, normal_real_wrapper, &scenarios[s]);

        // Truncated normal integers
        sprintf(filename, "%s/truncated_normal_integers.txt", scenario_dir);
        generate_and_save_sequence(filename, N, truncated_normal_int_wrapper, &scenarios[s]);

        // Truncated normal real numbers
        sprintf(filename, "%s/truncated_normal_real.txt", scenario_dir);
        generate_and_save_sequence(filename, N, truncated_normal_real_wrapper, &scenarios[s]);

        // Output for the scenario
        printf("\n--- Scenario %d ---\n", s + 1);
        printf("Generated scenario %d...\n", s + 1);
        printf("Statistics for Scenario %d:\n", s + 1);
        char stats_command[200];
        sprintf(stats_command, "python3 calculate_statistics.py DATA/Scenario%d", s + 1);
        system(stats_command);
        printf("The histogram has been created...\n");
    }

    return 0;
}
