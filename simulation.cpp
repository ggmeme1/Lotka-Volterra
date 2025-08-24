#include "simulation.hpp"

#include <cmath>
#include <stdexcept>
#include <limits> // Per std::numeric_limits

namespace lv {

double Simulation::abs_x(double x_rel) const {
  return x_rel * (params_.d / params_.c);
}

double Simulation::abs_y(double y_rel) const {
  return y_rel * (params_.a / params_.b);
}

double Simulation::compute_h(double x, double y) const {
  if (x <= 0. || y <= 0.) {
    return std::numeric_limits<double>::quiet_NaN();
  }
  return -params_.d * std::log(x) + params_.c * x + params_.b * y -params_.a * std::log(y);
}


Simulation::Simulation(Parameters params, double x0, double y0, double dt)
    : params_{params}, dt_{dt} {
  if (params.a <= 0. || params.b <= 0. || params.c <= 0. || params.d <= 0.) {
    throw std::invalid_argument("All parameters must be positive.");
  }
  if (x0 <= 0. || y0 <= 0.) {
    throw std::invalid_argument("Initial populations must be positive.");
  }
  if (dt <= 0.) {
    throw std::invalid_argument("Time step dt must be positive.");
  } 

  const double x_eq = params_.d / params_.c;
  const double y_eq = params_.a / params_.b;

  x_rel_ = x0 / x_eq;
  y_rel_ = y0 / y_eq;

  history_.push_back({x0, y0, compute_h(x0, y0)});
}

void Simulation::evolve() {
  const double x_rel_prev = x_rel_;
  const double y_rel_prev = y_rel_;

  // Discretized equations using relative values for stability
  x_rel_ = x_rel_prev + params_.a * (1. - y_rel_prev) * x_rel_prev * dt_;
  y_rel_ = y_rel_prev + params_.d * (x_rel_prev - 1.) * y_rel_prev * dt_;

  // Populations cannot be negative
  if (x_rel_ <= 0. || y_rel_ <= 0.) {
    x_rel_ = 0.;
    y_rel_ = 0.;
  }

  const double x_abs = abs_x(x_rel_);
  const double y_abs = abs_y(y_rel_);

  history_.push_back({x_abs, y_abs, compute_h(x_abs, y_abs)});
}

void Simulation::run(int steps) {
  for (int i = 0; i < steps; ++i) {
    evolve();
  }
}

const std::vector<State>& Simulation::history() const { return history_; }

State Simulation::current_state() const { return history_.back(); }


}  // namespace lv