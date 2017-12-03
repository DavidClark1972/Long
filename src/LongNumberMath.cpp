#include "LongNumberMath.h"
#include "Constants.h"

using namespace std;

namespace LongNumber
{

#define ADDITIONAL_PRECISION 5
#define STANDARD_PRECISION 100

LongInteger abs(LongInteger& x)
{
    if (x < 0)
        return -x;

    return x;
}

LongDouble fabs(LongDouble& x)
{
    if (x < 0)
        return -x;

    return x;
}

LongDouble fmax(const LongDouble& x, const LongDouble& y)
{
    if (x > y)
        return x;
    else
        return y;
}

LongDouble fmin(const LongDouble& x, const LongDouble& y)
{
    if (x < y)
        return x;
    else
        return y;
}

LongInteger max(const LongInteger& x, const LongInteger& y)
{
    if (x > y)
        return x;
    else
        return y;
}

LongInteger min(const LongInteger& x, const LongInteger& y)
{
    if (x < y)
        return x;
    else
        return y;
}

LongDouble round(const LongDouble& x)
{
    if (x.IsInteger())
        return x;

    if (x.GetDecimals()[0] > '4')
    {
        LongDouble result;
        result.SetDigits(x.GetDigits());
        result++;
        result.SetSign(x.GetSign());

        return result;
    }
    else
    {
        LongDouble result;
        result.SetDigits(x.GetDigits());
        result.SetSign(x.GetSign());

        return result;
    }
}

LongDouble floor(const LongDouble& x)
{
    if (x.IsInteger())
        return x;

    if (x.GetSign())
    {
        LongDouble result;
        result.SetDigits(x.GetDigits());

        return result;
    }
    else
    {
        LongDouble result;
        result.SetDigits(x.GetDigits());
        result++;
        result.SetSign(false);

        return result;
    }
}

LongDouble ceil(const LongDouble& x)
{
    if (x.IsInteger())
        return x;

    if (x.GetSign())
    {
        LongDouble result;
        result.SetDigits(x.GetDigits());
        result++;

        return result;
    }
    else
    {
        LongDouble result;
        result.SetDigits(x.GetDigits());
        result.SetSign(false);

        return result;
    }
}

LongDouble trunc(const LongDouble& x)
{
    LongDouble result;
    result.SetDigits(x.GetDigits());
    result.SetSign(x.GetSign());

    return result;
}

LongDouble copysign(const LongDouble& x, const LongDouble& y)
{
    LongDouble result = x;
    result.SetSign(y.GetSign());

    return result;
}

bool isgreater(const LongDouble& x, const LongDouble& y)
{
    return x > y;
}

bool isgreaterequal(const LongDouble& x, const LongDouble& y)
{
    return x >= y;
}

bool isless(const LongDouble& x, const LongDouble& y)
{
    return x < y;
}

bool islessequal(const LongDouble& x, const LongDouble& y)
{
    return x <= y;
}

bool islessgreater(const LongDouble& x, const LongDouble& y)
{
    return x != y;
}

LongDouble fdim(const LongDouble& x, const LongDouble& y)
{
    if (x > y)
        return x - y;
    else
        return 0;
}

LongDouble fmod(const LongDouble& x, const LongDouble& y)
{
    LongDouble result = x;
    result /= y;
    result.SetDigits("0");
    result *= y;
    result.SetSign(x.GetSign());

    return result;
}

LongDouble modf(const LongDouble& x, LongInteger& intpart)
{
    LongDouble result = x;
    intpart = x;

    result.SetDigits("0");

    return result;
}


/**
 * e = 1 / 0! + 1 / 1! + 1 / 2! + 1 / 3! + 1 / 4! + ...
 */
LongDouble ComputeEulerNumber(size_t precision)
{
    if (precision < 6)
        precision = 6;

    LongDouble result = 2;
    result.SetPrecisionWithoutRounding(precision + ADDITIONAL_PRECISION);

    string str = "0.";
    for (size_t i = 0; i < precision; i++)
        str.push_back('0');
    str += "00001";

    const LongDouble limit = str;
    LongDouble partialResult = 1, divisionNumber = 1;
    partialResult.SetPrecisionWithoutRounding(precision + ADDITIONAL_PRECISION);
    divisionNumber.SetPrecisionWithoutRounding(precision + ADDITIONAL_PRECISION);

    while (1)
    {
        divisionNumber++;
        partialResult /= divisionNumber;
        if (partialResult < limit)
            break;
        result += partialResult;
    }

    result.SetPrecisionWithoutRounding(precision);

    return result;
}

bool isnegative(const LongDouble& x)
{
    return !x.GetSign();
}

bool ispositive(const LongDouble& x)
{
    return x.GetSign();
}

bool isnegative(const LongInteger& x)
{
    return !x.GetSign();
}

bool ispositive(const LongInteger& x)
{
    return x.GetSign();
}

bool signbit(const LongDouble& x)
{
    return x.GetSign();
}

bool signbit(const LongInteger& x)
{
    return x.GetSign();
}

LongDouble intpow(const LongDouble& x, const LongInteger& y)
{
    if (x == 0)
        return 0;
    if (y == 0 || x == 1)
        return 1;
    if (y == 1)
        return x;
    if (isnegative(y))
        return 1 / intpow(x, -y);

    LongInteger i, j = y, k;
    LongDouble result = 1, partialResult, square = x * x;

    result.SetPrecision(x.GetPrecision());
    partialResult.SetPrecision(x.GetPrecision());

    if (j % 2 == 1)
    {
        result = x;
        j--;
    }

    while (j != 0)
    {
        i = 4;
        k = 2;
        partialResult = square;
        while (i <= j)
        {
            k = i;
            partialResult *= partialResult;
            i += i;
        }
        j -= k;
        result *= partialResult;
    }

    return result;
}

} //end namespace

