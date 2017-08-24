/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Program: изберете коректното: Информатика, Информационни системи, Компютърни науки, Софтуерно инженерство
// Date: 25.08.2017
//

#include <cstring>

///
/// Клас представящ дата
///
class Date
{
private:
  int m_Day;
  int m_Month;
  int m_Year;

public:

  Date(int Day = 0, int Month = 0, int Year = 0) :
    m_Day(Day),
    m_Month(Month),
    m_Year(Year)
  {
    bool isValid = true;

    if (m_Day < 1 || m_Day > 31)
      isValid = false;

    if (m_Day == 31)
      {
        switch (m_Month) {
        case 4:
        case 6:
        case 9:
        case 11: isValid = false;
        }
      }

    if (isValid && m_Month == 2)
      {
        bool isLeap = (m_Year % 4 == 0 && m_Year % 100 != 0) || m_Year % 400 == 0;
        isValid = m_Day <= 28 || isLeap && m_Day == 29;
      }

    if (!isValid)
      {
        m_Day = m_Month = m_Year = 0;
      }
  }

  int GetDay() const
  {
    return m_Day;
  }

  int GetMonth() const
  {
    return m_Month;
  }

  int GetYear() const
  {
    return m_Year;
  }

  bool operator==(const Date& other) const
  {
    return m_Day == other.m_Day &&
      m_Month == other.m_Month &&
      m_Year == other.m_Year;
  }

  bool operator!=(const Date& other) const
  {
    return !(*this == other);
  }

  bool operator< (const Date& other) const
  {
    return m_Year < other.m_Year ||
                    (m_Year == other.m_Year && m_Month < other.m_Month) ||
      (m_Year == other.m_Year && m_Month == other.m_Month && m_Day < other.m_Day);
  }

  bool operator> (const Date& other) const
  {
    return other < *this;
  }

  bool operator<= (const Date& other) const
  {
    return *this < other || *this == other;
  }

  bool operator>= (const Date& other) const
  {
    return other <= *this;
  }
};

///
/// Клас представящ студент
///
class Student
{
private:
  char* m_pName;

  Date m_DateOfBirth;

public:
  Student() :
    m_pName(nullptr),
    m_DateOfBirth(1, 1, 2017)
  {
    SetName("");
  }

  Student(const char* pName, const Date & DateOfBirth) :
    m_pName(nullptr),
    m_DateOfBirth(DateOfBirth)
  {
    SetName(pName);
  }

  Student(const Student& other) :
    m_pName(nullptr),
    m_DateOfBirth(other.m_DateOfBirth)
  {
    SetName(other.GetName());
  }

  ~Student()
  {
    delete[] m_pName;
  }

  Student & operator=(const Student & other)
  {
    if (this != &other)
      {
        SetName(other.GetName());
        m_DateOfBirth = other.m_DateOfBirth;
      }

    return *this;
  }

  void SetName(const char* pName)
  {
    delete[] m_pName;
    m_pName = new char[strlen(pName) + 1];
    strcpy(m_pName, pName);
  }

  const char* GetName() const
  {
    return m_pName;
  }

  const Date GetBirthDate() const
  {
    return m_DateOfBirth;
  }

  bool operator <(const Student & other) const
  {
    int comp = strcmp(m_pName, other.m_pName);

    return comp < 0 ||
                  (comp == 0 && m_DateOfBirth < other.m_DateOfBirth);
  }
};


// Този ред включва тестовете за задачата
#include "prob1-tests.h"

int main() {

  RunTests();

  return 0;
}
