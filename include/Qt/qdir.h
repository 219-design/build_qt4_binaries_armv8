/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#ifndef QDIR_H
#define QDIR_H

#include <QtCore/qstring.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qstringlist.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Core)

class QDirPrivate;

class Q_CORE_EXPORT QDir
{
protected:
    QDirPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(QDir)
public:
    enum Filter { Dirs        = 0x001,
                  Files       = 0x002,
                  Drives      = 0x004,
                  NoSymLinks  = 0x008,
                  AllEntries  = Dirs | Files | Drives,
                  TypeMask    = 0x00f,
#ifdef QT3_SUPPORT
                  All         = AllEntries,
#endif

                  Readable    = 0x010,
                  Writable    = 0x020,
                  Executable  = 0x040,
                  PermissionMask    = 0x070,
#ifdef QT3_SUPPORT
                  RWEMask     = 0x070,
#endif

                  Modified    = 0x080,
                  Hidden      = 0x100,
                  System      = 0x200,
                 
                  AccessMask  = 0x3F0,

                  AllDirs       = 0x400,
                  CaseSensitive = 0x800,
                  NoDotAndDotDot = 0x1000,

                  NoFilter = -1
#ifdef QT3_SUPPORT
                  ,DefaultFilter = NoFilter
#endif
    };
    Q_DECLARE_FLAGS(Filters, Filter)
#ifdef QT3_SUPPORT
    typedef Filters FilterSpec;
#endif

    enum SortFlag { Name        = 0x00,
                    Time        = 0x01,
                    Size        = 0x02,
                    Unsorted    = 0x03,
                    SortByMask  = 0x03,

                    DirsFirst   = 0x04,
                    Reversed    = 0x08,
                    IgnoreCase  = 0x10,
                    DirsLast    = 0x20,
                    LocaleAware = 0x40, 
                    Type        = 0x80,
                    NoSort = -1
#ifdef QT3_SUPPORT
                  ,DefaultSort = NoSort
#endif
    };
    Q_DECLARE_FLAGS(SortFlags, SortFlag)

    QDir(const QDir &);
    QDir(const QString &path = QString());
    QDir(const QString &path, const QString &nameFilter,
         SortFlags sort = SortFlags(Name | IgnoreCase), Filters filter = AllEntries);
    ~QDir();

    QDir &operator=(const QDir &);
    QDir &operator=(const QString &path);

    void setPath(const QString &path);
    QString path() const;
    QString absolutePath() const;
    QString canonicalPath() const;

    static void addResourceSearchPath(const QString &path);

    static void setSearchPaths(const QString &prefix, const QStringList &searchPaths);
    static void addSearchPath(const QString &prefix, const QString &path);
    static QStringList searchPaths(const QString &prefix);

    QString dirName() const;
    QString filePath(const QString &fileName) const;
    QString absoluteFilePath(const QString &fileName) const;
    QString relativeFilePath(const QString &fileName) const;

#ifdef QT_DEPRECATED
    QT_DEPRECATED static QString convertSeparators(const QString &pathName);
#endif
    static QString toNativeSeparators(const QString &pathName);
    static QString fromNativeSeparators(const QString &pathName);

    bool cd(const QString &dirName);
    bool cdUp();

    QStringList nameFilters() const;
    void setNameFilters(const QStringList &nameFilters);

    Filters filter() const;
    void setFilter(Filters filter);
    SortFlags sorting() const;
    void setSorting(SortFlags sort);

    uint count() const;
    QString operator[](int) const;

    static QStringList nameFiltersFromString(const QString &nameFilter);

    QStringList entryList(Filters filters = NoFilter, SortFlags sort = NoSort) const;
    QStringList entryList(const QStringList &nameFilters, Filters filters = NoFilter,
                          SortFlags sort = NoSort) const;

    QFileInfoList entryInfoList(Filters filters = NoFilter, SortFlags sort = NoSort) const;
    QFileInfoList entryInfoList(const QStringList &nameFilters, Filters filters = NoFilter,
                                SortFlags sort = NoSort) const;

    bool mkdir(const QString &dirName) const;
    bool rmdir(const QString &dirName) const;
    bool mkpath(const QString &dirPath) const;
    bool rmpath(const QString &dirPath) const;

    bool isReadable() const;
    bool exists() const;
    bool isRoot() const;

    static bool isRelativePath(const QString &path);
    inline static bool isAbsolutePath(const QString &path) { return !isRelativePath(path); }
    bool isRelative() const;
    inline bool isAbsolute() const { return !isRelative(); }
    bool makeAbsolute();

    bool operator==(const QDir &dir) const;
    inline bool operator!=(const QDir &dir) const {  return !operator==(dir); }

    bool remove(const QString &fileName);
    bool rename(const QString &oldName, const QString &newName);
    bool exists(const QString &name) const;

    static QFileInfoList drives();

    static QChar separator();

    static bool setCurrent(const QString &path);
    static inline QDir current() { return QDir(currentPath()); }
    static QString currentPath();

    static inline QDir home() { return QDir(homePath()); }
    static QString homePath();
    static inline QDir root() { return QDir(rootPath()); }
    static QString rootPath();
    static inline QDir temp() { return QDir(tempPath()); }
    static QString tempPath();

#ifndef QT_NO_REGEXP
    static bool match(const QStringList &filters, const QString &fileName);
    static bool match(const QString &filter, const QString &fileName);
#endif
    static QString cleanPath(const QString &path);
    void refresh() const;

#ifdef QT3_SUPPORT
    typedef SortFlags SortSpec;
    inline QT3_SUPPORT QString absPath() const { return absolutePath(); }
    inline QT3_SUPPORT QString absFilePath(const QString &fileName, bool acceptAbsPath = true) const
       { Q_UNUSED(acceptAbsPath); return absoluteFilePath(fileName); }
    QT3_SUPPORT bool matchAllDirs() const;
    QT3_SUPPORT void setMatchAllDirs(bool on);
    inline QT3_SUPPORT QStringList entryList(const QString &nameFilter, Filters filters = NoFilter,
                                           SortFlags sort = NoSort) const
    { return entryList(nameFiltersFromString(nameFilter), filters, sort); }
    inline QT3_SUPPORT QFileInfoList entryInfoList(const QString &nameFilter,
                                                 Filters filters = NoFilter,
                                                 SortFlags sort = NoSort) const
    { return entryInfoList(nameFiltersFromString(nameFilter), filters, sort); }

    QT3_SUPPORT QString nameFilter() const;
    QT3_SUPPORT void setNameFilter(const QString &nameFilter);

    inline QT3_SUPPORT bool mkdir(const QString &dirName, bool acceptAbsPath) const
        { Q_UNUSED(acceptAbsPath); return mkdir(dirName); }
    inline QT3_SUPPORT bool rmdir(const QString &dirName, bool acceptAbsPath) const
        { Q_UNUSED(acceptAbsPath); return rmdir(dirName); }

    inline QT3_SUPPORT void convertToAbs() { makeAbsolute(); }
    inline QT3_SUPPORT static QString currentDirPath() { return currentPath(); }
    inline QT3_SUPPORT static QString homeDirPath() { return homePath(); }
    inline QT3_SUPPORT static QString rootDirPath() { return rootPath(); }
    inline QT3_SUPPORT static QString cleanDirPath(const QString &name) { return cleanPath(name); }
#endif
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDir::Filters)
Q_DECLARE_OPERATORS_FOR_FLAGS(QDir::SortFlags)

#ifndef QT_NO_DEBUG_STREAM
class QDebug;
Q_CORE_EXPORT QDebug operator<<(QDebug debug, QDir::Filters filters);
Q_CORE_EXPORT QDebug operator<<(QDebug debug, const QDir &dir);
#endif

QT_END_NAMESPACE

QT_END_HEADER

#endif // QDIR_H
