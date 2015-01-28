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
#ifndef MARTES_KEY_H
#define MARTES_KEY_H

#include <stdint.h>
#include <string>

namespace blue
{

	struct marteskeystruct
	{
		int32_t key_offset;
		int32_t name_length;
		int32_t key_length;
	};

	class MartesKey
	{
		public:
			MartesKey(const char *buff, bool byteswap);

			int getLength() const;

			std::string getName() const;

			std::string getData() const;

			int nextOffset() const { return martes_.key_offset; }
			
			static bool IsMartesKeywordBuffer(const char *buff, bool byteswap);

		private:
			marteskeystruct martes_;
			const char *data_;
	};

}

#endif
