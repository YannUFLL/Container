namespace ft
{
	template <typename T1, typename T2>
	class pair {
		public :
			typedef T1 first_type;
			typedef T2 second_type;
			pair(): first(), second() {}
			pair(const T1 &a, const T2 &b): first(a), second(b) {}

			template<typename U1, typename U2>
			pair(const pair<U1, U2>& p):first(T1(p.first)), second(T2(p.second)) {}
			~pair() {};
			friend void	swap(pair &a, pair &b)
			{
				pair c(a);
				a.first = b.first;
				a.second = b.second; 
				b.first = c.first;
				b.second = c.second;
			}
			pair& operator=(const pair &assign) 
			{
				if (this != &assign)
				{
					first = assign.first;
					second = assign.second;
				}
				return *this;
			}
			first_type first; 
			second_type second; 
	};
}