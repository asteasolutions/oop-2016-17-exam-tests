#pragma once

#include "UnitTestFramework.h"

TEST_CASE("Chronometer", Chronometer_ClassKeepsAssignedData)
{
  const Chronometer t(23, 56, 15);
  Assert::AreEqual(t.GetSecond(), 15);
  Assert::AreEqual(t.GetMinute(), 56);
  Assert::AreEqual(t.GetHour(), 23);
}

TEST_CASE("Chronometer", Chronometer_DefaultChronometerIsZero)
{
  const Chronometer t;
  Assert::AreEqual(t.GetSecond(), 0);
  Assert::AreEqual(t.GetMinute(), 0);
  Assert::AreEqual(t.GetHour(), 0);
}

TEST_CASE("Chronometer", Chronometer_InvalidChronometerShouldDefaultToZero)
{
  const Chronometer t(100, 100, 100);
  Assert::AreEqual(t.GetSecond(), 0);
  Assert::AreEqual(t.GetMinute(), 0);
  Assert::AreEqual(t.GetHour(), 0);
}

TEST_CASE("Chronometer", Chronometer_PrefixIncrementWorks)
{
  const Chronometer t1(10, 59, 57);

  ++t1;
  Assert::IsEqual(t1.GetHour(), 10);
  Assert::IsEqual(t1.GetMinute(), 59);
  Assert::IsEqual(t1.GetSecond(), 58);

  ++(++t1);
  Assert::IsEqual(t1.GetHour(), 11);
  Assert::IsEqual(t1.GetMinute(), 0);
  Assert::IsEqual(t1.GetSecond(), 0);
}

TEST_CASE("Chronometer", Chronometer_PostfixIncrementWorks)
{
  const Chronometer t1(10, 20, 59);

  const Chronometer t2 = t1++;
  Assert::IsEqual(t1.GetHour(), 10);
  Assert::IsEqual(t1.GetMinute(), 21);
  Assert::IsEqual(t1.GetSecond(), 0);

  Assert::IsEqual(t2.GetHour(), 10);
  Assert::IsEqual(t2.GetMinute(), 20);
  Assert::IsEqual(t2.GetSecond(), 59);
}

TEST_CASE("Chronometer", Chronometer_AdditionWorks)
{
  const Chronometer t1(10, 20, 45);

  t1 += 90;
  
  Assert::IsEqual(t1.GetHour(), 10);
  Assert::IsEqual(t1.GetMinute(), 22);
  Assert::IsEqual(t1.GetSecond(), 15);

  (t1 += 10) += 20;

  Assert::IsEqual(t1.GetHour(), 10);
  Assert::IsEqual(t1.GetMinute(), 22);
  Assert::IsEqual(t1.GetSecond(), 45);
}

TEST_CASE("Chronometer", Chronometer_LessThanWorks)
{
  const Chronometer t1(10, 5, 13);
  const Chronometer t2(10, 5, 30);
  const Chronometer t3(10, 6, 1);
  const Chronometer t4(11, 2, 0);

  Assert::IsTrue(t1 < t2);
  Assert::IsTrue(t1 < t3);
  Assert::IsTrue(t1 < t4);
  Assert::IsTrue(t2 < t3);
  Assert::IsTrue(t2 < t4);
  Assert::IsTrue(t3 < t4);

  Assert::IsFalse(t1 < t1);
  Assert::IsFalse(t2 < t1);
  Assert::IsFalse(t2 < t2);
  Assert::IsFalse(t3 < t1);
  Assert::IsFalse(t3 < t2);
  Assert::IsFalse(t3 < t3);
  Assert::IsFalse(t4 < t1);
  Assert::IsFalse(t4 < t2);
  Assert::IsFalse(t4 < t3);
  Assert::IsFalse(t4 < t4);
}

TEST_CASE("Athlete", Athlete_DefaultSingletonIsEmpty)
{
  const Athlete at;
  
  Assert::AreEqual(at.GetSize(), 0);
}

TEST_CASE("Athlete", Athlete_ClassKeepsAssignedData)
{
  Chronometer Chronometers[] =
    { Chronometer(1, 15, 2), Chronometer(0, 45, 18), Chronometer(0, 50, 33) };
  const Athlete at(Chronometers, 3);
  
  Assert::AreEqual(at.GetSize(), 3);
  
  Assert::AreEqual(at.GetChronometers()[0].GetHour(), 1);
  Assert::AreEqual(at.GetChronometers()[0].GetMinute(), 15);
  Assert::AreEqual(at.GetChronometers()[0].GetSecond(), 2);

  Assert::AreEqual(at.GetChronometers()[1].GetHour(), 0);
  Assert::AreEqual(at.GetChronometers()[1].GetMinute(), 45);
  Assert::AreEqual(at.GetChronometers()[1].GetSecond(), 18);

  Assert::AreEqual(at.GetChronometers()[2].GetHour(), 0);
  Assert::AreEqual(at.GetChronometers()[2].GetMinute(), 50);
  Assert::AreEqual(at.GetChronometers()[2].GetSecond(), 33);
}

TEST_CASE("Athlete", Athlete_RegularConstrucorCopiesArray)
{
  // cannot really guarantee, but still better than nothing
  Chronometer Chronometers[] =
    { Chronometer(1, 15, 2), Chronometer(0, 45, 18), Chronometer(0, 50, 33) };
  
  const Athlete at(Chronometers, 3);
  
  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(at.GetChronometers()),
                      reinterpret_cast<intptr_t>(Chronometers)
                      );

  Chronometers[1] = Chronometer(2, 3, 4);

  Assert::AreNotEqual(at.GetChronometers()[1].GetHour(), 2);
  Assert::AreNotEqual(at.GetChronometers()[1].GetMinute(), 3);
  Assert::AreNotEqual(at.GetChronometers()[1].GetSecond(), 4);

}

TEST_CASE("Athlete", Athlete_CopyConstrucorCopiesArray)
{
  // cannot really guarantee, but still better than nothing
  Chronometer Chronometers[] =
    { Chronometer(1, 15, 2), Chronometer(0, 45, 18), Chronometer(0, 50, 33) };
  
  Athlete const * at1 = new Athlete(Chronometers, 3);
  const Athlete at2 = *at1;
  
  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(at1->GetChronometers()),
                      reinterpret_cast<intptr_t>(at2.GetChronometers())
                      );

  delete at1;

  Assert::AreEqual(at2.GetChronometers()[0].GetHour(), 1);
  Assert::AreEqual(at2.GetChronometers()[0].GetMinute(), 15);
  Assert::AreEqual(at2.GetChronometers()[0].GetSecond(), 2);

  Assert::AreEqual(at2.GetChronometers()[1].GetHour(), 0);
  Assert::AreEqual(at2.GetChronometers()[1].GetMinute(), 45);
  Assert::AreEqual(at2.GetChronometers()[1].GetSecond(), 18);

  Assert::AreEqual(at2.GetChronometers()[2].GetHour(), 0);
  Assert::AreEqual(at2.GetChronometers()[2].GetMinute(), 50);
  Assert::AreEqual(at2.GetChronometers()[2].GetSecond(), 33);
}

TEST_CASE("Athlete", Athlete_AssignmentOperatorCopiesArray)
{
  // cannot really guarantee, but still better than nothing
  Chronometer Chronometers[] =
    { Chronometer(1, 15, 2), Chronometer(0, 45, 18), Chronometer(0, 50, 33) };
  
  Athlete const * at1 = new Athlete(Chronometers, 3);
  Athlete at2;
  at2 = *at1;
  
  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(at1->GetChronometers()),
                      reinterpret_cast<intptr_t>(at2.GetChronometers())
                      );

  delete at1;

  Assert::AreEqual(at2.GetChronometers()[0].GetHour(), 1);
  Assert::AreEqual(at2.GetChronometers()[0].GetMinute(), 15);
  Assert::AreEqual(at2.GetChronometers()[0].GetSecond(), 2);

  Assert::AreEqual(at2.GetChronometers()[1].GetHour(), 0);
  Assert::AreEqual(at2.GetChronometers()[1].GetMinute(), 45);
  Assert::AreEqual(at2.GetChronometers()[1].GetSecond(), 18);

  Assert::AreEqual(at2.GetChronometers()[2].GetHour(), 0);
  Assert::AreEqual(at2.GetChronometers()[2].GetMinute(), 50);
  Assert::AreEqual(at2.GetChronometers()[2].GetSecond(), 33);
}


TEST_CASE("Athlete", Athlete_GetBestTimeWorks)
{
  Chronometer Chronometers[] =
    { Chronometer(1, 15, 2), Chronometer(0, 45, 18), Chronometer(0, 50, 33) };
  const Athlete at1(Chronometers, 3);
  const Chronotmeter t1 = at1.GetBestTime();

  Assert::AreEqual(t1.GetHour(), 0);
  Assert::AreEqual(t1.GetMinute(), 45);
  Assert::AreEqual(t1.GetSecond(), 18);

  const Athlete at2;
  const Chronotmeter t2 = at1.GetBestTime();
  
  Assert::AreEqual(t2.GetHour(), 0);
  Assert::AreEqual(t2.GetMinute(), 0);
  Assert::AreEqual(t2.GetSecond(), 0);  
}
