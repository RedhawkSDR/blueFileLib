#ifndef BYTE_SWAP_H
#define BYTE_SWAP_H

#include "Format.h"

namespace blue
{

	void Byteswap(void *buffer, int count, char formatcode);

	inline void Byteswap(void *buffer, int count, Format fmt) { Byteswap(buffer, count * fmt.getNumScalars(), fmt.formatCode()); }

}

#endif
