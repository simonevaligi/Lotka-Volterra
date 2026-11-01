#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <string>

struct simul_params {
  // initial conditions:
  double initial_x;
  double initial_y;

  // LV-DE parameters:
  double a;  // reproductivity x
  double b;  // mortality x
  double c;  // reproductivity y
  double d;  // mortality y

  // time step:
  double dt;
};

class Simulation {
 private:
  // x preys, y predators relative to eq pt:
  double x_rel, y_rel;

  // LV-DE parameters:
  double A, B, C, D;

  // equilibrium point:
  double x_eq;
  double y_eq;

  // global time and time step:
  double T;
  double dT;

 public:
  Simulation(simul_params const& params);

  double get_relative_x() const;
  double get_relative_y() const;

  double get_absolute_x() const;
  double get_absolute_y() const;

  double get_x_eq() const;
  double get_y_eq() const;

  double get_time() const;

  double get_H() const;

  void evolve();
  std::string info() const;
};

#endif