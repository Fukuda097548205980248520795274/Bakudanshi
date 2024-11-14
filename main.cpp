#include <Novice.h>
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

const char kWindowTitle[] = "1228_爆昼夢";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kScreenWtidh, kScreenHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	/*------------------------------
	    変数を作り、初期値を入れる
	------------------------------*/

	/*   プレイヤー   */

	// 構造体
	Player player;

	// 復活
	player.respawn.isRespawn = true;
	player.respawn.timer = 120;

	// 体力
	player.damage.hp = 0;
	player.damage.isDamage = false;
	player.damage.timer = 5;

	// 爆弾を持っているかどうか（爆弾所持フラグ）
	player.isBomHave = false;

	// 向ている方向
	player.directionNo = -1;

	// 位置
	player.pos.world = { {0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f} , {0.0f , 0.0f} };
	player.pos.screen = CoordinateTransformation(player.pos.world);

	// 移動速度
	player.vel = { 0.0f , 0.0f };

	// 加速度
	player.acceleration = { 0.0f , 0.0f };

	// ジャンプ
	player.jump.isJump = false;
	player.jump.count = 0;

	// 図形
	player.shape.scale = { 0.0f , 0.0f };
	player.shape.theta = 0.0f;
	player.shape.translate = { 0.0f , 0.0f };

	PlayerInitialValue(&player);


	/*   爆弾   */

	// 構造体
	Bomb bomb[kBombNum];

	for (int i = 0; i < kBombNum; i++)
	{
		// 復活
		bomb[i].respawn.isRespawn = true;
		bomb[i].respawn.timer = 120;

		// 起動しているかどうか（起動フラグ）
		bomb[i].isBoot = false;

		// 発射されているかどうか（発射フラグ）
		bomb[i].isShot = false;

		// 制限時間
		bomb[i].timeLimit = 0;

		// 図形
		bomb[i].shape.scale = { 0.0f , 0.0f };
		bomb[i].shape.theta = 0.0f;
		bomb[i].shape.translate = { 0.0f , 0.0f };

		// 位置
		bomb[i].pos.world = VertexAffineMatrix(bomb[i].shape);
		bomb[i].pos.screen = CoordinateTransformation(bomb[i].pos.world);

		// 移動速度
		bomb[i].vel = { 0.0f , 0.0f };

		// 加速度
		bomb[i].acceleration = { 0.0f , 0.0f };
	}


	/*   弾   */

	// 構造体
	Bullet bullet[kBulletNum];

	for (int i = 0; i < kBulletNum; i++)
	{
		// 復活
		bullet[i].respawn.isRespawn = true;
		bullet[i].respawn.timer = 120;

		// 発射しているかどうか（発射フラグ）
		bullet[i].isShot = false;

		// フレーム
		bullet[i].frame = 0;

		// 種類
		bullet[i].type = -1;

		// 図形
		bullet[i].shape.scale = { 0.0f , 0.0f };
		bullet[i].shape.theta = 0.0f;
		bullet[i].shape.translate = { 0.0f , 0.0f };

		// 位置
		bullet[i].pos.world = VertexAffineMatrix(bullet[i].shape);
		bullet[i].pos.screen = CoordinateTransformation(bullet[i].pos.world);

		// 移動速度
		bullet[i].vel = { 0.0f , 0.0f };

		// 加速度
		bullet[i].acceleration = { 0.0f , 0.0f };
	}


	/*   敵   */

	// 構造体
	Enemy enemy[kEnemyNum];

	for (int i = 0; i < kEnemyNum; i++)
	{
		// 復活
		enemy[i].respawn.isRespawn = true;
		enemy[i].respawn.timer = 120;

		// ダメージ
		enemy[i].damage.hp = 0;
		enemy[i].damage.isDamage = false;
		enemy[i].damage.timer = 5;

		// 出現しているかどうか（出現フラグ）
		enemy[i].isArrival = false;

		// フレーム
		enemy[i].frame = 0;

		// 種類
		enemy[i].type = -1;

		// 向いている方向
		enemy[i].directionNo = -1;

		// 図形
		enemy[i].shape.scale = { 0.0f , 0.0f };
		enemy[i].shape.theta = 0.0f;
		enemy[i].shape.translate = { 0.0f , 0.0f };

		// 位置
		enemy[i].pos.world = VertexAffineMatrix(enemy[i].shape);
		enemy[i].pos.screen = CoordinateTransformation(enemy[i].pos.world);

		// 移動速度
		enemy[i].vel = { 0.0f , 0.0f };

		// 加速度
		enemy[i].acceleration = { 0.0f , 0.0f };
	}


	/*   ボス   */

	// 構造体
	Boss boss;

	// 復活
	boss.respawn.isRespawn = true;
	boss.respawn.timer = 120;

	// ダメージ
	boss.damage.hp = 0;
	boss.damage.isDamage = false;
	boss.damage.timer = 5;

	// 出現しているかどうか（出現フラグ）
	boss.isArrival = false;

	// フレーム
	boss.frame = 0;

	// 種類
	boss.type = -1;

	// 向いている方向
	boss.directionNo = -1;

	// 攻撃しているかどうか（攻撃フラグ）
	boss.isAttack = false;

	// 現在の攻撃
	boss.attackNo = -1;

	// 図形
	boss.shape.scale = { 0.0f , 0.0f };
	boss.shape.theta = 0.0f;
	boss.shape.translate = { 0.0f , 0.0f };

	// 位置
	boss.pos.world = VertexAffineMatrix(boss.shape);
	boss.pos.screen = CoordinateTransformation(boss.pos.world);

	// 移動速度
	boss.vel = { 0.0f , 0.0f };

	// 加速度
	boss.accleration = { 0.0f , 0.0f };

	/*   コントローラーの左スティック   */

	// 構造体
	LeftStick leftStick;

	// Xが左右、Yが上下
	leftStick.x = 0;
	leftStick.y = 0;
	
	/*   画像   */

	// 白い図形
	int ghWhite = Novice::LoadTexture("./NoviceResources/white1x1.png");


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		/*----------------------
		    復活、ダメージ処理
		----------------------*/

		// プレイヤー
		RespawnProcess(&player.respawn);
		DamageProcess(&player);

		// 爆弾
		for (int i = 0; i < kBombNum; i++)
		{
			RespawnProcess(&bomb[i].respawn);
		}

		// 弾
		for (int i = 0; i < kBulletNum; i++)
		{
			RespawnProcess(&bullet[i].respawn);
		}

		// 敵
		for (int i = 0; i < kEnemyNum; i++)
		{
			RespawnProcess(&enemy[i].respawn);
			DamageProcess(&enemy[i]);
		}

		// ボス
		RespawnProcess(&boss.respawn);
		DamageProcess(&boss);


		/*-------------------
		    動きを設定する
		-------------------*/

		BossArrival(&boss, BOSS_TYPE_STAGE_1);

		// プレイヤーの移動操作
		PlayerMove(&player, keys , preKeys, &leftStick);

		// プレイヤーが爆弾を使う
		PlayerBombUse(&player, bomb, bullet, keys, preKeys);

		// 爆弾を動かす
		BombMove(bomb, bullet);

		// 弾を動かす
		BulletMove(bullet);

		// 敵を動かす
		EnemyMove(enemy , &player);

		// ボスを動かす
		BossMove(&boss , &player);


		/*-----------------
		    当たり判定
		-----------------*/

		// プレイヤー と 爆発
		if (player.respawn.isRespawn)
		{
			for (int i = 0; i < kBulletNum; i++)
			{
				if (bullet[i].isShot)
				{
					if (bullet[i].type == BULLET_TYPE_EXPLOSION)
					{
						if (HitBox(player.shape, bullet[i].shape))
						{
							if (player.damage.isDamage == false)
							{
								player.damage.isDamage = true;
							}
						}
					}
				}
			}
		}

		// 敵 と 爆発
		for (int i = 0; i < kEnemyNum; i++)
		{
			if (enemy[i].isArrival)
			{
				for (int j = 0; j < kBulletNum; j++)
				{
					if (bullet[j].isShot)
					{
						if (bullet[j].type == BULLET_TYPE_EXPLOSION)
						{
							if (HitBox(enemy[i].shape, bullet[j].shape))
							{
								if (enemy[i].damage.isDamage == false)
								{
									enemy[i].damage.isDamage = true;
								}
							}
						}
					}
				}
			}
		}

		// ボス と 爆発
		if (boss.isArrival)
		{
			for (int i = 0; i < kBulletNum; i++)
			{
				if (bullet[i].isShot)
				{
					if (bullet[i].type == BULLET_TYPE_EXPLOSION)
					{
						if (HitBox(boss.shape, bullet[i].shape))
						{
							if (boss.damage.isDamage == false)
							{
								boss.damage.isDamage = true;
							}
						}
					}
				}
			}
		}


		/*-------------
		    座標変換
		-------------*/

		// プレイヤー
		player.pos.screen = CoordinateTransformation(player.pos.world);

		// 爆弾
		for (int i = 0; i < kBombNum; i++)
		{
			bomb[i].pos.screen = CoordinateTransformation(bomb[i].pos.world);
		}

		// 弾
		for (int i = 0; i < kBulletNum; i++)
		{
			bullet[i].pos.screen = CoordinateTransformation(bullet[i].pos.world);
		}

		// 敵
		for (int i = 0; i < kEnemyNum; i++)
		{
			enemy[i].pos.screen = CoordinateTransformation(enemy[i].pos.world);
		}

		// ボス
		boss.pos.screen = CoordinateTransformation(boss.pos.world);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*----------------------------
		    図形や画像を描画する
		----------------------------*/

		// ボス
		if (boss.isArrival)
		{
			if (boss.damage.isDamage == false)
			{
				Novice::DrawQuad
				(
					static_cast<int>(boss.pos.screen.leftTop.x), static_cast<int>(boss.pos.screen.leftTop.y),
					static_cast<int>(boss.pos.screen.rightTop.x), static_cast<int>(boss.pos.screen.rightTop.y),
					static_cast<int>(boss.pos.screen.leftBottom.x), static_cast<int>(boss.pos.screen.leftBottom.y),
					static_cast<int>(boss.pos.screen.rightBottom.x), static_cast<int>(boss.pos.screen.rightBottom.y),
					0, 0, 1, 1, ghWhite, 0xFFFFFFFF
				);
			}
			else
			{
				Novice::DrawQuad
				(
					static_cast<int>(boss.pos.screen.leftTop.x), static_cast<int>(boss.pos.screen.leftTop.y),
					static_cast<int>(boss.pos.screen.rightTop.x), static_cast<int>(boss.pos.screen.rightTop.y),
					static_cast<int>(boss.pos.screen.leftBottom.x), static_cast<int>(boss.pos.screen.leftBottom.y),
					static_cast<int>(boss.pos.screen.rightBottom.x), static_cast<int>(boss.pos.screen.rightBottom.y),
					0, 0, 1, 1, ghWhite, 0x000000FF
				);
			}
		}

		// 敵
		for (int i = 0; i < kEnemyNum; i++)
		{
			if (enemy[i].isArrival)
			{
				if (enemy[i].damage.isDamage == false)
				{
					Novice::DrawQuad
					(
						static_cast<int>(enemy[i].pos.screen.leftTop.x) , static_cast<int>(enemy[i].pos.screen.leftTop.y) ,
						static_cast<int>(enemy[i].pos.screen.rightTop.x), static_cast<int>(enemy[i].pos.screen.rightTop.y),
						static_cast<int>(enemy[i].pos.screen.leftBottom.x), static_cast<int>(enemy[i].pos.screen.leftBottom.y),
						static_cast<int>(enemy[i].pos.screen.rightBottom.x), static_cast<int>(enemy[i].pos.screen.rightBottom.y),
						0,0,1,1,ghWhite,0xFFFFFFFF
					);
				}
				else
				{
					Novice::DrawQuad
					(
						static_cast<int>(enemy[i].pos.screen.leftTop.x), static_cast<int>(enemy[i].pos.screen.leftTop.y),
						static_cast<int>(enemy[i].pos.screen.rightTop.x), static_cast<int>(enemy[i].pos.screen.rightTop.y),
						static_cast<int>(enemy[i].pos.screen.leftBottom.x), static_cast<int>(enemy[i].pos.screen.leftBottom.y),
						static_cast<int>(enemy[i].pos.screen.rightBottom.x), static_cast<int>(enemy[i].pos.screen.rightBottom.y),
						0, 0, 1, 1, ghWhite, 0x000000FF
					);
				}
			}
		}

		// 弾
		for (int i = 0; i < kBulletNum; i++)
		{
			if (bullet[i].isShot)
			{
				Novice::DrawQuad
				(
					static_cast<int>(bullet[i].pos.screen.leftTop.x), static_cast<int>(bullet[i].pos.screen.leftTop.y),
					static_cast<int>(bullet[i].pos.screen.rightTop.x), static_cast<int>(bullet[i].pos.screen.rightTop.y),
					static_cast<int>(bullet[i].pos.screen.leftBottom.x), static_cast<int>(bullet[i].pos.screen.leftBottom.y),
					static_cast<int>(bullet[i].pos.screen.rightBottom.x), static_cast<int>(bullet[i].pos.screen.rightBottom.y),
					0, 0, 1, 1, ghWhite, 0xFFFFFFFF
				);
			}
		}

		// 爆弾
		for (int i = 0; i < kBombNum; i++)
		{
			if (bomb[i].isBoot || bomb[i].isShot)
			{
				Novice::DrawQuad
				(
					static_cast<int>(bomb[i].pos.screen.leftTop.x) , static_cast<int>(bomb[i].pos.screen.leftTop.y) ,
					static_cast<int>(bomb[i].pos.screen.rightTop.x), static_cast<int>(bomb[i].pos.screen.rightTop.y),
					static_cast<int>(bomb[i].pos.screen.leftBottom.x), static_cast<int>(bomb[i].pos.screen.leftBottom.y),
					static_cast<int>(bomb[i].pos.screen.rightBottom.x), static_cast<int>(bomb[i].pos.screen.rightBottom.y),
					0 , 0 , 1 , 1, ghWhite , 0xFFFFFFFF
				);
			}
		}


		// プレイヤー
		if (player.respawn.isRespawn)
		{
			if (player.damage.isDamage == false)
			{
				Novice::DrawQuad
				(
					static_cast<int>(player.pos.screen.leftTop.x), static_cast<int>(player.pos.screen.leftTop.y),
					static_cast<int>(player.pos.screen.rightTop.x), static_cast<int>(player.pos.screen.rightTop.y),
					static_cast<int>(player.pos.screen.leftBottom.x), static_cast<int>(player.pos.screen.leftBottom.y),
					static_cast<int>(player.pos.screen.rightBottom.x), static_cast<int>(player.pos.screen.rightBottom.y),
					0, 0, 1, 1, ghWhite, 0xFFFFFFFF
				);
			}
			else
			{
				Novice::DrawQuad
				(
					static_cast<int>(player.pos.screen.leftTop.x), static_cast<int>(player.pos.screen.leftTop.y),
					static_cast<int>(player.pos.screen.rightTop.x), static_cast<int>(player.pos.screen.rightTop.y),
					static_cast<int>(player.pos.screen.leftBottom.x), static_cast<int>(player.pos.screen.leftBottom.y),
					static_cast<int>(player.pos.screen.rightBottom.x), static_cast<int>(player.pos.screen.rightBottom.y),
					0, 0, 1, 1, ghWhite, 0x000000FF
				);
			}
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
