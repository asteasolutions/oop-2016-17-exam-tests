#pragma once

#include "UnitTestFramework.h"

TEST_CASE("PowerSpec", PowerSpec_DefalultSpecs)
{
  PowerSpec ps;
  Assert::AreEqual(ps.GetACDC(), "AC");
  Assert::AreEqual(ps.GetVoltage(), 230);
  Assert::AreEqual(ps.GetAmps(), 1);
}

TEST_CASE("PowerSpec", PowerSpec_ClassKeepsAssignedData)
{
  PowerSpec ps("DC", 12, 2);
  Assert::AreEqual(ps.GetACDC(), "DC");
  Assert::AreEqual(ps.GetVoltage(), 12);
  Assert::AreEqual(ps.GetAmps(), 2);
}

TEST_CASE("PowerSpec", PowerSpec_InvalidValuesShouldDefault)
{
  PowerSpec ps1("WAT", 12, 5);

  Assert::AreEqual(ps1.GetACDC(), "AC");
  Assert::AreEqual(ps1.GetVoltage(), 230);
  Assert::AreEqual(ps1.GetAmps(), 1);

  PowerSpec ps2("AC", -12, 5);

  Assert::AreEqual(ps2.GetACDC(), "AC");
  Assert::AreEqual(ps2.GetVoltage(), 230);
  Assert::AreEqual(ps2.GetAmps(), 1);

  PowerSpec ps3("DC", 12, -5);

  Assert::AreEqual(ps3.GetACDC(), "AC");
  Assert::AreEqual(ps3.GetVoltage(), 230);
  Assert::AreEqual(ps3.GetAmps(), 1);
}

TEST_CASE("PowerSpec", PowerSpec_PowerIsCorrect)
{
  PowerSpec ps("DC", 12, 2);
  Assert::AreEqual(ps.GetPower(), 24);
}

TEST_CASE("PowerSpec", PowerSpec_ComparisonsWork)
{
  PowerSpec ps1("AC", 230, 5);
  PowerSpec ps2("AC", 110, 3);
  PowerSpec ps3("DC", 12, 2);
  PowerSpec ps4("DC", 12, 1);

  Assert::AreComparisonOperatorsStrict(ps1);
  Assert::AreComparisonOperatorsStrict(ps2);
  Assert::AreComparisonOperatorsStrict(ps3);
  Assert::AreComparisonOperatorsStrict(ps4);

  Assert::AreComparisonOperatorsStrictForDifferingElements(ps2, ps1);
  Assert::AreComparisonOperatorsStrictForDifferingElements(ps4, ps3);

  Assert::IsFalse(ps1 < ps3);
  Assert::IsFalse(ps1 > ps3);
  Assert::IsFalse(ps1 <= ps3);
  Assert::IsFalse(ps1 >= ps3);

  Assert::IsFalse(ps2 < ps3);
  Assert::IsFalse(ps2 > ps3);
  Assert::IsFalse(ps2 <= ps3);
  Assert::IsFalse(ps2 >= ps3);

  Assert::IsFalse(ps1 < ps4);
  Assert::IsFalse(ps1 > ps4);
  Assert::IsFalse(ps1 <= ps4);
  Assert::IsFalse(ps1 >= ps4);

  Assert::IsFalse(ps2 < ps4);
  Assert::IsFalse(ps2 > ps4);
  Assert::IsFalse(ps2 <= ps4);
  Assert::IsFalse(ps2 >= ps4);
}

TEST_CASE("Transformer", Transformer_DefaultValues)
{
  Transformer t;
  PowerSpec zero("DC", 0, 0);

  Assert::AreEqual(t.GetBrand(), "");
  Assert::AreEqual(t.GetInSpec(), zero);
  Assert::AreEqual(t.GetOutSpec(), zero);
}

TEST_CASE("Transformer", Transformer_ClassKeepsAssignedData)
{
  PowerSpec ps1("AC", 230, 5);
  PowerSpec ps2("DC", 12, 1);
  Transformer t("MuchPower", ps1, ps2);

  Assert::AreEqual(t.GetBrand(), "MuchPower");
  Assert::AreEqual(t.GetInSpec(), ps1);
  Assert::AreEqual(t.GetOutSpec(), ps2);
}

TEST_CASE("Transformer", Transformer_InvalidOutSpecEqualsInSpec)
{
  PowerSpec ps1("AC", 230, 5);
  PowerSpec ps2("DC", 12, 1);
  Transformer t("MuchPower", ps2, ps1);

  Assert::AreEqual(t.GetBrand(), "MuchPower");
  Assert::AreEqual(t.GetInSpec(), ps2);
  Assert::AreEqual(t.GetOutSpec(), ps2);
}

TEST_CASE("Transformer", Transformer_RegularConstructorCopiesBrand)
{
  // cannot really guarantee, but still better than nothing
  char Brand[] = "MuchPower";

  Transformer t(Brand, PowerSpec("AC", 230, 5), PowerSpec("DC", 12, 1));
  Brand[1] = 'i';

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(t.GetBrand()),
                      reinterpret_cast<intptr_t>(Brand)
                      );
}

TEST_CASE("Transformer", Transformer_CopyConstructorCopiesBrand)
{
  // cannot really guarantee, but still better than nothing
  char Brand[] = "MuchPower";

  Transformer* t1 = new Transformer(Brand, PowerSpec("AC", 230, 5), PowerSpec("DC", 12, 1));
  Transformer t2 = *t1;

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(t1->GetBrand()),
                      reinterpret_cast<intptr_t>(t2.GetBrand())
                      );

  delete t1;

  Assert::AreEqual(Brand, t2.GetBrand());
}

TEST_CASE("Transformer", Transformer_CopyConstructorCopiesPowerSpecs)
{
  char Brand[] = "MuchPower";

  Transformer t1(Brand, PowerSpec("AC", 230, 5), PowerSpec("DC", 12, 1));
  Transformer t2 = t1;

  Assert::AreEqual(t1.GetInSpec(), t2.GetInSpec());
  Assert::AreEqual(t1.GetOutSpec(), t2.GetOutSpec());
}

TEST_CASE("Transformer", Transformer_AssignmentOperatorCopiesBrand)
{
  // cannot really guarantee, but still better than nothing
  char Brand[] = "MuchPower";

  Transformer* t1 = new Transformer(Brand, PowerSpec("AC", 230, 5), PowerSpec("DC", 12, 1));
  Transformer t2;
  t2 = *t1;

  Assert::AreNotEqual(
                      reinterpret_cast<intptr_t>(t1->GetBrand()),
                      reinterpret_cast<intptr_t>(t2.GetBrand())
                      );

  delete t1;

  Assert::AreEqual(Brand, t2.GetBrand());
}

TEST_CASE("Transformer", Transformer_AssignmentOperatorCopiesPowerSpecs)
{
  char Brand[] = "MuchPower";

  Transformer t1(Brand, PowerSpec("AC", 230, 5), PowerSpec("DC", 12, 1));
  Transformer t2;
  t2 = t1;

  Assert::AreEqual(t1.GetInSpec(), t2.GetInSpec());
  Assert::AreEqual(t1.GetOutSpec(), t2.GetOutSpec());
}

TEST_CASE("Transformer", Transformer_ComposeWorks)
{
  PowerSpec ps1("AC", 230, 5);
  PowerSpec ps2("AC", 110, 10);
  PowerSpec ps3("DC", 12, 1);

  Transformer t1("MuchPower", ps1, ps2);
  Transformer t2("SoElectrical", ps2, ps3);

  Transformer t3 = t1 * t2;
  Assert::AreEqual(t3.GetBrand(), "MuchPower-SoElectrical");
  Assert::AreEqual(t3.GetInSpec(), ps1);
  Assert::AreEqual(t3.GetOutSpec(), ps3);

  Transformer t4 = t2 * t1;
  Assert::AreEqual(t2.GetBrand(), t4.GetBrand());
  Assert::AreEqual(t2.GetInSpec(), t4.GetInSpec());
  Assert::AreEqual(t2.GetOutSpec(), t4.GetOutSpec());
}
