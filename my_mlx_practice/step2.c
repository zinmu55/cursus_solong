#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

// パスを修正// MinilibXの構造体を定義（ゲームの状態を保持するため）
// この struct は、フック関数に渡す情報をまとめるのに便利です。
typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	// 他のゲーム情報（マップ、プレイヤー位置など）は後で追加
}			t_game;

// ウィンドウを閉じるイベント（Xボタン）のフック関数
// MinilibXは特定のイベントに対して整数値を返します
// 17 は DestroyNotify イベントのタイプ
int	close_window_hook(t_game *game)
{
	printf("Window closed via X button or ESC. Exiting...\n");
	// ウィンドウを破棄
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	// 必要に応じて他のリソース（画像など）もここで解放
	exit(0);
	return (0);
}

// キープレスイベントのフック関数
// keycode は押されたキーの識別コード
int	key_press_hook(int keycode, t_game *game)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == 65307)
	{ // Linux環境でのESCキーの一般的なキーコード
		printf("ESC key pressed. Exiting...\n");
		close_window_hook(game); // ウィンドウを閉じる関数を呼び出す
	}
	return (0);
}

int	main(void)
{
	t_game game; // t_game構造体のインスタンス
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		error_exit("Could not initialize MinilibX.");
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600,
			"MinilibX with Events");
	if (game.win_ptr == NULL)
		error_exit("Could not create window.");
	printf("Window created! Try pressing ESC or closing the window.\n");
	// イベントフックを設定する
	// mlx_hook(ウィンドウポインタ, イベントタイプ, イベントマスク, コールバック関数, 関数に渡す引数)
	// 17 (DestroyNotify) はウィンドウのXボタンクリック
	// 1L<<17 (StructureNotifyMask) はそのイベントのマスク
	mlx_hook(game.win_ptr, 17, 1L << 17, close_window_hook, &game);
	// 2 (KeyPress) はキーが押されたイベント
	// 1L<<0 (KeyPressMask) はそのイベントのマスク
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_hook, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}

// エラー終了関数（前のステップからコピペ）
void	error_exit(const char *message)
{
	fprintf(stderr, "Error\n%s\n", message);
	exit(EXIT_FAILURE);
}
