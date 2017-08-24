#pragma once

#include "UnitTestFramework.h"

TEST_CASE("Date", Date_ClassKeepsAssignedData)
{
    Date d(1, 1, 2000);
    Assert::AreEqual(d.GetDay(), 1);
    Assert::AreEqual(d.GetMonth(), 1);
    Assert::AreEqual(d.GetYear(), 2000);
}

TEST_CASE("Date", Date_DefaultDateIsZero)
{
	Date d;
	Assert::AreEqual(d.GetDay(), 0);
	Assert::AreEqual(d.GetMonth(), 0);
	Assert::AreEqual(d.GetYear(), 0);
}

TEST_CASE("Date", Date_InvalidDateShouldDefaultToZero)
{
    Date d(100, 100, 100);
    Assert::AreEqual(d.GetDay(), 0);
    Assert::AreEqual(d.GetMonth(), 0);
    Assert::AreEqual(d.GetYear(), 0);
}

TEST_CASE("Date", Date_ComparisonsWork)
{
    Date d1(1, 1, 2000);
    Date d2(2, 1, 2000);
    Date d3(1, 2, 2000);
    Date d4(1, 1, 2001);

	Assert::AreComparisonOperatorsStrict(d1);
	Assert::AreComparisonOperatorsStrict(d2);
	Assert::AreComparisonOperatorsStrict(d3);
	Assert::AreComparisonOperatorsStrict(d4);

	Assert::AreComparisonOperatorsStrictForDifferingElements(d1, d2);
	Assert::AreComparisonOperatorsStrictForDifferingElements(d1, d3);
	Assert::AreComparisonOperatorsStrictForDifferingElements(d1, d4);
	Assert::AreComparisonOperatorsStrictForDifferingElements(d2, d3);
	Assert::AreComparisonOperatorsStrictForDifferingElements(d2, d4);
	Assert::AreComparisonOperatorsStrictForDifferingElements(d3, d4);
}


TEST_CASE("Student", Student_ClassKeepsAssignedData)
{
	Student s("John Smith", Date(23,8,2017));
	
	Assert::AreEqual(s.GetName(), "John Smith");
	Assert::AreEqual(s.GetBirthDate(), Date(23,8,2017));
}

TEST_CASE("Student", Student_DefaultValues)
{
	Student s;
	Assert::AreEqual(s.GetName(), "");
	Assert::AreEqual(s.GetBirthDate(), Date(1, 1, 2017));
}

TEST_CASE("Student", Student_NameIsCopied)
{
	// cannot really guarantee, but still better than nothing
	char Name[] = "John Smith";

	Student s(Name, Date(23, 8, 2017));
        Name[0] = 'S';
	
	Assert::AreNotEqual(
		reinterpret_cast<intptr_t>(s.GetName()),
		reinterpret_cast<intptr_t>(Name)
	);
}
