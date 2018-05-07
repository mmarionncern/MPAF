#include "analysis/utils/JSONUtils.hh"
#include <boost/version.hpp>

JSONUtils::JSONUtils(std::string fname) {
  _fname=fname;
}

JSONUtils::~JSONUtils() {
}


void
JSONUtils::readJSON() {
 
  //"/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt"
  std::ifstream ifile(_fname.c_str());
  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ifile, pt);
	
  using boost::property_tree::ptree;
  ptree::const_iterator end = pt.end();
  for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
    
    std::vector<std::vector<int> > values;
    int x = 0;
    for(ptree::value_type &row : pt.get_child( it->first )) {
      values.push_back(std::vector<int>() );
      
      for(ptree::value_type &cell : row.second) {
  	values[x].push_back(cell.second.get_value<int>() );
      }
      x++;
    }

    _goodLumis[ atoi(it->first.c_str() ) ]=values;
  }

}

bool
JSONUtils::isGoldenEvent(int run, int lumi) {

  if(_goodLumis.size()==0) {//read the JSON file
    readJSON();
  }

  _itGL=_goodLumis.find(run);
  if(_itGL==_goodLumis.end()) return false; //run not in the JSON
  else {
    bool findGoodLumi=false;
    for(unsigned int il=0;il<_itGL->second.size();il++) {
      if(_itGL->second[il][0]<lumi && _itGL->second[il][1]>lumi)
	{findGoodLumi=true; break;}
    }
    return findGoodLumi;
  }
  return false;//default
}
