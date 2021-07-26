//
// Created by tereb on 26.07.2021.
//

#include "SudokuBoardDelegate.h"

SudokuBoardDelegate::SudokuBoardDelegate(SudokuBoardService &tService) : mService(tService)
{}

void SudokuBoardDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    painter->setRenderHint(QPainter::Antialiasing);

    int row = index.row();
    int column = index.column();
    if(column != 0 && (column) % 3 == 0)
    {
        painter->save();
        auto pen = QPen(QColor("black"), 2);
        auto qr = QRect(option.rect);
        int newPos = option.rect.left();
        qr.setWidth(pen.width());
        qr.moveLeft(newPos - 1);
        painter->setPen(pen);
        painter->drawRect(qr);
        painter->restore();
    }
    if(row != 0 && (row) % 3 == 0)
    {
        painter->save();
        auto pen = QPen(QColor("black"), 2);
        auto qr = QRect(option.rect);
        int newPos = option.rect.top();
        qr.setHeight(pen.width());
        qr.moveBottom(newPos - 1);
        painter->setPen(pen);
        painter->drawRect(qr);
        painter->restore();
    }

    if(mService.checkOccupiedCell(row, column) && mService.getCurrentBoard().cellContainsValue(row, column))
    {
        // todo: see how to put the text over the circle
        painter->save();
        painter->setBrush(QBrush{QColor{19, 174, 75}});
        painter->setPen(QPen{QColor{19, 174, 75}});
        painter->drawEllipse(option.rect);

        auto cellText = index.data(Qt::DisplayRole);
        painter->setFont(QFont("Bahnschrift Light SemiCondensed", 13));
        painter->setPen(QPen{QColor{0, 0, 0}});
        painter->drawText(option.rect, Qt::AlignCenter, cellText.toString());

        painter->restore();
    }
}
