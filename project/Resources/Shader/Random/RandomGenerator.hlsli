
class RandomGenerator
{
    float32_t3 seed;

    float32_t rand3dTo1d(float32_t value, float32_t3 dotDir = float32_t3(12.9898, 78.233, 37.719))
    {
        float32_t smallValue = value;
        float32_t random = dot(smallValue, dotDir);
        random = frac(sin(random) * 143758.5453);
        return random;
    }

    float32_t2 rand3dTo2d(float32_t2 value, float32_t2 dotDir = float32_t2(12.9898, 78.233))
    {
        float32_t2 smallValue = value;
        float32_t2 random = dot(smallValue, dotDir);
        random = frac(sin(random) * 143758.5453);
        return random;
    }

    float32_t3 rand3dTo3d(float32_t3 value)
    {
        float32_t3 result = float32_t3(
        rand3dTo1d(value.x, float32_t3(12.989, 78.233, 37.719)),
        rand3dTo1d(value.y, float32_t3(39.346, 11.135, 83.155)),
        rand3dTo1d(value.z, float32_t3(73.156, 52.235, 09.151))
        );
        seed = result;
        return result;
    }

    float32_t3 Generate3d()
    {
        seed = rand3dTo3d(seed);
        return seed;

    }

    float32_t3 Generate1d()
    {
        seed.x = rand3dTo1d(seed.x);
        return seed;
    }

};