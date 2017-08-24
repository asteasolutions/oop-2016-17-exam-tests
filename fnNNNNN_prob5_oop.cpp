/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Program: изберете коректното: Информатика, Информационни системи, Компютърни науки, Софтуерно инженерство
// Date: 25.08.2017
//

#include <cstring>
#include <utility>

///
/// Клас, представящ момент от време
///
class Time
{
private:
  int m_Hour, m_Minute, m_Second;

public:
  
  Time(int Hour = 0, int Minute = 0, int Second = 0) :
    m_Hour(Hour), m_Minute(Minute), m_Second(Second)
  {
    if (m_Hour < 0 || m_Hour > 23 ||
        m_Minute < 0 || m_Minute > 59 ||
        m_Second < 0 || m_Second > 59)
      m_Hour = m_Minute = m_Second = 0;
  }

  int GetHour() const
  {
    return m_Hour;
  }

  int GetMinute() const
  {
    return m_Minute;
  }

  int GetSecond() const
  {
    return m_Second;
  }

  bool operator==(const Time& other) const
  {
    return m_Second == other.m_Second &&
      m_Minute == other.m_Minute &&
      m_Hour == other.m_Hour;
  }

  bool operator!=(const Time& other) const
  {
    return !(*this == other);
  }

  bool operator< (const Time& other) const
  {
    return m_Hour < other.m_Hour ||
                    (m_Hour == other.m_Hour && m_Minute < other.m_Minute) ||
      (m_Hour == other.m_Hour && m_Minute == other.m_Minute && m_Second < other.m_Second);
  }

  bool operator> (const Time& other) const
  {
    return other < *this;
  }

  bool operator<= (const Time& other) const
  {
    return *this < other || *this == other;
  }

  bool operator>= (const Time& other) const
  {
    return other <= *this;
  }
  
};

///
/// Клас, представящ среща
///
class Appointment
{
private:
  char* m_pDescription;
  Time m_Start, m_End;

public:
  Appointment() :
    m_pDescription(nullptr)
  {
    SetDescription("");
  }

  Appointment(const char* pDescription, const Time & Start, const Time & End) :
    m_pDescription(nullptr),
    m_Start(Start),
    m_End(End)
  {
    if (m_Start > m_End)
      std::swap(m_Start, m_End);

    SetDescription(pDescription);
  }

  Appointment(const Appointment& other) :
    m_pDescription(nullptr),
    m_Start(other.m_Start),
    m_End(other.m_End)
  {
    SetDescription(other.GetDescription());
  }

  ~Appointment()
  {
    delete[] m_pDescription;
  }

  Appointment & operator=(const Appointment & other)
  {
    if (this != &other)
      {
        SetDescription(other.GetDescription());
        m_Start = other.m_Start;
        m_End = other.m_End;
      }

    return *this;
  }

  void SetDescription(const char* pDescription)
  {
    delete[] m_pDescription;
    m_pDescription = new char[strlen(pDescription) + 1];
    strcpy(m_pDescription, pDescription);
  }

  char const* GetDescription() const
  {
    return m_pDescription;
  }

  Time GetStart() const
  {
    return m_Start;
  }

  Time GetEnd() const
  {
    return m_End;
  }

  Time GetLength() const
  {
    int Hour = GetEnd().GetHour() - GetStart().GetHour();
    int Minute = GetEnd().GetMinute() - GetStart().GetMinute();
    int Second = GetEnd().GetSecond() - GetStart().GetSecond();
    if (Second < 0)
      {
        Second += 60;
        Minute--;
      }
    if (Minute < 0)
      {
        Minute += 60;
        Hour--;
      }
    return Time(Hour, Minute, Second);
  }
};


// Този ред включва тестовете за задачата
#include "prob5-tests.h"

int main() {

  RunTests();
  
  return 0;
}
