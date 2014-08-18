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
