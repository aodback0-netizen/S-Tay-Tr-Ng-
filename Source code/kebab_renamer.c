#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>
#include <stdbool.h>

// Bảng ánh xạ ký tự tiếng Việt có dấu sang không dấu (Unicode)
const wchar_t* VIETNAMESE_CHARS = L"áàảãạăắằẳẵặâấầẩẫậđéèẻẽẹêếềểễệíìỉĩịóòỏõọôốồổỗộơớờởỡợúùủũụưứừửữựýỳỷỹỵÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬĐÉÈẺẼẸÊẾỀỂỄỆÍÌỈĨỊÓÒỎÕỌÔỐỒỔỖỘƠỚỜỞỠỢÚÙỦŨỤƯỨỪỬỮỰÝỲỶỸỴ";
const wchar_t* ENGLISH_CHARS    = L"aaaaaaaaaaaaaaaaadeeeeeeeeeeeiiiiiooooooooooooooooouuuuuuuuuuuyyyyyaaaaaaaaaaaaaaaaadeeeeeeeeeeeiiiiiooooooooooooooooouuuuuuuuuuuyyyyy";

// Hướng dẫn: Hàm thay thế các ký tự có dấu thành không dấu và chuyển thành chữ thường
void normalize_string(wchar_t* str) {
    for (int i = 0; str[i] != L'\0'; i++) {
        // Chuyển khoảng trắng thành gạch ngang
        if (str[i] == L' ') {
            str[i] = L'-';
            continue;
        }

        // Ép kiểu về chữ thường cho các ký tự ASCII cơ bản
        if (str[i] >= L'A' && str[i] <= L'Z') {
            str[i] = str[i] + 32;
        }

        // Tìm và thay thế ký tự tiếng Việt
        for (int j = 0; VIETNAMESE_CHARS[j] != L'\0'; j++) {
            if (str[i] == VIETNAMESE_CHARS[j]) {
                str[i] = ENGLISH_CHARS[j];
                break;
            }
        }
    }
}

// Hướng dẫn: Hàm duyệt thư mục và đổi tên file
void process_directory(const wchar_t* path) {
    WIN32_FIND_DATAW findFileData;
    wchar_t searchPath[MAX_PATH];
    
    // Nối chuỗi để tìm toàn bộ file/thư mục bên trong đường dẫn hiện tại (*.*)
    swprintf(searchPath, MAX_PATH, L"%s\\*.*", path);
    
    HANDLE hFind = FindFirstFileW(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        // Bỏ qua thư mục hiện tại (.) và thư mục cha (..)
        if (wcscmp(findFileData.cFileName, L".") == 0 || wcscmp(findFileData.cFileName, L"..") == 0) {
            continue;
        }

        wchar_t fullPath[MAX_PATH];
        swprintf(fullPath, MAX_PATH, L"%s\\%s", path, findFileData.cFileName);

        // Nếu là thư mục, thực hiện đệ quy để đi sâu vào trong
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            process_directory(fullPath);
        } 
        // Nếu là file, kiểm tra đuôi .md và bỏ qua file README.md
        else {
            wchar_t* ext = wcsrchr(findFileData.cFileName, L'.');
            if (ext != NULL && _wcsicmp(ext, L".md") == 0 && _wcsicmp(findFileData.cFileName, L"README.md") != 0) {
                
                wchar_t newFileName[MAX_PATH];
                wcscpy(newFileName, findFileData.cFileName);
                
                // Tiền xử lý tên file mới
                normalize_string(newFileName);

                if (wcscmp(findFileData.cFileName, newFileName) != 0) {
                    wchar_t newFullPath[MAX_PATH];
                    swprintf(newFullPath, MAX_PATH, L"%s\\%s", path, newFileName);
                    
                    // Thực thi đổi tên bằng Windows API
                    if (MoveFileW(fullPath, newFullPath)) {
                        wprintf(L"Da doi ten: %s -> %s\n", findFileData.cFileName, newFileName);
                    } else {
                        wprintf(L"Loi khi doi ten file: %s\n", findFileData.cFileName);
                    }
                }
            }
        }
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
}

int main() {
    // Hướng dẫn: Cấu hình Console để hiển thị Unicode một cách ổn định nhất có thể
    SetConsoleOutputCP(CP_UTF8);

    wchar_t currentDir[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, currentDir);
    
    wprintf(L"Dang xu ly thu muc: %s\n", currentDir);
    process_directory(currentDir);
    
    wprintf(L"Hoan tat qua trinh toi uu ten file!\n");
    return 0;
}
