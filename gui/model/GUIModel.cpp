//
// Created by tereb on 16.07.2021.
//

#include "GUIModel.h"
#include <QFont>
#include <QBrush>

GUIModel::GUIModel(SudokuBoardService &service, QObject *parent) : mService(service), QAbstractTableModel(parent)
{}

int GUIModel::rowCount(const QModelIndex &parent) const
{
    return this->mService.getCurrentBoard().getSize();
}

int GUIModel::columnCount(const QModelIndex &parent) const
{
    return this->mService.getCurrentBoard().getSize();
}

QVariant GUIModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();

    int value = this->mService.getCurrentBoard().getCellValue(row, column);

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(value > 0)
            return QString::number(value);
        return QVariant();
    }
    if (role == Qt::FontRole)
    {
        QFont font("Bahnschrift Light SemiCondensed", 12);
        return font;
    }
    if (role == Qt::BackgroundRole)
    {
        if (value < 0)
        {
            return QBrush{ QColor{220, 220, 220}};
        }
    }

    return QVariant();
}

Qt::ItemFlags GUIModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
