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
#include "Keyword.h"

#include "InternalKeyword.h"
#include "utils/utilsError.h"

#include <string>

namespace blue
{

	void Keyword::initInternals_(const char *name, FormatEnum format)
	{
		switch (format)
		{
			case BYTE:
				internals_ = new InternalKeyword<int8_t>(format, name);
				break;

			case OFFSET:
			case INTEGER:
				internals_ = new InternalKeyword<int16_t>(format, name);
				break;

			case LONG:
				internals_ = new InternalKeyword<int32_t>(format, name);
				break;

			case XTENDED:
				internals_ = new InternalKeyword<int64_t>(format, name);
				break;

			case FLOAT:
				internals_ = new InternalKeyword<float>(format, name);
				break;

			case DOUBLE:
				internals_ = new InternalKeyword<double>(format, name);
				break;

			case ASCII:
				internals_ = new InternalKeyword<std::string>(format, name);
				break;

			case FORMAT_ENUM_NOT_SET:
				internals_ = new InternalKeyword<std::string>(format, name);
				break;
			
			default:
				return;
		}
	}

	Keyword::Keyword(FormatEnum format, const char *name)
	: internals_(0), count_(0)
	{
		if (!IsValidName(name))
		{
			return;
		}

		initInternals_(name, format);

		count_ = new int(1);
	} 

	Keyword::Keyword(const MartesKey &mk)
	{
		count_ = new int(1);
		internals_ = new InternalKeyword<std::string>(ASCII, mk.getName().c_str());
		internals_->setString(mk.getData().c_str(), 0);
	}

	Keyword::Keyword(const MidasKey &mk)
	: internals_(0), count_(0)
	{
		char format = mk.getFormat();

		switch(format)
		{
			case 'B':
				internals_ = new InternalKeyword<int8_t>(BYTE, mk.getName().c_str()/*, NOT_APPLICABLE*/);
				break;
			case 'O':
				internals_ = new InternalKeyword<uint8_t>(OFFSET, mk.getName().c_str()/*, NOT_APPLICABLE*/);
				break;
			case 'I':
				internals_ = new InternalKeyword<int16_t>(INTEGER, mk.getName().c_str()/*, NOT_APPLICABLE*/);
				break;
			case 'L':
				internals_ = new InternalKeyword<int32_t>(LONG, mk.getName().c_str()/*, NOT_APPLICABLE*/);
				break;
			case 'X':
				internals_ = new InternalKeyword<int64_t>(XTENDED, mk.getName().c_str()/*, NOT_APPLICABLE*/);
				break;
			case 'F':
				internals_ = new InternalKeyword<float>(FLOAT, mk.getName().c_str()/*, NOT_APPLICABLE*/);
				break;
			case 'D':
				internals_ = new InternalKeyword<double>(DOUBLE, mk.getName().c_str()/*, NOT_APPLICABLE*/);
				break;
			case 'A':
				internals_ = new InternalKeyword<std::string>(ASCII, mk.getName().c_str()/*, NOT_APPLICABLE*/);
				break;
			default:
				return;
		}

		internals_->setRawData(mk.getAllValues(), mk.getCount());
		count_ = new int(1);
	}

	Keyword::Keyword(const Keyword &kw)
	{
		internals_ = kw.internals_;
		count_ = kw.count_;
		if (count_)
		{
			++(*count_);
		}
	}

	bool Keyword::operator<(const Keyword &rhs) const
	{
		return getName() < rhs.getName();
	}

	FormatEnum Keyword::getFormat() const
	{
		return internals_ ? internals_->getFormat() : FORMAT_ENUM_NOT_SET;
	}

	std::string Keyword::getName() const
	{
		return internals_ ? internals_->getName() : std::string();
	}

	UnitCodeEnum Keyword::getUnits() const
	{
		return internals_ ? internals_->getUnits() : NOT_APPLICABLE;
	}

	int Keyword::size() const
	{
		return internals_ ? internals_->size() : 0;
	}

	void Keyword::push()
	{
		if (internals_)
		{
			internals_->push();
		}
	}

	Keyword Keyword::duplicate() const
	{
		Keyword kw;

		if (internals_)
		{
			kw.internals_ = internals_->copy();
			kw.count_ = new int(1);
		}

		return kw;
	}

	int Keyword::setValue(char value, int index)
	{
		if (!internals_)
		{
			return utils::EBADVALUE;
		}

		return internals_->setValue(value, index);
	}

	int Keyword::setValue(signed char value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	int Keyword::setValue(unsigned char value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	int Keyword::setValue(short value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	int Keyword::setValue(int value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	int Keyword::setValue(long value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	int Keyword::setValue(long long value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	int Keyword::setValue(float value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	int Keyword::setValue(double value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	int Keyword::setValue(const std::string &value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	int Keyword::setValue(const char *value, int index)
	{
		if (!internals_)
                {
                        return utils::EBADVALUE;
                }

                return internals_->setValue(value, index);
	}

	const void *Keyword::getRawData() const
	{
		return internals_->getRawData();
	}

	bool Keyword::IsValidName(const char *name)
	{
		if (!name || !*name)
		{
			return false;
		}

		for (int ii = 1; ii < MAX_KEYWORD_NAME_LENGTH; ++ii)
		{
			if (!name[ii])
			{
				return true;
			}

			if (name[ii] <= ' ' || name[ii] > '~')
			{
				return false;
			}
		}

		return false;
	}

	std::string Keyword::getString() const
	{
		std::string ss;
		int nn = size();
		
		for (int ii = 0; ii < nn; ++ii)
		{
			if (ii != 0)
			{
				ss += ASCII_UNIT_SEPARATOR;
			}

			ss += getString(ii);
		}

		return ss;
	}

	FormatEnum Keyword::getIndexFormat() const
	{
		return FORMAT_ENUM_NOT_SET;
	}

	UnitCodeEnum Keyword::getIndexUnits() const
	{
		return NOT_APPLICABLE;
	}
	
	std::string Keyword::getIndexString(int index) const
	{
		return std::string();
	}

	std::string Keyword::getIndexString() const
	{
		std::string ss;
		int nn = size();

		for (int ii = 0; ii < nn; ++ii)
		{
			if (ii != 0)
			{
				ss += ASCII_UNIT_SEPARATOR;
			}

			ss += getIndexString(ii);
		}

		return ss;
	}

	bool Keyword::isIndexKeyword() const
	{
		return internals_ != 0;
	}

	void Keyword::getRawIndexData(std::vector<char> *data) const
	{
	
	}

}
