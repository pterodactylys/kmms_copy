#pragma once
#include <iostream>

namespace abc {
	class LongNumber {
		private:
			int* numbers;
			int length;
			int sign;
		
		public:
			LongNumber();
			LongNumber(int num);
			LongNumber(const char* const str);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x);
			
			bool operator == (const LongNumber& x) const;
			bool operator != (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;
			bool operator >= (const LongNumber& x) const;
			bool operator <= (const LongNumber& x) const;
			
			LongNumber operator + (const LongNumber& x) const;
			LongNumber operator - (const LongNumber& x) const;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;

			LongNumber abs() const;
			LongNumber subtract_abs(const LongNumber& a, const LongNumber& b) const;
			LongNumber divide_absolute(const LongNumber& dividend, const LongNumber& divisor) const;
			
			int get_digits_number() const noexcept;
			int get_rank_number(const int rank) const;
			bool is_negative() const noexcept;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
			
		private:
			int get_length(const char* const str) const noexcept;
	};
}
