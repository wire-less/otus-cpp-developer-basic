#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <stdexcept>

class Statistics {
public:
    virtual ~Statistics() = default;
    // Задает следующее значение из входной последовательности
    virtual void update(double next) = 0;
    // Возвращает величину статистической характеристики.
    // Выбрасывает std::logic_error, если оценить характеристику невозможно
    virtual double eval() const = 0;
    // Возвращает название статистики
    virtual const char* name() const = 0;
};


// Реализовать
class Min : public Statistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()}
	{
	}

	void update(double next) override
	{
		if (next < m_min)
		{
			m_min = next;
		}
	}

	double eval() const override
	{
      	if (m_min == std::numeric_limits<double>::max()) {
          throw std::logic_error("Cannot calculate: empty sequence.");
    }      
		else return m_min;
	}

	const char *name() const override
	{
    return "Min";
	}

private:
	double m_min;
};


class Max : public Statistics
{
public:
	Max() : m_max{std::numeric_limits<double>::lowest()}
	{
	}

	void update(double next) override
	{
		if (next > m_max)
		{
			m_max = next;
		}
	}

	double eval() const override
	{
    if (m_max == std::numeric_limits<double>::lowest()) {
      throw std::logic_error("Cannot calculate: empty sequence.");
    }
	  else return m_max;
	}

	const char *name() const override
	{
		return "Max";
	}

private:
	double m_max;
};


class Mean : public Statistics {
public:
	Mean() : m_counter{0}, m_sum{0.0}
	{
	}

	void update(double next) override
	{
		++m_counter;
		m_sum += next;
	}

	double eval() const override
	{
		if (m_counter == 0)
		{
		  throw std::logic_error("Cannot calculate: empty sequence.");
		}

		else return static_cast<double>(m_sum / m_counter);
	}

	const char *name() const override
	{
		return "Mean";
	}

private:
	int m_counter;
	double m_sum;
};


class StandardDeviation : public Statistics
{
public:
	StandardDeviation() = default;

	void update(double next) override
	{
		// заполнить копию вводимой последовательности по-элементно до EOF
		m_seq.push_back(next);
	}

	double eval() const override
	{
		if (m_seq.empty())
		{
		  throw std::logic_error("Cannot calculate: empty sequence.");
		}

        else {
		double sum{0.0};

		// вычислить среднее арифметическое
		for (double nextVal : m_seq)
		{
			sum += nextVal;
		}
		double mean = static_cast<double>(sum / m_seq.size());

		// вычислить среднее квадратическое отклонение
		sum = 0.0;
		for (double nextVal : m_seq)
		{
			double deviation = nextVal - mean;
			sum += pow(deviation, 2);
		}
		// и возвратить результат метода
		return sqrt(static_cast<double>(sum / m_seq.size()));
	  }
    }

	const char *name() const override
	{
		return "Standard Deviation";
	}

private:
	std::vector<double> m_seq;
};
