
#ifndef MATRIX_H_
#define MATRIX_H_

struct Matrix4
{
	Matrix4(float _00, float _10, float _20, float _30,
			float _01, float _11, float _21, float _31,
			float _02, float _12, float _22, float _32,
			float _03, float _13, float _23, float _33)
	{
		matrix[0] = _00; 
		matrix[1] = _10; 
		matrix[2] = _20;
		matrix[3] = _30;
		matrix[4] = _01;
		matrix[5] = _11; 
		matrix[6] = _21;
		matrix[7] = _31;
		matrix[8] = _02;
		matrix[9] = _12;
		matrix[10] = _22;
		matrix[11] = _32;
		matrix[12] = _03; 
		matrix[13] = _13;
		matrix[14] = _23;
		matrix[15] = _33;
	}

	float matrix[16];

		/*
		float _00;
		float _10;
		float _20;
		float _30;
		float _01;
		float _11;
		float _21;
		float _31;
		float _02;
		float _12;
		float _22;
		float _32;
		float _03;
		float _13;
		float _23;
		float _33;
		*/
};

#endif
