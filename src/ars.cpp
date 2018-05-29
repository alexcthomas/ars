#define BOOST_PYTHON_STATIC_LIB
//#define PY_MAJOR_VERSION 3
//#define PY_MINOR_VERSION 6


#include <boost/python.hpp>


char const* SayHello()
{
	return "Hello, from c++ dll!";
}
BOOST_PYTHON_MODULE(ars)
{
	using namespace boost::python;
	def("SayHello", SayHello);
}