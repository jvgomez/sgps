#include "file.h"

File::File()
{
}

File::File(path p) 
{ 
	name=p.filename();
	ppath=p.string();
	size=file_size(p);
}

File::~File()
{
}
