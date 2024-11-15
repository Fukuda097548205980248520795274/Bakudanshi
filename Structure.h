#pragma once

// 座標
typedef struct Coordinate2
{
	float x;
	float y;
}Coordinate2;

// 矩形の頂点のワールド座標
typedef struct BoxVertexWorld
{
	// 左上
	Coordinate2 leftTop;

	// 右上
	Coordinate2 rightTop;

	// 左下
	Coordinate2 leftBottom;

	// 右下
	Coordinate2 rightBottom;
}BoxVertexWorldPos;

// 矩形の頂点のスクリーン座標
typedef struct BoxVertexScreen
{
	// 左上
	Coordinate2 leftTop;

	// 右上
	Coordinate2 rightTop;

	// 左下
	Coordinate2 leftBottom;

	// 右下
	Coordinate2 rightBottom;
}BoxVertexScreenPos;

// 位置
typedef struct Pos2
{
	// ワールド座標
	BoxVertexWorld world;

	// スクリーン座標
	BoxVertexScreen screen;
}Pos2;


// ベクトル
typedef struct Vec2
{
	float x;
	float y;
}Vec2;

// 矩形の頂点のベクトル
typedef struct BoxVertexVec
{
	// 左上
	Vec2 leftTop;

	// 右上
	Vec2 rightTop;

	// 左下
	Vec2 leftBottom;

	// 右下
	Vec2 rightBottom;
}BoxVertexVec;


// 行列
typedef struct Matrix3x3
{
	float m[3][3];
}Matrix3x3;


// 移動速度
typedef struct Vel2
{
	float x;
	float y;
}Vel2;

// 加速度
typedef struct Acceleration2
{
	float x;
	float y;
}Acceleration2;


// 図形
typedef struct Shape
{
	// 大きさ
	Vec2 scale;

	// 角度
	float theta;

	// 平行移動
	Vec2 translate;
}Shape;


// ジャンプ
typedef struct Jump
{
	// ジャンプしているかどうか（ジャンプフラグ）
	int isJump;

	// Y軸の落下速度
	float fallingVel;

	// ジャンプの回数
	int count;
}Jump;


// 復活
typedef struct Respawn
{
	// 復活しているかどうか（復活フラグ）
	int isRespawn;

	// 復活処理
	int timer;
}Respawn;

// ダメージ
typedef struct Damage
{
	// 体力
	int hp;

	// ダメージが入ったかどうか（ダメージフラグ）
	int isDamage;

	// ダメージ処理
	int timer;
}Damage;


// プレイヤー
typedef struct Player
{
	// 復活
	Respawn respawn;

	// 体力
	Damage damage;

	// 爆弾を持っているか（爆弾所持フラグ）
	int isBomHave;

	// 向いている方向
	int directionNo;


	// 位置
	Pos2 pos;

	// 移動速度
	Vel2 vel;

	// 加速度
	Acceleration2 acceleration;


	// ジャンプ
	Jump jump;


	// 図形
	Shape shape;
}Player;

// 爆弾
typedef struct Bomb
{
	// 復活
	Respawn respawn;

	// 起動したかどうか（起動フラグ）
	int isBoot;

	// 発射したかどうか（発射フラグ）
	int isShot;

	// 制限時間
	int timeLimit;


	// 位置
	Pos2 pos;

	// 移動速度
	Vel2 vel;

	// 加速度
	Acceleration2 acceleration;


	// 図形
	Shape shape;
}Bomb;

// 弾
typedef struct Bullet
{
	// 復活
	Respawn respawn;

	// 発射したかどうか（発射フラグ）
	int isShot;

	// フレーム
	int frame;

	// 種類
	int type;


	// 位置
	Pos2 pos;

	// 移動速度
	Vel2 vel;

	// 加速度
	Acceleration2 acceleration;


	// 図形
	Shape shape;
}Bullet;

// 敵
typedef struct Enemy
{
	// 復活
	Respawn respawn;

	// ダメージ
	Damage damage;

	// 出現しているかどうか（出現フラグ）
	int isArrival;

	// フレーム
	int frame;

	// 種類
	int type;

	// 向いている方向
	int directionNo;


	// 図形
	Shape shape;

	// 位置
	Pos2 pos;

	// 移動速度
	Vel2 vel;

	// 加速度
	Acceleration2 acceleration;
}Enemy;

// ボス
typedef struct Boss
{
	// 復活
	Respawn respawn;

	// ダメージ
	Damage damage;

	// 出現しているかどうか（出現フラグ）
	int isArrival;

	// フレーム
	int frame;

	// 種類
	int type;

	// 向いている方向
	int directionNo;

	// 攻撃しているかどうか（攻撃フラグ）
	int isAttack;

	// 現在の攻撃
	int attackNo;


	// 図形
	Shape shape;

	// 位置
	Pos2 pos;

	// 移動速度
	Vel2 vel;

	// ジャンプ
	Jump jump;

	// 加速度
	Acceleration2 accleration;
}Boss;

// コントローラーの左スティックを感知する変数
typedef struct LeftStick {

	int x;
	int y;

}LeftStick;