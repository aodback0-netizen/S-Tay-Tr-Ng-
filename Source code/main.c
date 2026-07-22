#include <stdio.h>
#include <stdlib.h>

// Cấu trúc định nghĩa danh mục thư viện trà
typedef struct {
    char category[30];
    char path[100];
} TeaLibrary;

// Hàm thiết lập giao diện bảng ASCII
void renderTable(TeaLibrary items[], int size) {
    printf("+--------------------------------+------------------------------------------------+\n");
    printf("| Danh Muc                       | Duong Dan Tuong Doi                            |\n");
    printf("+--------------------------------+------------------------------------------------+\n");
    
    for (int i = 0; i < size; i++) {
        // Sử dụng định dạng %-30s và %-46s để căn lề trái và cố định độ rộng cột
        printf("| %-30s | %-46s |\n", items[i].category, items[i].path);
    }
    
    printf("+--------------------------------+------------------------------------------------+\n");
}

int main() {
    // Khởi tạo dữ liệu ánh xạ với cấu trúc kho lưu trữ thực tế
    TeaLibrary library[] = {
        {"Tra", "./Tra"},
        {"Am tra", "./Am tra"},
        {"Chen tra", "./Chen tra"},
        {"Tra cu", "./Tra cu"}
    };
    
    int size = sizeof(library) / sizeof(library[0]);

    printf("\nHe Thong Quan Ly Thu Vien Tra\n");
    renderTable(library, size);

    return 0;
}
