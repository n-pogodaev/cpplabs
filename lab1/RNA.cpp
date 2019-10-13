#include <iostream>
#include <algorithm>
#include "RNA.h"
// utility functions

unsigned char NuclToChar(RNA::Nucleotide value) {
    switch (value) {
        case RNA::Nucleotide::A:
            return 0u;
        case RNA::Nucleotide::G:
            return 1u;
        case RNA::Nucleotide::C:
            return 2u;
        case RNA::Nucleotide::T:
            return 3u;
        default:
            return 0u;
    }
}

RNA::Nucleotide CharToNucl(unsigned char value) {
    switch (value)
    {
        case 0u:
            return RNA::Nucleotide::A;
        case 1u:
            return RNA::Nucleotide::G;
        case 2u:
            return RNA::Nucleotide::C;
        case 3u:
            return RNA::Nucleotide::T;
        default:
            std::cerr << "function charToNucl() error: wrong value" << std::endl;
            return RNA::Nucleotide::A;
    }
}

unsigned char GetCharFilledWithNucl(RNA::Nucleotide value) {
    switch (value)
    {
        case RNA::Nucleotide::A:
            return 0u; //0000_0000
        case RNA::Nucleotide::G:
            return 85u; //0101_0101
        case RNA::Nucleotide::C:
            return 170u; //1010_1010
        case RNA::Nucleotide::T:
            return 255u; //1111_1111
        default:
            return 0u;
    }
}

//constructors
RNA::~RNA() {
    delete[] arr;
}

RNA::RNA(std::size_t nuclCount, Nucleotide value): rnaLength(nuclCount), arrLength(nuclCount / 4) {
    if (rnaLength % 4 != 0) {
        ++arrLength;
    }
    arr = new unsigned char[arrLength];
    unsigned char initValue = GetCharFilledWithNucl(value);
    for (std::size_t i = 0; i < arrLength; ++i) {
        arr[i] = initValue;
    }
}

RNA::RNA(const RNA &rna): rnaLength(rna.rnaLength), arrLength(rna.arrLength) {
    arr = new unsigned char[arrLength];
    for (std::size_t i = 0; i < arrLength; ++i) {
        arr[i] = rna.arr[i];
    }
}

// class methods

RNA &RNA::add(Nucleotide value) {
    (*this)[rnaLength] = value;
    return *this;
}

RNA &RNA::add(std::size_t nuclCount, Nucleotide value) {
    for (std::size_t i = 0; i < nuclCount; ++i) {
        add(value);
    }
    return *this;
}

void RNA::trim(std::size_t lastIndex) {
    std::size_t lastByteNum = lastIndex / 4;
    if (lastByteNum >= arrLength - 1) {
        return;
    }
    if (lastByteNum <= arrLength / allocRate) {
        auto *t = new unsigned char[lastByteNum + 1];
        std::copy(arr, arr + lastByteNum + 1, t);
        delete[] arr;
        arr = t;
        arrLength = lastByteNum + 1;
    }
    if (lastIndex < rnaLength) {
        rnaLength = lastIndex + 1;
    }
}

RNA RNA::split(std::size_t index) {
    RNA secondRNA(rnaLength - index, Nucleotide::A);
    for (size_t i = 0; i < secondRNA.rnaLength; ++i) {
        secondRNA[i] = (*this)[index + i];
    }
    trim(index - 1);
    return secondRNA;
}

std::size_t RNA::cardinality(Nucleotide value) const {
    size_t result = 0;
    for (std::size_t i = 0; i < rnaLength; ++i) {
        if (operator[](i) == value) {
            ++result;
        }
    }
    return result;
}

RNA::NucleotideUnorderedMap RNA::cardinality() const {
    NucleotideUnorderedMap result;
    result[Nucleotide::A] = cardinality(Nucleotide::A);
    result[Nucleotide::G] = cardinality(Nucleotide::G);
    result[Nucleotide::C] = cardinality(Nucleotide::C);
    result[Nucleotide::T] = cardinality(Nucleotide::T);
    return result;
}

// operators

bool operator==(const RNA &firstRNA, const RNA &secondRNA) {
    if (firstRNA.rnaLength != secondRNA.rnaLength) { return false; }
    std::size_t usedArrLength = firstRNA.rnaLength / 4;
    for (std::size_t i = 0; i < usedArrLength; ++i) {
        if (firstRNA.arr[i] != secondRNA.arr[i]) {
            return false;
        }
    }
    if (firstRNA.rnaLength % 4 != 0) {
        unsigned int lastByteNuclCount = firstRNA.rnaLength % 4;
        for (unsigned int i = 0; i < lastByteNuclCount; ++i) {
            if (firstRNA[firstRNA.rnaLength - i - 1] != secondRNA[secondRNA.rnaLength - i - 1]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const RNA &firstRNA, const RNA &secondRNA) {
    return !(firstRNA == secondRNA);
}

RNA RNA::operator!() const {
    RNA complemRNA(*this);
    for (std::size_t i = 0; i < complemRNA.arrLength; ++i) {
        complemRNA.arr[i] = static_cast<unsigned char>(~complemRNA.arr[i]);
    }
    return complemRNA;
}

RNA &RNA::operator+=(const RNA &rna) {
    for (std::size_t i = 0; i < rna.rnaLength; ++i) {
        add(rna[i]);
    }
    return *this;
}

RNA operator+(const RNA &firstRNA, const RNA &secondRNA) {
    RNA newRNA(firstRNA);
    newRNA += secondRNA;
    return newRNA;
}

RNA &RNA::operator=(const RNA &rna) {
    if (this == &rna) {
        return *this;
    }
    std::size_t rnaUsedArrLength = rna.rnaLength / 4;
    if (rna.rnaLength % 4 != 0) {
        ++rnaUsedArrLength;
    }
    if (arrLength < rnaUsedArrLength) {
        delete[] arr;
        arr = new unsigned char[rnaUsedArrLength * allocRate];
        arrLength = rnaUsedArrLength * allocRate;
    }
    rnaLength = rna.rnaLength;
    for (std::size_t i = 0; i < rnaUsedArrLength; ++i) {
        arr[i] = rna.arr[i];
    }
    return *this;
}

RNA::Nucleotide RNA::operator[](std::size_t index) const {
    if (index >= rnaLength) {
        std::cerr << "const operator[] error: wrong index" << std::endl;
        throw;
    }
    unsigned int shift = (3 - index % 4) * 2;
    unsigned char nuclCharValue = (0x03u << shift & arr[index / 4]) >> shift;
    return CharToNucl(nuclCharValue);
}

RNA::reference RNA::operator[](std::size_t index) {
    if (index > rnaLength) {
        std::cerr << "operator[] error: wrong index" << std::endl;
        //throw;
    }
    else {
        std::size_t byteNum = index / 4;
        if (arrLength <= byteNum) {
            // memory reallocating
            auto *t = new unsigned char[arrLength];
            std::copy(arr, arr + arrLength, t);
            delete[] arr;
            std::size_t newArrLength = arrLength * allocRate;
            arr = new unsigned char[newArrLength];
            std::copy(t, t + arrLength, arr);
            arrLength = newArrLength;
        }
    }
    return reference(*this, index);
}

RNA::reference &RNA::reference::operator=(Nucleotide value) {
    std::size_t index = byteNum * 4 + nuclNumInByte;
    if (index <= rna.rnaLength) {
        if ((NuclToChar(value) & 0x01u) == 0u) {
            // 0000_00*0
            rna.arr[byteNum] &= static_cast<unsigned char>(~(0x01u << (3 - nuclNumInByte) * 2));
        } else {
            // 0000_00*1
            rna.arr[byteNum] |= static_cast<unsigned char>(0x01u << (3 - nuclNumInByte) * 2);
        }
        if ((NuclToChar(value) & 0x02u) == 0u) {
            // 0000_000*
            rna.arr[byteNum] &= static_cast<unsigned char>(~(0x02u << (3 - nuclNumInByte) * 2));
        } else {
            // 0000_001*
            rna.arr[byteNum] |= static_cast <unsigned char>(0x02u << (3 - nuclNumInByte) * 2);
        }
        if (index == rna.rnaLength) {
            rna.rnaLength = index + 1;
        }
    }
    return *this;
}

RNA::reference &RNA::reference::operator=(const RNA::reference &ref) {
    unsigned int shift = (3 - ref.nuclNumInByte) * 2;
    *this = CharToNucl((0x03u << shift & ref.rna.arr[ref.byteNum]) >> shift);
    return *this;
}

RNA::reference::operator RNA::Nucleotide() const {
    if (byteNum * 4 + nuclNumInByte < rna.rnaLength) {
        unsigned int shift = (3 - nuclNumInByte) * 2;
        return CharToNucl((0x03u << shift & rna.arr[byteNum]) >> shift);
    }
    else return RNA::Nucleotide::A;
}

std::ostream &operator <<(std::ostream &out, const RNA &rna) {
    for (std::size_t i = 0; i < rna.rnaLength; ++i) {
        RNA::Nucleotide next = rna[i];
        switch(next) {
            case RNA::Nucleotide::A:
                out << "A ";
                break;
            case RNA::Nucleotide::C:
                out << "C ";
                break;
            case RNA::Nucleotide::G:
                out << "G ";
                break;
            case RNA::Nucleotide::T:
                out << "T ";
                break;
        }
    }
    return out;
}

// interface functions
RNA::Nucleotide ComplementaryTo(RNA::Nucleotide nucl) {
    switch (nucl) {
        case RNA::Nucleotide::A:
            return RNA::Nucleotide::T;
        case RNA::Nucleotide::G:
            return RNA::Nucleotide::C;
        case RNA::Nucleotide::C:
            return RNA::Nucleotide::G;
        case RNA::Nucleotide::T:
            return RNA::Nucleotide::A;
        default:
            return RNA::Nucleotide::A;
    }
}

bool IsComplementary(const RNA &firstRNA, const RNA &secondRNA) {
    if (firstRNA.rnaLength != secondRNA.rnaLength) { return false; }
    std::size_t usedArrLength = firstRNA.rnaLength / 4;
    for (std::size_t i = 0; i < usedArrLength; ++i) {
        if (firstRNA.arr[i] != static_cast<unsigned char>(~secondRNA.arr[i])) {
            return false;
        }
    }

    unsigned int lastByteNuclCount = firstRNA.rnaLength % 4;
    if (lastByteNuclCount != 0) {
        for (unsigned int i = 0; i < lastByteNuclCount; ++i) {
            if (firstRNA[firstRNA.rnaLength - i - 1] != ComplementaryTo(secondRNA[secondRNA.rnaLength - i - 1])) {
                return false;
            }
        }
    }
    return true;
}
