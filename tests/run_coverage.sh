#!/bin/bash
# ConfigWatcher 测试覆盖率统计脚本（简化版）

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
TEST_DIR="$SCRIPT_DIR"
BUILD_DIR="$PROJECT_DIR/build_tests"
COVERAGE_DIR="$PROJECT_DIR/coverage"

echo "=== ConfigWatcher 测试覆盖率统计 ==="
echo "项目目录：$PROJECT_DIR"
echo "测试目录：$TEST_DIR"

# 创建目录
mkdir -p "$BUILD_DIR"
mkdir -p "$COVERAGE_DIR"

# 进入测试目录
cd "$TEST_DIR"

# 清理之前的构建
rm -rf ../obj/tests ../moc/tests Makefile

# 使用覆盖率配置编译
echo "配置测试项目（带覆盖率）..."
qmake tests_simple.pro CONFIG+=gcov

# 编译
echo "编译测试项目..."
make clean
make -j$(nproc)

# 运行测试
echo ""
echo "运行测试..."
../bin/tests/ConfigWatcherTests

# 生成覆盖率报告
echo ""
echo "生成覆盖率报告..."

# 合并覆盖率数据
lcov --capture \
    --directory "$PROJECT_DIR/obj" \
    --directory "$PROJECT_DIR/src" \
    --output-file "$COVERAGE_DIR/coverage.info" \
    --ignore-errors mismatch 2>/dev/null || true

# 过滤系统文件
lcov --remove "$COVERAGE_DIR/coverage.info" \
    '/usr/*' \
    '*/moc/*' \
    '*/ui_*' \
    '*/test_*' \
    '*/.moc/*' \
    --output-file "$COVERAGE_DIR/coverage_filtered.info" \
    --ignore-errors unused 2>/dev/null || true

# 生成 HTML 报告
genhtml "$COVERAGE_DIR/coverage_filtered.info" \
    --output-directory "$COVERAGE_DIR/html" \
    --title "ConfigWatcher 测试覆盖率报告" \
    --show-details 2>/dev/null || true

# 生成文本摘要
echo ""
echo "=== 覆盖率摘要 ==="
lcov --list "$COVERAGE_DIR/coverage_filtered.info" 2>/dev/null || echo "无法生成覆盖率报告"

echo ""
echo "HTML 报告已生成：$COVERAGE_DIR/html/index.html"
echo "=== 完成 ==="
