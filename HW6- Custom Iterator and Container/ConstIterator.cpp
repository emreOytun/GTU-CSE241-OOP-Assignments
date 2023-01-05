#include "ConstIterator.hpp"

namespace GTU {
	
	template<class T>
	ConstIterator<T>::ConstIterator(shared_ptr<const T> elementPtr, int pos_) : ptr(elementPtr), pos(pos_) {
			
	}
	
	template<class T>
	const T& ConstIterator<T>::operator*() const {
		return ptr.get()[pos];
	}
	
	template<class T>
	const T* ConstIterator<T>::operator->() const {
		return ptr.get() + pos;
	}
	
	template<class T>
	ConstIterator<T>& ConstIterator<T>::operator++() {
		++pos;
		return *this;
	}
	
	template<class T>
	ConstIterator<T> ConstIterator<T>::operator++(int) {
		ConstIterator<T> copy = *this;
		++pos;
		return copy;
	}
	
	template<class T>
	ConstIterator<T>& ConstIterator<T>::operator--() {
		--pos;
		return *this;
	}
	
	template<class T>
	ConstIterator<T> ConstIterator<T>::operator--(int) {
		ConstIterator<T> copy = *this;
		--pos;
		return copy;
	}
	
	template<class T>
	ConstIterator<T> ConstIterator<T>::operator-(std::ptrdiff_t n) const {
		return ConstIterator<T>(ptr, pos-n);
	}
	
	template<class T>
	ConstIterator<T> ConstIterator<T>::operator+(std::ptrdiff_t n) const {
		return ConstIterator<T>(ptr, pos+n);
	}
	
	template<class T>
	std::ptrdiff_t ConstIterator<T>::operator-(const ConstIterator<T>& rhs) const {
		return pos - rhs.pos;
	}
	
	template<class T>
	bool ConstIterator<T>::operator==(const ConstIterator<T>& rhs) const noexcept {
		if (ptr == rhs.ptr && pos == rhs.pos) return true;
		return false;
	}
	
	template<class T>
	bool ConstIterator<T>::operator!=(const ConstIterator<T>& rhs) const noexcept {
		return !(*this == rhs);
	}
	
	template<class T>
	bool ConstIterator<T>::operator<(const ConstIterator<T> rhs) const {
		return pos < rhs.pos;
	}
	
	template<class T>
	bool ConstIterator<T>::operator<=(const ConstIterator<T> rhs) const {
		return pos <= rhs.pos;
	}
	
	template<class T>
	bool ConstIterator<T>::operator>(const ConstIterator<T> rhs) const {
		return pos > rhs.pos;
	}
	
	template<class T>
	bool ConstIterator<T>::operator>=(const ConstIterator<T> rhs) const {
		return pos >= rhs.pos;
	}	
		
}
