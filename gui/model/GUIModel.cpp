//
// Created by tereb on 16.07.2021.
//

#include "GUIModel.h"
#include <QFont>
#include <QBrush>

GUIModel::GUIModel(SudokuBoardService &service, QObject *parent) : QAbstractTableModel(parent), mService(service)
{}

int GUIModel::rowCount(const QModelIndex &parent) const
{
    return this->mService.getCurrentBoard().getSize();
}

int GUIModel::columnCount(const QModelIndex &parent) const
{
    return this->mService.getCurrentBoard().getSize();
}

// todo: check why multiple cells are marked as clashing when they are not

QVariant GUIModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();

    int value = this->mService.getCurrentBoard().getCellValue(row, column);

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(this->mService.getCurrentBoard().cellContainsValue(row, column))
            return QString::number(value);
        return QVariant();
    }
    if (role == Qt::FontRole)
    {
        QFont font("Bahnschrift Light SemiCondensed", 17);
        return font;
    }
    if (role == Qt::BackgroundRole)
    {
        if(value == BombedCell)
            return QBrush{ QColor{100, 100, 100}};
        return QBrush{ QColor{11, 170, 61, 100} };
    }
    if (role == Qt::ForegroundRole)
    {
        if(mService.checkClashingCell(row, column))
        {
            return QBrush{ QColor{170, 11, 40} };
        }
        else
        {
            return QBrush{ QColor{0, 0, 0} };
        }
    }
    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    return QVariant();
}

bool GUIModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int column = index.column();
    int userValue = value.toInt();
    if(value.toString().isEmpty())
        userValue = UnassignedCell;

    if(role == Qt::EditRole)
    {
        auto response = this->mService.setBoardCell(row, column, userValue);
        if(response == InvalidCell)
            return false;
        emit dataChanged(index, index, {role});
        if(mService.checkWinner())
            emit gameWon(1);
        return true;
    }

    return QAbstractItemModel::setData(index, value, role);
}

Qt::ItemFlags GUIModel::flags(const QModelIndex &index) const
{
    int row = index.row();
    int column = index.column();

    if(mService.checkOccupiedCell(row, column))
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    else
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}


