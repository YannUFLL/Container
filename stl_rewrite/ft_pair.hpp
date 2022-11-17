namespace ft
{
    template <typename T1, typename T2>
    class pair {
        public :
            typedef T1 first_type;
            typedef T2 second_type;
            pair(): _first(), _second() {}
            pair(const T1 &a): _first(a), _second() {}
            pair(const T1 &a, const T2 &b): _first(a), _second(b) {}
            pair(const pair<T1, T2>& copy): _first(copy._first), _second(copy._second) {}
            ~pair() {};
            friend void    swap(ft::pair<T1,T2> &a, ft::pair<T1,T2> &b)
            {
                ft::pair<T1, T2> c(a);
                a._first = b._first;
                a._second = b._second; 
                b._first = c._first;
                b._second = c._second;
            }
            pair& operator=(const pair &assign) 
            {
                if (this != assign)
                {
                    _first = assign._first;
                    _second = assign._second;
                }
            }
            first_type _first; 
            second_type _second; 
    };

}