#ifndef LIBWALLY_CORE_ADDRESS_H
#define LIBWALLY_CORE_ADDRESS_H

#include "wally_core.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WALLY_WIF_FLAG_COMPRESSED 0x0   /** Corresponding public key compressed */
#define WALLY_WIF_FLAG_UNCOMPRESSED 0x1 /** Corresponding public key uncompressed */

#define WALLY_CA_PREFIX_LIQUID 0x0c /** Liquid v1 confidential address prefix */

/**
 * Create a segwit native address from a v0 witness program.
 *
 * :param bytes: Witness program bytes, including the version and data push opcode.
 * :param bytes_len: Length of ``bytes`` in bytes. Must be 20 or 32 if script_version is 0.
 * :param addr_family: Address family to generate, e.g. "bc" or "tb".
 * :param flags: For future use. Must be 0.
 * :param output: Destination for the resulting segwit native address string.
 */
WALLY_CORE_API int wally_addr_segwit_from_bytes(
    const unsigned char *bytes,
    size_t bytes_len,
    const char *addr_family,
    uint32_t flags,
    char **output);

/**
 * Get a witness program from a segwit native address.
 *
 * :param addr: Address to fetch the witness program from.
 * :param addr_family: Address family to generate, e.g. "bc" or "tb".
 * :param flags: For future use. Must be 0.
 * :param bytes_out: Destination for the resulting witness program bytes.
 * :param len: Length of ``bytes_out`` in bytes.
 * :param written: Destination for the number of bytes written to ``bytes_out``.
 */
WALLY_CORE_API int wally_addr_segwit_to_bytes(
    const char *addr,
    const char *addr_family,
    uint32_t flags,
    unsigned char *bytes_out,
    size_t len,
    size_t *written);

/**
 * Convert a private key to Wallet Import Format.
 *
 * :param priv_key: Private key bytes.
 * :param priv_key_len: The length of ``priv_key`` in bytes. Must be ``EC_PRIVATE_KEY_LEN``.
 * :param prefix: Prefix byte to use, e.g. 0x80, 0xef.
 * :param flags: Pass ``WALLY_WIF_FLAG_COMPRESSED`` if the corresponding pubkey is compressed,
 *|    otherwise ``WALLY_WIF_FLAG_UNCOMPRESSED``.
 * :param output: Destination for the resulting Wallet Import Format string.
 */
WALLY_CORE_API int wally_wif_from_bytes(
    const unsigned char *priv_key,
    size_t priv_key_len,
    uint32_t prefix,
    uint32_t flags,
    char **output);

/**
 * Convert a Wallet Import Format string to a private key.
 *
 * :param wif: Private key in Wallet Import Format.
 * :param prefix: Prefix byte to use, e.g. 0x80, 0xef.
 * :param flags: Pass ``WALLY_WIF_FLAG_COMPRESSED`` if the corresponding pubkey is compressed,
 *|    otherwise ``WALLY_WIF_FLAG_UNCOMPRESSED``.
 * :param bytes_out: Destination for the private key.
 * :param len: The length of ``bytes_out`` in bytes. Must be ``EC_PRIVATE_KEY_LEN``.
 */
WALLY_CORE_API int wally_wif_to_bytes(
    const char *wif,
    uint32_t prefix,
    uint32_t flags,
    unsigned char *bytes_out,
    size_t len);

/**
 * Determine if a private key in Wallet Import Format corresponds to an uncompressed public key.
 *
 * :param wif: Private key in Wallet Import Format to check.
 * :param written: 1 if the corresponding public key is uncompressed, 0 if compressed.
 */
WALLY_CORE_API int wally_wif_is_uncompressed(
    const char *wif,
    size_t *written);

/**
 * Create a public key corresponding to a private key in Wallet Import Format.
 *
 * :param wif: Private key in Wallet Import Format.
 * :param prefix: Prefix byte to use, e.g. 0x80, 0xef.
 * :param bytes_out: Destination for the resulting public key.
 * :param len: The length of ``bytes_out``.
 * :param written: Destination for the number of bytes written to ``bytes_out``.
 */
WALLY_CORE_API int wally_wif_to_public_key(
    const char *wif,
    uint32_t prefix,
    unsigned char *bytes_out,
    size_t len,
    size_t *written);

/**
 * Create a P2PKH address corresponding to a private key in Wallet Import Format.
 *
 * :param wif: Private key in Wallet Import Format.
 * :param prefix: Prefix byte to use, e.g. 0x80, 0xef.
 * :param version: Version byte to generate address, e.g. 0x00, 0x6f.
 * :param output: Destination for the resulting address string.
 */
WALLY_CORE_API int wally_wif_to_address(
    const char *wif,
    uint32_t prefix,
    uint32_t version,
    char **output);

/**
 * Extract the address from a confidential address.
 *
 * :param address: The base58 encoded confidential address to extract the address from.
 * :param prefix: The confidential address prefix byte, e.g. WALLY_CA_PREFIX_LIQUID.
 * :param output: Destination for the resulting address string.
 */
WALLY_CORE_API int wally_confidential_addr_to_addr(
    const char *address,
    uint32_t prefix,
    char **output);

/**
 * Extract the blinding public key from a confidential address.
 *
 * :param address: The base58 encoded confidential address to extract the public key from.
 * :param prefix: The confidential address prefix byte, e.g. WALLY_CA_PREFIX_LIQUID.
 * :param bytes_out: Destination for the public key.
 * :param len: The length of ``bytes_out`` in bytes. Must be ``EC_PUBLIC_KEY_LEN``.
 */
WALLY_CORE_API int wally_confidential_addr_to_ec_public_key(
    const char *address,
    uint32_t prefix,
    unsigned char *bytes_out,
    size_t len);

/**
 * Create a confidential address from an address and blinding public key.
 *
 * :param address: The base58 encoded address to make confidential.
 * :param prefix: The confidential address prefix byte, e.g. WALLY_CA_PREFIX_LIQUID.
 * :param pub_key: The blinding public key to associate with ``address``.
 * :param pub_key_len: The length of ``pub_key`` in bytes. Must be ``EC_PUBLIC_KEY_LEN``.
 * :param output: Destination for the resulting address string.
 */
WALLY_CORE_API int wally_confidential_addr_from_addr(
    const char *address,
    uint32_t prefix,
    const unsigned char *pub_key,
    size_t pub_key_len,
    char **output);

#ifdef __cplusplus
}
#endif

#endif /* LIBWALLY_CORE_ADDRESS_H */
