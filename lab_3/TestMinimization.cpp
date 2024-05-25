#include "pch.h"
#include "CppUnitTest.h"
#include "Minimization.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMinimization
{
	TEST_CLASS(TestMinimization)
	{
	public:
		
		TEST_METHOD(Test_infixToPostfix_function)
		{
			string expression = "a & b | c > d";
			string expected_postfix = "ab&c|d>";
			Assert::AreEqual(infixToPostfix(expression), expected_postfix);
		}

		TEST_METHOD(Test_complex_expression)
		{
			string expression = "(a | b) & (!c | d)";
			string expected_postfix = "ab|c!d|&";
			Assert::AreEqual(infixToPostfix(expression), expected_postfix);
		}
		TEST_METHOD(Test_infixToPostfix_implication)
		{
			string expression = "a > b";
			string expected_postfix = "ab>";
			Assert::AreEqual(expected_postfix, infixToPostfix(expression));
		}

		TEST_METHOD(Test_infixToPostfix_equivalence)
		{
			string expression = "a ~ b";
			string expected_postfix = "ab~";
			Assert::AreEqual(expected_postfix, infixToPostfix(expression));
		}
		TEST_METHOD(Test_evaluatePostfix_simple)
		{
			string postfixExpression = "ab&c|";
			vector<bool> values = { true, false, true };
			vector<bool> expected_results = { false, true };

			vector<bool> results = evaluatePostfix(postfixExpression, values);
			Assert::IsTrue(equal(expected_results.begin(), expected_results.end(), results.begin()));
		}

		TEST_METHOD(Test_evaluatePostfix_complex)
		{
			string postfixExpression = "ab|c!d|&";
			vector<bool> values = { true, false, false, true };
			vector<bool> expected_results = { true }; 

			vector<bool> results = evaluatePostfix(postfixExpression, values);
			Assert::IsTrue(equal(expected_results.begin(), expected_results.end(), results.begin()));
		}
		TEST_METHOD(Test_evaluatePostfix_equivalence)
		{
			string postfixExpression = "ab~";
			vector<bool> values = { true, false };
			vector<bool> expected_results = { false };

			vector<bool> results = evaluatePostfix(postfixExpression, values);
			Assert::IsTrue(equal(expected_results.begin(), expected_results.end(), results.begin()));
		}

		TEST_METHOD(Test_SKNF_SDNF_update)
		{
			vector<bool> values1 = { true, false, true };
			string sknf = "";
			string sdnf = "";

			sknf = updateSKNF(values1, sknf);
			sdnf = updateSDNF(values1, sdnf);

			Assert::AreEqual(string("(!a|b|!c)&"), sknf);
			Assert::AreEqual(string("(a&!b&c)|"), sdnf);
		}

		TEST_METHOD(Test_MinimizeSDNF_Table)
		{
			string sdnf = "(!a&!b&!c)|(!a&b&!c)|(a&!b&!c)|(a&b&!c)|(a&b&c)";
			string minimized_sdnf = MinimizeSDNF_Table(sdnf);

			Assert::AreEqual(string("(!c) | (a&b)"), minimized_sdnf);
		}

		TEST_METHOD(Test_MinimizeSKNF_Table)
		{
			string sknf = "(a|b|!c)&(a|!b|!c)&(!a|b|!c)";
			string minimized_sknf = MinimizeSKNF_Table(sknf);

			Assert::AreEqual(string("(a|!c) & (b|!c)"), minimized_sknf);
		}

		TEST_METHOD(Test_createKarnaughMap)
		{
			vector<int> sdnfIndices = { 0, 2, 5, 7 };
			vector<vector<bool>> expected_kmap = {
				{ true, false, true, false },
				{ false, true, false, true }
			};

			vector<vector<bool>> kmap = createKarnaughMap(sdnfIndices);

			Assert::IsTrue(equal(expected_kmap.begin(), expected_kmap.end(), kmap.begin()));
		}
	};
}
