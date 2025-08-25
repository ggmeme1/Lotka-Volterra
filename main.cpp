#include "simulation.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

int main()
{
  try
  {

    const lv::Parameters params{.a = 0.8, .b = 0.004, .c = 0.002, .d = 0.3};

    const double x0 = 200.0;
    const double y0 = 80.0;

    const double dt = 0.001;
    int num_steps = 0;
    std::cout << "How many steps would you do in this simulation: " << '\n';
    std::cin >> num_steps;
    
    if (std::cin.fail() || num_steps <= 0)
    {
      std::cerr << "Error: Invalid input. Please provide a positive number of steps.\n";
      return EXIT_FAILURE;
    }

    // Create and run the simulation
    lv::Simulation sim(params, x0, y0, dt);
    sim.run(num_steps);

    std::ofstream outfile{"results.txt"};
    if (!outfile)
    {
      throw std::runtime_error("Failed to open results.txt for writing.");
    }

    outfile << "step,time,x,y,invariant\n";

    const auto &history = sim.history();
    for (size_t i = 0; i < history.size(); ++i)
    {
      const auto &state = history[i];
      outfile << i << ',' << i * dt << ',' << state.x << ',' << state.y << ','
              << state.invariant << '\n';
    }

    std::cout << "Simulation finished. " << history.size()
              << " states written to results.txt.\n";
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