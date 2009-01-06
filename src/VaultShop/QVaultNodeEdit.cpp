#include "QVaultNodeEdit.h"

#include "QVaultFolderNode.h"
#include "QVaultTextNode.h"
#include "QVaultSDLNode.h"

/* QVaultNodeEdit */
QVaultNodeEdit::QVaultNodeEdit(QWidget* parent)
              : QWidget(parent)
{ }

QVaultNodeEdit* QVaultNodeEdit::MakeEditor(QWidget* parent, const plVaultNode& node,
                                           plResManager* mgr, plSDLMgr* sdl)
{
    if (!node.isValid())
        return NULL;

    QVaultNodeEdit* editor = NULL;
    switch (node.getNodeType()) {
    case plVault::kNodeFolder:
        editor = new QVaultFolderNode(parent);
        break;
    case plVault::kNodePlayerInfoList:
        editor = new QVaultPlayerInfoList(parent);
        break;
    case plVault::kNodeAgeInfoList:
        editor = new QVaultAgeInfoList(parent);
        break;
    case plVault::kNodeTextNote:
        editor = new QVaultTextNode(parent);
        break;
    case plVault::kNodeSDL:
        editor = new QVaultSDLNode(parent);
        break;
    }

    if (editor != NULL) {
        editor->setMgrs(mgr, sdl);
        editor->setNode(node);
    }
    return editor;
}

void QVaultNodeEdit::setNode(const plVaultNode& node)
{
    fNode = node;
    IRefreshNode();
}

void QVaultNodeEdit::setMgrs(plResManager*, plSDLMgr*)
{ }