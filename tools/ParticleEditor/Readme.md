Compiling the Particle Editor on Windows
========================================

- Install Visual Studio version of Qt: http://download.qt-project.org/official_releases/qt/5.2/5.2.1/ (qt-opensource-windows-x86-msvc2010-5.2.1.exe)
- Install Qt Visual Studio Addin: http://download.qt-project.org/official_releases/vsaddin/ (qt-vs-addin-1.2.2-opensource.exe)
- Open Visual Studio and go to: Qt5 > Qt Options
- Use the 'Add' button to add a new version of Qt to the addin, you have to add the newly installed version of Qt (the one special for Visual Studio) I had to add C:\Qt\Qt5.2.1\5.2.1\mvsc2010, but you will have to find the right path. The addin will tell you if it is the right path or not.
- Now you can open the Solution in tools/ParticleEditor
