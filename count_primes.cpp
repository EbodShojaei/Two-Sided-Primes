// Author   : Ebod Shojaei
// Updated  : 02-12-2025

#include <chrono>       // For ns timing via cpp :3
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     // For uint64_t
#include <stddef.h>     // For size_t
#include <vector>
#include <primesieve.h> // For primes

// Utility function to calculate power of 10
unsigned long long power_of_10(int exp)
{
    unsigned long long res = 1;
    for (int i = 0; i < exp; ++i)
    {
        res *= 10;
    }
    return res;
}

// Composite function to calculate total number of two-sided primes
int count_two_sided_primes(const std::vector<unsigned long long> &all_primes_array,
                             std::vector<uint64_t> &primes_per_digit,
                             std::vector<bool> &prime_bitset, int digits)
{
    // Divide number by 0 repeatedly and if remainder 0 then number contains 0
    if (digits < 1 || digits > 19)
    {
        fprintf(stderr, "Error: digits must be between 1 and 19 for unsigned long long.\n");
        return -1;
    }

    primes_per_digit[digits] = 0;

    // Iterate through primes of the specified "digits" length
    int two_sided_count = 0;
    unsigned long long current_digits_start = power_of_10(digits - 1);
    unsigned long long current_digits_end   = power_of_10(digits) - 1;

    for (size_t i = 0; i < all_primes_array.size(); ++i)
    {
        unsigned long long current_prime = all_primes_array[i];

        // Skip primes outside current "digits" length window
        if (current_prime < current_digits_start) continue;
        if (current_prime > current_digits_end) break;

        primes_per_digit[digits]++;

        int is_l_truncatable = 1; // Assume left-truncatable until proven otherwise
        int is_r_truncatable = 1; // Assume right-truncatable until proven otherwise
        long long int l_temp_prime = current_prime;
        long long int r_temp_prime = current_prime;

        long long int current_digits = power_of_10(digits - 1);

        while (current_digits > 0) // Loop until the number becomes 0 (all digits removed)
        {
            int leftmost = l_temp_prime / current_digits;
            // Check if the current truncated number is prime using bitset
            if (l_temp_prime >= prime_bitset.size() || !prime_bitset[l_temp_prime] || leftmost == 0)
            {
                is_l_truncatable = 0; // Not a left-truncatable prime
                prime_bitset[current_prime] = false; // To print out list of two-sided primes
                break;
            } else if (r_temp_prime >= prime_bitset.size() || !prime_bitset[r_temp_prime]) {
                is_r_truncatable = 0; // Not a right-truncatable prime
                prime_bitset[current_prime] = false; // To print out list of two-sided primes
                break;
            }

            l_temp_prime %= current_digits; // Remove the leftmost digit
            r_temp_prime /= 10;             // Remove the rightmost digit
            current_digits /= 10;
        }
        
        if (is_l_truncatable && is_r_truncatable) {
            // printf("%llu\n", current_prime);
            two_sided_count++;
        }
        
    }

    return two_sided_count;
}

// Driver function to run the program
int main(int argc, char *argv[])
{
    // Setup the timer
    auto start_time = std::chrono::high_resolution_clock::now();

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <number_of_digits>\n", argv[0]);
        return 1;
    }
    
    int digits = atoi(argv[1]);
    if (digits < 1 || digits > 19)
    {
        fprintf(stderr, "Error: digits must be between 1 and 19 for unsigned long long.\n");
        return 1;
    }

    // 1. Generate ALL primes up to the max number of digits specified
    unsigned long long MAX_END   = power_of_10(digits) - 1;
    unsigned long long MIN_START = 2;

    size_t all_primes_count;
    unsigned long long *all_primes_array_ptr = (unsigned long long *)primesieve_generate_primes(MIN_START, MAX_END, &all_primes_count, ULONGLONG_PRIMES);
    if (!all_primes_array_ptr)
    {
        fprintf(stderr, "Error generating primes.\n");
        return 1;
    }

    std::vector<unsigned long long> all_primes_array(all_primes_array_ptr, all_primes_array_ptr + all_primes_count);
    primesieve_free(all_primes_array_ptr);

    // 2. Build a bitset for prime membership checks
    std::vector<bool> prime_bitset(MAX_END + 1, false);
    for (size_t i = 0; i < all_primes_array.size(); ++i)
    {
        prime_bitset[all_primes_array[i]] = true;
    }

    std::vector<uint64_t> primes_per_digit(digits + 1, 0);

    // Calculate total number of two-sided primes up to the specified number of digits
    int total_count = 0;
    for (int i = digits; i > 0; i--)
    {
        int count = count_two_sided_primes(all_primes_array, primes_per_digit, prime_bitset, i);
        if (count < 0)
        {
            fprintf(stderr, "Error counting two-sided primes for %d digits.\n", i);
            return 1;
        }
        total_count += count;
        printf("Number of %d-digit two-sided primes: %d (n = %llu)\n", i, count, primes_per_digit[i]);
    }
    printf("\nTotal number of two-sided primes up to %d digits: %d (n = %zu)\n\n", digits, total_count, all_primes_count);

    // Print the execution time
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;
    double time_diff = elapsed_time.count();
    // Print the execution time in ms granularity
    printf("Execution time: %.3f milliseconds\n", time_diff * 1000);
    // Print the execution time in us granularity
    printf("Execution time: %.3f microseconds\n", time_diff * 1000000);
    // Print the execution time in ns granularity
    printf("Execution time: %.3f nanoseconds\n", time_diff * 1000000000);

    // ===========================================================
    // NOTE: uncomment below to print out list of two-sided primes
    // ===========================================================
    // for (int i = 0; i < prime_bitset.size(); ++i) {
    //     if (prime_bitset[i] == 1) printf("%d ", i);
    // }
    // printf("\n");

    return 0;
}
