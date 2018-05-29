//#define BOOST_PYTHON_STATIC_LIB
#define BOOST_PYTHON_DYNAMIC_LIB

#include <iostream>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include <boost/random/taus88.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include "Hull.h"
#include "LogDensity.h"

namespace py = boost::python;
namespace np = boost::python::numpy;

typedef boost::taus88 base_generator_type;
base_generator_type generator(0);

boost::uniform_real<> uni_dist(0, 1);
boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(generator, uni_dist);


np::ndarray GetUniform(const int n)
{
	np::initialize();

	double * data = new double[n];

	for (int i = 0; i < n; i++) {
		data[i] = uni();
	}

	py::tuple shape = py::make_tuple(n);
	np::dtype dtype = np::dtype::get_builtin<double>();
	py::tuple stride = py::make_tuple(sizeof(double));
	np::ndarray a = np::from_data(data, dtype, shape, stride, py::object());
	return a;
}

np::ndarray GetGamma(const double alpha, const double beta, const int n)
{
	np::initialize();
	double pdf_args[] = { alpha, beta };

	Hull<GammaDistribution, base_generator_type> hull;
	hull.initialize(1.0, 2.0, pdf_args);

	double * data = new double[n];

	for (int i = 0; i < n; i++) {
		double x_star;
		int hull_sample_success = hull.drawSample(uni, x_star);
		if (hull_sample_success == 0) {
			hull.printHull();
			throw std::exception("Maximum iterations reached in adaptive rejection sampler");
		}
		data[i] = x_star;
	}

	py::tuple shape = py::make_tuple(n);
	np::dtype dtype = np::dtype::get_builtin<double>();
	py::tuple stride = py::make_tuple(sizeof(double));
	np::ndarray a = np::from_data(data, dtype, shape, stride, py::object());
	return a;
}

BOOST_PYTHON_MODULE(ars)
{
	py::def("get_uniform", GetUniform);
	py::def("get_gamma", GetGamma);
}