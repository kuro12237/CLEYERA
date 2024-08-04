
float32_t4x4 Mat4x4Identity()
{
    return float32_t4x4(
          float32_t4(1.0f, 0.0f, 0.0f, 0.0f),
          float32_t4(0.0f, 1.0f, 0.0f, 0.0f),
          float32_t4(0.0f, 0.0f, 1.0f, 0.0f),
          float32_t4(0.0f, 0.0f, 0.0f, 1.0f)
    );
}

float32_t4x4 ScaleMatrix(float32_t3 scale)
{
    return float32_t4x4(
        scale.x, 0.0, 0.0, 0.0,
        0.0, scale.y, 0.0, 0.0,
        0.0, 0.0, scale.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

float32_t4x4 TranslateMatrix(float32_t3 translation)
{
    return
    float32_t4x4(
        1.0, 0.0, 0.0, 0.0f,
        0.0, 1.0, 0.0, 0.0f,
        0.0, 0.0, 1.0, 0.0f,
        translation.x, translation.y, translation.z, 1.0
    );
}

float32_t4x4 RotateMatrixX(float angle)
{
    float32_t s = sin(angle);
    float32_t c = cos(angle);
    return float32_t4x4(
        1.0, 0.0, 0.0, 0.0,
        0.0, c, -s, 0.0,
        0.0, s, c, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

float32_t4x4 RotateMatrixY(float32_t angle)
{
    float32_t s = sin(angle);
    float32_t c = cos(angle);
    return float32_t4x4(
        c, 0.0, s, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -s, 0.0, c, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

float32_t4x4 RotateMatrixZ(float32_t angle)
{
    float32_t s = sin(angle);
    float32_t c = cos(angle);
    return float32_t4x4(
        c, -s, 0.0, 0.0,
        s, c, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

float32_t4x4 AffineMatrix(float32_t3 scale, float32_t3 rotate, float32_t3 translate)
{
    float32_t4x4 scalingMatrix = ScaleMatrix(scale);
    float32_t4x4 rotationMatrixX = RotateMatrixX(rotate.x);
    float32_t4x4 rotationMatrixY = RotateMatrixY(rotate.y);
    float32_t4x4 rotationMatrixZ = RotateMatrixZ(rotate.z);
    float32_t4x4 translationMatrix = TranslateMatrix(translate);
    float32_t4x4 rotateXYZ = Mat4x4Identity();
    rotateXYZ = mul(rotateXYZ, mul(rotationMatrixX, mul(rotationMatrixY, rotationMatrixZ)));
    return mul(scalingMatrix, mul(rotateXYZ, translationMatrix));

}