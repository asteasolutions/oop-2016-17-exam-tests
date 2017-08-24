#pragma once

#include "UnitTestFramework.h"

TEST_CASE("Interval", Interval_DefaultIntervalIsZeroOne)
{
  const Interval i;
  Assert::AreEqual(i.GetLeft(), 0);
  Assert::AreEqual(i.GetRight(), 1);
}

TEST_CASE("Interval", Interval_ClassKeepsAssignedData)
{
  const Interval i(5, 10);
  Assert::AreEqual(i.GetLeft(), 5);
  Assert::AreEqual(i.GetRight(), 10);
}

TEST_CASE("Interval", Interval_InvalidIntervalShouldDefaultToZeroOne)
{
  const Interval i(10, 5);
  Assert::AreEqual(i.GetLeft(), 0);
  Assert::AreEqual(i.GetRight(), 1);
}

TEST_CASE("Interval", Interval_ContainsNumber)
{
  const Interval i1(5, 10);
  Assert::IsFalse(i1.Contains(4));
  Assert::IsTrue (i1.Contains(5));
  Assert::IsTrue (i1.Contains(7));
  Assert::IsTrue (i1.Contains(10));
  Assert::IsFalse(i1.Contains(11));

  const Interval i2(3, 3);
  Assert::IsFalse(i2.Contains(2));
  Assert::IsTrue (i2.Contains(3));
  Assert::IsFalse(i2.Contains(4));
}

TEST_CASE("Interval", Interval_ComparisonsWork)
{
  const Interval i1(1, 5);
  const Interval i2(1, 3);
  const Interval i3(2, 4);
  const Interval i4(4, 4);

  Assert::AreComparisonOperatorsStrict(i1);
  Assert::AreComparisonOperatorsStrict(i2);
  Assert::AreComparisonOperatorsStrict(i3);
  Assert::AreComparisonOperatorsStrict(i4);

  Assert::AreComparisonOperatorsStrictForDifferingElements(i2, i1);
  Assert::AreComparisonOperatorsStrictForDifferingElements(i3, i1);
  Assert::AreComparisonOperatorsStrictForDifferingElements(i4, i1);
  Assert::AreComparisonOperatorsStrictForDifferingElements(i4, i3);

  Assert::IsFalse(i2 < i3);
  Assert::IsFalse(i2 > i3);
  Assert::IsFalse(i2 <= i3);
  Assert::IsFalse(i2 >= i3);

  Assert::IsFalse(i2 < i4);
  Assert::IsFalse(i2 > i4);
  Assert::IsFalse(i2 <= i4);
  Assert::IsFalse(i2 >= i4);
}

TEST_CASE("IntervalSet", IntervalSet_DefaultSingleton)
{
  const IntervalSet is;
  
  Assert::AreEqual(is.GetSize(), 1);
  Assert::AreEqual(is.GetIntervals()[0].GetLeft(), 0);
  Assert::AreEqual(is.GetIntervals()[0].GetRight(), 1);
}

TEST_CASE("IntervalSet", IntervalSet_ClassKeepsAssignedData)
{
  Interval Intervals[] = { Interval(1, 3), Interval(2, 4), Interval(3, 5) };
  const IntervalSet is(Intervals, 3);
  
  Assert::AreEqual(is.GetSize(), 3);
  
  Assert::AreEqual(is.GetIntervals()[0].GetLeft(), 1);
  Assert::AreEqual(is.GetIntervals()[0].GetRight(), 3);

  Assert::AreEqual(is.GetIntervals()[1].GetLeft(), 2);
  Assert::AreEqual(is.GetIntervals()[1].GetRight(), 4);

  Assert::AreEqual(is.GetIntervals()[2].GetLeft(), 3);
  Assert::AreEqual(is.GetIntervals()[2].GetRight(), 5);
}

TEST_CASE("IntervalSet", IntervalSet_RegularConstrucorCopiesArray)
{
  // cannot really guarantee, but still better than nothing
  Interval Intervals[] = { Interval(1, 3), Interval(2, 4), Interval(3, 5) };
  
  const IntervalSet is(Intervals, 3);
  
  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(is.GetIntervals()),
                      reinterpret_cast<intptr_t>(Intervals)
                      );

  Intervals[1] = Interval(6, 8);

  Assert::AreNotEqual(is.GetIntervals()[1].GetLeft(), 6);
  Assert::AreNotEqual(is.GetIntervals()[1].GetRight(), 8);
}

TEST_CASE("IntervalSet", IntervalSet_CopyConstrucorCopiesArray)
{
  // cannot really guarantee, but still better than nothing
  Interval Intervals[] = { Interval(1, 3), Interval(2, 4), Interval(3, 5) };
  
  IntervalSet const * is1 = new IntervalSet(Intervals, 3);
  const IntervalSet is2 = *is1;
  
  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(is1->GetIntervals()),
                      reinterpret_cast<intptr_t>(is2.GetIntervals())
                      );

  delete is1;

  Assert::AreEqual(is2.GetIntervals()[0].GetLeft(), 1);
  Assert::AreEqual(is2.GetIntervals()[0].GetRight(), 3);

  Assert::AreEqual(is2.GetIntervals()[1].GetLeft(), 2);
  Assert::AreEqual(is2.GetIntervals()[1].GetRight(), 4);

  Assert::AreEqual(is2.GetIntervals()[2].GetLeft(), 3);
  Assert::AreEqual(is2.GetIntervals()[2].GetRight(), 5);
}

TEST_CASE("IntervalSet", IntervalSet_AssignmentOperatorCopiesArray)
{
  // cannot really guarantee, but still better than nothing
  Interval Intervals[] = { Interval(1, 3), Interval(2, 4), Interval(3, 5) };
  
  IntervalSet const * is1 = new IntervalSet(Intervals, 3);
  IntervalSet is2;
  is2 = *is1;
  
  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(is1->GetIntervals()),
                      reinterpret_cast<intptr_t>(is2.GetIntervals())
                      );

  delete is1;

  Assert::AreEqual(is2.GetIntervals()[0].GetLeft(), 1);
  Assert::AreEqual(is2.GetIntervals()[0].GetRight(), 3);

  Assert::AreEqual(is2.GetIntervals()[1].GetLeft(), 2);
  Assert::AreEqual(is2.GetIntervals()[1].GetRight(), 4);

  Assert::AreEqual(is2.GetIntervals()[2].GetLeft(), 3);
  Assert::AreEqual(is2.GetIntervals()[2].GetRight(), 5);
}


TEST_CASE("IntervalSet", IntervalSet_CountSubsetsWorks)
{
  Interval Intervals[] = { Interval(1, 3), Interval(2, 4), Interval(3, 5) };
  const IntervalSet is(Intervals, 3);

  Assert::AreEqual(is.CountSubsets(Interval(0, 10)), 3);
  Assert::AreEqual(is.CountSubsets(Interval(4, 10)), 0);
  Assert::AreEqual(is.CountSubsets(Interval(3, 8)), 1);
  Assert::AreEqual(is.CountSubsets(Interval(2, 6)), 2);
  Assert::AreEqual(is.CountSubsets(Interval(1, 4)), 2);
  Assert::AreEqual(is.CountSubsets(Interval(1, 3)), 1);
}
