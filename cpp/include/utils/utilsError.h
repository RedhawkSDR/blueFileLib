/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file distributed with this
 * source distribution.
 *
 * This file is part of REDHAWK blueFileLib.
 *
 * REDHAWK blueFileLib is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * REDHAWK blueFileLib is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this
 * program.  If not, see http://www.gnu.org/licenses/.
 */
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
