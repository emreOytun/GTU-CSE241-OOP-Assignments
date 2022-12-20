#ifndef _DAYOFYEARSET_H_
#define _DAYOFYEARSET_H_

using std::ostream;
using std::initializer_list;

namespace GTUDate {
	
	class DayOfYearSet {

	public :

		class DayOfYear {
			
		public :
			DayOfYear();
			DayOfYear(int day_, int month_); /* throws invalid_argument */
				
			DayOfYear(const DayOfYear& oth) = default;
			DayOfYear& operator=(const DayOfYear& oth) = default;
			~DayOfYear() noexcept = default;
			
			void setDate(int day_, int month_); /* throws invalid_argument */
			void setMonth(int month_); /* throws invalid_argument */
			void setDay(int day_); /* throws invalid_argument */
			
			int getMonth() const noexcept;
			int getDay() const noexcept;
			
			bool operator==(const DayOfYear& oth) const noexcept;
			bool operator!=(const DayOfYear& oth) const noexcept;
			
			DayOfYear& operator++() noexcept;
			const DayOfYear operator++(int) noexcept;
			DayOfYear& operator--() noexcept;
			const DayOfYear operator--(int) noexcept;
			
			friend ostream& operator<<(ostream& ostream, const DayOfYear& date); 
			
		private :
			int day;
			int month;
		
		};
		
		DayOfYearSet();
		DayOfYearSet(const initializer_list<DayOfYear>& list);
		
		DayOfYearSet(const DayOfYearSet& oth);
		DayOfYearSet& operator=(const DayOfYearSet& oth);
		
		~DayOfYearSet() noexcept;
		
		void add(const DayOfYear& newDate);
		void remove(const DayOfYear& date);
		int size() const noexcept;
		
		DayOfYear& operator[](int idx); /* throws out_of_range */
		const DayOfYear operator[](int idx) const; /* throws out_of_range */
 		
		bool operator==(const DayOfYearSet& oth) const noexcept;
		bool operator!=(const DayOfYearSet& oth) const noexcept;
		
		/* '+'/'-' operators adds/removes the new date into/from the object whose operator is called and returns this object, since it's written in that way in the HW PDF. */
		DayOfYearSet& operator+(const DayOfYear& date);
		DayOfYearSet& operator-(const DayOfYear& date);
		
		const DayOfYearSet operator+(const DayOfYearSet& oth) const;
		const DayOfYearSet operator-(const DayOfYearSet& oth) const;
		const DayOfYearSet operator^(const DayOfYearSet& oth) const;
		
	
		friend const DayOfYearSet operator!(const DayOfYearSet& dateSet);
		friend ostream& operator<<(ostream& ostream, const DayOfYearSet& dateSet);
		
		
	private :
		DayOfYear* data;
		int len;
		int capacity;
		
		void adjustCapacity(int newCapacity);
		bool isExist(const DayOfYear& date) const noexcept;

	};

}

#endif


