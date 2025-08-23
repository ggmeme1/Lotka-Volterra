#ifndef LV_SIMULATION_HPP
#define LV_SIMULATION_HPP

#include <vector>

namespace lv {

// Parameters for the Lotka-Volterra model
struct Parameters {
  double a;  // Prey growth rate (alpha)
  double b;  // Prey death rate (beta)
  double c;  // Predator growth rate (gamma)
  double d;  // Predator death rate (delta)
};

// Represents the system state at a specific time
struct State {
  double x;          // Prey population
  double y;          // Predator population
  double invariant;  // The conserved quantity H
};

class Simulation {
  Parameters params_;
  double dt_;
  std::vector<State> history_;
  double x_rel_;  // Current relative prey population
  double y_rel_;  // Current relative predator population

  // Private helpers to convert between relative and absolute coordinates
  double abs_x(double x_rel) const;
  double abs_y(double y_rel) const;
  double compute_h(double x, double y) const;

 public:
  // Constructor requires system parameters and initial populations (x0, y0)
  Simulation(Parameters params, double x0, double y0, double dt);

  // Advances the simulation by a single time step
  void evolve();

  // Runs the simulation for a given number of steps
  void run(int steps);

  // Accessors
  const std::vector<State>& history() const;
  State current_state() const;
};

}  // namespace lv

#endif  // LV_SIMULATION_HPP