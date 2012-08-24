#ifndef DATASETFACTORY_H
#define DATASETFACTORY_H

#include "DataSet.h"
#include <vector>

/* supported datasets:
   data:
   	2011_data
   mc:
	TTJets
	WZ    
	ZZ    
	spWmWm
	spWpWp
	dpWW  
	TTG   
	TTW   
	TTZ   
	WWG   
	WWW   
	WWZ   
	WZZ   
	ZZZ   
*/
DataSet GetDataSet(const std::string& option);

std::vector<DataSet> GetDataSetVector(const std::string& option);

#endif // DATASETFACTORY_H
