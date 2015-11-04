/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, CERN, Summer 2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef DEBUG_HH
#define DEBUG_HH

#define DUMP(x) std::cout << #x << " = " << x << std::endl

#define DUMPVECTOR(x) for(int iti = 0; iti < x.size(); ++iti) std::cout << #x << "[" << iti << "] = " << x[iti] << std::endl

#define DUMPMAP(x) for(int iti = 0; iti < x.size(); ++iti) for(int itj = 0; itj < x[0].size(); ++itj) std::cout << #x << "[" << iti << "][" << itj << "] = " << x[iti][itj] << std::endl

#define DUMPCUBE(x) for(int iti = 0; iti < x.size(); ++iti) for(int itj = 0; itj < x[0].size(); ++itj) for(int itk = 0; itk < x[0][0].size(); ++itk) std::cout << #x << "[" << iti << "][" << itj << "][" << itk << "] = " << x[iti][itj][itk] << std::endl

#endif
