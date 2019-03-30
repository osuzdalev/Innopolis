

#ifndef HW5_GREATER_THEN_H
#define HW5_GREATER_THEN_H
template<typename T, T N>
struct greater_then
{
    bool operator()(T a) const { return a > N;}
};
#endif //HW5_GREATER_THEN_H
