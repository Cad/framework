/***************************************************************************
 *   Copyright 2014 Michael Eischer                                        *
 *   Robotics Erlangen e.V.                                                *
 *   http://www.robotics-erlangen.de/                                      *
 *   info@robotics-erlangen.de                                             *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   any later version.                                                    *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include "debugtreewidget.h"
#include "debugmodel.h"

#include <QSettings>
#include <QHeaderView>

DebugTreeWidget::DebugTreeWidget(QWidget *parent) :
    QTreeView(parent)
{
    m_modelTree = new DebugModel(this);
    setUniformRowHeights(true); // big performance win
    setModel(m_modelTree);
    expandAll();
    connect(this, SIGNAL(expanded(QModelIndex)), SLOT(debugExpanded(QModelIndex)));
    connect(this, SIGNAL(collapsed(QModelIndex)), SLOT(debugCollapsed(QModelIndex)));
    connect(m_modelTree, SIGNAL(expand(QModelIndex)), this, SLOT(expand(QModelIndex)));

    load();
}

DebugTreeWidget::~DebugTreeWidget()
{
    QSettings s;
    s.setValue("Debug/TreeHeader", header()->saveState());
}

void DebugTreeWidget::handleStatus(const Status &status)
{
    if (status->has_debug()) {
        const amun::DebugValues &debug = status->debug();
        m_modelTree->setDebug(debug, m_expanded);
    }
}

void DebugTreeWidget::clearData()
{
    m_modelTree->clearData();
}

void DebugTreeWidget::load()
{
    QSettings s;
    header()->restoreState(s.value("Debug/TreeHeader").toByteArray());
    m_expanded = s.value("Debug/Expanded").toStringList().toSet();
}

void DebugTreeWidget::save()
{
    QSettings s;
    s.setValue("Debug/Expanded", QStringList(QStringList::fromSet(m_expanded)));
}

void DebugTreeWidget::debugExpanded(const QModelIndex &index)
{
    const QString name = index.data(Qt::UserRole + 1).toString();
    if (!m_expanded.contains(name)) {
        m_expanded.insert(name);
        save();
    }
}

void DebugTreeWidget::debugCollapsed(const QModelIndex &index)
{
    const QString name = index.data(Qt::UserRole + 1).toString();
    if (m_expanded.remove(name)) {
        save();
    }
}