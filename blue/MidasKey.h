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
#ifndef MIDAS_KEY_H
#define MIDAS_KEY_H

#include "Format.h"

#include <stdint.h>
#include <string>
#include <vector>

namespace blue
{

	struct midaskeystruct
	{
		int32_t next_offset;
		int16_t non_data_len;
		char name_len;
		char format;
		char data[1];
	};

	class MidasKey
	{
		public:
			MidasKey(const char *buffer, int count, bool byteswap);

			bool isValid() const;

			int getCount() const;

			int getLength() const { return midas_->next_offset; }

			char getFormat() const { return midas_->format; }
			
			std::string getName() const;

			const char *getAllValues() const { return midas_->data; }

			static int PackMemory(const char *keyname, const void *keydata,
						int elementcount, Format fmt,
						std::vector<char> *buff);

			static inline int PackMemory(const std::string &name,
							const std::string &asciidata,
							std::vector<char> *buff) { if (asciidata[0] == '\0') { return 0; } return PackMemory(name.c_str(), &(asciidata[0]), asciidata.size(), ASCII, buff); }

			static inline int PackMemory(const std::string &keyname, const void *keydata,
							int count, Format fmt,
							std::vector<char> *buff) { return PackMemory(keyname.c_str(), keydata, count, fmt, buff); }

		private:
			midaskeystruct *midas_;
	};

}

#endif
