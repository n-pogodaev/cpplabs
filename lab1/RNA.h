#pragma once
#include <cstddef>

enum class Nucleotide {
	A, G, C, T
};

class RNA {
	// interface functions
	friend bool isComplementary(const RNA &, const RNA &);
private:
	// fields
	static constexpr std::size_t allocRate = 2;
	std::size_t rnaLength = 0;
	std::size_t arrLength = 0;
	unsigned char *arr = nullptr;
public:
	// constructors
	RNA() = default;
	RNA(std::size_t nuclCount, Nucleotide) {}
	RNA(const RNA &) {}
	// destructor
	~RNA() {}
	// methods
	RNA &add(Nucleotide);
	RNA &add(std::size_t nuclCount, Nucleotide);
	Nucleotide get(std::size_t) const;
	RNA &set(std::size_t, Nucleotide);
	std::size_t capacity() const { return arrLength * 4 - rnaLength; }
	std::size_t length() const { return rnaLength; }
	void trim(std::size_t lastIndex);
	// split(std::size_t index);
	// operators
	bool operator==(const RNA &) const;
	bool operator!=(const RNA &) const;
	RNA operator!() const;
	RNA operator+(const RNA &) const;
	RNA &operator=(const RNA &);
	RNA &operator+=(const RNA &);
};

bool isComplementary(const RNA &, const RNA &);
Nucleotide ComplementaryTo(Nucleotide nucl);
