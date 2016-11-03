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
#include "HeaderControlBlock.h"

#include "utils/utilsByteSwap.h"
#include "utils/utilsError.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sys/types.h>

namespace
{

  const int KEYWORD_SIZE = 92;
  const int HCB_SIZE=512;

}

namespace blue
{

	using std::cout;
	using std::endl;
	using std::setw;
	using utils::ESUCCESS;
	using utils::EBADHEADER;
	using utils::EINVALID_FORMAT;
	using utils::ENOTPLATINUM;
	using utils::ENOTCLOSED;

	void byteswap(hcb_s *hcb)
	{
		utils::byteswap(&hcb->detached,  5);
		utils::byteswap(&hcb->dataStart_I, 2);
		utils::byteswap(&hcb->typeCode);
		utils::byteswap(&hcb->flagMask);
		utils::byteswap(&hcb->timeCode_I);
		utils::byteswap(&hcb->inLets,  2);
		utils::byteswap(&hcb->outMask, 3);
		utils::byteswap(&hcb->inBytes, 10);
		utils::byteswap(&hcb->keywordLength); 

		utils::byteswap(&hcb->adjunct_swap.x1);
		utils::byteswap(&hcb->adjunct_swap.x2);
		utils::byteswap(&hcb->adjunct_swap.x3); 
		utils::byteswap(&hcb->adjunct_swap.x4);
		utils::byteswap(&hcb->adjunct_swap.x5);
		utils::byteswap(&hcb->adjunct_swap.x6);
		utils::byteswap(&hcb->adjunct_swap.x7);
		utils::byteswap(&hcb->adjunct_swap.x8);

		if ((hcb->typeCode/1000) == 6 || (hcb->typeCode/1000) == 3)
		{
			for (unsigned ii=0 ; ii<26; ii++)
				utils::byteswap(&hcb->adjunct_3000.subr[ii].offset); //uint16_t
		}
	}


	HeaderControlBlock::HeaderControlBlock()
	{
		memset(&data_, 0, HCB_SIZE);
		memcpy(data_.version, "BLUE", 4);
		memset(&data_.keyWords[1], 0x20, KEYWORD_SIZE-1); // Leave first byte as NULL (0), but pad rest of keywords with spaces (0x20)
		data_.extSize   = 0xFFFFFFFF;
		data_.extStart  = 0xFFFFFFFF;
		data_.dataStart = 512.0;
		data_.dataSize  = 0.0;
		data_.Protected = 0;
	}

	HeaderControlBlock::HeaderControlBlock(const hcb_s *hcb)
	{
		data_ = *hcb;
		Byteswap();
		ParseKeywords_();
	}

	bool HeaderControlBlock::setHeaderRep(uint32_t hr)
	{
		if (hr==IEEE || hr==EEEI)
		{
			data_.headerEndiance = hr;
			return true;
		}
		return false;
	}

	bool HeaderControlBlock::setDataRep(uint32_t hr)
	{
		if (hr==IEEE || hr==EEEI)
		{
			data_.dataEndiance = hr;
			return true;
		}
		return false;
	}

	void HeaderControlBlock::setTimeCode(double t)
	{
		data_.timeCode = t;
	}

	bool HeaderControlBlock::setExtStart(int start)
	{
		data_.extStart = static_cast<uint32_t>(start);
		return true;
	}

	bool HeaderControlBlock::setExtSize(int size)
	{
		data_.extSize = static_cast<uint32_t>(size);
		return true;
	}

	bool HeaderControlBlock::setDataSize(int64_t size)
	{
		data_.dataSize = static_cast<double>(size);
		return true;
	}

	bool HeaderControlBlock::setTypeCode(int typeCode)
	{
		switch(typeCode)
		{
			case 1000:
			case 1001:
			case 1002:
			case 1003:
			case 1004:
			case 1005:
			case 2000:
			case 2001:
			case 2004:
			case 3000:
			case 3001:
			case 3002:
			case 3003:
			case 3004:
			case 3005:
			case 6000:
			case 6001:
			case 6002:
			case 6003:
			case 6004:
			case 6005:
				data_.typeCode = typeCode;
				 return true;

			default:
				return false;
		}
	}

	bool HeaderControlBlock::setFormatCode(Format formatCode)
	{
		if (formatCode.isValid())
		{
			data_.formatCode[0] = formatCode.rankCode();
			data_.formatCode[1] = formatCode.formatCode();
			return true;
		}
		else
		{
			return false;
		}
	}

	bool HeaderControlBlock::setXstart(double start)
	{
		data_.adjunct_1000.xStart = start;
		return true;
	}

	bool HeaderControlBlock::setXdelta(double delta)
	{
		if (delta <= 0.0 || delta <= 1.0e-15 || delta > 1.0e+15)
		{
			return false;
		} else {
			data_.adjunct_1000.xDelta = delta;
			return true;
		}
	}

	bool HeaderControlBlock::setXunits(int units)
	{
		if (units < 58)
		{
			if (units < 20 || units >= 30)
			{
				data_.adjunct_1000.xUnits = units;
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}

	const char* HeaderControlBlock::getFormatCode() const
	{
		return data_.formatCode;
	}

	bool HeaderControlBlock::isHeaderEndianceReversed() const
	{
		return data_.headerEndiance == EEEI;
	}

	bool HeaderControlBlock::setColStart(double start)
	{
		data_.adjunct_2000.columnStart = start;
		return true;
	}

	bool HeaderControlBlock::setColDelta(double delta)
	{
		if (delta <= 0.0 || delta <= 1.0e-15 || delta > 1.0e+15)
		{
			return false;
		}
		data_.adjunct_2000.columnDelta = delta;
		return true;
	}

	bool HeaderControlBlock::setColUnits(int units)
	{
		if (units < 58)
		{
			if (units < 20 || units >= 30)
			{
				data_.adjunct_2000.columnUnits = static_cast<uint32_t>(units);
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}

	void HeaderControlBlock::Byteswap()
	{
		if (isHeaderEndianceReversed())
		{
			byteswap(&data_);
		}
	}

	int HeaderControlBlock::validate(bool incomplete) const
	{
		bool valid;

		if (!strncmp("OPEN", data_.dataRep, 4) || !strncmp("OPEN", data_.headerRep, 4))
		{
			return ENOTCLOSED;
		}

		if (strncmp("BLUE", data_.version, 4) != 0)
		{
			return ENOTPLATINUM;
		}

		if ((strncmp((char *) "IEEE", data_.headerRep, 4) != 0) && (strncmp((char *) "EEEI", data_.headerRep, 4) != 0))
		{
			return ENOTPLATINUM;
		}

		if ((strncmp((char *) "IEEE", data_.dataRep, 4) != 0) && (strncmp((char *) "EEEI", data_.dataRep, 4) != 0))
		{
			return ENOTPLATINUM;
		}

		if (!incomplete)
		{
			if (0xFFFFFFFF == data_.extStart)
			{
				return EBADHEADER;
			}

			if (0xFFFFFFFF == data_.extSize)
			{
				return EBADHEADER;
			}

			if (data_.dataStart <= 0 || data_.dataSize<0)
			{
				return EBADHEADER;
			}
		}

		if (data_.typeCode != 1000 && data_.typeCode != 1001 &&
			data_.typeCode != 1002 && data_.typeCode != 1003 &&
			data_.typeCode != 1004 && data_.typeCode != 1005 &&
			data_.typeCode != 1011 && data_.typeCode != 2000 &&
			data_.typeCode != 2001 && data_.typeCode != 2004 &&
			data_.typeCode != 3000 && data_.typeCode != 3001 &&
			data_.typeCode != 3002 && data_.typeCode != 3003 &&
			data_.typeCode != 3004 && data_.typeCode != 3005 &&
			data_.typeCode != 6000 && data_.typeCode != 6001 &&
			data_.typeCode != 6002 && data_.typeCode != 6003 &&
			data_.typeCode != 6004 && data_.typeCode != 6005)
		{
			return EINVALID_FORMAT;
		}

		valid = Format(data_.formatCode).isValid();
		
		if (false == valid)
		{
			return EINVALID_FORMAT;
		}
		
		std::string library;

		switch (data_.typeCode/1000)
		{
			case 1:
				break;

			case 2:
				if (data_.adjunct_2000.rowDelta <= 0.0 || data_.adjunct_2000.columnRecs <= 0       ||
					data_.adjunct_2000.columnDelta <= 0.0)
				{
					return EBADHEADER;
				}
				break;

			case 3:
			case 6:
				if (data_.adjunct_3000.numberSubrec <= 0   || data_.adjunct_3000.recordLength <= 0)
				{
					return EBADHEADER;
				}
				break;
		
			default:
				return EINVALID_FORMAT;
		}

		return ESUCCESS;
	}

	std::vector<std::string> HeaderControlBlock::getKeywordNames() const
	{
		std::vector<std::string> names;
		std::map<std::string, std::string>::const_iterator ii = keywords_.begin();

		while (ii!=keywords_.end())
		{
			names.push_back(ii->first);
			++ii;
		}

		return names;
	}

	std::map<std::string, std::string> ParseKeywords(const hcb_s &hcb, int keylen)
	{
		std::map<std::string, std::string> keys;

		if (keylen)
			keylen=KEYWORD_SIZE;

		if (keylen<1)
			return keys;
  
		const size_t kwLength = KEYWORD_SIZE + 2;
		char *kw = new char[kwLength];
		
		memcpy( kw, hcb.keyWords, KEYWORD_SIZE );
		kw[kwLength-2] = 0;
		kw[kwLength-1] = 0;

		int index = 0;
		while(index<hcb.keywordLength)
		{
			if (!kw[index])
			{	
				break;
			}

			std::string key( kw+index );
			std::string::size_type eq = key.find('=');

			if (eq==std::string::npos || eq==0)
			{
				index += key.size()+1;
				continue;
			}
	
			std::string name(key, 0, eq);
			std::string value(key, eq+1);
	
			if (name.size() && value.size())
			{
				keys[name] = value;
			}

			index += key.size()+1;
		}

		delete[] kw;
		kw = NULL;

		return keys;
	}

	int HeaderControlBlock::ParseKeywords_()
	{
		keywords_ = ParseKeywords(data_, data_.keywordLength);
		return keywords_.size();
	}

	std::string HeaderControlBlock::getKeywordValue(const std::string &name) const
	{
		std::map<std::string, std::string>::const_iterator ii=keywords_.find(name);
		if (ii == keywords_.end())
		{
			return "";
		}

		return ii->second;
	}

	std::string HeaderControlBlock::getHdrVersion() const
	{
		std::string value = getKeywordValue("VER");
		return value.size() ? value : std::string("1.0");
	}

	bool HeaderControlBlock::setColRecs(int recs)
	{
		if (recs > 0)
		{
			data_.adjunct_2000.columnRecs = recs;
			return true;
		} else {
			return false;
		}
	}

}
