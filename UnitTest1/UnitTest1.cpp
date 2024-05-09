#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_12.9.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		

		TEST_METHOD(TestSumOfElements)
		{
			BinaryTree tree;
			int elements[] = { 5, 3, 8, 2, 4, 7, 9 }; // Приклад елементів

			tree.create(elements, sizeof(elements) / sizeof(elements[0]));

			Assert::AreEqual(38, tree.sumOfElements()); // Перевіряємо, чи сума всіх елементів обчислюється правильно
		}
	};
}
