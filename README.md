# Two-Sided Prime Counter

This C program efficiently calculates the number of two-sided primes for a given number of digits. It uses the `primesieve` library for high-performance prime generation.

## Background

A **two-sided prime** is a prime number that is both left- and right-truncatable. For example, 373 is a two-sided prime because:

* 373 is prime.
* (1a) Removing the *rightmost* '3' gives 37, which is prime, or
* (1b) Removing the *leftmost* '3' gives 73, which is prime.
* (2a) Removing the *rightmost* '7' from 37 gives 3, which is prime, or
* (2b) Removing the *leftmost* '7' from 73 gives 3, which is prime.


There are 15 two-sided primes. The [complete list](https://en.wikipedia.org/wiki/Truncatable_prime):

    2, 3, 5, 7, 23, 37, 53, 73, 313, 317, 373, 797, 3137, 3797, 739397 (sequence A020994 in the OEIS)

The largest is the 6-digit 739397.

### Left-Truncatable Primes

A **left-truncatable prime** is a non-zero containing prime number that, when its leftmost (MSB) digit is successively removed, results in a sequence of primes. For example, 937 is a left-truncatable prime because:

* 937 is prime.
* Removing the leftmost '9' gives 37, which is prime.
* Removing the leftmost '3' from 37 gives 7, which is prime.

Left-truncatable primes must contain no zero digits. Prime numbers such as 103 are invalid because they contain a zero, which would produce leading zeros (e.g., 03) when the most significant digit is removed, violating the zerofree requirement.

There are 4260 [left-truncatable primes](https://en.wikipedia.org/wiki/Truncatable_prime). Based on the *current* [complete list](https://www.worldofnumbers.com/truncat.htm), the largest is 24 digits: `357686312646216567629137`.

### Right-Truncatable Primes

A **right-truncatable prime** is a prime number that, when its rightmost digit is successively removed, results in a sequence of primes. For example, 739 is a right-truncatable prime because:

* 739 is prime.
* Removing the rightmost '9' gives 73, which is prime.
* Removing the rightmost '3' from 73 gives 7, which is prime.

There are 83 right-truncatable primes. The [complete list](https://en.wikipedia.org/wiki/Truncatable_prime):

    2, 3, 5, 7, 23, 29, 31, 37, 53, 59, 71, 73, 79, 233, 239, 293, 311, 313, 317, 373, 
    379, 593, 599, 719, 733, 739, 797, 2333, 2339, 2393, 2399, 2939, 3119, 3137, 3733, 
    3739, 3793, 3797, 5939, 7193, 7331, 7333, 7393, 23333, 23339, 23399, 23993, 29399, 
    31193, 31379, 37337, 37339, 37397, 59393, 59399, 71933, 73331, 73939, 233993, 
    239933, 293999, 373379, 373393, 593933, 593993, 719333, 739391, 739393, 739397, 
    739399, 2339933, 2399333, 2939999, 3733799, 5939333, 7393913, 7393931, 7393933, 
    23399339, 29399999, 37337999, 59393339, 73939133 (sequence A024770 in the OEIS)

The largest is the 8-digit 73939133. All primes above 5 end with digit 1, 3, 7 or 9, so a right-truncatable prime can only contain those digits after the leading digit.

-----

## Table of Contents

* [Features](#features)
* [Requirements](#requirements)
* [Installation](#installation)
* [Usage](#usage)
* [License](#license)

-----

## Features

* **Efficient Prime Generation**: Leverages the `primesieve` library for rapid generation of prime numbers.
* **Correct Two-Sided Logic**: Implements the standard definition, ensuring all successive truncations (by removing the leftmost or rightmost digit) are prime.
* **Flexible Digit Count**: Calculates two-sided primes for a user-specified number of digits.
* **Error Handling**: Includes basic error handling for memory allocation and invalid input.

-----

## Requirements

To build and run this program, you'll need:

1. **C Compiler**: A C99 compatible compiler (e.g., GCC, Clang).
2. **`primesieve` Library**: The `primesieve` C/C++ library must be installed on your system.
3. **CMake**: Used for building the `primesieve` library and this project.
4. **Homebrew (macOS only)**: For easy installation of `CMake`.

-----

## Installation

You can use the provided `setup.sh` script to automate the installation and compilation process.

### Using the `setup.sh` Script

The `setup.sh` script automates the setup and compilation process for UNIX users.

    chmod +x setup.sh
    ./setup.sh

-----

## Usage

To run the program, execute the compiled binary and provide the desired number of digits as a command-line argument.

    ./count_primes.out <number_of_digits>

**Example:**

To find the number of 8-digit two-sided primes:

    ./count_primes.out 8

Expected output (will list the primes first, then the count):

    ❯ ./count_primes.out 8
    Number of 8-digit two-sided primes: 0 (n = 5096876)
    Number of 7-digit two-sided primes: 0 (n = 586081)
    Number of 6-digit two-sided primes: 1 (n = 68906)
    Number of 5-digit two-sided primes: 0 (n = 8363)
    Number of 4-digit two-sided primes: 2 (n = 1061)
    Number of 3-digit two-sided primes: 4 (n = 143)
    Number of 2-digit two-sided primes: 4 (n = 21)
    Number of 1-digit two-sided primes: 4 (n = 4)

    Total number of two-sided primes up to 8 digits: 15 (n = 5761455)

    Execution time: 308.998 milliseconds
    Execution time: 308998.208 microseconds
    Execution time: 308998208.000 nanoseconds

**Valid range for `<number_of_digits>`:** 1 to 19 to handle left-truncations. Only 83 possible right-trunctable values up to 8-digits long.

-----

## Resources

- Check out this [respository](https://github.com/EbodShojaei/Left-Truncatable-Primes) for calculating *left-truncatable* primes.

- Check out this [respository](https://github.com/EbodShojaei/Right-Truncatable-Primes) for calculating *right-truncatable* primes.

## License

This project is licensed under the MIT License.
