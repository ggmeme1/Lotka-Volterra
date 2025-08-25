#include "simulation.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

int main()
{
  try
  {
    // System parameters (alpha, beta, gamma, delta)
    const lv::Parameters params{.a = 0.8, .b = 0.004, .c = 0.002, .d = 0.3};

    // Initial populations for prey (x0) and predators (y0)
    const double x0 = 200.0;
    const double y0 = 80.0;

    // Simulation settings
    const double dt = 0.001;
    int num_steps = 0;
    std::cout << "How many steps would you do in this simulation: " << '\n';
    std::cin >> num_steps;
   
    // Create and run the simulation
    lv::Simulation sim(params, x0, y0, dt);
    sim.run(num_steps);

    // Write results to a CSV file
    std::ofstream outfile{"results.csv"};
    if (!outfile)
    {
      throw std::runtime_error("Failed to open results.csv for writing.");
    }

    // Write CSV header
    outfile << "step,time,x,y,invariant\n";

    const auto &history = sim.history();
    for (size_t i = 0; i < history.size(); ++i)
    {
      const auto &state = history[i];
      outfile << i << ',' << i * dt << ',' << state.x << ',' << state.y << ','
              << state.invariant << '\n';
    }

    std::cout << "Simulation finished. " << history.size()
              << " states written to results.csv.\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << "Caught exception: '" << e.what() << "'\n";
    return EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}