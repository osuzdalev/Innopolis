#ifndef UNTITLED_FIND_H
#define UNTITLED_FIND_H
/**
 *
 * @tparam Typename
 * @tparam Pointer to Typename
 * @param first
 * @param beyond
 * @param compare function
 * @return Pointer to result
 *
 *Type T should support operator!=().
 *Type P should support operator*();  this operator should return a value of type T.
 *Type P should support operator++(); the result should denote the next element of the data structure.
 *Type P should support operator--(); the result should denote the next element of the data structure.
 *Type P should support operator-(); the result should denote the next element of the data structure.
 *Type P should support operator!=().
 *
 *
 */
template < typename T, typename P >
P find ( P first, P beyond, bool (*c)(T))
{
    P p = beyond - 1;
    while ( p != first - 1 && !c(*p)) {
        p--;
    }
    return p;
}

#endif //UNTITLED_FIND_H
