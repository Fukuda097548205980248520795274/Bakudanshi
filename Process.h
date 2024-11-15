#pragma once

#include "Structure.h"

/// <summary>
/// 復活処理を行う
/// </summary>
/// <param name="respawn">復活</param>
void RespawnProcess(Respawn* respawn);

/// <summary>
/// ダメージ処理を行う
/// </summary>
/// <param name="player"></param>
void DamageProcess(Player* player);

/// <summary>
/// ダメージ処理を行う
/// </summary>
/// <param name="enemy">敵</param>
void DamageProcess(Enemy* enemy);

/// <summary>
/// ダメージ処理を行う
/// </summary>
/// <param name="boss">ボス</param>
void DamageProcess(Boss* boss);