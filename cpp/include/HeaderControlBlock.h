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
#ifndef HEADER_CONTROL_BLOCK__
#define HEADER_CONTROL_BLOCK__

#include "Format.h"

#include <map>
#include <vector>
#include <string>
#include <cstring>

namespace blue
{
	class Checksum;
	const int BLUE_OFFSET=0;
	const int DATA_ENDIANCE_OFFSET=8;
	const int HEADER_ENDIANCE_OFFSET=4;
	const int PIPE_OFFSET=20;
	const int EXTSTART_OFFSET=24;
	const int EXTSIZE_OFFSET =28;
	const int FORMAT_OFFSET=52;
	const int TYPECODE_OFFSET=48;
	const int CRCSIZE_OFFSET=76;
	const int KEYLEN_OFFSET=160;
	const int KEYWORD_OFFSET=164;
	
	const int XDELTA_OFFSET=264;
	const int XUNIT_OFFSET=272;
	const int YUNIT_OFFSET=296;
	
	const int XSTART_OFFSET=256+0;
	const int YSTART_OFFSET=256+24;

	const uint32_t IEEE = 0x49454545; // Represents local endiance as written
	const uint32_t EEEI = 0x45454549; // Oposite of local endiance.

	class FileFormatBase;

	struct hcb_subrecord_t
	{

		char name[4];

		union
		{
			char format[2];
			uint16_t iformat;
		};

		uint16_t offset;
	};

	struct ADJUNCT_1000
	{
		double xStart;
		double xDelta;
		uint32_t xUnits;
	};

	struct ADJUNCT_2000
	{
		double rowStart;
		double rowDelta;
		uint32_t rowUnits;
		uint32_t columnRecs;
		double columnStart;
		double columnDelta;
		uint32_t columnUnits;
	};

	struct ADJUNCT_3000
	{
		double tagStart;
		double tagDelta;
		uint32_t tagUnits;
		uint32_t numberSubrec;
		double r2Start;
		double r2Delta;
		uint32_t r2Units;
		uint32_t recordLength;
		hcb_subrecord_t subr[26];
	};

	struct ADJUNCT_4000
	{
		double vrstart;         
		double vrdelta;          
		int32_t vrunits;       
		int32_t nrecords;      
		double vr2start;        
		double vr2delta;         
		int32_t vr2units; 
		int32_t vrecord_length;
	};

	struct ADJUNCT_SWAP
	{
		int64_t x1;   // 256
		int64_t x2;   // 264
		int32_t x3;   // 272
		int32_t x4;   // 276
		int64_t x5;   // 280
		int64_t x6;   // 288
		int32_t x7;   // 296
		int32_t x8;   // 300
	};

	struct hcb_s
	{
		char       version[4];

		union
		{
			char     headerRep[4];
			uint32_t headerEndiance;
		};

		union
		{
			char     dataRep[4];
			uint32_t dataEndiance;
		};
		uint32_t   detached;
		uint32_t   Protected;
		uint32_t   pipe;
		uint32_t   extStart;
		uint32_t   extSize;
		union
		{
			double   dataStart;
			int64_t  dataStart_I;
		};
		union
		{
			double   dataSize;
			int64_t  dataSize_I;
		};
  
		uint32_t   typeCode; 
		union
		{
			char     formatCode[2];
			uint16_t format_i16;
		};
		int16_t    flagMask;
		union
		{
			double   timeCode;
			int64_t  timeCode_I;
		};
  
		uint16_t   inLets;
		uint16_t   outLets;
		uint32_t   outMask;
		uint32_t   pipeLoc;
		uint32_t   extCRCsize;
		union
		{
			double   inBytes;
			int64_t  inBytes_I;
		};
		union
		{
			double   outBytes;
			int64_t  outBytes_I;
		};
		union
		{
			double   outByte[8]; 
			int64_t  outByte_I[8];
		};
		int32_t    keywordLength; 
		char       keyWords[92]; 
		union
		{
			char adjunct[256];
			struct ADJUNCT_1000 adjunct_1000;
			struct ADJUNCT_2000 adjunct_2000;
			struct ADJUNCT_3000 adjunct_3000;
			struct ADJUNCT_4000 adjunct_4000;
			struct ADJUNCT_SWAP adjunct_swap;
		};
	};

	std::map<std::string, std::string> ParseKeywords(const hcb_s &);

	void byteswap(hcb_s *);

	class HeaderControlBlock
	{
		private:
			hcb_s data_;
			std::map<std::string, std::string> keywords_;
			bool write_crc_;
  
		public:
			HeaderControlBlock();
			HeaderControlBlock(const hcb_s *hcb);

			~HeaderControlBlock()  { }
			
			hcb_s getHCB() const   {return data_;}

			bool setHeaderRep(uint32_t);
			bool setDataRep(uint32_t);

			uint32_t getDataEndiance() const  {return data_.dataEndiance;}

			void setTimeCode(double code);
			double getTimeCode() const   {return data_.timeCode;}

			bool setTypeCode(int typeCode);
			int getTypeCode() const  {return data_.typeCode;}

			bool setExtStart(int start);
			bool setExtSize(int size = 0);
			int getExtStart() const {return data_.extStart;}
			int getExtSize()  const {return data_.extSize;}

			bool setDataSize(int64_t size);
			int64_t getDataSize() const {return static_cast<int64_t> (data_.dataSize);}
			int64_t getDataStart() const {return static_cast<int64_t> (data_.dataStart);}
			
			const char *getFormatCode() const;
			bool setFormatCode(Format formatCode);

			std::vector<std::string> getKeywordNames() const;
			std::string getKeywordValue(const std::string &name) const;

			bool setXstart(double start);
			bool setXdelta(double delta);
			bool setXunits(int units);

			double getXstart() const {return data_.adjunct_1000.xStart; }
			double getXdelta() const {return data_.adjunct_1000.xDelta; }
			int    getXunits() const {return data_.adjunct_1000.xUnits; }

			bool setColRecs(int recs);
			bool setColStart(double start);
			bool setColDelta(double delta);
			bool setColUnits(int units);

			double getColStart() const  {return data_.adjunct_2000.columnStart;}
			double getColDelta() const  {return data_.adjunct_2000.columnDelta;}
			int    getColUnits() const  {return data_.adjunct_2000.columnUnits;}
			int    getColRecs()  const  {return data_.adjunct_2000.columnRecs; }

			std::string getHdrVersion() const;

			void Byteswap();

			bool isHeaderEndianceReversed() const; 

			int validate(bool incomplete) const;
			
		private:
			int ParseKeywords_();
	};

}

#endif

