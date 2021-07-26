//
// Created by tereb on 26.07.2021.
//

#ifndef SUDOKU_MADNESS_SUDOKUBOARDDELEGATE_H
#define SUDOKU_MADNESS_SUDOKUBOARDDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include "../../service/game_service/sudoku_service/SudokuBoardService.h"

class SudokuBoardDelegate : public QStyledItemDelegate
{
private:
    SudokuBoardService & mService;
public:
    explicit SudokuBoardDelegate(SudokuBoardService & tService);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif //SUDOKU_MADNESS_SUDOKUBOARDDELEGATE_H
