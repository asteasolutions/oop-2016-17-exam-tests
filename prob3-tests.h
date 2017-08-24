#pragma once

#include "UnitTestFramework.h"

TEST_CASE("Temperature", Temperature_DefaultTemperatureIs12)
{
  Temperature t;
  Assert::AreEqual(t.GetMin(), 12);
  Assert::AreEqual(t.GetMax(), 12);
  Assert::AreEqual(t.GetAverage(), 12);
}

TEST_CASE("Temperature", Temperature_ClassKeepsAssignedData)
{
  Temperature t(7, 20, 28);
  Assert::AreEqual(t.GetMin(), 7);
  Assert::AreEqual(t.GetAverage(), 20);
  Assert::AreEqual(t.GetMax(), 28);
}

TEST_CASE("Temperature", Temperature_InvalidValuesShouldDefaultTo12)
{
  Temperature t(28, 10, 7);
  Assert::AreEqual(t.GetMin(), 12);
  Assert::AreEqual(t.GetMax(), 12);
  Assert::AreEqual(t.GetAverage(), 12);
}

TEST_CASE("Temperature", Temperature_AmplitudeIsCorrect)
{
  Temperature t(7, 10, 28);
  Assert::AreEqual(t.GetAmplitude(), 21);
}

TEST_CASE("Temperature", Temperature_ComparisonsWork)
{
  Temperature t1(7, 10, 28);
  Temperature t2(5, 12, 20);
  Temperature t3(8, 18, 20);
  Temperature t4(8, 12, 20);

  Assert::AreComparisonOperatorsStrict(t1);
  Assert::AreComparisonOperatorsStrict(t2);
  Assert::AreComparisonOperatorsStrict(t3);
  Assert::AreComparisonOperatorsStrict(t4);

  Assert::AreComparisonOperatorsStrictForDifferingElements(t2, t1);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t3, t1);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t4, t1);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t2, t3);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t2, t4);
  Assert::AreComparisonOperatorsStrictForDifferingElements(t4, t3);
}

TEST_CASE("Forecast", Forecast_DefaultValues)
{
  Forecast f;

  Assert::AreEqual(f.GetPlace(), "");
  Assert::AreEqual(f.GetTemperature().GetMin(), 0);
  Assert::AreEqual(f.GetTemperature().GetAverage(), 0);
  Assert::AreEqual(f.GetTemperature().GetMax(), 0);
}

TEST_CASE("Forecast", Forecast_ClassKeepsAssignedData)
{
  Forecast f("Sofia", Temperature(7, 20, 28));

  Assert::AreEqual(f.GetPlace(), "Sofia");
  Assert::AreEqual(f.GetTemperature().GetMin(), 7);
  Assert::AreEqual(f.GetTemperature().GetAverage(), 20);
  Assert::AreEqual(f.GetTemperature().GetMax(), 28);
}

TEST_CASE("Forecast", Forecast_RegularConstructorCopiesPlace)
{
  // cannot really guarantee, but still better than nothing
  char Place[] = "Sofia";

  Forecast f(Place, Temperature(7, 20, 28));
  Place[2] = 'n';

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(f.GetPlace()),
                      reinterpret_cast<intptr_t>(Place)
                      );
}

TEST_CASE("Forecast", Forecast_CopyConstructorCopiesPlace)
{
  // cannot really guarantee, but still better than nothing
  char Place[] = "Sofia";

  Forecast* f1 = new Forecast(Place, Temperature(7, 20, 28));
  Forecast f2 = *f1;

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(f1->GetPlace()),
                      reinterpret_cast<intptr_t>(f2.GetPlace())
                      );

  delete f1;

  Assert::AreEqual(Place, f2.GetPlace());
}

TEST_CASE("Forecast", Forecast_CopyConstructorCopiesTemperature)
{
  // cannot really guarantee, but still better than nothing
  char Place[] = "Sofia";

  Forecast f1(Place, Temperature(7, 20, 28));
  Forecast f2 = f1;

  Assert::AreEqual(f1.GetTemperature(), f2.GetTemperature());
}

TEST_CASE("Forecast", Forecast_AssignmentOperatorCopiesPlace)
{
  // cannot really guarantee, but still better than nothing
  char Place[] = "John Smith";

  Forecast* f1 = new Forecast(Place, Temperature(23, 8, 2017));
  Forecast f2;
  f2 = *f1;

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(f1->GetPlace()),
                      reinterpret_cast<intptr_t>(f2.GetPlace())
                      );

  delete f1;

  Assert::AreEqual(Place, f2.GetPlace());
}

TEST_CASE("Forecast", Forecast_AssignmentOperatorCopiesTemperature)
{
  // cannot really guarantee, but still better than nothing
  char Place[] = "Sofia";

  Forecast f1(Place, Temperature(7, 20, 28));
  Forecast f2;
  f2 = f1;

  Assert::AreEqual(f1.GetTemperature(), f2.GetTemperature());
}

TEST_CASE("Forecast", Forecast_UpdateIfHotterWorks)
{
  Temperature t1(7, 10, 28);
  Temperature t2(5, 12, 20);
  Temperature t3(8, 18, 20);

  Forecast f1("Sofia", t3);
  Forecast f2("Varna", t2);
  Forecast f3("Sofia", t1);
  Forecast f4("Sofia", t3);

  f1.UpdateIfHotter(f2);
  Assert::AreEqual(f1.GetTemperature(), t3);

  f1.UpdateIfHotter(f3);
  Assert::AreEqual(f1.GetTemperature(), t1);

  f3.UpdateIfHotter(f4);
  Assert::AreEqual(f3.GetTemperature(), t1);
}
