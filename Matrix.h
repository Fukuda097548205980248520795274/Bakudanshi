#pragma once

/// <summary>
/// 行列の積を求める
/// </summary>
/// <param name="matrix1">行列1</param>
/// <param name="matrix2">行列2</param>
/// <returns>行列の積を求めた構造体を返却する</returns>
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

/// <summary>
/// ベクトルと行列の積を求める
/// </summary>
/// <param name="vec">ベクトル</param>
/// <param name="matrix">行列</param>
/// <returns>ベクトルと行列の積を求めた構造体を返却する</returns>
Coordinate2 Transform(Vec2 vec, Matrix3x3 matrix);

/// <summary>
/// 拡大縮小行列を作る
/// </summary>
/// <param name="sclae">大きさ</param>
/// <returns>拡大縮小行列を作り、返却する</returns>
Matrix3x3 MakeScaleMatrix(Vec2 scale);

/// <summary>
/// 回転行列を作る
/// </summary>
/// <param name="theta">角度</param>
/// <returns>回転行列を作り、返却する</returns>
Matrix3x3 MakeRotateMatrix(float theta);

/// <summary>
/// 平行移動行列を作る
/// </summary>
/// <param name="translate">平行移動</param>
/// <returns>平行移動行列を作り、返却する</returns>
Matrix3x3 MakeTranslateMatrix(Vec2 translate);

/// <summary>
/// アフィン行列を作る
/// </summary>
/// <param name="scale">大きさ</param>
/// <param name="theta">角度</param>
/// <param name="translate">平行移動</param>
/// <returns>アフィン行列を作り、返却する</returns>
Matrix3x3 MakeAffineMatrix(Vec2 scale, float theta, Vec2 translate);