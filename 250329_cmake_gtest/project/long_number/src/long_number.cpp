#include "long_number.hpp"

using abc::LongNumber;
		
LongNumber::LongNumber() {
	length = 1;
	sign = 1;
	numbers = new int[length];
	numbers[0] = 0;
}

LongNumber::LongNumber(int num) {
    if (num == 0) {
        length = 1;
        sign = 1;
        numbers = new int[length];
        numbers[0] = 0;
        return;
    }

    sign = (num >= 0) ? 1 : -1;
    num = std::abs(num);
    int temp = num;
    length = 0;
    while (temp != 0) {
        temp /= 10;
        length++;
    }

    numbers = new int[length];
    for (int i = length - 1; i >= 0; i--) {
        numbers[i] = num % 10;
        num /= 10;
    }
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

bool LongNumber::operator >= (const LongNumber& x) const {
	return !(*this < x);
}

bool LongNumber::operator <= (const LongNumber& x) const {
	return !(*this > x);
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    if (sign == x.sign) {
        LongNumber result;
        int carry = 0;
        int maxLength = std::max(length, x.length);
        result.length = maxLength + 1;
        result.sign = sign;
        result.numbers = new int[result.length]();
        
        for (int i = 0; i < maxLength; i++) {
            int a = (i < length) ? numbers[length - 1 - i] : 0;
            int b = (i < x.length) ? x.numbers[x.length - 1 - i] : 0;
            int sum = a + b + carry;
            result.numbers[result.length - 1 - i] = sum % 10;
            carry = sum / 10;
        }
        
        if (carry > 0) {
            result.numbers[0] = carry;
        } else {
            int* newNumbers = new int[result.length - 1];
            for (int i = 0; i < result.length - 1; i++) {
                newNumbers[i] = result.numbers[i + 1];
            }
            delete[] result.numbers;
            result.numbers = newNumbers;
            result.length--;
        }
        
        return result;
    } else {
        if (sign == -1) {
            LongNumber temp = *this;
            temp.sign = 1;
            return x - temp;
        } else {
            LongNumber temp = x;
            temp.sign = 1;
            return *this - temp;
        }
    }
}


LongNumber LongNumber::operator - (const LongNumber& x) const {
    if (sign == 1 && x.sign == 1) {
        if (*this >= x) {
            return subtract_abs(*this, x);
        } else {
            LongNumber result = subtract_abs(x, *this);
            result.sign = -1;
            return result;
        }
    } else if (sign == -1 && x.sign == -1) {
        LongNumber temp1 = *this;
        temp1.sign = 1;
        LongNumber temp2 = x;
        temp2.sign = 1;
        return temp2 - temp1;
    } else {
        LongNumber temp = x;
        temp.sign = (x.sign == 1) ? -1 : 1;
        return *this + temp;
    }
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

LongNumber LongNumber::operator / (const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0) {
        throw std::runtime_error("Division by zero");
    }

    int resultSign = (sign == x.sign) ? 1 : -1;

    LongNumber dividend = this->abs();
    LongNumber divisor = x.abs();
    
    if (dividend < divisor) {
        LongNumber zero("0");
        zero.sign = resultSign;
        return zero;
    }

    LongNumber quotient = divide_absolute(dividend, divisor);
    quotient.sign = resultSign;

    if (sign != x.sign && !((*this % x) == 0)) {
        quotient = quotient + LongNumber("-1");
    }

    return quotient;
}

LongNumber LongNumber::divide_absolute(const LongNumber& dividend, const LongNumber& divisor) const {
    LongNumber quotient;
    quotient.length = dividend.length;
    quotient.numbers = new int[quotient.length]();
    quotient.sign = 1;

    LongNumber currentValue("0");

    for (int i = 0; i < dividend.length; i++) {
        currentValue = currentValue * LongNumber("10") + LongNumber(dividend.numbers[i]);

        int digit = 0;
        while (digit <= 9) {
            LongNumber multiple = divisor * LongNumber(digit);
            if (multiple > currentValue) {
                digit--;
                break;
            }
            digit++;
        }
        
        digit = std::max(0, digit);
        quotient.numbers[i] = digit;

        if (digit > 0) {
            currentValue = currentValue - (divisor * LongNumber(digit));
        }
    }

    int leadingZeros = 0;
    while (leadingZeros < quotient.length && quotient.numbers[leadingZeros] == 0) {
        leadingZeros++;
    }

    if (leadingZeros > 0) {
        int newLength = quotient.length - leadingZeros;
        int* newNumbers = new int[newLength];
        for (int i = 0; i < newLength; i++) {
            newNumbers[i] = quotient.numbers[leadingZeros + i];
        }
        delete[] quotient.numbers;
        quotient.numbers = newNumbers;
        quotient.length = newLength;
    }
    return quotient;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	if (x.length == 1 && x.numbers[0] == 0) {
		throw std::runtime_error("Division by zero");
	}

	LongNumber quotient = *this / x;
	LongNumber product = quotient * x;
	LongNumber remainder = *this - product;

	if (remainder.sign == -1) {
		remainder.sign = 1;
		return remainder + x;
	}
	int leadingZeros = 0;
    while (leadingZeros < remainder.length && remainder.numbers[leadingZeros] == 0) {
        leadingZeros++;
    }

    if (leadingZeros == remainder.length) {
        return LongNumber("0");
    }

    if (leadingZeros > 0) {
        int newLength = remainder.length - leadingZeros;
        int* newNumbers = new int[newLength];
        for (int i = 0; i < newLength; i++) {
            newNumbers[i] = remainder.numbers[leadingZeros + i];
        }
        delete[] remainder.numbers;
        remainder.numbers = newNumbers;
        remainder.length = newLength;
    }

	return remainder;
}

LongNumber LongNumber::abs() const {
    LongNumber result = *this;
    result.sign = 1;
    return result;
}

LongNumber LongNumber::subtract_abs(const LongNumber& a, const LongNumber& b) const {
    LongNumber result;
    result.length = a.length;
    result.sign = 1;
    result.numbers = new int[result.length]();
    
    int borrow = 0;
    for (int i = 0; i < a.length; i++) {
        int digit_a = a.numbers[a.length - 1 - i];
        int digit_b = (i < b.length) ? b.numbers[b.length - 1 - i] : 0;
        int diff = digit_a - digit_b - borrow;
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.numbers[result.length - 1 - i] = diff;
    }
    
    int leading_zeros = 0;
    while (leading_zeros < result.length && result.numbers[leading_zeros] == 0) {
        leading_zeros++;
    }
    
    if (leading_zeros == result.length) {
        return LongNumber("0");
    }
    
    if (leading_zeros > 0) {
        int new_length = result.length - leading_zeros;
        int* new_numbers = new int[new_length];
        for (int i = 0; i < new_length; i++) {
            new_numbers[i] = result.numbers[leading_zeros + i];
        }
        delete[] result.numbers;
        result.numbers = new_numbers;
        result.length = new_length;
    }
    
    return result;
}

int LongNumber::get_digits_number() const noexcept {
	return length;
}

int LongNumber::get_rank_number(const int rank) const {
	if (rank < 1 || rank > length) {
		throw std::out_of_range("Rank out of range");
	}
	return numbers[length - rank];
}

bool LongNumber::is_negative() const noexcept {
	return sign == -1;
}

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
