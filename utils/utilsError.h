#ifndef UTILS_ERROR_H
#define UTILS_ERROR_H

#include <cerrno>

#ifdef ESUCCESS
#undef ESUCCESS
#endif

namespace utils
{

	const int FIRST_ERROR = 1000;

	enum error
	{
		ESUCCESS         = 0,			// 0      
		EBADVALUE	 = FIRST_ERROR + 6,	// 1006	Invalid parameter
		EBADHEADER       = FIRST_ERROR + 61,	// 1061	Part of the file header/structure is bad
		EINVALID_FORMAT  = FIRST_ERROR + 86,	// 1086 Specified format is invalid
		ENOTPLATINUM     = FIRST_ERROR + 91,	// 1091 Not a Platinum file.
		ENOTCLOSED       = FIRST_ERROR + 92,	// 1092 File has not been closed.
		ECORRUPTKEYWORDS = FIRST_ERROR + 93	// 1093	Bad keyword
	};

}

#endif
