#include "ByteSwap.h"

#include "utils/utilsByteSwap.h"

namespace blue
{

	void Byteswap(void *buffer, int count, char formatcode)
	{
		switch (formatcode)
		{
			case 'I':
			case 'U':
				utils::byteswap(static_cast<int16_t *>(buffer), count);
				break;
	
			case 'L':
			case 'V':
			case 'F':
				utils::byteswap(static_cast<int32_t *>(buffer), count);
				break;
	
			case 'X':
			case 'D':
				utils::byteswap(static_cast<int64_t *>(buffer), count);
				break;
		}
	}

}
