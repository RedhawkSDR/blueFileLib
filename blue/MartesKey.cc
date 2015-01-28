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
#include "MartesKey.h"

#include "utils/utilsByteSwap.h"

namespace
{

	inline int Roundup(int nn)
	{
		return nn % 4 ? (nn/4 + 1) * 4 : nn;
	}

}

namespace blue
{

	MartesKey::MartesKey(const char *buffer, bool byteswap)
	{
		martes_ = *reinterpret_cast<const marteskeystruct *>(buffer);
		
		if (byteswap)
		{
			utils::byteswap(&(martes_.key_offset));
			utils::byteswap(&(martes_.key_length));
			utils::byteswap(&(martes_.name_length));
		}
		
		data_ = buffer + 12;
	}

	int MartesKey::getLength() const
	{
		return 12 + Roundup(martes_.key_length) + Roundup(martes_.name_length);
	}

	std::string MartesKey::getName() const
	{
		return std::string(data_, martes_.name_length);
	}

	std::string MartesKey::getData() const
	{
		return std::string(data_ + Roundup(martes_.name_length), martes_.key_length);
	}

	bool MartesKey::IsMartesKeywordBuffer(const char *buffer, bool byteswap)
	{
		MartesKey mk(buffer, byteswap);
		return mk.nextOffset() == mk.getLength();
	}

}
