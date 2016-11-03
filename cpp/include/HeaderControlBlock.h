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
	
	// FIXED HCB
	//const int BLUE_OFFSET            =   0; //   0 (char4)   Header version
	//const int HEADER_ENDIANCE_OFFSET =   4; //   4 (char4)   Header representation
	//const int DATA_ENDIANCE_OFFSET   =   8; //   8 (char4)   Data representations
	//const int DETACHED_OFFSET        =  12; //  12 (int4)    Detached header
	//const int PROTECTED_OFFSET       =  16; //  16 (int4)    Protected from overwrite
	//const int PIPE_OFFSET            =  20; //  20 (int4)    Pipe mode (N/A)
	//const int EXTSTART_OFFSET        =  24; //  24 (int4)    Extended header start, in 512-byte blocks
	//const int EXTSIZE_OFFSET         =  28; //  28 (int4)    Extended header size in bytes
	//const int DATASTART_OFFSET       =  32; //  32 (real8)    Data start in bytes
	//const int DATASIZE_OFFSET        =  40; //  40 (real8)    Data size in bytes
	//const int TYPECODE_OFFSET        =  48; //  48 (int4)    File type code
	//const int FORMAT_OFFSET          =  52; //  52 (char2)   Data format code
	//const int FLAGMASK_OFFSET        =  54; //  54 (int2)     16-bit flagmask (1=flagbit)
	//const int TIMECODE_OFFSET        =  56; //  56 (real8)    Time code field
	//const int INLET_OFFSET           =  64; //  64 (int2)     Inlet owner
	//const int OUTLEST_OFFSET         =  66; //  66 (int2)     Number of outlets
	//const int OUTMASK_OFFSET         =  68; //  68 (int4)     Outlet async mask
	//const int PIPELOC_OFFSET         =  72; //  72 (int4)     Pipe location
	//const int PIPESIZE_OFFSET        =  76; //  76 (int4)    Pipe size in bytes
	//const int INBYTE_OFFSET          =  80; //  80 (real8)    Next input byte
	//const int OUTBYTE_OFFSET         =  88; //  88 (real8)    Next out byte (cumulative)
	//const int OUTBYTES_OFFSET        =  96; //  96 (real8[8]) Next out byte (each outlet)
	//const int KEYLEN_OFFSET          = 160; // 160 (int4)    Length of keyword string
	//const int KEYWORD_OFFSET         = 164; // 164 (char92)  User defined keyword string
	//const int ADJUNCT_OFFSET         = 256; // 256 (char256) Type-specific adjunct union (see below)

	// TYPE 1000 and TYPE 2000 ADJUNCT HCB
	//const int XSTART_OFFSET  = ADJUNCT_OFFSET +  0; // 256 (real8)   TYPE 1000: Abscissa value for first sample
	//                                                //               TYPE 2000: Frame (row) starting value
	//const int XDELTA_OFFSET  = ADJUNCT_OFFSET +  8; // 264 (real8)   TYPE 1000: Abscissa interval between samples
	//                                                //               TYPE 2000: Increment between samples in frame
	//const int XUNIT_OFFSET   = ADJUNCT_OFFSET + 16; // 272 (int4)    TYPE 1000: Units for abscissa values
	//                                                //               TYPE 2000: Frame (row) units

	// ADDITIONAL TYPE 2000 ADJUNCT HCB
	//const int SUBSIZE_OFFSET = ADJUNCT_OFFSET + 20; // 276 (int4)    Number of data points per frame (row)
	//const int YSTART_OFFSET  = ADJUNCT_OFFSET + 24; // 280 (real8)   Abscissa (column) start
	//const int YDELTA_OFFSET  = ADJUNCT_OFFSET + 32; // 288 (real8)   Increment between frames
	//const int YUNIT_OFFSET   = ADJUNCT_OFFSET + 40; // 296 (int4)    Abscissa (column) unit code
	// NOTE: MIDAS docs say yunit offset is 36 instead of 40, which must be a typo
	//       because ydelta could only be 4 bytes in that case.

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
		double rowStart;      // xStart
		double rowDelta;      // xDelta
		uint32_t rowUnits;    // xUnits
		uint32_t columnRecs;  // subsize
		double columnStart;   // yStart
		double columnDelta;   // yDelta
		uint32_t columnUnits; // yUnits
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
		uint32_t   pipeSize;
		union
		{
			double   inBytes;
			int64_t  inBytes_I;
		};
		union
		{
			double   outByte;
			int64_t  outByte_I;
		};
		union
		{
			double   outBytes[8];
			int64_t  outBytes_I[8];
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
			//bool write_crc_; // TODO - this is never used, missing feature?
  
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

			double getColStart() const  {return data_.adjunct_2000.columnStart;} // ystart
			double getColDelta() const  {return data_.adjunct_2000.columnDelta;} // ydelta
			int    getColUnits() const  {return data_.adjunct_2000.columnUnits;} // yunits
			int    getColRecs()  const  {return data_.adjunct_2000.columnRecs; } // subsize

			std::string getHdrVersion() const;

			void Byteswap();

			bool isHeaderEndianceReversed() const; 

			int validate(bool incomplete) const;
			
		private:
			int ParseKeywords_();
	};

}

#endif

