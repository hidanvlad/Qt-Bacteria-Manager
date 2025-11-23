#ifndef BACTERIUMTABLEMODEL_H
#define BACTERIUMTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "Bacterium.h"

class BacteriumTableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Bacterium> bacteria;
    const QStringList headers = {"Name", "Species", "Size", "Diseases"};

public:
    explicit BacteriumTableModel(QObject* parent = nullptr);
    void setBacteria(const std::vector<Bacterium>& newBacteria);
    const std::vector<Bacterium>& getBacteria() const { return bacteria; }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
};

#endif