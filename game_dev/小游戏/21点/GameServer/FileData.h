#ifndef _FILE_DATA_H_
#define _FILE_DATA_H_

#include <map>
#include <string>
#include "DataType.h"

#define _CLIENT_INFO_FILE "Íæ¼ÒÐÅÏ¢"

void GetIDPasswordFromFile(const char* fn,
						   std::map<std::string, _PLAYER>* m);
void SaveFile(const char* fn, std::map<std::string, _PLAYER>* m);


#endif