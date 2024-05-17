#include "pch.h"
#include "CppUnitTest.h"
#include "MedicalDictionary.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestHashTable
{
	TEST_CLASS(TestHashTable)
	{
	public:
        TEST_METHOD(Check_searching_multiple_definitions)
        {
            MedicalDictionary medicalDict;
            medicalDict.addTerm("Jaundice", "A medical condition with yellowing of the skin or whites of the eyes, arising from excess of the pigment bilirubin.");
            medicalDict.addTerm("Jaundice", "Persistent problems falling and staying asleep.");
            string expectedResult = "Definitions for 'Jaundice':\n - A medical condition with yellowing of the skin or whites of the eyes, arising from excess of the pigment bilirubin.\n - Persistent problems falling and staying asleep.\n";
            string result = medicalDict.searchTerm("Jaundice");
            Assert::AreEqual(expectedResult, result);
        }
        TEST_METHOD(Check_searching_non_existing_term)
        {
            MedicalDictionary medicalDict;
            medicalDict.addTerm("Anemia", "A condition in which there is a deficiency of red cells or of hemoglobin in the blood.");
            string expectedResult = "The term is not found in the dictionary.";
            string result = medicalDict.searchTerm("Fever");
            Assert::AreEqual(expectedResult, result);
        }
        TEST_METHOD(Check_deleting_existing_term)
        {
            MedicalDictionary medicalDict;
            medicalDict.addTerm("Anemia", "A condition in which there is a deficiency of red cells or of hemoglobin in the blood.");
            string expectedResult = "The term has been successfully deleted.";
            string result = medicalDict.deleteTerm("Anemia");
            Assert::AreEqual(expectedResult, result);
            string searchResult = medicalDict.searchTerm("Anemia");
            Assert::AreEqual(string("The term is not found in the dictionary."), searchResult);
        }
        TEST_METHOD(Check_deleting_non_existing_term)
        {
            MedicalDictionary medicalDict;
            string expectedResult = "The term is not found in the dictionary.";
            string result = medicalDict.deleteTerm("Fever");
            Assert::AreEqual(expectedResult, result);
        }
        TEST_METHOD(Check_capacity_getter_and_setter)
        {
            MedicalDictionary medicalDict;
            int initialCapacity = medicalDict.getCapacity();
            Assert::AreEqual(20, initialCapacity);

            medicalDict.setCapacity(30);
            int newCapacity = medicalDict.getCapacity();
            Assert::AreEqual(30, newCapacity);
        }
	};
}
