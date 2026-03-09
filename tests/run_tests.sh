#!/bin/bash
# ConfigWatcher 测试运行脚本

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
TEST_DIR="$SCRIPT_DIR"

echo "=== ConfigWatcher 单元测试 ==="
echo ""

# 进入测试目录
cd "$TEST_DIR"

# 清理之前的构建
if [ -d "../obj/tests" ]; then
    echo "清理之前的构建..."
    rm -rf ../obj/tests
fi

if [ -d "../moc/tests" ]; then
    rm -rf ../moc/tests
fi

if [ -d "../rcc/tests" ]; then
    rm -rf ../rcc/tests
fi

# 配置
echo "配置测试项目..."
qmake tests.pro

# 编译
echo "编译测试项目..."
make -j$(nproc)

# 运行测试
echo ""
echo "运行测试..."
echo ""

if [ -f "../bin/tests/ConfigWatcherTests" ]; then
    ../bin/tests/ConfigWatcherTests -v
    EXIT_CODE=$?
else
    echo "错误：测试可执行文件未找到"
    exit 1
fi

echo ""
echo "=== 测试完成 ==="

if [ $EXIT_CODE -eq 0 ]; then
    echo "✓ 所有测试通过!"
else
    echo "✗ 测试失败，退出码：$EXIT_CODE"
fi

exit $EXIT_CODE
