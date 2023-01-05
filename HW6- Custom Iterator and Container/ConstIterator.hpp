#ifndef _CONST_ITERATOR_H_
#define _CONST_ITERATOR_H_

#include <memory>
using std::shared_ptr;

namespace GTU {

	template<class T>
	class ConstIterator : public std::iterator<std::bidirectional_iterator_tag, const T> {
		
	public :
		/* Specify iterator traits to the compiler. */
		using difference_type = std::ptrdiff_t;
	    	using value_type = const T;
		using reference = const T&;
		using pointer = const T*;
	    	using iterator_category = std::bidirectional_iterator_tag;
	    	
		ConstIterator(shared_ptr<const T> elementPtr, int pos_);
		
		/* BIG THREE is default and no need to move semantics here, since shallow copy is enough. */
		ConstIterator(const ConstIterator<T>& oth) = default;
		ConstIterator<T>& operator=(const ConstIterator<T>& oth) = default;
		~ConstIterator() = default;
		
		reference operator*() const;
		pointer operator->() const;
		
		ConstIterator<T>& operator++();
		ConstIterator<T> operator++(int);
		ConstIterator<T>& operator--();
		ConstIterator<T> operator--(int);
		
		
		ConstIterator<T> operator-(difference_type n) const;
		ConstIterator<T> operator+(difference_type n) const;
		
		difference_type operator-(const ConstIterator<T>& rhs) const;
		
		bool operator==(const ConstIterator<T>& rhs) const noexcept;
		bool operator!=(const ConstIterator<T>& rhs) const noexcept;
		bool operator<(const ConstIterator<T> rhs) const;
		bool operator<=(const ConstIterator<T> rhs) const;
		bool operator>(const ConstIterator<T> rhs) const;
		bool operator>=(const ConstIterator<T> rhs) const;
		
	private :
		shared_ptr<const T> ptr;
		int pos;
	};
	

}


#endif

