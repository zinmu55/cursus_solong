#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for close()

// MinilibXのヘッダーファイル
// 環境によってパスが異なる場合があります。例えば、<X11/mlx.h> のようなパスの場合もあります。
#include "./minilibx_opengl_20191021/mlx.h" // minilibx_opengl_20191021 フォルダにあると仮定

// 定数
#define TILE_SIZE 32 // 各タイルのピクセルサイズ (例: 32x32px)

// エラーメッセージを出力し、プログラムを終了する関数
void error_exit(const char *message) {
    fprintf(stderr, "Error\n%s\n", message);
    exit(EXIT_FAILURE);
}

// マップの構造体 (前回のものと同一)
typedef struct s_map {
    char    **data;
    int     width;
    int     height;
    int     player_count;
    int     exit_count;
    int     collectible_count;
    int     player_pos_x; // プレイヤーの現在位置X
    int     player_pos_y; // プレイヤーの現在位置Y
} t_map;

// MinilibX関連の構造体
typedef struct s_mlx {
    void    *mlx_ptr;   // mlx_init()が返すポインタ
    void    *win_ptr;   // mlx_new_window()が返すポインタ
    t_map   *map;       // マップデータへのポインタ
    
    // 各タイルの画像ポインタ
    void    *img_wall;
    void    *img_floor;
    void    *img_player;
    void    *img_collectible;
    void    *img_exit;
    // 必要に応じて画像の幅と高さも保持
    int     img_w;
    int     img_h;
} t_mlx;


// マップファイルの行数と列数を取得する関数 (前回のものと同一)
void get_map_dimensions(const char *file_path, t_map *map) {
    FILE    *file;
    char    *line = NULL;
    size_t  len = 0;
    ssize_t read;
    int     first_line_len = -1;

    file = fopen(file_path, "r");
    if (!file) {
        error_exit("Could not open map file.");
    }

    map->height = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
            read--;
        }
        if (read == 0) { // 空行のチェック
            error_exit("Map contains empty lines.");
        }
        if (first_line_len == -1) {
            first_line_len = read;
        } else if (read != first_line_len) {
            error_exit("Map is not rectangular.");
        }
        map->height++;
    }
    map->width = first_line_len;

    free(line);
    fclose(file);

    if (map->height == 0 || map->width == 0) {
        error_exit("Map is empty or invalid dimensions.");
    }
}

// マップファイルを読み込み、2次元配列に格納する関数 (前回のものと同一)
void read_map_from_file(const char *file_path, t_map *map) {
    FILE    *file;
    char    *line = NULL;
    size_t  len = 0;
    ssize_t read;
    int     i;

    get_map_dimensions(file_path, map);

    map->data = (char **)malloc(sizeof(char *) * map->height);
    if (!map->data) {
        error_exit("Memory allocation failed for map data.");
    }

    file = fopen(file_path, "r");
    if (!file) {
        error_exit("Could not open map file for reading content.");
    }

    i = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        map->data[i] = strdup(line);
        if (!map->data[i]) {
            // エラー時のメモリ解放処理を追加するべきですが、ここでは簡略化
            error_exit("Memory allocation failed for map row.");
        }
        i++;
    }

    free(line);
    fclose(file);
}

// マップの壁が正しいかチェックする関数 (前回のものと同一)
void check_walls(t_map *map) {
    int x, y;

    for (x = 0; x < map->width; x++) {
        if (map->data[0][x] != '1' || map->data[map->height - 1][x] != '1') {
            error_exit("Map is not surrounded by walls (top/bottom).");
        }
    }
    for (y = 0; y < map->height; y++) {
        if (map->data[y][0] != '1' || map->data[y][map->width - 1] != '1') {
            error_exit("Map is not surrounded by walls (left/right).");
        }
    }
}

// マップ内の要素（P, E, C, 不正文字）をチェックする関数 (前回のものと同一)
void check_elements(t_map *map) {
    int x, y;

    map->player_count = 0;
    map->exit_count = 0;
    map->collectible_count = 0;

    for (y = 0; y < map->height; y++) {
        for (x = 0; x < map->width; x++) {
            char c = map->data[y][x];
            if (c == 'P') {
                map->player_count++;
                map->player_pos_x = x; // プレイヤーの初期位置を保存
                map->player_pos_y = y;
            } else if (c == 'E') {
                map->exit_count++;
            } else if (c == 'C') {
                map->collectible_count++;
            } else if (c != '0' && c != '1') {
                error_exit("Map contains invalid characters. (Allowed: 0, 1, P, E, C)");
            }
        }
    }

    if (map->player_count != 1) {
        error_exit("Map must contain exactly one player ('P').");
    }
    if (map->exit_count != 1) {
        error_exit("Map must contain exactly one exit ('E').");
    }
    if (map->collectible_count < 1) {
        error_exit("Map must contain at least one collectible ('C').");
    }
}

// パスが存在するかどうかをチェックする関数（簡易版、BFS/DFSで本格的に実装が必要）(前回のものと同一)
void check_path_existence(t_map *map) {
    (void)map; 
    printf("Path existence check (simplified): This requires a full BFS/DFS implementation.\n");
    printf("Ensure player can reach all collectibles, then the exit.\n");
}

// 全てのバリデーションを実行する関数 (前回のものと同一)
void validate_map(t_map *map) {
    printf("Validating map...\n");
    check_walls(map);
    check_elements(map);
    check_path_existence(map);
    printf("Map validation successful!\n");
}

// マップデータを解放する関数 (前回のものと同一)
void free_map_data(t_map *map) {
    if (map->data) {
        for (int i = 0; i < map->height; i++) {
            free(map->data[i]);
        }
        free(map->data);
    }
}

// MinilibXのリソースを解放する関数
int close_window(t_mlx *mlx) {
    printf("Closing window and exiting...\n");
    // ここでmlx_destroy_image など、ロードした画像を解放する処理も追加
    // 例: mlx_destroy_image(mlx->mlx_ptr, mlx->img_wall);
    if (mlx->win_ptr)
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
    // mlx_destroy_display(mlx->mlx_ptr); // X11の場合に必要だが、macOSでは不要な場合が多い
    free_map_data(mlx->map); // マップデータもここで解放
    exit(EXIT_SUCCESS);
    return (0);
}

// 画像をロードする関数
void load_images(t_mlx *mlx) {
    int w, h; // 画像の幅と高さはロード時に取得できる

    // ここに画像ファイルのパスを記述
    // 実際にこれらの画像ファイルが存在する必要があります！
    mlx->img_wall = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/wall.xpm", &w, &h);
    mlx->img_floor = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/floor.xpm", &w, &h);
    mlx->img_player = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/player.xpm", &w, &h);
    mlx->img_collectible = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/collectible.xpm", &w, &h);
    mlx->img_exit = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/exit.xpm", &w, &h);

    if (!mlx->img_wall || !mlx->img_floor || !mlx->img_player ||
        !mlx->img_collectible || !mlx->img_exit) {
        error_exit("Failed to load one or more XPM image files. Check paths and formats.");
    }
    mlx->img_w = w; // 全ての画像が同じサイズであると仮定
    mlx->img_h = h;
}

// マップを描画する関数
int render_map(t_mlx *mlx) {
    int x;
    int y;
    void *current_img;

    // 描画前に一度ウィンドウをクリアしたい場合 (常に必要とは限らない)
    // mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);

    y = 0;
    while (y < mlx->map->height) {
        x = 0;
        while (x < mlx->map->width) {
            char cell = mlx->map->data[y][x];
            current_img = NULL;

            if (cell == '1') {
                current_img = mlx->img_wall;
            } else if (cell == '0') {
                current_img = mlx->img_floor;
            } else if (cell == 'P') {
                current_img = mlx->img_player;
            } else if (cell == 'C') {
                current_img = mlx->img_collectible;
            } else if (cell == 'E') {
                current_img = mlx->img_exit;
            }

            if (current_img) {
                mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
                                        current_img, x * TILE_SIZE, y * TILE_SIZE);
            }
            x++;
        }
        y++;
    }
    return (0); // 正常終了
}

// メイン関数
int main(int argc, char **argv) {
    t_map   game_map;
    t_mlx   mlx_data;

    if (argc != 2) {
        error_exit("Usage: ./so_long <map_file.ber>");
    }
    if (strlen(argv[1]) < 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".ber") != 0) {
        error_exit("Map file must have .ber extension.");
    }

    // --- マップの読み込みとバリデーション ---
    read_map_from_file(argv[1], &game_map);
    printf("Map loaded:\n");
    for (int i = 0; i < game_map.height; i++) {
        printf("%s\n", game_map.data[i]);
    }
    printf("Width: %d, Height: %d\n", game_map.width, game_map.height);
    validate_map(&game_map); // バリデーションに成功したら続行

    // --- MinilibXの初期化とウィンドウの準備 ---
    mlx_data.map = &game_map; // mlx構造体にマップデータへのポインタを渡す

    mlx_data.mlx_ptr = mlx_init();
    if (!mlx_data.mlx_ptr) {
        error_exit("Failed to initialize MiniLibX.");
    }

    mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr,
                                     game_map.width * TILE_SIZE,
                                     game_map.height * TILE_SIZE,
                                     "So Long Game");
    if (!mlx_data.win_ptr) {
        error_exit("Failed to create window.");
    }

    // --- 画像のロード ---
    load_images(&mlx_data);

    // --- マップの初回描画 ---
    render_map(&mlx_data);

    // --- イベントフックの設定 ---
    // ウィンドウのクローズボタン (Xボタン) が押されたときの処理
    // 0x110001 は DestroyNotify イベントに対応するマスクとイベントタイプ
    // または #define DestroyNotify 17 と #define StructureNotifyMask (1L<<17) を使う
    mlx_hook(mlx_data.win_ptr, 17, 1L<<17, close_window, &mlx_data);
    
    // KeyPressイベントをキャッチするフック (これは後でプレイヤー移動に使う)
    // mlx_key_hook(mlx_data.win_ptr, handle_keypress, &mlx_data); // handle_keypressは後で実装

    // メインループの開始
    printf("Starting game loop...\n");
    mlx_loop(mlx_data.mlx_ptr); // ここから先はイベントが発生するまでブロックされる

    // ここは通常、mlx_loop()から抜けることはないので到達しないが、
    // 万一抜けた場合に備えてリソースを解放する
    free_map_data(&game_map);
    printf("Program finished successfully.\n"); // これは通常表示されない

    return 0;
}