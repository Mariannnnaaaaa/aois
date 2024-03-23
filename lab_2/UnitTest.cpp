#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2______real.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(Test_infixToPostfix_function)
		{
			string expression = "a & b | c";
			string expected_postfix = "ab&c|";
			Assert::AreEqual(infixToPostfix(expression), expected_postfix);
		}

		TEST_METHOD(Test_complex_expression)
		{
			string expression = "(a | b) & (!c | d)";
			string expected_postfix = "ab|c!d|&";
			Assert::AreEqual(infixToPostfix(expression), expected_postfix);
		}

		TEST_METHOD(Test_binary_result)
		{
			string expression = "(a | b) & !c";
			int expected_result = 42;

			set<char> variables;
			for (char c : expression) {
				if (isalpha(c)) {
					variables.insert(c);
				}
			}
			int actual_result = printTruthTable(variables.size(), expression);
			Assert::AreEqual(actual_result, expected_result);
		}
	};
}
