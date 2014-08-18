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
