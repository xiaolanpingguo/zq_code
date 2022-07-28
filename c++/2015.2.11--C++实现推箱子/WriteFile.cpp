#include "WriteFile.h"
#include <iostream>
#include "Map.h"

void CWriteFile::SaveFile(const char* filename,CMap* map)
{
	FILE* pf = 0;
	fopen_s(&pf,filename,"wb");

	int gq = map->GetGuanQia();
	fwrite(&gq,4,1,pf);
	fwrite(map->GetMap(),map->GetMapDaXiao(),1,pf);

	fclose(pf);
}