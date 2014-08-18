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
