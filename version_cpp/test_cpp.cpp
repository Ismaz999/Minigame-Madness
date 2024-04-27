#include <iostream>
#include "test_cpp.h"
#include <windows.h>

int test_fonction() {

    int taille;
    std::cout << "Entrez la taille du tableau : ";
    std::cin >> taille;


    int* monTableau = new int[taille];

    std::cout << "Entrez " << taille << " entiers :" << std::endl;
    for (int i = 0; i < taille; i++){
        int entier = 0;
        std::cin >> entier;
        monTableau[i] = entier;
    }

    int somme = 0;

    for (int j = 0; j < taille; j++){
        somme += monTableau[j];
    }
    std::cout << "Somme des éléments : " << somme << std::endl;

    double moyenne = 0;
    moyenne = somme / taille;
    std::cout << "Moyenne des éléments : " << moyenne << std::endl;

    delete[] monTableau;
    return moyenne;
}

void CaptureScreen(const std::wstring& fileName)
{
    // On récupere les dimensions de lecran
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Créer un contexte de périphérique compatible avec l'écran
    HDC hScreenDC = GetDC(NULL);
    HDC hMemDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenWidth, screenHeight); // on crée un bitmap (un calque) qui a les meme dimensions que notre cran
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

    // Copier l'écran vers le contexte de mémoire
    BitBlt(hMemDC, 0, 0, 960, 720, hScreenDC, 960, 182, SRCCOPY);

    // Sauvegarder le contexte de mémoire dans un fichier bitmap
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenWidth;
    bi.biHeight = -screenHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    HANDLE hFile = CreateFileW(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        DWORD dwBytesWritten;
        BITMAPFILEHEADER bfh;
        bfh.bfType = 0x4D42; // "BM"
        bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + screenWidth * screenHeight * 3;
        bfh.bfReserved1 = 0;
        bfh.bfReserved2 = 0;
        bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        // Write the bitmap file header
        WriteFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);

        // Write the bitmap info header
        WriteFile(hFile, &bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);

        // Write the bitmap data
        DWORD dwBmpSize = ((screenWidth * 24 + 31) / 32) * 4 * screenHeight; // DWORD aligned
        BYTE* pData = new BYTE[dwBmpSize];
        GetDIBits(hMemDC, hBitmap, 0, screenHeight, pData, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
        WriteFile(hFile, pData, dwBmpSize, &dwBytesWritten, NULL);

        // Cleanup
        delete[] pData;
        CloseHandle(hFile);
    }
    else
    {
        std::cerr << "Error: Could not create file." << std::endl;
    }

    // Libérer les ressources
    SelectObject(hMemDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemDC);
    ReleaseDC(NULL, hScreenDC);
}
