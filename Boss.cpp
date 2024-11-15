#include <stdlib.h>
#include <time.h>
#include "Structure.h"
#include "Constant.h"
#include "Enumration.h"
#include "Shapes.h"
#include "Matrix.h"
#include "Process.h"
#include "Player.h"
#include "Bomb.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boss.h"

/// <summary>
/// ボスを出現させる!
/// </summary>
/// <param name="boss">ボス</param>
/// <param name="type">種類</param>
void BossArrival(Boss* boss, int type)
{
	// null を探す
	if (boss == nullptr)
	{
		return;
	}

	if (boss->isArrival == false && boss->respawn.isRespawn)
	{
		// ボスを出現させる（出現フラグをtrueにする）
		boss->isArrival = true;

		// フレーム
		boss->frame = 0;

		// 種類
		boss->type = type;

		// 向いている方向
		boss->directionNo = DIRECTION_LEFT;

		// 攻撃させない（攻撃フラグをfalseにする）
		boss->isAttack = false;
		boss->attackNo = -1;

		switch (boss->type)
		{
		case BOSS_TYPE_STAGE_1:

			// 図形
			boss->shape.scale = { 16.0f , 32.0f };
			boss->shape.theta = 0.0f;
			boss->shape.translate = { 980.0f , 0.0f };

			// 体力
			boss->damage.hp = 300;
			boss->damage.isDamage = false;
			boss->damage.timer = 5;

			break;
		}

		// 位置
		boss->pos.world = VertexAffineMatrix(boss->shape);
		boss->pos.screen = CoordinateTransformation(boss->pos.world);

		// 移動速度
		boss->vel = { 0.0f , 0.0f };

		// ジャンプ
		boss->jump.isJump = false;
		boss->jump.count = 0;

		// 加速度
		boss->accleration = { 0.0f , 0.0f };
	}
}

/// <summary>
/// ボスを動かす
/// </summary>
/// <param name="boss">ボス</param>
/// <param name="player">プレイヤー</param>
/// <param name="bullet">弾</param>
void BossMove(Boss* boss , Player* player , Bullet* bullet)
{
	// null を探す
	if (boss == nullptr || player == nullptr || bullet == nullptr)
	{
		return;
	}

	// 乱数
	unsigned int currentTimer = static_cast<unsigned int>(time(nullptr));
	srand(currentTimer);

	// 出現している（出現フラグがtrueである）ボスを動かす
	if (boss->isArrival)
	{
		// フレームを進める
		boss->frame++;

		// 横移動を初期化する
		boss->vel.x = 0.0f;

		// 20フレームから、攻撃を始める
		if (boss->frame >= 20)
		{
			switch (boss->type)
			{
			case BOSS_TYPE_STAGE_1:

				// 攻撃していない（攻撃フラグがfalseである）ときは、攻撃をランダムに決める
				if (boss->isAttack == false)
				{
					boss->attackNo = rand() % 3;

					// 攻撃を行う（攻撃フラグがtrueになる）
					boss->isAttack = true;
				}
				else
				{
					switch (boss->attackNo)
					{
					case 0:

						/*   突進   */

						// プレイヤーのいる方向に突進する
						if (boss->frame == 21)
						{
							if (boss->shape.translate.x - boss->shape.scale.x > 0.0f &&
								boss->shape.translate.x + boss->shape.scale.x < static_cast<float>(kScreenWtidh))
							{
								boss->frame--;

								if (boss->directionNo == DIRECTION_LEFT)
								{
									boss->vel.x = -14.0f;
								}
								else if (boss->directionNo == DIRECTION_RIGHT)
								{
									boss->vel.x = 14.0f;
								}
							}
						}

						// 跳ね飛ぶ
						if (boss->frame == 22)
						{
							boss->frame--;


							if (boss->directionNo == DIRECTION_LEFT)
							{
								boss->vel.x = static_cast<float>(4 - boss->jump.count) * 2.0f;
							}
							else if (boss->directionNo == DIRECTION_RIGHT)
							{
								boss->vel.x = static_cast<float>(4 - boss->jump.count) * -2.0f;
							}

							if (boss->jump.isJump == false)
							{
								if (boss->jump.count >= 3)
								{
									boss->frame++;
								}

								if (boss->jump.count < 3)
								{
									boss->jump.isJump = true;
									boss->vel.y = 6.0f;
									boss->jump.fallingVel = 1.0f;

									boss->jump.count++;
								}
							}
						}

						// 攻撃終了
						if (boss->frame == 100)
						{
							boss->isAttack = false;
							boss->attackNo = -1;

							boss->frame = -20;

							boss->jump.count = 0;
						}

						break;

					case 1:

						/*   振動   */

						// 25フレームで大ジャンプ
						if (boss->frame == 25)
						{
							if (boss->jump.isJump == false)
							{
								boss->jump.isJump = true;

								boss->vel.y = 12.0f;

								boss->jump.fallingVel = 0.2f;
							}
						}

						// 着地するまで、空中移動する
						if (boss->frame == 26)
						{
							if (boss->jump.isJump)
							{
								if (boss->directionNo == DIRECTION_LEFT)
								{
									boss->vel.x = -4.0f;
								}
								else if (boss->directionNo == DIRECTION_RIGHT)
								{
									boss->vel.x = 4.0f;
								}

								if (boss->vel.y <= 0.0f)
								{
									boss->jump.fallingVel = 2.0f;
								}

								boss->frame--;
							}
							else
							{
								BulletShot(bullet, BULLET_TYPE_VIBRATION_LEFT,
									boss->shape.translate.x, boss->shape.translate.y - boss->shape.scale.y);
								BulletShot(bullet, BULLET_TYPE_VIBRATION_RIGHT,
									boss->shape.translate.x, boss->shape.translate.y - boss->shape.scale.y);
							}
						}

						// バウンドジャンプ
						if (boss->frame == 27)
						{
							if (boss->jump.isJump == false)
							{
								boss->jump.isJump = true;

								boss->vel.y = 6.0f;

								boss->jump.fallingVel = 1.0f;
							}
						}

						// 着地するまで、フレームを進めない
						if (boss->frame == 28)
						{
							if (boss->jump.isJump)
							{
								boss->frame--;
							}
						}

						// 攻撃終了
						if (boss->frame >= 80)
						{
							boss->isAttack = false;
							boss->attackNo = -1;

							boss->frame = -40;
						}


						break;

					case 2:

						/*   がれき落とし   */

						// 50フレームで大ジャンプ
						if (boss->frame == 50)
						{
							if (boss->jump.isJump == false)
							{
								boss->vel.y = 24.0f;

								boss->jump.fallingVel = 0.0f;

								boss->jump.isJump = true;
							}

							if (boss->shape.translate.y + boss->shape.scale.y < static_cast<float>(kScreenHeight) - 120.0f)
							{
								boss->frame--;
							}
						}

						// 天井に60フレーム刺さり、がれきも落下する
						if (boss->frame > 50 && boss->frame <= 110)
						{
							boss->vel.y = 0.0f;

							boss->jump.isJump = false;

							BulletShot(bullet, BULLET_TYPE_RUBBLE_SMALL, static_cast<float>(rand() % kScreenWtidh), 800.0f);
						}

						// 落下する
						if (boss->frame == 110)
						{
							if (boss->jump.isJump == false)
							{
								boss->jump.isJump = true;

								boss->jump.fallingVel = 0.5f;
							}
						}

						// 着地するまで、フレームを進めない
						if (boss->frame == 111)
						{
							if (boss->jump.isJump)
							{
								boss->frame--;
							}
						}

						// 攻撃終了
						if (boss->frame >= 120)
						{
							boss->isAttack = false;
							boss->attackNo = -1;

							boss->frame = -40;
						}

						break;
					}
				}

				break;
			}
		}
		else
		{
			// 20f以前は、プレイヤーの方向に近づく
			if (boss->shape.translate.x - 200.0f > player->shape.translate.x)
			{
				boss->vel.x = -1.0f;
			}
			else if (boss->shape.translate.x + 200.0f < player->shape.translate.x)
			{
				boss->vel.x = 1.0f;
			}

			// プレイヤーの方向を向く
			if (boss->shape.translate.x > player->shape.translate.x)
			{
				boss->directionNo = DIRECTION_LEFT;
			}
			else if (boss->shape.translate.x < player->shape.translate.x)
			{
				boss->directionNo = DIRECTION_RIGHT;
			}
		}

		if (boss->jump.isJump)
		{
			boss->vel.y -= boss->jump.fallingVel;

			boss->shape.translate.y += boss->vel.y;
			boss->pos.world = VertexAffineMatrix(boss->shape);

			if (boss->shape.translate.y - boss->shape.scale.y <= 0.0f)
			{
				boss->jump.isJump = false;
				boss->vel.y = 0.0f;
				boss->jump.fallingVel = 0.0f;
			}
		}

		boss->shape.translate.x += boss->vel.x;
		boss->pos.world = VertexAffineMatrix(boss->shape);
	}


	/*   位置   */

	// 地面
	if (boss->shape.translate.y - boss->shape.scale.y < 0.0f)
	{
		boss->shape.translate.y = boss->shape.scale.y;
		boss->pos.world = VertexAffineMatrix(boss->shape);
	}

	// 天井
	if (boss->shape.translate.y + boss->shape.scale.y > static_cast<float>(kScreenHeight) - 120.0f)
	{
		boss->shape.translate.y = static_cast<float>(kScreenHeight) - 120.0f - boss->shape.scale.y;
		boss->pos.world = VertexAffineMatrix(boss->shape);
	}

	// 左の壁
	if (boss->shape.translate.x - boss->shape.scale.x < 0.0f)
	{
		boss->shape.translate.x = boss->shape.scale.x;
		boss->pos.world = VertexAffineMatrix(boss->shape);
	}

	// 右の壁
	if (boss->shape.translate.x + boss->shape.scale.x > static_cast<float>(kScreenWtidh))
	{
		boss->shape.translate.x = static_cast<float>(kScreenWtidh) - boss->shape.scale.x;
		boss->pos.world = VertexAffineMatrix(boss->shape);
	}
}