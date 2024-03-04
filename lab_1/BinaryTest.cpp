#include "pch.h"
#include "CppUnitTest.h"
#include "../BinaryConverter.h"
#include "../FloatPointConverter.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTest
{
	TEST_CLASS(BinaryTest)
	{
	public:
		
        TEST_METHOD(Check_sum)
        {
            BinaryConverter b1(10);
            BinaryConverter b2(5);
            BinaryConverter sum = b1 + b2;
            sum.print();
            cout << "Decimal representation of the sum: " << sum.toDecimal() << endl;
            Assert::AreEqual(sum.toDecimal(), 15);
        }

        TEST_METHOD(Check_dif)
        {
            BinaryConverter b1(10);
            BinaryConverter b2(-5);
            BinaryConverter dif = b1 - b2;
            Assert::AreEqual(dif.toDecimal(), 15);
        }

        TEST_METHOD(Check_mult)
        {
            BinaryConverter b1(10);
            BinaryConverter b2(-5);
            BinaryConverter mult = b1 * b2;
            Assert::AreEqual(mult.toDecimal(), -50);
        }

        TEST_METHOD(Check_division)
        {
            BinaryConverter b1(-10);
            BinaryConverter b2(5);
            BinaryConverter division = b1 / b2;
            Assert::AreEqual(division.toDecimal(), -2);
        }

        TEST_METHOD(Check_float_sum)
        {
            FloatingPointConverter f1(23.348);
            FloatingPointConverter f2(14.52);
            FloatingPointConverter sum2 = f1 + f2;
            sum2.print();
            cout << "Float representation of the sum: " << sum2.convertToDecimal() << endl;
            float num = 37.868;
            Assert::AreEqual(sum2.convertToDecimal(), num);
        }

        TEST_METHOD(Check_float_sum2)
        {
            FloatingPointConverter f1(1.348);
            FloatingPointConverter f2(14.52);
            FloatingPointConverter sum2 = f1 + f2;
            sum2.print();
            cout << "Float representation of the sum: " << sum2.convertToDecimal() << endl;
            float num = 15.868;
            Assert::AreEqual(sum2.convertToDecimal(), num);
        }
	};
}
