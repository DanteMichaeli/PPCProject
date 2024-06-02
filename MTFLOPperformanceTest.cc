
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;
using namespace chrono;

int main() {
  ofstream file("results.csv");
  file << "Iterations,Operations,Time,OperationsPerSecond,CPUFrequency\n";

  // Loop through different numbers of iterations
  for (long long num_iterations = 1000000; num_iterations <= 1000000000;
       num_iterations *= 10) {
    double a = 1.0, b = 1.0000001, c = 1.00000001;

    auto start = high_resolution_clock::now();

    // Parallelize the loop with OpenMP
    double result = 0.0;
#pragma omp parallel for reduction(+ : result)
    for (long long i = 0; i < num_iterations; ++i) {
      double local_result = 0.0;  // Local result variable for each thread
      local_result += a * b;
      local_result -= c;
      local_result *= a;
      local_result /= b;
      result += local_result;
    }

    auto end = high_resolution_clock::now();

    duration<double> elapsed = end - start;

    // Get CPU frequency
    system("sysctl -n machdep.cpu.brand_string > cpuinfo.txt");
    ifstream cpuinfo("cpuinfo.txt");
    string cpufreq;
    getline(cpuinfo, cpufreq);
    cpuinfo.close();
    system("rm cpuinfo.txt");

    // Calculate operations per second
    double ops_per_second =
        num_iterations * 4 / elapsed.count();  // 4 FLOPs per iteration
    file << num_iterations << "," << num_iterations * 4 << ","
         << elapsed.count() << "," << ops_per_second << "," << cpufreq << "\n";
  }

  file.close();

  return 0;
}