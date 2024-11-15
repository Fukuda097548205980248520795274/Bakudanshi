#include "Structure.h"
#include "Constant.h"
#include "Enumration.h"
#include "Shapes.h"
#include "Matrix.h"
#include "Player.h"
#include "Bomb.h"
#include "Bullet.h"
#include "Enemy.h"

/// <summary>
/// 敵を出現させる
/// </summary>
/// <param name="enemy">敵</param>
/// <param name="type">種類</param>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
void EnemyArrival(Enemy* enemy, int type, float posX, float posY)
{
	// nullを探す
	if (enemy == nullptr)
	{
		return;
	}

	// 敵を出現させる
	for (int i = 0; i <kEnemyNum; i++)
	{
		if (enemy[i].isArrival == false && enemy[i].respawn.isRespawn)
		{
			// 敵を出現させる（出現フラグがtrueになる）
			enemy[i].isArrival = true;

			// フレーム
			enemy[i].frame = 0;

			// 種類
			enemy[i].type = type;

			// 向いている方向
			enemy[i].directionNo = DIRECTION_LEFT;

			switch (enemy[i].type)
			{
			case ENEMY_TYPE_GROUND:

				// ダメージ
				enemy[i].damage.hp = 3;
				enemy[i].damage.isDamage = false;
				enemy[i].damage.timer = 5;

				// 図形
				enemy[i].shape.scale = { 8.0f , 8.0f };
				enemy[i].shape.theta = 0.0f;
				enemy[i].shape.translate = { posX , posY };

				// 移動速度
				enemy[i].vel = { 0.0f , 0.0f };

				// 加速度
				enemy[i].acceleration = { 0.0f , 0.0f };

				break;
			}

			// 位置
			enemy[i].pos.world = VertexAffineMatrix(enemy[i].shape);
			enemy[i].pos.screen = CoordinateTransformation(enemy[i].pos.world);

			break;
		}
	}
}

/// <summary>
/// 敵を動かす
/// </summary>
/// <param name="enemy">敵</param>
void EnemyMove(Enemy* enemy , Player* player)
{
	// null を探す
	if (enemy == nullptr || player == nullptr)
	{
		return;
	}

	// 出現している（出現フラグがtrueである）敵を動かす
	for (int i = 0; i < kEnemyNum; i++)
	{
		if (enemy[i].isArrival)
		{
			// フレームを進める
			enemy[i].frame++;

			switch (enemy[i].type)
			{
			case ENEMY_TYPE_GROUND:

				break;
			}

			// プレイヤーの方向を向く
			if (enemy[i].shape.translate.x > player->shape.translate.x)
			{
				enemy[i].directionNo = DIRECTION_LEFT;
			}
			else if (enemy[i].shape.translate.x < player->shape.translate.x)
			{
				enemy[i].directionNo = DIRECTION_RIGHT;
			}
		}
	}
}