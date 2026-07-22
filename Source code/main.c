#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hàm hỗ trợ thay thế chuỗi (dùng để xử lý tiếng Việt có dấu dạng UTF-8)
void replace_string(char *target, const char *needle, const char *replacement) {
    char buffer[1024] = {0};
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);

    while (1) {
        const char *p = strstr(tmp, needle);
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;
        tmp = p + needle_len;
    }
    strcpy(target, buffer);
}

// Hàm chuyển đổi Tiếng Việt có dấu sang không dấu cơ bản (UTF-8)
void remove_diacritics(const char *input, char *output) {
    strcpy(output, input);
    
    // Xử lý các ký tự có dấu cơ bản trong danh sách của bạn
    replace_string(output, "à", "a");
    replace_string(output, "á", "a");
    replace_string(output, "ả", "a");
    replace_string(output, "ã", "a");
    replace_string(output, "ạ", "a");
    replace_string(output, "ấ", "a");
    replace_string(output, "ầ", "a");
    replace_string(output, "ẫ", "a");
    replace_string(output, "ẩ", "a");
    replace_string(output, "ậ", "a");
    replace_string(output, "é", "e");
    replace_string(output, "è", "e");
    replace_string(output, "ụ", "u");
    replace_string(output, "ủ", "u");
    
    // Thay thế khoảng trắng thành dấu gạch ngang cho chuẩn URL GitHub
    replace_string(output, " ", "-");
}

int main() {
    // Tên tài khoản và Repository GitHub của bạn (thay đổi tại đây)
    const char *github_base_url = "https://github.com/Username/RepoName/tree/main/";
    
    // Danh sách các thư mục
    const char *folders[] = {"trà", "chén trà", "ấm trà", "trà cụ"};
    int num_folders = sizeof(folders) / sizeof(folders[0]);

    // Tạo file HTML
    FILE *html_file = fopen("index.html", "w");
    if (html_file == NULL) {
        printf("Loi: Khong the tao file HTML.\n");
        return 1;
    }

    // Ghi cấu trúc HTML và CSS cơ bản
    fprintf(html_file, "<!DOCTYPE html>\n<html lang=\"vi\">\n<head>\n");
    fprintf(html_file, "<meta charset=\"UTF-8\">\n");
    fprintf(html_file, "<title>Quản Lý Thư Mục Trà Cụ</title>\n");
    fprintf(html_file, "<style>\n");
    fprintf(html_file, "body { font-family: Arial, sans-serif; margin: 40px; background-color: #f4f4f9; }\n");
    fprintf(html_file, "table { width: 100%%; border-collapse: collapse; margin-top: 20px; }\n");
    fprintf(html_file, "th, td { border: 1px solid #ddd; padding: 12px; text-align: left; }\n");
    fprintf(html_file, "th { background-color: #4CAF50; color: white; }\n");
    fprintf(html_file, "tr:hover { background-color: #f1f1f1; }\n");
    fprintf(html_file, "a { color: #0066cc; text-decoration: none; font-weight: bold; }\n");
    fprintf(html_file, "a:hover { text-decoration: underline; }\n");
    fprintf(html_file, "</style>\n</head>\n<body>\n");

    fprintf(html_file, "<h2>Danh sách Thư mục Trà Đạo trên GitHub</h2>\n");
    fprintf(html_file, "<table>\n");
    fprintf(html_file, "<tr><th>Tên Thư Mục (Gốc)</th><th>Tên Đã Chuyển Đổi (URL)</th><th>Liên Kết GitHub</th></tr>\n");

    // Xử lý từng thư mục và ghi vào bảng
    for (int i = 0; i < num_folders; i++) {
        char url_name[256];
        remove_diacritics(folders[i], url_name);
        
        fprintf(html_file, "<tr>\n");
        fprintf(html_file, "<td>%s</td>\n", folders[i]);
        fprintf(html_file, "<td>%s</td>\n", url_name);
        fprintf(html_file, "<td><a href=\"%s%s\" target=\"_blank\">Truy cập thư mục %s</a></td>\n", github_base_url, url_name, url_name);
        fprintf(html_file, "</tr>\n");
    }

    fprintf(html_file, "</table>\n");
    fprintf(html_file, "</body>\n</html>\n");
    fclose(html_file);

    printf("Da tao thanh cong trang web 'index.html'!\n");
    printf("Dang mo trinh duyet...\n");

    // Lệnh gọi CMD để mở file HTML trên Windows
    system("start index.html");
    
    // Nếu bạn dùng macOS, thay bằng: system("open index.html");
    // Nếu bạn dùng Linux, thay bằng: system("xdg-open index.html");

    return 0;
}
