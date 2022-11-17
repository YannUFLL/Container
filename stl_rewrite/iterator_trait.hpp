#ifndef ITERATOR_TRAIT
#define ITERATOR_TRAIT
namespace ft
{

template <typename IT>
    struct iterator_trait 
    {
        typedef typename IT::difference_type difference_type;
        typedef typename IT::value_type value_type;
        typedef typename IT::pointer pointer;
        typedef typename IT::reference reference;
        typedef typename IT::iterator_category iterator_category;

    };

template <typename IT>
    struct iterator_trait<IT *>
    {
        typedef std::ptrdiff_t difference_type;
        typedef IT value_type;  
        typedef IT* pointer; 
        typedef IT& reference ;
        typedef std::random_access_iterator_tag iterator_category;
    };

template <typename IT>
    struct iterator_trait<const IT *>
    {
        typedef std::ptrdiff_t difference_type;
        typedef IT value_type;  
        typedef const IT* pointer; 
        typedef const IT& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };
}



#endif