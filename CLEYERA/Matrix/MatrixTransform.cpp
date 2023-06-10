#include"MatrixTransform.h"




MatrixTransform::MatrixTransform()
{

}

MatrixTransform::~MatrixTransform()
{

}

#pragma region 二次元行列

#pragma region +-*
Matrix2x2 MatrixTransform::Add(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 result;
	result.m[0][0] = matrix1.m[0][0] + matrix2.m[0][0];
	result.m[0][1] = matrix1.m[0][1] + matrix2.m[0][1];
	result.m[1][0] = matrix1.m[1][0] + matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][1] + matrix2.m[1][1];

	return result;
}

Matrix2x2 MatrixTransform::Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 result;
	result.m[0][0] = matrix1.m[0][0] - matrix2.m[0][0];
	result.m[0][1] = matrix1.m[0][1] - matrix2.m[0][1];
	result.m[1][0] = matrix1.m[1][0] - matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][1] - matrix2.m[1][1];

	return result;
}

Matrix2x2 MatrixTransform::Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 result;

	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0];
	result.m[0][1] = matrix1.m[0][1] * matrix2.m[0][1];
	result.m[1][0] = matrix1.m[1][0] * matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][1] * matrix2.m[1][1];
	return result;
}

#pragma endregion

#pragma region 回転

Matrix2x2 MatrixTransform::MakeRotate2x2Matrix(float theta)
{
	Matrix2x2 restult;
	restult.m[0][0] = std::cosf(theta);
	restult.m[0][1] = std::sinf(theta);
	restult.m[1][0] = -std::sinf(theta);
	restult.m[1][1] = std::cosf(theta);
	return restult;
}

#pragma endregion 

#pragma region 変換

Matrix2x2 MatrixTransform::Inverse(Matrix2x2 matrix)
{
	Matrix2x2 result;
	float determinant = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];
	assert(determinant != 0.0f);
	float deteminanRacp = 1.0f / determinant;
	result.m[0][0] = matrix.m[1][1] * deteminanRacp;
	result.m[0][1] = -matrix.m[0][1] * deteminanRacp;
	result.m[1][0] = -matrix.m[1][0] * deteminanRacp;
	result.m[1][1] = matrix.m[0][0] * deteminanRacp;
	return result;
}

Matrix2x2 MatrixTransform::Transpose(Matrix2x2 matrix)
{
	Matrix2x2 result;
	result.m[0][0] = matrix.m[0][0];
	result.m[0][1] = matrix.m[1][0];
	result.m[1][0] = matrix.m[0][1];
	result.m[1][1] = matrix.m[1][1];
	return result;

}

#pragma endregion

#pragma endregion


#pragma region 三次元行列

#pragma region +-*

Matrix3x3 MatrixTransform::Add(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 result;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			result.m[row][col] = m1.m[row][col] + m2.m[row][col];
		}
	}

	return result;
}

Matrix3x3 MatrixTransform::Subract(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 result;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			result.m[row][col] = m1.m[row][col] - m2.m[row][col];
		}
	}

	return result;
}

Matrix3x3 MatrixTransform::Multiply(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 result;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			result.m[row][col] = 0.0f;

			for (int k = 0; k < 3; k++) {
				result.m[row][col] += m1.m[row][k] * m2.m[k][col];
			}
		}
	}

	return result;
}



#pragma endregion 

#pragma region 移動・回転・大きさ

Matrix3x3 MatrixTransform::MakeTranslate3x3Matrix(Vector2 translate)
{
	Matrix3x3 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;

	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;
	return result;

}

Matrix3x3 MatrixTransform::MakeRotate3x3Matrix(float theta)
{
	Matrix3x3 result;

	result.m[0][0] = std::cosf(theta);
	result.m[0][1] = std::sinf(theta);
	result.m[0][2] = 0.0f;

	result.m[1][0] = -std::sinf(theta);
	result.m[1][1] = std::cosf(theta);
	result.m[1][2] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	return result;
}

Matrix3x3 MatrixTransform::MakeScaleMatrix(const Vector2 scale)
{
	Matrix3x3 result;
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 0.0f;
	

	return result;
}

#pragma endregion

#pragma region 行列変換

Matrix3x3 MatrixTransform::MakeAffineMatrix(const Vector2 translate, float radian, const Vector2 scale)
{
	Matrix3x3 result;

	//S
	Matrix3x3 scaleMatrix;
	scaleMatrix = MakeScaleMatrix(scale);
	//R
	Matrix3x3 rotateMatrix;
	rotateMatrix = MakeRotate3x3Matrix(radian);
	//T
	Matrix3x3 translateMatrix;
	translateMatrix = MakeTranslate3x3Matrix(translate);

	result = Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);

	return result;
}

Vector2 MatrixTransform::Transform(Vector2 v, Matrix3x3 matrix)
{
	Vector2 result;
	result.x = v.x * matrix.m[0][0] + v.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = v.x * matrix.m[0][1] + v.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = v.x * matrix.m[0][2] + v.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 MatrixTransform::Inverse(Matrix3x3 matrix)
{
	Matrix3x3 result;

	float determinant =
		matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +

		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];
	assert(determinant != 0.0f);
	float determinantRecp = 1.0f / determinant;

	result.m[0][0] =
		(matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) * determinantRecp;
	result.m[0][1] =
		-(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) * determinantRecp;
	result.m[0][2] =
		(matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) * determinantRecp;


	result.m[1][0] =
		-(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) * determinantRecp;
	result.m[1][1] =
		(matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) * determinantRecp;
	result.m[1][2] =
		-(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) * determinantRecp;


	result.m[2][0] =
		(matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) * determinantRecp;
	result.m[2][1] =
		-(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) * determinantRecp;
	result.m[2][2] =
		(matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) * determinantRecp;

	return result;
}

Matrix3x3 MatrixTransform::Transpose(Matrix3x3 matrix)
{
	Matrix3x3 result;

	result.m[0][0] = matrix.m[0][0];
	result.m[0][1] = matrix.m[1][0];
	result.m[0][2] = matrix.m[2][0];

	result.m[1][0] = matrix.m[0][1];
	result.m[1][1] = matrix.m[1][1];
	result.m[1][2] = matrix.m[2][1];

	result.m[2][0] = matrix.m[0][2];
	result.m[2][1] = matrix.m[1][2];
	result.m[2][2] = matrix.m[2][2];
	return result;


}

Matrix3x3 MatrixTransform::MakeOrthographicMatrix(float left, float top, float right, float bottom)
{
	assert(left != right);
	assert(top != bottom);
	Matrix3x3 result;

	result.m[0][0] = 2.0f / (right - left);//
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2.0f / (top - bottom);//
	result.m[1][2] = 0.0f;

	result.m[2][0] = (left + right) / (left - right);//
	result.m[2][1] = (top + bottom) / (bottom - top);//
	result.m[2][2] = 1.0f;

	return result;

}

Matrix3x3 MatrixTransform::MakeviewportMatrix(float left, float top, float width, float height)
{
	Matrix3x3 result;

	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[1][2] = 0.0f;

	result.m[2][0] = left + (width / 2.0f);
	result.m[2][1] = top + (height / 2.0f);
	result.m[2][2] = 1.0f;

	return result;

}


#pragma endregion

#pragma endregion 


#pragma region 四次元行列

#pragma region +-*
Matrix4x4 MatrixTransform::Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			result.m[row][col] = m1.m[row][col] + m2.m[row][col];
		}
	}

	return result;
}

Matrix4x4 MatrixTransform::Subract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			result.m[row][col] = m1.m[row][col] - m2.m[row][col];
		}
	}

	return result;
}

Matrix4x4 MatrixTransform::Multiply(Matrix4x4 m1, Matrix4x4 m2)
{
	Matrix4x4 result;

	result.m[0][0] = (m1.m[0][0] * m2.m[0][0]) + (m1.m[0][1] * m2.m[1][0]) +
		(m1.m[0][2] * m2.m[2][0]) + (m1.m[0][3] * m2.m[3][0]);
	result.m[0][1] = (m1.m[0][0] * m2.m[0][1]) + (m1.m[0][1] * m2.m[1][1]) +
		(m1.m[0][2] * m2.m[2][1]) + (m1.m[0][3] * m2.m[3][1]);
	result.m[0][2] = (m1.m[0][0] * m2.m[0][2]) + (m1.m[0][1] * m2.m[1][2]) +
		(m1.m[0][2] * m2.m[2][2]) + (m1.m[0][3] * m2.m[3][2]);
	result.m[0][3] = (m1.m[0][0] * m2.m[0][3]) + (m1.m[0][1] * m2.m[1][3]) +
		(m1.m[0][2] * m2.m[2][3]) + (m1.m[0][3] * m2.m[3][3]);

	result.m[1][0] = (m1.m[1][0] * m2.m[0][0]) + (m1.m[1][1] * m2.m[1][0]) +
		(m1.m[1][2] * m2.m[2][0]) + (m1.m[1][3] * m2.m[3][0]);
	result.m[1][1] = (m1.m[1][0] * m2.m[0][1]) + (m1.m[1][1] * m2.m[1][1]) +
		(m1.m[1][2] * m2.m[2][1]) + (m1.m[1][3] * m2.m[3][1]);
	result.m[1][2] = (m1.m[1][0] * m2.m[0][2]) + (m1.m[1][1] * m2.m[1][2]) +
		(m1.m[1][2] * m2.m[2][2]) + (m1.m[1][3] * m2.m[3][2]);
	result.m[1][3] = (m1.m[1][0] * m2.m[0][3]) + (m1.m[1][1] * m2.m[1][3]) +
		(m1.m[1][2] * m2.m[2][3]) + (m1.m[1][3] * m2.m[3][3]);

	result.m[2][0] = (m1.m[2][0] * m2.m[0][0]) + (m1.m[2][1] * m2.m[1][0]) +
		(m1.m[2][2] * m2.m[2][0]) + (m1.m[2][3] * m2.m[3][0]);
	result.m[2][1] = (m1.m[2][0] * m2.m[0][1]) + (m1.m[2][1] * m2.m[1][1]) +
		(m1.m[2][2] * m2.m[2][1]) + (m1.m[2][3] * m2.m[3][1]);
	result.m[2][2] = (m1.m[2][0] * m2.m[0][2]) + (m1.m[2][1] * m2.m[1][2]) +
		(m1.m[2][2] * m2.m[2][2]) + (m1.m[2][3] * m2.m[3][2]);
	result.m[2][3] = (m1.m[2][0] * m2.m[0][3]) + (m1.m[2][1] * m2.m[1][3]) +
		(m1.m[2][2] * m2.m[2][3]) + (m1.m[2][3] * m2.m[3][3]);

	result.m[3][0] = (m1.m[3][0] * m2.m[0][0]) + (m1.m[3][1] * m2.m[1][0]) +
		(m1.m[3][2] * m2.m[2][0]) + (m1.m[3][3] * m2.m[3][0]);
	result.m[3][1] = (m1.m[3][0] * m2.m[0][1]) + (m1.m[3][1] * m2.m[1][1]) +
		(m1.m[3][2] * m2.m[2][1]) + (m1.m[3][3] * m2.m[3][1]);
	result.m[3][2] = (m1.m[3][0] * m2.m[0][2]) + (m1.m[3][1] * m2.m[1][2]) +
		(m1.m[3][2] * m2.m[2][2]) + (m1.m[3][3] * m2.m[3][2]);
	result.m[3][3] = (m1.m[3][0] * m2.m[0][3]) + (m1.m[3][1] * m2.m[1][3]) +
		(m1.m[3][2] * m2.m[2][3]) + (m1.m[3][3] * m2.m[3][3]);

	return result;
}

#pragma endregion 

#pragma region スケール・移動・回転
Matrix4x4 MatrixTransform::MakeScaleMatrix(const Vector3 scale)
{
	Matrix4x4 result;
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MatrixTransform::MakeTranslateMatrix(Vector3 translate)
{
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;
}

#pragma region 回転
Matrix4x4 MatrixTransform::MakeRotateXMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -(std::sin(radian));
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MatrixTransform::MakeRotateYMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0.0f;
	result.m[0][2] = -(std::sin(radian));
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0.0f;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MatrixTransform::MakeRotateZMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -(std::sin(radian));
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MatrixTransform::MakeRotateXYZMatrix(float radianX, float radianY, float radianZ)
{
	Matrix4x4 result;

	Matrix4x4 rotateMatrixX = MakeRotateXMatrix(radianX);
	Matrix4x4 rotateMatrixY = MakeRotateYMatrix(radianY);
	Matrix4x4 rotateMatrixZ = MakeRotateZMatrix(radianZ);

	result = Multiply(rotateMatrixX, Multiply(rotateMatrixY, rotateMatrixZ));

	return result;
}
#pragma endregion 
#pragma endregion 

#pragma region 行列の変換
Matrix4x4 MatrixTransform::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 result;

	// S
	Matrix4x4 scaleMatrix;
	scaleMatrix = MakeScaleMatrix(scale);

	// R
	Matrix4x4 rotateMatrix;
	rotateMatrix = MakeRotateXYZMatrix(rotate.x, rotate.y, rotate.z);

	Matrix4x4 translateMatrix;
	translateMatrix = MakeTranslateMatrix(translate);

	result = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));

	return result;
}

Matrix4x4 MatrixTransform::Transpose(const Matrix4x4 m)
{
	Matrix4x4 result;

	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; c++)
		{

			result.m[c][r] = m.m[r][c];

		}

	}
	return result;
}

Matrix4x4 MatrixTransform::Inverse(Matrix4x4& matrix)
{
	float MatrixFormula;
	MatrixFormula =
		+(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3])
		+ (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1])
		+ (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2])

		- (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1])
		- (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3])
		- (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2])

		- (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3])
		- (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1])
		- (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2])

		+ (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1])
		+ (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3])
		+ (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2])

		+ (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3])
		+ (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1])
		+ (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2])


		- (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1])
		- (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3])
		- (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2])

		- (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0])
		- (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0])
		- (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0])

		+ (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0])
		+ (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0])
		+ (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]);

	Matrix4x4 result = {};



	result.m[0][0] = (1 / MatrixFormula) * (
		+(matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3])
		+ (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1])
		+ (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2])
		- (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1])
		- (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3])
		- (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]));

	result.m[0][1] = (1 / MatrixFormula) * (
		-(matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][3])
		- (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1])
		- (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2])
		+ (matrix.m[0][3] * matrix.m[2][2] * matrix.m[0][2])
		+ (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3])
		+ (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2]));


	result.m[0][2] = (1 / MatrixFormula) * (
		+(matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3])
		+ (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1])
		+ (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2])
		- (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1])
		- (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3])
		- (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2]));

	result.m[0][3] = (1 / MatrixFormula) * (
		-(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3])
		- (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1])
		- (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2])
		+ (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1])
		+ (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3])
		+ (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2]));



	result.m[1][0] = (1 / MatrixFormula) * (
		-(matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3])
		- (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0])
		- (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2])
		+ (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0])
		+ (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3])
		+ (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]));

	result.m[1][1] = (1 / MatrixFormula) * (
		+(matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3])
		+ (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0])
		+ (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2])
		- (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0])
		- (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3])
		- (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2]));

	result.m[1][2] = (1 / MatrixFormula) * (
		-(matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3])
		- (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0])
		- (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2])
		+ (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0])
		+ (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3])
		+ (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2]));

	result.m[1][3] = (1 / MatrixFormula) * (
		+(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3])
		+ (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0])
		+ (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2])
		- (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0])
		- (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3])
		- (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2]));



	result.m[2][0] = (1 / MatrixFormula) * (
		+(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3])
		+ (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0])
		+ (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1])
		- (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0])
		- (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3])
		- (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]));

	result.m[2][1] = (1 / MatrixFormula) * (
		-(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3])
		- (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0])
		- (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1])
		+ (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0])
		+ (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3])
		+ (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1]));

	result.m[2][2] = (1 / MatrixFormula) * (
		+(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3])
		+ (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0])
		+ (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1])
		- (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0])
		- (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3])
		- (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1]));

	result.m[2][3] = (1 / MatrixFormula) * (
		-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3])
		- (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0])
		- (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1])
		+ (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0])
		+ (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3])
		+ (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1]));


	result.m[3][0] = (1 / MatrixFormula) * (
		-(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2])
		- (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0])
		- (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1])
		+ (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0])
		+ (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2])
		+ (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]));


	result.m[3][1] = (1 / MatrixFormula) * (
		+(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2])
		+ (matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0])
		+ (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1])
		- (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0])
		- (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2])
		- (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1]));

	result.m[3][2] = (1 / MatrixFormula) * (
		-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2])
		- (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0])
		- (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1])
		+ (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0])
		+ (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2])
		+ (matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1]));

	result.m[3][3] = (1 / MatrixFormula) * (
		+(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2])
		+ (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0])
		+ (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1])
		- (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0])
		- (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2])
		- (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]));


	return result;
}
Matrix4x4 MatrixTransform::Identity()
{
	Matrix4x4 result =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f

	};


	return result;
}

Matrix4x4 MatrixTransform::MakeOrthographicMatrix(float left, float top, float right, float bottom, float neaCrlip, float farClip)
{
	Matrix4x4 result;
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = (1 / farClip - neaCrlip);
	result.m[2][3] = 0;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = neaCrlip / (neaCrlip - farClip);
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MatrixTransform::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result;
	result.m[0][0] = width / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -(height / 2);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;

}

float MatrixTransform::Cot(float theta)
{
	
	return (1.0f / tan(theta));
	
}


Matrix4x4 MatrixTransform::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result;
	float theta = fovY / 2.0f;

	result.m[0][0] = (1.0f / aspectRatio) * Cot(theta);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = Cot(theta);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	result.m[3][3] = 0;

	return result;
}


#pragma endregion 

#pragma endregion