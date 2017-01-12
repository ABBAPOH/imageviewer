import qbs.base 1.0

Project {
    property string app_target: qbs.targetOS.contains("osx") ? "Image Viewer" : "imageviewer"
    property string install_app_path: qbs.targetOS.contains("osx") ? "" : "bin"
    property string install_binary_path: {
        if (qbs.targetOS.contains("osx"))
            return app_target + ".app/Contents/MacOS"
        else
            return install_app_path
    }
    property string lib_suffix: qbs.targetOS.contains("linux") ? (qbs.architecture == "x86_64" ? "64" : "") : ""
    property string install_library_path: {
        if (qbs.targetOS.contains("osx"))
            return app_target + ".app/Contents/Frameworks"
        else if (qbs.targetOS.contains("windows"))
            return install_app_path
        else
            return "lib" + lib_suffix + "/" + app_target
    }
    property string install_plugin_path: {
        if (qbs.targetOS.contains("osx"))
            return app_target + ".app/Contents/PlugIns"
        else if (qbs.targetOS.contains("windows"))
            return "plugins"
        else
            return install_library_path + "/plugins"
    }
    property string install_data_path: {
        if (qbs.targetOS.contains("osx"))
            return app_target + ".app/Contents/Resources"
        else if (qbs.targetOS.contains("windows"))
            return "resources"
        else
            return "share/" + app_target
    }
    property string installNamePrefix: "@executable_path/../Frameworks/"

    references: [
        "libs/src/3rdparty/qtsingleapplication/qtsingleapplication.qbs",
        "libs/src/imageviewer/imageviewer.qbs",
        "libs/src/widgets/widgets.qbs",
        "src/app/app.qbs"
    ]

    Product {
        name: "translations"
        type: "qm"
        Depends { name: "Qt.core" }
        files: [
            "libs/src/imageviewer/translations/*.ts",
            "libs/src/widgets/translations/*.ts",
            "src/app/translations/*.ts"
        ]

        Group {
            fileTagsFilter: product.type
            qbs.install: true
            qbs.installDir: project.install_data_path + "/translations"
        }
    }
}
