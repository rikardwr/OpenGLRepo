
#ifndef vector_h
#define vector_h

#include <cmath>




template <typename Z>
class Vector2 {
public:
    Z x;
    Z y;
    Vector2();
    Vector2(Z val);
    Vector2(Z a, Z b);
    Vector2(const Vector2& a);
    Vector2& operator=(const Vector2& a);
    void normalized();
    void scaling(Z a);
    void add(const Vector2& a);
    void substraction(const Vector2& a);
    Z dot_product(const Vector2& a);
    Z mod();
    void compare(Z& a, Z& b);
    void compare(Vector2& a);

};


template<typename Z>
Vector2<Z>::Vector2()
{
	x = y = 0;
}

template<typename Z>
 Vector2<Z>::Vector2(Z val)
{
	x = y = val;
	
}

template<typename Z>
 Vector2<Z>::Vector2(Z a, Z b)
{
	x = a;
	y = b;
	
}

template<typename Z>
 Vector2<Z>::Vector2(const Vector2& a)
{
	x = a.x;
	y = a.y;
	
}

template<typename Z>
Vector2<Z>& Vector2<Z>::operator=(const Vector2& a)
{
	x = a.x;
	y = a.y;
	return *this;
}

template<typename Z>
 void Vector2<Z>::normalized()
{
	Z tmp = sqrt(x * x + y * y);
	if (tmp == 0)
		return;
	x /= tmp;
	y /= tmp;
}

template<typename Z>
 void Vector2<Z>::scaling(Z a)
{
	x *= a;
	y *= a;
}

template<typename Z>
 void Vector2<Z>::add(const Vector2& a)
{
	x += a.x;
	y += a.y;
}

template<typename Z>
 void Vector2<Z>::substraction(const Vector2& a)
{
	x -= a.x;
	y -= a.y;
	
}

template<typename T>
 T Vector2<T>::dot_product(const Vector2& a)
{
	return (x * a.x + y * a.y);
	
}

template<typename Z>
 Z Vector2<Z>::mod()
{
    return sqrt(x * x + y * y);
}

template<typename Z>
 void Vector2<Z>::compare(Z& a, Z& b)
{
	a = x;
	b = y;
}

template<typename Z>
 void Vector2<Z>::compare(Vector2& a)
{
	a.x = x;
	a.y = y;
	
}

#endif // VECTOR_H