/*
 * File: SHA256.inc
 * Author: 1therealcloud
 * Last Update: 2026-05-29
 * Description: SHA-256 string hashing plugin for SA-MP.
 */
#if defined _sha256_included
    #endinput
#endif
#define _sha256_included

/*
 * Crypto_SHA256
 *
 * Hashes a string using SHA-256.
 *
 * @param input[]    The input string to hash.
 * @param output[]   The buffer to store the hex-encoded result.
 * @param len        The size of the output buffer. (Must be at least 65 bytes: 64 characters + \0).
 *
 * @return           1 on success, 0 on failure.
 */
native Crypto_SHA256(const input[], output[], len);
