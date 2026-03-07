#!/bin/bash

#===============================================================================
# ConfigWatcher 打包脚本
# 功能：编译并打包 ConfigWatcher 为可直接安装的软件包
# 支持：Linux (AppImage, DEB, RPM)
#===============================================================================

set -e

# 配置
APP_NAME="ConfigWatcher"
APP_VERSION="1.0.0"
APP_AUTHOR="张宇鹏"
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${PROJECT_DIR}/build_package"
INSTALL_DIR="${BUILD_DIR}/install"
APPIMAGE_DIR="${BUILD_DIR}/AppImage"

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

log_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
log_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
log_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
log_error() { echo -e "${RED}[ERROR]${NC} $1"; }

# 清理函数
cleanup() {
    log_info "清理临时目录..."
    rm -rf "${BUILD_DIR}"
}

# 检查依赖
check_dependencies() {
    log_info "检查依赖..."
    local missing_deps=()
    
    # 检查 Qt 相关
    if ! command -v qmake &> /dev/null; then
        missing_deps+=("qt5-qmake")
    fi
    
    if ! command -v lrelease &> /dev/null; then
        missing_deps+=("qttools5-dev-tools")
    fi
    
    # 检查打包工具
    if ! command -v linuxdeployqt &> /dev/null && \
       ! command -v appimagetool &> /dev/null; then
        log_warning "未找到 linuxdeployqt 或 appimagetool，将使用基础打包方式"
    fi
    
    if [ ${#missing_deps[@]} -ne 0 ]; then
        log_error "缺少依赖：${missing_deps[*]}"
        log_info "请运行以下命令安装依赖："
        echo "  sudo apt-get install qt5-default qt5-qmake qttools5-dev-tools libx11-dev libxcb1-dev"
        exit 1
    fi
    
    log_success "依赖检查通过"
}

# 编译项目
build_project() {
    log_info "开始编译项目..."
    
    cd "${PROJECT_DIR}"
    
    # 清理之前的构建
    log_info "清理之前的构建..."
    make clean 2>/dev/null || true
    rm -rf bin/ConfigWatcher
    
    # 生成 Makefile
    log_info "运行 qmake..."
    qmake ConfigWatcher.pro
    
    # 编译
    log_info "编译中..."
    make -j$(nproc)
    
    # 检查编译结果
    if [ ! -f "bin/ConfigWatcher" ]; then
        log_error "编译失败，未找到可执行文件"
        exit 1
    fi
    
    log_success "编译完成：bin/ConfigWatcher"
}

# 创建安装包目录结构
create_package_structure() {
    log_info "创建安装包目录结构..."
    
    rm -rf "${INSTALL_DIR}"
    mkdir -p "${INSTALL_DIR}"
    mkdir -p "${INSTALL_DIR}/usr/bin"
    mkdir -p "${INSTALL_DIR}/usr/share/applications"
    mkdir -p "${INSTALL_DIR}/usr/share/icons/hicolor/256x256/apps"
    mkdir -p "${INSTALL_DIR}/usr/lib/${APP_NAME}"
    
    # 复制可执行文件
    cp "${PROJECT_DIR}/bin/ConfigWatcher" "${INSTALL_DIR}/usr/bin/"
    
    # 复制 Qt 依赖库（使用 linuxdeployqt 或手动复制）
    if command -v linuxdeployqt &> /dev/null; then
        log_info "使用 linuxdeployqt 收集依赖..."
        linuxdeployqt -executable="${INSTALL_DIR}/usr/bin/ConfigWatcher" \
                      -appimage \
                      -verbose=1 2>/dev/null || true
    else
        log_info "手动收集 Qt 依赖..."
        collect_qt_deps
    fi
    
    # 创建桌面文件
    create_desktop_file
    
    # 创建图标
    create_icon
    
    log_success "目录结构创建完成"
}

# 收集 Qt 依赖
collect_qt_deps() {
    # 获取 Qt 安装路径
    local qt_lib_path=$(qmake -query QT_INSTALL_LIBS)
    local qt_qml_path=$(qmake -query QT_INSTALL_QML)
    local qt_plugins_path=$(qmake -query QT_INSTALL_PLUGINS)
    
    if [ -z "${qt_lib_path}" ]; then
        log_warning "无法获取 Qt 库路径，尝试使用系统路径"
        qt_lib_path="/usr/lib/x86_64-linux-gnu"
    fi
    
    # 复制必要的 Qt 库
    local libs=(
        "libQt5Core.so.5"
        "libQt5Gui.so.5"
        "libQt5Quick.so.5"
        "libQt5Qml.so.5"
        "libQt5QuickControls2.so.5"
        "libQt5QuickTemplates2.so.5"
        "libQt5Widgets.so.5"
        "libQt5Sql.so.5"
        "libQt5Concurrent.so.5"
        "libQt5X11Extras.so.5"
    )
    
    mkdir -p "${INSTALL_DIR}/usr/lib/${APP_NAME}/lib"
    
    for lib in "${libs[@]}"; do
        if [ -f "${qt_lib_path}/${lib}" ]; then
            cp "${qt_lib_path}/${lib}" "${INSTALL_DIR}/usr/lib/${APP_NAME}/lib/" 2>/dev/null || \
            cp "/usr/lib/x86_64-linux-gnu/${lib}" "${INSTALL_DIR}/usr/lib/${APP_NAME}/lib/" 2>/dev/null || true
        fi
    done
    
    # 复制插件
    mkdir -p "${INSTALL_DIR}/usr/lib/${APP_NAME}/plugins"
    if [ -d "${qt_plugins_path}" ]; then
        cp -r "${qt_plugins_path}/platforms" "${INSTALL_DIR}/usr/lib/${APP_NAME}/plugins/" 2>/dev/null || true
        cp -r "${qt_plugins_path}/iconengines" "${INSTALL_DIR}/usr/lib/${APP_NAME}/plugins/" 2>/dev/null || true
        cp -r "${qt_plugins_path}/imageformats" "${INSTALL_DIR}/usr/lib/${APP_NAME}/plugins/" 2>/dev/null || true
    fi
    
    # 复制 QML 模块
    mkdir -p "${INSTALL_DIR}/usr/lib/${APP_NAME}/qml"
    if [ -d "${qt_qml_path}" ]; then
        cp -r "${qt_qml_path}/QtQuick" "${INSTALL_DIR}/usr/lib/${APP_NAME}/qml/" 2>/dev/null || true
        cp -r "${qt_qml_path}/QtQuick.2" "${INSTALL_DIR}/usr/lib/${APP_NAME}/qml/" 2>/dev/null || true
        cp -r "${qt_qml_path}/QtQuick/Controls.2" "${INSTALL_DIR}/usr/lib/${APP_NAME}/qml/" 2>/dev/null || true
        cp -r "${qt_qml_path}/QtQuick/Templates.2" "${INSTALL_DIR}/usr/lib/${APP_NAME}/qml/" 2>/dev/null || true
    fi
}

# 创建桌面文件
create_desktop_file() {
    log_info "创建桌面文件..."
    
    cat > "${INSTALL_DIR}/usr/share/applications/configwatcher.desktop" << EOF
[Desktop Entry]
Version=1.0
Type=Application
Name=ConfigWatcher
GenericName=配置文件搜索工具
Comment=快速搜索和管理系统配置文件
Exec=/usr/bin/ConfigWatcher
Icon=configwatcher
Categories=Utility;System;
Keywords=config;configuration;search;ini;json;xml;
Terminal=false
StartupNotify=true
EOF
    
    log_success "桌面文件创建完成"
}

# 创建图标
create_icon() {
    log_info "创建应用图标..."
    
    # 如果有图标文件则复制，否则创建占位符
    if [ -f "${PROJECT_DIR}/res/images/app.ico" ]; then
        # 转换 ICO 为 PNG（需要 imagemagick）
        if command -v convert &> /dev/null; then
            convert "${PROJECT_DIR}/res/images/app.ico" \
                    -resize 256x256 \
                    "${INSTALL_DIR}/usr/share/icons/hicolor/256x256/apps/configwatcher.png"
        else
            log_warning "未找到 imagemagick，创建占位符图标"
            create_placeholder_icon
        fi
    else
        log_warning "未找到图标文件，创建占位符图标"
        create_placeholder_icon
    fi
    
    log_success "图标创建完成"
}

# 创建占位符图标
create_placeholder_icon() {
    # 创建一个简单的蓝色正方形作为占位符
    if command -v convert &> /dev/null; then
        convert -size 256x256 xc:'#2563EB' \
                -fill white -gravity center -pointsize 40 \
                -annotate 0 "CW" \
                "${INSTALL_DIR}/usr/share/icons/hicolor/256x256/apps/configwatcher.png"
    else
        # 如果没有 imagemagick，创建一个简单的 SVG
        cat > "${INSTALL_DIR}/usr/share/icons/hicolor/256x256/apps/configwatcher.svg" << 'EOF'
<svg xmlns="http://www.w3.org/2000/svg" width="256" height="256">
  <rect width="256" height="256" fill="#2563EB" rx="40"/>
  <text x="128" y="160" font-size="80" fill="white" text-anchor="middle" font-family="Arial">CW</text>
</svg>
EOF
    fi
}

# 打包为 DEB
package_deb() {
    log_info "打包 DEB 安装包..."
    
    local deb_dir="${BUILD_DIR}/deb"
    local package_name="${APP_NAME,,}_${APP_VERSION}_amd64"
    
    rm -rf "${deb_dir}"
    mkdir -p "${deb_dir}/${package_name}/DEBIAN"
    
    # 复制安装文件
    cp -r "${INSTALL_DIR}/"* "${deb_dir}/${package_name}/"
    
    # 创建控制文件
    cat > "${deb_dir}/${package_name}/DEBIAN/control" << EOF
Package: ${APP_NAME,,}
Version: ${APP_VERSION}
Section: utils
Priority: optional
Architecture: amd64
Depends: qt5-default, qtquickcontrols2-5-dev, libx11-6, libxcb1
Maintainer: ${APP_AUTHOR}
Description: 配置文件搜索工具
 ConfigWatcher 是一个基于 Qt 开发的跨平台配置文件搜索工具，
 支持快速检索 .ini、.json、.xml 等格式的配置文件。
EOF
    
    # 创建安装后脚本
    cat > "${deb_dir}/${package_name}/DEBIAN/postinst" << 'EOF'
#!/bin/bash
update-desktop-database
update-mime-database
echo "ConfigWatcher 安装完成！"
EOF
    chmod 755 "${deb_dir}/${package_name}/DEBIAN/postinst"
    
    # 创建卸载脚本
    cat > "${deb_dir}/${package_name}/DEBIAN/postrm" << 'EOF'
#!/bin/bash
update-desktop-database
update-mime-database
echo "ConfigWatcher 已卸载"
EOF
    chmod 755 "${deb_dir}/${package_name}/DEBIAN/postrm"
    
    # 打包
    cd "${deb_dir}"
    dpkg-deb --build "${package_name}"
    
    # 移动到输出目录
    mkdir -p "${PROJECT_DIR}/packages"
    mv "${package_name}.deb" "${PROJECT_DIR}/packages/"
    
    log_success "DEB 包创建完成：${PROJECT_DIR}/packages/${package_name}.deb"
}

# 打包为 AppImage
package_appimage() {
    log_info "打包 AppImage..."
    
    rm -rf "${APPIMAGE_DIR}"
    mkdir -p "${APPIMAGE_DIR}"
    
    # 复制可执行文件和依赖
    cp "${INSTALL_DIR}/usr/bin/ConfigWatcher" "${APPIMAGE_DIR}/"
    cp -r "${INSTALL_DIR}/usr/lib/${APP_NAME}"/* "${APPIMAGE_DIR}/" 2>/dev/null || true
    
    # 创建 AppRun
    cat > "${APPIMAGE_DIR}/AppRun" << 'EOF'
#!/bin/bash
SELF=$(readlink -f "$0")
HERE=${SELF%/*}
export LD_LIBRARY_PATH="${HERE}:${HERE}/lib:${LD_LIBRARY_PATH}"
export QT_QPA_PLATFORM_PLUGIN_PATH="${HERE}/plugins/platforms"
export QML2_IMPORT_PATH="${HERE}/qml"
exec "${HERE}/ConfigWatcher" "$@"
EOF
    chmod +x "${APPIMAGE_DIR}/AppRun"
    
    # 复制图标
    if [ -f "${INSTALL_DIR}/usr/share/icons/hicolor/256x256/apps/configwatcher.png" ]; then
        cp "${INSTALL_DIR}/usr/share/icons/hicolor/256x256/apps/configwatcher.png" "${APPIMAGE_DIR}/configwatcher.png"
    fi
    
    # 创建桌面文件
    cp "${INSTALL_DIR}/usr/share/applications/configwatcher.desktop" "${APPIMAGE_DIR}/configwatcher.desktop"
    
    # 使用 appimagetool 打包
    if command -v appimagetool &> /dev/null; then
        cd "${BUILD_DIR}"
        appimagetool "${APPIMAGE_DIR}" "${PROJECT_DIR}/packages/${APP_NAME}-${APP_VERSION}.AppImage"
        log_success "AppImage 创建完成：${PROJECT_DIR}/packages/${APP_NAME}-${APP_VERSION}.AppImage"
    else
        log_warning "未找到 appimagetool，创建目录包"
        mkdir -p "${PROJECT_DIR}/packages"
        tar -czf "${PROJECT_DIR}/packages/${APP_NAME}-${APP_VERSION}-linux-x64.tar.gz" \
            -C "${BUILD_DIR}" AppImage
        log_success "压缩包创建完成：${PROJECT_DIR}/packages/${APP_NAME}-${APP_VERSION}-linux-x64.tar.gz"
    fi
}

# 创建 RPM 包
package_rpm() {
    log_info "打包 RPM..."
    
    # 检查 rpmbuild
    if ! command -v rpmbuild &> /dev/null; then
        log_warning "未找到 rpmbuild，跳过 RPM 打包"
        return
    fi
    
    local rpm_dir="${BUILD_DIR}/rpm"
    mkdir -p "${rpm_dir}"
    
    # 创建 spec 文件
    cat > "${rpm_dir}/${APP_NAME,,}.spec" << EOF
Name:           ${APP_NAME,,}
Version:        ${APP_VERSION}
Release:        1%{?dist}
Summary:        配置文件搜索工具
License:        Proprietary
URL:            https://github.com/ConfigWatcher
BuildArch:      x86_64

Requires:       qt5-qtbase qt5-qtquickcontrols2 libX11 libxcb

%description
ConfigWatcher 是一个基于 Qt 开发的跨平台配置文件搜索工具，
支持快速检索 .ini、.json、.xml 等格式的配置文件。

%install
mkdir -p %{buildroot}/usr/bin
mkdir -p %{buildroot}/usr/share/applications
mkdir -p %{buildroot}/usr/share/icons/hicolor/256x256/apps

cp %{_sourcedir}/ConfigWatcher %{buildroot}/usr/bin/
cp %{_sourcedir}/configwatcher.desktop %{buildroot}/usr/share/applications/
cp %{_sourcedir}/configwatcher.png %{buildroot}/usr/share/icons/hicolor/256x256/apps/

%files
/usr/bin/ConfigWatcher
/usr/share/applications/configwatcher.desktop
/usr/share/icons/hicolor/256x256/apps/configwatcher.png

%post
update-desktop-database || :

%postun
update-desktop-database || :
EOF
    
    # 准备源文件
    mkdir -p ~/rpmbuild/SOURCES
    cp "${INSTALL_DIR}/usr/bin/ConfigWatcher" ~/rpmbuild/SOURCES/
    cp "${INSTALL_DIR}/usr/share/applications/configwatcher.desktop" ~/rpmbuild/SOURCES/
    cp "${INSTALL_DIR}/usr/share/icons/hicolor/256x256/apps/configwatcher.png" ~/rpmbuild/SOURCES/ 2>/dev/null || true
    cp "${rpm_dir}/${APP_NAME,,}.spec" ~/rpmbuild/SPECS/
    
    # 构建 RPM
    rpmbuild -bb ~/rpmbuild/SPECS/${APP_NAME,,}.spec
    
    # 移动结果
    mkdir -p "${PROJECT_DIR}/packages"
    find ~/rpmbuild/RPMS -name "*.rpm" -exec cp {} "${PROJECT_DIR}/packages/" \;
    
    log_success "RPM 包创建完成"
}

# 显示使用帮助
show_help() {
    cat << EOF
使用方法：$0 [选项]

选项:
  -h, --help      显示此帮助信息
  -b, --build     仅编译，不打包
  -d, --deb       打包为 DEB 格式（默认）
  -a, --appimage  打包为 AppImage 格式
  -r, --rpm       打包为 RPM 格式
  -all, --all     打包所有格式
  -c, --clean     清理构建目录

示例:
  $0                    # 编译并打包为 DEB
  $0 --all              # 编译并打包所有格式
  $0 --clean            # 清理构建目录

输出目录：${PROJECT_DIR}/packages/
EOF
}

# 主函数
main() {
    local action="deb"
    local do_clean=false
    
    # 解析参数
    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_help
                exit 0
                ;;
            -b|--build)
                action="build"
                shift
                ;;
            -d|--deb)
                action="deb"
                shift
                ;;
            -a|--appimage)
                action="appimage"
                shift
                ;;
            -r|--rpm)
                action="rpm"
                shift
                ;;
            -all|--all)
                action="all"
                shift
                ;;
            -c|--clean)
                do_clean=true
                shift
                ;;
            *)
                log_error "未知选项：$1"
                show_help
                exit 1
                ;;
        esac
    done
    
    # 清理
    if [ "${do_clean}" = true ]; then
        cleanup
        log_success "清理完成"
        exit 0
    fi
    
    echo "========================================"
    echo "  ${APP_NAME} v${APP_VERSION} 打包脚本"
    echo "  作者：${APP_AUTHOR}"
    echo "========================================"
    echo
    
    # 创建输出目录
    mkdir -p "${PROJECT_DIR}/packages"
    
    # 检查依赖
    check_dependencies
    
    # 编译
    build_project
    
    # 创建包结构
    create_package_structure
    
    # 根据选项打包
    case ${action} in
        build)
            log_success "编译完成，输出目录：${PROJECT_DIR}/bin/"
            ;;
        deb)
            package_deb
            ;;
        appimage)
            package_appimage
            ;;
        rpm)
            package_rpm
            ;;
        all)
            package_deb
            package_appimage
            package_rpm
            ;;
    esac
    
    echo
    echo "========================================"
    log_success "打包完成！"
    echo "========================================"
    echo
    echo "安装包位置：${PROJECT_DIR}/packages/"
    ls -lh "${PROJECT_DIR}/packages/" 2>/dev/null || true
    echo
    echo "安装方法:"
    echo "  DEB:    sudo dpkg -i ${APP_NAME,,}_${APP_VERSION}_amd64.deb"
    echo "  RPM:    sudo rpm -ivh ${APP_NAME,,}-${APP_VERSION}*.rpm"
    echo "  AppImage: chmod +x ${APP_NAME}-*.AppImage && ./${APP_NAME}-*.AppImage"
    echo
}

# 运行主函数
main "$@"
