/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Program: изберете коректното: Информатика, Информационни системи, Компютърни науки, Софтуерно инженерство
// Date: 25.08.2017
//

#include <cstring>

const char AC[] = "AC";
const char DC[] = "DC";

///
/// Клас, спецификация на електрически уред
///
class PowerSpec
{
private:
  bool m_IsAC;
  int m_Voltage, m_Amps;

public:

  PowerSpec(char const* ACDC = AC, int voltage = 230, int amps = 1) : m_Voltage(voltage), m_Amps(amps)
  {
    if (!strcmp(ACDC, AC))
      m_IsAC = true;
    else if (!strcmp(ACDC, DC))
      m_IsAC = false;
    else
      m_Voltage = -1;

    if (m_Voltage < 0 || m_Amps < 0)
    {
      m_IsAC = true;
      m_Voltage = 230;
      m_Amps = 1;
    }
  }

  char const* GetACDC() const
  {
    return m_IsAC ? AC : DC;
  }

  int GetVoltage() const
  {
    return m_Voltage;
  }

  int GetAmps() const
  {
    return m_Amps;
  }

  int GetPower() const
  {
    return GetVoltage() * GetAmps();
  }

  bool operator==(const PowerSpec& other) const
  {
    return
      GetACDC()  == other.GetACDC() &&
      GetVoltage() == other.GetVoltage() &&
      GetAmps() == other.GetAmps();
  }

  bool operator!=(const PowerSpec& other) const
  {
    return !(*this == other);
  }

  bool operator<= (const PowerSpec& other) const
  {
    return *this < other || *this == other;
  }

  bool operator> (const PowerSpec& other) const
  {
    return other < *this;
  }

  bool operator< (const PowerSpec& other) const
  {
    return GetACDC() == other.GetACDC() &&
      (GetVoltage() < other.GetVoltage() ||
       (GetVoltage() == other.GetVoltage() && GetAmps() < other.GetAmps()));
  }

  bool operator>= (const PowerSpec& other) const
  {
    return other <= *this;
  }
};

///
/// Клас, представящ трансформатор
///
class Transformer
{
private:
  char* m_pBrand;
  PowerSpec m_InSpec, m_OutSpec;

public:

  Transformer() :
    m_pBrand(nullptr),
    m_InSpec("DC", 0, 0),
    m_OutSpec("DC", 0, 0)
  {
    SetBrand("");
  }

  Transformer(const char* pBrand, const PowerSpec & InSpec, const PowerSpec & OutSpec) :
    m_pBrand(nullptr),
    m_InSpec(InSpec),
    m_OutSpec(OutSpec)
  {
    if (m_InSpec.GetPower() < m_OutSpec.GetPower())
      m_OutSpec = m_InSpec;
    SetBrand(pBrand);
  }

  Transformer(const Transformer& other) :
    m_pBrand(nullptr),
    m_InSpec(other.m_InSpec),
    m_OutSpec(other.m_OutSpec)
  {
    SetBrand(other.GetBrand());
  }

  ~Transformer()
  {
    delete[] m_pBrand;
  }

  Transformer & operator=(const Transformer & other)
  {
    if (this != &other)
      {
        SetBrand(other.GetBrand());
        m_InSpec = other.m_InSpec;
        m_OutSpec = other.m_OutSpec;
      }

    return *this;
  }

  void SetBrand(const char* pBrand)
  {
    delete[] m_pBrand;
    m_pBrand = new char[strlen(pBrand) + 1];
    strcpy(m_pBrand, pBrand);
  }

  char const* GetBrand() const
  {
    return m_pBrand;
  }

  PowerSpec GetInSpec() const
  {
    return m_InSpec;
  }

  PowerSpec GetOutSpec() const
  {
    return m_OutSpec;
  }

  Transformer operator*(Transformer const& other) const
  {
    if (GetOutSpec() != other.GetInSpec())
      return *this;

    char* newBrand = new char[strlen(GetBrand()) + strlen(other.GetBrand()) + 2];
    strcpy(newBrand, GetBrand());
    strcat(newBrand, "-");
    strcat(newBrand, other.GetBrand());

    Transformer result(newBrand, GetInSpec(), other.GetOutSpec());
    delete[] newBrand;
    return result;
  }
};


// Този ред включва тестовете за задачата
#include "prob4-tests.h"

int main() {

//-------------------------------------------------------------------------
//
// ВАЖНО: Преди предаване на решението, моля премахнете коментара от дадения по-долу ред,
//        за да активирате автоматичните тестове за решението си.
//
//-------------------------------------------------------------------------

  RunTests();

  return 0;
}
