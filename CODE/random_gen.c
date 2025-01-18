#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#define frand() ((double)rand() / RAND_MAX)
#define nrand() (sqrt(-2.0 * log(frand())) * cos(2.0 * M_PI * frand()))

// Function prototypes
double generate_uniform_real(double m, double M);
int generate_uniform_int(int m, int M);
double generate_normal_real(double mu, double sigma);
int generate_normal_int(double mu, double sigma);
double generate_truncated_normal_real(double mu, double sigma, double m, double M);
int generate_truncated_normal_int(double mu, double sigma, int m, int M);
void create_directory(const char* path);
void generate_scenario_data(int scenario, double mu, double sigma, int m, int M, int N);

int main() {
    srand(time(NULL));
    
    // Create main DATA directory
    create_directory("DATA");
    
    // Scenario 1: μ=5, σ=1, m=1, M=8
    generate_scenario_data(1, 5.0, 1.0, 1, 8, 1000);
    
    // Scenario 2: μ=2^10, σ=2^8, m=1, M=2000
    generate_scenario_data(2, pow(2,10), pow(2,8), 1, 2000, 1000);
    
    // Scenario 3: μ=2^12, σ=1.3×2^10, m=1, M=8100
    generate_scenario_data(3, pow(2,12), 1.3*pow(2,10), 1, 8100, 1000);
    
    return 0;
}

void create_directory(const char* path) {
    #ifdef _WIN32
        mkdir(path);
    #else
        mkdir(path, 0777);
    #endif
}

double generate_uniform_real(double m, double M) {
    return m + (M - m) * frand();
}

int generate_uniform_int(int m, int M) {
    return m + rand() % (M - m + 1);
}

double generate_normal_real(double mu, double sigma) {
    return mu + sigma * nrand();
}

int generate_normal_int(double mu, double sigma) {
    return (int)round(generate_normal_real(mu, sigma));
}

double generate_truncated_normal_real(double mu, double sigma, double m, double M) {
    double value;
    do {
        value = generate_normal_real(mu, sigma);
    } while (value < m || value > M);
    return value;
}

int generate_truncated_normal_int(double mu, double sigma, int m, int M) {
    return (int)round(generate_truncated_normal_real(mu, sigma, m, M));
}

void generate_scenario_data(int scenario, double mu, double sigma, int m, int M, int N) {
    char scenario_dir[100];
    char filepath[200];
    FILE *fp;
    
    // Create scenario directory
    sprintf(scenario_dir, "DATA/Scenario%d", scenario);
    create_directory(scenario_dir);
    
    // Generate uniform integers
    sprintf(filepath, "%s/uniform_integers.txt", scenario_dir);
    fp = fopen(filepath, "w");
    for(int i = 0; i < N; i++)
        fprintf(fp, "%d\n", generate_uniform_int(m, M));
    fclose(fp);
    
    // Generate uniform reals
    sprintf(filepath, "%s/uniform_reals.txt", scenario_dir);
    fp = fopen(filepath, "w");
    for(int i = 0; i < N; i++)
        fprintf(fp, "%.6f\n", generate_uniform_real(m, M));
    fclose(fp);
    
    // Generate normal integers
    sprintf(filepath, "%s/normal_integers.txt", scenario_dir);
    fp = fopen(filepath, "w");
    for(int i = 0; i < N; i++)
        fprintf(fp, "%d\n", generate_normal_int(mu, sigma));
    fclose(fp);
    
    // Generate normal reals
    sprintf(filepath, "%s/normal_reals.txt", scenario_dir);
    fp = fopen(filepath, "w");
    for(int i = 0; i < N; i++)
        fprintf(fp, "%.6f\n", generate_normal_real(mu, sigma));
    fclose(fp);
    
    // Generate truncated normal integers
    sprintf(filepath, "%s/truncated_normal_integers.txt", scenario_dir);
    fp = fopen(filepath, "w");
    for(int i = 0; i < N; i++)
        fprintf(fp, "%d\n", generate_truncated_normal_int(mu, sigma, m, M));
    fclose(fp);
    
    // Generate truncated normal reals
    sprintf(filepath, "%s/truncated_normal_reals.txt", scenario_dir);
    fp = fopen(filepath, "w");
    for(int i = 0; i < N; i++)
        fprintf(fp, "%.6f\n", generate_truncated_normal_real(mu, sigma, m, M));
    fclose(fp);
}