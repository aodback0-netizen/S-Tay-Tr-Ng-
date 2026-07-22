#include <stdio.h>
#include <stdlib.h>

// Tích hợp thư viện xử lý bảng mã cho môi trường Windows
#ifdef _WIN32
#include <windows.h>
#endif

// Cấu trúc định nghĩa danh mục thư viện trà
typedef struct {
    char category[30];
    char path[100];
} TeaLibrary;

// Hàm thiết lập giao diện bảng ASCII
void renderTable(TeaLibrary items[], int size) {
    printf("+--------------------------------+------------------------------------------------+\n");
    printf("| Danh Mục                       | Đường Dẫn Tương Đối                            |\n");
    printf("+--------------------------------+------------------------------------------------+\n");
    
    for (int i = 0; i < size; i++) {
        // Căn lề trái các chuỗi UTF-8. Lưu ý: Ký tự có dấu có thể chiếm nhiều byte hơn,
        // nhưng với giao diện console cơ bản, %-30s vẫn giữ được cấu trúc lưới ở mức ổn định.
        printf("| %-30s | %-46s |\n", items[i].category, items[i].path);
    }
    
    printf("+--------------------------------+------------------------------------------------+\n");
}

int main() {
    // Thiết lập bảng mã UTF-8 cho dòng lệnh trước khi in dữ liệu
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    // Khởi tạo dữ liệu ánh xạ tiếng Việt có dấu
    TeaLibrary library[] = {
        {"Trà", "./Tra"},
        {"Ấm trà", "./Am tra"},
        {"Chén trà", "./Chen tra"},
        {"Trà cụ", "./Tra cu"}
    };
    
    int size = sizeof(library) / sizeof(library[0]);

    printf("\nHệ Thống Quản Lý Thư Viện Trà\n");
    renderTable(library, size);

    return 0;
}
