#ifndef INTERNAL_KEYWORD_H
#define INTERNAL_KEYWORD_H

#include "Format.h"
#include "InternalKeywordBase.h"

#include <iomanip>
#include <sstream>
#include <vector>

namespace blue
{

	template <class T>
	class InternalKeyword : public InternalKeywordBase
	{
		public:
			InternalKeyword(FormatEnum format, const char *name)
				: InternalKeywordBase(format, name) {}

			int setValue(char value, int index);
                        int setValue(unsigned char value, int index);
                        int setValue(signed char value, int index);
                        int setValue(short value, int index);
                        int setValue(int value, int index);
                        int setValue(long value, int index);
                        int setValue(long long value, int index);
                        int setValue(float value, int index);
                        int setValue(double value, int index);
                        int setValue(const std::string value, int index) { return setString(value, index); }
                        int setValue(const char *value, int index) { return setString(value, index); }

			void getValue(bool  *value, int index) const { *value = static_cast<bool>(getValue_(index)); }
			void getValue(char  *value, int index) const { *value = static_cast<char>(getValue_(index)); }
			void getValue(signed char *value, int index) const { *value = static_cast<signed char>(getValue_(index)); }
			void getValue(unsigned char *value, int index) const { *value=static_cast<unsigned char>(getValue_(index)); }
			void getValue(short *value, int index) const { *value = static_cast<short>(getValue_(index)); }
			void getValue(int   *value, int index) const { *value = static_cast<int>(getValue_(index)); }
			void getValue(long  *value, int index) const { *value = static_cast<long>(getValue_(index)); }
			void getValue(long long *value, int index) const { *value = static_cast<long long>(getValue_(index)); }
			void getValue(float   *value, int index) const { *value = static_cast<float>(getValue_(index)); }
			void getValue(double  *value, int index) const { *value = static_cast<double>(getValue_(index)); }
			void getValue(std::string *value, int index) const { *value = getString(index); }

			std::string getString(int index) const;
			std::string getString() const;

			void setRawData(const void *data, int count);

			const T *getRawDataT() const;
			const void *getRawData() const;

			int setString(const std::string &data);
			int setString(const std::string &data, int index);
			int setString(const char *data, int index) { return setString(std::string(data), index); }

			virtual InternalKeyword<T> *copy() const { return new InternalKeyword<T>(*this); }

			int size() { return static_cast<int>(data_.size()); }
			void push() { data_.push_back(T()); }

		private:
			int setValue_(int index, const T &value);
			T getValue_(int index) const;

		private:
			std::vector<T> data_;
	};

	template <class T>
	T InternalKeyword<T>::getValue_(int index) const
	{
		return data_[index];
	}

	template <>
	inline uint8_t InternalKeyword<uint8_t>::getValue_(int) const
	{
		throw 1;
	}

	template <>
	inline void InternalKeyword<std::string>::getValue(bool *value, int ii) const
	{
		*value = (	data_[ii] == "YES"	|| data_[ii] == "yes"	|| data_[ii] == "Yes" 	||
				data_[ii] == "TRUE"	|| data_[ii] == "true"	|| data_[ii] == "True"	||
				data_[ii] == "ON"	|| data_[ii] == "on"	|| data_[ii] == "On"	||
				data_[ii] == "1");
	}

	template <>
	inline void InternalKeyword<std::string>::getValue(char *value, int ii) const
	{
		std::istringstream stream(data_[ii]);
		int temp;
		stream >> temp;
		*value = static_cast<int8_t>(temp);
	}

	template <>
	inline void InternalKeyword<std::string>::getValue(signed char *value, int ii) const
	{
		std::istringstream stream(data_[ii]);
		int temp;
		stream >> temp;
		*value = static_cast<int8_t>(temp);
	}

	template <>
	inline void InternalKeyword<std::string>::getValue(unsigned char *value, int ii) const
	{
		std::istringstream stream(data_[ii]);
		int temp;
		stream >> temp;
		*value = static_cast<int8_t>(temp);
	}

	template <>
	inline void InternalKeyword<std::string>::getValue(short *value, int ii) const
	{
		std::istringstream stream(data_[ii]);
		stream >> *value;
        }

	template <>
	inline void InternalKeyword<std::string>::getValue(int *value, int ii) const
	{
		std::istringstream stream(data_[ii]);
		stream >> *value;
	}

	template <>
	inline void InternalKeyword<std::string>::getValue(long *value, int ii) const
	{
		std::istringstream stream(data_[ii]);
		stream >> *value;
	}

	template <>
	inline void InternalKeyword<std::string>::getValue(long long *value, int ii) const
	{
		std::istringstream stream(data_[ii]);
		stream >> *value;
	}

	template <>
	inline void InternalKeyword<std::string>::getValue(float *value, int ii) const
	{
		std::istringstream stream(data_[ii]);
		stream >> *value;
	}

	template <>
	inline void InternalKeyword<std::string>::getValue(double *value, int ii) const
	{
		std::istringstream stream(data_[ii]);
		stream >> *value;
	}

	template <class T>
	std::string InternalKeyword<T>::getString(int index) const
	{
		if (index >= static_cast<int>(data_.size()))
		{
			return "";
		}

		std::ostringstream stream;
		stream << data_[index];

		return stream.str();
	}

	template <>
	inline std::string InternalKeyword<int8_t>::getString(int index) const
	{
		std::ostringstream stream;
		stream << static_cast<int>(data_[index]);

		return stream.str();
	}

	template <>
	inline std::string InternalKeyword<float>::getString(int index) const
	{
		std::ostringstream stream;
		stream << std::setprecision(doubleprecision) << data_[index];

		return stream.str();
	}

	template <>
	inline std::string InternalKeyword<double>::getString(int index) const
	{
		std::ostringstream stream;
		stream << std::setprecision(doubleprecision) << data_[index];

		return stream.str();
	}

	template <>
	inline std::string InternalKeyword<std::string>::getString(int index) const
	{
		return data_[index];
	}

	template <class T>
	inline std::string InternalKeyword<T>::getString() const
	{
		std::string rr;
		const int NN = static_cast<int>(data_.size());

		for (int ii = 0; ii < NN; ++ii)
		{
			rr += getString(ii);
			if (ii+1 < NN)
			{
				rr += ASCII_UNIT_SEPARATOR;
			}
		}

		return rr;
	}

}

#endif
