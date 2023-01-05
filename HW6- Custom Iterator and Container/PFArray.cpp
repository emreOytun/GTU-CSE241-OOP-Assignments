#include "PFArray.hpp"

namespace GTU {


	template<class T>
	PFArray<T>::PFArray() : data(nullptr), capacity_(0), size_(0) {
		adjustCapacity(50);
	}
	
	template<class T>
	PFArray<T>::PFArray(int capacityValue) : data(nullptr), capacity_(0), size_(0) {
		adjustCapacity(capacityValue);
	}
	
	template<class T>
	PFArray<T>::PFArray(const PFArray<T>& oth) : data(nullptr), capacity_(0), size_(0) {
		adjustCapacity(oth.capacity_); // Set the capacity to the other's capacity.
		size_ = oth.size_; // Set the size to the other's size.
		
		/* Copy the elements one-by-one. */
		for (int i = 0; i < size_; ++i) {
			data.get()[i] = oth.data.get()[i];
		}
	}
	
	template<class T>
	PFArray<T>& PFArray<T>::operator=(const PFArray<T>& rhs) {
		/* Release the old memory data. */
		data = nullptr;
		size_ = 0;
		capacity_ = 0;
		
		/* Set the capacity and size to the other's. */
		adjustCapacity(rhs.capacity_);
		size_ = rhs.size_;
		
		/* Copy the elements one-by-one. */
		for (int i = 0; i < size_; ++i) {
			data.get()[i] = rhs.data.get()[i];
		}
		
		return *this;
	}
	
	template<class T>
	PFArray<T>::PFArray(PFArray<T>&& oth) noexcept : capacity_(oth.capacity_), size_(oth.size_) {
		data = oth.data;
		
		/* Set other's internal data to default values to avoid dangling pointer. */
		oth.data = nullptr;
		oth.capacity_ = 0;
		oth.size_ = 0;
	}
	
	template<class T>
	PFArray<T>& PFArray<T>::operator=(PFArray<T>&& rhs) {
		data = rhs.data;
		capacity_ = rhs.capacity_;
		size_ = rhs.size_;
		
		rhs.data = nullptr;
		rhs.capacity_ = 0;
		rhs.size_ = 0;
	
		return *this;
	}
	
	template<class T>
	void PFArray<T>::add(const T& element) {
		if (size_ == capacity_) adjustCapacity(capacity_ * 2);
		data.get()[size_] = element;
		++size_;
	}
	
	template<class T>
	void PFArray<T>::clear() {
		data = nullptr;
		capacity_ = 0;
		size_ = 0;
		
		adjustCapacity(50);	// Set capacity to default value.
	}
	
	template<class T>
	Iterator<T> PFArray<T>::erase(const Iterator<T>& it) {
		Iterator<T> start = begin();
		bool isFound = false;
		int idx = -1;
		for (int i = 0; i < size_ && !isFound; ++i) {
			if (start == it) {
				isFound = true;
				idx = i;
			}
			else ++start;
		}
		
		/* If given iterator is not found then return end. */
		if (isFound == false) return end();
		
		/* Shift the elements toward the left side which is the position of the removed element. */
		for (int i = idx+1; i < size_; ++i) {
			data.get()[i-1] = data.get()[i];
		}
		
		/* Check if the given iterator pointed to the last element. */
		if (idx == size_-1) {
			--size_;
			/* Return the last element in the updated data if condition is true. */
			return Iterator<T>(data, size_-1);
		}
		else {
			--size_;
			/* If the given iterator points an element except the last element in the old array, then return the element following the last removed element. */
			return Iterator<T>(data, idx); 	
		}
	}
	
	
	template<class T>
	Iterator<T> PFArray<T>::erase(const ConstIterator<T>& it) {
		ConstIterator<T> start = cbegin();
		bool isFound = false;
		int idx = -1;
		for (int i = 0; i < size_ && !isFound; ++i) {
			if (start == it) {
				isFound = true;
				idx = i;
			}
			else ++start;
		}
		
		/* If given iterator is not found then return end. */
		if (isFound == false) return end();
		
		/* Shift the elements toward the left side which is the position of the removed element. */
		for (int i = idx+1; i < size_; ++i) {
			data.get()[i-1] = data.get()[i];
		}
		
		/* Check if the given iterator pointed to the last element. */
		if (idx == size_-1) {
			--size_;
			/* Return the last element in the updated data if condition is true. */
			return Iterator<T>(data, size_-1);
		}
		else {
			--size_;
			/* If the given iterator points an element except the last element in the old array, then return the element following the last removed element. */
			return Iterator<T>(data, idx); 	
		}
	}
	
	template<class T>
	Iterator<T> PFArray<T>::begin() noexcept { return Iterator<T>(data, 0); }
	
	template<class T>
	ConstIterator<T> PFArray<T>::begin() const noexcept { return ConstIterator<T>(data, 0); }
	
	template<class T>
	ConstIterator<T> PFArray<T>::cbegin() const noexcept { return ConstIterator<T>(data, 0); }
	
	template<class T>
	Iterator<T> PFArray<T>::end() noexcept { return Iterator<T>(data, size_); }
	
	template<class T>
	ConstIterator<T> PFArray<T>::end() const noexcept { return ConstIterator<T>(data, size_); }
	
	template<class T>
	ConstIterator<T> PFArray<T>::cend() const noexcept { return ConstIterator<T>(data, size_); }
	
	template<class T>
	int PFArray<T>::capacity() const noexcept {
		return capacity_;
	}
	
	template<class T>
	int PFArray<T>::size() const noexcept {
		return size_;
	}
	
	template<class T>
	bool PFArray<T>::empty() const noexcept {
		if (size_ == 0) return true;
		return false;
	}
	
	template<class T>
	T& PFArray<T>::operator[](int idx) {
		if (idx < 0 || idx >= size_) {
			throw out_of_range("EXCEPTION: Given index is out of boundaries.");
		}
		return data.get()[idx];
	}
	
	template<class T>
	const T& PFArray<T>::operator[](int idx) const {
		if (idx < 0 || idx >= size_) {
			throw out_of_range("EXCEPTION: Given index is out of boundaries.");
		}
		return data.get()[idx];
	}
	
	template<class T>
	void PFArray<T>::adjustCapacity(int newCapacity) {
		/* Allocate the new memory area. */
		shared_ptr<T> newData(new T[newCapacity], default_delete<T[]>()); /* To use shared_ptr with arrays properly, we should pass default_delete function parameter. */
	
		/* Copy the data into the new memory. */
		for (int i = 0; i < size_; ++i) {
			newData.get()[i] = data.get()[i];
		}
	
		/* Change old data to point new data and set new capacity. */
		data = newData;
		capacity_ = newCapacity;
	}
	
	
	
	
}
