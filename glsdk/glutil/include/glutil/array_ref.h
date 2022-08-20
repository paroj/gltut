/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/


#ifndef ARRAY_REF_OPENGL_UTILITY_H
#define ARRAY_REF_OPENGL_UTILITY_H

/**
\file
\brief Contains the array reference utility class.
**/

#include <vector>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <array>

/**
\brief For special reference utility types.

These are utility objects that are just handy to use for everyday C++ tasks. Sadly they
aren't part of Boost or anything, so I have to implement them here.

**/
namespace refs
{
	/**
	\brief A constant reference to an array.
	
	This class represents a constant reference to an array of values. It is \em not a container.
	Containers have storage, and array_ref does not manage the storage for anything.
	
	The idea is that you use array_ref in function interfaces, rather than std::vector. Why?
	So that the user has the freedom to use C-style arrays, boost::array, or any number of other
	array-like classes to manage their memory. A function that takes array_ref quite simply
	does not care how the user is managing the memory; it just wants an array of stuff.

	This serves as a happy medium between giving the user the freedom to use any possible container
	by using a range+template, and forcing the user to use exactly and only one container type.

	This version of array_ref can be implicitly constructed from:
	\li boost::array
	\li std::vector
	\li C-style arrays with a fixed size (int[4])

	They can also be constructed from a pointer + a size.

	This class fulfills all of the requirements for a sequential range in C++. It's iterators
	are random-access iterators, and in fact are pointers. It's interface works effectively like
	that of std::vector, except that it only provides const access to its members.

	The only mutating operations allowed on this type are clearing and removing elements from the
	front/back of the array.

	\ingroup module_glutil
	**/
	template<typename T>
	class array_ref
	{
	public:
		typedef T value_type;
		typedef const T * pointer;
		typedef const T & reference;
		typedef const T & const_reference;
		typedef const T * const_iterator;
		typedef const_iterator iterator;
		typedef std::reverse_iterator< const_iterator > const_reverse_iterator;
		typedef const_reverse_iterator reverse_iterator;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		// construct/copy
		array_ref() : m_data(NULL), m_size(0) {}

		array_ref(const T *arr, size_t length) : m_data(arr), m_size(length) {}
		array_ref(const std::vector<T> & v) : m_data(&v[0]), m_size(v.size()) {}
		template<size_t N>
		array_ref(const T(&a)[N]) : m_data(a), m_size(N) {}
		template<size_t N>
		array_ref(const std::array< T, N > & a) : m_data(a.data()), m_size(N) {}

		const_iterator begin() const {return m_data;}
		const_iterator end() const {return m_data + m_size;}
		const_iterator cbegin() const {return m_data;}
		const_iterator cend() const {return m_data + m_size;}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
		const_reverse_iterator crbegin() const  {return const_reverse_iterator(cend());}
		const_reverse_iterator crend() const {return const_reverse_iterator(cbegin());}

		size_type size() const {return m_size;}
		size_type max_size() const {return std::numeric_limits<size_type>::max();}
		bool empty() const {return m_size == 0;}

		const T & operator[](size_t i) const {return m_data[i];}
		const T & at(size_t i) const
		{
			if(i >= m_size)
				throw std::out_of_range("Error: array indexing out of range");
			return m_data[i];
		}
		const T & front() const {return m_data[0];}
		const T & back() const {return m_data[m_size - 1];}
		const T * data() const {return m_data;}

		std::vector<T> vec() const {return std::vector<T>(m_data, m_data + m_size);}
		std::basic_string<T> str() const {return std::basic_string<T>(m_data, m_data + m_size);}

		void clear() {m_size = 0; m_data = NULL;}
		void remove_prefix(size_type n)
		{
			m_data += n;
			m_size -= n;
			if(m_size <= 0)
				clear();
		}

		void remove_suffix(size_type n)
		{
			m_size -= n;
			if(m_size <= 0)
				clear();
		}

		void pop_front() {remove_prefix(1);}
		void pop_back() {remove_suffix(1);}
	private:
		const T *m_data;
		size_t m_size;
	};
}


#endif //ARRAY_REF_OPENGL_UTILITY_H
