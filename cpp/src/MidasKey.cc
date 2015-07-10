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
#include "MidasKey.h"

#include "ByteSwap.h"
#include "Format.h"
#include "utils/utilsByteSwap.h"

#include <cstring>

namespace blue
{

	MidasKey::MidasKey(const char *buffer, int count, bool byteswap) :
	midas_(NULL)
	{
		const midaskeystruct *mks = reinterpret_cast<const midaskeystruct *>(buffer);
		int32_t size = mks->next_offset;

		if (byteswap)
		{
			utils::byteswap(&size);
		}

		if (size <= 0 || size > count)
		{
			return;
		}

		midas_ = reinterpret_cast<midaskeystruct *>(new char[size]);
		memcpy(midas_, buffer, size);

		if (byteswap)
		{
			utils::byteswap(&midas_->next_offset);
			utils::byteswap(&midas_->non_data_len);

			Format format("SB");
			format.SecondChar(midas_->format);

			if (format.getScalarSize() > 1)
			{
				Byteswap(midas_->data, getCount(), format);
			}
		}

		if (midas_->format == '0')
		{
			for (int i = 0; i < getCount(); ++i)
			{
				midas_->data[i] = 0x80 ^ midas_->data[i];
			}
		}
	}

	bool MidasKey::isValid() const
	{
		if (!midas_)
		{
			return false;
		}

		if (!Format::IsValidFormatCode(midas_->format))
		{
			return false;
		}

		if (midas_->name_len < 1)
		{
			return false;
		}

		if (midas_->name_len > midas_->next_offset)
		{
			return false;
		}

		if (midas_->next_offset < midas_->non_data_len)
		{
			return false;
		}

		if (midas_->name_len > midas_->non_data_len)
		{
			return false;
		}

		if (midas_->non_data_len - midas_->name_len > 1024)
		{
			return false;
		}

		return true;
	}

	int MidasKey::getCount() const
	{
		Format format("SB");
		format.SecondChar(midas_->format);

		if (format.getScalarSize() == 0)
		{
			return 0;
		}

		return (midas_->next_offset - midas_->non_data_len) / format.getScalarSize();
	}

	std::string MidasKey::getName() const
	{
		if (!midas_)
		{
			return "** NULL KEY **";
		}

		char *name = midas_->data + midas_->next_offset - midas_->non_data_len;
		return std::string(name, midas_->name_len);
	}

	int MidasKey::PackMemory(const char *keyname, const void *keydata,
					int elementcount, Format fmt,
					std::vector<char> *buff)
	{
		if (!keyname || !*keyname || !keydata || !elementcount)
		{
			return 0;
		}

		int datalen = elementcount * fmt.getScalarSize();
		int namelen = std::strlen(keyname);
		int pad = (8 - (datalen + namelen) % 8) % 8;
		int bufflen = datalen + namelen + pad + 8;

		midaskeystruct mks;
		mks.next_offset = bufflen;
		mks.non_data_len = bufflen - datalen;
		mks.name_len = namelen;
		mks.format = fmt.formatCode();

		buff->insert(buff->end(), (char *) &mks, (char *) &mks + 8);
		buff->insert(buff->end(), (char *) keydata, (char *) keydata + datalen);
		buff->insert(buff->end(), keyname, keyname + namelen);

		if (pad)
		{
			buff->insert(buff->end(), pad, 0);
		}

		return bufflen;
	}

}
