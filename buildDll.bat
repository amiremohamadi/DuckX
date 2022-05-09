@setlocal
call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat"

mkdir c:\r
mkdir b
cd b
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=c:\r -DBUILD_SAMPLES:BOOL=ON -DCMAKE_DEBUG_POSTFIX:STRING="D" -DBUILD_SHARED_LIBS:BOOL="1" ..
devenv.com duckx.sln /build "Debug|x64" /project INSTALL.vcxproj
devenv.com duckx.sln /build "Release|x64" /project INSTALL.vcxproj
