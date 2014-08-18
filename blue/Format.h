#ifndef FORMAT_H
#define FORMAT_H

#include <stdint.h>
#include <string>

namespace blue
{

	const char ASCII_UNIT_SEPARATOR = 037;

	const int doubleprecision = 17;

	enum FormatEnum
	{
		FORMAT_ENUM_NOT_SET = 0,

		BYTE	= 0x42,
		OFFSET	= 0x4F,
		INTEGER = 0x49,
		LONG	= 0x4C,
		XTENDED = 0x58,
		FLOAT	= 0x46,
		DOUBLE	= 0x44,
		PACKED 	= 0x50,
		ASCII	= 0x41
	};

	class Format
	{
		private:
			union
			{
				char codes_[2];
				uint16_t format_;
			};

		public:
			Format(const char *format);
			Format(const std::string &format);
			Format(FormatEnum format);

			char rankCode() const {return codes_[0];}

			char formatCode() const {return codes_[1];}
			
			Format &SecondChar(char sc);

			int getElementSize() const;
			
			int getScalarSize() const {return GetScalarSize(codes_[1]);}

			int getNumScalars() const;
			
			bool isValid() const;

			static int  GetScalarSize(FormatEnum);
			
			static int  GetScalarSize(char fe) { return GetScalarSize(static_cast<FormatEnum>(fe)); }

			static bool IsValidFormatCode(char);
	};

}

#endif
