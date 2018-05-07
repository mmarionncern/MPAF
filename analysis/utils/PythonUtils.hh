#include <cstdlib>  // setenv, atoi
#include <iostream> // cerr, cout, endl
#include <string>
#include <boost/python.hpp>

class PythonUtils{

public:
  
  PythonUtils();
  PythonUtils(std::string macroName, std::string fctName );
  ~PythonUtils();

  float exec(int narg, char* argv[]);
  
private:
  
  void init();

  std::string _macroN;
  std::string _fctN;
  

};
