#include "analysis/utils/PythonUtils.hh"

// #include <cstdlib>  // setenv, atoi
// #include <iostream> // cerr, cout, endl
// #include <boost/python.hpp>

PythonUtils::PythonUtils() {

  init();
}

PythonUtils::PythonUtils(std::string macroName, std::string fctName ) {

  _macroN=macroName;
  _fctN=fctName;
  
  init();
}

PythonUtils::~PythonUtils() {

}

void
PythonUtils::init() {

  // Explicitly add initializers for staticly linked modules.
  //PyImport_AppendInittab("hello", &inithello);

  // Initialize Python.
  setenv("PYTHONPATH", ".", 1);
  Py_Initialize();


}

float
PythonUtils::exec(int narg, char* argv[]) {

  namespace python = boost::python;
  try {
    // Convert remaining args into a Python list of integers.
    python::list args;
    for (int i=3; i < narg; ++i)
      {
	args.append(std::atof(argv[i]));
      }

    // Import the user requested module.
    // >>> import module
    python::object module = python::import(_macroN.c_str());

    // Invoke the user requested function with the provided arguments.
    // >>> result = module.fn(*args)
    python::object result = module.attr(_fctN.c_str())(*python::tuple(args));

    // Print the result.
    std::cout << python::extract<float>(result)() << std::endl;
    return python::extract<float>(result)();
  }
  catch (const python::error_already_set&)
  {
    PyErr_Print();
    return -100;
  }


}
