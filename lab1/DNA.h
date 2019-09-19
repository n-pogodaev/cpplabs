#pragma once
#include "RNA.h"

class DNA {
private:
	// fields
	RNA firstRNA;
	RNA secondRNA;
public:
	// constructors
	DNA() = default;
	DNA(const RNA &rna1, const RNA &rna2) : firstRNA(rna1), secondRNA(rna2) {}
	DNA(const DNA &dna) : firstRNA(dna.firstRNA), secondRNA(dna.secondRNA) {}
	// destructor
	~DNA() = default;
};
