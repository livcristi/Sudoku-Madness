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
        QFont font("Bahnschrift Light SemiCondensed", 13);
        return font;
    }
    if (role == Qt::BackgroundRole)
    {
        if(value == BombedCell)
            return QBrush{ QColor{100, 100, 100}};
        if(mService.checkClashingCell(row, column))
            return QBrush{QColor{232, 53, 53}};
        if(mService.checkOccupiedCell(row, column))
            return QBrush{ QColor{255, 255, 255}};
        if(value != OccupiedCell)
            return QBrush{ QColor{230, 230, 230}};
        else
            return QBrush{ QColor{240, 240, 240}};
    }
    if (role == Qt::ForegroundRole)
    {
        if(mService.checkOccupiedCell(row, column))
        {
            return QBrush{ QColor{52, 22, 97}};
        }
        else
        {
            return QBrush{QColor{78, 145, 207}};
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


