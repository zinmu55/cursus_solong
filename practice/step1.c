#include "./solong.h"

int	main(void)
{
	void *mlx_ptr; // MinilibXコネクションへのポインタ
	void *win_ptr; // ウィンドウへのポインタ
	// 1. MinilibXを初期化する
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
	{
		fprintf(stderr, "Error: Could not initialize MinilibX.\n");
		exit(1);
	}
	// 2. 新しいウィンドウを作成する (幅, 高さ, タイトル)
	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "My First MinilibX Window");
	if (win_ptr == NULL)
	{
		fprintf(stderr, "Error: Could not create window.\n");
		exit(1);
	}
	printf("Window created! Press ESC or close the window to exit.\n");
	// 3. MinilibXのイベントループを開始する
	// これにより、ウィンドウが表示され、イベント（キー入力、ウィンドウ閉じなど）が処理される
	mlx_loop(mlx_ptr);
	// mlx_loop()が終了することは稀ですが、念のため
	return (0);
}
