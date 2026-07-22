#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_ITEMS 100

// Cấu trúc định nghĩa danh mục thư viện trà
typedef struct {
    char category[50];
    char path[100];
} TeaLibrary;

// Hàm thiết lập giao diện bảng ASCII
void renderTable(TeaLibrary items[], int size) {
    printf("+--------------------------------+------------------------------------------------+\n");
    printf("| Danh Mục                       | Đường Dẫn Tương Đối                            |\n");
    printf("+--------------------------------+------------------------------------------------+\n");
    
    for (int i = 0; i < size; i++) {
        printf("| %-30s | %-46s |\n", items[i].category, items[i].path);
    }
    
    printf("+--------------------------------+------------------------------------------------+\n");
}

int main() {
    // Thiết lập bảng mã UTF-8 cho dòng lệnh Windows
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    TeaLibrary library[MAX_ITEMS];
    int count = 0;

    // Mở thư mục hiện tại
    DIR *dir = opendir(".");
    if (dir == NULL) {
        printf("Lỗi hệ thống: Không thể cấp phát luồng đọc thư mục.\n");
        return EXIT_FAILURE;
    }

    struct dirent *ent;
    struct stat path_stat;

    // Quét động các thành phần bên trong
    while ((ent = readdir(dir)) != NULL) {
        // Bỏ qua các thành phần ẩn của hệ thống (ví dụ: .git, .github, ., ..)
        if (ent->d_name[0] == '.') {
            continue;
        }

        // Truy xuất metadata để xác minh đối tượng là thư mục
        stat(ent->d_name, &path_stat);
        if (S_ISDIR(path_stat.st_mode)) {
            strncpy(library[count].category, ent->d_name, sizeof(library[count].category) - 1);
            snprintf(library[count].path, sizeof(library[count].path), "./%s", ent->d_name);
            
            count++;
            if (count >= MAX_ITEMS) break;
        }
    }
    closedir(dir);

    printf("\nHệ Thống Quản Lý Thư Viện Trà (Quét Tự Động)\n");
    if (count > 0) {
        renderTable(library, count);
    } else {
        printf("Không tìm thấy cấu trúc dữ liệu hợp lệ trong vùng nhớ.\n");
    }

    return 0;
}
