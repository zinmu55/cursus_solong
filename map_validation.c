#include <stdio.h>   // For file operations (fopen, fclose, getline, etc.)
#include <stdlib.h>  // For memory allocation (malloc, free, exit)
#include <string.h>  // For string operations (strlen, strchr, strdup)

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
} t_map;

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
        // get_map_dimensions で開けているはずだが、念のため
        error_exit("Could not open map file for reading content.");
    }

    i = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        map->data[i] = strdup(line);
        if (!map->data[i]) {
            // ここで以前に確保したメモリを解放するロジックも必要だが、簡略化
            error_exit("Memory allocation failed for map row.");
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
// 現段階ではプレースホルダ。実際のゲームではBFSやDFSアルゴリズムを使用して、
// プレイヤーが全てのコレクタブルを回収後に出口に到達可能かチェックします。
void check_path_existence(t_map *map) {
    // ここにBFS (幅優先探索) や DFS (深さ優先探索) を実装し、
    // プレイヤーの開始位置から全てのコレクタブル、そして出口への到達可能性を検証します。
    // 例:
    // 1. Pから到達可能な全てのマスをマークする。
    // 2. 全てのCがマークされているか確認する。
    // 3. Eがマークされているか確認する。
    // 詳細な実装は複雑なため、ここでは省略します。
    // if (!path_found) {
    //     error_exit("No valid path found to collectibles or exit.");
    // }
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

// マップデータを解放する関数
void free_map_data(t_map *map) {
    if (map->data) {
        for (int i = 0; i < map->height; i++) {
            free(map->data[i]);
        }
        free(map->data);
    }
}

// メイン関数
int main(int argc, char **argv) {
    t_map game_map;

    // 引数のチェック
    if (argc != 2) {
        error_exit("Usage: ./so_long <map_file.ber>");
    }

    // マップファイルの拡張子チェック (簡易版)
    if (strlen(argv[1]) < 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".ber") != 0) {
        error_exit("Map file must have .ber extension.");
    }

    // マップの読み込み
    read_map_from_file(argv[1], &game_map);
    printf("Map loaded:\n");
    for (int i = 0; i < game_map.height; i++) {
        printf("%s\n", game_map.data[i]);
    }
    printf("Width: %d, Height: %d\n", game_map.width, game_map.height);

    // マップのバリデーション
    validate_map(&game_map);

    // メモリの解放
    free_map_data(&game_map);
    printf("Program finished successfully.\n");

    return 0;
}