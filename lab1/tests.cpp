#include "gtest/gtest.h"
#include "RNA.h"

TEST(TestCaseRNA, TestConstIndexOperator) {
    const RNA rna1(10, RNA::Nucleotide::A);
    ASSERT_TRUE(rna1[0] == RNA::Nucleotide::A);
    ASSERT_TRUE(rna1[9] == RNA::Nucleotide::A);
    RNA rna2(10, RNA::Nucleotide::A);
    ASSERT_TRUE(rna2[0] == RNA::Nucleotide::A);
    ASSERT_TRUE(rna2[9] == RNA::Nucleotide::A);
    ASSERT_TRUE(rna1[5] == rna2[7]);
}

TEST(TestCaseRNA, TestIndexOperator) {
    RNA rna1(10, RNA::Nucleotide::A);
    RNA rna2(10, RNA::Nucleotide::G);
    std::size_t allocLength1 = rna1.capacity();
    std::size_t allocLength2 = rna2.capacity();
    rna1[5] = RNA::Nucleotide::T;
    ASSERT_TRUE(rna1[5] == RNA::Nucleotide::T);
    ASSERT_TRUE(rna1.length() == 10);
    ASSERT_TRUE(rna1.capacity() == allocLength1);
    rna1[10] = RNA::Nucleotide::A;
    ASSERT_TRUE(rna1.length() == 11);
    ASSERT_TRUE(rna1.capacity() >= allocLength1);
    ASSERT_TRUE(rna1[10] == RNA::Nucleotide::A);
    rna2[11] = RNA::Nucleotide::A;
    ASSERT_TRUE(rna2.length() == 10);
    ASSERT_TRUE(rna2.capacity() == allocLength2);
    rna1[0] = rna2[0];
    ASSERT_TRUE(rna1[0] == RNA::Nucleotide::G);
}

TEST(TestCaseRNA, TestEqOperator) {
    RNA rna1(10, RNA::Nucleotide::A);
    RNA rna2(10, RNA::Nucleotide::A);
    RNA rna3(30, RNA::Nucleotide::A);
    RNA rna4(10, RNA::Nucleotide::C);
    RNA rna5(5, RNA::Nucleotide::G);
    ASSERT_TRUE(rna1 == rna2);
    ASSERT_FALSE(rna1 == rna3);
    ASSERT_FALSE(rna1 == rna4);
    ASSERT_FALSE(rna1 == rna5);
    rna2[2] = RNA::Nucleotide::T;
    ASSERT_FALSE(rna1 == rna2);
    rna1[2] = RNA::Nucleotide::T;
    ASSERT_TRUE(rna1 == rna2);
}

TEST(TestCaseRNA, TestNEqOperator) {
    RNA rna1(10, RNA::Nucleotide::A);
    RNA rna2(10, RNA::Nucleotide::A);
    RNA rna3(30, RNA::Nucleotide::A);
    RNA rna4(10, RNA::Nucleotide::C);
    RNA rna5(5, RNA::Nucleotide::G);
    ASSERT_FALSE(rna1 != rna2);
    ASSERT_TRUE(rna1 != rna3);
    ASSERT_TRUE(rna1 != rna4);
    ASSERT_TRUE(rna1 != rna5);
    rna2[2] = RNA::Nucleotide::T;
    ASSERT_TRUE(rna1 != rna2);
    rna1[2] = RNA::Nucleotide::T;
    ASSERT_FALSE(rna1 != rna2);
}

TEST(TestCaseRNA, TestCopyConstructor) {
    RNA rna1(10, RNA::Nucleotide::A);
    RNA rna2(rna1);
    ASSERT_TRUE(rna1 == rna2);
    rna1[0] = RNA::Nucleotide::G;
    RNA rna3(rna1);
    ASSERT_TRUE(rna2 != rna3);
}

TEST(TestCaseRNA, TestSumOperator) {
    RNA rna1(10, RNA::Nucleotide::A);
    RNA rna2(5, RNA::Nucleotide::C);
    RNA rna3(rna1 + rna2);
    RNA rna4(rna2 + rna1);
    ASSERT_TRUE(rna3.length() == rna1.length() + rna2.length());
    ASSERT_TRUE(rna4.length() == rna1.length() + rna2.length());
    ASSERT_TRUE(rna3 != rna4);

    ASSERT_TRUE(rna3[0] == rna1[0]);
    ASSERT_TRUE(rna3[9] == rna1[9]);
    ASSERT_TRUE(rna3[10] == rna2[0]);

    ASSERT_TRUE(rna4[0] == rna2[0]);
    ASSERT_TRUE(rna4[4] == rna2[4]);
    ASSERT_TRUE(rna4[5] == rna1[0]);
}

TEST(TestCaseRNA, TestIsComplementary) {
    RNA rna1(5, RNA::Nucleotide::A);
    rna1 += RNA(5, RNA::Nucleotide::G);
    RNA rna2(5, ComplementaryTo(RNA::Nucleotide::A));
    rna2 += RNA(5, ComplementaryTo(RNA::Nucleotide::G));
    RNA rna3(5, ComplementaryTo(RNA::Nucleotide::A));
    ASSERT_TRUE(IsComplementary(rna1, rna2));
    ASSERT_FALSE(IsComplementary(rna1, rna3));
    ASSERT_FALSE(IsComplementary(rna1, rna1));
    rna1[3] = RNA::Nucleotide::C;
    rna2[3] = ComplementaryTo(RNA::Nucleotide::C);
    ASSERT_TRUE(IsComplementary(rna1, rna2));
}

TEST(TestCaseRNA, TestAddMethod) {
    RNA rna1(5, RNA::Nucleotide::A);
    rna1.add(RNA::Nucleotide::G).add(RNA::Nucleotide::C);
    ASSERT_TRUE(rna1.length() == 7);
    ASSERT_TRUE(rna1[5] == RNA::Nucleotide::G);
    ASSERT_TRUE(rna1[6] == RNA::Nucleotide::C);
    rna1.add(3, RNA::Nucleotide::T);
    ASSERT_TRUE(rna1.length() == 10);
    ASSERT_TRUE(rna1[7] == RNA::Nucleotide::T);
    ASSERT_TRUE(rna1[rna1.length() - 1] == RNA::Nucleotide::T);
}

TEST(TestCaseRNA, TestNotOperator) {
    RNA rna1(5, RNA::Nucleotide::A);
    rna1 += RNA(5, RNA::Nucleotide::G);
    ASSERT_TRUE(IsComplementary(rna1, !rna1));
    rna1[2] = RNA::Nucleotide::C;
    ASSERT_TRUE(IsComplementary(rna1, !rna1));
}

TEST(TestCaseRNA, TestAssignOperator) {
    RNA rna1(10, RNA::Nucleotide::A);
    rna1[5] = RNA::Nucleotide::C;
    RNA rna2(5, RNA::Nucleotide::A);
    rna2 = rna1;
    ASSERT_TRUE(rna2 == rna1);
    rna1[0] = RNA::Nucleotide::G;
    ASSERT_TRUE(rna2 != rna1);
    rna2 = rna1;
    rna2[0] = RNA::Nucleotide::C;
    ASSERT_TRUE(rna1 != rna2);
}

TEST(TestCaseRNA, TestSumAssignOperator) {
    RNA rna1(10, RNA::Nucleotide::A);
    RNA rna2(5, RNA::Nucleotide::C);
    rna1 += rna2;
    ASSERT_TRUE(rna1.length() == 15);
    ASSERT_TRUE(rna1[9] == RNA::Nucleotide::A);
    ASSERT_TRUE(rna1[10] == RNA::Nucleotide::C);
}

TEST(TestCaseRNA, TestCardinalityMethod) {
    RNA rna1(10, RNA::Nucleotide::A);
    rna1[3] = rna1[5] = RNA::Nucleotide::C;
    rna1[2] = rna1[6] = rna1[9] = RNA::Nucleotide::G;
    ASSERT_TRUE(rna1.cardinality(RNA::Nucleotide::A) == 5);
    ASSERT_TRUE(rna1.cardinality(RNA::Nucleotide::C) == 2);
    ASSERT_TRUE(rna1.cardinality(RNA::Nucleotide::G) == 3);
    ASSERT_TRUE(rna1.cardinality(RNA::Nucleotide::T) == 0);
    auto map = rna1.cardinality();
    EXPECT_TRUE(map.size() == 4);
    ASSERT_TRUE(map[RNA::Nucleotide::A] == 5);
    ASSERT_TRUE(map[RNA::Nucleotide::C] == 2);
    ASSERT_TRUE(map[RNA::Nucleotide::G] == 3);
    ASSERT_TRUE(map[RNA::Nucleotide::T] == 0);
}

TEST(TestCaseRNA, TestSplitMethod) {
    RNA rna1(5, RNA::Nucleotide::A);
    rna1 += RNA(5, RNA::Nucleotide::G);
    RNA rna2(rna1.split(6));
    ASSERT_TRUE(rna1.length() == 6);
    ASSERT_TRUE(rna2.length() == 4);
    ASSERT_TRUE(rna1[4] == RNA::Nucleotide::A);
    ASSERT_TRUE(rna1[5] == RNA::Nucleotide::G);
    ASSERT_TRUE(rna2[0] == RNA::Nucleotide::G);
    ASSERT_TRUE(rna2[3] == RNA::Nucleotide::G);
}

TEST(TestCaseRNA, TestTrimMethod) {
    RNA rna1(1000, RNA::Nucleotide::G);
    RNA rna2(1000, RNA:: Nucleotide::G);
    rna1.trim(10);
    ASSERT_TRUE(rna1.length() == 11);
    ASSERT_TRUE(rna1.capacity() >= rna1.length() / 4);
    ASSERT_TRUE(rna1[0] == RNA::Nucleotide::G);
    ASSERT_TRUE(rna1[10] == RNA::Nucleotide::G);
    EXPECT_TRUE(rna1.capacity() < rna2.capacity());
    std::size_t t = rna1.capacity();
    rna1.trim(9);
    EXPECT_TRUE(rna1.capacity() == t);
}

TEST(TestCaseRNA, TestReallocatingTime) {
    RNA rna1(10, RNA::Nucleotide::A);
    for (int i = 0; i < 10'000'000; ++i) {
        rna1.add(RNA::Nucleotide::G);
    }
}
