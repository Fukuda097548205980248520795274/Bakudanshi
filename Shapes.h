#pragma once

/// <summary>
/// 矩形の頂点のベクトルを作る
/// </summary>
/// <returns>矩形の頂点のベクトルの構造体を返却する</returns>
BoxVertexVec MakeBoxVertexVec();

/// <summary>
/// 矩形の当たり判定を行う
/// </summary>
/// <param name="shape1">図形1</param>
/// <param name="shape2">図形2</param>
/// <returns>矩形の当たり判定を行いtrueかfalseを返却する</returns>
int HitBox(Shape shape1, Shape shape2);

/// <summary>
/// 大きさ、角度、平行移動を頂点の位置に変換する
/// </summary>
/// <param name="shape">図形</param>
/// <returns>頂点の位置の構造体を返却する</returns>
BoxVertexWorld VertexAffineMatrix(Shape shape);

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="world">ワールド座標</param>
/// <returns>スクリーン座標を返却する</returns>
BoxVertexScreen CoordinateTransformation(BoxVertexWorld world);