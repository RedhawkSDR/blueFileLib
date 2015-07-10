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
#include "InternalKeyword.h"

#include <sstream>

namespace blue
{

	template <class T>
	int InternalKeyword<T>::setValue(char value, int index)
	{
		return setValue_(index, value);
	}

	template <>
	int InternalKeyword<std::string>::setValue(char value, int index)
	{
		std::ostringstream stream;
		stream << value;
		
		return setString(stream.str().c_str(), index);
	}

	template <class T>
	int InternalKeyword<T>::setValue(signed char value, int index)
	{
		return setValue_(index, value);
	}

	template <>
	int InternalKeyword<std::string>::setValue(signed char value, int index)
	{
		std::ostringstream stream;
		stream << value;
		
		return setString(stream.str().c_str(), index);
	}

	template <class T>
	int InternalKeyword<T>::setValue(unsigned char value, int index)
	{
		return setValue_(index, value);
	}

	template <>
	int InternalKeyword<std::string>::setValue(unsigned char value, int index)
	{
		std::ostringstream stream;
		stream << value;
		
		return setString(stream.str().c_str(), index);
	}

	template <class T>
	int InternalKeyword<T>::setValue(short value, int index)
	{
		return setValue_(index, value);
	}

	template <>
	int InternalKeyword<std::string>::setValue(short value, int index)
	{
		std::ostringstream stream;
		stream << value;
		
		return setString(stream.str().c_str(), index);
	}

	template <class T>
	int InternalKeyword<T>::setValue(int value, int index)
	{
		return setValue_(index, value);
	}

	template <>
	int InternalKeyword<std::string>::setValue(int value, int index)
	{
		std::ostringstream stream;
		stream << value;
		
		return setString(stream.str().c_str(), index);
	}

	template <class T>
	int InternalKeyword<T>::setValue(long value, int index)
	{
		return setValue_(index, value);
	}

	template <>
	int InternalKeyword<std::string>::setValue(long value, int index)
	{
		std::ostringstream stream;
		stream << value;
		
		return setString(stream.str().c_str(), index);
	}

	template <class T>
	int InternalKeyword<T>::setValue(long long value, int index)
	{
		return setValue_(index, value);
	}

	template <class T>
	int InternalKeyword<T>::setValue(float value, int index)
	{
		return setValue_(index, value);
	}

	template <>
	int InternalKeyword<std::string>::setValue(float value, int index)
	{
		std::ostringstream stream;
		stream << value;
		
		return setString(stream.str().c_str(), index);
	}

	template <class T>
	int InternalKeyword<T>::setValue(double value, int index)
	{
		return setValue_(index, value);
	}

	template <>
	int InternalKeyword<std::string>::setValue(double value, int index)
	{
		std::ostringstream stream;
		stream << value;
		
		return setString(stream.str().c_str(), index);
	}

	template <>
	int InternalKeyword<std::string>::setValue(long long value, int index)
	{
		std::ostringstream stream;
		stream << value;
		
		return setString(stream.str().c_str(), index);
	}

	template <class T>
	int InternalKeyword<T>::setValue_(int index, const T &value)
	{
		int toAdd = index - (int)data_.size() + 1;
		
		if (toAdd > 0)
		{
			data_.insert(data_.end(), toAdd, T());
		}

		data_[index] = value;

		return 0;
	}

	template <class T>
	void InternalKeyword<T>::setRawData(const void *data, int count)
	{
		const T *dd = static_cast<const T*>(data);
		data_.erase(data_.begin(), data_.end());
		data_.insert(data_.begin(), dd, dd+count);
	}

	template <>
	void InternalKeyword<std::string>::setRawData(const void *dd, int count)
	{
		setString(std::string(static_cast<const char *>(dd), count));
	}

	template <class T>
	int InternalKeyword<T>::setString(const std::string &ss)
	{
		int index = 0;
		size_t pos = 0;
		int nn = 0;
		
		while ((nn = ss.find(ASCII_UNIT_SEPARATOR, pos)) > 0)
		{
			setString(ss.substr(pos, nn-pos), index++);
			pos = nn + 1;
		}

		if (pos < ss.size())
		{
			setString(ss.substr(pos), index);
		}

		return 0;
	}

	template <class T>
	int InternalKeyword<T>::setString(const std::string &data, int index)
	{
		T value;
		std::istringstream ist(data);
		ist >> value;
		return setValue_(index, value);
	}

	template <>
	int InternalKeyword<char>::setString(const std::string &data, int index)
	{
		int value;
		std::istringstream ist(data);
		ist >> value;
		return setValue_(index, value);
	}
	
	template <>
	int InternalKeyword<unsigned char>::setString(const std::string &data, int index)
        {
                int value;
                std::istringstream ist(data);
                ist >> value;
                return setValue_(index, value);
        }

	template <>
	int InternalKeyword<signed char>::setString(const std::string &data, int index)
        {
                int value;
                std::istringstream ist(data);
                ist >> value;
                return setValue_(index, value);
        }

	template <class T>
	const T *InternalKeyword<T>::getRawDataT() const
	{
		return &(data_[0]);
	}

	template <class T>
	const void *InternalKeyword<T>::getRawData() const
	{
		return static_cast<const void *>(getRawDataT());
	}

	template class InternalKeyword<char>;
	template class InternalKeyword<signed char>;
	template class InternalKeyword<unsigned char>;
	template class InternalKeyword<short>;
	template class InternalKeyword<int>;
	template class InternalKeyword<long>;
	template class InternalKeyword<long long>;
	template class InternalKeyword<float>;
	template class InternalKeyword<double>;
	template class InternalKeyword<std::string>;

}
