#include <math.h>
#include "Vector2.h"

// メソッド定義
Vector2::Vector2()
{
	*this = Vector2::Zero;
}

Vector2::Vector2(const Vector2& other)
{
	*this = other;
}

template<typename NUM>
Vector2::Vector2(const NUM& x, const NUM& y)
{
	*this = Vector2(x, y);
}

template <typename NUM>
void Vector2::Set(NUM x, NUM y) {
	*this = Vector2(x, y);
}

void Vector2::Set(Vector2 other) {
	*this = other;
}

Vector2 Vector2::Normalized() const
{
	if (Magnitude() == 0) {
		// TODO:ゼロベクトルの時に正規化しようとした場合のエラー処理
	}
	return *this / Magnitude;
}

double Vector2::Magnitude()const 
{
	return sqrtf((x * x) + (y * y));
}

// メンバ演算子オーバーロード
inline Vector2 Vector2::operator+()const
{
	return Vector2(x,y);
}

inline Vector2 Vector2::operator-()const
{
	return Vector2(-x, -y);
}

inline Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

inline double& Vector2::operator[](const int& index)
{
	if (index == 0) { return x; }
	if (index == 1) { return y; }
	// TODO:0か1以外が渡されたときのエラー処理
}

// メンバでない演算子オーバーロード
inline bool operator== (const Vector2& left, const Vector2& right) 
{
	if (left.x == right.x && left.y == right.y) 
	{
		return true;
	}
	return false;
}

inline bool operator!= (const Vector2& left, const Vector2& right)
{
	if (left == right) 
	{
		return false;
	}
	return true;
}

inline Vector2 operator+(const Vector2& left, const Vector2& right)
{
	double tx = left.x + right.x;
	double ty = left.y + right.y;
	return Vector2(tx, ty);
}

inline Vector2 operator-(const Vector2& left, const Vector2& right)
{
	double tx = left.x - right.x;
	double ty = left.y - right.y;
	return Vector2(tx, ty);
}

template <typename NUM>
inline Vector2 operator*(const Vector2& vector, const NUM& num)
{
	double tx = vector.x * num;
	double ty = vector.y * num;
	return Vector2(tx, ty);
}

template <typename NUM>
inline Vector2 operator*( const NUM num,const Vector2& vector)
{
	double tx = vector.x * num;
	double ty = vector.y * num;
	return Vector2(tx, ty);
}

template <typename NUM>
inline Vector2 operator/(const Vector2& vector, const NUM& num)
{
	if (vector == Vector2::Zero) {
		// TODO::ゼロベクトルの場合のエラー処理
	}
	double tx = vector.x / num;
	double ty = vector.y / num;
	return Vector2(tx, ty);
}

inline Vector2& operator+=(Vector2& left, const Vector2& right)
{
	return left = left + right;
}

inline Vector2& operator-=(Vector2& left, const Vector2& right)
{
	return left = left - right;
}

template <typename NUM>
inline Vector2& operator*=(Vector2& vector, const NUM& num)
{
	return vector = vector * num;
}

template <typename NUM>
inline Vector2& operator/=(Vector2& vector, const NUM& num)
{
	if (vector == Vector2::Zero) {
		// TODO::ゼロベクトルの場合のエラー処理
	}
	return vector = vector / num;
}

// 静的変数の実体定義
const Vector2 Vector2::One = Vector2(1, 1);
const Vector2 Vector2::Up = Vector2(0, 1);
const Vector2 Vector2::Down = Vector2(0, -1);
const Vector2 Vector2::Right = Vector2(1, 0);
const Vector2 Vector2::Left = Vector2(-1, 0);
const Vector2 Vector2::Zero = Vector2(0, 0);

