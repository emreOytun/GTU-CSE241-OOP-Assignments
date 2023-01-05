#ifndef _PFARRAY_H_
#define _PFARRAY_H_

#include <memory>
#include <stdexcept>
#include "Iterator.cpp"
#include "ConstIterator.cpp"
using std::shared_ptr;
using std::default_delete;
using std::out_of_range;

namespace GTU {
	
	template<class T>
	class PFArray {
	
	public :
			
		/* Initializes the array with default 10 elements. */
		PFArray();	
		
		/* Initializes the array with the given capacity. */
		explicit PFArray(int capacityValue);  
		
		/* Big Five Functions */
		PFArray(const PFArray<T>& oth);
		PFArray& operator=(const PFArray<T>& rhs);
		
		PFArray(PFArray<T>&& oth) noexcept;
		PFArray& operator=(PFArray&& rhs);
		
		~PFArray() = default;
		
		void add(const T& element);
		void clear();
		
		/* Erase functions do not throw exception just like std::vector::erase function. */
		Iterator<T> erase(const Iterator<T>& it);
		Iterator<T> erase(const ConstIterator<T>& it);
		
		//iterator begin() noexcept { return iterator(data, 0); } /* Disarda yazmak zor ama icerde olursa bu sekilde yazilabilir. */
		Iterator<T> begin() noexcept;
		ConstIterator<T> begin() const noexcept;
		ConstIterator<T> cbegin() const noexcept;
		
		Iterator<T> end() noexcept;
		ConstIterator<T> end() const noexcept;
		ConstIterator<T> cend() const noexcept;
		
		int capacity() const noexcept;
		int size() const noexcept;
		bool empty() const noexcept;
		
		T& operator[](int idx); /* throws out_of_range exception */
		const T& operator[](int idx) const; /* throws out_of_range exception. */
		
	private : 
		shared_ptr<T> data;
		int capacity_;
		int size_;
		
		void adjustCapacity(int newCapacity);
	};

}


#endif
