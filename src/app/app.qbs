import qbs.base 1.0
import qbs.FileInfo

Application {
    name : project.app_target

    Depends { name: "cpp" }
    Depends { id: qtcore; name: "Qt.core" }
    Depends { name: "Qt"; submodules: ["widgets", "network"] }
    Depends { name: "ImageViewer" }
    Depends { name: "Widgets" }
    Depends { name: "QtSingleApplication" }
    cpp.includePaths : [
        "../../libs/include",
        "../../libs/src/3rdparty/qtsingleapplication/qtsingleapplication"
    ]

    cpp.rpaths: qbs.targetOS.contains("osx")
                ? [ "@executable_path/.." ]
                : [ "$ORIGIN/../lib/" + project.app_target ]
    cpp.cxxLanguageVersion: "c++11"

    files : [
        "application.cpp",
        "application.h",
        "imageviewer.qrc",
        "main.cpp",
        "mainwindow.cpp",
        "mainwindow.h",
        "preferenceswindow.cpp",
        "preferenceswindow.h",
    ]

    Group {
        fileTagsFilter: ["application"]
        qbs.install: true
        qbs.installDir: {
            print(bundle.isBundle);
            return bundle.isBundle
                        ? FileInfo.joinPaths(project.install_app_path, FileInfo.path(bundle.executablePath))
                        : project.install_app_path
        }
    }
    Group {
        name: "Image Viewer.icns"
        condition: qbs.targetOS.contains("osx")
        files: "icons/Image Viewer.icns"
        qbs.install: true
        qbs.installDir: project.install_data_path
    }
    Group {
        name: "imageviewer.rc"
        condition: qbs.targetOS.contains("windows")
        files: "imageviewer.rc"
    }
    Group {
        name: "imageviewer.desktop"
        condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("unix")
        files: "imageviewer.desktop"
        qbs.install: true
        qbs.installDir: "share/applications"
    }
    Group {
        name: "imageviewer.png"
        condition: qbs.targetOS.contains("linux") || qbs.targetOS.contains("unix")
        files: "icons/imageviewer.png"
        qbs.install: true
        qbs.installDir: "share/pixmaps"
    }
}
