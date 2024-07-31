/*
    flippedarray.h

    Class declaration for FlippedArray.
*/

#ifndef FLIPPEDARRAY_H
#define FLIPPEDARRAY_H

#include <algorithm>
#include <array>
#include <stdexcept>

/*
    FlippedArray

    This is a class that subclasses std::array but flips the access operator so that it always returns the opposite element specified.
    For instance, in a hypothetical array of 10 elements, trying to access the element at position 0 will return the element at position 9.
    This is useful for changing the origin point of 2D arrays from the top left to the bottom left by using a FlippedArray for the Y array.
*/
template<typename T, std::size_t N>
class FlippedArray : public std::array<T, N>
{
public:
    /*
        Default constructor.
    */
    FlippedArray() = default;

    /*
        Initializer list constructor.
        Takes initializer list and flips it before storing.
    */
    FlippedArray(std::initializer_list<T> init)
    {
        if (init.size() != N)
        {
            throw std::invalid_argument("Initializer list size must match array size");
        }
        std::copy(init.begin(), init.end(), this->begin());
    }

    /*
        Override operator[] to return the opposite element as specified.
    */
    T& operator[](std::size_t index)
    {
        if (index >= N)
            throw std::out_of_range("Index out of range");

        return std::array<T, N>::operator[](N - 1 - index);
    }

    /*
        Const override operator[].
    */
    const T& operator[](std::size_t index) const
    {
        if (index >= N)
            throw std::out_of_range("Index out of range");

        return std::array<T, N>::operator[](N - 1 - index);
    }
};

#endif // FLIPPEDARRAY_H
