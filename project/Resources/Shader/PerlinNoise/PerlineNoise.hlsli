#include"../Random/RandomGenerator.hlsli"
// グラデーションベクトルを生成 (時間による変化を追加)
float2 Gradient(float2 pos, float32_t time, RandomGenerator rg)
{
    // 時間に基づいた乱数を生成し、角度を動的に変化させる
    float random = rg.rand3dTo2d(pos + float2(sin(time), cos(time))).x;
    float angle = random * 2.0 * 3.14159265; // 0〜2πの角度を生成
    return float2(cos(angle), sin(angle)); // 角度に基づいてベクトルを返す
}

// 補間関数 (スムーズステップ)
float Fade(float t)
{
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0); // 6t^5 - 15t^4 + 10t^3
}

// 2Dパーリンノイズの実装 (時間による模様の変化)
float PerlinNoise2D(float2 st, float32_t time, RandomGenerator rg)
{
    // 各グリッド点の座標を取得
    float2 i = floor(st);
    float2 f = frac(st);

    // 時間によってグラデーションベクトルを変化させる
    float2 g00 = Gradient(i + float2(0.0, 0.0), time, rg);
    float2 g10 = Gradient(i + float2(1.0, 0.0), time, rg);
    float2 g01 = Gradient(i + float2(0.0, 1.0), time, rg);
    float2 g11 = Gradient(i + float2(1.0, 1.0), time, rg);

    // 各グリッド点からの距離ベクトル
    float2 d00 = f - float2(0.0, 0.0);
    float2 d10 = f - float2(1.0, 0.0);
    float2 d01 = f - float2(0.0, 1.0);
    float2 d11 = f - float2(1.0, 1.0);

    // 各グリッド点の寄与を計算（グラデーションベクトルとのドット積）
    float n00 = dot(g00, d00);
    float n10 = dot(g10, d10);
    float n01 = dot(g01, d01);
    float n11 = dot(g11, d11);

    // 補間関数でスムーズに補間
    float2 u = float2(Fade(f.x), Fade(f.y));
    float nx0 = lerp(n00, n10, u.x);
    float nx1 = lerp(n01, n11, u.x);
    float nxy = lerp(nx0, nx1, u.y);

    return nxy;
}