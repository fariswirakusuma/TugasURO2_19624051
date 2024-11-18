PENJELASAN PROGRAM OPEN CV:
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Cara Build dan Run:
1. Install dan Download VSCODE,CMake,g++,Intel TBB
2. Download dan extrak Source code ini
3. Edit system envirement untuk CMake,g++,Intel TBB di bagian PATH
4. Buatlah folder pada drive C: misalnya C:/opencv
5. ke Terminal dan command:
   
cd C:/opencv
git clone https://github.com/opencv/opencv_contrib.git
git clone https://github.com/opencv/opencv.git

5. buatlah folder install dan build pada folder C:/opencv
6. ke Terminal lagi dan command:

cd build (pastikan sudah di C:/opencv pada terminal jika belum maka command: cd C:/opencv/build)
cmake -D CMAKE_BUILD_TYPE=Debug -D CMAKE_INSTALL_PREFIX="C:/opencv/install" -D OPENCV_EXTRA_MODULES_PATH="C:/opencv/opencv_contrib/modules" -D WITH_TBB=ON -D WITH_GTK=ON -D WITH_WIN32UI=ON -D WITH_GTK_2_X=OFF -D WITH_GTK_3=OFF C:/opencv/opencv
cmake --build . --config Debug --target INSTALL


7. install extension yang di butuhkan seperti C++,C++ Extension Pack, Cmake, Cmake Tools,.NET Install Tool pada VS Code
8. Edit environment untuk open cv bin dan lib pada PATH(C:\opencv\install\x64\vc17\lib dan C:\opencv\install\x64\vc17\bin) dan buatlah variable baru OpenCV_DIR yang berisi C:\opencv\build
9. buka folder source code dengan VS code
10. nantinya di output folder build akan automatis ter-build
11. pada terminal ketik command berikut:
cd build
cmake --build . --config Debug
12. Untuk run ketik command berikut:
13. cd..
14. .\build\Debug\TugasURO2.exe
15. Nantinya OPENCV akan terun
