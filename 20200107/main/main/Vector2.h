#pragma once

struct Vector2
{
	Vector2();
	template <typename NUM>
	Vector2(const NUM& x, const NUM& y);
	Vector2(const Vector2& other);

	double x;
	double y;

	// �ȉ��֐���`
	//Point(double x, double y) : x(x), y(y){}
	template <typename NUM>
	void Set(NUM x, NUM y);
	void Set(Vector2 other);

	Vector2 Normalized() const;
	double Magnitude() const;

	/*	�ǉ��\��֐�
	�EVector3�ɂ����l��Ԃ��֐�
	�E�����̍ő�l���󂯎��ő�l��蒷�������ꍇ�͍ő�l�܂Ő؂�l�߂�֐�
	*/
	
	// �����o���Z�q�I�[�o�[���[�h
	inline Vector2 operator+() const;
	inline Vector2 operator-() const;
	inline Vector2& operator=	(const Vector2& other);
	inline double& operator[]	(const int& index);

	/* �ǉ��\�艉�Z�q�I�[�o�[���[�h
	Vector3�ւ̃L���X�g���Z�q
	*/

	// �ÓI�ϐ�
	const static Vector2 One;
	const static Vector2 Up;
	const static Vector2 Down;
	const static Vector2 Right;
	const static Vector2 Left;
	const static Vector2 Zero;

};

// ���\�b�h�łȂ�Vector2�֘A�̊֐��錾
/*	�ǉ��\��֐�
�E��_�Ԃ̊p�x��Ԃ��֐�
�E��̃x�N�g���̓��ς�Ԃ��֐�
�E���₷���悤�����񉻂����l��Ԃ��֐�
*/


// �����o�łȂ�Vector2�֘A�̉��Z�q�I�[�o�[���[�h�錾
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