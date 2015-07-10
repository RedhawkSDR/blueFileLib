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
#include "Format.h"

namespace
{

	// Note sizeof returns 64 bits if compiled with 64 bit
	const int memSizeofM2k[]=
	{
		/*A*/ (int) (sizeof(char)),    /*B*/ (int) sizeof(int8_t),
		/*C*/ (int) -1,                /*D*/ (int) sizeof(double),
		/*E*/ (int) -1,                /*F*/ (int) sizeof(float),
		/*G*/ (int) -1,                /*H*/ (int) 0,
		/*I*/ (int) sizeof(int16_t),   /*J*/ (int) -1,
		/*K*/ (int) -1,                /*L*/ (int) sizeof(int32_t),
		/*M*/ (int) -1,                /*N*/ (int) -1,
		/*O*/ (int) sizeof(uint8_t),   /*P*/ (int) sizeof(int8_t),
		/*Q*/ (int) -1,                /*R*/ (int) -1,
		/*S*/ (int) -1,                /*T*/ (int) -1,
		/*U*/ (int) sizeof(uint16_t),  /*V*/ (int) sizeof(uint32_t),
		/*W*/ (int) -1,                /*X*/ (int) sizeof(int64_t),
		/*Y*/ (int) -1,                /*Z*/ (int) -1
	};

	const int COUNT_OF_M2K [] =
	{
		/*A*/ 10,                /*B*/ 0,
		/*C*/ 2,                 /*D*/ 0,
		/*E*/ 0,                 /*F*/ 0,
		/*G*/ 0,                 /*H*/ 1,
		/*I*/ 0,                 /*J*/ 0,
		/*K*/ 0,                 /*L*/ 0,
		/*M*/ 9,                 /*N*/ 0,
		/*O*/ 0,                 /*P*/ 0,
		/*Q*/ 4,                 /*R*/ 0,
		/*S*/ 1,                 /*T*/ 16,
		/*U*/ 0,                 /*V*/ 3,
		/*W*/ 0,                 /*X*/ 0,
		/*Y*/ 0,                 /*Z*/ 0
	};

}

namespace blue
{
	
	Format::Format(const char *format)
	{
		codes_[0] = format[0];
		codes_[1] = format[1];
	}

	Format::Format(const std::string &format)
	{
		codes_[0] = format[0];
		codes_[1] = format[1];
	}

	Format::Format(FormatEnum format)
	{
		codes_[0] = 'S';
		codes_[1] = format;
	}

	Format &Format::SecondChar(char sc)
	{
		codes_[1] = sc;
		return *this;
	}

	int Format::GetScalarSize(FormatEnum fe)
	{
		char sc = static_cast<char>(fe);

		if (sc < 'A' || 'Z' < sc) 
		{
			return 0;
		}

		return memSizeofM2k[sc-'A'];
	}

	int Format::getNumScalars() const
	{
		char fc = rankCode();

		if ('0' <= fc && fc <= '9')
		{
			return fc-'0';
		}
	
		if ('A' <= fc && fc <= 'Z')
		{
			return COUNT_OF_M2K[fc-'A'];
		}

		return 0;
	}

	int Format::getElementSize() const
	{
		return getNumScalars()*getScalarSize();
	}

	bool Format::isValid() const
	{
		return getElementSize()>0 ||                                 // Actual data
		(codes_[0]=='N' && codes_[1]=='H') ||                        // NH
		(codes_[0]=='P' && (codes_[1]=='B' || codes_[1]=='E')) ||    // PB PE
		(codes_[0]=='R' && (codes_[1]=='B' || codes_[1]=='E')) ||    // RB RE
		(codes_[0]=='B' && (codes_[1]=='B' || codes_[1]=='E'));      // BB BE
	}

	bool Format::IsValidFormatCode(char fc)
	{
		return (fc == 'B' || fc == 'O' || fc == 'I' || fc == 'L' ||
			fc == 'X' || fc == 'F' || fc == 'D' || fc == 'A');
	}

}
