#include "include/SHA1.h"

SHA1::SHA1() :digest({ 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 }), transforms(0) {};

void SHA1::update(const std::string& s)
{
	std::istringstream is(s);
	update(is);
}

void SHA1::update(std::istream& is)
{
	while (true) {
		char sbuf[64];
		is.read(sbuf, 64);
		std::streamsize s = is.gcount();
		if (s > 0) {
			update(reinterpret_cast<const uint8_t*>(sbuf), s);
		}
		if (is.eof()) {
			break;
		}
	}
}

std::string SHA1::final()
{
	uint64_t total_bits = transforms * 512 + buffer.size() * 8;
	buffer.push_back(0x80);
	while (buffer.size() < 56) {
		buffer.push_back(0x00);
	}
	for (int i = 0; i < 8; i++) {
		buffer.push_back(static_cast<unsigned char>((total_bits >> ((7 - i) * 8)) & 0xFF));
	}
	transform(buffer.data(), buffer.size());

	std::ostringstream result;
	for (unsigned int i : digest) {
		result << std::hex << std::uppercase;
		result.width(8);
		result.fill('0');
		result << i;
	}

	return result.str();
}

void SHA1::update(const uint8_t* data, size_t len)
{
	buffer.insert(buffer.end(), data, data + len);
	while (buffer.size() >= 64) {
		transform(buffer.data(), buffer.size());
		buffer.erase(buffer.begin(), buffer.begin() + 64);
	}
}

void SHA1::transform(const uint8_t* data, size_t len)
{
	if (len < 64) {
		return;
	}

	uint32_t block[80];
	for (int i = 0; i < 16; i++) {
		block[i] = (data[i * 4 + 0] << 24) |
			(data[i * 4 + 1] << 16) |
			(data[i * 4 + 2] << 8) |
			(data[i * 4 + 3]);
	}

	for (int i = 16; i < 80; i++) {
		block[i] = rotate_left(block[i - 3] ^ block[i - 8] ^ block[i - 14] ^ block[i - 16], 1);
	}

	uint32_t a = digest[0];
	uint32_t b = digest[1];
	uint32_t c = digest[2];
	uint32_t d = digest[3];
	uint32_t e = digest[4];

	for (int i = 0; i < 80; i++) {
		uint32_t f, k;
		if (i < 20) {
			f = (b & c) | ((~b) & d);
			k = 0x5A827999;
		}
		else if (i < 40) {
			f = b ^ c ^ d;
			k = 0x6ED9EBA1;
		}
		else if (i < 60) {
			f = (b & c) | (b & d) | (c & d);
			k = 0x8F1BBCDC;
		}
		else {
			f = b ^ c ^ d;
			k = 0xCA62C1D6;
		}

		uint32_t temp = rotate_left(a, 5) + f + e + k + block[i];
		e = d;
		d = c;
		c = rotate_left(b, 30);
		b = a;
		a = temp;
	}
	digest[0] += a;
	digest[1] += b;
	digest[2] += c;
	digest[3] += d;
	digest[4] += e;
	transforms++;
}

uint32_t SHA1::rotate_left(uint32_t value, size_t count)
{
	return (value << count) | (value >> (32 - count));
}
