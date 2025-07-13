# include "./solong.h"

// 定数
#define TILE_SIZE 32 // 各タイルのピクセルサイズ (例: 32x32px)

// エラーメッセージを出力し、プログラムを終了する関数
void error_exit(const char *message) {
    fprintf(stderr, "Error\n%s\n", message);
    exit(EXIT_FAILURE);
}

// マップの構造体
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

// MinilibX関連の構造体とゲームの状態を保持
typedef struct s_game {
    void    *mlx_ptr;       // mlx_init()が返すポインタ
    void    *win_ptr;       // mlx_new_window()が返すポインタ
    t_map   map;            // マップデータ (ポインタではなく直接格納)
    
    // 各タイルの画像ポインタ
    void    *img_wall;
    void    *img_floor;
    void    *img_player;
    void    *img_collectible;
    void    *img_exit;
    int     img_w;          // ロードされた画像の幅 (全ての画像が同じサイズと仮定)
    int     img_h;          // ロードされた画像の高さ (全ての画像が同じサイズと仮定)

    int     move_count;     // 移動回数
} t_game;

// マップのデータを解放する関数
void free_map_data(t_map *map) {
    if (map && map->data) {
        for (int i = 0; i < map->height; i++) {
            if (map->data[i]) {
                free(map->data[i]);
            }
        }
        free(map->data);
        map->data = NULL; // ポインタをNULLに設定して二重解放を防ぐ
    }
}

// MinilibXのリソースを解放し、プログラムを終了する関数
// mlx_hookのコールバックとして使用される
int close_window(t_game *game) {
    printf("Closing window and exiting...\n");
    // ロードした画像があれば解放（実際には全て解放する必要がある）
    if (game->img_wall) mlx_destroy_image(game->mlx_ptr, game->img_wall);
    if (game->img_floor) mlx_destroy_image(game->mlx_ptr, game->img_floor);
    if (game->img_player) mlx_destroy_image(game->mlx_ptr, game->img_player);
    if (game->img_collectible) mlx_destroy_image(game->mlx_ptr, game->img_collectible);
    if (game->img_exit) mlx_destroy_image(game->mlx_ptr, game->img_exit);
    
    if (game->win_ptr)
        mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    // mlx_destroy_display(game->mlx_ptr); // X11環境の場合に必要だが、macOSでは不要な場合が多い
    free_map_data(&game->map); // マップデータも解放
    exit(EXIT_SUCCESS);
    return (0);
}

// マップファイルの行数と列数を取得する関数
// 矩形性の初期チェックもここで行う
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
        // 改行文字を削除
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

// マップファイルを読み込み、2次元配列に格納する関数
void read_map_from_file(const char *file_path, t_map *map) {
    FILE    *file;
    char    *line = NULL;
    size_t  len = 0;
    ssize_t read;
    int     i;

    get_map_dimensions(file_path, map); // 先にサイズを取得し、矩形性をチェック

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
        if (i < map->height) { // 確保したメモリの範囲内であることを確認
            map->data[i] = strdup(line);
            if (!map->data[i]) {
                free(line);
                fclose(file);
                // これまでに確保したマップデータを解放
                while (--i >= 0) free(map->data[i]);
                free(map->data);
                error_exit("Memory allocation failed for map row.");
            }
        }
        i++;
    }

    free(line);
    fclose(file);
}

// マップの壁が正しいかチェックする関数
void check_walls(t_map *map) {
    int x, y;

    // 上下の壁をチェック
    for (x = 0; x < map->width; x++) {
        if (map->data[0][x] != '1' || map->data[map->height - 1][x] != '1') {
            error_exit("Map is not surrounded by walls (top/bottom).");
        }
    }

    // 左右の壁をチェック
    for (y = 0; y < map->height; y++) {
        if (map->data[y][0] != '1' || map->data[y][map->width - 1] != '1') {
            error_exit("Map is not surrounded by walls (left/right).");
        }
    }
}

// マップ内の要素（P, E, C, 不正文字）をチェックする関数
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

// パスが存在するかどうかをチェックする関数（簡易版、BFS/DFSで本格的に実装が必要）
void check_path_existence(t_map *map) {
    (void)map; // 未使用引数警告を抑制
    printf("Path existence check (simplified): This requires a full BFS/DFS implementation.\n");
    printf("Ensure player can reach all collectibles, then the exit.\n");
}

// 全てのバリデーションを実行する関数
void validate_map(t_map *map) {
    printf("Validating map...\n");
    check_walls(map);
    check_elements(map);
    check_path_existence(map); // これは後で本格的に実装が必要です
    printf("Map validation successful!\n");
}

// 画像をロードする関数
void load_images(t_game *game) {
    int w, h; // 画像の幅と高さはロード時に取得できる

    // ここに画像ファイルのパスを記述し、実際にそれらのファイルが存在する必要があります！
    // 例: "./textures/wall.xpm" のように、実行ファイルからの相対パス
    game->img_wall = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/wall.xpm", &w, &h);
    game->img_floor = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/floor.xpm", &w, &h);
    game->img_player = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/player.xpm", &w, &h);
    game->img_collectible = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/collectible.xpm", &w, &h);
    game->img_exit = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/exit.xpm", &w, &h);

    if (!game->img_wall || !game->img_floor || !game->img_player ||
        !game->img_collectible || !game->img_exit) {
        // エラーが発生した場合、適切なクリーンアップをしてから終了
        error_exit("Failed to load one or more XPM image files. Check paths and formats.");
    }
    game->img_w = w; // 全ての画像が同じサイズであると仮定
    game->img_h = h;
}

// マップを描画する関数
int render_map(t_game *game) {
    int x;
    int y;
    void *current_img;

    y = 0;
    while (y < game->map.height) {
        x = 0;
        while (x < game->map.width) {
            char cell = game->map.data[y][x];
            current_img = NULL;

            if (cell == '1') {
                current_img = game->img_wall;
            } else if (cell == '0') {
                current_img = game->img_floor;
            } else if (cell == 'P') {
                current_img = game->img_player;
            } else if (cell == 'C') {
                current_img = game->img_collectible;
            } else if (cell == 'E') {
                current_img = game->img_exit;
            }

            if (current_img) {
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                                        current_img, x * TILE_SIZE, y * TILE_SIZE);
            }
            x++;
        }
        y++;
    }
    return (0); // 正常終了
}

// キープレスイベントを処理する関数（今後プレイヤー移動を実装する場所）
int handle_keypress(int keycode, t_game *game) {
    printf("Key pressed: %d\n", keycode);
    if (keycode == 53) { // ESCキー (macOSでのキーコード)
        close_window(game); // プログラムを終了
    }
    // ここにW, A, S, Dキーなどの移動ロジックを追加
    // 例:
    // if (keycode == 13) { // Wキー (macOS)
    //     // 上に移動するロジック
    //     printf("Move up!\n");
    //     game->move_count++;
    // }
    // printf("Moves: %d\n", game->move_count);
    return (0);
}


// メイン関数
int main(int argc, char **argv) {
    t_game   game_data; // t_game構造体のインスタンスを宣言

    // プロジェクトの初期設定
    game_data.move_count = 0; // 移動回数を初期化

    // --- 引数のチェック ---
    if (argc != 2) {
        error_exit("Usage: ./so_long <map_file.ber>");
    }
    if (strlen(argv[1]) < 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".ber") != 0) {
        error_exit("Map file must have .ber extension.");
    }

    // --- マップの読み込みとバリデーション ---
    read_map_from_file(argv[1], &game_data.map); // t_game.mapに直接読み込む
    printf("Map loaded:\n");
    for (int i = 0; i < game_data.map.height; i++) {
        printf("%s\n", game_data.map.data[i]);
    }
    printf("Width: %d, Height: %d\n", game_data.map.width, game_data.map.height);
    validate_map(&game_data.map); // バリデーションに成功したら続行

    // --- MinilibXの初期化とウィンドウの準備 ---
    game_data.mlx_ptr = mlx_init();
    if (!game_data.mlx_ptr) {
        error_exit("Failed to initialize MiniLibX.");
    }

    game_data.win_ptr = mlx_new_window(game_data.mlx_ptr,
                                     game_data.map.width * TILE_SIZE,
                                     game_data.map.height * TILE_SIZE,
                                     "So Long Game");
    if (!game_data.win_ptr) {
        error_exit("Failed to create window.");
    }

    // --- 画像のロード ---
    load_images(&game_data);

    // --- マップの初回描画 ---
    render_map(&game_data);

    // --- イベントフックの設定 ---
    // ウィンドウのクローズボタン (Xボタン) が押されたときの処理
    // イベントタイプ: 17 (DestroyNotify), マスク: (1L<<17) (StructureNotifyMask)
    mlx_hook(game_data.win_ptr, 17, 1L<<17, close_window, &game_data);
    
    // キープレスイベントをキャッチするフック
    // イベントタイプ: 2 (KeyPress), マスク: (1L<<0) (KeyPressMask)
    mlx_hook(game_data.win_ptr, 2, 1L<<0, handle_keypress, &game_data);

    // メインループの開始
    printf("Starting game loop...\n");
    mlx_loop(game_data.mlx_ptr); // ここから先はイベントが発生するまでブロックされる

    // ここは通常、mlx_loop()から抜けることはないので到達しない
    // もし到達した場合に備えてリソースを解放
    free_map_data(&game_data.map);
    printf("Program finished successfully.\n"); 

    return 0;
}