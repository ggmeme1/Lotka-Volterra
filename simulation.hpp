#ifndef LV_SIMULATION_HPP
#define LV_SIMULATION_HPP

#include <vector>

namespace lv {

// Parameters for the Lotka-Volterra model
struct Parameters {
  double a;  
  double b; 
  double c; 
  double d; 
};

// Represents the system state at a specific time
struct State {
  double x;          
  double y;          
  double invariant;  
};

class Simulation {
  Parameters params_;
  double dt_;
  std::vector<State> history_;
  double x_rel_; 
  double y_rel_;  

  // convert between relative and absolute coordinates
  double abs_x(double x_rel) const;
  double abs_y(double y_rel) const;
  double compute_h(double x, double y) const;

 public:

  Simulation(Parameters params, double x0, double y0, double dt);

  // Advances the simulation 
  void evolve();


  void run(int steps);

  // Accessors
  const std::vector<State>& history() const;
  State current_state() const;
};

}  

#endif 