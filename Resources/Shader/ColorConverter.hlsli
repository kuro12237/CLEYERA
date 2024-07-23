// RGB‚©‚çHSV‚É•ÏŠ·
float32_t3 RGBtoHSV(float32_t3 rgb)
{
    float r = rgb.r;
    float g = rgb.g;
    float b = rgb.b;
    
    
    float max = r > g ? r : g;
    max = max > b ? max : b;
    float min = r < g ? r : g;
    min = min < b ? min : b;
    float h = max - min;
    if (h > 0.0f)
    {
        if (max == r)
        {
            h = (g - b) / h;
            if (h < 0.0f)
            {
                h += 6.0f;
            }
        }
        else if (max == g)
        {
            h = 2.0f + (b - r) / h;
        }
        else
        {
            h = 4.0f + (r - g) / h;
        }
    }
    h /= 6.0f;
    float s = (max - min);
    if (max != 0.0f)
        s /= max;
    float v = max;

    return float32_t3(h, s, v);
}

///
///HSV‚©‚çRGB•ÏŠ·
float32_t3 HSVtoRGB(float32_t3 hsv)
{
    float h = hsv.r;
    float s = hsv.g;
    float v = hsv.b;
    float r = v;
    float g = v;
    float b = v;
    if (s > 0.0f)
    {
        h *= 6.0f;
        int i = (int) h;
        float f = h - (float) i;
        switch (i)
        {
            default:
            case 0:
                g *= 1 - s * (1 - f);
                b *= 1 - s;
                break;
            case 1:
                r *= 1 - s * f;
                b *= 1 - s;
                break;
            case 2:
                r *= 1 - s;
                b *= 1 - s * (1 - f);
                break;
            case 3:
                r *= 1 - s;
                g *= 1 - s * f;
                break;
            case 4:
                r *= 1 - s * (1 - f);
                g *= 1 - s;
                break;
            case 5:
                g *= 1 - s;
                b *= 1 - s * f;
                break;
        }
    }
    return float32_t3(r, g, b);
}

float WrapValue(float32_t value,float32_t minRange,float32_t maxRange)
{
    float32_t range = maxRange - minRange;
    float32_t modValue = fmod(value - minRange, range);
    if(modValue<0)
    {
        modValue += range;
    }
    return minRange + modValue;
}