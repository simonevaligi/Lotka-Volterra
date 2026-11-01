#define DOCTEST_COMFIG_IMPLEMENT_WITH_MAIN

#include <cmath>
#include <stdexcept>

#include "../source/simulation.hpp"
#include "doctest.h"

TEST_CASE("Testing initial parameters") {
  SUBCASE("Valid parameters:") {
    simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 0.001};

    CHECK_NOTHROW({
      Simulation s = Simulation(params);
      (void)s;
    });
  }

  ////////  ////////  ////////  ////////  ////////  ////////  ////////

  SUBCASE("Zero initial_x:") {
    simul_params params{0.0, 4.3, 0.1, 0.02, 0.05, 0.1, 0.001};
    CHECK_THROWS_AS(Simulation s(params), std::invalid_argument);
  }

  SUBCASE("Negative initial_x:") {
    simul_params params{-1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 0.001};

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;
        },
        std::invalid_argument);
  }

  SUBCASE("Zero initial_y:") {
    simul_params params{1.8, 0.0, 0.1, 0.02, 0.05, 0.1, 0.001};
    CHECK_THROWS_AS(Simulation s(params), std::invalid_argument);
  }

  SUBCASE("Negative initial_y:") {
    simul_params params{1.8, -4.3, 0.1, 0.02, 0.05, 0.1, 0.001};

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;
        },
        std::invalid_argument);
  }

  ////////  ////////  ////////  ////////  ////////  ////////  ////////

  SUBCASE("Zero A::") {
    simul_params params{1.8, 4.3, 0.0, 0.02, 0.05, 0.1, 0.001};

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;
        },
        std::invalid_argument);
  }
  SUBCASE("Zero B:") {
    simul_params params{1.8, 4.3, 0.1, 0.0, 0.05, 0.1, 0.001};

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;
        },
        std::invalid_argument);
  }
  SUBCASE("Zero C:") {
    simul_params params{1.8, 4.3, 0.1, 0.02, 0.0, 0.1, 0.001};

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;
        },
        std::invalid_argument);
  }
  SUBCASE("Zero D:") {
    simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.0, 0.001};

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;
        },
        std::invalid_argument);
  }

  ////////  ////////  ////////  ////////  ////////  ////////  ////////

  SUBCASE("Zero dt:") {
    simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 0.0};
    CHECK_THROWS_AS(Simulation s(params), std::invalid_argument);
  }

  SUBCASE("Negative dt:") {
    simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, -0.001};

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;
        },
        std::invalid_argument);
  }
}

// =============================================================

TEST_CASE("Populations evolution:") {
  simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 0.001};
  Simulation simulation(params);

  // checking no exceptions during evolution:
  CHECK_NOTHROW(simulation.evolve());

  // ensuring x and y to be positive and not infinite:
  for (int i = 0; i < 1000; ++i) {
    simulation.evolve();

    CHECK(simulation.get_absolute_x() > 0.0);
    CHECK(simulation.get_absolute_y() > 0.0);

    CHECK_FALSE(std::isinf(simulation.get_absolute_x()));
    CHECK_FALSE(std::isinf(simulation.get_absolute_y()));
  }
}

// =============================================================

TEST_CASE("Testing equilibrium point and relative values calculation:") {
  simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 0.001};
  Simulation s = Simulation(params);

  SUBCASE("Explicit equilbrium point calculation: ") {
    CHECK(s.get_x_eq() == doctest::Approx(2.0));
    CHECK(s.get_y_eq() == doctest::Approx(5.0));
  }

  SUBCASE("Absolute values calculation:") {
    CHECK(s.get_absolute_x() == doctest::Approx(1.8));
    CHECK(s.get_absolute_y() == doctest::Approx(4.3));
  }

  SUBCASE("Relative values calculation:") {
    CHECK(s.get_relative_x() == doctest::Approx(0.9));
    CHECK(s.get_relative_y() == doctest::Approx(0.86));
  }
}

// =============================================================

TEST_CASE("Testing one integration step:") {
  simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 0.001};
  Simulation s = Simulation(params);

  s.evolve();

  // expected 1-step values calculated by-hand:
  double expected_y_rel = 0.8599914;
  double expected_x_rel = 0.9000126;

  CHECK(s.get_absolute_y() == doctest::Approx(expected_y_rel * 5.0));
  CHECK(s.get_absolute_x() == doctest::Approx(expected_x_rel * 2.0));
}

// =============================================================

TEST_CASE(
    "Testing initial conditions at equilibrium, system must remain stable:") {
  simul_params params{2.0, 5.0, 0.1, 0.02, 0.05, 0.1, 0.001};
  Simulation s = Simulation(params);

  for (int i = 0; i < 10000; ++i) {
    s.evolve();
  }

  CHECK(s.get_absolute_x() == doctest::Approx(2.0));
  CHECK(s.get_absolute_y() == doctest::Approx(5.0));
}

// =============================================================

TEST_CASE("Testing simulation global time T:") {
  simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 0.001};
  Simulation s = Simulation(params);

  CHECK(s.get_time() == doctest::Approx(0.0));

  for (int i = 0; i < 15; ++i) {
    s.evolve();
  }

  CHECK(s.get_time() == doctest::Approx(0.015));
}

// =============================================================

TEST_CASE("Testing H(x,y) calculation and conservation:") {
  simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 0.001};
  Simulation s = Simulation(params);

  SUBCASE("H(x,y) calculation:") {
    CHECK(s.get_H() == doctest::Approx(-0.02864).epsilon(0.001));
  }

  SUBCASE("H(x,y) conservation") {
    double h = s.get_H();

    for (int i = 0; i < 10000; i++) {
      s.evolve();
    }

    CHECK(s.get_H() == doctest::Approx(h).epsilon(0.01));
  }
}

// =============================================================

TEST_CASE("Testing simulation string:") {
  simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 0.001};
  Simulation s = Simulation(params);

  std::string state = s.info();

  CHECK(state.find("| x: 1.8000") != std::string::npos);
  CHECK(state.find("| y: 4.3000") != std::string::npos);
  CHECK(state.find("T: 0.0000") != std::string::npos);
}

// =============================================================

TEST_CASE("Testing simulation divergence at large dt:") {
  simul_params params{1.8, 4.3, 0.1, 0.02, 0.05, 0.1, 150.0};

  Simulation s = Simulation(params);

  CHECK_THROWS_AS(
      {
        for (int i = 0; i < 5; ++i) {
          s.evolve();
        }
      },
      std::runtime_error);
}