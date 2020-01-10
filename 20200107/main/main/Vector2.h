#pragma once

struct Vector2
{
	Vector2();
	template <typename NUM>
	Vector2(const NUM& x, const NUM& y);
	Vector2(const Vector2& other);

	double x;
	double y;

	// 以下関数定義
	//Point(double x, double y) : x(x), y(y){}
	template <typename NUM>
	void Set(NUM x, NUM y);
	void Set(Vector2 other);

	Vector2 Normalized() const;
	double Magnitude() const;

	/*	追加予定関数
	・Vector3にした値を返す関数
	・長さの最大値を受け取り最大値より長かった場合は最大値まで切り詰める関数
	*/
	
	// メンバ演算子オーバーロード
	inline Vector2 operator+() const;
	inline Vector2 operator-() const;
	inline Vector2& operator=	(const Vector2& other);
	inline double& operator[]	(const int& index);

	/* 追加予定演算子オーバーロード
	Vector3へのキャスト演算子
	*/

	// 静的変数
	const static Vector2 One;
	const static Vector2 Up;
	const static Vector2 Down;
	const static Vector2 Right;
	const static Vector2 Left;
	const static Vector2 Zero;

};

// メソッドでないVector2関連の関数宣言
/*	追加予定関数
・二点間の角度を返す関数
・二つのベクトルの内積を返す関数
・見やすいよう文字列化した値を返す関数
*/


// メンバでないVector2関連の演算子オーバーロード宣言
inline bool operator==	(const Vector2& left, const Vector2& right);
inline bool operator!=	(const Vector2& left, const Vector2& right);

inline Vector2 operator+	(const Vector2& left, const Vector2& right);
inline Vector2 operator-	(const Vector2& left, const Vector2& right);
template <typename NUM>
inline Vector2 operator*	(const Vector2& vector, const NUM& num)	;
template <typename NUM>
inline Vector2 operator*	(const NUM num,const Vector2& vector)	;
template <typename NUM>	
inline Vector2 operator/	(const Vector2& vector, const NUM& num)	;

inline Vector2& operator-=	(Vector2& left, const Vector2& right)	;
inline Vector2& operator+=	(Vector2& left, const Vector2& right)	;
template <typename NUM>
inline Vector2 operator*=	(Vector2& vector, const NUM& num);
template <typename NUM>
inline Vector2 operator/=	(Vector2& vector, const NUM& num);

/*
*/