#ifndef _QVAULTNODE_H
#define _QVAULTNODE_H

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPlainTextEdit>
#include <Vault/plVaultNode.h>

class QVaultNode : public QWidget {
private:
    Q_OBJECT
    QLabel* fAutoTime;
    QLabel* fModifyTime;
    QLabel* fAgeTime;
    QLineEdit* fAgeName;
    QLineEdit* fAgeGUID;
    QLineEdit* fAgeBlobID;

    QLineEdit* fCreatorID;
    QLineEdit* fOwnerID;
    QLineEdit* fGroupID;

    QCheckBox* fOwnerRead;
    QCheckBox* fOwnerWrite;
    QCheckBox* fGroupRead;
    QCheckBox* fGroupWrite;
    QCheckBox* fOtherRead;
    QCheckBox* fOtherWrite;
    QComboBox* fNodeType;

    QLineEdit* fInt32_1;
    QLineEdit* fInt32_2;
    QLineEdit* fInt32_3;
    QLineEdit* fInt32_4;
    QLineEdit* fUInt32_1;
    QLineEdit* fUInt32_2;
    QLineEdit* fUInt32_3;
    QLineEdit* fUInt32_4;

    QLineEdit* fString64_1;
    QLineEdit* fString64_2;
    QLineEdit* fString64_3;
    QLineEdit* fString64_4;
    QLineEdit* fString64_5;
    QLineEdit* fString64_6;
    QLineEdit* fIString64_1;
    QLineEdit* fIString64_2;

    QPlainTextEdit* fText_1;
    QPlainTextEdit* fText_2;

    QLabel* fBlob1_Info;
    QLabel* fBlob2_Info;

public:
    QVaultNode();
};

QIcon GetNodeTypeIcon(const plVaultNode& node);
QString GetNodeDisplay(const plVaultNode& node);
QString GetFolderName(const plVaultNode& node);

#endif