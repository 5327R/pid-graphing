#include "matplot/backend/gnuplot.h"
#include "matplot/backend/opengl.h"
#include "matplot/util/handle_types.h"
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
                              matplot::figure_handle fig,
                              int max_points = 500) {

  double target = 1000;
  double start = 0.01;
  double incr = 0.01;
  double err = 0;
  double time = 0;
  std::vector<double> p;
  std::vector<double> y;
  std::vector<double> x;

  auto ax = fig->current_axes();

  for (int i = 0; i < max_points; i++) {

    y.push_back(start);
    x.push_back(i);
    err = target - start;
    incr = process_input(err, p, Kp, Ki, Kd);
    start += incr;
    /* std::cout << "current:" << start << " incr: " << incr << "\n" <<
     * std::endl; */
  }
  return y;
}

int main() {
  /**/
  auto fig = matplot::figure<matplot::backend::gnuplot>(true);

  auto ax = fig->current_axes();

  std::vector<double> test = test_vals(0.1, 0.0001, 0.005, fig);
  std::vector<double> test2 = test_vals(1.0, 0.01, 0.05, fig);
  std::vector<double> test3 = test_vals(0.01, 0.02, 0.5, fig);
  /* ax->plot(matplot::iota(0, 100), test); */
  /* ax->hold(matplot::on); */
  /* ax->plot(matplot::iota(0, 100), test2); */
  /* ax->plot(matplot::iota(0, 100), test3); */
  ax->plot(test);
  ax->hold(true);
  ax->plot(test2);
  ax->plot(test3);

  fig->show();

  /**/

  return 0;
}
