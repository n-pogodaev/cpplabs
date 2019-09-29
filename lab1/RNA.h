#pragma once
#include <cstddef>
#include <unordered_map>

class RNA {
    // friend functions
    friend bool IsComplementary(const RNA &, const RNA &);
    friend bool operator==(const RNA &, const RNA &);
    friend bool operator!=(const RNA &, const RNA &);
    friend RNA operator+(const RNA &, const RNA &);
private:
    // fields
    static constexpr std::size_t allocRate = 2;
    std::size_t rnaLength = 0;
    std::size_t arrLength = 0;
    unsigned char *arr = nullptr;
public:
    enum class Nucleotide: unsigned char {
        A, G, C, T
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
    [[nodiscard]] std::size_t capacity() const { return arrLength; }
    [[nodiscard]] std::size_t length() const { return rnaLength; }
    void trim(std::size_t lastIndex);
    [[nodiscard]] RNA split(std::size_t index);
    [[nodiscard]] std::size_t cardinality(Nucleotide) const;
    [[nodiscard]] NucleotideUnorderedMap cardinality() const;
    // reference class
    class reference {
        friend class RNA;
    private:
        std::size_t index;
        unsigned char *pointer;
        reference(unsigned char *p, std::size_t i): pointer(p), index(i) {}
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
    [[nodiscard]] Nucleotide operator[](std::size_t) const; // tested
    RNA::reference operator[](std::size_t index);
};

bool IsComplementary(const RNA &, const RNA &);
RNA::Nucleotide ComplementaryTo(RNA::Nucleotide);
