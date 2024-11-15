#pragma once

/// <summary>
/// ボスを出現させる
/// </summary>
/// <param name="boss">ボス</param>
/// <param name="type">種類</param>
void BossArrival(Boss* boss, int type);

/// <summary>
/// ボスを動かす
/// </summary>
/// <param name="boss">ボス</param>
/// <param name="player">プレイヤー</param>
/// <param name="bullet">弾</param>
void BossMove(Boss* boss, Player* player, Bullet* bullet);