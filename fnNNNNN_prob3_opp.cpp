/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Program: изберете коректното: Информатика, Информационни системи, Компютърни науки, Софтуерно инженерство
// Date: 25.08.2017
//

#include <cstring>

///
/// Клас, представящ статистика за температура
///
class Temperature
{
private:
  int m_Min, m_Avg, m_Max;

public:
  Temperature(int min = 12, int avg = 12, int max = 12) : m_Min(min), m_Avg(avg), m_Max(max)
  {
    if (m_Min > m_Avg || m_Avg > m_Max)
      m_Min = m_Avg = m_Max = 12;
  }

  int GetMin() const
  {
    return m_Min;
  }

  int GetAverage() const
  {
    return m_Avg;
  }

  int GetMax() const
  {
    return m_Max;
  }

  int GetAmplitude() const
  {
    return m_Max - m_Min;
  }

  bool operator==(const Temperature& other) const
  {
    return m_Avg == other.m_Avg &&
      m_Min == other.m_Min &&
      m_Max == other.m_Max;
  }

  bool operator!=(const Temperature& other) const
  {
    return !(*this == other);
  }

  bool operator< (const Temperature& other) const
  {
    return m_Max < other.m_Max ||
                   (m_Max == other.m_Max && m_Min < other.m_Min) ||
      (m_Max == other.m_Max && m_Min == other.m_Min && m_Avg < other.m_Avg);
  }

  bool operator> (const Temperature& other) const
  {
    return other < *this;
  }

  bool operator<= (const Temperature& other) const
  {
    return *this < other || *this == other;
  }

  bool operator>= (const Temperature& other) const
  {
    return other <= *this;
  }

};

///
/// Клас, представящ прогноза
///
class Forecast
{
private:
  char* m_pPlace;
  Temperature m_Temperature;

public:
  Forecast() :
    m_pPlace(nullptr),
    m_Temperature(0, 0, 0)
  {
    SetPlace("");
  }

  Forecast(const char* pPlace, const Temperature & temp) :
    m_pPlace(nullptr),
    m_Temperature(temp)
  {
    SetPlace(pPlace);
  }

  Forecast(const Forecast& other) :
    m_pPlace(nullptr),
    m_Temperature(other.m_Temperature)
  {
    SetPlace(other.GetPlace());
  }

  ~Forecast()
  {
    delete m_pPlace;
  }

  Forecast & operator=(const Forecast & other)
  {
    if (this != &other)
      {
        SetPlace(other.GetPlace());
        m_Temperature = other.m_Temperature;
      }

    return *this;
  }

  void SetPlace(const char* pPlace)
  {
    delete[] m_pPlace;
    m_pPlace = new char[strlen(pPlace) + 1];
    strcpy(m_pPlace, pPlace);
  }

  const char* GetPlace() const
  {
    return m_pPlace;
  }
	
  const Temperature GetTemperature() const
  {
    return m_Temperature;
  }

  void UpdateIfHotter(Temperature const& t)
  {
    if (t > GetTemperature())
      m_Temperature = t;
  }
};


// Този ред включва тестовете за задачата
#include "prob3-tests.h"

int main() {

  RunTests();
  
  return 0;
}
