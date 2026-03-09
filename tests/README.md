# ConfigWatcher 单元测试

本项目使用 Qt Test 框架进行单元测试，已达到 100% 测试通过率。

## 测试统计

| 模块 | 测试用例数 | 通过率 |
|------|-----------|--------|
| ConfigEntry | 13 | 100% |
| ConfigParser | 10 | 100% |
| DatabaseManager | 12 | 100% |
| AIService | 14 | 100% |
| FileWatcher | 10 | 100% |
| ConfigDiff | 12 | 100% |
| BatchOperation | 10 | 100% |
| ConfigValidator | 12 | 100% |
| AIClient | 19 | 100% |
| **总计** | **112** | **100%** |

## 快速开始

### 编译和运行测试

```bash
cd tests
qmake tests_simple.pro
make
../bin/tests/ConfigWatcherTests
```

### 运行覆盖率统计

```bash
# 安装依赖
sudo apt-get install lcov gcov

# 运行覆盖率脚本
./run_coverage.sh
```

覆盖率报告将生成在 `coverage/html/index.html`。

## 测试覆盖的功能

### 1. ConfigEntry (配置条目)
- 构造函数测试
- 属性 getter/setter 测试
- 重置功能测试
- 信号触发测试
- 对象池功能测试

### 2. ConfigParser (配置解析器)
- INI 文件解析测试
- JSON 文件解析测试
- 注释处理测试
- 搜索功能测试
- 大小写不敏感搜索测试

### 3. DatabaseManager (数据库管理)
- 数据库连接测试
- INI/JSON 文件导入测试
- 搜索功能测试
- 翻译功能测试
- 修改记录测试

### 4. AIService (AI 服务)
- 意图识别测试
- 关键词扩展测试
- 同义词查询测试
- 用户词典测试
- 搜索历史测试

### 5. FileWatcher (文件监控)
- 文件监控添加/移除测试
- 目录监控测试
- 文件格式过滤测试
- 暂停/恢复监控测试

### 6. ConfigDiff (配置对比)
- 文件对比测试
- 快照管理测试
- 报告生成测试

### 7. BatchOperation (批量操作)
- 批量更新测试
- 批量导入导出测试
- CSV 导出测试

### 8. ConfigValidator (配置验证)
- 规则管理测试
- 配置验证测试
- 报告生成测试

### 9. AIClient (AI 客户端)
- 属性配置测试
- Provider 切换测试
- 设置保存加载测试

## 测试最佳实践

1. **独立性**：每个测试使用临时目录，互不干扰
2. **可重复性**：测试使用临时文件，每次运行环境相同
3. **原子性**：每个测试只验证一个功能点
4. **命名规范**：使用 `test_FunctionName_Condition` 格式

## 添加新测试

在 `main.cpp` 中添加新的测试类：

```cpp
class TestMyClass : public TestBase
{
    Q_OBJECT
private slots:
    void test_MyFunction()
    {
        // Arrange
        MyClass obj;
        
        // Act
        bool result = obj.doSomething();
        
        // Assert
        QVERIFY(result);
    }
};
```

然后在 `main()` 函数中注册：

```cpp
status += QTest::qExec(new TestMyClass(), argc, argv);
```

## 持续集成

在 CI/CD 流程中运行测试：

```yaml
test:
  script:
    - cd tests
    - qmake tests_simple.pro
    - make
    - ../bin/tests/ConfigWatcherTests
```

## 测试报告示例

```
=== ConfigWatcher 单元测试套件 ===
开始运行测试...

--- ConfigEntry 测试 ---
Totals: 13 passed, 0 failed, 0 skipped, 0 blacklisted, 1ms

--- ConfigParser 测试 ---
Totals: 10 passed, 0 failed, 0 skipped, 0 blacklisted, 4ms

...

=== 测试完成 ===
✓ 所有测试通过!
```

## 依赖

- Qt 5.15 或更高版本
- Qt Test 框架
- lcov（覆盖率统计，可选）
- gcov（代码覆盖率，可选）

## 故障排除

### 测试失败

1. 检查临时文件权限
2. 验证数据库连接
3. 查看测试输出日志

### 覆盖率偏低

1. 检查是否有未测试的代码路径
2. 添加边界条件测试
3. 增加异常处理测试

## 联系方式

如有问题或建议，请提交 Issue。
