#include "gtest/gtest.h"
#include "../RNA.h"

TEST(TestCaseRNA, TestingEqOperator) {
    RNA rna1(10, Nucleotide::A);
    RNA rna2(10, Nucleotide::A);
    RNA rna3(30, Nucleotide::A);
    RNA rna4(5, Nucleotide::G);
    RNA rna5(10, Nucleotide::C);
    EXPECT_TRUE(rna1 == rna2);
    EXPECT_FALSE(rna1 == rna3);
    EXPECT_FALSE(rna1 == rna4);
    EXPECT_FALSE(rna1 == rna5);
};

TEST(TestCaseRNA, TestingNEqOperator) {
    RNA rna1(10, Nucleotide::A);
    RNA rna2(10, Nucleotide::A);
    RNA rna3(30, Nucleotide::A);
    RNA rna4(5, Nucleotide::G);
    RNA rna5(10, Nucleotide::C);
    EXPECT_FALSE(rna1 != rna2);
    EXPECT_TRUE(rna1 != rna3);
    EXPECT_TRUE(rna1 != rna4);
    EXPECT_TRUE(rna1 != rna5);
}
