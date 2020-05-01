#pragma once
template<class T1, class T2>
class DataCouple {
public:
	DataCouple(T1 letter = T1(), T2 frequency = T2()) :letter(letter), frequency(frequency) {}
	T1 letter;
	T2 frequency;
	template<class T1, class T2> 
		friend bool operator >(const DataCouple<T1, T2>& a, const DataCouple<T1, T2>& b);
	template<class T1, class T2> 
		friend bool operator <(const DataCouple<T1, T2>& a, const DataCouple<T1, T2>& b);
};
template<class T1, class T2> 
inline bool operator> (const DataCouple<T1, T2>& a, const DataCouple<T1, T2>& b) 
{
	return a.frequency > b.frequency;
}
template<class T1, class T2> 
inline bool operator< (const DataCouple<T1, T2>& a, const DataCouple<T1, T2>& b) 
{
	return a.frequency < b.frequency;
}