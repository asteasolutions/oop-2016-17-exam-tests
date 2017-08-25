#pragma once

#include "UnitTestFramework.h"

TEST_CASE("Date", Date_ClassKeepsAssignedData)
{
  const Date d(1, 1, 2000);
  Assert::AreEqual(d.GetDay(), 1);
  Assert::AreEqual(d.GetMonth(), 1);
  Assert::AreEqual(d.GetYear(), 2000);
}

TEST_CASE("Date", Date_DefaultDateIsZero)
{
  const Date d;
  Assert::AreEqual(d.GetDay(), 0);
  Assert::AreEqual(d.GetMonth(), 0);
  Assert::AreEqual(d.GetYear(), 0);
}

TEST_CASE("Date", Date_InvalidDateShouldDefaultToZero)
{
  const Date d(100, 100, 100);
  Assert::AreEqual(d.GetDay(), 0);
  Assert::AreEqual(d.GetMonth(), 0);
  Assert::AreEqual(d.GetYear(), 0);
}

TEST_CASE("Date", Date_ComparisonsWork)
{
  const Date d1(1, 1, 2000);
  const Date d2(2, 1, 2000);
  const Date d3(1, 2, 2000);
  const Date d4(1, 1, 2001);

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
  const Student s("John Smith", Date(23,8,2017));

  Assert::AreEqual(s.GetName(), "John Smith");
  Assert::AreEqual(s.GetBirthDate(), Date(23,8,2017));
}

TEST_CASE("Student", Student_DefaultValues)
{
  const Student s;
  Assert::AreEqual(s.GetName(), "");
  Assert::AreEqual(s.GetBirthDate(), Date(1, 1, 2017));
}

TEST_CASE("Student", Student_RegularConstructorCopiesName)
{
  // cannot really guarantee, but still better than nothing
  char Name[] = "John Smith";

  const Student s(Name, Date(23, 8, 2017));
  Name[0] = 'S';

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(s.GetName()),
                      reinterpret_cast<intptr_t>(Name)
                      );
}

TEST_CASE("Student", Student_CopyConstructorCopiesName)
{
  // cannot really guarantee, but still better than nothing
  char Name[] = "John Smith";

  Student const* s1 = new Student(Name, Date(23, 8, 2017));
  const Student s2 = *s1;

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(s1->GetName()),
                      reinterpret_cast<intptr_t>(s2.GetName())
                      );

  delete s1;

  Assert::AreEqual(
		   reinterpret_cast<const char*>(Name),
		   reinterpret_cast<const char*>(s2.GetName())
		   );
}

TEST_CASE("Student", Student_CopyConstructorCopiesDate)
{
  // cannot really guarantee, but still better than nothing
  char Name[] = "John Smith";

  const Student s1(Name, Date(23, 8, 2017));
  const Student s2 = s1;

  Assert::AreEqual(s1.GetBirthDate(), s2.GetBirthDate());
}

TEST_CASE("Student", Student_AssignmentOperatorCopiesName)
{
  // cannot really guarantee, but still better than nothing
  char Name[] = "John Smith";

  Student const* s1 = new Student(Name, Date(23, 8, 2017));
  Student s2;
  s2 = *s1;

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(s1->GetName()),
                      reinterpret_cast<intptr_t>(s2.GetName())
                      );

  delete s1;

  Assert::AreEqual(
		   reinterpret_cast<const char*>(Name),
		   reinterpret_cast<const char*>(s2.GetName())
		   );
}

TEST_CASE("Student", Student_AssignmentOperatorCopiesDate)
{
  // cannot really guarantee, but still better than nothing
  char Name[] = "John Smith";

  const Student s1(Name, Date(23, 8, 2017));
  Student s2;
  s2 = s1;

  Assert::AreEqual(s1.GetBirthDate(), s2.GetBirthDate());
}
