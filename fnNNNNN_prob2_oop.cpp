/////////////////////////////////////////////////////////////
//
// Author: Иван Иванов
// FN: 80000
// Program: Компютърни науки
// Date: 25.08.2017
//

///
/// Клас, представящ интервал
///
class Interval
{
private:
  int m_Left, m_Right;

public:

  Interval(int left = 0, int right = 1) : m_Left(left), m_Right(right)
  {
    if (left > right)
    {
      m_Left = 0;
      m_Right = 1;
    }
  }

  int GetLeft() const
  {
    return m_Left;
  }

  int GetRight() const
  {
    return m_Right;
  }

  bool Contains(int x) const
  {
    return GetLeft() <= x && x <= GetRight();
  }

  bool operator==(const Interval& other) const
  {
    return
      GetLeft()  == other.GetLeft() &&
      GetRight() == other.GetRight();
  }

  bool operator!=(const Interval& other) const
  {
    return !(*this == other);
  }
  
  bool operator<= (const Interval& other) const
  {
    return other.GetLeft() <= GetLeft() && GetRight() <= other.GetRight();
  }
  
  bool operator> (const Interval& other) const
  {
    return other < *this;
  }
  
  bool operator< (const Interval& other) const
  {
    return *this <= other && *this != other;
  }
  
  bool operator>= (const Interval& other) const
  {
    return other <= *this;
  }

};

///
/// Клас, представящ множество от интервали
///
class IntervalSet
{
private:
  Interval* m_Intervals;
  int m_Size;

  void copy(Interval const* intervals, int size)
  {
    m_Size = size;
    m_Intervals = new Interval[m_Size];

    for(int i = 0; i < m_Size; i++)
      m_Intervals[i] = intervals[i];
  }

  void erase()
  {
    delete[] m_Intervals;
  }

public:

  IntervalSet() : m_Size(1), m_Intervals(new Interval[1])
  {
  }

  IntervalSet(Interval const* intervals, int size)
  {
    if (size < 0)
      size = 1;

    copy(intervals, size);
  }

  IntervalSet(IntervalSet const& other)
  {
    copy(other.m_Intervals, other.m_Size);
  }

  IntervalSet& operator=(IntervalSet const& other)
  {
    if (this != &other)
    {
      erase();
      copy(other.m_Intervals, other.m_Size);
    }
    return *this;
  }

  ~IntervalSet()
  {
    delete[] m_Intervals;
  }

  int GetSize() const
  {
    return m_Size;
  }

  Interval const* GetIntervals() const
  {
    return m_Intervals;
  }

  int CountSubsets(Interval const& i) const
  {
    int count = 0;
    for(int j = 0 ; j < GetSize(); j++)
      if (GetIntervals()[j] <= i)
        count++;

    return count;
  }
};


// Този ред включва тестовете за задачата
#include "prob2-tests.h"

int main() {

  RunTests();
  
  return 0;
}
