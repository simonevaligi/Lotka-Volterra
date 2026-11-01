#include "simulation.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>

// parameters constraints:
void check_params(simul_params const& params) {
  // initial conditions:
  if (params.initial_x <= 0) {
    throw std::invalid_argument(
        "Initial number of preys must be > 0: invalid parameter value "
        "initial_x");
  }

  if (params.initial_y <= 0) {
    throw std::invalid_argument(
        "Initial number of predators must be > 0: invalid parameter value "
        "initial_y");
  }

  // LV-DE parameters:
  if (params.a <= 0) {
    throw std::invalid_argument(
        "Preys' reproductivity must be > 0: invalid parameter value A");
  }

  if (params.b <= 0) {
    throw std::invalid_argument(
        "Preys' mortality must be > 0: invalid parameter value B");
  }

  if (params.c <= 0) {
    throw std::invalid_argument(
        "Predators' reproductivity must be > 0: invalid parameter value C");
  }

  if (params.d <= 0) {
    throw std::invalid_argument(
        "Predators' mortality must be > 0: invalid parameter value D");
  }

  // time step:
  if (params.dt <= 0) {
    throw std::invalid_argument(
        "Simulation time step must be > 0: invalid parameter value dt");
  }
}

// constructor:
Simulation::Simulation(simul_params const& params) {
  // parameters checking:
  check_params(params);

  A = params.a;
  B = params.b;
  C = params.c;
  D = params.d;

  T = 0.0;
  dT = params.dt;

  // equilibrium point:
  x_eq = D / C;
  y_eq = A / B;

  // x and y initialization:
  x_rel = (x_eq != 0) ? (params.initial_x / x_eq) : 0;
  y_rel = (y_eq != 0) ? (params.initial_y / y_eq) : 0;
}

// normalized variables method:
double Simulation::get_relative_x() const { return x_rel; }
double Simulation::get_relative_y() const { return y_rel; }

// absolute variables method:
double Simulation::get_absolute_x() const { return x_rel * x_eq; }
double Simulation::get_absolute_y() const { return y_rel * y_eq; }

// equilbrium point method:
double Simulation::get_x_eq() const { return x_eq; }
double Simulation::get_y_eq() const { return y_eq; }

// total time method:
double Simulation::get_time() const { return T; }

// method for calculation of integral of motion:
double Simulation::get_H() const {
  // auxiliary variables:
  double x_abs = get_absolute_x();
  double y_abs = get_absolute_y();

  return -D * std::log(x_abs) + C * x_abs + B * y_abs - A * std::log(y_abs);
}

// time evolution method:
void Simulation::evolve() {
  T += dT;

  y_rel += D * (x_rel - 1.0) * y_rel * dT;
  x_rel += A * (1.0 - y_rel) * x_rel * dT;

  // ensuring positive new relative values:
  if (x_rel <= 0 || y_rel <= 0) {
    throw std::runtime_error(
        "Error: Invalid state occurred, x and y values must be positive");
  }

  // ensuring non-infinite new relative values:
  if (std::isinf(x_rel) || std::isinf(y_rel)) {
    throw std::runtime_error(
        "Error: Invalid state occurred, overflow during simulation");
  }
}

// method for info on current state:
std::string Simulation::info() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(4);  // decimal points

  oss << "T: " << std::left << std::setw(8) << T << " | x: " << get_absolute_x()
      << std::endl;
  oss << std::string(12, ' ') << " | y: " << get_absolute_y() << std::endl;
  oss << std::string(12, ' ') << " | H: " << get_H() << std::endl << std::endl;

  return oss.str();
}
