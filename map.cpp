#include <map>
#include <iostream>
using namespace std;
template <typename K, typename V>
class interval_map
{
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val
	interval_map(V const &val)
		: m_valBegin(val)
	{

	}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.

	void assign(K const &keyBegin, K const &keyEnd, V const &val)
	{

		if (!(keyBegin < keyEnd))
		{
			return;
		}

		if (m_map.size() == 0)
		{
			if (val == m_valBegin)
			{
				return;
			}
		}

		auto it = m_map.lower_bound(keyBegin);

		while (it != m_map.end() && it->first < keyEnd)
		{
			it = m_map.erase(it);
		}

		m_map.insert({keyEnd, val});
		m_map.insert(std::make_pair(keyBegin, val));
	}

	// look-up of the value associated with key
	V const &operator[](K const &key) const
	{
		auto it = m_map.upper_bound(key);
		if (it == m_map.begin())
		{
			return m_valBegin;
		}
		else
		{
			return (--it)->second;
		}
	}
};
int main()
{
	// Create an instance of interval_map
	interval_map<int, char> *t = new interval_map<int, char>('B');

	// Assign values to intervals
	t->assign(1, 3, 'B');
	t->assign(3, 8, 'Z');
	t->assign(6, 9, 'C');

	// Test operator[]
	for (int i = 0; i < 100; ++i)
	{
		std::cout << "Value at key " << i << ": " << (*t)[i] << std::endl;
	}

	delete t; // Don't forget to delete dynamically allocated memory
	return 0;
}