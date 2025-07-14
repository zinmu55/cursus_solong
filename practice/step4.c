#include "./solong.h"

typedef struct s_game {
    void *mlx_ptr;
    void *win_ptr;
    void *my_img; // ロードする画像へのポインタ
    int  img_width;
    int  img_height;
} t_game;

// エラー終了関数（変更なし）
void error_exit(const char *message) {
    fprintf(stderr, "Error\n%s\n", message);
    exit(EXIT_FAILURE);
}

// close_window_hook, key_press_hook は変更なし

// 描画関数 (今回は画像をメインに)
int draw_image(t_game *game) {
    // ウィンドウをクリア (残像を消すため)
    mlx_clear_window(game->mlx_ptr, game->win_ptr);

    // ロードした画像をウィンドウの左上 (0,0) に描画
    // mlx_put_image_to_window(mlx_ptr, win_ptr, image_ptr, x座標, y座標)
    if (game->my_img) {
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                                game->my_img, 0, 0);

        // 画面中央に移動させて描画することもできる
        // mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
        //                         game->my_img,
        //                         (800 - game->img_width) / 2,
        //                         (600 - game->img_height) / 2);
    }
    return (0);
}

int main() {
    t_game game;

    game.mlx_ptr = mlx_init();
    if (game.mlx_ptr == NULL) error_exit("Could not initialize MinilibX.");

    game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "MinilibX Images");
    if (game.win_ptr == NULL) error_exit("Could not create window.");

    // XPM画像をロード
    // mlx_xpm_file_to_image(mlx_ptr, ファイルパス, &幅, &高さ)
    game.my_img = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/my_image.xpm", &game.img_width, &game.img_height);
    if (game.my_img == NULL) {
        error_exit("Failed to load XPM image. Check path and format.");
    }
    printf("Image loaded: width=%d, height=%d\n", game.img_width, game.img_height);


    // イベントフックを設定
    mlx_hook(game.win_ptr, 17, 1L<<17, close_window_hook, &game);
    mlx_hook(game.win_ptr, 2, 1L<<0, key_press_hook, &game);
    mlx_hook(game.win_ptr, 12, 1L<<15, draw_image, &game); // Exposeイベントで描画

    // 初回描画を明示的に呼び出す
    draw_image(&game);

    mlx_loop(game.mlx_ptr);

    // プログラム終了時に画像を解放
    if (game.my_img) {
        mlx_destroy_image(game.mlx_ptr, game.my_img);
    }

    return 0;
}