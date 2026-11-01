#include <fstream>
#include <iostream>
#include <string>

#include "simulation.hpp"

// parameters input at runtime
void insert_params(simul_params& params) {
  std::cout << "Provide initial number of preys (x): ";
  std::cin >> params.initial_x;

  std::cout << "Provide initial number of predators (y): ";
  std::cin >> params.initial_y;

  std::cout << "Provide reproductive coefficient of preys (A): ";
  std::cin >> params.a;

  std::cout << "Provide mortality coefficient of preys (B): ";
  std::cin >> params.b;

  std::cout << "Provide reproductive coefficient of predators (C): ";
  std::cin >> params.c;

  std::cout << "Provide mortality coefficient of preys (D): ";
  std::cin >> params.d;

  std::cout << "Provide time step for calculation: ";
  std::cin >> params.dt;
}

int main(int argc, char* argv[]) {
  simul_params params;

  int time_steps;

  // handling wrong number of parameters:
  if (argc != 8 && argc != 1) {
    std::cerr << "Provide 0 or 7 parameters from command line" << std::endl;
    return 1;
  }

  try {
    // passing parameters:
    if (argc == 8) {  // during invokation
      params.initial_x = std::stod(argv[1]);
      params.initial_y = std::stod(argv[2]);
      params.a = std::stod(argv[3]);
      params.b = std::stod(argv[4]);
      params.c = std::stod(argv[5]);
      params.d = std::stod(argv[6]);
      params.dt = std::stod(argv[7]);
    } else if (argc == 1) {
      insert_params(params);
    }

    if (params.dt > 0.01 || params.dt < 0.0001) {
      std::cerr
          << "\n[WARNING]: Time step provided (" << params.dt
          << ") is not of the order of 0.001: simulation might diverge.\n\n";
    }

    // total time steps:
    std::cout
        << "Provide total calculation time as multiple of chosen time step: "
        << std::endl;
    std::cin >> time_steps;

    Simulation simulation(params);

    // opening .txt file for result saving:
    std::ofstream file("simulation_output.txt");

    if (!file.is_open()) {
      std::cerr << "Error while opening result file" << std::endl;

      return 1;
    }

    // main loop for whole calculation:
    for (int i = 0; i < time_steps + 1; ++i) {
      // saving current state:
      file << simulation.get_absolute_x() << " ";
      file << simulation.get_absolute_y() << std::endl;

      // printing info:
      std::cout << simulation.info() << std::endl;

      // evolving:
      simulation.evolve();
    }

    file.close();

    if (file.fail()) {
      std::cerr << "Error while closing result file" << std::endl;

      return 1;
    };

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}