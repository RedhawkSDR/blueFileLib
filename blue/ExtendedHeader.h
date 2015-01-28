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
#ifndef EXTENDED_HEADER_H
#define EXTENDED_HEADER_H

#include "Keyword.h"
#include "MartesKey.h"
#include "MidasKey.h"

#include <set>
#include <vector>

namespace blue 
{

	class ExtendedHeader 
	{
		public:
			ExtendedHeader();

			int loadFromBuffer(const void * buffer, int count, bool byteswap);
			int getKeywords(std::vector<Keyword> *keywords) const;

			bool keyParsed_(MidasKey *, int) { return true; }
			bool keyParsed_(MartesKey *, int) { return true; }

		private:
			std::set<Keyword> keys_;
			bool read_ascii_;
			mutable int keyword_error_;
	};

}

#endif
