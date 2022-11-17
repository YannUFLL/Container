

template <bool VALUE, typename ISFALSE, typename ISTRUE>
struct choose_type {};

template <typename ISFALSE, typename ISTRUE>
struct choose_type<true, ISFALSE, ISTRUE>
{
    typedef ISTRUE type;
};

template <typename ISFALSE, typename ISTRUE>
struct choose_type<false, ISFALSE, ISTRUE>
{
    typedef ISFALSE type;
};
