#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "simulation.hpp"

int main() {
  try {
    lv::Parameters params{};

    const double x0 = 200.0;
    const double y0 = 80.0;
    const double dt = 0.001;

    int num_steps = 0;

    std::cout << "--- Lotka-Volterra Simulation Setup ---\n";
    std::cout << "Please provide the four model parameters.\n";

    std::cout << "Enter parameter A (prey growth rate, e.g., 0.8): ";
    std::cin >> params.a;
    if (std::cin.fail()) {
      std::cerr << "Error: Invalid input for parameter A.\n";
      return EXIT_FAILURE;
    }

    std::cout << "Enter parameter B (prey death rate, e.g., 0.004): ";
    std::cin >> params.b;
    if (std::cin.fail()) {
      std::cerr << "Error: Invalid input for parameter B.\n";
      return EXIT_FAILURE;
    }

    std::cout << "Enter parameter C (predator growth rate, e.g., 0.002): ";
    std::cin >> params.c;
    if (std::cin.fail()) {
      std::cerr << "Error: Invalid input for parameter C.\n";
      return EXIT_FAILURE;
    }

    std::cout << "Enter parameter D (predator death rate, e.g., 0.3): ";
    std::cin >> params.d;
    if (std::cin.fail()) {
      std::cerr << "Error: Invalid input for parameter D.\n";
      return EXIT_FAILURE;
    }

    std::cout << "How many steps would you do in this simulation: " << '\n';
    std::cin >> num_steps;

    if (std::cin.fail() || num_steps <= 0) {
      std::cerr << "Error: Invalid input. Please provide a positive number of "
                   "steps.\n";
      return EXIT_FAILURE;
    }

    // Create and run the simulation
    lv::Simulation sim(params, x0, y0, dt);
    sim.run(num_steps);

    std::ofstream outfile{"results.txt"};
    if (!outfile) {
      throw std::runtime_error("Failed to open results.txt for writing.");
    }

    outfile << "step,time,x,y,invariant\n";

    const auto &history = sim.history();
    for (size_t i = 0; i < history.size(); ++i) {
      const auto &state = history[i];
      outfile << i << ',' << i * dt << ',' << state.x << ',' << state.y << ','
              << state.invariant << '\n';
    }

    std::cout << "Simulation finished. " << history.size()
              << " states written to results.txt.\n";
  } catch (const std::exception &e) {
    std::cerr << "Caught exception: '" << e.what() << "'\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}