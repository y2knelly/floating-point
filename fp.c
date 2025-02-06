#include <stdio.h>
#include <stdlib.h>

/*
 * Helper functions. These can be left alone.
 */

char *as_bin_str(int val) {
  /*
   * Convert an int to bits to print as a string 
   *
   * Example usage: 
   * int number = 7; 
   * printf("Number in binary: %s\n", int_to_bin(number)); 
   */
  static char buf[33] = { 0 };

  for (int i = 31; i >= 0; i -= 1) {
    buf[i] = "01"[val & 1];
    val = val >> 1;
  }

  return buf;
}

unsigned int as_int(float f) {
  /*
   * Aliases the passed float as an integer
   *
   * This allows integer operations such as masks and shifts
   */
  return *(unsigned int *) &f;
}

#define print_binary(v) \
  printf("0b%s for %s (%.02f as float) at line %d\n", \
  as_bin_str(*(unsigned int *) &v), #v, *(float *) &v, __LINE__)

/*
 * Provide Implementations for the following functions
 */

unsigned int is_negative(float f) {
  /*
   * Return true if the supplied float is negative 
   */
  return (as_int(f) >> 31) & 1;
}

unsigned int get_raw_exponent(float f) {
  /*
   * Returns the raw unsigned exponent bits of the passed float 
   */
   return (as_int(f) >> 23) & 0xFF;
}

int get_exponent(float f) {
  /*
   * Returns the exponent value of the passed float including the bias 
   *
   * Hint: You may call `get_raw_exponent`
   */
   return get_raw_exponent(f) - 127;
}

unsigned int get_raw_mantissa(float f) {
  /*
   * Returns the mantissa as extracted directly from the bit field
   */
  return as_int(f) & 0x7FFFFF;
}

unsigned int get_mantissa(float f) {
  /*
   * Returns the mantissa of the passed float 
   */
  return get_raw_mantissa(f) | (1 << 23);
}

int float_to_int(float f) {
  /*
   * Converts a float to an int 
   *
   * This function must perform the conversion manually. You may not
   * simply cast the float to an int
   *
   * Hint 1: Call the other functions you've implemented
   *
   * Hint 2: You need the left shift (<<) and right shift (>>) operators
   * 
   * Hint 3: Shift operators in C produce undefined results if shifting by
   * more than the operand word size or if shifting by a negative number
   */

  if (f == 0) {
    return 0;
  }

  unsigned int sign = is_negative(f);
  int exponent = get_exponent(f);
  unsigned int mantissa = get_mantissa(f);

  // Handle small numbers by returning 0
  if (exponent < 0) {
    return 0;
  }

  // Check for overflow
  if (exponent >= 31) {
    return sign ? 0x80000000 : 0x7FFFFFFF;
  }

  // Adjust mantissa based on exponent
  int result;
  if (exponent > 23) {
    result = mantissa << (exponent - 23);
  } else {
    result = mantissa >> (23 - exponent);
  }

  // Apply sign
  return sign ? -result : result;
}

/* 
Test code 

It is not recommended to modify any code below this point
*/

int _test_int_equal_result;

#define test_int_equal(exp, result) \
printf("Testing %s == %d\n", #exp, result); \
_test_int_equal_result = exp; \
if ((_test_int_equal_result) != result) { \
  printf("Test for %s == %d FAILED (got %d)\n", #exp, result, _test_int_equal_result); \
  exit(1); \
}

int main() {
  printf("Sign bit tests\n");
  test_int_equal(is_negative(0), 0);
  test_int_equal(is_negative(-1), 1);
  test_int_equal(is_negative(-5863921.5), 1);
  test_int_equal(is_negative(16.23), 0);

  printf("\nRaw Exponent tests\n");
  test_int_equal(get_raw_exponent(0), 0);
  test_int_equal(get_raw_exponent(-1), 127);
  test_int_equal(get_raw_exponent(16), 131);
  test_int_equal(get_raw_exponent(.5), 126);
  test_int_equal(get_raw_exponent(3), 128);
  test_int_equal(get_raw_exponent(.9), 126);
  test_int_equal(get_raw_exponent(457.2), 135);

  printf("\nExponent tests\n");
  test_int_equal(get_exponent(0), -127);
  test_int_equal(get_exponent(-1), 0);
  test_int_equal(get_exponent(16), 4);
  test_int_equal(get_exponent(.5), -1);
  test_int_equal(get_exponent(3), 1);
  test_int_equal(get_exponent(.9), -1);
  test_int_equal(get_exponent(457.2), 8);

  printf("\nRaw mantissa tests\n");
  test_int_equal(get_raw_mantissa(1.0), 0);
  test_int_equal(get_raw_mantissa(-0.25), 0);
  test_int_equal(get_raw_mantissa(-1), 0);
  test_int_equal(get_raw_mantissa(16), 0);
  test_int_equal(get_raw_mantissa(.5), 0);
  test_int_equal(get_raw_mantissa(3), 4194304);
  test_int_equal(get_raw_mantissa(.9), 6710886);
  test_int_equal(get_raw_mantissa(457.2), 6592922);
  test_int_equal(get_raw_mantissa(1.9999999), (1 << 23) - 1);

  printf("\nMantissa tests\n");
  test_int_equal(get_mantissa(1.0), 1 << 23);
  test_int_equal(get_mantissa(-0.25), 1 << 23);
  test_int_equal(get_mantissa(-1), 1 << 23);
  test_int_equal(get_mantissa(16), 1 << 23);
  test_int_equal(get_mantissa(.5), 1 << 23);
  test_int_equal(get_mantissa(3), 12582912);
  test_int_equal(get_mantissa(.9), 15099494);
  test_int_equal(get_mantissa(457.2), 14981530);
  test_int_equal(get_mantissa(1.9999999), 16777215);

  printf("\nfloat_to_int tests\n");
  test_int_equal(float_to_int(1), 1);
  test_int_equal(float_to_int(-1), -1);
  test_int_equal(float_to_int(16.5), 16);
  test_int_equal(float_to_int(408.3), 408);
  test_int_equal(float_to_int(-301.2), -301);
  test_int_equal(float_to_int(0.00000001), 0);
  test_int_equal(float_to_int(1.99), 1);
  test_int_equal(float_to_int(6.00001), 6);
  test_int_equal(float_to_int(49598123.12), 49598124);

  printf("\nAll tests passed.\n");
}
