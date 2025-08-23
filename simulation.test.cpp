#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "simulation.hpp"

#include "doctest.h"

TEST_CASE("Testing Simulation Initialization") {
  const lv::Parameters params{.a = 1., .b = 1., .c = 1., .d = 1.};

  SUBCASE("Valid initialization") {
    lv::Simulation sim(params, 100., 50., 0.01);
    auto state = sim.current_state();
    CHECK(state.x == doctest::Approx(100.));
    CHECK(state.y == doctest::Approx(50.));
  }

  SUBCASE("Invalid parameters or populations throw exceptions") {
    CHECK_THROWS_AS(lv::Simulation({0., 1., 1., 1.}, 100., 50., 0.01),
                    std::invalid_argument);
    CHECK_THROWS_AS(lv::Simulation(params, 0., 50., 0.01),
                    std::invalid_argument);
    CHECK_THROWS_AS(lv::Simulation(params, 100., 50., 0.),
                    std::invalid_argument);
  }
}

TEST_CASE("Testing Evolution Logic") {
  const lv::Parameters params{.a = 0.8, .b = 0.004, .c = 0.002, .d = 0.3};
  const double dt = 0.001;

  SUBCASE("Equilibrium point should be stable") {
    const double x_eq = params.d / params.c;  // 150
    const double y_eq = params.a / params.b;  // 200

    lv::Simulation sim(params, x_eq, y_eq, dt);
    sim.evolve();
    auto state = sim.current_state();

    CHECK(state.x == doctest::Approx(x_eq));
    CHECK(state.y == doctest::Approx(y_eq));
  }

  SUBCASE("A single evolution step is computed correctly") {
    lv::Simulation sim(params, 200., 80., dt);
    sim.evolve();
    auto state = sim.current_state();

    // Expected values from one step of the discretized equations
    CHECK(state.x == doctest::Approx(200.096));
    CHECK(state.y == doctest::Approx(80.008));
  }

  SUBCASE("Running for multiple steps populates history") {
    lv::Simulation sim(params, 200., 80., dt);
    sim.run(100);
    // 1 initial state + 100 evolved states
    CHECK(sim.history().size() == 101);
  }
}

TEST_CASE("Testing Invariant Conservation") {
  const lv::Parameters params{.a = 0.8, .b = 0.004, .c = 0.002, .d = 0.3};
  lv::Simulation sim(params, 200., 80., 0.001);
  sim.run(1000);

  const auto& history = sim.history();
  const double h_initial = history.front().invariant;
  const double h_final = history.back().invariant;

  // The invariant H should remain almost constant
  CHECK(h_initial == doctest::Approx(h_final).epsilon(0.01));
}