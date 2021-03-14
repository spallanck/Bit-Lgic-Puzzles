/*
 *
 * <Please put your name and userid here>
 * Sophie Pallanck W#01402279
 * 
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution by editing the collection of functions below.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  /* brief description of how your implementation works */
  int Funct(arg1, arg2, ...) {
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   *
   * exploit ability of shifts to compute powers of 2
   */
  int pow2plus1(int x) {
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   *
   * exploit ability of shifts to compute powers of 2
   */
  int pow2plus4(int x) {
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 *   Hint : less than 5 lines of code
 */
int bitAnd(int x, int y) {
  /*Used the principles of DeMorgans laws to 
  simulate the use of the & operator. In this case 
  the ~ is distributive and will change this line
  of code into x & y */
  return ~(~x | ~y);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 *   Hint : less than 5 lines of code
 */  
int getByte(int x, int n) { 
  /* Exploits the ability of the left shift
  to multiply by powers of 2 in order to shift the
  correct byte into the right-most position, then uses
  shifting of 1s and the integer 255 which has all ones
  in the right-most byte, to get rid of any leading 1s before
  returning the correct byte */
  int shifts = n << 3; 
  int result = x >> shifts;
  int cover = 1 << 31;
  cover = cover >> 23;
  cover = ~cover;
  result = result & cover;
  return result;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 *   Hint : less than 10 lines of code
 */
int logicalShift(int x, int n) {
  /*Preforms a standard arithmetic shift to the right
  by n, then goes back and zeros out any left-most
  1s that may have been carried over (as in the
  case of negative input), so as to simulate a
  logical shift */
  int result = x >> n;
  int zeroOut = 1 << 31;
  zeroOut = zeroOut >> n;
  zeroOut = zeroOut << 1;
  zeroOut = ~zeroOut;
  result = result & zeroOut;
  return result;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 *   Hint : less than 10 lines of code
 */
int bitCount(int x) {
  /*Uses the Hamming Weight algorithm also known 
  as Population Count to create 'masks', which are used to
  extract certain values, toggle values, or set certain values. In
  this case, bit masks are used to sort of divide and conquer the problem
  by summing smaller sections of the number and using shifts to add them
  up */
  int oneApart = 85;
  int twoApart = 51;
  int fourApart = 15;
  int eighApart = 255;
  int sixtApart = 255;
  int count = 0;
  oneApart = oneApart + (85 << 8);
  oneApart = oneApart + (85 << 16);
  oneApart = oneApart + (85 << 24);
  twoApart = twoApart + (51 << 8);
  twoApart = twoApart + (51 << 16);
  twoApart = twoApart + (51 << 24);
  fourApart = fourApart + (15 << 8);
  fourApart = fourApart + (15 << 16);
  fourApart = fourApart + (15 << 24);
  eighApart = eighApart + (255 << 16);
  sixtApart = sixtApart + (255 << 8);
  count = (x & oneApart) + ((x >>  1) & oneApart);  
  count = (count & twoApart) + ((count >>  2) & twoApart); 
  count = (count + (count >> 4) & fourApart); 
  count = (count + (count >> 8) & eighApart); 
  count = (count + (count >> 16) & sixtApart); 
  return count;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 *   Hint : less than 5 lines of code
 */
int tmin(void) {
  /*The smallest possible negative integer is 
  represented by a 1 in the left-most position */
  return 1 << 31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 *   Hint : less than 5 lines of code
 */
int fitsBits(int x, int n) {
  /*Checks to see if x can be represented in n bits
  using the idea that if x can fit in n bits, then shifting left 
  and then right by 33 - (n + 1) (and potentially using sign extension)
  will cause our result to either equal zero, meaning we can fit in n bits
  or equal some non-zero value, meaning we cannot fit in n bits
  (Special thank you to Filip for telling us which
  operators to use and tipping us off about 33 + ~n, we were struggling) */
  int num_shifts = 33 + ~n;
  int result = x << num_shifts;
  result = result >> num_shifts;
  result = x ^ result;
  return !result;
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 *   Hint : less than 5 lines of code
*/
int divpwr2(int x, int n) {
  /*Exploits the ability of the right shift to divide x by 
  2^n, but needs to take into account the special case where 
  x is negative and does not go into 2^n evenly and rounding the numbers
  down instead of to 0, by forcing all negative numbers to be able to round
  down to the correct answer, instead of rounding down to one smaller */
    int grabSign = x >> 31; 
    int addOne = grabSign & 1; 
    int correctX = addOne << n; 
    correctX = correctX + grabSign; 
    correctX = x + correctX; 
    correctX = correctX >> n; 
    return correctX;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 *   Hint : less than 5 lines of code
 */
int negate(int x) {
  /* Take the 2s complement of the
  integer and return it */
  return ~x + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 *   Hint : less than 5 lines of code
 */
int isPositive(int x) {
  /*The left-most bit will be 1 if the number
  is negative, and 0 otherwise, so you need to inspect
  it, and use the not boolean operator to return the correct
  result. There is also a special case where 0 is considered
  to be positive and will return 1, so we must negate that */
  int grabSign = x >> 31; 
  int testZero = !x;
  grabSign = grabSign & 1;
  return !(!!grabSign | testZero);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 *   Hint : less than 100 lines of code
 */
int ilog2(int x) {
  /*Shift the most significant set bit to the
  right-most side, causing log2(x) - 1 ones
  to be placed on the right side of the integer, then uses bitCount
  to count the number of set bits and subtracts one from the
  count to get the correct answer */
  int oneApart = 85;
  int twoApart = 51;
  int fourApart = 15;
  int eighApart = 255;
  int sixtApart = 255;
  int count = 0;
  x = x | x >> 1;
  x = x | x >> 2;
  x = x | x >> 4;
  x = x | x >> 8;
  x = x | x >> 16;
  oneApart = oneApart + (85 << 8);
  oneApart = oneApart + (85 << 16);
  oneApart = oneApart + (85 << 24);
  twoApart = twoApart + (51 << 8);
  twoApart = twoApart + (51 << 16);
  twoApart = twoApart + (51 << 24);
  fourApart = fourApart + (15 << 8);
  fourApart = fourApart + (15 << 16);
  fourApart = fourApart + (15 << 24);
  eighApart = eighApart + (255 << 16);
  sixtApart = sixtApart + (255 << 8);
  count = (x & oneApart) + ((x >>  1) & oneApart);  
  count = (count & twoApart) + ((count >>  2) & twoApart); 
  count = (count + (count >> 4) & fourApart); 
  count = (count + (count >> 8) & eighApart); 
  count = (count + (count >> 16) & sixtApart); 
  count = count + ~0;
  return count;
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 *   Hint : less than 10 lines of code
 */
unsigned float_neg(unsigned uf) {
  /*To negate a floating point number,
  simply flip the sign bit stored at
  the beginning of floating point numbers, also check
  if the number passed in is a NaN by comparing the exp 
  portion of the number to make sure it is not all 1s, and the
  frac portion of the number to make sure it is not all 0s */
  int nanExp = 255 << 23; 
  int frac = 8388607; 
  if ((nanExp & uf) == nanExp && (frac & uf) != 0) {
    return uf;
  }
  return uf ^ (1 << 31); 
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 *   Hint : less than 20 lines of code
 */
unsigned float_twice(unsigned uf) {
  /*The basic idea is to add 1 to the exp bits of the float
  but there are several special cases to account for, like the 
  NaN case, the case where uf is zero, and cases where the number is too
  big or too small to be represented by a float */
  int nanExp = 255 << 23; 
  int checkSmall = uf >> 23;
  int frac = 8388607; 
  if ((nanExp & uf) == nanExp && (frac & uf) != 0) {
    return uf;
  }
  if (uf == 0x7f800000 || uf == 0xff800000 || uf == 0x80000000) {
    return uf;
  }
  if (uf == 0) {
    return 0;
  }
  if ((checkSmall & 255) == 0x0) {
    return (uf & (1 << 31)) | (uf << 1);
  }
  return uf + (1 << 23);
}
