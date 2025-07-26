#pragma once

#include <D2D1Helper.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Math
{
	constexpr float DegToRad(float deg)
	{
		return static_cast<float>(deg * (M_PI / 180.0f));
	}

	constexpr float RadToDeg(float rad)
	{
		return static_cast<float>(rad * (180.0f / M_PI));
	}

	inline float Clamp(float value, float min, float max)
	{
		if (value < min)	return min;
		if (value > max)	return max;
		return value;
	}

	struct Point2F : public D2D1_POINT_2F
	{
		Point2F() = default;
		Point2F(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
		Point2F(const D2D1_POINT_2F& point)
		{
			this->x = point.x;
			this->y = point.y;
		}

		void operator=(const D2D1_POINT_2F& point)
		{
			this->x = point.x;
			this->y = point.y;
		}
	};

	class Vector2F : public D2D_VECTOR_2F
	{
	public:
		Vector2F() = default;
		Vector2F(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2F(const D2D_VECTOR_2F& vector)
		{
			this->x = vector.x;
			this->y = vector.y;
		}

		Vector2F(const Vector2F&) = default;

		Vector2F& operator=(const Vector2F&) = default;

		Vector2F(Vector2F&&) = default;
		Vector2F& operator=(Vector2F&&) = default;

		~Vector2F() = default;

		Vector2F operator+(const Vector2F& vector) const
		{
			return Vector2F(this->x + vector.x, this->y + vector.y);
		}

		Vector2F operator-(const Vector2F& vector) const
		{
			return Vector2F(this->x - vector.x, this->y - vector.y);
		}

		Vector2F operator*(float scalar) const
		{
			return Vector2F(this->x * scalar, this->y * scalar);
		}

		Vector2F operator/(float scalar) const
		{
			return Vector2F(this->x / scalar, this->y / scalar);
		}

		Vector2F& operator+=(const Vector2F& vector)
		{
			this->x += vector.x;
			this->y += vector.y;

			return *this;
		}

		Vector2F& operator-=(const Vector2F& vector)
		{
			this->x -= vector.x;
			this->y -= vector.y;

			return *this;
		}

		Vector2F& operator*=(float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;

			return *this;
		}

		Vector2F& operator/=(float scalar)
		{
			this->x /= scalar;
			this->y /= scalar;

			return *this;
		}

		bool operator==(const Vector2F& vector) const
		{
			return (this->x == vector.x && this->y == vector.y);
		}

		float Length() const
		{
			return sqrtf(this->x * this->x + this->y * this->y);
		}

		float LengthSquared() const
		{
			return (this->x * this->x + this->y * this->y);
		}

		float Normalize()
		{
			float length = Length();

			if (length > 0.0f)
			{
				float invLength = 1.0f / length;
				this->x *= invLength;
				this->y *= invLength;
			}

			return length;
		}

		const float Cross(const Vector2F& a) const
		{
			return x * a.y - y * a.x;
		}

		Vector2F Normalized() const
		{
			float length = Length();
			if (length > 0.0f)
			{
				float invLength = 1.0f / length;
				return Vector2F(x * invLength, y * invLength);
			}
			else
			{
				return Vector2F(0.0f, 0.0f); // Ȥ�� (1, 0) �� �⺻ ����
			}
		}

		Vector2F operator-() const 
		{
			return Vector2F(-x, -y);
		}

		bool operator<(const Vector2F& other) const
		{
			return (x < other.x) || (x == other.x && y < other.y);
		}

		bool operator>(const Vector2F& other) const
		{
			return other < *this;
		}
	};

	inline Vector2F Clamp(Vector2F value, Vector2F min, Vector2F max)
	{
		if (value < min)	return min;
		if (value > max)	return max;
		return value;
	}

	inline int IsLeft(D2D1_POINT_2F P0, D2D1_POINT_2F P1, D2D1_POINT_2F P2)
	{
		return static_cast<int>(((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y)));
	}

	int cn_PnPoly(D2D1_POINT_2F P, std::vector<D2D1_POINT_2F> V, int n);
	int wn_PnPoly(D2D1_POINT_2F P, std::vector<D2D1_POINT_2F> V, int n);

	class Edge
	{
	public:
		Edge() = default;
		Edge(int a, int b)
		{
			if (a < b)
			{
				this->a = a;
				this->b = b;
			}
			else
			{
				this->a = b;
				this->b = a;
			}
		}

		const bool operator==(const Edge& x) const
		{
			return a == x.a && b == x.b;
		}
		const bool operator<(const Edge& x) const
		{
			if (a == x.a) return b < x.b;
			return a < x.a;
		}

		int a;
		int b;
	};


	class Triangle
	{
	public:
		Triangle() { a = b = c = 0; }
		Triangle(int a, int b, int c)
		{
			this->a = a;
			this->b = b;
			this->c = c;
		}

		const bool operator==(const Triangle& x) const
		{
			return a == x.a && b == x.b && c == x.c;
		}

		int a;
		int b;
		int c;
	};

	bool is_circum(Triangle cur, int i, std::vector<Vector2F>& point);
}


