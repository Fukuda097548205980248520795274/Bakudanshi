#include "Structure.h"
#include "Constant.h"
#include "Enumration.h"
#include "Shapes.h"
#include "Matrix.h"
#include "Bullet.h"

/// <summary>
/// 弾を発射する
/// </summary>
/// <param name="bullet">弾</param>
/// <param name="type">種類</param>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
void BulletShot(Bullet* bullet , int type , float posX , float posY)
{
	// null を探す
	if (bullet == nullptr)
	{
		return;
	}

	// 弾を発射する
	for (int i = 0; i < kBulletNum; i++)
	{
		if (bullet[i].isShot == false && bullet[i].respawn.isRespawn)
		{
			// 弾を発射する（発射フラグをtrueにする）
			bullet[i].isShot = true;

			// フレーム
			bullet[i].frame = 0;

			// 種類
			bullet[i].type = type;

			switch (bullet[i].type)
			{
			case BULLET_TYPE_EXPLOSION:

				// 図形
				bullet[i].shape.scale = { 90.0f , 90.0f };
				bullet[i].shape.theta = 0.0f;
				bullet[i].shape.translate = { posX , posY };

				// 移動速度
				bullet[i].vel = { 0.0f , 0.0f };

				// 加速度
				bullet[i].acceleration = { 0.0f , 0.0f };

				break;

			case BULLET_TYPE_VIBRATION_LEFT:

				// 図形
				bullet[i].shape.scale = { 20.0f , 10.0f };
				bullet[i].shape.theta = 0.0f;
				bullet[i].shape.translate = { posX , posY };

				// 移動速度
				bullet[i].vel = { -6.0f , 0.0f };

				// 加速度
				bullet[i].acceleration = { 0.0f , 0.0f };

				break;

			case BULLET_TYPE_VIBRATION_RIGHT:

				// 図形
				bullet[i].shape.scale = { 20.0f , 10.0f };
				bullet[i].shape.theta = 0.0f;
				bullet[i].shape.translate = { posX , posY };

				// 移動速度
				bullet[i].vel = { 6.0f , 0.0f };

				// 加速度
				bullet[i].acceleration = { 0.0f , 0.0f };

				break;

			case BULLET_TYPE_RUBBLE_SMALL:
				
				// 図形
				bullet[i].shape.scale = { 6.0f , 6.0f };
				bullet[i].shape.theta = 0.0f;
				bullet[i].shape.translate = { posX , posY };

				// 移動速度
				bullet[i].vel = { 0.0f , -2.0f };

				// 加速度
				bullet[i].acceleration = { 0.0f , 0.0f };

				break;

			case BULLET_TYPE_RUBBLE_MIDDLE:

				// 図形
				bullet[i].shape.scale = { 12.0f , 12.0f };
				bullet[i].shape.theta = 0.0f;
				bullet[i].shape.translate = { posX , posY };

				// 移動速度
				bullet[i].vel = { 0.0f , -2.0f };

				// 加速度
				bullet[i].acceleration = { 0.0f , 0.0f };

				break;

			case BULLET_TYPE_RUBBLE_BIG:

				// 図形
				bullet[i].shape.scale = { 20.0f , 20.0f };
				bullet[i].shape.theta = 0.0f;
				bullet[i].shape.translate = { posX , posY };

				// 移動速度
				bullet[i].vel = { 0.0f , -2.0f };

				// 加速度
				bullet[i].acceleration = { 0.0f , 0.0f };

				break;
			}

			// 位置
			bullet[i].pos.world = VertexAffineMatrix(bullet[i].shape);

			break;
		}
	}
}

/// <summary>
/// 弾を動かす
/// </summary>
/// <param name="bullet">弾</param>
void BulletMove(Bullet* bullet)
{
	// null を探す
	if (bullet == nullptr)
	{
		return;
	}

	// 発射されている（発射フラグがtrueである）弾を動かす
	for (int i = 0; i < kBulletNum; i++)
	{
		if (bullet[i].isShot)
		{
			// 弾の時間を数える
			bullet[i].frame++;

			// 弾の種類で動きを変える
			switch (bullet[i].type)
			{
			case BULLET_TYPE_EXPLOSION:

				// 1フレームを超えたら、消える（復活、発射フラグがfalseになる）
				if (bullet[i].frame > 1)
				{
					bullet[i].respawn.isRespawn = false;
					bullet[i].isShot = false;
				}

				// 弾を動かす
				bullet[i].shape.translate.x += bullet[i].vel.x;
				bullet[i].shape.translate.y += bullet[i].vel.y;
				bullet[i].pos.world = VertexAffineMatrix(bullet[i].shape);

				break;

			case BULLET_TYPE_VIBRATION_LEFT:

				// 弾を動かす
				bullet[i].shape.translate.x += bullet[i].vel.x;
				bullet[i].shape.translate.y += bullet[i].vel.y;
				bullet[i].pos.world = VertexAffineMatrix(bullet[i].shape);

				// 画面外に出たら消える（発射フラグがtrueになる）
				if (bullet[i].shape.translate.x + bullet[i].shape.scale.x < 0.0f ||
					bullet[i].shape.translate.x - bullet[i].shape.scale.x > static_cast<float>(kScreenWtidh) ||
					bullet[i].shape.translate.y - bullet[i].shape.scale.y > static_cast<float>(kScreenHeight) - 120.0f ||
					bullet[i].shape.translate.y + bullet[i].shape.scale.y < -120.0f)
				{
					bullet[i].isShot = false;
				}

				break;

			case BULLET_TYPE_VIBRATION_RIGHT:

				// 弾を動かす
				bullet[i].shape.translate.x += bullet[i].vel.x;
				bullet[i].shape.translate.y += bullet[i].vel.y;
				bullet[i].pos.world = VertexAffineMatrix(bullet[i].shape);

				// 画面外に出たら消える（発射フラグがtrueになる）
				if (bullet[i].shape.translate.x + bullet[i].shape.scale.x < 0.0f ||
					bullet[i].shape.translate.x - bullet[i].shape.scale.x > static_cast<float>(kScreenWtidh) ||
					bullet[i].shape.translate.y - bullet[i].shape.scale.y > static_cast<float>(kScreenHeight) - 120.0f ||
					bullet[i].shape.translate.y + bullet[i].shape.scale.y < -120.0f)
				{
					bullet[i].isShot = false;
				}

				break;

			case BULLET_TYPE_RUBBLE_SMALL:

				// 弾を動かす
				bullet[i].shape.translate.x += bullet[i].vel.x;
				bullet[i].shape.translate.y += bullet[i].vel.y;
				bullet[i].pos.world = VertexAffineMatrix(bullet[i].shape);

				// 画面外に出たら消える（発射フラグがtrueになる）
				if (bullet[i].shape.translate.x + bullet[i].shape.scale.x < 0.0f ||
					bullet[i].shape.translate.x - bullet[i].shape.scale.x > static_cast<float>(kScreenWtidh) ||
					bullet[i].shape.translate.y - bullet[i].shape.scale.y < 0.0f)
				{
					bullet[i].isShot = false;
				}

				break;

			case BULLET_TYPE_RUBBLE_MIDDLE:

				// 弾を動かす
				bullet[i].shape.translate.x += bullet[i].vel.x;
				bullet[i].shape.translate.y += bullet[i].vel.y;
				bullet[i].pos.world = VertexAffineMatrix(bullet[i].shape);

				// 画面外に出たら消える（発射フラグがtrueになる）
				if (bullet[i].shape.translate.x + bullet[i].shape.scale.x < 0.0f ||
					bullet[i].shape.translate.x - bullet[i].shape.scale.x > static_cast<float>(kScreenWtidh) ||
					bullet[i].shape.translate.y - bullet[i].shape.scale.y < 0.0f)
				{
					bullet[i].isShot = false;
				}

				break;

			case BULLET_TYPE_RUBBLE_BIG:

				// 弾を動かす
				bullet[i].shape.translate.x += bullet[i].vel.x;
				bullet[i].shape.translate.y += bullet[i].vel.y;
				bullet[i].pos.world = VertexAffineMatrix(bullet[i].shape);

				// 画面外に出たら消える（発射フラグがtrueになる）
				if (bullet[i].shape.translate.x + bullet[i].shape.scale.x < 0.0f ||
					bullet[i].shape.translate.x - bullet[i].shape.scale.x > static_cast<float>(kScreenWtidh) ||
					bullet[i].shape.translate.y - bullet[i].shape.scale.y < 0.0f)
				{
					bullet[i].isShot = false;
				}

				break;
			}
		}
	}
}