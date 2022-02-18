#include "Chapter11_Cryptography.h"

#include "RtcFilesystem.h"

#include <filesystem>
#include <format>
#include <iostream>  // cout
#include <vector>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "cryptocpp/cryptlib.h"
#include "cryptocpp/filters.h"  // StringSink
#include "cryptocpp/hex.h"  // HexEncoder
#include "cryptocpp/md5.h"  // MD5
#include "cryptocpp/sha.h"  // SHA1, SHA256

namespace fs = std::filesystem;


template <size_t DigestSize>
std::string encode_hash_as_hex_string(const CryptoPP::byte (&digest)[DigestSize])
{
    CryptoPP::HexEncoder encoder{};
    std::string output{};

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
}

template <typename Hash>
std::string get_hash_as_hex_string(const std::vector<unsigned char>& text)
{
    static CryptoPP::byte digest[Hash::DIGESTSIZE];
    Hash{}.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(text.data()), text.size());
    return encode_hash_as_hex_string(digest);
}


// Computing file hashes
//
// Write a program that, given a path to a file, computes and prints to the console
// the SHA1, SHA256, and MD5 hash values for the content of the file.
void problem_92_main()
{
    const auto input_file_path{ std::filesystem::current_path() / "res" / "fonts" / "calibri.ttf" };

    std::cout << std::format("Calculating SHA1, SHA256 and MD5 for file '{}'\n", input_file_path.string());

    const auto input_file_content{ rtc::filesystem::get_binary_file_content<unsigned char>(input_file_path) };

    std::cout << std::format("\tSHA1: '{}'\n", get_hash_as_hex_string<CryptoPP::SHA1>(input_file_content));
    std::cout << std::format("\tSHA256: '{}'\n", get_hash_as_hex_string<CryptoPP::SHA256>(input_file_content));
    std::cout << std::format("\tMD5: '{}'\n", get_hash_as_hex_string<CryptoPP::Weak::MD5>(input_file_content));

    std::cout << "\n";
}
