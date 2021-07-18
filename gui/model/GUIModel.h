//
// Created by tereb on 16.07.2021.
//

#ifndef SUDOKU_MADNESS_GUIMODEL_H
#define SUDOKU_MADNESS_GUIMODEL_H


#include <QAbstractTableModel>
#include "../../service/game_service/sudoku_service/SudokuBoardService.h"

class GUIModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    SudokuBoardService & mService;
public:
    explicit GUIModel(SudokuBoardService & service, QObject * parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif //SUDOKU_MADNESS_GUIMODEL_H
