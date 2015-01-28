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
#ifndef INTERNAL_KEYWORD_BASE_H
#define INTERNAL_KEYWORD_BASE_H

#include "Format.h"
#include "UnitCode.h"

#include <string>

namespace blue
{

	class InternalKeywordBase
	{
		public:
			InternalKeywordBase(FormatEnum format, const char *name)
			: format_(format), name_(name) {}

			std::string getName() const { return name_; }
			UnitCodeEnum getUnits() const { return units_; }
			FormatEnum getFormat() const { return format_; }

			virtual InternalKeywordBase *copy() const = 0;

			virtual int setValue(char value, int index) = 0;
			virtual int setValue(unsigned char value, int index) = 0;
			virtual int setValue(signed char value, int index) = 0;
			virtual int setValue(short value, int index) = 0;
			virtual int setValue(int value, int index) = 0;
			virtual int setValue(long value, int index) = 0;
			virtual int setValue(long long value, int index) = 0;
			virtual int setValue(float value, int index) = 0;
			virtual int setValue(double value, int index) = 0;
			virtual int setValue(const std::string value, int index) = 0;
			virtual int setValue(const char *value, int index) = 0;

			virtual void getValue(bool *value, int index) const = 0;
			virtual void getValue(char *value, int index) const = 0;
                        virtual void getValue(unsigned char *value, int index) const = 0;
                        virtual void getValue(signed char *value, int index) const = 0;
                        virtual void getValue(short *value, int index) const = 0;
                        virtual void getValue(int *value, int index) const = 0;
                        virtual void getValue(long *value, int index) const = 0;
                        virtual void getValue(long long *value, int index) const = 0;
                        virtual void getValue(float *value, int index) const = 0;
                        virtual void getValue(double *value, int index) const = 0;
                        virtual void getValue(std::string *value, int index) const = 0;

			virtual const void *getRawData() const = 0;
			virtual void setRawData(const void *, int num_elements) = 0;

			virtual void setUnits(UnitCodeEnum units) { units_ = units; }

			virtual int setString(const std::string &, int index) = 0;
			virtual int setString(const char *data, int index) { return setString(std::string(data), index); }

			virtual int size() = 0;
			virtual void push() = 0;

		private:
			FormatEnum format_;
			std::string name_;
			UnitCodeEnum units_;
	};

}

#endif
