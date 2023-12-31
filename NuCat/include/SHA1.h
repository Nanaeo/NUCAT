#include <array>
#include <vector>
#include <string>
#include <sstream>

class SHA1 {
public:
	SHA1();
	void update(const std::string& s);
	void update(std::istream& is);
	std::string final();

private:
	void update(const uint8_t* data, size_t len);
	void transform(const uint8_t* data, size_t len);
	static uint32_t rotate_left(uint32_t value, size_t count);

	std::array<uint32_t, 5> digest;
	std::vector<uint8_t> buffer;
	uint64_t transforms;
};
