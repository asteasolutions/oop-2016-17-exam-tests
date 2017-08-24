#pragma once

#include "UnitTestFramework.h"

TEST_CASE("Time", Time_ClassKeepsAssignedData)
{
  const Time t(23, 56, 15);
  Assert::AreEqual(t.GetSecond(), 23);
  Assert::AreEqual(t.GetMinute(), 56);
  Assert::AreEqual(t.GetHour(), 15);
}

TEST_CASE("Time", Time_DefaultTimeIsZero)
{
  const Time t;
  Assert::AreEqual(t.GetSecond(), 0);
  Assert::AreEqual(t.GetMinute(), 0);
  Assert::AreEqual(t.GetHour(), 0);
}

TEST_CASE("Time", Time_InvalidTimeShouldDefaultToZero)
{
  const Time t(100, 100, 100);
  Assert::AreEqual(t.GetSecond(), 0);
  Assert::AreEqual(t.GetMinute(), 0);
  Assert::AreEqual(t.GetHour(), 0);
}

TEST_CASE("Time", Time_ComparisonsWork)
{
  const Time t1(10, 5, 13);
  const Time t2(10, 5, 30);
  const Time t3(10, 6, 1);
  const Time t4(11, 2, 0);

  Assert::AreComparisonOperatorsStrict(t1);
  Assert::AreComparisonOperatorsStrict(t2);
  Assert::AreComparisonOperatorsStrict(t3);
  Assert::AreComparisonOperatorsStrict(t4);

  Assert::AreComparisonOperatorsStrictForDifferingElements(t1, t2);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t1, t3);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t1, t4);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t2, t3);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t2, t4);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t3, t4);
}

TEST_CASE("Appointment", Appointment_ClassKeepsAssignedData)
{
  const Time t1(9, 15, 10);
  const Time t2(10, 55, 20);
  const Appointment a("OOP exam", t1, t2);

  Assert::AreEqual(a.GetDescription(), "OOP exam");
  Assert::AreEqual(a.GetStart(), t1);
  Assert::AreEqual(a.GetEnd(), t2);
}

TEST_CASE("Appointment", Appointment_DefaultValues)
{
  const Time t(0, 0, 0);
  const Appointment a;
  Assert::AreEqual(a.GetDescription(), "");
  Assert::AreEqual(a.GetStart(), t);
  Assert::AreEqual(a.GetEnd(), t);
}

TEST_CASE("Appointment", Appointment_InvalidStartEndDatesAreSwapped)
{
  const Time t1(9, 15, 10);
  const Time t2(10, 55, 20);
  const Appointment a("OOP exam", t2, t1);

  Assert::AreEqual(a.GetDescription(), "OOP exam");
  Assert::AreEqual(a.GetStart(), t1);
  Assert::AreEqual(a.GetEnd(), t2);
}

TEST_CASE("Appointment", Appointment_RegularConstructorCopiesDescription)
{
  // cannot really guarantee, but still better than nothing
  char Description[] = "OOP exam";

  const Appointment a(Description, Time(9, 15, 10), Time(10, 55, 20));
  Description[0] = 'S';
  Description[1] = 'D';

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(a.GetDescription()),
                      reinterpret_cast<intptr_t>(Description)
                      );
}

TEST_CASE("Appointment", Appointment_CopyConstructorCopiesDescription)
{
  // cannot really guarantee, but still better than nothing
  char Description[] = "OOP Exam";

  Appointment const* a1 = new Appointment(Description, Time(9, 15, 10), Time(10, 55, 20));
  const Appointment a2 = *a1;

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(a1->GetDescription()),
                      reinterpret_cast<intptr_t>(a2.GetDescription())
                      );

  delete a1;

  Assert::AreEqual(Description, a2.GetDescription());
}

TEST_CASE("Appointment", Appointment_CopyConstructorCopiesTimes)
{
  // cannot really guarantee, but still better than nothing
  char Description[] = "OOP Exam";

  const Appointment a1(Description, Time(9, 15, 10), Time(10, 55, 20));
  const Appointment a2 = a1;

  Assert::AreEqual(a1.GetStart(), a2.GetStart());
  Assert::AreEqual(a1.GetEnd(), a2.GetEnd());
}

TEST_CASE("Appointment", Appointment_AssignmentOperatorCopiesDescription)
{
  // cannot really guarantee, but still better than nothing
  char Description[] = "OOP Exam";

  Appointment const* a1 = new Appointment(Description, Time(9, 15, 10), Time(10, 55, 20));
  Appointment a2;
  a2 = *a1;

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(a1->GetDescription()),
                      reinterpret_cast<intptr_t>(a2.GetDescription())
                      );

  delete a1;

  Assert::AreEqual(Description, a2.GetDescription());
}

TEST_CASE("Appointment", Appointment_AssignmentOperatorCopiesTime)
{
  // cannot really guarantee, but still better than nothing
  char Description[] = "OOP Exam";

  const Appointment a1(Description, Time(9, 15, 10), Time(10, 55, 20));
  Appointment a2;
  a2 = a1;

  Assert::AreEqual(a1.GetStart(), a2.GetStart());
  Assert::AreEqual(a1.GetEnd(), a2.GetEnd());
}

TEST_CASE("Appointment", Appointment_GetLengthWorks)
{
  const Appointment a1(Description, Time(9, 15, 10), Time(10, 55, 20));
  Assert::1AreEqual(a1.GetLength(), Time(1, 40, 10));

  const Appointment a2(Description, Time(9, 15, 10), Time(12, 10, 20));
  Assert::1AreEqual(a2.GetLength(), Time(2, 55, 10));

  const Appointment a3(Description, Time(9, 15, 10), Time(14, 5, 5));
  Assert::1AreEqual(a2.GetLength(), Time(4, 49, 55));
}
