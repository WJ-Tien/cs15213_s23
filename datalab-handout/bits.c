/*

* CS:APP Data Lab

*

* <Please put your name and userid here>

*

* bits.c - Source file with your solutions to the Lab.

*          This is the file you will hand in to your instructor.

*/

/* Instructions to Students:



You will provide your solution to the Data Lab by

editing the collection of functions in this source file.



INTEGER CODING RULES:



  Replace the "return" statement in each function with one

  or more lines of C code that implements the function. Your code

  must conform to the following style:



  long Funct(long arg1, long arg2, ...) {

      // brief description of how your implementation works

      long var1 = Expr1;

      ...

      long varM = ExprM;



      varJ = ExprJ;

      ...

      varN = ExprN;

      return ExprR;

  }



  Each "Expr" is an expression using ONLY the following:

  1. (Long) integer constants 0 through 255 (0xFFL), inclusive. You are

      not allowed to use big constants such as 0xffffffffL.

  2. Function arguments and local variables (no global variables).

  3. Local variables of type int and long

  4. Unary integer operations ! ~

     - Their arguments can have types int or long

     - Note that ! always returns int, even if the argument is long

  5. Binary integer operations & ^ | + << >>

     - Their arguments can have types int or long

  6. Casting from int to long and from long to int



  Some of the problems restrict the set of allowed operators even further.

  Each "Expr" may consist of multiple operators. You are not restricted to

  one operator per line.



  You are expressly forbidden to:

  1. Use any control constructs such as if, do, while, for, switch, etc.

  2. Define or use any macros.

  3. Define any additional functions in this file.

  4. Call any functions.

  5. Use any other operations, such as &&, ||, -, or ?:

  6. Use any form of casting other than between int and long.

  7. Use any data type other than int or long.  This implies that you

     cannot use arrays, structs, or unions.



  You may assume that your machine:

  1. Uses 2s complement representations for int and long.

  2. Data type int is 32 bits, long is 64.

  3. Performs right shifts arithmetically.

  4. Has unpredictable behavior when shifting if the shift amount

     is less than 0 or greater than 31 (int) or 63 (long)



EXAMPLES OF ACCEPTABLE CODING STYLE:

  //

  // pow2plus1 - returns 2^x + 1, where 0 <= x <= 63

  //

  long pow2plus1(long x) {

     // exploit ability of shifts to compute powers of 2

     // Note that the 'L' indicates a long constant

     return (1L << x) + 1L;

  }



  //

  // pow2plus4 - returns 2^x + 4, where 0 <= x <= 63

  //

  long pow2plus4(long x) {

     // exploit ability of shifts to compute powers of 2

     long result = (1L << x);

     result += 4L;

     return result;

  }



NOTES:

  1. Use the dlc (data lab checker) compiler (described in the handout) to

     check the legality of your solutions.

  2. Each function has a maximum number of operations (integer, logical,

     or comparison) that you are allowed to use for your implementation

     of the function.  The max operator count is checked by dlc.

     Note that assignment ('=') is not counted; you may use as many of

     these as you want without penalty.

  3. Use the btest test harness to check your functions for correctness.

  4. Use the BDD checker to formally verify your functions

  5. The maximum number of ops for each function is given in the

     header comment for each function. If there are any inconsistencies

     between the maximum ops in the writeup and in this file, consider

     this file the authoritative source.



CAUTION:

  Do not add an #include of <stdio.h> (or any other C library header)

  to this file.  C library headers almost always contain constructs

  that dlc does not understand.  For debugging, you can use printf,

  which is declared for you just below.  It is normally bad practice

  to declare C library functions by hand, but in this case it's less

  trouble than any alternative.



  dlc will consider each call to printf to be a violation of the

  coding style (function calls, after all, are not allowed) so you

  must remove all your debugging printf's again before submitting your

  code or testing it with dlc or the BDD checker.  */

extern int printf(const char *, ...);

/* Edit the functions below.  Good luck!  */

// 2

/*

* implication - given input x and y, which are binary

* (taking  the values 0 or 1), return x -> y in propositional logic -

* 0 for false, 1 for true

*

* Below is a truth table for x -> y where A is the result

*

* |-----------|-----|

* |  x  |  y  |  A  |

* |-----------|-----|

* |  1  |  1  |  1  |

* |-----------|-----|

* |  1  |  0  |  0  |

* |-----------|-----|

* |  0  |  1  |  1  |

* |-----------|-----|

* |  0  |  0  |  1  |

* |-----------|-----|

*

*

*   Example: implication(1L,1L) = 1L

*            implication(1L,0L) = 0L

*   Legal ops: ! ~ ^ |

*   Max ops: 5

*   Rating: 2

*/

long implication(long x, long y) {

    return (!x) | y;
}

/*

* leastBitPos - return a mask that marks the position of the

*               least significant 1 bit. If x == 0, return 0

*   Example: leastBitPos(96L) = 0x20L

*   Legal ops: ! ~ & ^ | + << >>

*   Max ops: 6

*   Rating: 2

*/

long leastBitPos(long x) {

    return x & (~x + 1);
}

/*

* distinctNegation - returns 1 if x != -x.

*     and 0 otherwise

*   Legal ops: ! ~ & ^ | +

*   Max ops: 5

*   Rating: 2

*/

long distinctNegation(long x) {

    return !!(x ^ (~x + 1));
}

/*

* fitsBits - return 1 if x can be represented as an

*  n-bit, two's complement integer.

*   1 <= n <= 64

*   Examples: fitsBits(5,3) = 0L, fitsBits(-4,3) = 1L

*   Legal ops: ! ~ & ^ | + << >>

*   Max ops: 15

*   Rating: 2

*/

long fitsBits(long x, long n) {

    // shuffle to clear the bits

    long shift_val = 64 + (~n + 1);

    return !(((x << shift_val) >> shift_val) ^ x);
}

// 3

/*

* trueFiveEighths - multiplies by 5/8 rounding toward 0,

*  avoiding errors due to overflow

*  Examples:

*    trueFiveEighths(11L) = 6L

*    trueFiveEighths(-9L) = -5L

*    trueFiveEighths(0x3000000000000000L) = 0x1E00000000000000L (no overflow)

*  Legal ops: ! ~ & ^ | + << >>

*  Max ops: 20

*  Rating: 4

*/

long trueFiveEighths(long x) {

    long sign = x >> 63;

    long x_high = x >> 3; // Divide by 8 first to avoid overflow

    long x_low = x & 7; // Remainder of division by 8

    long fiveX_high = (x_high << 2) + x_high; // multiply high part by 5

    long fiveX_low = (x_low << 2) + x_low; // multiply low part by 5

    // Adjust for rounding towards zero

    return fiveX_high + (fiveX_low >> 3) +

           ((((fiveX_low & 7) + (sign & 7)) >> 3) & 1);
}

/*

* addOK - Determine if can compute x+y without overflow

*   Example: addOK(0x8000000000000000L,0x8000000000000000L) = 0L,

*            addOK(0x8000000000000000L,0x7000000000000000L) = 1L,

*   Legal ops: ! ~ & ^ | + << >>

*   Max ops: 20

*   Rating: 3

*/

long addOK(long x, long y) {

    long sign_x = x >> 63;

    long sign_y = y >> 63;

    long sum = x + y;

    long sign_sum = sum >> 63;

    // Overflow occurs if x and y have the same sign and the sum has a different

    // sign If there is no overflow, return 1. Otherwise, return 0.

    return !(~(sign_x ^ sign_y) & (sign_x ^ sign_sum));
}

/*

* isPower2 - returns 1 if x is a power of 2, and 0 otherwise

*   Examples: isPower2(5L) = 0L, isPower2(8L) = 1L, isPower2(0) = 0L

*   Note that no negative number is a power of 2.

*   Legal ops: ! ~ & ^ | + << >>

*   Max ops: 20

*   Rating: 3

*/

long isPower2(long x) {

    long sign = x >> 63;

    long minusOne = x + ~0L;

    return !(sign | (x & minusOne) | !x);
}

/*

* rotateLeft - Rotate x to the left by n

*   Can assume that 0 <= n <= 63

*   Examples:

*      rotateLeft(0x8765432187654321L,4L) = 0x7654321876543218L

*   Legal ops: ~ & ^ | + << >> !

*   Max ops: 25

*   Rating: 3

*/

long rotateLeft(long x, long n) {

    // Move the bits to the left by n

    long leftShift = (x << n);

    // Move the bits to the right by (64 - n) and take the n most significant

    // bits

    long rightShift = (x >> (64 + (~n + 1))) & ((1L << n) + (~1 + 1));

    // Combine the left-shifted and right-shifted values

    long result = leftShift | rightShift;

    return result;
}

// 4

/*

* isPalindrome - Return 1 if bit pattern in x is equal to its mirror image

*   Example: isPalindrome(0x6F0F0123c480F0F6L) = 1L

*   Legal ops: ! ~ & ^ | + << >>

*   Max ops: 70

*   Rating: 4

*/

long isPalindrome(long x) {
    long x_ = x;
    long a_x = 0xFF << 8 | 0xFF;
    long a0 = a_x | (a_x << 16);
    long a1 = a0 ^ (a0 << 16);
    long a2 = a1 ^ (a1 << 8);
    long a3 = a2 ^ (a2 << 4);
    long a4 = a3 ^ (a3 << 2);
    long a5 = a4 ^ (a4 << 1);

    x_ = (x_ << 32) | ((x_ >> 32) & a0);
    x_ = ((x_ & a1) << 16) | ((x_ >> 16) & a1);
    x_ = ((x_ & a2) << 8) | ((x_ >> 8) & a2);
    x_ = ((x_ & a3) << 4) | ((x_ >> 4) & a3);
    x_ = ((x_ & a4) << 2) | ((x_ >> 2) & a4);
    x_ = ((x_ & a5) << 1) | ((x_ >> 1) & a5);

    return !(x ^ x_);
}

/*

* bitParity - returns 1 if x contains an odd number of 0's

*   Examples: bitParity(5L) = 0L, bitParity(7L) = 1L

*   Legal ops: ! ~ & ^ | + << >>

*   Max ops: 22

*   Rating: 4

*/

long bitParity(long x) {

    x ^= (x >> 32);

    x ^= (x >> 16);

    x ^= (x >> 8);

    x ^= (x >> 4);

    x ^= (x >> 2);

    x ^= (x >> 1);

    return x & 1;
}

/*

* absVal - absolute value of x

*   Example: absVal(-1) = 1.

*   You may assume -TMax <= x <= TMax

*   Legal ops: ! ~ & ^ | + << >>

*   Max ops: 10

*   Rating: 4

*/

long absVal(long x) {

    // x or ~(x-1)

    long mask = x >> 63;

    return (x ^ mask) + (~mask + 1);
}