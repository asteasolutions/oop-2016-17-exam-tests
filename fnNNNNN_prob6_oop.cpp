/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Program: изберете коректното: Информатика, Информационни системи, Компютърни науки, Софтуерно инженерство
// Date: 25.08.2017
//

///
/// Клас, представящ хронометър
///
class Chronometer
{
private:
  int m_Hour, m_Minute, m_Second;

public:

  Chronometer(int Hour = 0, int Minute = 0, int Second = 0) :
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

  bool operator< (const Chronometer& other) const
  {
    return m_Hour < other.m_Hour ||
                    (m_Hour == other.m_Hour && m_Minute < other.m_Minute) ||
      (m_Hour == other.m_Hour && m_Minute == other.m_Minute && m_Second < other.m_Second);
  }

  Chronometer& operator+=(int N)
  {
    m_Second += N;
    m_Minute += m_Second / 60;
    m_Hour += m_Minute / 60;
    m_Minute %= 60;
    m_Second %= 60;
    return *this;
  }

  Chronometer& operator++()
  {
    return (*this += 1);
  }

  Chronometer operator++(int)
  {
    Chronometer old = *this;
    ++*this;
    return old;
  }
};

///
/// Клас, представящ атлет
///
class Athlete
{
private:
  Chronometer* m_Chronometers;
  int m_Size;

  void copy(Chronometer const* Chronometers, int size)
  {
    m_Size = size;
    m_Chronometers = new Chronometer[m_Size];

    for(int i = 0; i < m_Size; i++)
      m_Chronometers[i] = Chronometers[i];
  }

  void erase()
  {
    delete[] m_Chronometers;
  }

public:

  Athlete() : m_Size(0), m_Chronometers(nullptr)
  {
  }

  Athlete(Chronometer const* Chronometers, int size)
  {
    if (size < 0)
    {
      size = 0;
      m_Chronometers = nullptr;
    }
    else
      copy(Chronometers, size);
  }

  Athlete(Athlete const& other)
  {
    copy(other.m_Chronometers, other.m_Size);
  }

  Athlete& operator=(Athlete const& other)
  {
    if (this != &other)
    {
      erase();
      copy(other.m_Chronometers, other.m_Size);
    }
    return *this;
  }

  ~Athlete()
  {
    delete[] m_Chronometers;
  }

  int GetSize() const
  {
    return m_Size;
  }

  Chronometer const* GetChronometers() const
  {
    return m_Chronometers;
  }

  Chronometer GetBestTime() const
  {
    if (GetSize() == 0)
      return Chronometer();

    int bestIndex = 0;
    for(int j = 1 ; j < GetSize(); j++)
      if (GetChronometers()[j] < GetChronometers()[bestIndex])
        bestIndex = j;

    return GetChronometers()[bestIndex];
  }
};


// Този ред включва тестовете за задачата
#include "prob6-tests.h"

int main() {
  RunTests();

  return 0;
}
