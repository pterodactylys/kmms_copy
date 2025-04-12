#include "long_number.hpp"

using abc::LongNumber;
		
LongNumber::LongNumber() {
	length = 1;
	sign = 1;
	numbers = new int[length];
	numbers[0] = 0;
}

LongNumber::LongNumber(const char* const str) {
	int len = get_length(str);
	if (len == 0) {
		length = 1;
		sign = 1;
		numbers = new int[length];
		numbers[0] = 0;
	}
	else {
		if (str[0] == '-') {
			sign = -1;
			len--;
		}
		else {
			sign = 1;
		}
		length = len;
		numbers = new int[length];
		int start = (str[0] == '-') ? 1 : 0;
		for (int i = start; i < len + start; i++) {
			numbers[i - start] = str[i] - '0';
		}
	}
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = x.numbers[i];
	}
}

LongNumber::LongNumber(LongNumber&& x) {
	length = x.length;
	sign = x.sign;
	numbers = x.numbers;
	x.length = 0;
	x.sign = 0;
	x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	length = 0;
	delete[] numbers;
	numbers = nullptr;
	sign = 0;
}

LongNumber& LongNumber::operator = (const char* const str) {
	int len = get_length(str);
	if (len == 0) {
		length = 1;
		sign = 1;
		numbers = new int[length];
		numbers[0] = 0;
	}
	else {
		if (str[0] == '-') {
			sign = -1;
			len--;
		}
		else {
			sign = 1;
		}
		length = len;
		delete[] numbers;
		numbers = new int[length];
		int start = (str[0] == '-') ? 1 : 0;
		for (int i = start; i < len + start; i++) {
			numbers[i - start] = str[i] - '0';
		}
	}
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this != &x) {
		length = x.length;
		sign = x.sign;
		delete[] numbers;
		numbers = new int[length];
		for (int i = 0; i < length; i++) {
			numbers[i] = x.numbers[i];
		}
	}
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if (this != &x) {
		length = x.length;
		sign = x.sign;
		delete[] numbers;
		numbers = x.numbers;
		x.length = 0;
		x.sign = 0;
		x.numbers = nullptr;
	}
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (this == &x) {
		return true;
	}
	if (length != x.length || sign != x.sign) {
		return false;
	}
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) {
			return false;
		}
	}
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (this == &x) {
		return false;
	}
	if (sign != x.sign) {
		return sign > x.sign;
	}
	if (length != x.length) {
		if (sign == 1) {
			return length > x.length;
		}
		else {
			return length < x.length;
		}
	}
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) {
			if (sign == 1) {
				return numbers[i] > x.numbers[i];
			}
			else {
				return numbers[i] < x.numbers[i];
			}
		}
	}
	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	if (this == &x) {
		return false;
	}
	if (sign != x.sign) {
		return sign < x.sign;
	}
	if (length != x.length) {
		if (sign == 1) {
			return length < x.length;
		}
		else {
			return length > x.length;
		}
	}
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) {
			if (sign == 1) {
				return numbers[i] < x.numbers[i];
			}
			else {
				return numbers[i] > x.numbers[i];
			}
		}
	}
	return false;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	LongNumber result;
	int carry = 0;
	int maxLength = (length > x.length) ? length : x.length;
	result.length = maxLength + 1;
	result.sign = sign;
	result.numbers = new int[result.length];
	for (int i = 0; i < result.length; i++) {
		result.numbers[i] = 0;
	}
	if (sign == x.sign == 1) {
		for (int i = 0; i < maxLength; i++) {
			int a = (i < length) ? numbers[length - 1 - i] : 0;
			int b = (i < x.length) ? x.numbers[x.length - 1 - i] : 0;
			int sum = a + b + carry;
			result.numbers[result.length - 1 - i] = sum % 10;
			carry = sum / 10;
		}
		if (carry > 0) {
			result.numbers[0] = carry;
		}
		else {
			result.length--;
			for (int i = 0; i < result.length; i++) {
				result.numbers[i] = result.numbers[i + 1];
			}
		}
	}
	else if (sign == x.sign == -1) {
		for (int i = 0; i < maxLength; i++) {
			int a = (i < length) ? numbers[length - 1 - i] : 0;
			int b = (i < x.length) ? x.numbers[x.length - 1 - i] : 0;
			int sum = a + b + carry;
			result.numbers[result.length - 1 - i] = sum % 10;
			carry = sum / 10;
		}
		if (carry > 0) {
			result.numbers[0] = carry;
		}
		else {
			result.length--;
			for (int i = 0; i < result.length; i++) {
				result.numbers[i] = result.numbers[i + 1];
			}
		}
	}
	else if (sign == -1 && x.sign == 1) {
		LongNumber temp(*this);
		temp.sign = 1;
		return temp - x;
	}
	else if (sign == 1 && x.sign == -1) {
		LongNumber temp(x);
		temp.sign = 1;
		return *this - temp;
	}
	return result;
}


LongNumber LongNumber::operator - (const LongNumber& x) const {
	LongNumber result;
	int borrow = 0;
	int maxLength = (length > x.length) ? length : x.length;
	result.length = maxLength + 1;
	result.sign = sign;
	result.numbers = new int[result.length];
	for (int i = 0; i < result.length; i++) {
		result.numbers[i] = 0;
	}
	if (sign == x.sign == 1) {
		for (int i = 0; i < maxLength; i++) {
			int a = (i < length) ? numbers[length - 1 - i] : 0;
			int b = (i < x.length) ? x.numbers[x.length - 1 - i] : 0;
			int diff = a - b - borrow;
			if (diff < 0) {
				diff += 10;
				borrow = 1;
			}
			else {
				borrow = 0;
			}
			result.numbers[result.length - 1 - i] = diff % 10;
		}
		if (borrow > 0) {
			result.numbers[0] = borrow;
		}
		else {
			result.length--;
			for (int i = 0; i < result.length; i++) {
				result.numbers[i] = result.numbers[i + 1];
			}
		}
	}
	else if (sign == x.sign == -1) {
		for (int i = 0; i < maxLength; i++) {
			int a = (i < length) ? numbers[length - 1 - i] : 0;
			int b = (i < x.length) ? x.numbers[x.length - 1 - i] : 0;
			int diff = a - b - borrow;
			if (diff < 0) {
				diff += 10;
				borrow = 1;
			}
			else {
				borrow = 0;
			}
			result.numbers[result.length - 1 - i] = diff % 10;
		}
		if (borrow > 0) {
			result.numbers[0] = borrow;
		}
		else {
			result.length--;
			for (int i = 0; i < result.length; i++) {
				result.numbers[i] = result.numbers[i + 1];
			}
		}
	}
	else if (sign == -1 && x.sign == 1) {
		LongNumber temp(*this);
		temp.sign = 1;
		return temp + x;
	}
	else if (sign == 1 && x.sign == -1) {
		LongNumber temp(x);
		temp.sign = 1;
		return *this + temp;
	}
	return result;
}
			

LongNumber LongNumber::operator * (const LongNumber& x) const {
	LongNumber result;
	result.length = length + x.length;
	result.sign = sign * x.sign;
	result.numbers = new int[result.length];
	for (int i = 0; i < result.length; i++) {
		result.numbers[i] = 0;
	}
	for (int i = 0; i < length; i++) {
		int carry = 0;
		for (int j = 0; j < x.length; j++) {
			int product = numbers[length - 1 - i] * x.numbers[x.length - 1 - j] + carry + result.numbers[result.length - 1 - (i + j)];
			result.numbers[result.length - 1 - (i + j)] = product % 10;
			carry = product / 10;
		}
		if (carry > 0) {
			result.numbers[result.length - 1 - (i + x.length)] += carry;
		}
	}
	int leadingZeros = 0;
	while (leadingZeros < result.length && result.numbers[leadingZeros] == 0) {
		leadingZeros++;
	}
	if (leadingZeros == result.length) {
		delete[] result.numbers;
		result.length = 1;
		result.numbers = new int[result.length];
		result.numbers[0] = 0;
	}
	else {
		int newLength = result.length - leadingZeros;
		int* newNumbers = new int[newLength];
		for (int i = 0; i < newLength; i++) {
			newNumbers[i] = result.numbers[leadingZeros + i];
		}
		delete[] result.numbers;
		result.numbers = newNumbers;
		result.length = newLength;
	}
	return result;
}

// LongNumber LongNumber::operator / (const LongNumber& x) const {
// 	// TODO
// }

// LongNumber LongNumber::operator % (const LongNumber& x) const {
// 	// TODO
// }

// int LongNumber::get_digits_number() const noexcept {
// 	// TODO
// }

// int LongNumber::get_rank_number(int rank) const {
// 	// TODO
// }

// bool LongNumber::is_negative() const noexcept {
// 	// TODO
// }

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int count = 0;
	while (str[count] != '\0') {
		count++;
	}
	return count;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace abc {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.numbers == nullptr) {
			os << "0";
		}
		else {
			if (x.sign == -1) {
				os << "-";
			}
			for (int i = 0; i < x.length; i++) {
				os << x.numbers[i];
			}
		}
		return os;
	}
}
