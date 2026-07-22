#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Hàm quét và đếm số lượng tệp trong một thư mục cụ thể
void scan_directory(const char* dir_name, const char* label) {
    DIR *dir;
    struct dirent *ent;
    int count = 0;

    printf("\n=== KHO DU LIEU: %s ===\n", label);
    printf("%-5s | %-50s\n", "STT", "TEN FILE (.md)");
    printf("------------------------------------------------------------\n");

    // Mở thư mục (xử lý tên UTF-8 trực tiếp trên Linux runner)
    if ((dir = opendir(dir_name)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            // Bỏ qua các thư mục ẩn hoặc thư mục cha (., ..)
            if (ent->d_name[0] == '.') continue;
            
            // Lọc và chỉ hiển thị các file có đuôi .md
            if (strstr(ent->d_name, ".md") != NULL) {
                count++;
                printf("%-5d | %-50s\n", count, ent->d_name);
            }
        }
        closedir(dir);
    } else {
        printf("[Loi] Khong the mo thu muc: '%s'. Kiem tra lai duong dan.\n", dir_name);
    }
    printf("-> Tong cong: %d thuc the.\n", count);
}

int main(int argc, char *argv[]) {
    printf("============================================================\n");
    printf("      HE THONG QUAN LY THU VIEN TRA DAO (GITHUB CI/CD)      \n");
    printf("============================================================\n");

    // Nếu có truyền đối số khi chạy script
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "tra") == 0) scan_directory("Trà", "TRA");
            else if (strcmp(argv[i], "am") == 0) scan_directory("Ấm trà", "AM TRA");
            else if (strcmp(argv[i], "chen") == 0) scan_directory("Chén trà", "CHEN TRA");
            else if (strcmp(argv[i], "tracu") == 0) scan_directory("Trà cụ", "TRA CU");
        }
    } else {
        // Mặc định: Quét toàn bộ hệ thống
        scan_directory("Trà", "TRA");
        scan_directory("Ấm trà", "AM TRA");
        scan_directory("Chén trà", "CHEN TRA");
        scan_directory("Trà cụ", "TRA CU");
    }

    printf("\n[He thong] Da hoan tat truy xuat du lieu.\n");
    return 0;
}
