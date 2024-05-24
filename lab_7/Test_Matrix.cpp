#include "pch.h"
#include "CppUnitTest.h"
#include "Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMatrix
{
	TEST_CLASS(TestMatrix)
	{
	public:
        TEST_METHOD(TestFindWord)
        {
            Matrix matrix;
            string result = matrix.findWord(0);
            string expected = "1011010000010110";
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestFindAddressColumn)
        {
            Matrix matrix;
            string result = matrix.findAddressColumn(4);
            string expected = "0100111111010100";
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestSumma)
        {
            Matrix matrix;
            string key = "111";
            string result = matrix.summa(key);
            string expected = "1110111000101000";
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestSetElement)
        {
            Matrix matrix;
            matrix.setElement(0, 0, 0);
            int result = matrix.getElement(0, 0);
            int expected = 0;
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestGetElement)
        {
            Matrix matrix;
            int result = matrix.getElement(0, 0);
            int expected = 1;
            Assert::AreEqual(expected, result);
        }

        TEST_METHOD(TestFindWordPosition)
        {
            Matrix matrix;
            string searchedWord = "0000000000000000";
            int result = matrix.findWordPosition(searchedWord, false);
            int expected = -1; 
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestSetWordInColumn)
        {
            Matrix matrix;
            string word = "1111111111111111";
            matrix.setWordInColumn(word, 0);
            string result = matrix.findWord(0);
            Assert::AreEqual(word, result);
        }
        TEST_METHOD(TestF1)
        {
            Matrix matrix;
            string firstWord = "1111000011110000";
            string secondWord = "1010101010101010";
            string result = matrix.f1(firstWord, secondWord);
            string expected = "1010000010100000";
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestF3)
        {
            Matrix matrix;
            string firstWord = "1111000011110000";
            string result = matrix.f3(firstWord);
            string expected = "1111000011110000";
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestF12)
        {
            Matrix matrix;
            string firstWord = "1111000011110000";
            string result = matrix.f12(firstWord);
            string expected = "0000111100001111";
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestF14)
        {
            Matrix matrix;
            string firstWord = "1111000011110000";
            string secondWord = "1010101010101010";
            string result = matrix.f14(firstWord, secondWord);
            string expected = "0000010100000101";
            Assert::AreEqual(expected, result);
        }
	};
}
