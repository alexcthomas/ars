//#define BOOST_PYTHON_STATIC_LIB
#define BOOST_PYTHON_DYNAMIC_LIB

#include <iostream>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include <boost/random/taus88.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>

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

BOOST_PYTHON_MODULE(ars)
{
	py::def("GetUniform", GetUniform);
}