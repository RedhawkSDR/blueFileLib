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
