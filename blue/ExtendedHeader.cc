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
#include "ExtendedHeader.h"

#include "utils/utilsError.h"

namespace blue
{

	using utils::ESUCCESS;
	using utils::ECORRUPTKEYWORDS;
	
	ExtendedHeader::ExtendedHeader() :
	read_ascii_(false),
	keyword_error_(ESUCCESS)
	{
	}

	int ExtendedHeader::loadFromBuffer(const void *buffer, int count, bool byteswap) 
	{
		const char *bb = static_cast<const char*>(buffer);
		const int NN = count;

		read_ascii_ = MartesKey::IsMartesKeywordBuffer(bb, byteswap);

		int nn = 0;

		if (!read_ascii_)
		{
			while(nn<NN)
			{
				MidasKey mk(bb+nn, NN-nn, byteswap);
				if (!mk.isValid())
				{
					return keyword_error_ = ECORRUPTKEYWORDS;
				}
				if (keyParsed_(&mk, nn))
				{
					if (!keys_.insert(Keyword(mk)).second)
					{
					}
				}
				nn += mk.getLength();
			}

			if (nn!=NN)
			{
				return keyword_error_ = ECORRUPTKEYWORDS;
			}
		}
		else
		{
			while(nn<NN)
			{
				MartesKey mk(bb+nn, byteswap);
				int loc=nn;
				nn = mk.nextOffset();
				if (nn<=0)
				{
					return keyword_error_ = ECORRUPTKEYWORDS;
				}
				if (keyParsed_(&mk, loc))
				{
					if (!keys_.insert(Keyword(mk)).second)
					{
					}
				}
			}

			if (nn>NN)
			{
				return keyword_error_ = ECORRUPTKEYWORDS;
			}	
		}

		return 0;
	}

	int ExtendedHeader::getKeywords(std::vector<Keyword> *kws) const
	{
		if (keyword_error_)
		{
			return keyword_error_;
		}

		std::set<Keyword>::const_iterator it = keys_.begin();

		for ( ; it != keys_.end(); ++it)
		{
			kws->push_back(it->duplicate());
		}

		return 0;
	}

}
