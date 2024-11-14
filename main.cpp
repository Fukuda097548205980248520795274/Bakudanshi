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

const char kWindowTitle[] = "1228_爆男子";

// ゲームの状態を表す列挙型
enum GameState {
    TITLE,
    MENU,
    STAGE_SELECT,
    GAME,
    GAME_OVER,
    GAME_CLEAR
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, kScreenWtidh, kScreenHeight);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 初期状態はタイトル画面
    GameState gameState = TITLE;

    /*------------------------------
        変数を作り、初期値を入れる
    ------------------------------*/

    // プレイヤー、爆弾、弾、敵、ボスの初期化コード
    Player player;
    Bomb bomb[kBombNum];
    Bullet bullet[kBulletNum];
    Enemy enemy[kEnemyNum];
    Boss boss;

    PlayerInitialValue(&player);
    // Bomb, Bullet, Enemy, Bossの初期化コードをそれぞれ追加

    /*-------------------
        その他の設定
    -------------------*/

    LeftStick leftStick = {};
    int ghWhite = Novice::LoadTexture("./NoviceResources/white1x1.png");

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // Rキーでタイトル画面に戻る
        if (keys[DIK_R] && !preKeys[DIK_R]) {
            gameState = TITLE;
        }

        // シーンごとの処理
        switch (gameState) {
        case TITLE:
            // タイトル画面の描画
            Novice::ScreenPrintf(100,100,"title");
            if (keys[DIK_1]) {  // スペースキーでメニューへ
                gameState = MENU;
            }
            break;

        case MENU:
            // メニュー画面の描画
            Novice::ScreenPrintf(100,100,"menu");
            if (keys[DIK_2]) {  // 1キーでステージセレクトへ
                gameState = STAGE_SELECT;
            }
            break;

        case STAGE_SELECT:
            // ステージセレクトの描画
            Novice::ScreenPrintf(100,100,"stage select");
            if (keys[DIK_3]) {  // 1キーでゲームスタート
                gameState = GAME;
            }
            break;

        case GAME:
            // ゲームのメイン処理
            /*----------------------
                復活、ダメージ処理
            ----------------------*/

            RespawnProcess(&player.respawn);
            DamageProcess(&player);

            for (int i = 0; i < kBombNum; i++) {
                RespawnProcess(&bomb[i].respawn);
            }

            for (int i = 0; i < kBulletNum; i++) {
                RespawnProcess(&bullet[i].respawn);
            }

            for (int i = 0; i < kEnemyNum; i++) {
                RespawnProcess(&enemy[i].respawn);
                DamageProcess(&enemy[i]);
            }

            RespawnProcess(&boss.respawn);
            DamageProcess(&boss);

            /*-------------------
                動きを設定する
            -------------------*/

            BossArrival(&boss, BOSS_TYPE_STAGE_1);
            PlayerMove(&player, keys, preKeys, &leftStick);
            PlayerBombUse(&player, bomb, bullet, keys, preKeys);
            BombMove(bomb, bullet);
            BulletMove(bullet);
            EnemyMove(enemy);
            BossMove(&boss);

            /*-----------------
                当たり判定
            -----------------*/

            // プレイヤー と 爆発の判定など
            // 以下に全ての当たり判定処理を実装
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
            PlayerMove(&player, keys, preKeys, &leftStick);

            // プレイヤーが爆弾を使う
            PlayerBombUse(&player, bomb, bullet, keys, preKeys);

            // 爆弾を動かす
            BombMove(bomb, bullet);

            // 弾を動かす
            BulletMove(bullet);

            // 敵を動かす
            EnemyMove(enemy);

            // ボスを動かす
            BossMove(&boss);


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

            player.pos.screen = CoordinateTransformation(player.pos.world);
            for (int i = 0; i < kBombNum; i++) {
                bomb[i].pos.screen = CoordinateTransformation(bomb[i].pos.world);
            }
            for (int i = 0; i < kBulletNum; i++) {
                bullet[i].pos.screen = CoordinateTransformation(bullet[i].pos.world);
            }
            for (int i = 0; i < kEnemyNum; i++) {
                enemy[i].pos.screen = CoordinateTransformation(enemy[i].pos.world);
            }
            boss.pos.screen = CoordinateTransformation(boss.pos.world);

            /* ゲームオーバー、クリア判定 */
           // if (player.damage.hp <= 0) {
           //     gameState = GAME_OVER;
           // } else if (boss.isDefeated) {
            //    gameState = GAME_CLEAR;
            //}

            if (keys[DIK_S]) {
                gameState = TITLE;
            }

            /* 描画処理 */
            // ここにゲーム中の描画処理を配置
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
                } else
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
                            static_cast<int>(enemy[i].pos.screen.leftTop.x), static_cast<int>(enemy[i].pos.screen.leftTop.y),
                            static_cast<int>(enemy[i].pos.screen.rightTop.x), static_cast<int>(enemy[i].pos.screen.rightTop.y),
                            static_cast<int>(enemy[i].pos.screen.leftBottom.x), static_cast<int>(enemy[i].pos.screen.leftBottom.y),
                            static_cast<int>(enemy[i].pos.screen.rightBottom.x), static_cast<int>(enemy[i].pos.screen.rightBottom.y),
                            0, 0, 1, 1, ghWhite, 0xFFFFFFFF
                        );
                    } else
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
                        static_cast<int>(bomb[i].pos.screen.leftTop.x), static_cast<int>(bomb[i].pos.screen.leftTop.y),
                        static_cast<int>(bomb[i].pos.screen.rightTop.x), static_cast<int>(bomb[i].pos.screen.rightTop.y),
                        static_cast<int>(bomb[i].pos.screen.leftBottom.x), static_cast<int>(bomb[i].pos.screen.leftBottom.y),
                        static_cast<int>(bomb[i].pos.screen.rightBottom.x), static_cast<int>(bomb[i].pos.screen.rightBottom.y),
                        0, 0, 1, 1, ghWhite, 0xFFFFFFFF
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
                } else
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

            break;

        case GAME_OVER:
            Novice::ScreenPrintf(100,100,"game over");
            if (keys[DIK_SPACE]) {
                gameState = TITLE;
            }
            break;

        case GAME_CLEAR:
            Novice::ScreenPrintf(100,100,"game clear");
            if (keys[DIK_SPACE]) {
                gameState = TITLE;
            }
            break;
        }

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
