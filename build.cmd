pushd %~dp0

mkdir bin
cd bin
cmake ../src/ -G "Visual Studio 16 2019" -DCMAKE_PREFIX_PATH=C:/Qt/6.2.0/msvc2019_64/
REM -T ClangCL
MSBuild.exe .\tic-tac-toe.vcxproj /p:Configuration=Debug
MSBuild.exe .\tic-tac-toe.vcxproj /p:Configuration=Release
MSBuild.exe .\tic-tac-toe.vcxproj /p:Configuration=RelWithDebInfo
MSBuild.exe .\tic-tac-toe.vcxproj /p:Configuration=MinSizeRel

popd
