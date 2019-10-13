#pragma once
#include <cstddef>
#include <unordered_map>
#include <iostream>

class RNA {
    // friend functions
    friend bool IsComplementary(const RNA &, const RNA &);
    friend bool operator==(const RNA &, const RNA &);
    friend bool operator!=(const RNA &, const RNA &);
    friend RNA operator+(const RNA &, const RNA &);
    friend std::ostream &operator<<(std::ostream &, const RNA &);
private:
    // fields
    static constexpr std::size_t allocRate = 2;
    std::size_t rnaLength = 0;
    std::size_t arrLength = 0;
    unsigned char *arr = nullptr;
public:
    enum class Nucleotide: unsigned char {
        A = 0, G, C, T
    };
    using NucleotideUnorderedMap = std::unordered_map<Nucleotide, std::size_t>;
    // constructors
    RNA() = default;
    RNA(std::size_t nuclCount, Nucleotide);
    RNA(const RNA &);
    // destructor
    ~RNA();
    // methods
    RNA &add(Nucleotide);
    RNA &add(std::size_t nuclCount, Nucleotide);
    std::size_t capacity() const { return arrLength; }
    std::size_t length() const { return rnaLength; }
    void trim(std::size_t lastIndex);
    RNA split(std::size_t index);
    std::size_t cardinality(Nucleotide) const;
    NucleotideUnorderedMap cardinality() const;
    // reference class
    class reference {
        friend class RNA;
    private:
        std::size_t byteNum;
        std::size_t nuclNumInByte;
        RNA &rna;
        reference(RNA &p, std::size_t i): rna(p), byteNum(i / 4), nuclNumInByte(i % 4) {}
    public:
        ~reference() = default;
        reference &operator=(Nucleotide);
        reference &operator=(const reference &);
        operator RNA::Nucleotide() const;
    };
    // operators
    RNA operator!() const;
    RNA &operator=(const RNA &);
    RNA &operator+=(const RNA &);
    Nucleotide operator[](std::size_t) const;
    RNA::reference operator[](std::size_t index);
};

bool IsComplementary(const RNA &, const RNA &);
RNA::Nucleotide ComplementaryTo(RNA::Nucleotide);
