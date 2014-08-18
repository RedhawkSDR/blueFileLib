#include "ExtendedHeader.h"

#include "utils/utilsError.h"

namespace blue
{

	using utils::ECORRUPTKEYWORDS;
	
	ExtendedHeader::ExtendedHeader() :
	read_ascii_(false)
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
