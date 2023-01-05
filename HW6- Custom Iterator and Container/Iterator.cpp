#include "Iterator.hpp"

namespace GTU {
	
	
	template<class T>
	Iterator<T>::Iterator(shared_ptr<T> elementPtr, int pos_) : ptr(elementPtr), pos(pos_) {
				
	}
	
	template<class T>
	T& Iterator<T>::operator*() const {
		return ptr.get()[pos];
	}
	
	template<class T>
	T* Iterator<T>::operator->() const {
		return ptr.get() + pos;
	}
	
	template<class T>
	Iterator<T>& Iterator<T>::operator++() {
		++pos;
		return *this;
	}
	
	template<class T>
	Iterator<T> Iterator<T>::operator++(int) {
		Iterator<T> copy = *this;
		++pos;
		return copy;
	}
	
	template<class T>
	Iterator<T>& Iterator<T>::operator--() {
		--pos;
		return *this;
	}
	
	template<class T>
	Iterator<T> Iterator<T>::operator--(int) {
		Iterator<T> copy = *this;
		--pos;
		return copy;
	}		
	
	template<class T>
	Iterator<T> Iterator<T>::operator-(std::ptrdiff_t n) const {
		return Iterator<T>(ptr, pos-n);
	}		
	
	template<class T>
	Iterator<T> Iterator<T>::operator+(std::ptrdiff_t n) const {
		return Iterator<T>(ptr, pos+n);
	}
	
	
	template<class T>
	std::ptrdiff_t Iterator<T>::operator-(const Iterator<T>& rhs) const {
		return pos - rhs.pos;
	}
			
	template<class T>
	bool Iterator<T>::operator==(const Iterator<T>& rhs) const noexcept {
		if (ptr == rhs.ptr && pos == rhs.pos) return true;
		return false;
	}

	template<class T>	
	bool Iterator<T>::operator!=(const Iterator<T>& rhs) const noexcept {
		return !(*this == rhs);
	}
	
	template<class T>	
	bool Iterator<T>::operator<(const Iterator<T> rhs) const {
		return pos < rhs.pos;
	}
	
	template<class T>	
	bool Iterator<T>::operator<=(const Iterator<T> rhs) const {
		return pos <= rhs.pos;
	}

	template<class T>	
	bool Iterator<T>::operator>(const Iterator<T> rhs) const {
		return pos > rhs.pos;
	}

	template<class T>	
	bool Iterator<T>::operator>=(const Iterator<T> rhs) const {
		return pos >= rhs.pos;
	}
	

}
