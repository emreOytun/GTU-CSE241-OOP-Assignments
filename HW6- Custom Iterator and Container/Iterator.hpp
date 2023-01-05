#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <memory>
#include <iterator>
using std::shared_ptr;

namespace GTU {

	template<class T>
	class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {

	public :
		/* Specify iterator traits to the compiler. */
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using iterator_category = typename std::iterator<std::random_access_iterator_tag, T>::iterator_category;
	
		Iterator(shared_ptr<T> elementPtr, int pos_);
		
		/* BIG THREE is default and no need to move semantics here, since shallow copy is enough. */
		Iterator(const Iterator<T>& oth) = default;
		~Iterator() = default;
		Iterator& operator=(const Iterator<T>& oth) = default;
		
		reference operator*() const;
		pointer operator->() const;
		
		Iterator<T>& operator++();
		Iterator<T> operator++(int);
		Iterator<T>& operator--();
		Iterator<T> operator--(int);
		
		
		Iterator<T> operator-(difference_type n) const;
		Iterator<T> operator+(difference_type n) const;
		
		difference_type operator-(const Iterator<T>& rhs) const;
				
		bool operator==(const Iterator<T>& rhs) const noexcept;
		bool operator!=(const Iterator<T>& rhs) const noexcept;
		bool operator<(const Iterator<T> rhs) const;
		bool operator<=(const Iterator<T> rhs) const;
		bool operator>(const Iterator<T> rhs) const;
		bool operator>=(const Iterator<T> rhs) const;
		
	private :	
		/* Keep the dynamic array's pointer and the position to reach the specific element. */
		shared_ptr<T> ptr;
		int pos;
	};

}


#endif






