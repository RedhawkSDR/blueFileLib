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
#include "ByteSwap.h"

#include "utils/utilsByteSwap.h"

namespace blue
{

	void Byteswap(void *buffer, int count, char formatcode)
	{
		switch (formatcode)
		{
			case 'I':
			case 'U':
				utils::byteswap(static_cast<int16_t *>(buffer), count);
				break;
	
			case 'L':
			case 'V':
			case 'F':
				utils::byteswap(static_cast<int32_t *>(buffer), count);
				break;
	
			case 'X':
			case 'D':
				utils::byteswap(static_cast<int64_t *>(buffer), count);
				break;
		}
	}

}
