#include "RNA.h"
#include <iostream>
// utility functions

void CopyCharArray(unsigned char *firstArr, const unsigned char *secondArr, std::size_t arrLength) {
    for (decltype(arrLength) i = 0; i < arrLength; ++i) {
        firstArr[i] = secondArr[i];
    }
}

unsigned char NuclToChar(Nucleotide nucl) {
    switch (nucl) {
        case Nucleotide::A:
            return 0u;
        case Nucleotide::G:
            return 1u;
        case Nucleotide::C:
            return 2u;
        case Nucleotide::T:
            return 3u;
        default:
            return 0u;
    }
}

Nucleotide CharToNucl(unsigned char val) {
    switch (val)
    {
        case 0u:
            return Nucleotide::A;
        case 1u:
            return Nucleotide::C;
        case 2u:
            return Nucleotide::G;
        case 3u:
            return Nucleotide::T;
        default:
            std::cerr << "function charToNucl() error: wrong value" << std::endl;
            return Nucleotide::A;
    }
}

unsigned char GetCharFilledWithNucl(Nucleotide nucl) {
    switch (nucl)
    {
        case Nucleotide::A:
            return 0u; //0000_0000
        case Nucleotide::G:
            return 85u; //0101_0101
        case Nucleotide::C:
            return 170u; //1010_1010
        case Nucleotide::T:
            return 255u; //1111_1111
        default:
            return 0u;
    }
}

//constructors
RNA::~RNA() {
    delete[] arr;
}

RNA::RNA(std::size_t nuclCount, Nucleotide nucl): rnaLength(nuclCount), arrLength(nuclCount / 4) {
    if (rnaLength % 4 != 0) {
        ++arrLength;
    }
    arr = new unsigned char[arrLength];
    unsigned char initValue = GetCharFilledWithNucl(nucl);
    for (std::size_t i = 0; i < arrLength; ++i) {
        arr[i] = initValue;
    }
}

RNA::RNA(const RNA &rna): rnaLength(rna.rnaLength), arrLength(rna.rnaLength / 4) {
    if (rnaLength % 4 != 0) {
        ++arrLength;
    }
    arr = new unsigned char[arrLength];
    for (std::size_t i = 0; i < arrLength; ++i) {
        arr[i] = rna.arr[i];
    }
}

// class methods

RNA &RNA::add(Nucleotide nucl) {
    set(rnaLength, nucl);
    return *this;
}

RNA &RNA::add(std::size_t nuclCount, Nucleotide nucl) {
    for (std::size_t i = 0; i < nuclCount; ++i) {
        add(nucl);
    }
    return *this;
}

Nucleotide RNA::get(std::size_t index) const {
    if (index >= rnaLength) {
        std::cerr << "member function RNA::get() error: wrong index" << std::endl;
        return Nucleotide::A;
    }
    std::size_t byteNum = index / 4;
    unsigned int shift = (3 - index % 4) * 2;
    unsigned char nuclCharValue = (0x03u << shift & arr[byteNum]) >> shift;
    return CharToNucl(nuclCharValue);
}

RNA &RNA::set(std::size_t index, Nucleotide nucl) {
    std::size_t byteNum = index / 4;
    unsigned int nuclNumInByte = index % 4;
    if (arrLength < byteNum + 1) {
        std::size_t usedArrLength = rnaLength / 4;
        if (index % 4 != 0) ++usedArrLength;
        auto *t = new unsigned char[usedArrLength];
        CopyCharArray(t, arr, usedArrLength);
        delete[] arr;
        std::size_t newArrLength = (byteNum + 1) * allocRate;
        arr = new unsigned char[newArrLength];
        arrLength = newArrLength;
        CopyCharArray(arr, t, usedArrLength);
        rnaLength = index + 1;
    }
    if ((NuclToChar(nucl) & 0x01u) == 0u) {
        arr[byteNum] &= static_cast<unsigned char>(~(0x01u << (3 - nuclNumInByte) * 2));
    }
    else {
        arr[byteNum] |= static_cast<unsigned char>(0x01u << (3 - nuclNumInByte) * 2);
    }
    if ((NuclToChar(nucl) & 0x03u) == 0u) {
        arr[byteNum] &= static_cast<unsigned char>(~(0x03u << (3 - nuclNumInByte) * 2));
    }
    else {
        arr[byteNum] |= static_cast <unsigned char>(0x03u << (3 - nuclNumInByte) * 2);
    }
    if (rnaLength < index + 1) {
        rnaLength = index + 1;
    }
    return *this;
}

void RNA::trim(std::size_t lastIndex) {
    std::size_t lastByteNum = lastIndex / 4;
    if (lastByteNum >= arrLength) {
        return;
    }
    if (lastIndex < rnaLength) {
        rnaLength = lastIndex + 1;
    }
    delete[](arr + lastByteNum + 1);
    arrLength = lastByteNum + 1;
}

void RNA::split(std::size_t index) {

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
            if (firstRNA.get(firstRNA.rnaLength - i - 1) != secondRNA.get(secondRNA.rnaLength - i - 1)) {
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
    for (std::size_t i = 0; i < arrLength; ++i) {
        complemRNA.arr[i] = ~complemRNA.arr[i];
    }
    return complemRNA;
}

RNA &RNA::operator+=(const RNA &rna) {
    for (std::size_t i = 0; i < rna.rnaLength; ++i) {
        add(rna.get(i));
    }
    return *this;
}

RNA operator+(const RNA &firstRNA, const RNA &secondRNA) {
    RNA newRNA(firstRNA);
    newRNA += secondRNA;
    return newRNA;
}

RNA &RNA::operator=(const RNA &rna) {
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

// interface functions
Nucleotide ComplementaryTo(Nucleotide nucl) {
    switch (nucl) {
        case Nucleotide::A:
            return Nucleotide::T;
        case Nucleotide::G:
            return Nucleotide::C;
        case Nucleotide::C:
            return Nucleotide::G;
        case Nucleotide::T:
            return Nucleotide::A;
        default:
            return Nucleotide::A;
    }
}

bool IsComplementary(const RNA &firstRNA, const RNA &secondRNA) {
    if (firstRNA.rnaLength != secondRNA.rnaLength) { return false; }
    std::size_t usedArrLength = firstRNA.rnaLength / 4;
    for (std::size_t i = 0; i < usedArrLength; ++i) {
        if (firstRNA.arr[i] != ~secondRNA.arr[i]) {
            return false;
        }
    }
    unsigned int lastByteNuclCount = firstRNA.rnaLength % 4;
    if (lastByteNuclCount != 0) {
        for (unsigned int i = 0; i < lastByteNuclCount; ++i) {
            if (firstRNA.get(firstRNA.rnaLength - i - 1) != ComplementaryTo(secondRNA.get(secondRNA.rnaLength - i - 1))) {
                return false;
            }
        }
    }
    return true;
}
