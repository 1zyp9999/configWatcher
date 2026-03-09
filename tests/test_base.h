#ifndef TEST_BASE_H
#define TEST_BASE_H

#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTemporaryDir>
#include <QDateTime>

/**
 * @brief 测试基类 - 提供通用的测试辅助功能
 */
class TestBase : public QObject
{
    Q_OBJECT

protected:
    QTemporaryDir m_tempDir;
    
    /**
     * @brief 创建临时测试文件
     */
    QString createTempFile(const QString& content, const QString& suffix = ".ini")
    {
        if (!m_tempDir.isValid()) {
            return QString();
        }
        
        QString fileName = QString("test_%1%2")
            .arg(QDateTime::currentMSecsSinceEpoch())
            .arg(suffix);
        QString filePath = m_tempDir.filePath(fileName);
        
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out.setCodec("UTF-8");
            out << content;
            file.close();
            return filePath;
        }
        
        return QString();
    }
    
    /**
     * @brief 创建临时目录
     */
    bool createTempDirectory(const QString& dirName)
    {
        if (!m_tempDir.isValid()) {
            return false;
        }
        QDir dir(m_tempDir.path());
        return dir.mkdir(dirName);
    }
    
    /**
     * @brief 验证文件内容
     */
    bool verifyFileContent(const QString& filePath, const QString& expectedContent)
    {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return false;
        }
        
        QTextStream in(&file);
        in.setCodec("UTF-8");
        QString actualContent = in.readAll();
        file.close();
        
        return actualContent.trimmed() == expectedContent.trimmed();
    }
    
    /**
     * @brief 等待信号触发
     */
    bool waitForSignal(QObject* sender, const char* signal, int timeout = 5000)
    {
        QSignalSpy spy(sender, signal);
        return spy.wait(timeout);
    }
    
    /**
     * @brief 比较两个 QVariantList 是否相等
     */
    bool compareVariantLists(const QVariantList& list1, const QVariantList& list2)
    {
        if (list1.size() != list2.size()) {
            return false;
        }
        
        for (int i = 0; i < list1.size(); ++i) {
            if (list1[i].toMap() != list2[i].toMap()) {
                return false;
            }
        }
        
        return true;
    }
};

#endif // TEST_BASE_H
