#include <matplot/matplot.h>
#include <numeric>
#include <vector>

double process_input(double error, std::vector<double> &prev, double Kp,
                     double Ki, double Kd) {
  prev.push_back(error);
  double P = Kp * error;
  double I = Ki * std::accumulate(prev.begin(), prev.end(), 0);
  double D = Kd * (error - prev[prev.size() - 2]);
  return P + I + D;
}

std::vector<double> test_vals(double Kp, double Ki, double Kd,
                              int max_points = 500) {
  double target = 1000;
  double start = 0.01;
  double incr = 0.01;
  double err = 0;
  double time = 0;
  std::vector<double> p;
  std::vector<double> y;

  for (int i = 0; i < max_points; i++) {
    y.push_back(start);
    err = target - start;
    incr = process_input(err, p, Kp, Ki, Kd);
    start += incr;
    /* std::cout << "current:" << start << " incr: " << incr << "\n" <<
     * std::endl; */
  }
  return y;
}

int main() {
  std::vector<double> test = test_vals(0.1, 0.0001, 0.005);
  std::vector<double> test2 = test_vals(1.0, 0.01, 0.05);
  std::vector<double> test3 = test_vals(0.01, 0.02, 0.5);

  matplot::figure_type f;

  /* auto ax = f.add_axes(); */
  auto ax = matplot::nexttile();

  matplot::xlabel(ax, "Time");
  matplot::ylabel(ax, "Position");

  matplot::plot(test);
  matplot::hold(matplot::on);
  matplot::plot(test2);
  matplot::plot(test3);
  matplot::show();

  return 0;
}
