#include "BacteriumTableModel.h"

BacteriumTableModel::BacteriumTableModel(QObject* parent) : QAbstractTableModel(parent) {}

void BacteriumTableModel::setBacteria(const std::vector<Bacterium>& newBacteria) {
    beginResetModel();
    bacteria = newBacteria;
    endResetModel();
}

int BacteriumTableModel::rowCount(const QModelIndex& parent) const {
    return bacteria.size();
}

int BacteriumTableModel::columnCount(const QModelIndex& parent) const {
    return headers.size();
}


QVariant BacteriumTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= bacteria.size())
        return QVariant();

    const Bacterium& bacterium = bacteria[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 0: return QString::fromStdString(bacterium.getName());
            case 1: return QString::fromStdString(bacterium.getSpecies());
            case 2: return bacterium.getSize();
            case 3: {
                QString diseases;
                for (const auto& disease : bacterium.getDiseases())
                    diseases += QString::fromStdString(disease) + "; ";
                return diseases;
            }
        }
    }
    return QVariant();
}



QVariant BacteriumTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal && section < headers.size())
        return headers[section];
    return QVariant();
}


bool BacteriumTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    Bacterium& bacterium = bacteria[index.row()];
    switch (index.column()) {
        case 0: bacterium.setName(value.toString().toStdString()); break;
        case 1: bacterium.setSpecies(value.toString().toStdString()); break;
        case 2: bacterium.setSize(value.toInt()); break;
        default: return false;
    }
    
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags BacteriumTableModel::flags(const QModelIndex& index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}
