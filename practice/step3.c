#include "./solong.h"

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_game;

// エラー終了関数（変更なし）
void	error_exit(const char *message)
{
	fprintf(stderr, "Error\n%s\n", message);
	exit(EXIT_FAILURE);
}

// close_window_hook, key_press_hook は変更なし

// 描画関数 (exposeイベントで自動的に呼び出されることもある)
int	draw_stuff(t_game *game)
{
	// ウィンドウをクリア (任意、描画前に残像を消す場合)
	// mlx_clear_window(game->mlx_ptr, game->win_ptr);
	// 中央に赤いピクセルを描画 (x, y, 色(0xRRGGBB))
	mlx_pixel_put(game->mlx_ptr, game->win_ptr, 400, 300, 0xFF0000); // 赤色
	// 複数のピクセルで四角形を描画
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			mlx_pixel_put(game->mlx_ptr, game->win_ptr, 100 + i, 100 + j,
				0x00FF00); // 緑色
		}
	}
	return (0);
}

int	main(void)
{
	t_game	game;

	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		error_exit("Could not initialize MinilibX.");
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "MinilibX Pixels");
	if (game.win_ptr == NULL)
		error_exit("Could not create window.");
	printf("Window created! Look for pixels.\n");
	// イベントフックを設定
	mlx_hook(game.win_ptr, 17, 1L << 17, close_window_hook, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_hook, &game);
	// 描画関数をexposeイベントにフック (ウィンドウが再描画される際に呼び出される)
	// 12 (Expose) はウィンドウが再描画されるべきイベントタイプ
	// 1L<<15 (ExposureMask) はそのイベントのマスク
	mlx_hook(game.win_ptr, 12, 1L << 15, draw_stuff, &game);
	// 初回描画を明示的に呼び出す (exposeイベントは必ずしも初回に発生しないため)
	draw_stuff(&game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
