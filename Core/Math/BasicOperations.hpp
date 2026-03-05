#pragma once

#include <cstddef>
#include <cmath>
#include <array>

template<typename T, std::size_t N>
struct VectorNt : public std::array<T, N>
{
    template<typename Scalar>
    VectorNt operator*(const Scalar scalar) const
    {
        VectorNt result{};
        for (std::size_t i = 0; i < N; ++i)
            result[i] = (*this)[i] * scalar;
        return result;
    }

    // note: scalar * vector is a free function below


    VectorNt operator/(const double scalar) const
    {
        VectorNt result{};
        for (std::size_t i = 0; i < N; ++i)
            result[i] = (*this)[i] / scalar;
        return result;
    }

    VectorNt operator+(const VectorNt& other) const
    {
        VectorNt result{};
        for (std::size_t i = 0; i < N; ++i)
            result[i] = (*this)[i] + other[i];
        return result;
    }

    VectorNt operator-(const VectorNt& other) const
    {
        VectorNt result{};
        for (std::size_t i = 0; i < N; ++i)
            result[i] = (*this)[i] - other[i];
        return result;
    }

    bool operator==(const VectorNt& other) const
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            if ((*this)[i] != other[i])
                return false;
        }
        return true;
    }

    bool operator!=(const VectorNt& other) const
    {
        return !(*this == other);
    }

    T Dot(const VectorNt& other) const
    {
        T result{};
        for (std::size_t i = 0; i < N; ++i)
            result += (*this)[i] * other[i];
        return result;
    }

    T Magnitude() const
    {
        return std::sqrt(this->Dot(*this));
    }

    VectorNt Cross(const VectorNt& other) const requires (N == 3)
    {
        return VectorNt{
            (*this)[1] * other[2] - (*this)[2] * other[1],
            (*this)[2] * other[0] - (*this)[0] * other[2],
            (*this)[0] * other[1] - (*this)[1] * other[0]
        };
    }

    T Cross(const VectorNt& other) const requires (N == 2)
    {
        return (*this)[0] * other[1] - (*this)[1] * other[0];
    }
};

// free-function for scalar * vector (commutative multiplication)

template<typename T, std::size_t N, typename Scalar>
VectorNt<T, N> operator*(const Scalar scalar, const VectorNt<T, N>& vec)
{
    return vec * scalar;
}

using Vector2d = VectorNt<double, 2>;