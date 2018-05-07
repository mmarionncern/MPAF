#ifndef JSONUtils_hh
#define JSONUtils_hh

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

class JSONUtils{

public:
  JSONUtils();
  JSONUtils(std::string fname);
  
  ~JSONUtils();

  bool isGoldenEvent(int run, int lumi);

private:

  void readJSON();

  std::string _fname;

  std::map<int, std::vector<std::vector<int> > > _goodLumis;
  std::map<int, std::vector<std::vector<int> > >::const_iterator _itGL;
  
};

#endif
