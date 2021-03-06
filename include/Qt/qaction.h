/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QACTION_H
#define QACTION_H

#include <QtGui/qkeysequence.h>
#include <QtCore/qstring.h>
#include <QtGui/qwidget.h>
#include <QtCore/qvariant.h>
#include <QtGui/qicon.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

#ifndef QT_NO_ACTION

class QMenu;
class QActionGroup;
class QActionPrivate;

class Q_GUI_EXPORT QAction : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QAction)

    Q_ENUMS(MenuRole)
    Q_PROPERTY(bool checkable READ isCheckable WRITE setCheckable)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked DESIGNABLE isCheckable NOTIFY toggled)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString iconText READ iconText WRITE setIconText)
    Q_PROPERTY(QString toolTip READ toolTip WRITE setToolTip)
    Q_PROPERTY(QString statusTip READ statusTip WRITE setStatusTip)
    Q_PROPERTY(QString whatsThis READ whatsThis WRITE setWhatsThis)
    Q_PROPERTY(QFont font READ font WRITE setFont)
#ifndef QT_NO_SHORTCUT
    Q_PROPERTY(QKeySequence shortcut READ shortcut WRITE setShortcut)
    Q_PROPERTY(Qt::ShortcutContext shortcutContext READ shortcutContext WRITE setShortcutContext)
    Q_PROPERTY(bool autoRepeat READ autoRepeat WRITE setAutoRepeat)
#endif
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)
    Q_PROPERTY(MenuRole menuRole READ menuRole WRITE setMenuRole)
    Q_PROPERTY(bool iconVisibleInMenu READ isIconVisibleInMenu WRITE setIconVisibleInMenu)

public:
    enum MenuRole { NoRole, TextHeuristicRole, ApplicationSpecificRole, AboutQtRole,
                    AboutRole, PreferencesRole, QuitRole };
    explicit QAction(QObject* parent);
    QAction(const QString &text, QObject* parent);
    QAction(const QIcon &icon, const QString &text, QObject* parent);

#ifdef QT3_SUPPORT
    QT3_SUPPORT_CONSTRUCTOR QAction(QObject* parent, const char* name);
    QT3_SUPPORT_CONSTRUCTOR QAction(const QString &text, const QKeySequence &shortcut,
                                    QObject* parent, const char* name);
    QT3_SUPPORT_CONSTRUCTOR QAction(const QIcon &icon, const QString &text,
                                    const QKeySequence &shortcut,
                                    QObject* parent, const char* name);
#endif
    ~QAction();

    void setActionGroup(QActionGroup *group);
    QActionGroup *actionGroup() const;
    void setIcon(const QIcon &icon);
    QIcon icon() const;

    void setText(const QString &text);
    QString text() const;

    void setIconText(const QString &text);
    QString iconText() const;

    void setToolTip(const QString &tip);
    QString toolTip() const;

    void setStatusTip(const QString &statusTip);
    QString statusTip() const;

    void setWhatsThis(const QString &what);
    QString whatsThis() const;

#ifndef QT_NO_MENU
    QMenu *menu() const;
    void setMenu(QMenu *menu);
#endif

    void setSeparator(bool b);
    bool isSeparator() const;

#ifndef QT_NO_SHORTCUT
    void setShortcut(const QKeySequence &shortcut);
    QKeySequence shortcut() const;

    void setShortcuts(const QList<QKeySequence> &shortcuts);
    void setShortcuts(QKeySequence::StandardKey);
    QList<QKeySequence> shortcuts() const;

    void setShortcutContext(Qt::ShortcutContext context);
    Qt::ShortcutContext shortcutContext() const;

    void setAutoRepeat(bool);
    bool autoRepeat() const;
#endif

    void setFont(const QFont &font);
    QFont font() const;

    void setCheckable(bool);
    bool isCheckable() const;

    QVariant data() const;
    void setData(const QVariant &var);

    bool isChecked() const;

    bool isEnabled() const;

    bool isVisible() const;

    enum ActionEvent { Trigger, Hover };
    void activate(ActionEvent event);
    bool showStatusText(QWidget *widget=0);

    void setMenuRole(MenuRole menuRole);
    MenuRole menuRole() const;

    void setIconVisibleInMenu(bool visible);
    bool isIconVisibleInMenu() const;

#ifdef QT3_SUPPORT
    inline QT3_SUPPORT void setMenuText(const QString &text) { setText(text); }
    inline QT3_SUPPORT QString menuText() const { return text(); }
    inline QT3_SUPPORT bool isOn() const { return isChecked(); }
    inline QT3_SUPPORT bool isToggleAction() const { return isCheckable(); }
    inline QT3_SUPPORT void setToggleAction(bool b) { setCheckable(b); }
    inline QT3_SUPPORT void setIconSet(const QIcon &i) { setIcon(i); }
    inline QT3_SUPPORT QIcon iconSet() const { return icon(); }
    inline QT3_SUPPORT bool addTo(QWidget *w) { w->addAction(this); return true; }
    inline QT3_SUPPORT bool removeFrom(QWidget *w) { w->removeAction(this); return true; }
    inline QT3_SUPPORT void setAccel(const QKeySequence &shortcut) { setShortcut(shortcut); }
    inline QT3_SUPPORT QKeySequence accel() const { return shortcut(); }
#endif

    QWidget *parentWidget() const;

    QList<QWidget *> associatedWidgets() const;

protected:
    bool event(QEvent *);
    QAction(QActionPrivate &dd, QObject *parent);

public Q_SLOTS:
#ifdef QT3_SUPPORT
    inline QT_MOC_COMPAT void setOn(bool b) { setChecked(b); }
#endif
    void trigger() { activate(Trigger); }
    void hover() { activate(Hover); }
    void setChecked(bool);
    void toggle();
    void setEnabled(bool);
    inline void setDisabled(bool b) { setEnabled(!b); }
    void setVisible(bool);

Q_SIGNALS:
    void changed();
    void triggered(bool checked = false);
    void hovered();
    void toggled(bool);
#ifdef QT3_SUPPORT
    QT_MOC_COMPAT void activated(int = 0);
#endif

private:
    Q_DISABLE_COPY(QAction)

#ifdef QT3_SUPPORT
    friend class QMenuItem;
#endif
    friend class QWidget;
    friend class QActionGroup;
    friend class QMenu;
    friend class QMenuPrivate;
    friend class QMenuBar;
    friend class QShortcutMap;
    friend class QToolButton;
};

QT_BEGIN_INCLUDE_NAMESPACE
#include <QtGui/qactiongroup.h>
QT_END_INCLUDE_NAMESPACE

#endif // QT_NO_ACTION

QT_END_NAMESPACE

QT_END_HEADER

#endif // QACTION_H
