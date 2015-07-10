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
#ifndef KEYWORD_H
#define KEYWORD_H

#include "Format.h"
#include "InternalKeywordBase.h"
#include "MartesKey.h"
#include "MidasKey.h"
#include "UnitCode.h"

#include <string>
#include <vector>

namespace blue
{

	class Keyword {
		public:
			const static int MAX_KEYWORD_NAME_LENGTH = 128;

			Keyword()
			: internals_(0), count_(0) { }

			Keyword(FormatEnum format, const char *name);
			Keyword(const MartesKey &mk);
			Keyword(const MidasKey &mk);
			Keyword(const Keyword &kw);

			bool operator<(const Keyword &rhs) const;

			FormatEnum getFormat() const;
			std::string getName() const;

			UnitCodeEnum getUnits() const;

			int size() const;
			void push();

			Keyword duplicate() const;

			std::string getString() const;
			
			std::string getString(int index) const { std::string ss; getValue(&ss, index); return ss; }

			template <typename U>
			void getValue(U* value, int offset=0) const
			{
				if (internals_)
				{
					internals_->getValue(value, offset);
				}
				else
				{
					*value = U();
				}
			}

			template <typename U>
			void getValue(int offset=0) const
			{
				U uu;

				getValue(&uu, offset);
				
				return uu;
			}

			int setValue(char value, int);
			int setValue(signed char value, int);
			int setValue(unsigned char value, int);
			int setValue(short value, int);
			int setValue(int value, int);
			int setValue(long value, int);
			int setValue(long long value, int);
			int setValue(float value, int);
			int setValue(double value, int);
			int setValue(const std::string &value, int);
			int setValue(const std::string *value, int idx) { return setValue(*value, idx); }
			int setValue(const char *value, int);

			void setUnits(UnitCodeEnum units) { internals_->setUnits(units); }

			const void *getRawData() const;

			FormatEnum getIndexFormat() const;
			UnitCodeEnum getIndexUnits() const;

			std::string getIndexString(int offset) const;
			std::string getIndexString() const;

			bool isIndexKeyword() const;

			void getRawIndexData(std::vector<char> *data) const;

			static bool IsValidName(const char *name);

		private:
			InternalKeywordBase *internals_;
			mutable int *count_;

		private:
			void initInternals_(const char *name, FormatEnum format);
	};

}

#endif
